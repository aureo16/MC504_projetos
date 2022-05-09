#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <semaphore.h>


#define N_CAPACIDADE_FILA_INTERNA 10
#define N_CAPACIDADE_FILA_EXTERNA 5
#define N_ALUNOS 45
#define N_CATRACAS 2
#define N_FILA_INTERNA 2
#define N_ASSENTOS 10

/*
 * Variaveis para guardar estado dos aluno.
 * FE - Fila externa
 * NC - Na catraca
 * FT - Fila tradicional (interna)
 * FV - Fila vegetariana (interna)
 * CO - Comendo
 * EX - Saindo
 */
typedef enum {FE, NC, FT, FV, CO, EX} estado_aluno;

/*
 * Variaveis para guardar estado das catracas.
 * L - Liberada
 * O - Ocupada
 */
typedef enum {L, O} estado_catraca;

/*
 * Variaveis para guardar estado dos assento.
 * AO - Ocupado
 * AL - Livre
 */
typedef enum {AO, AL} estado_assento;

estado_aluno estadoAluno[N_ALUNOS];
estado_catraca estadoCatraca[N_CATRACAS];
estado_assento alunosAssento[N_ASSENTOS];

int alunosFilaExterna[N_CAPACIDADE_FILA_EXTERNA];
int alunosFilaTradicional[N_CAPACIDADE_FILA_INTERNA];
int alunosFilaVegetariana[N_CAPACIDADE_FILA_INTERNA];
int alunosCatracas[N_CATRACAS];
int alunosAssentos[N_ASSENTOS];
int alunos[N_ALUNOS];

sem_t sem_catraca;
sem_t sem_filaInterna[N_FILA_INTERNA];
sem_t sem_assento;
sem_t sem_estados;
sem_t sem_verifFilaExterna;
sem_t sem_verifFilaInterna[N_FILA_INTERNA];
sem_t sem_estado_catracas;

#endif
