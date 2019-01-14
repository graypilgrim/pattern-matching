#ifndef UTILS_HPP
#define UTILS_HPP

#include <mpi.h>

#include <vector>

namespace utils
{
    inline int getProcessorsCount() {
        int x;
        MPI_Comm_size(MPI_COMM_WORLD, &x);
        return x;
    }

    inline int getProcessorNo() {
        int x;
        MPI_Comm_rank(MPI_COMM_WORLD, &x);
        return x;
    }

    inline void mpiSend(const unsigned char* data, int dataLen, int dest) {
        auto ret = MPI_Send(data, dataLen, MPI_BYTE, dest, 0, MPI_COMM_WORLD);
        if (ret != MPI_SUCCESS)
            std::cout << "MPI_Isend error: " << ret << std::endl;
    }

    inline void mpiIrecv(unsigned char* data, int dataLen, int source, MPI_Request *request) {
        auto ret = MPI_Irecv(data, dataLen, MPI_BYTE, source, 0, MPI_COMM_WORLD, request);
        if (ret != MPI_SUCCESS)
            std::cout << "MPI_Irecv error: " << ret << std::endl;
    }
}

#endif /* end of include guard: UTILS_HPP */
