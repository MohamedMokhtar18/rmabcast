#include "benchmark.h"  


void run_benchmark(MPI_Comm comm, int rank, int size,void* dataWin,bench_type* benchType,std::string type,MPI_Win* win){
 if (rank == 0 )
    {
        std::fstream file; /* value for result file*/
        std::fstream fileBench;
        file.open("results/result" + type + std::to_string(size) + ".dat", std::ios::out); /*create file and open it*/
        fileBench.open("results/result" + type + std::to_string(size) + "Bench.dat", std::ios::out);
        fileBench << "    message size      transfertime  duplex bandwidth per process and neighbor" << std::endl;
        printf("    message size      transfertime  duplex bandwidth per process and neighbor\n");
        double start, finish, transfer_time;
        int i, length, test_value;
        length = start_length;

        float snd_buf[max_length]; //[max_length];

        for (int j = 1; j <= number_package_sizes; j++)
        {
            for (i = 0; i <= number_of_messages; i++)
            {
                if (i == 1)
                    start = MPI_Wtime(); // start the timer
                test_value = j * 1000000 + i * 10000 + rank * 10;
                intialize_send_buffer(snd_buf, test_value, length, i);
                // Todo make a generic method for each type to be compared
                //RMA_Bcast_binomial(snd_buf,MPI_FLOAT,rank,max_length,size,win);
                if (*benchType == binomialBench){
                 RMA_Bcast_binomial(snd_buf,MPI_FLOAT,rank,length,size,win);
                 }else if (*benchType == linearBench){
                 RMA_Bcast_Linear(snd_buf,MPI_FLOAT,length,size,win,MPI_COMM_WORLD);
                } else if (*benchType == binaryBench){
                 RMA_Bcast_Binary(snd_buf,MPI_FLOAT,rank,length,size,win);
                 }

            }
            finish = MPI_Wtime();
            if (rank == 0)
            {
                transfer_time = (finish - start) / number_of_messages; // calculate transfer message for each pacakge
                 fileBench << std::setw(10) << length * sizeof(float) << " bytes " << std::setw(12) << transfer_time * 1e3 << " Msec " << std::setw(13) << 1.0e-6 * 2 * length * sizeof(float) / transfer_time << " MB/s" << std::endl;
                printf("%10i bytes %12.3f Msec %13.3f MB/s\n",
                       length * (int)sizeof(float), transfer_time * 1e3, 1.0e-6 * 2 * length * sizeof(float) / transfer_time);
            }
            length = length * length_factor;
        }
      
    }
   
}

void intialize_send_buffer(float* snd_buf, int test_value, int length, int message_number)
{
    int mid = (length - 1) / number_of_messages * message_number;
    snd_buf[0] = test_value + 1;
    snd_buf[mid] = test_value + 2;
    snd_buf[length - 1] = test_value + 3;
}

