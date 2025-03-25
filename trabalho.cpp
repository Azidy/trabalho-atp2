// Codigo feito por Diego Felippe da Fonseca Calesco e Heitor Franzo Justo

/* --- Comentarios: ---
-ULTIMA ATUALIZACAO: 24/03/2025 03:03 AM
-Resultado: Informar num do concurso, verificar concurso e status, pegar infos de apostas com o mesmo numero de concurso, comparar numeros apostados com os sorteados, informar vencedor
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include "conio2.h"

#define TF 100

struct typeData
{
    int dia, mes, ano;
};

struct typeConcurso
{
    int idConc, numeroSorteado[5], status = 0;
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

int achouConcurso(typeConcurso concursos[TF], int tl, int idConc)
{
    int i = 0;
    while (i < tl && concursos[i].idConc != idConc)
        i++;

    if (i < tl)
        return i;
    else
        return -1;
}

int achouAposta(typeAposta apostas[TF], int tl, int idAposta)
{
    int i = 0;
    while (i < tl && apostas[i].idAposta != idAposta)
        i++;

    if (i < tl)
        return i;
    else
        return -1;
}

int achouNumApostado(int numApostadoAnalise[10], int tl, int numApostado)
{
    int i = 0;
    while (i < tl && numApostadoAnalise[i] != numApostado)
        i++;

    if (i < tl)
        return i;
    else
        return -1;
}

void apostarNum(int qtde, typeAposta apostas[TF], int tl)
{
    int numApostado, i, cod;
    for (i = 0; i < qtde; i++)
    {
        cod = 0;
        do
        {
            system("cls");
            printf("--- Apostar numeros ---\n");
            printf("-------------------------------------------------------------\n");
            printf("\n[INFO] Voce pode apostar numeros de 1 a 60, sem repeti-los!\n");
            printf("\n-----------------------------------------------------------\n");
            printf("Digite sua aposta num.[%d]: ", i + 1);
            scanf("%d", &numApostado);

            if (numApostado > 0 && numApostado < 61)
            {
                if (achouNumApostado(apostas[tl].numApostado, i, numApostado) == -1)
                {
                    apostas[tl].numApostado[i] = numApostado;
                    cod = 1;
                }
                else
                {
                    printf("\n[ERRO] O numero [%d] ja foi digitado e nao pode ser repitido!\n", numApostado);
                    getch();
                }
            }
            else
            {
                printf("\n[ERRO] Digite numeros de 1 a 60!\n");
                getch();
            }
        } while (cod == 0);
    }
}

void realizarConcurso(typeConcurso concursos[TF], int tl)
{
    int auxId, pos;
    system("cls");
    printf("--- Realizacao de concursos ---\n");
    if (tl == 0)
    {
        printf("\n[ERRO] Nao ha nenhum concurso cadastrado!");
        getch();
    }

    else
    {
        printf("\nDigite o Id do concurso a ser realizado: ");
        fflush(stdin);
        scanf("%d", &auxId);

        if (auxId != 0)
        {
            pos = achouConcurso(concursos, tl, auxId);
            if (pos == -1)
            {
                printf("\n[ERRO] O concurso num. [%d] nao foi encontrado!\n", auxId);
                getch();
            }

            else
            {
                if (concursos[pos].status == 0)
                {
                    concursos[pos].status = 1;
                    for (int i = 0; i < 5; i++)
                        concursos[pos].numeroSorteado[i] = (rand() % 60) + 1;

                    printf("\n[INFO] Os numeros do concurso num. [%d] foram sorteados, verifique em 'Consultar'!\n", auxId);
                    getch();
                }
                else
                {
                    printf("\n[ERRO] Os numeros do concurso num. [%d] ja foram sorteados, verifique em 'Consultar'!\n", auxId);
                    getch();
                }
            }
        }
    }
}

void DesenhaMoldura(int LI, int CI, int LF, int CF)
{
	int a;
	gotoxy(CI,LI);
	printf("%c",201);
	
	gotoxy(CF,LF);
	printf("%c",188);
	
	gotoxy(CI,LF);
	printf("%c",200);
	
	gotoxy(CF,LI);
	printf("%c",187);
	
	for(a=CI+1;a<CF;a++)
	{
		gotoxy(a,LI);
		printf("%c",205);
		gotoxy(a,LF);
		printf("%c",205);
	}
	
	for(a=LI+1;a<LF;a++)
	{
		gotoxy(CI,a);
		printf("%c",186);
		gotoxy(CF,a);
		printf("%c",186);
	}
}

void molduraSistema()
{
    system("cls");
    DesenhaMoldura(1, 10, 3, 110);
    DesenhaMoldura(1, 10, 30, 110);
    DesenhaMoldura(3, 42, 30, 42);
    DesenhaMoldura(12, 10, 30, 42);
    gotoxy(10,3); printf("%c",204);
    gotoxy(10,12); printf("%c",204);
    gotoxy(110,3); printf("%c",185);

    gotoxy(42,3); printf("%c",203);
    gotoxy(42,12); printf("%c",185);
    gotoxy(42,30); printf("%c",202);
}

char menuInicial(void)
{   
    
    molduraSistema();
                        //-------------------------------------------------+-------------------------------------------------
    gotoxy(11,2); printf("                                           MENU PRINCIPAL                                          ");              
    gotoxy(12,4); printf("[A] Concursos\n");                        
    gotoxy(12,5); printf("[B] Apostadores\n");
    gotoxy(12,6); printf("[C] Apostas\n");
    gotoxy(12,7); printf("[D] Excluir\n");
    gotoxy(12,10); printf("[Esc] Sair\n");
    gotoxy(12,11); printf("Opcao desejada: ");
    fflush(stdin);
    return toupper(getche());
}

char menuSubApostadores()
{
    molduraSistema();
    gotoxy(11,2); printf("                                        MENU DE APOSTADORES                                        ");      
    gotoxy(12,4); printf("[A] Cadastrar\n");
    gotoxy(12,5); printf("[B] Consultar\n");
    gotoxy(12,6); printf("[C] Alterar\n");
    gotoxy(12,7); printf("[D] Excluir\n");
    gotoxy(12,10); printf("[Esc] Sair\n");
    gotoxy(12,11); printf("Opcao desejada: ");
    fflush(stdin);
    return toupper(getche());
}

char menuSubConsurso()
{
    molduraSistema();
    gotoxy(11,2); printf("                                         MENU DE CONCURSOS                                         ");     
    gotoxy(12,4); printf("[A] Cadastrar\n");
    gotoxy(12,5); printf("[B] Consultar\n");
    gotoxy(12,6); printf("[C] Alterar\n");
    gotoxy(12,7); printf("[D] Excluir\n");
    gotoxy(12,8); printf("[E] Realizar Sorteio\n");
    gotoxy(12,10); printf("[Esc] Sair\n");
    gotoxy(12,11); printf("Opcao desejada: ");
    fflush(stdin);
    return toupper(getche());
}

char menuSubAposta()
{
    molduraSistema();   
    gotoxy(11,2); printf("                                          MENU DE APOSTAS                                          ");     
    gotoxy(12,4); printf("[A] Cadastrar\n");                              
    gotoxy(12,5); printf("[B] Consultar\n");

    gotoxy(12,10); printf("[Esc] Sair\n");
    gotoxy(12,11); printf("Opcao desejada: ");
    fflush(stdin);
    return toupper(getche());
}

char menuAlterarConcursos()
{
    printf("\n[A] Alterar Data\n");
    printf("[Esc] Sair\n");
    printf("Opcao desejada: ");
    fflush(stdin);
    return toupper(getche());
}

char menuAlterarApostadores()
{
    printf("\n[A] Alterar Nome\n");
    printf("[B] Alterar Telefone\n");
    printf("[Esc] Sair\n");
    printf("Opcao desejada: ");
    fflush(stdin);
    return toupper(getche());
}

void cabecalhoCadastro(char mensagem[10], int tipo)
{

    system("cls");
    printf("--- Cadastro de %s ---\n", mensagem);
    switch (tipo)
    {
    case 1:
        printf("\n[INFO] Para sair do cadastro de %s, apenas aperte [ENTER]\n", mensagem);
        break;
    case 2:
        printf("\n[INFO] Para sair do cadastro de %s, digite [0]\n", mensagem);
        break;
    }
}

void cabecalhoAlterar(char mensagem[10], int tipo)
{
    system("cls");
    printf("--- Alteracao de %s ---\n", mensagem);
    if (tipo == 1)
        printf("%s sendo alterado: \n", mensagem);
}

void cabecalhoCadastroAposta(int exibir, char apostador[12], int concurso)
{
    system("cls");
    printf("--- Cadastro de apostas ---\n");

    if (exibir == 1)
    {
        printf("\n---------------------------\n");
        printf("CPF do apostador: %s\n", apostador);
        printf("Id do concurso: %d\n", concurso);
        printf("---------------------------\n");
    }
}

void cadastroApostadores(typeApostador apostadores[TF], int &tl)
{
    char auxCPF[12], auxNome[30], auxTel[12];
    cabecalhoCadastro("apostadores", 1);
    printf("\nCPF: ");
    fflush(stdin);
    gets(auxCPF);
    while (tl < TF && strcmp(auxCPF, "\0") != 0)
    {
        if (achouCPF(apostadores, tl, auxCPF) == -1)
        {
            printf("Nome: ");
            fflush(stdin);
            gets(auxNome);

            printf("Telefone: ");
            fflush(stdin);
            gets(auxTel);

            if (strcmp(auxNome, "\0") != 0 && strcmp(auxTel, "\0") != 0)
            {
                strcpy(apostadores[tl].CPF, auxCPF);
                strcpy(apostadores[tl].nome, auxNome);
                strcpy(apostadores[tl].telefone, auxTel);
                tl++;
            }
            else
            {
                printf("\n[ERRO] Um ou mais campos estao vazios!");
                getch();
            }
        }

        else
        {
            printf("\n[ERRO] O CPF [%s] ja existe e nao pode ser duplicado!\n\n", auxCPF);
            getch();
        }

        cabecalhoCadastro("apostadores", 1);
        printf("\n------------------------------------------------\n");
        printf("\nCPF: ");
        fflush(stdin);
        gets(auxCPF);
    }
}

void cadastroConcursos(typeConcurso concursos[TF], int &tl)
{
    int auxId, dia, mes, ano;
    cabecalhoCadastro("apostadores", 2);
    printf("\nId. do concurso: ");
    fflush(stdin);
    scanf("%d", &auxId);
    while (tl < TF && auxId != 0)
    {
        if (achouConcurso(concursos, tl, auxId) == -1)
        {
            printf("\nData do concurso: [dd] [mm] [aaaa]: ");
            fflush(stdin);
            scanf("%d %d %d", &dia, &mes, &ano);
            if (dia != 0 && mes != 0 && ano != 0)
            {
                concursos[tl].idConc = auxId;
                concursos[tl].data.dia = dia;
                concursos[tl].data.mes = mes;
                concursos[tl].data.ano = ano;
                for (int i = 0; i < 5; i++)
                    concursos[i].numeroSorteado[i] = 0;

                tl++;
            }

            else
            {
                printf("\n[ERRO] Um ou mais campos estao vazios!");
                getch();
            }
        }

        else
        {
            printf("\n[ERRO] O concurso num. [%d] ja existe e nao pode ser duplicado!\n\n", auxId);
            getch();
        }

        cabecalhoCadastro("apostadores", 2);
        printf("\n------------------------------------------------\n");
        printf("\nId. do concurso: ");
        fflush(stdin);
        scanf("%d", &auxId);
    }
}

void cadastroApostas(typeAposta apostas[TF], int &tl, typeConcurso concursos[TF], int tlc, typeApostador apostadores[TF], int tlp)
{
    int auxId, pos;
    cabecalhoCadastroAposta(0, "", 0);
    if (tlp != 0)
    {
        if (tlc != 0)
        {
            printf("\n[INFO] Para sair do cadastro de apostas, digite [0]\n");
            printf("\nId. da aposta: ");
            fflush(stdin);
            scanf("%d", &auxId);
            while (tl < TF && auxId != 0)
            {
                if (achouAposta(apostas, tl, auxId) == -1)
                {
                    char auxCPF[12];
                    printf("\nDigite o CPF do apostador que ira apostar: ");
                    fflush(stdin);
                    gets(auxCPF);

                    pos = achouCPF(apostadores, tlp, auxCPF);
                    if (pos != -1)
                    {
                        int auxConc;
                        printf("\nDigite o Id do concurso: ");
                        fflush(stdin);
                        scanf("%d", &auxConc);

                        pos = achouConcurso(concursos, tlc, auxConc);
                        if (pos != -1)
                        {
                            int qtde;
						    cabecalhoCadastroAposta(1, auxCPF, auxConc);
						    printf("\n[INFO] Para sair do cadastro de apostas, digite [0]\n");
						    printf("\nQuantos numeros deseja apostar? [Aposte entre 5 a 10 numeros]: ");
						    scanf("%d", &qtde);
						    if (qtde > 4 && qtde < 11)
						    {
						        apostas[tl].qtdeNumApostado = qtde;
						        cabecalhoCadastroAposta(1, auxCPF, auxConc);
						        apostarNum(qtde, apostas, tl);
						        apostas[tl].idConc = auxConc;
						        apostas[tl].idAposta = auxId;
						        strcpy(apostas[tl].CPF, auxCPF);
						        tl++;
						    }
						    else
						    {
						        printf("\n[ERRO] Digite a qtde. solicitada!\n");
						        getch();
						    }
                        }
                        else
                        {
                            printf("\n[ERRO] O concurso num. [%d] nao foi encontrado!\n", auxConc);
                            getch();
                        }
                    }
                    else
                    {
                        printf("\n[ERRO] O CPF [%s] nao foi encontrado!\n", auxCPF);
                        getch();
                    }
                }
                else
                {
                    printf("\n[ERRO] A aposta num. [%d] ja existe e nao pode ser duplicado!\n\n", auxId);
                    getch();
                }

                cabecalhoCadastroAposta(0, "", 0);
                printf("\n[INFO] Para sair do cadastro de apostas, digite [0]\n");
                printf("\n-----------------------------------------------------------\n");
                printf("\nId. da aposta: ");
                fflush(stdin);
                scanf("%d", &auxId);
            }
        }
        else
        {
            printf("\n[ERRO] Nao ha nenhum concurso cadastrado!");
            getch();
        }
    }
    else
    {
        printf("\n[ERRO] Nao ha nenhum apostador cadastrado!");
        getch();
    }
}

void exibirConcurso(typeConcurso concursos[TF], int pos)
{
    printf("\n-----------------------------------------------\n");
    printf("Id do concurso: %d\n", concursos[pos].idConc);
    printf("Data do concurso: %d/%d/%d\n", concursos[pos].data.dia, concursos[pos].data.mes, concursos[pos].data.ano);
    printf("Numeros sorteados: [%d] [%d] [%d] [%d] [%d]\n", concursos[pos].numeroSorteado[0], concursos[pos].numeroSorteado[1], concursos[pos].numeroSorteado[2], concursos[pos].numeroSorteado[3], concursos[pos].numeroSorteado[4]);
}

void exibirTodosConcursos(typeConcurso concursos[TF], int tl)
{
    system("cls");
    printf("--- Exibir Concursos ---\n");
    if (tl == 0)
        printf("\n[ERRO] Nao ha nenhum concurso cadastrado!");
    else
        for (int i = 0; i < tl; i++)
            exibirConcurso(concursos, i);

    getch();
}

void exibirApostador(typeApostador apostadores[TF], int pos)
{
    printf("\n-----------------------------------------------\n");
    printf("CPF: %s\n", apostadores[pos].CPF);
    printf("Nome: %s\n", apostadores[pos].nome);
    printf("Fone: %s\n", apostadores[pos].telefone);
}

void exibirTodosApostadores(typeApostador apostadores[TF], int tl)
{
    system("cls");
    printf("--- Exibir Apostadores ---\n");
    if (tl == 0)
        printf("\n[ERRO] Nao ha nenhum apostador cadastrado!");
    else
        for (int i = 0; i < tl; i++)
            exibirApostador(apostadores, i);

    getch();
}

void exibirAposta(typeAposta apostas[TF], int pos)
{

    printf("\n-----------------------------------------------\n");
    printf("Id da Aposta: %d\n", apostas[pos].idAposta);
    printf("Id do Concurso: %d\n", apostas[pos].idConc);
    printf("CPF do Apostador: %s\n", apostas[pos].CPF);
    printf("Qtde de num. apostados: %d\n", apostas[pos].qtdeNumApostado);
    printf("Num. apostados: ");
    for (int j = 0; j < apostas[pos].qtdeNumApostado; j++)
        printf("[%d] ", apostas[pos].numApostado[j]);
}

void exibirTodasApostas(typeAposta apostas[TF], int tl)
{
    system("cls");
    printf("--- Exibir Apostas ---\n");
    if (tl == 0)
        printf("\n[ERRO] Nao ha nenhuma aposta cadastrada!");
    else
        for (int i = 0; i < tl; i++)
            exibirAposta(apostas, i);

    getch();
}

void alterarDadoConcursos(typeConcurso concursos[TF], int pos, int opr, int tl)
{
    int aux;
    cabecalhoAlterar("Concurso", 1);
    exibirConcurso(concursos, pos);

    switch (opr)
    {
    case 1:
        int dia, mes, ano;
        if(concursos[pos].status==0)
        {
        	printf("\n[INFO] Para cancelar alteracao, digite [0 0 0]\n");
	        printf("\nData atualizada: ");
	        fflush(stdin);
	        scanf("%d %d %d", &dia, &mes, &ano);
	        if (dia != 0 && mes != 0 && ano != 0)
	        {
	            concursos[pos].data.dia = dia;
	            concursos[pos].data.mes = mes;
	            concursos[pos].data.ano = ano;
	        }
        }
        else
        {
        	printf("\n[ERRO] O concurso ja foi apurado!\n");
        	getch();
        }
        
        break;
      
    }
}

void alterarConcursos(typeConcurso concursos[TF], int tl)
{
    char opcao;
    int auxId, pos;
    cabecalhoAlterar("Concurso", 0);
    if (tl == 0)
    {
        printf("\n[ERRO] Nao ha nenhum concurso cadastrado!");
        getch();
    }

    else
    {
        printf("\nDigite o Id do concurso a ser alterado: ");
        fflush(stdin);
        scanf("%d", &auxId);

        if (auxId != 0)
        {
            pos = achouConcurso(concursos, tl, auxId);
            if (pos == -1)
            {
                printf("\n[ERRO] O concurso num. [%d] nao foi encontrado!\n", auxId);
                getch();
            }

            else
            {
                do
                {
                    cabecalhoAlterar("Concurso", 1);
                    exibirConcurso(concursos, pos);
                    opcao = menuAlterarConcursos();
                    switch (opcao)
                    {
                    case 'A':
                        alterarDadoConcursos(concursos, pos, 1, tl);
                        break;
                    }
                } while (opcao != 27);
            }
        }
    }
}

void alterarDadoApostadores(typeApostador apostadores[TF], int pos, int opr, int tl)
{
    char aux[30];
    cabecalhoAlterar("Apostador", 1);
    exibirApostador(apostadores, pos);

    switch (opr)
    {
    case 1:
         printf("\n[INFO] Para cancelar alteracao, apenas aperte [ENTER]\n");
        printf("\nNome atualizado: ");
        fflush(stdin);
        gets(aux);
        if (strcmp(aux, "\0") != 0)
            strcpy(apostadores[pos].nome, aux);
        break;
        break;
    case 2:
       printf("\n[INFO] Para cancelar alteracao, apenas aperte [ENTER]\n");
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
    cabecalhoAlterar("Apostadores", 0);
    if (tl == 0)
    {
        printf("\n[ERRO] Nao ha nenhum apostador cadastrado!");
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
                    cabecalhoAlterar("Apostador", 1);
                    exibirApostador(apostadores, pos);
                    opcao = menuAlterarApostadores();
                    switch (opcao)
                    {
                    case 'A':
                        alterarDadoApostadores(apostadores, pos, 1, tl);
                        break;
                    case 'B':
                        alterarDadoApostadores(apostadores, pos, 2, tl);
                        break;
                    }
                } while (opcao != 27);
            }
        }
    }
}

void confirmaExcluir(int tipo, int pos, char msg[10], typeAposta apostas[TF], typeApostador apostadores[TF], typeConcurso concursos[TF])
{
    system("cls");
    printf("--- Exclusao de %s ---\n", msg);
    printf("\n%s sendo excluido:\n", msg);

    switch (tipo)
    {
    case 1:
        exibirConcurso(concursos, pos);
        break;
    case 2:
        exibirApostador(apostadores, pos);
        break;
    case 3:
        exibirAposta(apostas, pos);
        break;
    }
    printf("\nDeseja mesmo excluir este %s?\n", msg);
    printf("\n[S] Sim \t [N] Nao\n");
}

void excluirConcursos(typeConcurso concursos[TF], int &tl)
{
    char opcao;
    int pos, auxId;
    system("cls");
    printf("--- Exclusao de concursos ---\n");
    if (tl == 0)
    {
        printf("\n[ERRO] Nao ha nenhum concurso cadastrado!");
        getch();
    }

    else
    {
        printf("\n[INFO] Para sair da exclusao, digite [0]\n");
        printf("\nDigite o Id do concurso a ser excluido: ");
        fflush(stdin);
        scanf("%d", &auxId);

        if (auxId != 0)
        {
            pos = achouConcurso(concursos, tl, auxId);
            if (pos == -1)
            {
                printf("\n[ERRO] O concurso [%d] nao foi encontrado!\n", auxId);
                getch();
            }

            else
            {
                confirmaExcluir(1, pos, "concurso", NULL, NULL, concursos);

                while (opcao != 'S' && opcao != 'N')
                    opcao = toupper(getch());

                switch (opcao)
                {
                case 'S':
                    for (; pos < tl - 1; pos++)
                        concursos[pos] = concursos[pos + 1];
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
}

void excluirApostadores(typeApostador apostadores[TF], int &tl)
{
    char auxCPF[12], opcao;
    int pos;
    system("cls");
    printf("--- Exclusao de apostadores ---\n");
    if (tl == 0)
    {
        printf("\n[ERRO] Nao ha nenhum apostador cadastrado!");
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
                printf("\n[ERRO] O CPF [%s] nao foi encontrado!\n", auxCPF);
                getch();
            }

            else
            {
                confirmaExcluir(2, pos, "apostador", NULL, apostadores, NULL);

                while (opcao != 'S' && opcao != 'N')
                    opcao = toupper(getch());

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
}

void excluirApostas(typeAposta apostas[TF], int &tl)
{
    char opcao;
    int pos, aux;
    system("cls");
    printf("--- Exclusao de apostas ---\n");
    if (tl == 0)
    {
        printf("\n[ERRO] Nao ha nenhuma aposta cadastrado!");
        getch();
    }

    else
    {
        printf("\nDigite o Id da aposta a ser excluido: ");
        fflush(stdin);
        scanf("%d", &aux);

        if (aux != 0)
        {
            pos = achouAposta(apostas, tl, aux);
            if (pos == -1)
            {
                printf("\n[ERRO] A aposta num. [%d] nao foi encontrado!\n", aux);
                getch();
            }

            else
            {

                confirmaExcluir(3, pos, "aposta", apostas, NULL, NULL);

                while (opcao != 'S' && opcao != 'N')
                {
                    opcao = toupper(getch());
                }

                switch (opcao)
                {
                case 'S':
                    for (; pos < tl - 1; pos++)
                        apostas[pos] = apostas[pos + 1];
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
}

int main(void)
{

    srand(time(NULL));
    typeApostador apostadores[TF];
    typeConcurso concursos[TF];
    typeAposta apostas[TF];
    int tlp = 0, tlc = 0, tla = 0;
    char opcao, subOpcao;
    do
    {

        opcao = menuInicial();
        switch (opcao)
        {
        case 'A':
            do
            {
                subOpcao = menuSubConsurso();
                switch (subOpcao)
                {
                case 'A':
                    cadastroConcursos(concursos, tlc);
                    break;

                case 'B':
                    exibirTodosConcursos(concursos, tlc);
                    break;

                case 'C':
                    alterarConcursos(concursos, tlc);
                    break;

                case 'D':
                    excluirConcursos(concursos, tlc);
                    break;

                case 'E':
                    realizarConcurso(concursos, tlc);
                    break;
                }
            } while (subOpcao != 27);
            break;

        case 'B':
            do
            {
                subOpcao = menuSubApostadores();
                switch (subOpcao)
                {
                case 'A':
                    cadastroApostadores(apostadores, tlp);
                    break;

                case 'B':
                    exibirTodosApostadores(apostadores, tlp);
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
                subOpcao = menuSubAposta();
                switch (subOpcao)
                {
                case 'A':
                    cadastroApostas(apostas, tla, concursos, tlc, apostadores, tlp);
                    break;

                case 'B':
                    exibirTodasApostas(apostas, tla);
                    break;
                }
            } while (subOpcao != 27);
            break;
        }
    } while (opcao != 27);
    return 0;
}
