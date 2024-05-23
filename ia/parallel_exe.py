import multiprocessing
import subprocess

def run_script():
    subprocess.run(["./pytorchAI", "-p", "4242", "-n", "cedric", "-h", "localhost"])

if __name__ == "__main__":
    num_instances = 1
    processes = []

    for _ in range(num_instances):
        p = multiprocessing.Process(target=run_script)
        p.start()
        processes.append(p)

    for p in processes:
        p.join()
