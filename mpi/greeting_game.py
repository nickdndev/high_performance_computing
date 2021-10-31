import random

from mpi4py import MPI

N = 6

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

ranks = list(range(0, size))

if rank == 0:
    print(f"Process [{rank}]:", "Let's start")
    ranks.remove(rank)
    destination = random.choice(ranks)
    print(f"Process [{rank}] will send to {destination} process")
    comm.send([rank], dest=destination)
else:
    ranks.remove(rank)
    data_from_another_process = comm.recv()
    print(f"Process {rank} get data {data_from_another_process}")

    for processed_rank in data_from_another_process:
        ranks.remove(processed_rank)

    if ranks and len(data_from_another_process) < N - 1:
        destination = random.choice(ranks)
        data_from_another_process.append(rank)

        print(f"Process [{rank}] will send to {destination} process")
        comm.send(data_from_another_process, dest=destination)
    else:
        print(f"Process {rank}:", "Finished")
        MPI.Finalize()
