#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//int A [3][4] = { {5,8,10,2}, {7,9,5,1}, {6,0,8,12} };
int **A;
//int B [4][2] = { {22,13}, {1,5}, {9,7}, {17,9} } ;
int **B;
int **C;
int comun;

struct v {
   int i; /* fila */
   int j; /* columna */
};

void *multi(void *param); 

int main(int argc, char *argv[]) {

   
   int f1,c1,c2,f2, i,j, count = 0;
   time_t t;
   int control = 0;
   
   srandom(time(&t));
   
   
   while(control == 0){
      printf("matriz_hilos ");
      scanf("%d %d %d %d",&f1,&c1,&f2,&c2);
      
      if(c1 != f2){
         system("clear");
         printf("Las matrices no se pueden multiplicar. Ingrese los valores nuevamente\n");
      }
      else{
         comun = c1;
         control = 1;
      }
   }
   
   //Reservamos espacio de memoria para las matrices 
   A =  malloc(f1*sizeof(int*)); 
      for(i=0;i<f1;i++)
        A[i]=malloc(c1*sizeof(int));
   B =  malloc(f2*sizeof(int*)); 
      for(i=0;i<f2;i++)
        B[i]=malloc(c2*sizeof(int));
   C =  malloc(f1*sizeof(int*)); 
      for(i=0;i<f1;i++)
        C[i]=malloc(c2*sizeof(int));
        
        
   // Generamos numeros aleatorios para la matriz A Y B
   for(i = 0; i < f1; i++) {
      for(j = 0; j < c1; j++) {
         A[i][j] = random()%100;      
      }
   }
   for(i = 0; i < f2; i++) {
      for(j = 0; j < c2; j++) {
         B[i][j] = random()%100;      
      }
   }      
   
   for(i = 0; i < f1; i++) {
      for(j = 0; j < c2; j++) {
         //asignar una fila y columna por cada hilo
         struct v *data = (struct v *) malloc(sizeof(struct v));
         data->i = i;
         data->j = j;
         /* creamos el hilo y le pasaamos data como parametro  */
         pthread_t tid;       
         pthread_attr_t attr; //Set de atributos del hilo 
         pthread_attr_init(&attr);
         pthread_create(&tid,&attr,multi,data);
         //Aeguramos que el main espera a que terminen todos lo hilos
         pthread_join(tid, NULL);
         count++;
      }
   }
   printf("Matriz A\n");
   for(i = 0; i < f1; i++) {
      for(j = 0; j < c1; j++) {
         printf("%d ", A[i][j]);
      }
      printf("\n");
   }
   printf("Matriz B\n");
   for(i = 0; i < f2; i++) {
      for(j = 0; j < c2; j++) {
         printf("%d ", B[i][j]);
      }
      printf("\n");
   }
   printf("Matriz C\n");
   for(i = 0; i < f1; i++) {
      for(j = 0; j < c2; j++) {
         printf("%d ", C[i][j]);
      }
      printf("\n");
   }
   free(A);
   free(B);
   free(C);
}

void *multi(void *param) {
   struct v *data = param; 
   int n, sum = 0; 

   for(n = 0; n< comun; n++){
      sum += A[data->i][n] * B[n][data->j];
   }
   
   C[data->i][data->j] = sum;
   //finalizamos el hilo
   pthread_exit(0);
}
# multi_mat_threads
