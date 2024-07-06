#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>   // para usar gettimeofday e structs relacionadas

#define TERMS_PER_THREAD 2500000 // Número de termos da série por thread para uma boa aproximação
#define NUM_THREADS 12             // Número de threads a serem utilizadas

// Estrutura para armazenar os dados de cada thread
typedef struct
{
    double start; // Índice de início da série para esta thread
    double end;   // Índice de fim da série para esta thread
    double sum;    // Soma dos termos da série para esta thread
} ThreadData;

// Função para calcular os termos da série de Leibniz-Gregory em uma thread
void *calculate_pi(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    data->sum = 0.0;

    // Calcular a série de Leibniz-Gregory para os termos atribuídos a esta thread
    for (double i = data->start; i < data->end; ++i)
    {
        double term = pow(-1, i) / (2.0 * i + 1);
        data->sum += term;
    }

    pthread_exit(NULL);
}

// Função para obter o tempo atual em segundos
double get_current_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + (double)tv.tv_usec / 1e6;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    double total_sum = 0.0;
    double pi_estimate = 0.0;
    double start_time, end_time; // variáveis para armazenar o tempo inicial e final

    // Calcular o número total de termos
    double total_terms = TERMS_PER_THREAD * NUM_THREADS;

    // Iniciar cronômetro
    start_time = get_current_time();

    // Iniciar threads
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        thread_data[i].start = i * TERMS_PER_THREAD;
        thread_data[i].end = (i + 1) * TERMS_PER_THREAD;
        pthread_create(&threads[i], NULL, calculate_pi, (void *)&thread_data[i]);
    }

    // Aguardar término das threads e acumular a soma total
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
        total_sum += thread_data[i].sum;
    }

    // Parar cronômetro
    end_time = get_current_time();

    // Calcular π estimado
    pi_estimate = 4.0 * total_sum;

    // Imprimir o valor estimado de π com 10 casas decimais e o tempo de execução
    printf("Estimated value of PI: %.10f\n", pi_estimate);
    printf("Elapsed time: %.6f seconds\n", end_time - start_time);

    return 0;
}
