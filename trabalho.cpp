<<<<<<< HEAD
// Codigo feito por Diego Felippe da Fonseca Calesco e Heitor Franzo Justo

/* --- Comentarios: ---
-Fazer um SubMenu para Concurso, pois o concurso requer cadastro somente de ID e data, o sorteio sera feito depois
=======
// Codigo feitor por Diego Felipe Calesco e Heitor Franzo Justo

/* --- Comentarios: ---
-Fazer um SubMenu para Concurso, pois o concurso requer cadastro somente de ID e data, o sorteio é feito depois
>>>>>>> b1f798a581e6b0cac6786d12f0f86668d6e69e96
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <math.h>
// #include "meuconio.h"

#define TF 100

struct typeData
{
    int dia, mes, ano;
};

struct typeConcurso
{
    int idConc, numeroSorteado[5];
    typeData data;
};

struct typeApostador
{
    char CPF[12], nome[30], telefone[11];
};

struct typeAposta
{
    int idAposta, idConc, qtdeNumApostado, numApostado[10];
    char CPF[12];
};

int achouCPF(typeApostador apostadores[TF], int tl, char CPF[12])
{
    int i = 0;
    while (i < tl && strcmp(apostadores[i].CPF, CPF) != 0)
        i++;

    if (i < tl)
        return i;
    else
        return -1;
}

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
        if (achouCPF(apostadores, tl, auxCPF) == -1)
        {
            strcpy(apostadores[tl].CPF, auxCPF);

            printf("Nome: ");
            fflush(stdin);
            gets(apostadores[tl].nome);

            printf("Telefone: ");
            fflush(stdin);
            gets(apostadores[tl].telefone);

            tl++;
        }

        else
            printf("\n[ERRO] O CPF [%s] ja existe e nao pode ser duplicado!\n\n", auxCPF);

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
        printf("\n[ERRO] Nao ha nenhum apostador cadastrado");
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

char menuAlterarApostadores()
{
    printf("\n[A] Alterar CPF\n");
    printf("[B] Alterar Nome\n");
    printf("[C] Alterar Telefone\n");
    printf("[Esc] Sair\n");
    printf("Opcao desejada: ");
    fflush(stdin);
    return toupper(getche());
}

void excluirApostadores(typeApostador apostadores[TF], int &tl)
{
    char auxCPF[12], opcao;
    int pos;
    system("cls");
    printf("--- Exclusao de apostadores ---\n");
<<<<<<< HEAD
    if(tl==0)
    {
    	printf("\n[ERRO] Nao ha nenhum apostador cadastrado");
    	getch();
	}
	
	else
		{
			printf("\nDigite o CPF do apostador a ser excluido: ");
		    fflush(stdin);
		    gets(auxCPF);
		
		    if (strcmp(auxCPF, "\0") != 0)
		    {
		        pos = achouCPF(apostadores, tl, auxCPF);
		        if (pos == -1)
		        {
		            printf("\n[ERRO] O CPF nao foi encontrado!\n");
		            getch();
		        }
		
		        else
		        {
		            system("cls");
		            printf("--- Exclusao de apostadores ---\n");
		            printf("\nApostador sendo excluido:\n");
		            printf("\n------------------------\n");
		            printf("CPF: %s\n", apostadores[pos].CPF);
		            printf("Nome: %s\n", apostadores[pos].nome);
		            printf("Fone: %s\n", apostadores[pos].telefone);
		            printf("------------------------\n");
		            printf("\nDeseja mesmo excluir este apostador?\n");
		            printf("\n[S] Sim \t [N] Nao\n");
		
		            while (opcao != 'S' && opcao != 'N')
		            {
		                opcao = toupper(getch());
		            }
		
		            switch (opcao)
		            {
			            case 'S':
			                for (; pos < tl - 1; pos++)
			                    apostadores[pos] = apostadores[pos + 1];
			                tl--;
			                printf("\n[INFO] Exclusao concluida!");
			                getch();
			                break;
			            case 'N':
			                printf("\n[INFO] Exclusao cancalada!");
			                getch();
			                return;
			                break;
		            }
		        }
		    }
		}
   
=======
    printf("\nDigite o CPF do apostador a ser excluido: ");
    fflush(stdin);
    gets(auxCPF);

    if (strcmp(auxCPF, "\0") != 0)
    {
        pos = achouCPF(apostadores, tl, auxCPF);
        if (pos == -1)
        {
            printf("\n[ERRO] O CPF nao foi encontrado!\n");
            getch();
        }

        else
        {
            system("cls");
            printf("--- Exclusao de apostadores ---\n");
            printf("\nApostador sendo excluido:\n");
            printf("\n------------------------\n");
            printf("CPF: %s\n", apostadores[pos].CPF);
            printf("Nome: %s\n", apostadores[pos].nome);
            printf("Fone: %s\n", apostadores[pos].telefone);
            printf("------------------------\n");
            printf("\nDeseja mesmo excluir este apostador?\n");
            printf("\n[S] Sim \t [N] Nao\n");

            while (opcao != 'S' && opcao != 'N')
            {
                opcao = toupper(getch());
            }

            switch (opcao)
            {
            case 'S':
                for (; pos < tl - 1; pos++)
                    apostadores[pos] = apostadores[pos + 1];
                tl--;
                printf("\n[INFO] Exclusao concluida!");
                getch();
                break;
            case 'N':
                printf("\n[INFO] Exclusao cancalada!");
                getch();
                return;
                break;
            }
        }
    }
>>>>>>> b1f798a581e6b0cac6786d12f0f86668d6e69e96
}

void alterarDadoApostadores(typeApostador apostadores[TF], int pos, int opr, int tl)
{
    char aux[30];
    system("cls");
    printf("--- Alteracao de apostadores ---\n");
    printf("\n------------------------\n");
    printf("CPF: %s\n", apostadores[pos].CPF);
    printf("Nome: %s\n", apostadores[pos].nome);
    printf("Fone: %s\n", apostadores[pos].telefone);
    printf("------------------------\n");

    switch (opr)
    {
    case 1:
        printf("\nCPF atualizado: ");
        fflush(stdin);
        gets(aux);
        if (achouCPF(apostadores, tl, aux) == -1)
            strcpy(apostadores[pos].CPF, aux);
        else
        {
            printf("\n[ERRO] O CPF [%s] ja existe e nao pode ser duplicado!", aux);
            getch();
        }
        break;
    case 2:
        printf("\nNome atualizado: ");
        fflush(stdin);
        gets(aux);
        if (strcmp(aux, "\0") != 0)
            strcpy(apostadores[pos].nome, aux);
        break;

    case 3:
        printf("\nTelefone atualizado: ");
        fflush(stdin);
        gets(aux);
        if (strcmp(aux, "\0") != 0)
            strcpy(apostadores[pos].telefone, aux);
        break;
    }
}

void alterarApostadores(typeApostador apostadores[TF], int tl)
{
    char auxCPF[12], opcao;
    int pos;
    system("cls");
    printf("--- Alteracao de apostadores ---\n");
<<<<<<< HEAD
    if(tl==0)
    {
    	printf("\n[ERRO] Nao ha nenhum apostador cadastrado");
    	getch();
	}
    	
    else
    	{
    		printf("\nDigite o CPF do apostador a ser alterado: ");
		    fflush(stdin);
		    gets(auxCPF);
		
		    if (strcmp(auxCPF, "\0") != 0)
		    {
		        pos = achouCPF(apostadores, tl, auxCPF);
		        if (pos == -1)
		        {
		            printf("\n[ERRO] O CPF [%s] nao foi encontrado!\n", auxCPF);
		            getch();
		        }
		
		        else
		        {
		            do
		            {
		                system("cls");
		                printf("--- Alteracao de apostadores ---\n");
		                printf("\nApostador sendo alterado:\n");
		                printf("\n------------------------\n");
		                printf("CPF: %s\n", apostadores[pos].CPF);
		                printf("Nome: %s\n", apostadores[pos].nome);
		                printf("Fone: %s\n", apostadores[pos].telefone);
		                printf("------------------------\n");
		                opcao = menuAlterarApostadores();
		                switch (opcao)
		                {
		                case 'A':
		                    alterarDadoApostadores(apostadores, pos, 1, tl);
		                    break;
		                case 'B':
		                    alterarDadoApostadores(apostadores, pos, 2, tl);
		                    break;
		                case 'C':
		                    alterarDadoApostadores(apostadores, pos, 3, tl);
		                    break;
		                }
		            } while (opcao != 27);
		        }
		    }
		}
    
}

=======
    printf("\nDigite o CPF do apostador a ser alterado: ");
    fflush(stdin);
    gets(auxCPF);

    if (strcmp(auxCPF, "\0") != 0)
    {
        pos = achouCPF(apostadores, tl, auxCPF);
        if (pos == -1)
        {
            printf("\n[ERRO] O CPF [%s] nao foi encontrado!\n", auxCPF);
            getch();
        }

        else
        {
            do
            {
                system("cls");
                printf("--- Alteracao de apostadores ---\n");
                printf("\nApostador sendo alterado:\n");
                printf("\n------------------------\n");
                printf("CPF: %s\n", apostadores[pos].CPF);
                printf("Nome: %s\n", apostadores[pos].nome);
                printf("Fone: %s\n", apostadores[pos].telefone);
                printf("------------------------\n");
                opcao = menuAlterarApostadores();
                switch (opcao)
                {
                case 'A':
                    alterarDadoApostadores(apostadores, pos, 1, tl);
                    break;
                case 'B':
                    alterarDadoApostadores(apostadores, pos, 2, tl);
                    break;
                case 'C':
                    alterarDadoApostadores(apostadores, pos, 3, tl);
                    break;
                }
            } while (opcao != 27);
        }
    }
}

>>>>>>> b1f798a581e6b0cac6786d12f0f86668d6e69e96
char menuInicial(void)
{
    system("cls");
    printf("\n-----MENU PRINCIPAL-----\n");
    printf("[A] Concursos\n");
    printf("[B] Apostadores\n");
    printf("[C] Apostas\n");
    printf("[Esc] Sair\n");
    printf("Opcao desejada: ");
    fflush(stdin);
    return toupper(getche());
}

char menuSubInicial(char msg[15])
{
    system("cls");
    printf("\n-----MENU %s-----\n", msg);
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
                subOpcao = menuSubInicial("CONCURSOS");
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
                subOpcao = menuSubInicial("APOSTADORES");
                switch (subOpcao)
                {
                case 'A':
                    cadastroApostadores(apostadores, tlp);
                    break;

                case 'B':
                    exibirApostadores(apostadores, tlp);
                    break;

                case 'C':
                    alterarApostadores(apostadores, tlp);
                    break;

                case 'D':
                    excluirApostadores(apostadores, tlp);
                    break;
                }
            } while (subOpcao != 27);
            break;

        case 'C':
            do
            {
                subOpcao = menuSubInicial("APOSTAS");
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
