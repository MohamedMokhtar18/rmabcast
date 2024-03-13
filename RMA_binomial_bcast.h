#pragma once

#include <mpi.h>
#include "utils.h"
//#include <bits/stdc++.h>

/**
 * @brief Broadcasts data using MPI RMA (Remote Memory Access) with binomial communication pattern.
 * 
 * @param origin_addr Starting address of data buffer to broadcast.
 * @param origin_datatype Datatype of data being broadcasted.
 * @param my_rank Rank of the current process.
 * @param message_length Length of the message.
 * @param nproc Number of processes in the communicator.
 * @param win MPI window object.
 */
void RMA_Bcast_binomial(void* origin_addr, MPI_Datatype origin_datatype, int my_rank,
                     int message_length, int nproc, MPI_Win* win);


/**
 * @brief Helper function to perform the send phase of the binomial broadcast algorithm.
 * 
 * @param origin_addr Starting address of data buffer to send.
 * @param origin_datatype Datatype of data being sent.
 * @param my_rank Rank of the current process.
 * @param iteration Current iteration of the broadcast.
 * @param message_length Length of the message.
 * @param nproc Number of processes in the communicator.
 * @param win MPI window object.
 * @return MPI_SUCCESS on success.
 */
int send_loop(void* origin_addr, MPI_Datatype origin_datatype, int my_rank,int iteration,
              int message_length, int nproc,MPI_Win* win);