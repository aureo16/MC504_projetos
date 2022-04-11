#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *L;
char **matriz;

void imprimir() 
{
    for (int i = 0; i < L[0]; i++)
    {    
        for (int j = 0; j < L[1]; j++) 
        {
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }
}

int validar(int i, int j)
{
    return (i >= 0 && i < L[0]) && (j >= 0 && j < L[1]) ? 1 : 0;
}

void dicas()
{
    for (int i = 0; i < L[0]; i++)
    {
        for (int j = 0; j < L[1]; j++)
        {
            if(matriz[i][j] == 'x')
                continue;

            int tmp = 0;

            for (int a = -1; a < 2; a++)
            {
                for (int b = -1; b < 2; b++)
                {
                    if((a == 0) && (b ==0))
                        continue;
                    else if (validar(a + i,b + j) && matriz[a + i][b + j] == 'x')
                        tmp++;
                }
            }
            matriz[i][j] = tmp + '0';
        }
    }
}

void preencher() 
{
    for (int i = 0; i < L[0]; i++)
    {
        for (int j = 0; j < L[1]; j++) 
        {
            scanf("%c ", &matriz[i][j]);
        }
    }
}

int main() 
{
    clock_t inicio, fim;
    double tempo_cpu;
    inicio = clock();

    L = malloc (2 * sizeof (int));
    scanf("%d %d ", &L[0], &L[1]);

    matriz = malloc (L[0] * sizeof (char*));
    for (int i = 0; i < L[0]; i++)
        matriz[i] = malloc (L[1] * sizeof (char));

    preencher();

    /// criação matriz de dicas
    dicas();

    imprimir();

    for (int i = 0; i < L[0]; i++)
        free(matriz[i]);
    free(matriz);
    free(L);

    fim  = clock();
    tempo_cpu = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de CPU: %.5f s\n", tempo_cpu);
    return 0;
}

/* 
8 8
o o o o o o o o
o o x o o o o o
o o o o o o x o
o o o o x o o o
o o x o o x o o
o o o o o o o o
o o x o o x o o
o o o o o o o o */