#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>

#define TERMS_PER_THREAD 2500000
#define NUM_THREADS 12

typedef struct {
    double start;
    double end;
    double sum;
} ThreadData;

void *calculate_pi(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    data->sum = 0.0;

    for (double i = data->start; i < data->end; ++i) {
        double term = pow(-1, i) / (2.0 * i + 1);
        data->sum += term;
    }

    pthread_exit(NULL);
}

double get_current_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + (double)tv.tv_usec / 1e6;
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    double total_sum = 0.0;
    double pi_estimate = 0.0;
    double start_time, end_time;

    double total_terms = TERMS_PER_THREAD * NUM_THREADS;

    start_time = get_current_time();

    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_data[i].start = i * TERMS_PER_THREAD;
        thread_data[i].end = (i + 1) * TERMS_PER_THREAD;
        pthread_create(&threads[i], NULL, calculate_pi, (void *)&thread_data[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
        total_sum += thread_data[i].sum;
    }

    end_time = get_current_time();

    pi_estimate = 4.0 * total_sum;

    printf("Valor estimado de π: %.10f\n", pi_estimate);
    printf("Tempo decorrido: %.6f segundos \n", end_time - start_time);
    return 0;
}
