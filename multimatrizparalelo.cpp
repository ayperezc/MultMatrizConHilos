#include <iostream>
#include <pthread.h>
#include <iomanip>
#include <ctime>

using namespace std;

// maximum size of matrix 
#define MAX 1024 
  
// maximum number of threads 
#define NUM_THREADS 2 
  
long matA[MAX][MAX]; 
long matB[MAX][MAX]; 
long matC[MAX][MAX]; 
int paso = 0;

struct entradas {
    double acum;
    long inicio;
    long fin;
};

void* multi(void* args) 
{ 
    struct entradas *misEntradas;
    misEntradas = (struct entradas *) args;
    long inicio = misEntradas->inicio;
    long fin = misEntradas->fin;
    // Each thread computes 1/4th of matrix multiplication 
    for(long i = inicio; i < fin; i++){
        for (int j = 0; j < MAX; j++){
            for (int k = 0; k < MAX; k++){
                matC[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
    pthread_exit(NULL);
} 

int main(void){

    pthread_t threads[NUM_THREADS];
    struct entradas td[NUM_THREADS];
    long paso = MAX/NUM_THREADS;
    long imas1 = 1;

    int k;
    for(int i = 0; i < MAX; i++)
    {
        k=1;
        for(int j = 0; j < MAX; j++)
        {
            matA[i][j] = k;
            k++;
        }
        
    }

    for(int i = 0; i < MAX; i++)
    {
        k=1;
        for(int j = 0; j < MAX; j++)
        {
            matB[i][j] = k;
            k++;
        }
        
    }
    

    /*
    matA[0][0] = 1;
    matA[0][1] = 2;
    matA[0][2] = 3;
    matA[0][3] = 4;
    matA[1][0] = 5;
    matA[1][1] = 6;
    matA[1][2] = 7;
    matA[1][3] = 8;
    matA[2][0] = 9;
    matA[2][1] = 10;
    matA[2][2] = 11;
    matA[2][3] = 12;
    matA[3][0] = 13;
    matA[3][1] = 14;
    matA[3][2] = 15;
    matA[3][3] = 16;

    matB[0][0] = 1;
    matB[0][1] = 2;
    matB[0][2] = 3;
    matB[0][3] = 4;
    matB[1][0] = 5;
    matB[1][1] = 6;
    matB[1][2] = 7;
    matB[1][3] = 8;
    matB[2][0] = 9;
    matB[2][1] = 10;
    matB[2][2] = 11;
    matB[2][3] = 12;
    matB[3][0] = 13;
    matB[3][1] = 14;
    matB[3][2] = 15;
    matB[3][3] = 16;
    */

    // Displaying matA 
    // cout << endl 
    //     << "Matrix A" << endl; 
    // for (int i = 0; i < MAX; i++) { 
    //     for (int j = 0; j < MAX; j++)  
    //         cout << matA[i][j] << " "; 
    //     cout << endl; 
    // } 
  
    // Displaying matB 
    // cout << endl 
    //     << "Matrix B" << endl; 
    // for (int i = 0; i < MAX; i++) { 
    //     for (int j = 0; j < MAX; j++)  
    //         cout << matB[i][j] << " ";         
    //     cout << endl; 
    // }

    //multi((void *)&td);
    
    clock_t t;
    t = clock();
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        long imas1 = i+1;
        td[i].inicio = i*paso;
        td[i].fin = imas1*paso;
        int t = pthread_create(&threads[i], NULL, multi, (void *)&td[i]);
        if (t != 0)
        {
            cout << "Error in thread creation: " << t << endl;
        }
    }
    for (int i = 0; i < NUM_THREADS; ++i){
        int rc = pthread_join(threads[i], NULL);
        if (rc) {
            cout << "Error:unable to join," << rc << endl;
            exit(-1);
        }
    }
    t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",(int)t,((float)t)/CLOCKS_PER_SEC);

    // Displaying the result matrix 
    // cout << endl 
    //      << "Multiplication of A and B" << endl; 
    // for (int i = 0; i < MAX; i++) { 
    //     for (int j = 0; j < MAX; j++)  
    //         cout << matC[i][j] << " ";         
    //     cout << endl; 
    // } 
}