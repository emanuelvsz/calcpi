#  🧮 Cálculo de π com threads em C
_Esse repositorio contém o código feito em C utilizado para avaliação de Sistemas Operacionais. <br/> A proposta da atividade completa pode ser encontrada [aqui](https://wiki.inf.ufpr.br/maziero/doku.php?id=so:calculo_de_pi_com_threads)._

_Alunos que contribuiram para essa atividade:_ 
- [Alice Julia](https://github.com/Alljuly)
- [Divaldo Verçosa](https://github.com/Divaldoh)
- [Emanuel Vilela](https://github.com/emanuelvsz)
- [Levid Lima](https://github.com/DEVLevid)


## Processo do código
### Escolha das bibliotecas 
```C
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>
```
- `<stdio.h>`: Biblioteca para chamadas de função padrão como `print()`;
- `<pthread.h>`: Utilizamos para criação e manipulação das threads;
  - `pthread_create()` criação e  `pthread_join()` junção das threads.
- `<math.h>`: Para função `pow()`, utilizando na potenciação na fórmula de Leibniz;
- `<sys/time.h>`: Para calcular o tempo levado pelas threads para calcular o valor de PI com a função `gettimeofday()`, usada em `void get_current_time()`.

### Macros
- `#define TERMS_PER_THREAD`: Número de termos calculado por cada thread;
- `#define NUM_THREADS`: Número de threads utilizadas.

### Struct da thread 
  ```C
typedef struct {
    double start;
    double end;
    double sum;
} ThreadData;
```
- Essa estrutura armazena o `start` e `end` do intervalo da quantidade de termos que a thread irá calcular;
- Em `sum` guardamos o resultado parcial por cada thread.

### Uso da função `void *calculate_pi(void *arg)`
- Recebe um ponteiro genérico `*arg` que é convertido para o tipo da struct `ThreadData`.
- O Atributo `sum` da struct é inicializado em 0.
- No loop em seguida, a variavel `term` recebe o resultado da série de Leibniz `(pow(-1, i) / (2.0 * i + 1))`.

### Função `main()`
- Declaração das variáveis:
``` C
pthread_t threads[NUM_THREADS]; // numero de threads utilizadas
ThreadData thread_data[NUM_THREADS]; // 
double total_sum = 0.0; // inicializando a variavel para soma
double pi_estimate = 0.0; // inicializando variavel que recebera p resultado
double start_time, end_time; // declaracao as variavaveis que contaram a hora que o calculo começou e terminou

double total_terms = TERMS_PER_THREAD * NUM_THREADS; // numero total de termos que serao calculados por todas as threads.

```
- Chamada das funções:
```C
for (int i = 0; i < NUM_THREADS; ++i) {
        thread_data[i].start = i * TERMS_PER_THREAD;
        thread_data[i].end = (i + 1) * TERMS_PER_THREAD;
        pthread_create(&threads[i], NULL, calculate_pi, (void *)&thread_data[i]);
}


for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
        total_sum += thread_data[i].sum;
}
```

### Resultados obtidos
<table>
  <tr>
  <td>Nº threads</td>
  <td>Valor estimado</td>
  <td>Tempo decorrido (s)</td>
</tr>
<tr>
  <td>12</td>
  <td>3.141592620256410</td>
  <td>0.192246</td>
</tr>
  <tr>
  <td>4</td>
  <td>3.141592553589743</td>
  <td>0.117020</td>
</tr>
  <tr>
  <td>1</td>
  <td>3.141592253589742</td>
  <td>0.035409</td>
</tr>
</table>

## Questionário.
### 1. As threads implementadas são preemptivas ou cooperativas? Explique sua resposta.
  - As threads implementadas no código são **PREEMPITIVAS**. Threads preemptivas são gerenciadas pelo sistema operacional, que pode interromper uma thread em execução para permitir que outra thread seja executada. Isso é diferente das threads cooperativas, onde as threads devem liberar o controle voluntariamente.

Motivo: O código utiliza a biblioteca pthread do POSIX, que geralmente é associada a threads preemptivas. As pthreads são gerenciadas pelo sistema operacional, que pode fazer o agendamento das threads de forma preemptiva, alternando entre elas automaticamente.

### 2. Que modelo de threads o sistema operacional que você usou implementa (N:1, 1:1 ou N:M) ? 
  - O modelo de threads que o sistema operacional utilizado implementa pode ser determinado como 1:1.
#### - 2.1 Explicação dos Modelos de Threads:

- N:1: Várias threads de nível de usuário mapeadas para um único thread de nível de kernel. Esse modelo pode enfrentar problemas de desempenho porque todas as threads de nível de usuário competem por um único thread de nível de kernel.

- 1:1: Cada thread de nível de usuário corresponde a uma thread de nível de kernel. Esse modelo permite que o sistema operacional gerencie as threads de forma eficiente, com agendamento e preempção de threads.

- N:M Combina N:1 e 1:1, permitindo que múltiplas threads de nível de usuário sejam mapeadas para múltiplas threads de nível de kernel.

### 3. Como isso pode ser deduzido a partir dos experimentos?
  - através do comando  `ps -eLf | grep main` ele mostra as threads que rolam no processo e são várias, mostrando assim que é um processo multithread
