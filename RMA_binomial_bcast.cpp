#include "RMA_binomial_bcast.h" // Include the header file

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
                     int message_length, int nproc, MPI_Win* win)
{
    int result; // Variable to store MPI function call results
    
        // Call send_loop function for each iteration
        result = send_loop(origin_addr, origin_datatype, my_rank, my_rank, message_length, nproc, win);
    
}

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
int send_loop(void* origin_addr, MPI_Datatype origin_datatype, int my_rank, int iteration,
              int message_length, int nproc, MPI_Win* win)
{
    int result; // Variable to store MPI function call results
    int srank = comp_srank(my_rank, 0, nproc); // Compute rank relative to root
    auto mask = 1;
    while (mask < nproc)
    {
        if ((srank & mask) == 0)
        { // send data to the next process if bit is not set
            auto rank = srank | mask;
            if (rank < nproc)
            {
                rank = comp_rank(rank, iteration, nproc); // Compute rank from srank
                // Lock the target window on the destination process
                if (rank ==0)
                {
                    break;
                }
                
                MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, *win);
                // Perform the MPI Put operation to send data to the destination process
                MPI_Put(origin_addr, message_length, origin_datatype, rank, 0, message_length, origin_datatype, *win);
                // Unlock the window
                MPI_Win_unlock(rank, *win);
            }
            else
            {
                // If bit is set, break (in the original non-RMA algorithm, it's the receive phase)
                break;
            }
            mask = mask << 1;
        }
    }
    return MPI_SUCCESS;
}