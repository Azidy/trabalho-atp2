#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <math.h>
#include "meuconio.h"

#define TF 100

struct typeData
{
    int dia, mes, ano;
};

struct typeConcurso
{
    int idConc, numeroSorteado;
    typeData data;
};

struct typeApostador
{
    char CPF[12], nome[30], telefone[11];
};

struct typeAposta
{
    int idAposta, idConc, qtdeNumApostado, numApostado;
    char CPF[12];
};

void cadastroApostadores(typeApostador apostadores[TF], int &tl)
{
    char auxCPF[12];
    system("cls");
    printf("--- Cadastro de apostadores ---\n");
    printf("CPF: ");
    fflush(stdin);
    gets(auxCPF);
    while (tl < TF && strcmp(auxCPF, "\0") != 0)
    {
        strcpy(apostadores[tl].CPF, auxCPF);

        printf("Nome: ");
        fflush(stdin);
        gets(apostadores[tl].nome);

        printf("Telefone: ");
        fflush(stdin);
        gets(apostadores[tl].telefone);

        tl++;

        printf("------------------------------------------------\n");

        printf("CPF: ");
        fflush(stdin);
        gets(auxCPF);
    }
}

void exibirApostadores(typeApostador apostadores[TF], int tl)
{
    system("cls");
    printf("--- Exibir Apostadores ---\n");
    if (tl == 0)
    {
        printf("Nao ha nenhum apostador cadastrado");
    }
    else
    {
        for (int i = 0; i < tl; i++)
        {
            printf("\n-----------------------------------------------\n");
            printf("CPF: %s\n", apostadores[i].CPF);
            printf("Nome: %s\n", apostadores[i].nome);
            printf("Fone: %s\n", apostadores[i].telefone);
        }
    }
    getch();
}

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

char menuSubInicial(void)
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
    typeApostador apostadores[TF];
    int tlp = 0;
    char opcao, subOpcao;
    do
    {
        opcao = menuInicial();
        switch (opcao)
        {
        case 'A':
            do
            {
                subOpcao = menuSubInicial();
                switch (subOpcao)
                {
                case 'A':

                    break;

                case 'B':

                    break;

                case 'C':

                    break;

                case 'D':

                    break;
                }
            } while (subOpcao != 27);
            break;

        case 'B':
            do
            {
                subOpcao = menuSubInicial();
                switch (subOpcao)
                {
                case 'A':
                    cadastroApostadores(apostadores, tlp);
                    break;

                case 'B':
                    exibirApostadores(apostadores, tlp);
                    break;

                case 'C':

                    break;

                case 'D':

                    break;
                }
            } while (subOpcao != 27);
            break;

        case 'C':
            do
            {
                subOpcao = menuSubInicial();
                switch (subOpcao)
                {
                case 'A':

                    break;

                case 'B':

                    break;

                case 'C':

                    break;

                case 'D':

                    break;
                }
            } while (subOpcao != 27);
            break;
        }
    } while (opcao != 27);
    return 0;
}