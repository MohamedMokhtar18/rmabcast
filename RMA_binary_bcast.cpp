#include "RMA_binary_bcast.h" // Include the header file

/**
 * @brief Broadcasts data using MPI RMA (Remote Memory Access) with binary communication pattern.
 * 
 * @param origin_addr Starting address of data buffer to broadcast.
 * @param origin_datatype Datatype of data being broadcasted.
 * @param message_length Length of the message.
 * @param nproc Number of processes in the communicator.
 * @param win MPI window object.
 * @return MPI_SUCCESS on success, or an MPI error code on failure.
 */
int RMA_Bcast_Binary(void* origin_addr, MPI_Datatype origin_datatype,
                    int message_length, int nproc, MPI_Win* win)
{
    int result; // Variable to store MPI function call results
    int rank; // Process rank
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the process
    
    // Iterate through powers of 2 to determine communication partners
    for (int i = 1; i < nproc; i *= 2) {
        int partner = rank ^ i; // Determine the partner process using bitwise XOR
        if (partner < nproc) {
            // Lock the target window on the partner process
            MPI_Win_lock(MPI_LOCK_EXCLUSIVE, partner, 0, *win);
            if (rank < partner) {
                // Perform the MPI Put operation to broadcast data from origin process to partner process
                result = MPI_Put(origin_addr, message_length, origin_datatype, partner, 0, message_length, origin_datatype, *win);
            }
            // Unlock the window
            MPI_Win_unlock(partner, *win);
        }
    }
    
    return result; // Return the MPI function call result
}