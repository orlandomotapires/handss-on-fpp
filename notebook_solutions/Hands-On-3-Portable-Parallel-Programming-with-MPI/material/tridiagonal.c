#include <stdio.h>
#include <mpi.h>
#define ORDER 4

void printMatrix (int m[][ORDER]) 
{
  int i, j;
  for(i = 0; i < ORDER; i++) {
    printf ("| ");
    for (j = 0; j < ORDER; j++) {
      printf ("%3d ", m[i][j]);
    }
    printf ("|\n");
  }
  printf ("\n");
}

int main (int argc, char **argv){
  int k[3] = {100, 200, 300};
  int matrix[ORDER][ORDER] = {0}, received_matrix[ORDER][ORDER], i, j;
  
  int tag = 1000, numberOfProcessors, id;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcessors);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Status status;

  if(id == 0) {
    for(int to = 1; to < numberOfProcessors; to++) {
      MPI_Send(&matrix, ORDER * ORDER, MPI_INT, to, tag, MPI_COMM_WORLD);
    }
    for(i = 1; i < numberOfProcessors; i++){
      MPI_Recv(&received_matrix, ORDER * ORDER, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
      int worker_id = status.MPI_SOURCE;
      switch(worker_id){
        case 1:
          for(j = 0; j < ORDER; j++) matrix[j][j]     += received_matrix[j][j];    //main diagonal           
          break;
        case 2:
          for(j = 0; j < ORDER; j++) {
            matrix[j + 1][j] += received_matrix[j + 1][j];    //subdiagonal
            matrix[j][j + 1] += received_matrix[j][j + 1];    //superdiagonal
          }
          break;
        case 3:
          for(j = 0; j < ORDER; j++) {
            if(!(j == (ORDER - 1))) matrix[j][j + 1] += received_matrix[j][j + 1];    //superdiagonal
            if(!(j == 0)) matrix[j][j - 1] += received_matrix[j][j - 1];    //subdiagonal
          }
          break;
      }
    }
  } else {
    MPI_Recv(&matrix, ORDER * ORDER, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
    switch(id){
      case 1:
        for(i = 0; i < ORDER; i++)
          for(j = 0; j < ORDER; j++) if( i == j ) matrix[i][j] = i + j + 1 + k[0];             
        break;
      case 2:
        for(i = 0; i < ORDER; i++)
          for(j = 0; j < ORDER; j++) if(i == (j + 1)){
            matrix[i][j] = i +  j + 1 + k[1];
            matrix[j][i] = matrix[i][j] + k[2];
          }
        break;
      case 3:
        for(i = 0; i < ORDER; i++)
          for(j = 0; j < ORDER; j++) if(!(i == j) && !(i == (j + 1))) matrix[i][j] = 0;
        break;
    }
    MPI_Send(&matrix, ORDER * ORDER, MPI_INT, 0, tag, MPI_COMM_WORLD);
  }

  printf("ID: %d\n", id);
  printMatrix(matrix);

  MPI_Finalize();
  return 0;
}
