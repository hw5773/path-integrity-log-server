#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <getopt.h>

#define BUF_SIZE 16384
#define TS_SIZE 256

#define DEFAULT_PORT 5555
#define DEFAULT_OUTPUT_FILENAME "output_stderr.out"
#define DEFAULT_INTERVAL 5
#define DEFAULT_NUM_OF_LINES 10
#define DEFAULT_EXIT_INTERVAL 30
#define DEFAULT_SHELL_SCRIPT "runTamarinShell.sh"

FILE *fp = NULL;
int clnt_sock = 0;
int serv_sock = 0;

void error_handling(char *message);
void sigint_handler(int signo);
int usage(const char *pname);

int main(int argc, char *argv[])
{
  FILE *sfp;
  int recv, c, cnt, logging, port, interval, lines, incoming, exit;
  time_t curr, prev, t1, t2;
  const char *pname, *output, *script;
  char *ptr;
  struct tm *info;

	struct sockaddr_in serv_addr, clnt_addr;
	socklen_t clnt_addr_size;

  char buf[BUF_SIZE] = {0, };
  char tmp[TS_SIZE] = {0, };

  sfp = NULL;
  pname = argv[0];
  signal(SIGINT, sigint_handler);

  port = DEFAULT_PORT;
  output = DEFAULT_OUTPUT_FILENAME;
  interval = DEFAULT_INTERVAL;
  lines = DEFAULT_NUM_OF_LINES;
  exit = DEFAULT_EXIT_INTERVAL;
  script = DEFAULT_SHELL_SCRIPT;

  while (1)
  {
    int index = 0;
    static struct option long_options[] = {
      {"port", required_argument, 0, 'p'},
      {"output", required_argument, 0, 'o'},
      {"interval", required_argument, 0, 'i'},
      {"lines", required_argument, 0, 'l'},
      {"exit", required_argument, 0, 'e'},
      {"script", required_argument, 0, 's'},
      {"help", required_argument, 0, 'h'},
      {0, 0, 0, 0}
    };

    c = getopt_long(argc, argv, "p:o:i:l:e:s:h:0", long_options, &index);

    if (c == -1)
      break;

    switch (c)
    {
      case 'p':
        port = atoi(optarg);
        break;
      case 'o':
        output = optarg;
        break;
      case 'i':
        interval = atoi(optarg);
        break;
      case 'l':
        lines = atoi(optarg);
        break;
      case 'e':
        exit = atoi(optarg);
        break;
      case 's':
        script = optarg;
        break;
      case 'h':
      default:
        usage(pname);
    }
  }

  if (access(script, F_OK) == -1)
  {
      printf(">> ERROR: %s does not exist\n", script);
      printf(">> ERROR: Please input the path of the shell script correctly\n");
      usage(pname);
  }

  fp = fopen(output, "w");
  curr = time(NULL);
  info = localtime(&curr);
  strftime(tmp, TS_SIZE, "%x - %X", info);

  fprintf(fp, ">> Setting for the log server at %s\n", tmp);
  fprintf(stderr, ">> INFO: %s: Setting for the log server\n", tmp);
  fprintf(fp, "port: %d\n", port);
  fprintf(stderr, "port: %d\n", port);
  fprintf(fp, "output file name: %s\n", output);
  fprintf(stderr, "output file name: %s\n", output);
  fprintf(fp, "interval (seconds): %d\n", interval);
  fprintf(stderr, "interval (seconds): %d\n", interval);
  fprintf(fp, "num of log lines: %d\n", lines);
  fprintf(stderr, "num of log lines: %d\n", lines);
  fprintf(fp, "waiting time (seconds): %d\n", exit);
  fprintf(stderr, "waiting time (seconds): %d\n", exit);
  fprintf(fp, "script file: %s\n\n", script);
  fprintf(stderr, "script file: %s\n", script);

  fprintf(fp, ">> Logging starts at %s (Configuration below)\n", tmp);
  fprintf(stderr, ">> INFO: %s: Configuration below\n", tmp);

  sfp = fopen(script, "r");
  while (feof(sfp) == 0)
  {
    memset(buf, 0x0, BUF_SIZE);
    fgets(buf, BUF_SIZE, sfp);
    if (buf[0] != '#' || buf[1] != 'S')
      continue;
    fprintf(fp, "%s", buf);
    fprintf(stderr, "%s", buf);
  }
  fclose(sfp);

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);

	if (bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1)
		error_handling("bind() error");
	
	if (listen(serv_sock, 5) == -1)
		error_handling("listen() error");
	
	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (struct sockaddr *) &clnt_addr, &clnt_addr_size);
	if (clnt_sock == -1)
		error_handling("accept() error");

  prev = 0;
  logging = 0;
  incoming = 0;
  t1 = time(NULL);
  t2 = time(NULL);
  cnt = 0;

  while (1)
  {
    recv = read(clnt_sock, buf, BUF_SIZE-1);
    if (recv > 0)
    {
      incoming = 1;
      curr = time(NULL);
      info = localtime(&curr);
      strftime(tmp, TS_SIZE, "%x - %X", info);

      if (curr - prev > interval)
      {
        printf(">> INFO: %s: Logging enabled\n", tmp);
        info = localtime(&curr);
        strftime(tmp, TS_SIZE, "%x - %X", info);
        fprintf(fp, "\n>> Logging at %s\n", tmp);
        prev = curr;
        logging = 1;
        cnt = 0;
      }

      if (logging && cnt >= lines)
      {
        printf(">> INFO: %s: Logging disabled (%d lines are logged to %s)\n", 
            tmp, cnt, output);
        logging = 0;
        cnt = 0;
      }

      if (logging)
      {
        if (recv < BUF_SIZE)
          buf[recv] = 0;
        cnt++;
        fprintf(fp, "%s", buf);
        memset(buf, 0x0, sizeof(buf));
      }
    }
    else
    {
      t2 = time(NULL);
      if (incoming)
        t1 = time(NULL);
      incoming = 0;

      if (t2 - t1 > exit)
      {
        curr = t2;
        info = localtime(&curr);
        strftime(tmp, TS_SIZE, "%x - %X", info);
        printf(">> INFO: %s: No log messages for %d seconds\n", tmp, exit); 
        break;
      }
    }
  }

  printf(">> INFO: Finalizing the log server\n");
  close(clnt_sock);
  close(serv_sock);
  fclose(fp);

	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

void sigint_handler(int signo)
{
  printf(">> INFO: Finalizing the log server\n");

  if (fp)
    fclose(fp);

  if (clnt_sock > 0)
    close(clnt_sock);

  if (serv_sock > 0)
    close(serv_sock);

  exit(0);
}

int usage(const char *pname)
{
  printf(">> Usage: %s [options]\n", pname);
  printf(">> Options\n");
  printf("  -p, --port\tPort number\n");
  printf("  -o, --output\tOutput file name\n");
  printf("  -i, --interval\tInterval time between two logging periods\n");
  printf("  -l, --lines\tNumber of lines to be logged during the logging period\n");
  printf("  -e, --exit\tWaiting time (If there is no logs during this time, then the applications is exited\n");
  printf("  -s, --script\tPath of the running script file\n");
  printf("  -h, --help Help message (This message)\n");
  printf(">> Example: ./log_server --port 5555 --output log.out --interval 30 --lines 100, --exit 300 --script runTamarinShell.sh\n");
  exit(1);
}

