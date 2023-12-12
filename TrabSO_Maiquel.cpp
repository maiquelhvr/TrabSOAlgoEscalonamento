#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
Trabalho de algoritmos de escalonamento.
Disciplina de Sistemas Operacionais, professor Jean.
Aluno: Maiquel Rheinheimer (2022012656)
Entrega: 12 de Dezembro de 2023
IFRS Campus Restinga - Analise e Desenvolvimento de Sistemas
*/


// CRIANDO O STRUCT COM OS DADOS DE CADA PROCESSO
struct Processo {
  int idProcesso;
  int chegada;
  int prioridade;
  int tempoTotal;
  int tempoAtual;
  int tempoEsperando;
};

// CHAMAREMOS ESSA FUNCAO PARA NUMEROS ALEATORIOS
int geraNumAleatorio(int menorValorIntervalo, int maiorValorIntervalo) {
  int numAleatorioGerado = 0;
  numAleatorioGerado = (rand() % (maiorValorIntervalo - menorValorIntervalo + 1)) + menorValorIntervalo;
  return numAleatorioGerado;
}


// OK VAMOS COMECAR PRA VALER O PROGRAMA
main() {
// linhas para definir que o usuario podera reiniciar ao final
int usarMesmosProcessos = 0;
int rodarTudoDenovo = 1;
while ( rodarTudoDenovo == 1 ) {

printf("\n**********************************************");
printf("\n**                                          **");
printf("\n** Trabalho dos Algoritmos de Escalonamento **");
printf("\n**                                          **");
printf("\n**   por Maiquel Rheinheimer (2022012656)   **");
printf("\n**                                          **");
printf("\n**********************************************\n\n");

// inicializacao da aleatoriedade
srand(time(0));
// professor define aqui os intervalos que tu quer pra numeros aleatorios
// vou usar como regra pra todos inputs do usuario tambem alem do random.
// favor nao usar menos do que "1" como menor parte do intervalo, senao
// vai quebrar um monte de coisa, principalmente controles de execucao
int menorValorIntervalo = 1;
int maiorValorIntervalo = 10;

// caso alguem pegue esse codigo e fique de palhacada, vou arrumar
if ( menorValorIntervalo < 1 ) {
  printf("Eu disse pra nao setar variavel menor do intervalo abaixo de 1...\n");
  printf("Estou definindo ela eu mesmo para 1 agora.\n");
  menorValorIntervalo = 1;
}


// ----- * -----


// PARTE 1: DEFININDO NUMERO DE PROCESSOS
printf("\nDEFININDO NUMERO DE PROCESSOS");
printf("\n=============================\n");
printf("Precisamos saber o numero de processos, entre %d e %d.\n", menorValorIntervalo, maiorValorIntervalo);
printf("Voce pode definir esses valores nas variaveis especificas.\n");
printf("Digite zero (0) se quiser gerar aleatoriamente.\n");
// vamos comecar a variavel com um valor que ative o while da validacao
int numDeProcessos = 0;
// validaremos se o usuario esta digitando certo
while ( (numDeProcessos < menorValorIntervalo) || (numDeProcessos > maiorValorIntervalo) ) {
  printf("\nPor favor, digite o numero de processos agora: ");
  scanf("%d", &numDeProcessos);
  // se digitou zero, vai ser definido aleatoriamente
  if ( numDeProcessos == 0 ) {
    numDeProcessos = geraNumAleatorio(menorValorIntervalo,maiorValorIntervalo);
  }
}
printf("Valor definido: %d", numDeProcessos);


// ----- * -----
printf("\n\n");
// ----- * -----


// PARTE 2 DEFINIR AS CARACERISTICAS DE CADA PROCESSO
printf("\nDEFININDO DADOS DOS PROCESSOS");
printf("\n=============================\n");
printf("Cada processo precisa ter alguns valores inerentes a ele. A saber:\n");
printf("1) Chegada = momento em o processo chegou para execucao.\n");
printf("2) Prioridade* = qual processo seria mais importante;\n");
printf("3) Tempo de execucao = quanto tempo leva para executar.\n");
printf("* OBS: numero mais baixo significa maior prioridade...\n");
printf("Nem todos os algoritmos usarao todos os dados sobre o processo, alem\n");
printf("do que estes nem sao todos os dados a respeito de cada processo.\n");
printf("Mas estes tres devem ser definidos aleatoriamente ou manualmente.\n");
printf("Digite zero (0) se quiser definir aleatoriamente ou 1 manualmente.\n");
// iniciando a variavel com um valor que ativa o while para validacao
int respostaDadosDosProcessos = 2;
// valideremos aqui se o usuario esta respondendo certo
while ( (respostaDadosDosProcessos != 0) && (respostaDadosDosProcessos != 1) ) {
  printf("\nSua resposta: ");
  scanf("%d", &respostaDadosDosProcessos);
}

// ok hora de declarar a criacao da struct
struct Processo processo[numDeProcessos];

// caso tenha sido escolhido gerar os valores aleatoriamente
if ( respostaDadosDosProcessos == 0 ) {
  printf("Vamos gerar aleatoriamente entao...\n\n");
  for ( int c = 0; c < numDeProcessos; c++ ) {
    // comecamos salvando a ID do processo
    processo[c].idProcesso = c;
    processo[c].chegada = geraNumAleatorio(menorValorIntervalo,maiorValorIntervalo);
    processo[c].prioridade = geraNumAleatorio(menorValorIntervalo,maiorValorIntervalo);
    processo[c].tempoTotal = geraNumAleatorio(menorValorIntervalo,maiorValorIntervalo);
  }
}
// eita chatice, nao sei pq alguem iria querer digitar manualmente, mas ok...
else if ( respostaDadosDosProcessos == 1 ) {
  printf("Parece que escolhemos o caminho demorado...\n\n");
  printf("Sao um total de %d processos, vamos definir cada valor deles.", numDeProcessos);
  for (int c = 0; c < numDeProcessos; c++ ) {
    // comecamos salvando a ID do processo
    processo[c].idProcesso = c;
    printf("\nValores para processo %d (de %d a %d):\n", c, menorValorIntervalo, maiorValorIntervalo);
    // vamos forcar mais uma vez valores definidos no comeco
    processo[c].chegada = 0;
    while ( (processo[c].chegada < menorValorIntervalo) || (processo[c].chegada > maiorValorIntervalo) ) {
      printf("Digite o tempo de chegada do processo: ");
      scanf("%d", &processo[c].chegada); }
    // mesma validacao e pergunta para a prioridade
    processo[c].prioridade = 0;
    while ( (processo[c].prioridade < menorValorIntervalo) || (processo[c].prioridade > maiorValorIntervalo) ) {
      printf("Digite a prioridade do processo: ");
      scanf("%d", &processo[c].prioridade); }
    // agora mesma coisa pro tempo
    processo[c].tempoTotal = 0;
    while ( (processo[c].tempoTotal < menorValorIntervalo) || (processo[c].tempoTotal > maiorValorIntervalo) ) {
      printf("Digite o tempo total de execucao do processo: ");
      scanf("%d", &processo[c].tempoTotal); }
  }
}
// nao deveria cair aqui nunca
else { printf("Usuario conseguiu furar minha validacao..."); }
// e essa aspa vem la de quando decidimos usar os mesmos processos


// ====================================
// ====================================
// ====================================


// PARTE 3 ESCOLHENDO O ALGORITMO DE ESCALONAMENTO
// aqui recomeca outra execucao com os mesmos processos
do {
// printando aquele relatorio basico
printf("\nInformacoes preliminares definidas, esses sao os processos:");
for ( int c = 0; c < numDeProcessos; c++ ) {
  printf("\nProcesso %d com chegada %d, prioridade %d e tempo total %d", c, processo[c].chegada, processo[c].prioridade, processo[c].tempoTotal);
}

printf("\n\n\nDEFININDO ALGORITMO DE ESCALONAMENTO");
printf("\n====================================\n");
printf("Podemos agora escolher o algoritmo de escalonamento:\n\n");
printf("1 - First Come First Served (FCFS)\n");
printf("2 - Shortest Job First (SJF) Simples\n");
printf("3 - Shortest Job First (SJF) Preemptivo\n");
printf("4 - Prioridade Simples\n");
printf("5 - Prioridade Preemptivo\n");
printf("6 - Round-Robin\n");
// validando o input do usuario dentro do escopo do menu
int opcaoDeAlgoritmo = 0;
while ( (opcaoDeAlgoritmo != 1) && (opcaoDeAlgoritmo != 2) && (opcaoDeAlgoritmo != 3) && (opcaoDeAlgoritmo != 4) && (opcaoDeAlgoritmo != 5) && (opcaoDeAlgoritmo != 6)  ) {
  printf("\nDigite o numero desejado: ");
  scanf("%d", &opcaoDeAlgoritmo);
}


// ----- * -----
printf("\n");
// ----- * -----


// PARTE 4 VARIAVEIS COMUNS AOS ALGORITMOS
// vamos precisar alguns controles para os algoritmos, nao usaremos todos
// necessariamente sempre, mas vamos declarar todo aqui logo num lugar comum
// comecando por uma struct para copiar os processos prontos
struct Processo escalonados[numDeProcessos];
// ja vamos correr ela e zerando os valores necessarios
for ( int c = 0; c < numDeProcessos; c++ ) {
  escalonados[c].idProcesso = 0;
  escalonados[c].tempoAtual = 0;
  escalonados[c].prioridade = 0;
  escalonados[c].tempoEsperando = 0;
}
// tempo de execucao
int tempo = 1;
// media do tempo de espera
float tempoMedioEspera = 0;
// controle de quantos processos foram pra lista de execucao
int contEscalonados = 0;
// variaveis auxiliares para usar no ordenamento
int dir;
int aux;
// flag pra saber se alguem executou nessa rodada
int executouAlguem = 0;
// flag pra saber se alguem travou cpu pra finalizar execucao
int cpuLock = 0;
// posicao que vai executar nesse tempo do round robin
int executaRR = 0;
// flag pra sair quando terminar tudo
int sair = 0;


// ====================================
// ====================================
// ====================================


// OPCAO 1 FIRST COME FIRST SERVED
if ( opcaoDeAlgoritmo == 1 ) {
printf("\n1 - FIRST COME FIRST SERVED (FCFS)");
printf("\n==================================\n");
while ( sair == 0 ) {

  // comecamos zerando a flag de controle de execucao
  executouAlguem = 0;

  // antes de mais nada, vamos verificar se existem processos chegando
  // vamos encontrar os processos com o tempo de chegada atual
  for ( int c = 0; c < numDeProcessos; c++ ) {
    // se o o processo tem a chegada pra esse momento, vamos escalonar
    if ( processo[c].chegada == tempo ) {
      escalonados[contEscalonados].idProcesso = processo[c].idProcesso;
      escalonados[contEscalonados].tempoAtual = processo[c].tempoTotal;
      contEscalonados++;
    }
  }

  // agora sim, vamos ver quem precisa ser executado nesse tempo
  for ( int c = 0; c < numDeProcessos; c++ ) {
    if  ( (escalonados[c].tempoAtual > 0) && (executouAlguem == 0) ) {
      // aqui consideremos que encontramos o processo e vamos retirar seu tempo
      escalonados[c].tempoAtual = escalonados[c].tempoAtual - 1;
      printf("Finalizamos tempo %d, executado processo %d restando %d.\n", tempo, escalonados[c].idProcesso, escalonados[c].tempoAtual);
      // ok ja tivemos uma execucao nesse tempo, marcaremos pra nao fazer mais
      executouAlguem = 1;
    }
    // essa avaliacao tem o objetivo de contabilizar tempo de espera dos processos
    // caiu aqui se o processo ja foi escalonado mas outro ja executou antes
    else if ( escalonados[c].tempoAtual > 0 ) {
      escalonados[c].tempoEsperando = escalonados[c].tempoEsperando + 1;
    }
  }

  // regra de fim de execucao, ja escalonamos todos processos e foram executados
  if ( (contEscalonados == numDeProcessos) && (executouAlguem == 0) ) {
    printf("Finalizamos a execucao de todos os processos.\n");
    sair = 1;
  }
  else if ( executouAlguem == 0 ) {
    // ninguem executou nesse tempo, mas ainda tem processos pra chegar
    printf("Finalizamos tempo %d com processador ocioso.\n", tempo);;
  }

tempo++; }

// contabilizacao e relatorio do tempo de espera dessa execucao
for ( int c = 0; c < numDeProcessos; c++ ) {
  tempoMedioEspera = tempoMedioEspera + escalonados[c].tempoEsperando;
  printf("Processo %d teve tempo de espera %d\n", escalonados[c].idProcesso, escalonados[c].tempoEsperando);
}
// calculo e retorno do tempo medio de espera
tempoMedioEspera = tempoMedioEspera/numDeProcessos;
printf("Tempo medio de espera foi %.2f", tempoMedioEspera);

// FIM DO FCFS
}


// ====================================
// ====================================
// ====================================


// OPCAO 2 SJF SIMPLES
else if ( opcaoDeAlgoritmo == 2 ) {
printf("\n2 - SHORTEST JOB FIRST (SJF) SIMPLES");
printf("\n====================================\n");
while ( sair == 0 ) {

  // comecamos zerando a flag de controle de execucao
  executouAlguem = 0;

  // antes de mais nada, vamos verificar se existem processos chegando
  // vamos encontrar os processos com o tempo de chegada atual
  for ( int c = 0; c < numDeProcessos; c++ ) {
    // se o o processo tem a chegada pra esse momento, vamos escalonar
    if ( processo[c].chegada == tempo ) {
      escalonados[contEscalonados].idProcesso = processo[c].idProcesso;
      escalonados[contEscalonados].tempoAtual = processo[c].tempoTotal;
      contEscalonados++;
    }
  }

  // grande novidade aqui vai ser aplicar o ordenamento pelo menor tempo atual
  // porem, como esse algoritmo nao eh preemptivo, vamos analisar a CPU
  // se a cpu esta livre, fazemos o ordenamento, senao deixamos processar
  if ( cpuLock == 0 ) {
  // vamos comecar verificando se ja temos alguem na fila pra ordenar
  if ( contEscalonados > 1 ) {
    // laco externo do ordenamento, que vai pegar cada elemento
    for ( int c = 0; c < contEscalonados; c++ ) {
    // laco interno do ordenamento, que compara cada elemento
    for ( int esq = 0; esq < contEscalonados; esq++ ){
      // se for a ultima posicao do array, nao faz nada
      if ( esq != contEscalonados-1 ) {
        // ja que nao estamos na ultima posicao, tem alguem pra direita
        dir = esq + 1;
        // se o cara do lado direito for menor, trocamos as posicoes
        if ( escalonados[dir].tempoAtual < escalonados[esq].tempoAtual ) {
          // vamos trocar a posicao do ID
          aux = escalonados[esq].idProcesso;
          escalonados[esq].idProcesso = escalonados[dir].idProcesso;
          escalonados[dir].idProcesso = aux;
          // e tambem trocamos o valor do tempo atual
          aux = escalonados[esq].tempoAtual;
          escalonados[esq].tempoAtual = escalonados[dir].tempoAtual;
          escalonados[dir].tempoAtual = aux;
          // por fim trocamos tambem o tempo esperando          
          aux = escalonados[esq].tempoEsperando;
          escalonados[esq].tempoEsperando = escalonados[dir].tempoEsperando;
          escalonados[dir].tempoEsperando = aux;
        }
      }
    }
    }
  }
  }

  // agora sim, vamos ver quem precisa ser executado nesse tempo
  for ( int c = 0; c < numDeProcessos; c++ ) {
    if  ( (escalonados[c].tempoAtual > 0) && (executouAlguem == 0) ) {
      // aqui consideremos que encontramos o processo e vamos retirar seu tempo
      escalonados[c].tempoAtual = escalonados[c].tempoAtual - 1;
      printf("Finalizamos tempo %d, executado processo %d restando %d.\n", tempo, escalonados[c].idProcesso, escalonados[c].tempoAtual);
      // ok ja tivemos uma execucao nesse tempo, marcaremos pra nao fazer mais
      executouAlguem = 1;
      // agora vamos ver se travamos ou liberamos a cpu
      if ( escalonados[c].tempoAtual > 0 ) {
        // processo no comeco da fila ainda esta executando
        cpuLock = 1;
      }
      else if ( escalonados[c].tempoAtual == 0 ) {
        // processo no comeco da fila ja finalizou
        cpuLock = 0;
      }
    }
    // essa avaliacao tem o objetivo de contabilizar tempo de espera dos processos
    // caiu aqui se o processo ja foi escalonado mas outro ja executou antes
    else if ( escalonados[c].tempoAtual > 0 ) {
      escalonados[c].tempoEsperando = escalonados[c].tempoEsperando + 1;
    }
  }

  // regra de fim de execucao, ja escalonamos todos processos e foram executados
  if ( (contEscalonados == numDeProcessos) && (executouAlguem == 0) ) {
    printf("Finalizamos a execucao de todos os processos.\n");
    sair = 1;
  }
  else if ( executouAlguem == 0 ) {
    // ninguem executou nesse tempo, mas ainda tem processos pra chegar
    printf("Finalizamos tempo %d com processador ocioso.\n", tempo);;
  }

tempo++; }

// contabilizacao e relatorio do tempo de espera dessa execucao
for ( int c = 0; c < numDeProcessos; c++ ) {
  tempoMedioEspera = tempoMedioEspera + escalonados[c].tempoEsperando;
  printf("Processo %d teve tempo de espera %d\n", escalonados[c].idProcesso, escalonados[c].tempoEsperando);
}
// calculo e retorno do tempo medio de espera
tempoMedioEspera = tempoMedioEspera/numDeProcessos;
printf("Tempo medio de espera foi %.2f", tempoMedioEspera);

// FIM DO SJF SIMPLES
}


// ====================================
// ====================================
// ====================================


// OPCAO 3 SJF PREEMPTIVO
else if ( opcaoDeAlgoritmo == 3 ) {
printf("\n3 - SHORTEST JOB FIRST (SJF) PREEMPTIVO");
printf("\n=======================================\n");
while ( sair == 0 ) {

  // comecamos zerando a flag de controle de execucao
  executouAlguem = 0;

  // antes de mais nada, vamos verificar se existem processos chegando
  // vamos encontrar os processos com o tempo de chegada atual
  for ( int c = 0; c < numDeProcessos; c++ ) {
    // se o o processo tem a chegada pra esse momento, vamos escalonar
    if ( processo[c].chegada == tempo ) {
      escalonados[contEscalonados].idProcesso = processo[c].idProcesso;
      escalonados[contEscalonados].tempoAtual = processo[c].tempoTotal;
      contEscalonados++;
    }
  }

  // grande novidade aqui vai ser aplicar o ordenamento pelo menor tempo atual
  // vamos comecar verificando se ja temos alguem na fila pra ordenar
  if ( contEscalonados > 1 ) {
    // laco externo do ordenamento, que vai pegar cada elemento
    for ( int c = 0; c < contEscalonados; c++ ) {
    // laco interno do ordenamento, que compara cada elemento
    for ( int esq = 0; esq < contEscalonados; esq++ ){
      // se for a ultima posicao do array, nao faz nada
      if ( esq != contEscalonados-1 ) {
        // ja que nao estamos na ultima posicao, tem alguem pra direita
        dir = esq + 1;
        // se o cara do lado direito for menor, trocamos as posicoes
        if ( escalonados[dir].tempoAtual < escalonados[esq].tempoAtual ) {
          // vamos trocar a posicao do ID
          aux = escalonados[esq].idProcesso;
          escalonados[esq].idProcesso = escalonados[dir].idProcesso;
          escalonados[dir].idProcesso = aux;
          // e tambem trocamos o valor do tempo atual
          aux = escalonados[esq].tempoAtual;
          escalonados[esq].tempoAtual = escalonados[dir].tempoAtual;
          escalonados[dir].tempoAtual = aux;
          // por fim trocamos tambem o tempo esperando          
          aux = escalonados[esq].tempoEsperando;
          escalonados[esq].tempoEsperando = escalonados[dir].tempoEsperando;
          escalonados[dir].tempoEsperando = aux;
        }
      }
    }
    }
  }

  // agora sim, vamos ver quem precisa ser executado nesse tempo
  for ( int c = 0; c < numDeProcessos; c++ ) {
    if  ( (escalonados[c].tempoAtual > 0) && (executouAlguem == 0) ) {
      // aqui consideremos que encontramos o processo e vamos retirar seu tempo
      escalonados[c].tempoAtual = escalonados[c].tempoAtual - 1;
      printf("Finalizamos tempo %d, executado processo %d restando %d.\n", tempo, escalonados[c].idProcesso, escalonados[c].tempoAtual);
      // ok ja tivemos uma execucao nesse tempo, marcaremos pra nao fazer mais
      executouAlguem = 1;
    }
    // essa avaliacao tem o objetivo de contabilizar tempo de espera dos processos
    // caiu aqui se o processo ja foi escalonado mas outro ja executou antes
    else if ( escalonados[c].tempoAtual > 0 ) {
      escalonados[c].tempoEsperando = escalonados[c].tempoEsperando + 1;
    }
  }

  // regra de fim de execucao, ja escalonamos todos processos e foram executados
  if ( (contEscalonados == numDeProcessos) && (executouAlguem == 0) ) {
    printf("Finalizamos a execucao de todos os processos.\n");
    sair = 1;
  }
  else if ( executouAlguem == 0 ) {
    // ninguem executou nesse tempo, mas ainda tem processos pra chegar
    printf("Finalizamos tempo %d com processador ocioso.\n", tempo);;
  }

tempo++; }

// contabilizacao e relatorio do tempo de espera dessa execucao
for ( int c = 0; c < numDeProcessos; c++ ) {
  tempoMedioEspera = tempoMedioEspera + escalonados[c].tempoEsperando;
  printf("Processo %d teve tempo de espera %d\n", escalonados[c].idProcesso, escalonados[c].tempoEsperando);
}
// calculo e retorno do tempo medio de espera
tempoMedioEspera = tempoMedioEspera/numDeProcessos;
printf("Tempo medio de espera foi %.2f", tempoMedioEspera);

// FIM DO SJF PREEMPTIVO
}


// ====================================
// ====================================
// ====================================


// OPCAO 4 PRIORIDADE SIMPLES
else if ( opcaoDeAlgoritmo == 4 ) {
printf("\n4 - PRIORIDADE SIMPLES");
printf("\n======================\n");
while ( sair == 0 ) {

  // comecamos zerando a flag de controle de execucao
  executouAlguem = 0;

  // antes de mais nada, vamos verificar se existem processos chegando
  // vamos encontrar os processos com o tempo de chegada atual
  for ( int c = 0; c < numDeProcessos; c++ ) {
    // se o o processo tem a chegada pra esse momento, vamos escalonar
    if ( processo[c].chegada == tempo ) {
      escalonados[contEscalonados].idProcesso = processo[c].idProcesso;
      escalonados[contEscalonados].tempoAtual = processo[c].tempoTotal;
      // vamos usar a prioridade nesse algoritmo
      escalonados[contEscalonados].prioridade = processo[c].prioridade;
      contEscalonados++;
    }
  }

  // grande novidade aqui vai ser aplicar o ordenamento pela prioridade
  // porem, como esse algoritmo nao eh preemptivo, vamos analisar a CPU
  // se a cpu esta livre, fazemos o ordenamento, senao deixamos processar
  if ( cpuLock == 0 ) {
  // vamos comecar verificando se ja temos alguem na fila pra ordenar
  if ( contEscalonados > 1 ) {
    // laco externo do ordenamento, que vai pegar cada elemento
    for ( int c = 0; c < contEscalonados; c++ ) {
    // laco interno do ordenamento, que compara cada elemento
    for ( int esq = 0; esq < contEscalonados; esq++ ){
      // se for a ultima posicao do array, nao faz nada
      if ( esq != contEscalonados-1 ) {
        // ja que nao estamos na ultima posicao, tem alguem pra direita
        dir = esq + 1;
        // se o cara do lado direito for menor, trocamos as posicoes
        // lembrando que consideramos numero mais baixo uma prioridade maior
        if ( escalonados[dir].prioridade < escalonados[esq].prioridade ) {
          // de cara ja vamos reposicionar a prioridade
          aux = escalonados[esq].prioridade;
          escalonados[esq].prioridade = escalonados[dir].prioridade;
          escalonados[dir].prioridade = aux;
          // vamos trocar a posicao do ID
          aux = escalonados[esq].idProcesso;
          escalonados[esq].idProcesso = escalonados[dir].idProcesso;
          escalonados[dir].idProcesso = aux;
          // e tambem trocamos o valor do tempo atual
          aux = escalonados[esq].tempoAtual;
          escalonados[esq].tempoAtual = escalonados[dir].tempoAtual;
          escalonados[dir].tempoAtual = aux;
          // por fim trocamos tambem o tempo esperando          
          aux = escalonados[esq].tempoEsperando;
          escalonados[esq].tempoEsperando = escalonados[dir].tempoEsperando;
          escalonados[dir].tempoEsperando = aux;
        }
      }
    }
    }
  }
  }

  // agora sim, vamos ver quem precisa ser executado nesse tempo
  for ( int c = 0; c < numDeProcessos; c++ ) {
    if  ( (escalonados[c].tempoAtual > 0) && (executouAlguem == 0) ) {
      // aqui consideremos que encontramos o processo e vamos retirar seu tempo
      escalonados[c].tempoAtual = escalonados[c].tempoAtual - 1;
      printf("Finalizamos tempo %d, executado processo %d, prioridade %d, restando %d.\n", tempo, escalonados[c].idProcesso, escalonados[c].prioridade, escalonados[c].tempoAtual);
      // ok ja tivemos uma execucao nesse tempo, marcaremos pra nao fazer mais
      executouAlguem = 1;
      // agora vamos ver se travamos ou liberamos a cpu
      if ( escalonados[c].tempoAtual > 0 ) {
        // processo no comeco da fila ainda esta executando
        cpuLock = 1;
      }
      else if ( escalonados[c].tempoAtual == 0 ) {
        // processo no comeco da fila ja finalizou
        cpuLock = 0;
      }
    }
    // essa avaliacao tem o objetivo de contabilizar tempo de espera dos processos
    // caiu aqui se o processo ja foi escalonado mas outro ja executou antes
    else if ( escalonados[c].tempoAtual > 0 ) {
      escalonados[c].tempoEsperando = escalonados[c].tempoEsperando + 1;
    }
  }

  // regra de fim de execucao, ja escalonamos todos processos e foram executados
  if ( (contEscalonados == numDeProcessos) && (executouAlguem == 0) ) {
    printf("Finalizamos a execucao de todos os processos.\n");
    sair = 1;
  }
  else if ( executouAlguem == 0 ) {
    // ninguem executou nesse tempo, mas ainda tem processos pra chegar
    printf("Finalizamos tempo %d com processador ocioso.\n", tempo);;
  }

tempo++; }

// contabilizacao e relatorio do tempo de espera dessa execucao
for ( int c = 0; c < numDeProcessos; c++ ) {
  tempoMedioEspera = tempoMedioEspera + escalonados[c].tempoEsperando;
  printf("Processo %d teve tempo de espera %d\n", escalonados[c].idProcesso, escalonados[c].tempoEsperando);
}
// calculo e retorno do tempo medio de espera
tempoMedioEspera = tempoMedioEspera/numDeProcessos;
printf("Tempo medio de espera foi %.2f", tempoMedioEspera);

// FIM DO PRIORIDADE SIMPLES
}


// ====================================
// ====================================
// ====================================


// OPCAO 5 PRIORIDADE PREEMPTIVO
else if ( opcaoDeAlgoritmo == 5 ) {
printf("\n5 - PRIORIDADE PREEMPTIVO");
printf("\n=========================\n");
while ( sair == 0 ) {

  // comecamos zerando a flag de controle de execucao
  executouAlguem = 0;

  // antes de mais nada, vamos verificar se existem processos chegando
  // vamos encontrar os processos com o tempo de chegada atual
  for ( int c = 0; c < numDeProcessos; c++ ) {
    // se o o processo tem a chegada pra esse momento, vamos escalonar
    if ( processo[c].chegada == tempo ) {
      escalonados[contEscalonados].idProcesso = processo[c].idProcesso;
      escalonados[contEscalonados].tempoAtual = processo[c].tempoTotal;
      // vamos usar a prioridade nesse algoritmo
      escalonados[contEscalonados].prioridade = processo[c].prioridade;
      contEscalonados++;
    }
  }

  // grande novidade aqui vai ser aplicar o ordenamento pela prioridade
  // vamos comecar verificando se ja temos alguem na fila pra ordenar
  if ( contEscalonados > 1 ) {
    // laco externo do ordenamento, que vai pegar cada elemento
    for ( int c = 0; c < contEscalonados; c++ ) {
    // laco interno do ordenamento, que compara cada elemento
    for ( int esq = 0; esq < contEscalonados; esq++ ){
      // se for a ultima posicao do array, nao faz nada
      if ( esq != contEscalonados-1 ) {
        // ja que nao estamos na ultima posicao, tem alguem pra direita
        dir = esq + 1;
        // se o cara do lado direito for menor, trocamos as posicoes
        // lembrando que consideramos numero mais baixo uma prioridade maior
        if ( escalonados[dir].prioridade < escalonados[esq].prioridade ) {
          // de cara ja vamos reposicionar a prioridade
          aux = escalonados[esq].prioridade;
          escalonados[esq].prioridade = escalonados[dir].prioridade;
          escalonados[dir].prioridade = aux;
          // vamos trocar a posicao do ID
          aux = escalonados[esq].idProcesso;
          escalonados[esq].idProcesso = escalonados[dir].idProcesso;
          escalonados[dir].idProcesso = aux;
          // e tambem trocamos o valor do tempo atual
          aux = escalonados[esq].tempoAtual;
          escalonados[esq].tempoAtual = escalonados[dir].tempoAtual;
          escalonados[dir].tempoAtual = aux;
          // por fim trocamos tambem o tempo esperando          
          aux = escalonados[esq].tempoEsperando;
          escalonados[esq].tempoEsperando = escalonados[dir].tempoEsperando;
          escalonados[dir].tempoEsperando = aux;
        }
      }
    }
    }
  }

  // agora sim, vamos ver quem precisa ser executado nesse tempo
  for ( int c = 0; c < numDeProcessos; c++ ) {
    if  ( (escalonados[c].tempoAtual > 0) && (executouAlguem == 0) ) {
      // aqui consideremos que encontramos o processo e vamos retirar seu tempo
      escalonados[c].tempoAtual = escalonados[c].tempoAtual - 1;
      printf("Finalizamos tempo %d, executado processo %d, prioridade %d, restando %d.\n", tempo, escalonados[c].idProcesso, escalonados[c].prioridade, escalonados[c].tempoAtual);
      // ok ja tivemos uma execucao nesse tempo, marcaremos pra nao fazer mais
      executouAlguem = 1;
    }
    // essa avaliacao tem o objetivo de contabilizar tempo de espera dos processos
    // caiu aqui se o processo ja foi escalonado mas outro ja executou antes
    else if ( escalonados[c].tempoAtual > 0 ) {
      escalonados[c].tempoEsperando = escalonados[c].tempoEsperando + 1;
    }
  }

  // regra de fim de execucao, ja escalonamos todos processos e foram executados
  if ( (contEscalonados == numDeProcessos) && (executouAlguem == 0) ) {
    printf("Finalizamos a execucao de todos os processos.\n");
    sair = 1;
  }
  else if ( executouAlguem == 0 ) {
    // ninguem executou nesse tempo, mas ainda tem processos pra chegar
    printf("Finalizamos tempo %d com processador ocioso.\n", tempo);;
  }

tempo++; }

// contabilizacao e relatorio do tempo de espera dessa execucao
for ( int c = 0; c < numDeProcessos; c++ ) {
  tempoMedioEspera = tempoMedioEspera + escalonados[c].tempoEsperando;
  printf("Processo %d teve tempo de espera %d\n", escalonados[c].idProcesso, escalonados[c].tempoEsperando);
}
// calculo e retorno do tempo medio de espera
tempoMedioEspera = tempoMedioEspera/numDeProcessos;
printf("Tempo medio de espera foi %.2f", tempoMedioEspera);

// FIM DO PRIORIDADE PREEMTIVO
}


// ====================================
// ====================================
// ====================================


// OPCAO 6 ROUND-ROBIN
else if ( opcaoDeAlgoritmo == 6 ) {
printf("\n6 - ROUND-ROBIN");
printf("\n===============\n");
while ( sair == 0 ) {

  // comecamos zerando a flag de controle de execucao
  executouAlguem = 0;

  // antes de mais nada, vamos verificar se existem processos chegando
  // vamos encontrar os processos com o tempo de chegada atual
  for ( int c = 0; c < numDeProcessos; c++ ) {
    // se o o processo tem a chegada pra esse momento, vamos escalonar
    if ( processo[c].chegada == tempo ) {
      escalonados[contEscalonados].idProcesso = processo[c].idProcesso;
      escalonados[contEscalonados].tempoAtual = processo[c].tempoTotal;
      contEscalonados++;
    }
  }

  // agora sim, vamos ver quem precisa ser executado nesse tempo
  for ( int c = 0; c < numDeProcessos; c++ ) {
    // vamos adicionar uma verificacao para pular processos finalizados
    if ( (contEscalonados > 0) && (escalonados[executaRR].tempoAtual == 0) ) { executaRR++; } 
    // a novidade no round robin seria verificar se o processo esta na sua vez
    if  ( (escalonados[c].tempoAtual > 0) && (executouAlguem == 0) && (c == executaRR) ) {
      // aqui consideremos que encontramos o processo e vamos retirar seu tempo
      escalonados[c].tempoAtual = escalonados[c].tempoAtual - 1;
      printf("Finalizamos tempo %d, executado processo %d restando %d.\n", tempo, escalonados[c].idProcesso, escalonados[c].tempoAtual);
      // ok ja tivemos uma execucao nesse tempo, marcaremos pra nao fazer mais
      executouAlguem = 1;
      // vamos passar a vez pro proximo da fila
      executaRR++;
    }
    // essa avaliacao tem o objetivo de contabilizar tempo de espera dos processos
    // caiu aqui se o processo ja foi escalonado mas outro ja executou antes
    else if ( escalonados[c].tempoAtual > 0 ) {
      escalonados[c].tempoEsperando = escalonados[c].tempoEsperando + 1;
    }

    // porem se eu cheguei no final da fila, volta pro comeco
    // isso significa que na primeira rodada, se um processo estiver sozinho
    // ele vai acabar se marcando para rodar de novo na proxima (afinal ele
    // nao sabia se outro seria escalonado na proxima ou nao)
    if ( executaRR == contEscalonados ) {
      executaRR = 0;
    }
  }

  // regra de fim de execucao, ja escalonamos todos processos e foram executados
  if ( (contEscalonados == numDeProcessos) && (executouAlguem == 0) ) {
    printf("Finalizamos a execucao de todos os processos.\n");
    sair = 1;
  }
  else if ( executouAlguem == 0 ) {
    // ninguem executou nesse tempo, mas ainda tem processos pra chegar
    printf("Finalizamos tempo %d com processador ocioso.\n", tempo);;
  }

tempo++; }

// contabilizacao e relatorio do tempo de espera dessa execucao
for ( int c = 0; c < numDeProcessos; c++ ) {
  tempoMedioEspera = tempoMedioEspera + escalonados[c].tempoEsperando;
  printf("Processo %d teve tempo de espera %d\n", escalonados[c].idProcesso, escalonados[c].tempoEsperando);
}
// calculo e retorno do tempo medio de espera
tempoMedioEspera = tempoMedioEspera/numDeProcessos;
printf("Tempo medio de espera foi %.2f", tempoMedioEspera);

// FIM DO ROUND-ROBIN
}


// ====================================
// ====================================
// ====================================


// NAO DEVERIA CAIR AQUI NUNCA
else { printf("Usuario furou minha validacao..."); }
// ----- * -----
printf("\n\n");
// ----- * -----


// FIM DO PROGRAMA
printf("\n======================================\n");
printf("Fim da execucao, voce pode sair ou reiniciar.\n");
printf("Digite um (1) para testar outro algorimo com os mesmos processos: ");
scanf("%d", &usarMesmosProcessos);
} while ( usarMesmosProcessos == 1 );
printf("Digite um (1) para reiniciar ou qualquer outro numero para sair: ");
scanf("%d", &rodarTudoDenovo);
printf("\n\n");
} }
