# calcpi


As threads implementadas são preemptivas ou cooperativas? Explique sua resposta.

As threads implementadas no código são **PREEMPITIVAS**. Threads preemptivas são gerenciadas pelo sistema operacional, que pode interromper uma thread em execução para permitir que outra thread seja executada. Isso é diferente das threads cooperativas, onde as threads devem liberar o controle voluntariamente.

Motivo: O código utiliza a biblioteca pthread do POSIX, que geralmente é associada a threads preemptivas. As pthreads são gerenciadas pelo sistema operacional, que pode fazer o agendamento das threads de forma preemptiva, alternando entre elas automaticamente.

Que modelo de threads o sistema operacional que você usou implementa (N:1, 1:1 ou N:M) ? 

O modelo de threads que o sistema operacional utilizado implementa pode ser determinado como 1:1.

Explicação dos Modelos de Threads:

N:1: Várias threads de nível de usuário mapeadas para um único thread de nível de kernel. Esse modelo pode enfrentar problemas de desempenho porque todas as threads de nível de usuário competem por um único thread de nível de kernel.

1:1: Cada thread de nível de usuário corresponde a uma thread de nível de kernel. Esse modelo permite que o sistema operacional gerencie as threads de forma eficiente, com agendamento e preempção de threads.

N
: Combina N:1 e 1:1, permitindo que múltiplas threads de nível de usuário sejam mapeadas para múltiplas threads de nível de kernel.

Como isso pode ser deduzido a partir dos experimentos?

através do comando 

`ps -eLf | grep main` ele mostra as threads que rolam no processo e são várias, mostrando assim que é um processo multithread