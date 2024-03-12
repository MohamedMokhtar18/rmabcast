#pragma once

#include <mpi.h>
//#include <bits/stdc++.h>

int RMA_Bcast_Binary(void* origin_addr, MPI_Datatype origin_datatype, int my_rank,
                     int message_length, int nproc, MPI_Win* win);

int send_loop_binary(void* origin_addr, MPI_Datatype origin_datatype, int my_rank,int iteration,
              int message_length, int nproc,MPI_Win* win);
                    