#include <stdio.h>
#include <mpi.h>

int main (int argc, char **argv){
    double coef[4], result[4], x = 10, total, received_result;   
    int tag = 1000, numberOfProcessors, id, to, from, i, id_indexed, received_index;

    for(i = 1; i <= 4; i++) coef[i-1] = i;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcessors);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Status status;

    switch(id){
        case 0: //Master
            for(to = 1; to < numberOfProcessors; to++) {
                MPI_Send(&x, 1, MPI_DOUBLE, to, tag, MPI_COMM_WORLD);
            }
            break;

        default: // Workers
            MPI_Recv(&x, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &status);
            
            id_indexed = 3 - id;
            result[id_indexed] = coef[id_indexed];
            for(i = 1; i <= id; i++)
                result[id_indexed] *= x;
            break;
    }

    MPI_Send(&result[id_indexed], 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
    MPI_Send(&id_indexed, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);

    if(id == 0) {
        for(from = 1; from < numberOfProcessors; from++) {
            MPI_Recv(&received_result, 1, MPI_DOUBLE, from, tag, MPI_COMM_WORLD, &status);
            MPI_Recv(&received_index, 1, MPI_INT, from, tag, MPI_COMM_WORLD, &status);
            result[received_index] = received_result;
            printf ("(%d) = %lf\n", received_index, result[received_index]);
            total += received_result;
        }

        if(total > 0) printf("Total: %.5lf\n", total);
    }

    MPI_Finalize();
    return 0;
}
