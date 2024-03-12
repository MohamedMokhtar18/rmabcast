
#pragma once // Ensures that this header file is included only once during compilation

// comp_srank: Compute rank relative to root
// Parameters:
//   myrank: Rank of the current process
//   root: Rank of the root process
//   nproc: Total number of processes
// Returns:
//   The relative rank of the current process with respect to the root process
inline int comp_srank(int myrank, int root, int nproc)
{
    return (myrank - root + nproc) % nproc; // Compute relative rank
}

// comp_rank: Compute rank from srank
// Parameters:
//   srank: Relative rank
//   root: Rank of the root process
//   nproc: Total number of processes
// Returns:
//   The absolute rank of the process given its relative rank and the root process
inline int comp_rank(int srank, int root, int nproc)
{
    return (srank + root) % nproc; // Compute absolute rank
}