#include "Mpi_identity.h"
#include <unistd.h>
#include "RMA_linear_bcast.h"
#include "RMA_binary_bcast.h"
#include "RMA_binomial_bcast.h"
#include "benchmark.h"

enum bcast_types_t
{
    linear = 1,
    binomial = 2,
    binary = 3,
    benchmark=4,
    test = 5,
};
bcast_types_t bcast_type = linear;


int main(int argc, char *argv[]){
    bench_type bench_type=linearBench;
    // int provided;
    // MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);
    MPI_Comm comm;
    MPI_Win win=NULL;
    
    void* dataWin[max_length] ;
    MpiId mpiId(&argc, &argv, &comm);
    mpiId.MpiInit();

    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    mpiId.Mpi_allocate(&rank,max_length,sizeof(float),&dataWin,&win);
    if (argc == 3)
    {
        if (std::string(argv[1]) == "linear")
            bcast_type = linear;
        else if (std::string(argv[1]) == "binomial")
            bcast_type = binomial;
        else if (std::string(argv[1]) == "binary")
            bcast_type = binary;
        else if (std::string(argv[1]) == "benchmark")
            {
                bcast_type = benchmark;
                if (std::string(argv[2]) == "linear")
                 bench_type = linearBench;
                 else if (std::string(argv[2]) == "binomial")
                 bench_type = binomialBench;
                 else if (std::string(argv[2]) == "binary")
                 bench_type = binaryBench;
             
            }
        else if (std::string(argv[1]) == "test")
        {
            // filetestbinomial.open("results/resultTestBinomial" + std::to_string(size) + ".dat", std::ios::app); /*create file and open it*/
            // filetestbinary.open("results/resultTestBinary" + std::to_string(size) + ".dat", std::ios::app);     /*create file and open it*/
            // filetestlinear.open("results/resultTestLinear" + std::to_string(size) + ".dat", std::ios::app);     /*create file and open it*/
            // ::testing::InitGoogleTest(&argc, argv);
            // bcast_type = test;
            // int res = RUN_ALL_TESTS();
        }
        else
            throw std::runtime_error("Invalid argument");
    }

    if (rank==0) {
        char data[9] = "Mokhtar";
         if (bcast_type!=benchmark)
      {
         printf("data %s send from rank %d\n",data,rank);

      }
        // RMA_Bcast_Linear(&data,MPI_CHAR,8,size,&win,MPI_COMM_WORLD);
        // RMA_Bcast_binomial(&data,MPI_CHAR,rank,8,size,&win);
        // RMA_Bcast_Binary(&data,MPI_CHAR,rank,8,size,&win);
         if (bcast_type == binomial) {
             RMA_Bcast_binomial(&data,MPI_CHAR,rank,8,size,&win);
         } else if (bcast_type == linear){
             RMA_Bcast_Linear(&data,MPI_CHAR,8,size,&win,MPI_COMM_WORLD);
         } else if (bcast_type == binary){
             RMA_Bcast_Binary(&data,MPI_CHAR,rank,8,size,&win);
         }  
        }
        
        if (bcast_type==benchmark){
             run_benchmark(MPI_COMM_WORLD,rank,size,dataWin,&bench_type,std::string(argv[2]),&win);
             }


     if (rank!=0){
      while (!(*dataWin)){}
      if (bcast_type!=benchmark)
      {
         printf("receved data %s at rank %d \n",dataWin,rank);

      }
      
    }
    mpiId.MPIFinish(&win);

} 