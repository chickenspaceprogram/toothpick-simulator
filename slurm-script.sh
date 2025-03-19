#!/bin/bash
#SBATCH --partition=hpc_club
#SBATCH --job-name=toothpick-toss-sim
#SBATCH --output=out/sim.out
#SBATCH --error=out/sim.err
#SBATCH --mail-type=FAIL
#SBATCH --mail-user=timothy.boose@wsu.edu
#SBATCH --time=1-00:00:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=40

srun ./build.sh
srun ./run.sh
