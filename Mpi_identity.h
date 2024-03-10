#ifndef MPI_IDENTITY_H
#define MPI_IDENTITY_H
#include <mpi.h>
class MpiId {
    
private:
    int provided;
    int *argc;
    char ***argv;
    MPI_Comm* comm;
    MPI_Win* win;
public:
    // Constructor
    MpiId(int *argc, char ***argv, MPI_Comm *comm_sm);

    // Getter functions
    int MpiInit() ;
    int Mpi_allocate(int *rank,int size,int disp_unit,void *rcv_buf,MPI_Win *win);
    int MPIFinish(MPI_Win *win) ;
};
#endif