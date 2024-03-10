#include "Mpi_identity.h"
#include <unistd.h>
#include "RMA_linear_bcast.h"

using namespace std;

int main(int argc, char *argv[]){
    // int provided;
    // MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);
    MPI_Comm comm;
    MPI_Win win=NULL;
    char data[9] = "Mokhtar";
    char dataWin[9] ;
    MpiId mpiId(&argc, &argv, &comm);
    mpiId.MpiInit();

    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    mpiId.Mpi_allocate(&rank,10,sizeof(char),&dataWin,&win);

    if (rank==0) {
        printf("data %s send from rank %d\n",data,rank);
        RMA_Bcast_Linear(&data,MPI_CHAR,8,size,&win,MPI_COMM_WORLD);
    }

     if (rank!=0){
      while (!(*dataWin)){}
      printf("receved data %s at rank %d \n",dataWin,rank);
    }
    mpiId.MPIFinish(&win);

} 