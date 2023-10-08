#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[])
{
    int nthreads,nprocs,idpro,idthr;
    int  namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&idpro);
    MPI_Get_processor_name(processor_name,&namelen);

    #pragma omp parallel private(idthr) firstprivate(idpro,processor_name)
    {
    idthr = omp_get_thread_num();
    printf("Hello World  thread %d,From %d processor %s\n",idthr,idpro,processor_name);
    }

    MPI_Finalize();
}
