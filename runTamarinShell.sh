#!/bin/sh
#SBATCH --mail-type=end,fail
#SBATCH --mail-user=zach.smith@uni.lu
#SBATCH -n 40
#SBATCH --time=0:59:0
#SBATCH -p batch
#SBATCH --qos=qos-batch
#SBATCH --mem=64GB

LOG_SERVER=log_server
LOG_SERVER_ADDR=127.0.0.1
LOG_SERVER_PORT=5555
LOG_DIRECTORY=output

INTERVAL=30
NUM_OF_LINES=1000
EXIT_CONDITION=300

generate_output_file()
{
  str=$1
  name=`echo $str | rev | cut -d'/' -f 1 | rev`
  ofname=`echo $name | cut -d'.' -f 1`
  ts=$(date +"%d-%m-%y_%H:%M:%S")
  echo $LOG_DIRECTORY/${ofname}_stdout_${ts}.out
}

if [ "$#" -ne 1 ] || [ "$#" -ge 2 ]; then
  echo ">> Usage: $0 <spthy file path>" >&2
  exit 1
fi

mkdir -p $LOG_DIRECTORY

test -f $LOG_SERVER || echo "== Make the log server"; make
#test -f $LOG_SERVER || echo "Please locate the log server in the same directory"; exit 1
echo "== Starting the log server"
./$LOG_SERVER -p $LOG_SERVER_PORT -d $LOG_DIRECTORY -t $1 -i $INTERVAL \
  -l $NUM_OF_LINES -e $EXIT_CONDITION -s $0 &
echo "./$LOG_SERVER -p $LOG_SERVER_PORT -d $LOG_DIRECTORY -t $1 -i $INTERVAL \
  -l $NUM_OF_LINES -e $EXIT_CONDITION -s $0 &"

echo "== Starting run at $(date)"
echo "== Job ID: ${SLURM_JOBID}, Task ID: ${SLURM_ARRAY_TASK_ID}"
echo "== Node list: ${SLURM_NODELIST}"
echo "== Submit dir. : ${SLURM_SUBMIT_DIR}"

(tamarin-prover \
  $1 \
  --prove \
  3>&1 1>&2 2>&3 \
  | nc $LOG_SERVER_ADDR $LOG_SERVER_PORT
) 2>$(generate_output_file $1)
