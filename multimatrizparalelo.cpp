#include <iostream>
#include <pthread.h>
#include <iomanip>
#include <ctime>

using namespace std;

#define NUM_THREADS 16 // 2,4,8,16

struct entradas {
    double acum;
    long inicio;
    long fin;
};

void* gregLeibParalelo(void* args){  //OJO!!!!!, esto da pi/4
    struct entradas *misEntradas;
    misEntradas = (struct entradas *) args;
    long inicio = misEntradas->inicio;
    long fin = misEntradas->fin;
    double numerador,denominador,fraccion;
    int alternante = -1;
    
    for(long i = inicio; i < fin; i++)
    {
        alternante = -alternante;
        numerador = alternante;
        denominador = 2*i + 1;
        fraccion = numerador/denominador;
        misEntradas->acum = misEntradas->acum + fraccion;
    }

    pthread_exit(NULL);
}

int main (void) {
    pthread_t threads[NUM_THREADS];
    struct entradas td[NUM_THREADS];
    void *status;
    long paso = 1000000000/NUM_THREADS;
    double acumTotal = 0;

    clock_t t;
    t = clock();

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        long imas1 = i+1;
        td[i].inicio = i*paso;
        td[i].fin = imas1*paso;
        int t = pthread_create(&threads[i], NULL, gregLeibParalelo, (void *)&td[i]);
        if (t != 0)
        {
            cout << "Error in thread creation: " << t << endl;
        }
    }
    for(int i = 0; i < NUM_THREADS; ++i)
    {
        int rc = pthread_join(threads[i], &status);
        if (rc) {
            cout << "Error:unable to join," << rc << endl;
            exit(-1);
        }
        acumTotal = acumTotal + td[i].acum;
    }
    
    cout << std::setprecision(15) << 4*acumTotal << endl;
    t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",(int)t,((float)t)/CLOCKS_PER_SEC);
}
