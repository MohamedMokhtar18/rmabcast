#include "RMA_binary_bcast.h" // Include the header file

/**
 * @brief Broadcasts data using MPI RMA (Remote Memory Access) with binary communication pattern.
 * 
 * @param origin_addr Starting address of data buffer to broadcast.
 * @param origin_datatype Datatype of data being broadcasted.
 * @param my_rank Rank of the current process.
 * @param message_length Length of the message.
 * @param nproc Number of processes in the communicator.
 * @param win MPI window object.
 * @return MPI_SUCCESS on success.
 */
int RMA_Bcast_Binary(void* origin_addr, MPI_Datatype origin_datatype, int my_rank,
                     int message_length, int nproc, MPI_Win* win)
{
    int result; // Variable to store MPI function call results
    for (int i = 0; i < nproc; i++)
    {
        // Call send_loop_binary function for each iteration
        result = send_loop_binary(origin_addr, origin_datatype, my_rank, i, message_length, nproc, win);
    }

    return result; // Return the result
}

/**
 * @brief Helper function to perform the send phase of the binary broadcast algorithm.
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
int send_loop_binary(void* origin_addr, MPI_Datatype origin_datatype, int my_rank, int iteration,
              int message_length, int nproc, MPI_Win* win)
{
    int result; // Variable to store MPI function call results
    int rank = (my_rank - 0 + nproc) % nproc; // reorder, so fake root is zero
    int child1 = 2 * rank + 1;
    int child2 = 2 * rank + 2;
    
    if (child1 < nproc)
    {
        child1 = (child1 + iteration) % nproc; // mapping to real
        // Lock the target window on the first child
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, child1, 0, *win);
        // Perform the MPI Put operation to send data to the first child
        MPI_Put(origin_addr, message_length, origin_datatype, child1, 0, message_length, origin_datatype, *win);
        // Unlock the window
        MPI_Win_unlock(child1, *win);
    }
    
    if (child2 < nproc)
    {
        child2 = (child2 + iteration) % nproc; // mapping to real
        // Lock the target window on the second child
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, child2, 0, *win);
        // Perform the MPI Put operation to send data to the second child
        MPI_Put(origin_addr, message_length, origin_datatype, child2, 0, message_length, origin_datatype, *win);
        // Unlock the window
        MPI_Win_unlock(child2, *win);
    }
    
    return MPI_SUCCESS; // Return success
}