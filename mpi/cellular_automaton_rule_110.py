import random

from mpi4py import MPI

STEPS = 10
CELLS_PER_PROCESS = 10

comm = MPI.COMM_WORLD
rank = comm.Get_rank()

size = comm.Get_size()

ring_1d = comm.Create_cart(dims=[size], periods=[False], reorder=False)
ring_1d_rank = ring_1d.Get_rank()

cells = [int(random.random() < 0.5) for i in range(CELLS_PER_PROCESS + 2)]
res = ring_1d.gather(cells[1:-1], root=0)


def draw_cells(result):
    result = sum(result, [])
    print(''.join(['x' if i else ' ' for i in result]))


if ring_1d_rank == 0:
    draw_cells(res)

for step in range(STEPS):
    left, right = ring_1d.Shift(direction=0, disp=1)

    if right >= 0:
        ring_1d.send(cells[-2], dest=right, tag=step)

    if left >= 0:
        ring_1d.send(cells[1], dest=left, tag=step)

    if right >= 0:
        cells[-1] = ring_1d.recv(source=right, tag=step)

    if left >= 0:
        cells[0] = ring_1d.recv(source=left, tag=step)

    new_cells = [None for i in range(len(cells))]

    for i in range(1 + (left < 0), CELLS_PER_PROCESS + 1 - (right < 0)):
        if cells[i - 1:i + 2] in [
            [1, 1, 1], [1, 0, 0], [0, 0, 0]
        ]:
            new_cells[i] = 0
        else:
            new_cells[i] = 1

    cells = new_cells

    res = ring_1d.gather(cells[1:-1], root=0)

    if ring_1d_rank == 0:
        draw_cells(res)
