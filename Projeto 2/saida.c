#include "constantes.h" 
#include "saida.h"

int alunosFilaExterna[N_CAPACIDADE_FILA_EXTERNA];
int alunosFilaTradicional[N_CAPACIDADE_FILA_INTERNA];
int alunosFilaVegetariana[N_CAPACIDADE_FILA_INTERNA];
int alunosCatracas[N_CATRACAS];
int alunosAssentos[N_ASSENTOS];
int alunos[N_ALUNOS];

/* Funcao responsavel pela impressao do cineminha. */
void imprimeCineminha() {
  int i, qtdAlunosFE = 0, qtdAlunosFT = 0, qtdAlunosFV = 0, qtdAlunosCO = 0, qtdAlunosEX = 0, titulo = 0;
  int alunosFE[N_ALUNOS], alunosFT[N_ALUNOS], alunosFV[N_ALUNOS], alunosCO[N_ALUNOS], alunosEX[N_ALUNOS];

  /* Inicialzia parametros das filas. */
  for (i = 0; i < N_ALUNOS; i++){
    alunosFE[i] = INT_MAX;
    alunosFT[i] = INT_MAX;
    alunosFV[i] = INT_MAX;
    alunosCO[i] = INT_MAX;
    alunosEX[i] = INT_MAX;
  }

  /* Verifica quais alunos estao no estado "FE", "FT", "FV", "CO" e "EX". */
  for (i = 0; i < N_ALUNOS; i++){
    if (estadoAluno[i] == FE)
      alunosFE[qtdAlunosFE++] = i + 1;
    else if (estadoAluno[i] == FT)
      alunosFT[qtdAlunosFT++] = i + 1;
    else if (estadoAluno[i] == FV)
      alunosFV[qtdAlunosFV++] = i + 1;
    else if (estadoAluno[i] == CO)
      alunosCO[qtdAlunosCO++] = i + 1;
    else if (estadoAluno[i] == EX)
      alunosEX[qtdAlunosEX++] = i + 1;
  }

  /*****************************************************************************
   **************************** IMPRESSAO DO TITULO ****************************
   ****************************************************************************/
  
  titulo = (4 + 5 * N_CAPACIDADE_FILA_INTERNA + 5) / 2;
  
  titulo -= 7;
  
  for (i = 0; i < titulo; i++) {
    printf(" ");
  }
  
  printf("BANDECO\n");
  
  /*****************************************************************************
   ************************** FIM IMPRESSAO DO TITULO **************************
   ****************************************************************************/
  
  /*****************************************************************************
   ************************** IMPRESSAO PRIMEIRA LINHA *************************
   ****************************************************************************/
  
  printf ("/");
  
  for (i = 0; i < N_CAPACIDADE_FILA_INTERNA; i++)
    printf("─────");
  printf("\\");
  printf("\tEntrada\n");
  
  /*****************************************************************************
   ********************** FIM DA IMPRESSAO PRIMEIRA LINHA **********************
   ****************************************************************************/
  
  /*****************************************************************************
   ************************** IMPRESSAO SEGUNDA LINHA **************************
   ****************************************************************************/

  printf ("< ");
  
  for (i = 0; i < N_CAPACIDADE_FILA_INTERNA; i++) {
    if (alunosFT[i] != INT_MAX)
      printf(" %2d  ", alunosFT[i]);
    else
      printf(" ..  ");
  }

  if (estadoCatraca[0] == L)
    printf("L \n");
  else
    printf("O \n");

  /*****************************************************************************
   ********************** FIM DA IMPRESSAO SEGUNDA LINHA ***********************
   ****************************************************************************/

  /*****************************************************************************
   ************************** IMPRESSAO TERCEIRA LINHA *************************
   ****************************************************************************/
 
  printf("|");

  for (i = 0; i < (titulo / 2) - 7; i++)
    printf(" ");
  
  printf("^ Fila Tradicional ^ - v Fila Vegetariana v");

  for (i = 0; i < (titulo / 2) - 8; i++)
    printf(" ");

  printf(" |  ");

  for (i = 0; i < N_CAPACIDADE_FILA_EXTERNA; i++) {
    if (alunosFE[i] != INT_MAX)
      printf(" %2d  ", alunosFE[i]);
    else
      printf(" ..  ");
  }

  printf("\n");

  /*****************************************************************************
   ********************** FIM DA IMPRESSAO TERCEIRA LINHA **********************
   ****************************************************************************/

  /*****************************************************************************
   ************************** IMPRESSAO QUARTA LINHA ***************************
   ****************************************************************************/
  
  printf ("< ");
  
  for (i = 0; i < N_CAPACIDADE_FILA_INTERNA; i++) {
    if (alunosFV[i] != INT_MAX)
      printf(" %2d  ", alunosFV[i]);
    else
      printf(" ..  ");
  }

  if (estadoCatraca[1] == L)
    printf("L \n");
  else
    printf("O \n");

  
  /*****************************************************************************
   *********************** FIM DA IMPRESSAO QUARTA LINHA ***********************
   ****************************************************************************/
  

  /*****************************************************************************
   *************************** IMPRESSAO QUINTA LINHA **************************
   ****************************************************************************/
  
  printf ("|");
  
  for (i = 0; i < N_CAPACIDADE_FILA_INTERNA; i++)
    printf("─────");
  
  printf("|\n");
  /*****************************************************************************
   *********************** FIM DA IMPRESSAO QUINTA LINHA ***********************
   ****************************************************************************/

  /*****************************************************************************
   *********************** FIM DA IMPRESSAO SEXTA LINHA ************************
   ****************************************************************************/

  printf ("> ");
  
  for (i = 0; i < (titulo / 2) - 2; i++)
    printf("  ");
  
  printf("v Refeitório v");

  for (i = 0; i < (titulo / 2) - 2; i++)
    printf("  ");

  printf("> \n");

  /*****************************************************************************
   *********************** FIM DA IMPRESSAO SEXTA LINHA ************************
   ****************************************************************************/

  /*****************************************************************************
   *********************** FIM DA IMPRESSAO SÉTIMA LINHA ***********************
   ****************************************************************************/

  printf ("|");
  
  for (i = N_CAPACIDADE_FILA_INTERNA - 1; i >= 0; i--) {
    if (alunosCO[i] != INT_MAX)
      printf(" %2d  ", alunosCO[i]);
    else
      printf(" ..  ");
  }
  
  printf(" |  ");

  int j = 0;
  for (i = N_ALUNOS - 1; i >= 0; i--) {
    if (alunosEX[i] != INT_MAX){
      printf(" %2d  ", alunosEX[i]);
      j++;
    }
    
    if (j == N_CAPACIDADE_FILA_EXTERNA)
      break;
  
  }

  if (j < N_CAPACIDADE_FILA_EXTERNA){
    for (i = 0; i < N_CAPACIDADE_FILA_EXTERNA - j; i++){
      printf(" ..  ");
    }
  }

  printf("\n");

  /*****************************************************************************
   *********************** FIM DA IMPRESSAO SÉTIMA LINHA ***********************
   ****************************************************************************/

  printf ("> ");
  
  for (i = 0; i < N_CAPACIDADE_FILA_INTERNA; i++) {
      printf("==   ");
  }

  printf("> \n");

  /*****************************************************************************
   *********************** FIM DA IMPRESSAO OITAVA LINHA ***********************
   ****************************************************************************/

  printf ("\\");
  
  for (i = 0; i < N_CAPACIDADE_FILA_INTERNA; i++)
    printf("─────");
  
  printf("/");
  printf("\tSaída\n\n");
  
  /*****************************************************************************
   *********************** FIM DA IMPRESSAO OITAVA LINHA ***********************
   ****************************************************************************/
  return;
}
