#pragma once

#include <mpi.h>
int RMA_Bcast_Linear(const void *origin_addr, MPI_Datatype origin_datatype,
                     int message_length, int nproc, MPI_Win* win, MPI_Comm comm);