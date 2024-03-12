#pragma once

#include <mpi.h>
#include "utils.h"
//#include <bits/stdc++.h>

void RMA_Bcast_binomial(void* origin_addr, MPI_Datatype origin_datatype, int my_rank,
                     int message_length, int nproc, MPI_Win* win);
int send_loop(void* origin_addr, MPI_Datatype origin_datatype, int my_rank,int iteration,
              int message_length, int nproc,MPI_Win* win);