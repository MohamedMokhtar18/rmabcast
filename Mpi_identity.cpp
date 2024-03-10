#include "Mpi_identity.h"
MpiId::MpiId(int *argc, char ***argv, MPI_Comm *comm_sm){
    this->argc=argc;
    this->argv=argv;
    this->comm=comm_sm;
}

int MpiId::MpiInit(){
   return MPI_Init_thread(argc, argv, MPI_THREAD_FUNNELED, &provided);
}
int MpiId::Mpi_allocate(int *rank,int size,int disp_unit,void *rcv_buf,MPI_Win *win){
  // MPI_Comm_split_type(MPI_COMM_WORLD, MPI_COMM_TYPE_SHARED, 0, MPI_INFO_NULL, comm);
//  return MPI_Win_allocate_shared(size * disp_unit, disp_unit, MPI_INFO_NULL, MPI_COMM_WORLD, rcv_buf, win);
return MPI_Win_create(rcv_buf, (MPI_Aint)size * disp_unit, size *disp_unit, MPI_INFO_NULL, MPI_COMM_WORLD, win);
}
int MpiId::MPIFinish(MPI_Win *win){
  MPI_Win_free(win);
  return MPI_Finalize();
}