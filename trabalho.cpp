#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <math.h>
#include "meuconio.h"

#define TF 100
#define TFE 25
#define TFC 20
#define TFN 30

struct typeConcurso
{
    
};

struct typeApostador
{
    
};

struct typeAposta
{
    
};

char menuInicial(void)
{
    system("cls");
    printf("\n-----MENU-----\n");
    printf("[A] Concursos\n");
    printf("[B] Apostadores\n");
    printf("[C] Apostas\n");
    printf("[Esc] Sair\n");
    printf("Opcao desejada: ");
    fflush(stdin);
    return toupper(getche());
}

char menuInicial(void)
{
    system("cls");
    printf("\n-----MENU-----\n");
    printf("[A] Cadastrar\n");
    printf("[B] Consultar\n");
    printf("[C] Alterar\n");
    printf("[D] Excluir\n");
    printf("[Esc] Sair\n");
    printf("Opcao desejada: ");
    fflush(stdin);
    return toupper(getche());
}

int main(void)
{

    char opcao;
    do
    {
        opcao = menuInicial();
        switch (opcao)
        {
        case 'A':

            break;

        case 'B':

            break;

        case 'C':

            break;

        default:
            break;
        }
    } while (opcao != 27);
    return 0;
}