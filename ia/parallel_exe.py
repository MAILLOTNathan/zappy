#!/usr/bin/python3

import multiprocessing
import subprocess

def run_script(team_name, id):
    subprocess.run(["./pytorchAI", "-p", "4243", "-n", team_name, "-h", "localhost", "-id", str(id)])

if __name__ == "__main__":
    num_instances =  2
    processes = []

    for i in range(num_instances):
        team_name = f"team{i}"
        p = multiprocessing.Process(target=run_script, args=(team_name, i))
        p.start()
        processes.append(p)

    for p in processes:
        p.join()
