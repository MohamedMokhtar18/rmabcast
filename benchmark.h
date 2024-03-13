#pragma once
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include <mpi.h>
#include "RMA_binary_bcast.h" // Include the header file
#include "RMA_binomial_bcast.h"
#include "RMA_linear_bcast.h"
#define start_length 4        /*length of the array */
#define max_length 8388608           /* ==> 2 x 32 MB per process */
#define number_package_sizes 8       /*number of package sizes for each size 16,128,...*/
#define length_factor 8
#define number_of_messages 50 /*number of messages transfered per package */
enum bench_type
{
    linearBench = 1,
    binaryBench = 2,
    binomialBench = 3,
};
void run_benchmark(MPI_Comm comm, int rank, int size,void* dataWin,bench_type* benchType,std::string type,MPI_Win* win);
void intialize_send_buffer(float* snd_buf, int test_value, int length, int message_number);