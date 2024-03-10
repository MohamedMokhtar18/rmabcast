#include "RMA_linear_bcast.h"
/**
 * @brief Broadcasts data using MPI RMA (Remote Memory Access) with linear communication pattern.
 * 
 * @param origin_addr Starting address of data buffer to broadcast.
 * @param origin_datatype Datatype of data being broadcasted.
 * @param message_length Length of the message.
 * @param nproc Number of processes in the communicator.
 * @param win MPI window object.
 * @param comm MPI communicator.
 * @return MPI_SUCCESS on success, or an MPI error code on failure.
 */

int RMA_Bcast_Linear(const void *origin_addr, MPI_Datatype origin_datatype,
                     int message_length, int nproc, MPI_Win* win, MPI_Comm comm)
{

    // Iterate over all processes except rank 0 to broadcast data
    for (int rank = 1; rank < nproc; rank++)
    {
        // Lock the target window on process 'rank'
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, *win);
        
        // Perform the MPI Put operation to broadcast data from origin process to process 'rank'
        int result = MPI_Put(origin_addr, message_length, origin_datatype,
                             rank, 0, message_length, origin_datatype, *win);
        
        // Unlock the window
        MPI_Win_unlock(rank, *win);                    
        
        // Check if the MPI_Put operation was successful, if not abort the communicator
        if (result != MPI_SUCCESS)
            MPI_Abort(comm, result);
    }

    return MPI_SUCCESS;
}
