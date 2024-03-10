#pragma once

#include <mpi.h>
//#include <bits/stdc++.h>

int RMA_Bcast_Binary(void* origin_addr, MPI_Datatype origin_datatype,
                    int message_length, int nproc, MPI_Win* win);
                    