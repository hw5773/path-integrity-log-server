#!/bin/sh
#SBATCH --mail-type=end,fail
#SBATCH --mail-user=zach.smith@uni.lu
#SBATCH -n 40
#SBATCH --time=0:59:0
#SBATCH -p batch
#SBATCH --qos=qos-batch
#SBATCH --mem=64GB

generate_output_file()
{
  str=$1
  name=`expr $str | cut -d'.' -f 1`
  echo $name.txt
}

echo "== Starting run at $(date)"
echo "== Job ID: ${SLURM_JOBID}, Task ID: ${SLURM_ARRAY_TASK_ID}"
echo "== Node list: ${SLURM_NODELIST}"
echo "== Submit dir. : ${SLURM_SUBMIT_DIR}"

tamarin-prover \
  $1 \
  --heuristic=O --oraclename=batchWrapper.sh \
  --prove \
  1>$(generate_output_file $1) \
  2>/dev/null
