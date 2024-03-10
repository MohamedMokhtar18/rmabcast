#include <mpi.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]){

    // {
    //     int i=0;
    //     while (0 == i)
    //         sleep(5);
    // }

    MPI_Init(&argc,&argv);
    int rank,size;
    MPI_Win win=NULL;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    char data[9] = "fuck you";
    char dataWin[9] ;
    
    MPI_Win_create(&dataWin, 10*sizeof(char),10*sizeof(char), MPI_INFO_NULL, MPI_COMM_WORLD, &win);
    if (rank==0) {
        printf("data %s send from rank %d\n",data,rank);

        for (int i = 1; i < size; i++)
        {
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, i, 0, win);
         MPI_Put(&data, 8, MPI_CHAR, i, 0, 8, MPI_CHAR, win);
        MPI_Win_unlock(i, win);        
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);

     if (rank!=0){
      while (dataWin==""||dataWin==NULL)
      {
        /* code */
      }
      
        printf("rceved data %s at rank %d \n",dataWin,rank);

    }
MPI_Win_free(&win);
MPI_Finalize();
} 