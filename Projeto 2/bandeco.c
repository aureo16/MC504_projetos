#include "constantes.h"
#include "saida.h"
#include "linkedList.h"

int verifFilaExterna = 0;

plist fVeg;
plist fTrad;

/* Thread dos estudantes. */
void* f_estudante(void* v) {
  int id = *(int*)v;
  int i, minha_catraca, minha_fila, meu_assento = 0;

  /* Esperando na fila externa */
  sem_wait(&sem_estados);
  estadoAluno[id] = FE;
  imprimeCineminha();
  sem_post(&sem_estados);

  while (1) {
    sem_wait(&sem_verifFilaExterna);    
    if (verifFilaExterna < id) {
      sem_post(&sem_verifFilaExterna);
      sleep(2);
    } else {
      verifFilaExterna++;
      break;
    }
  }

  /* Chega na catraca */
  sem_wait(&sem_catraca);
  sem_post(&sem_verifFilaExterna);

  sem_wait(&sem_estados);
  estadoAluno[id] = NC;

  for (i = 0; i < N_CATRACAS; i++) {
    if (estadoCatraca[i] == L) {
      estadoCatraca[i] = O;
      alunosCatracas[i] = id;
      minha_catraca = i;
      break;
    }
  }
  imprimeCineminha();
  sem_post(&sem_estados);

  /* Se necessário, espera liberar*/
  /* Passa pela catraca */
  /* Seleciona fila */
  /* Entra na fila interna */
  plist fila;
  while (1) {
    srand(time(0));
    minha_fila = (rand()%10 < 5) ? 1 : 0;
    if (sem_trywait(&sem_filaInterna[minha_fila]) == 0) {
      sem_wait(&sem_estados);
      
      estadoAluno[id] = minha_fila ? FT : FV;
      estadoCatraca[minha_catraca] = L;
      sem_post(&sem_catraca);

      fila = (minha_fila? fTrad : fVeg);
      fila = adicionar_elemento(fila, id);
      imprimeCineminha();
      sem_post(&sem_estados);
      break; 
    }
  }
  
  /* Esperando na fila interna */
  while (1) { 
    sem_wait(&sem_verifFilaInterna[minha_fila]);
    if (fila->head->data < id){
      sem_post(&sem_verifFilaInterna[minha_fila]);
      sleep(2);
    } else {
      fila = remover_elemento(fila);
      break;
    }
  }

  /* Chega na refeição */
  /* Espera assento */
  sem_wait(&sem_assento);
  sem_wait(&sem_estados);

  sem_post(&sem_verifFilaInterna[minha_fila]);
  sem_post(&sem_filaInterna[minha_fila]);

  /* Senta para comer */
  estadoAluno[id] = CO;
  for (i = 0; i < N_ASSENTOS; i++) {
    if (alunosAssento[i] == AL) {
      alunosAssento[i] = AO;
      alunosAssento[i] = id;
      meu_assento = i;
      break;
    }
  }
  imprimeCineminha();
  sem_post(&sem_estados);
  
  sleep(20); //Tempinho para comer
  
  /* Vai embora */
  sem_wait(&sem_estados);
  sem_post(&sem_assento);
  estadoAluno[id] = EX;
  alunosAssento[meu_assento] = AL;
  imprimeCineminha();
  sem_post(&sem_estados);
}

int main() {
  fVeg = criar_lista();
  fTrad = criar_lista();

  pthread_t thr_alunos[N_ALUNOS];
  int id_alunos[N_ALUNOS];

  sem_init(&sem_catraca, 0, N_CATRACAS);
  sem_init(&sem_assento, 0, N_ASSENTOS);
  sem_init(&sem_estados, 0, 1);
  sem_init(&sem_verifFilaExterna, 0, N_CAPACIDADE_FILA_EXTERNA);
  sem_init(&sem_estado_catracas, 0, 1);

  for (int i = 0; i < N_ASSENTOS; i++ )
    alunosAssento[i] = AL;

  for (int i = 0; i < N_CATRACAS; i++ )
    alunosCatracas[i] = L;

  for (int i = 0; i < N_FILA_INTERNA; i++){
    sem_init(&sem_filaInterna[i], 0, N_CAPACIDADE_FILA_INTERNA);
    sem_init(&sem_verifFilaInterna[i], 0, 1);
  }

  for (int i = 0; i < N_ALUNOS; i++) {
    id_alunos[i] = i;
    pthread_create(&thr_alunos[i], NULL, f_estudante, (void*) &id_alunos[i]);
  }

  for (int i = 0; i < N_ALUNOS; i++)
    pthread_join(thr_alunos[i], NULL);

  destruir_lista(fVeg);
  destruir_lista(fTrad);
  return 0;
}