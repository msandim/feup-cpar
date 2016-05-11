#include <stdio.h>
#include "mpi.h"

int main( int argc, char **argv)
{
   int rank, size, erro, root = 0;
   float *v1, *v2, *sv1, *sv2;
   int k, j, nelementos, my_k, maisum;
   float mysoma, soma;
   
   // int MPI_Init(int *argc, char ***argv) argc : Pointer to the number of arguments, argv: Argument vector
   MPI_Init( &argc, &argv );

   // int MPI_Comm_size(MPI_Comm comm, int *size) comm: Communicator (handle), size: Number of processes in the group of comm
   MPI_Comm_size( MPI_COMM_WORLD, &size );

   // int MPI_Comm_rank(MPI_Comm comm, int *rank) comm: Communicator (handle), rank: Rank of the calling process in group of comm (integer)
   MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    
    
   if (rank == 0)
   {
   	printf("Tamanho dos vectores ? ");
   	scanf("%d", &k);
   	maisum = (k % size)==0 ? 0 : 1;
   	nelementos = ((k/size)+maisum)*size;
   	v1 = new float[nelementos];
   	v2 = new float[nelementos];
   	for(j=0; j<k; j++)
   	{	v1[j]=j;	v2[j]=1;}
		for(j=k; j<nelementos; j++)
   	{	v1[j]=0;	v2[j]=0;}
   	   	
   }

	// broadcast de k a todos os processos
    MPI_Bcast(&k, 1, MPI_INT, root, MPI_COMM_WORLD);
   
   	// reservar espaco para os dados, o ultimo processador podera ficar com zeros no fim
	maisum = (k % size)==0 ? 0 : 1;
	my_k = (k/size)+maisum;
	sv1 = new float[my_k];
	sv2 = new float[my_k];

	// distribui os dados
	// int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
	erro = MPI_Scatter(v1, my_k, MPI_INT, sv1, my_k, MPI_INT, root, MPI_COMM_WORLD);
	printf("processo %d recebeu %d elementos, erro=%d\n",rank, my_k, erro);    

	erro = MPI_Scatter(v2, my_k, MPI_INT, sv2, my_k, MPI_INT, root, MPI_COMM_WORLD);
	printf("processo %d recebeu %d elementos, erro=%d\n",rank, my_k, erro);    
    
  
   // calcula produto interno
   mysoma = 0.0;
   for(j=0; j<my_k; j++)
   		mysoma += sv1[j]*sv2[j];
   	
   // processo 0 obtem resultado
   // int MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm)
   erro = MPI_Reduce(&mysoma, &soma, 1, MPI_FLOAT, MPI_SUM, root, MPI_COMM_WORLD); 

   	
   if (rank == 0)
   {	printf("Produto interno = %.1f\n", soma);
		delete [] v1;
		delete [] v2;
   }
   delete [] sv1;
   delete [] sv2;
   	
   MPI_Finalize();
    
   return 0;
}
