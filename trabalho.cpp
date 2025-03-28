// Codigo feito por Diego Felippe da Fonseca Calesco e Heitor Franzo Justo

/* --- Comentarios: ---
-ULTIMA ATUALIZACAO: 27/03/2025 05:03 PM
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
    int idConc, numeroSorteado[5], status = 0, qtdePremiados = 0, jaFoiApostado = 0;
    typeData data;
};

struct typeApostador
{
    char CPF[12], nome[30], telefone[11];
    int jaApostou = 0;
};

struct typeAposta
{
    int idAposta, idConc, qtdeNumApostado = 0, numApostado[10], numAcertado[5], qtdeNumAcertado = 0, qtdeTernos = 0, qtdeQuinas = 0, qtdeQuadras = 0;
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

int AchouSorteio(int NumSorteado[5], int tl, int valorNumApostado)
{
    int i = 0;
    while (i < tl && valorNumApostado != NumSorteado[i])
        i++;

    if (i < tl)
        return 1;
    else
        return 0;
}

int achouNumSorteado(int numSorteadolise[5], int tl, int numSorteado)
{
    int i = 0;
    while (i < tl && numSorteadolise[i] != numSorteado)
        i++;

    if (i < tl)
        return i;
    else
        return -1;
}

void msgErro(char mensagem[60], int xMsg)
{
    textcolor(4);
    gotoxy(44, xMsg);
    printf("[ERRO] %s", mensagem);
    gotoxy(44, xMsg + 2);
    textcolor(10);
    gotoxy(44, xMsg + 2);
    Sleep(2000);
    printf("[OK]");
    getch();
    textcolor(7);
}

void msgSucesso(char mensagem[60], int xMsg)
{
    gotoxy(44, xMsg);
    textcolor(10);
    printf("[INFO] %s", mensagem);
    textcolor(7);
    getch();
}

void limparPainel(int xInicio, int yInicio, int xFinal, int yFinal)
{
    for (int y = yInicio; y <= yFinal; y++)
    {
        for (int x = xInicio; x <= xFinal; x++)
        {
            gotoxy(x, y);
            printf(" ");
        }
    }
}

void apostarNum(int qtde, typeAposta apostas[TF], int tl, int numAposta[60], int &dado)
{
    int numApostado, i, cod;
    for (i = 0; i < qtde; i++)
    {
        cod = 0;
        do
        {
            limparPainel(43, 4, 109, 29);
            textcolor(13);
            gotoxy(44, 4);
            printf("--------------------------APOSTAR NUMEROS-------------------------");
            gotoxy(44, 6);
            textcolor(12);
            printf("[INFO] Agora nao e mais possivel cancelar o cadastro da aposta!");
            gotoxy(44, 8);
            textcolor(14);
            printf("[INFO] Voce pode apostar numeros de 1 a 60, sem repeti-los!");
            textcolor(7);
            gotoxy(44, 10);
            printf("Digite sua aposta numero [%d]: ", i + 1);
            scanf("%d", &numApostado);

            if (numApostado > 0 && numApostado < 61)
            {
                if (achouNumApostado(apostas[tl].numApostado, i, numApostado) == -1)
                {
                    apostas[tl].numApostado[i] = numApostado;
                    cod = 1;
                    for (int i = 0; i < 60; i++)
                    {
                        if (numApostado - 1 == i)
                        {
                            numAposta[i] += 1;
                            dado = 1;
                        }
                    }
                }
                else
                    msgErro("Voce ja digitou esse numero!", 12);
            }
            else
                msgErro("Digite um numero de 1 a 60!", 12);
        } while (cod == 0);
    }
}

void realizarConcurso(typeConcurso concursos[TF], int tl, int numSorteado[60], int &dado)
{
    int auxId, pos;
    gotoxy(44, 4);
    textcolor(13);
    printf("--------------------- Realizacao de concursos --------------------");
    textcolor(7);
    if (tl == 0)
        msgErro("Nao ha nenhum concurso cadastrado!", 6);
    else
    {
        gotoxy(44, 6);
        textcolor(14);
        printf("[INFO] Para sair da realizacao de concursos, digite [0]");
        textcolor(7);
        gotoxy(44, 8);
        printf("Digite o Id do concurso a ser realizado: ");
        fflush(stdin);
        scanf("%d", &auxId);

        if (auxId != 0)
        {
            pos = achouConcurso(concursos, tl, auxId);
            if (pos == -1)
                msgErro("O ID do concurso digitado nao foi encontrado!", 10);

            else
            {
                if (concursos[pos].status == 0)
                {
                    concursos[pos].status = 1;
                    int i = 0, numero_sorteado;
                    while (i < 5)
                    {
                        numero_sorteado = (rand() % 60) + 1;
                        if (achouNumSorteado(concursos[pos].numeroSorteado, i, numero_sorteado) == -1)
                        {
                            concursos[pos].numeroSorteado[i] = numero_sorteado;
                            i++;
                        }
                    }

                    for (int x = 0; x < 5; x++)
                    {
                        for (int j = 0; j < 60; j++)
                        {
                            if ((concursos[pos].numeroSorteado[x]) - 1 == j)
                            {
                                numSorteado[j] += 1;
                                dado = 1;
                            }
                        }
                    }

                    msgSucesso("Os numeros desse concurso foram sorteados com sucesso!", 10);
                }
                else
                    msgErro("Os numeros desse concurso ja foram sorteados!", 10);
            }
        }
    }
}

void DesenhaMoldura(int LI, int CI, int LF, int CF)
{
    int a;
    gotoxy(CI, LI);
    printf("%c", 201);

    gotoxy(CF, LF);
    printf("%c", 188);

    gotoxy(CI, LF);
    printf("%c", 200);

    gotoxy(CF, LI);
    printf("%c", 187);

    for (a = CI + 1; a < CF; a++)
    {
        gotoxy(a, LI);
        printf("%c", 205);
        gotoxy(a, LF);
        printf("%c", 205);
    }

    for (a = LI + 1; a < LF; a++)
    {
        gotoxy(CI, a);
        printf("%c", 186);
        gotoxy(CF, a);
        printf("%c", 186);
    }
}

void molduraSistema(int cls)
{
    if (cls == 1)
        system("cls");

    textcolor(11);
    DesenhaMoldura(1, 10, 3, 110);
    DesenhaMoldura(25, 10, 27, 42);
    DesenhaMoldura(1, 10, 30, 110);
    DesenhaMoldura(3, 42, 30, 42);
    DesenhaMoldura(12, 10, 30, 42);
    gotoxy(10, 3);
    printf("%c", 204);
    gotoxy(10, 12);
    printf("%c", 204);
    gotoxy(110, 3);
    printf("%c", 185);
    gotoxy(10, 25);
    printf("%c", 204);
    gotoxy(10, 27);
    printf("%c", 204);
    gotoxy(42, 3);
    printf("%c", 203);
    gotoxy(42, 27);
    printf("%c", 185);
    gotoxy(42, 25);
    printf("%c", 185);
    gotoxy(42, 12);
    printf("%c", 185);
    gotoxy(42, 30);
    printf("%c", 202);
    textcolor(13);
    gotoxy(12, 26);
    printf("== CODIGO DESENVOLVIDO POR ==");
    textcolor(9);
    gotoxy(12, 28);
    printf("Heitor Franzo Justo");
    gotoxy(12, 29);
    printf("Diego Felippe da F. Calesco");
    textcolor(7);
}

void proximaPag(int &j, int cor)
{
    textcolor(14);
    gotoxy(96, 29);
    printf("[PROXIMO -->]");
    textcolor(cor);
    getch();
    j = -1;
    limparPainel(43, 4, 109, 29);
}

void relatorioNumSorteio(int numSorteio[60], int dado)
{
    int numMenosValor = __INT_MAX__, numMaisValor = 0;
    int numMenosNum = 0, numMaisNum = 0;
    gotoxy(44, 6);
    textcolor(9);
    printf("------------- Relatorio de numeros mais sorteados ---------------");
    gotoxy(44, 8);
    textcolor(14);
    if (dado == 0)
        printf("[INFO] Ate o momento, nenhum concurso foi apurado!");
    else
    {
        for (int x = 0; x < 60; x++)
        {
            if (numSorteio[x] > numMaisValor)
            {
                numMaisValor = numSorteio[x];
                numMaisNum = x + 1;
            }

            if (numSorteio[x] < numMenosValor)
            {
                numMenosValor = numSorteio[x];
                numMenosNum = x + 1;
            }
        }

        for (int i = 0; i < 60; i++)
        {
            gotoxy(44, 8);
            printf("O numero que mais e sorteado e: %d, e ele aparece %d vezes.", numMaisNum, numMaisValor);
            gotoxy(44, 10);
            printf("O numero que menos e sorteado e: %d, e ele aparece %d vezes.", numMenosNum, numMenosValor);
        }
    }
}

void relatorioNumAposta(int numAposta[60], int dado)
{
    int numMenosValor = __INT_MAX__, numMaisValor = 0;
    int numMenosNum = 0, numMaisNum = 0;
    gotoxy(44, 12);
    textcolor(9);
    printf("------------- Relatorio de numeros mais apostados ---------------");
    textcolor(14);
    gotoxy(44, 14);
    if (dado == 0)
        printf("[INFO] Ate o momento, ainda nao foi feita nenhuma aposta!");
    else
    {
        for (int x = 0; x < 60; x++)
        {
            if (numAposta[x] > numMaisValor)
            {
                numMaisValor = numAposta[x];
                numMaisNum = x + 1;
            }

            if (numAposta[x] < numMenosValor)
            {
                numMenosValor = numAposta[x];
                numMenosNum = x + 1;
            }
        }

        for (int i = 0; i < 60; i++)
        {
            gotoxy(44, 14);
            printf("O numero mais apostado e: %d, e ele aparece %d vezes.", numMaisNum, numMaisValor);
            gotoxy(44, 16);
            printf("O numero menos apostado e: %d, e ele aparece %d vezes.", numMenosNum, numMenosValor);
        }
    }
}

char menuInicial(int numSorteio[60], int dadoSorteio, int numAposta[60], int dadoAposta)
{

    molduraSistema(1);
    relatorioNumSorteio(numSorteio, dadoSorteio);
    relatorioNumAposta(numAposta, dadoAposta);
    //-------------------------------------------------+-------------------------------------------------
    textcolor(13);
    gotoxy(11, 2);
    printf("                                           MENU PRINCIPAL                                          ");
    textcolor(10);
    gotoxy(44, 4);
    printf("----------- Selecione uma opcao no menu a esquerda --------------");

    gotoxy(12, 4);
    printf("[A] Menu de Concursos");
    gotoxy(12, 5);
    printf("[B] Menu de Apostadores");
    gotoxy(12, 6);
    printf("[C] Menu de Apostas");
    gotoxy(12, 7);
    printf("[D] Relatorios de premiados");
    textcolor(8);
    gotoxy(12, 10);
    printf("[Esc] Sair");
    gotoxy(12, 11);
    textcolor(7);
    printf("Opcao desejada: ");
    fflush(stdin);
    return toupper(getche());
}

char menuSubApostadores()
{
    molduraSistema(1);
    textcolor(13);
    gotoxy(11, 2);
    printf("                                        MENU DE APOSTADORES                                        ");
    textcolor(10);
    gotoxy(44, 4);
    printf("----------- Selecione uma opcao no menu a esquerda --------------");
    gotoxy(12, 4);
    printf("[A] Cadastrar");
    gotoxy(12, 5);
    printf("[B] Consultar");
    gotoxy(12, 6);
    printf("[C] Alterar");
    gotoxy(12, 7);
    printf("[D] Excluir");
    gotoxy(12, 10);
    textcolor(8);
    printf("[Esc] Sair");
    textcolor(7);
    gotoxy(12, 11);
    printf("Opcao desejada: ");
    fflush(stdin);
    return toupper(getche());
}

char menuSubConsurso()
{
    molduraSistema(1);
    textcolor(13);
    gotoxy(11, 2);
    printf("                                         MENU DE CONCURSOS                                         ");
    textcolor(10);
    gotoxy(44, 4);
    printf("----------- Selecione uma opcao no menu a esquerda --------------");
    gotoxy(12, 4);
    printf("[A] Cadastrar");
    gotoxy(12, 5);
    printf("[B] Consultar");
    gotoxy(12, 6);
    printf("[C] Alterar");
    gotoxy(12, 7);
    printf("[D] Excluir");
    gotoxy(12, 8);
    printf("[E] Realizar Sorteio");
    gotoxy(12, 10);
    textcolor(8);
    printf("[Esc] Sair");
    textcolor(7);
    gotoxy(12, 11);
    printf("Opcao desejada: ");
    fflush(stdin);
    return toupper(getche());
}

char menuSubAposta()
{
    molduraSistema(1);
    textcolor(13);
    gotoxy(11, 2);
    printf("                                          MENU DE APOSTAS                                          ");
    textcolor(10);
    gotoxy(44, 4);
    printf("----------- Selecione uma opcao no menu a esquerda --------------");
    gotoxy(12, 4);
    printf("[A] Cadastrar");
    gotoxy(12, 5);
    printf("[B] Consultar");
    gotoxy(12, 10);
    textcolor(8);
    printf("[Esc] Sair");
    gotoxy(12, 11);
    textcolor(7);
    printf("Opcao desejada: ");
    fflush(stdin);
    return toupper(getche());
}

char menuSubRelatorios()
{
    molduraSistema(1);
    textcolor(13);
    gotoxy(11, 2);
    printf("                                          MENU DE RELATORIOS                                       ");
    textcolor(10);
    gotoxy(44, 4);
    printf("----------- Selecione uma opcao no menu a esquerda --------------");
    gotoxy(12, 4);
    printf("[A] Ganhadores por concurso");
    gotoxy(12, 5);
    printf("[B] Acertadores especifico");
    gotoxy(12, 10);
    textcolor(8);
    printf("[Esc] Sair");
    gotoxy(12, 11);
    textcolor(7);
    printf("Opcao desejada: ");
    fflush(stdin);
    return toupper(getche());
}

char menuAlterarConcursos()
{
    molduraSistema(0);
    textcolor(13);
    gotoxy(11, 2);
    printf("                                      MENU DE ALTERAR CONCURSOS                                    ");
    textcolor(10);
    gotoxy(44, 4);
    printf("----------- Selecione uma opcao no menu a esquerda --------------");
    gotoxy(12, 4);
    printf("[A] Alterar data\n");
    gotoxy(12, 10);
    textcolor(8);
    printf("[Esc] Sair\n");
    gotoxy(12, 11);
    textcolor(7);
    printf("Opcao desejada: ");
    fflush(stdin);
    return toupper(getche());
}

char menuAlterarApostadores()
{
    molduraSistema(0);
    textcolor(13);
    gotoxy(11, 2);
    printf("                                     MENU DE ALTERAR APOSTADORES                                   ");
    textcolor(10);
    gotoxy(44, 4);
    printf("----------- Selecione uma opcao no menu a esquerda --------------");
    gotoxy(12, 4);
    printf("[A] Alterar Nome");
    textcolor(10);
    gotoxy(12, 5);
    printf("[B] Alterar Telefone");
    gotoxy(12, 10);
    textcolor(8);
    printf("[Esc] Sair");
    gotoxy(12, 11);
    textcolor(7);
    printf("Opcao desejada: ");
    fflush(stdin);
    return toupper(getche());
}

void cabecalhoCadastro(char mensagem[10], int tipo)
{
    limparPainel(44, 4, 109, 4);
    textcolor(13);
    gotoxy(44, 4);
    printf("-------------------- Cadastro de %s --------------------", mensagem);
    textcolor(14);
    switch (tipo)
    {
    case 1:
        gotoxy(44, 6);
        printf("[INFO] Para sair do cadastro de %s, aperte [ENTER]", mensagem);
        break;
    case 2:
        gotoxy(44, 6);
        printf("[INFO] Para sair do cadastro de %s, digite [0]", mensagem);
        break;
    }
    textcolor(7);
}

void cabecalhoCadastroAposta(int exibir, char apostador[12], int concurso)
{
    limparPainel(44, 4, 109, 4);
    textcolor(13);
    gotoxy(44, 4);
    printf("-------------------- Cadastro de apostas --------------------");
    gotoxy(44, 6);
    textcolor(14);
    printf("[INFO] Para sair do cadastro de apostas, digite [0]");

    if (exibir == 1)
    {
        textcolor(9);
        gotoxy(12, 13);
        printf("Aposta sendo feita por:");
        gotoxy(12, 15);
        printf("CPF do apostador: %s", apostador);
        gotoxy(12, 16);
        printf("Id do concurso: %d", concurso);
    }

    textcolor(7);
}

void cadastroApostadores(typeApostador apostadores[TF], int &tl)
{
    char auxCPF[12], auxNome[30], auxTel[12];
    cabecalhoCadastro("apostadores", 1);
    gotoxy(44, 8);
    printf("Digite o CPF do apostador: ");
    fflush(stdin);
    gets(auxCPF);
    while (tl < TF && strcmp(auxCPF, "\0") != 0 && strcmp(auxCPF, "0") != 0)
    {
        if (achouCPF(apostadores, tl, auxCPF) == -1)
        {
            gotoxy(44, 10);
            printf("Digite o nome do apostador: ");
            fflush(stdin);
            gets(auxNome);

            gotoxy(44, 12);
            printf("Digite o telefone do apostador com DDD: ");
            fflush(stdin);
            gets(auxTel);

            if (strcmp(auxNome, "\0") != 0 && strcmp(auxTel, "\0") != 0 && strcmp(auxNome, "0") != 0 && strcmp(auxTel, "0") != 0)
            {
                strcpy(apostadores[tl].CPF, auxCPF);
                strcpy(apostadores[tl].nome, auxNome);
                strcpy(apostadores[tl].telefone, auxTel);
                msgSucesso("Apostador cadastrado com sucesso!", 14);
                tl++;
            }
            else
                msgErro("Os campos nao podem ser vazios ou nulos!", 14);
        }

        else
            msgErro("Ja existe um apostador cadastrado com esse CPF!", 10);

        limparPainel(43, 4, 109, 29);
        cabecalhoCadastro("apostadores", 1);
        gotoxy(44, 8);
        printf("Digite o CPF do apostador: ");
        fflush(stdin);
        gets(auxCPF);
    }
}

void cadastroConcursos(typeConcurso concursos[TF], int &tl)
{
    int auxId, dia, mes, ano;
    cabecalhoCadastro("Concurso", 2);
    gotoxy(44, 8);
    printf("Digite o ID do concurso: ");
    fflush(stdin);
    scanf("%d", &auxId);
    while (tl < TF && auxId != 0)
    {
        if (achouConcurso(concursos, tl, auxId) == -1)
        {
            gotoxy(44, 10);
            printf("Digite a data do concurso: [dd] [mm] [aaaa]: ");
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

                msgSucesso("Concurso cadastrado com sucesso!", 12);
                tl++;
            }
            else
                msgErro("Os campos da data nao podem ser 0!", 12);
        }

        else
            msgErro("Ja existe um concurso cadastrado com esse ID!", 10);

        limparPainel(43, 4, 109, 29);
        cabecalhoCadastro("Concurso", 2);
        gotoxy(44, 8);
        printf("Digite o ID do concurso: ");
        fflush(stdin);
        scanf("%d", &auxId);
    }
}

void cadastroApostas(typeAposta apostas[TF], int &tl, typeConcurso concursos[TF], int tlc, typeApostador apostadores[TF], int tlp, int numAposta[60], int &dado)
{
    int auxId, pos, posCPF;
    cabecalhoCadastroAposta(0, "", 0);
    if (tlp != 0)
    {
        if (tlc != 0)
        {
            gotoxy(44, 8);
            printf("Digite o ID da aposta: ");
            fflush(stdin);
            scanf("%d", &auxId);
            while (tl < TF && auxId != 0)
            {
                if (achouAposta(apostas, tl, auxId) == -1)
                {
                    char auxCPF[12] = {};
                    gotoxy(44, 10);
                    printf("Digite o CPF do apostador que ira apostar: ");
                    fflush(stdin);
                    gets(auxCPF);

                    posCPF = achouCPF(apostadores, tlp, auxCPF);
                    if (posCPF != -1)
                    {
                        int auxConc;
                        gotoxy(44, 12);
                        printf("Digite o Id do concurso: ");
                        fflush(stdin);
                        scanf("%d", &auxConc);

                        pos = achouConcurso(concursos, tlc, auxConc);
                        if (pos != -1)
                        {
                            if (concursos[pos].status != 1)
                            {
                                concursos[pos].jaFoiApostado = 1;
                                int qtde, cod = 0;
                                do
                                {
                                    limparPainel(43, 4, 109, 29);
                                    cabecalhoCadastroAposta(1, auxCPF, auxConc);
                                    gotoxy(44, 8);
                                    printf("Quantos numeros deseja apostar?");
                                    gotoxy(44, 10);
                                    textcolor(14);
                                    printf("[Selecione entre 5 a 10 numeros]: ");
                                    textcolor(7);
                                    scanf("%d", &qtde);
                                    if (qtde > 4 && qtde < 11)
                                    {
                                        apostas[tl].qtdeNumApostado = qtde;
                                        cabecalhoCadastroAposta(1, auxCPF, auxConc);
                                        apostarNum(qtde, apostas, tl, numAposta, dado);
                                        apostas[tl].idConc = auxConc;
                                        apostas[tl].idAposta = auxId;
                                        strcpy(apostas[tl].CPF, auxCPF);
                                        apostadores[posCPF].jaApostou = 1;
                                        msgSucesso("Aposta cadastrada com sucesso!", 12);
                                        cod = 1;
                                        tl++;
                                    }
                                    else if (qtde != 0)
                                        msgErro("Digite a quantidade solicitada!", 12);
                                } while (cod == 0 && qtde != 0);
                            }
                            else
                                msgErro("Este concurso esta fechado, pois ja foi apurado!", 14);
                        }
                        else
                            msgErro("Este ID de concurso nao foi encontrado!", 14);
                    }
                    else
                        msgErro("Este CPF nao foi encontrado!", 12);
                }
                else
                    msgErro("Ja existe uma aposta com esse ID!", 10);

                limparPainel(43, 4, 109, 29);
                limparPainel(12, 13, 41, 24);
                cabecalhoCadastroAposta(0, "", 0);
                gotoxy(44, 8);
                printf("Digite o ID da aposta: ");
                fflush(stdin);
                scanf("%d", &auxId);
            }
        }
        else
            msgErro("Nao ha nenhum concurso cadastrado!", 6);
    }
    else
        msgErro("Nao ha nenhum apostador cadastrado!", 8);
}

void exibirConcurso(typeConcurso concursos[TF], int pos)
{
    textcolor(9);
    gotoxy(12, 14);
    printf("Id do concurso: %d", concursos[pos].idConc);
    gotoxy(12, 15);
    printf("Data do concurso: %d/%d/%d", concursos[pos].data.dia, concursos[pos].data.mes, concursos[pos].data.ano);
    gotoxy(12, 16);
    printf("Numeros sorteados: ");
    gotoxy(12, 17);
    printf("[%d] [%d] [%d] [%d] [%d]", concursos[pos].numeroSorteado[0], concursos[pos].numeroSorteado[1], concursos[pos].numeroSorteado[2], concursos[pos].numeroSorteado[3], concursos[pos].numeroSorteado[4]);
}

void exibirTodosConcursos(typeConcurso concursos[TF], int tl)
{
    gotoxy(44, 4);
    textcolor(13);
    printf("------------------------ Exibir Concursos ------------------------\n");
    if (tl == 0)
        msgErro("Nao ha nenhum concurso cadastrado!", 6);
    else
    {
        int j = 0, cor = 14;
        for (int i = 0; i < tl; i++)
        {
            textcolor(cor);
            gotoxy(44, 5 + j);
            printf("------------------------------------------------------------------");
            gotoxy(44, 6 + j);
            printf("Id do concurso: %d", concursos[i].idConc);
            gotoxy(44, 7 + j);
            printf("Data do concurso: %d/%d/%d", concursos[i].data.dia, concursos[i].data.mes, concursos[i].data.ano);
            gotoxy(44, 8 + j);
            printf("Numeros sorteados: [%d] [%d] [%d] [%d] [%d]", concursos[i].numeroSorteado[0], concursos[i].numeroSorteado[1], concursos[i].numeroSorteado[2], concursos[i].numeroSorteado[3], concursos[i].numeroSorteado[4]);
            gotoxy(44, 9 + j);
            printf("Status do concurso: %d", concursos[i].status);
            j += 5;
            cor -= 1;

            if (j == 25 || j == 24)
                proximaPag(j, cor);
        }
        getch();
    }
}

void exibirApostador(typeApostador apostadores[TF], int pos)
{
    textcolor(9);
    gotoxy(12, 14);
    printf("CPF do apostador: %s", apostadores[pos].CPF);
    gotoxy(12, 15);
    printf("Nome: %s", apostadores[pos].nome);
    gotoxy(12, 16);
    printf("Fone: %s", apostadores[pos].telefone);
}

void exibirTodosApostadores(typeApostador apostadores[TF], int tl)
{
    gotoxy(44, 4);
    textcolor(13);
    printf("---------------------- Exibir Apostadores ----------------------\n");
    if (tl == 0)
        msgErro("Nao ha nenhum apostador cadastrado!", 6);
    else

    {
        int j = 0, cor = 14;
        for (int i = 0; i < tl; i++)
        {
            textcolor(cor);
            gotoxy(44, 5 + j);
            printf("------------------------------------------------------------------");
            gotoxy(44, 6 + j);
            printf("CPF do apostador: %s", apostadores[i].CPF);
            gotoxy(44, 7 + j);
            printf("Nome: %s", apostadores[i].nome);
            gotoxy(44, 8 + j);
            printf("Fone: %s", apostadores[i].telefone);
            j += 5;
            cor--;

            if (j == 24 || j == 23)
                proximaPag(j, cor);
        }
        getch();
    }
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
    gotoxy(44, 4);
    textcolor(13);
    printf("------------------------ Exibir Apostas -------------------------\n");
    if (tl == 0)
        msgErro("Nao ha nenhuma aposta cadastrado!", 6);
    else
    {
        int cor = 14, t = 0;
        for (int i = 0; i < tl; i++)
        {
            textcolor(cor);
            gotoxy(44, 5 + t);
            printf("------------------------------------------------------------------");
            gotoxy(44, 6 + t);
            printf("ID da Aposta: %d", apostas[i].idAposta);
            gotoxy(44, 7 + t);
            printf("Id do Concurso: %d", apostas[i].idConc);
            gotoxy(44, 8 + t);
            printf("CPF do Apostador: %s", apostas[i].CPF);
            gotoxy(44, 9 + t);
            printf("Qtde de num. apostados: %d", apostas[i].qtdeNumApostado);
            gotoxy(44, 10 + t);
            printf("Num. apostados:");
            for (int j = 0, espaco = 0; j < apostas[i].qtdeNumApostado; j++, espaco += 4)
            {
                gotoxy(60 + espaco, 10 + t);
                printf("[%d] ", apostas[i].numApostado[j]);
            }

            if (t == 18 || t == 17)
                proximaPag(t, cor);

            cor--;
            t += 6;
        }
        getch();
    }
}

void alterarDadoConcursos(typeConcurso concursos[TF], int pos, int opr)
{
    textcolor(13);
    gotoxy(44, 4);
    printf("--------------------- Alteracao de concursos ---------------------");
    textcolor(7);

    switch (opr)
    {
    case 1:
        int dia, mes, ano;
        if (concursos[pos].status == 0)
        {
            gotoxy(44, 6);
            textcolor(14);
            printf("[INFO] Para cancelar alteracao, digite [0] [0] [0]");
            gotoxy(44, 8);
            textcolor(7);
            printf("Data atualizada [dd] [mm] [aaaa]: ");
            fflush(stdin);
            scanf("%d %d %d", &dia, &mes, &ano);
            if (dia != 0 && mes != 0 && ano != 0)
            {
                concursos[pos].data.dia = dia;
                concursos[pos].data.mes = mes;
                concursos[pos].data.ano = ano;
                msgSucesso("Data do concurso alterada com sucesso!", 10);
            }
        }
        else
            msgErro("O concurso ja foi apurado!", 6);

        break;
        limparPainel(12, 13, 41, 25);
    }
}

void alterarConcursos(typeConcurso concursos[TF], int tl)
{
    char opcao;
    int auxId, pos;
    textcolor(13);
    gotoxy(44, 4);
    printf("--------------------- Alteracao de concursos ---------------------");
    if (tl == 0)
        msgErro("Nao ha nenhum concurso cadastrado!", 6);

    else
    {
        gotoxy(44, 6);
        textcolor(14);
        printf("[INFO] Para sair da alteracao de concursos, digite [0]");
        textcolor(7);
        gotoxy(44, 8);
        printf("Digite o Id do concurso a ser alterado: ");
        fflush(stdin);
        scanf("%d", &auxId);

        if (auxId != 0)
        {
            pos = achouConcurso(concursos, tl, auxId);
            if (pos == -1)
                msgErro("O concurso digitado nao foi encontrado!", 10);
            else
            {
                limparPainel(11, 4, 41, 11);
                do
                {
                    limparPainel(12, 13, 41, 24);
                    limparPainel(43, 4, 109, 29);
                    textcolor(14);
                    gotoxy(12, 13);
                    printf("Concurso sendo alterado:");
                    exibirConcurso(concursos, pos);
                    opcao = menuAlterarConcursos();
                    switch (opcao)
                    {
                    case 'A':
                        alterarDadoConcursos(concursos, pos, 1);
                        break;
                    }
                } while (opcao != 27);
            }
        }
    }
}

void alterarDadoApostadores(typeApostador apostadores[TF], int pos, int opr)
{
    char aux[30];
    textcolor(13);
    gotoxy(44, 4);
    printf("--------------------- Alteracao de concursos ---------------------");
    textcolor(7);

    switch (opr)
    {
    case 1:
        textcolor(14);
        gotoxy(44, 6);
        printf("[INFO] Para cancelar alteracao do nome, aperte [ENTER]");
        textcolor(7);
        gotoxy(44, 8);
        printf("Nome atualizado: ");
        fflush(stdin);
        gets(aux);
        if (strcmp(aux, "\0") != 0)
        {
            if (strcmp(aux, "0") != 0)
            {
                strcpy(apostadores[pos].nome, aux);
                msgSucesso("Nome alterado com sucesso!", 10);
            }
            else
                msgErro("O campo de nome nao pode ser nulo!", 10);
        }

        break;
    case 2:
        textcolor(14);
        gotoxy(44, 6);
        printf("[INFO] Para cancelar alteracao do telefone, aperte [ENTER]");
        textcolor(7);
        gotoxy(44, 8);
        printf("Telefone atualizado: ");
        fflush(stdin);
        gets(aux);
        if (strcmp(aux, "\0") != 0)
        {
            strcpy(apostadores[pos].telefone, aux);
            msgSucesso("Telefone alterado com sucesso!", 10);
        }
        else
            msgErro("O campo de telefone nao pode ser nulo!", 10);

        break;
    }
    limparPainel(12, 13, 41, 24);
}

void alterarApostadores(typeApostador apostadores[TF], int tl)
{
    char auxCPF[12], opcao;
    int pos;
    textcolor(13);
    gotoxy(44, 4);
    printf("-------------------- Alteracao de apostadores --------------------");
    if (tl == 0)
        msgErro("Nao ha nenhum apostador cadastrado!", 6);

    else
    {
        textcolor(14);
        gotoxy(44, 6);
        printf("[INFO] Para sair da alteracao de apostadores, aperte [ENTER]");
        textcolor(7);
        gotoxy(44, 8);
        printf("Digite o CPF do apostador a ser alterado: ");
        fflush(stdin);
        gets(auxCPF);

        if (strcmp(auxCPF, "\0") != 0 && strcmp(auxCPF, "0") != 0)
        {
            pos = achouCPF(apostadores, tl, auxCPF);
            if (pos == -1)
                msgErro("Nenhum apostador com o CPF digitado encontrado!", 10);

            else
            {
                limparPainel(11, 4, 41, 11);
                do
                {
                    limparPainel(12, 13, 41, 24);
                    limparPainel(43, 4, 109, 29);
                    textcolor(14);
                    gotoxy(12, 13);
                    printf("Apostador sendo alterado:");
                    exibirApostador(apostadores, pos);
                    opcao = menuAlterarApostadores();
                    switch (opcao)
                    {
                    case 'A':
                        alterarDadoApostadores(apostadores, pos, 1);
                        break;
                    case 'B':
                        alterarDadoApostadores(apostadores, pos, 2);
                        break;
                    }
                } while (opcao != 27);
            }
        }
    }
}

void confirmaExcluir(int tipo, int pos, char msg[10], typeApostador apostadores[TF], typeConcurso concursos[TF])
{
    textcolor(12);
    gotoxy(12, 13);
    printf("%s sendo excluido:", msg);
    switch (tipo)
    {
    case 1:
        exibirConcurso(concursos, pos);
        break;
    case 2:
        exibirApostador(apostadores, pos);
        break;
    }

    textcolor(14);
    gotoxy(44, 10);
    printf("Deseja mesmo excluir este %s?\n", msg);
    gotoxy(50, 12);
    textcolor(12);
    printf("[S] Sim");
    gotoxy(64, 12);
    textcolor(10);
    printf("[N] Nao");
}

void excluirConcursos(typeConcurso concursos[TF], int &tl)
{
    char opcao = ' ';
    int pos, auxId;
    textcolor(13);
    gotoxy(44, 4);
    printf("--------------------- Exclusao de concursos ----------------------");
    if (tl == 0)
        msgErro("Nao ha nenhum concurso cadastrado!", 6);

    else
    {
        textcolor(14);
        gotoxy(44, 6);
        printf("[INFO] Para sair da exclusao, digite [0]");
        textcolor(7);
        gotoxy(44, 8);
        printf("Digite o Id do concurso a ser excluido: ");
        fflush(stdin);
        scanf("%d", &auxId);

        if (auxId != 0)
        {
            pos = achouConcurso(concursos, tl, auxId);
            if (pos == -1)
                msgErro("O ID do concurso digitado nao foi encontrado!", 10);

            else
            {
                if (concursos[pos].status == 0)
                    if (concursos[pos].jaFoiApostado == 0)
                    {
                        confirmaExcluir(1, pos, "Concurso", NULL, concursos);

                        while (opcao != 'S' && opcao != 'N')
                            opcao = toupper(getch());

                        switch (opcao)
                        {
                        case 'S':
                            for (; pos < tl - 1; pos++)
                                concursos[pos] = concursos[pos + 1];
                            tl--;
                            msgSucesso("Exclusao do concurso realizada com sucesso!", 14);
                            break;
                        case 'N':
                            msgSucesso("Exclusao do concurso cancelada!", 14);
                            return;
                            break;
                        }
                    }
                    else
                        msgErro("Essa concurso nao pode ser deletado, pois ja foi apostado!", 10);
                else
                    msgErro("Esse concurso nao pode ser deletado pois ja foi apurado!", 10);
            }
        }
    }
}

void excluirApostadores(typeApostador apostadores[TF], int &tl)
{
    char auxCPF[12], opcao = ' ';
    int pos;
    textcolor(13);
    gotoxy(44, 4);
    printf("-------------------- Exclusao de apostadores ---------------------");
    if (tl == 0)
        msgErro("Nao ha nenhum apostador cadastrado!", 6);

    else
    {
        textcolor(14);
        gotoxy(44, 6);
        printf("[INFO] Para sair da exclusao, aperte [ENTER]");
        textcolor(7);
        gotoxy(44, 8);
        printf("Digite o CPF do apostador a ser excluido: ");
        fflush(stdin);
        gets(auxCPF);

        if (strcmp(auxCPF, "\0") != 0 && strcmp(auxCPF, "0") != 0)
        {
            pos = achouCPF(apostadores, tl, auxCPF);
            if (pos == -1)
                msgErro("Nenhum apostador com o CPF digitado encontrado!", 10);

            else
            {
                if (apostadores[pos].jaApostou == 0)
                {
                    confirmaExcluir(2, pos, "apostador", apostadores, NULL);
                    while (opcao != 'S' && opcao != 'N')
                        opcao = toupper(getch());

                    switch (opcao)
                    {
                    case 'S':
                        for (; pos < tl - 1; pos++)
                            apostadores[pos] = apostadores[pos + 1];
                        tl--;
                        msgSucesso("Exclusao do apostador realizada com sucesso!", 14);
                        break;
                    case 'N':
                        msgSucesso("Exclusao do apostador cancelada!", 14);
                        return;
                        break;
                    }
                }
                else
                    msgErro("Esse apostador nao pode ser deletado pois ele ja apostou!", 10);
            }
        }
    }
}





void InterseccaoConjuntos(int NumSorteado[5], int NumApostado[10], int qtdeNumApostado, int &qtdeAcerto, int numAcertados[5])
{
    int i = 0;
    qtdeAcerto = 0;
    for (i = 0; i < qtdeNumApostado; i++)
        if (AchouSorteio(NumSorteado, 5, NumApostado[i]))
            numAcertados[qtdeAcerto++] = NumApostado[i];
}

void ganhouAposta(typeConcurso concursos[TF], typeAposta apostas[TF], int posAposta, int posConcurso, int tlc)
{
    InterseccaoConjuntos(concursos[posConcurso].numeroSorteado, apostas[posAposta].numApostado, apostas[posAposta].qtdeNumApostado, apostas[posAposta].qtdeNumAcertado, apostas[posAposta].numAcertado);
    int i, qtdeAcerto = apostas[posAposta].qtdeNumAcertado;
    apostas[posAposta].qtdeTernos = 0;
    apostas[posAposta].qtdeQuadras = 0;
    apostas[posAposta].qtdeQuinas = 0;

    switch (qtdeAcerto)
    {
    case 3:
        apostas[posAposta].qtdeTernos++;
        break;
    case 4:
        apostas[posAposta].qtdeQuadras++;
        break;
    case 5:
        apostas[posAposta].qtdeQuinas++;
        break;
    }
}

void limparRelatorio(int &linhasNaTela, int cor, int t)
{
    proximaPag(t, cor);
    linhasNaTela = 3;
}

void relatorioGanhadores(typeConcurso concursos[TF], int tl, typeAposta apostas[TF], int tla, int qtdeApurado)
{
    gotoxy(44, 4);
    textcolor(13);
    printf("------------------------ Exibir Ganhadores ----------------------");
    if (qtdeApurado == 0)
        msgErro("Ate o momento, nenhum concurso foi apurado!", 6);
    else
    {
        int t = 1, cor = 14, l, i, cont = 0, linhasNaTela = 4;
        for (int i = 0; i < tl; i++)
            if (concursos[i].status == 1)
                for (int j = 0; j < tla; j++)
                    if (apostas[j].idConc == concursos[i].idConc)
                        ganhouAposta(concursos, apostas, j, i, tl);

        for (l = 0; l < tl; l++)
        {
            t = 1;
            linhasNaTela = 4;
            gotoxy(44, 4);
            textcolor(13);
            printf("------------------------ Exibir Ganhadores ----------------------");
            if (concursos[l].status == 1)
            {
                textcolor(cor);
                gotoxy(44, t + linhasNaTela);
                printf("------------------------- [CONCURSO %d] --------------------------", concursos[l].idConc);
                linhasNaTela++;
                gotoxy(44, t + linhasNaTela);
                printf("Apostadores que fizeram terno:");
                linhasNaTela += 2;
                textcolor(cor - 1);
                for (i = 0; i < tla; i++)
                {
                    if (concursos[l].idConc == apostas[i].idConc)
                    {
                        textcolor(cor);
                        gotoxy(12, 13);
                        printf("CONCURSO: %d", concursos[l].idConc);
                        gotoxy(12, 15);
                        printf("Qtd. apostador com terno:");
                        gotoxy(12, 16);
                        printf("%d apostadores", apostas[i].qtdeTernos);
                        gotoxy(12, 18);
                        printf("Qtd. de apostador com quadra:");
                        gotoxy(12, 19);
                        printf("%d apostadores", apostas[i].qtdeQuadras);
                        gotoxy(12, 21);
                        printf("Qtd. apostador com quina:");
                        gotoxy(12, 22);
                        printf("%d apostadores", apostas[i].qtdeQuinas);
                    }
                }

                textcolor(cor - 1);
                for (i = 0; i < tla; i++)
                {
                    if (apostas[i].qtdeNumAcertado == 3 && concursos[l].idConc == apostas[i].idConc)
                    {
                        if (linhasNaTela + 1 > 29)
                            limparRelatorio(linhasNaTela, cor, t);
                        gotoxy(44, t + linhasNaTela);
                        printf("ID da aposta: %d", apostas[i].idAposta);
                        linhasNaTela++;
                        if (linhasNaTela + 1 > 29)
                            limparRelatorio(linhasNaTela, cor, t);
                        gotoxy(44, t + linhasNaTela);
                        printf("CPF do apostador: %s", apostas[i].CPF);
                        linhasNaTela++;
                        if (linhasNaTela + 1 > 29)
                            limparRelatorio(linhasNaTela, cor, t);
                        gotoxy(44, t + linhasNaTela);
                        printf("Numeros acertados:");
                        for (int j = 0, espaco = 0; j < apostas[i].qtdeNumAcertado; j++, espaco += 4)
                        {
                            gotoxy(63 + espaco, linhasNaTela + t);
                            printf("[%d] ", apostas[i].numAcertado[j]);
                        }
                        linhasNaTela += 2;
                        cont++;
                    }
                }

                if (cont == 0)
                {
                    if (linhasNaTela + 1 > 29)
                        limparRelatorio(linhasNaTela, cor, t);
                    gotoxy(44, t + linhasNaTela);
                    printf("Nenhum apostador acertou um terno neste concurso!");
                    linhasNaTela += 2;
                }

                cont = 0;

                textcolor(cor);
                if (linhasNaTela + 2 > 29)
                    limparRelatorio(linhasNaTela, cor, t);
                gotoxy(44, t + linhasNaTela);
                printf("------------------------------------------------------------------");
                linhasNaTela++;
                if (linhasNaTela + 1 > 29)
                    limparRelatorio(linhasNaTela, cor, t);
                gotoxy(44, t + linhasNaTela);
                printf("Apostadores que fizeram quadra:");
                linhasNaTela += 2;
                textcolor(cor - 1);
                for (i = 0; i < tla; i++)
                {
                    if (apostas[i].qtdeNumAcertado == 4 && concursos[l].idConc == apostas[i].idConc)
                    {
                        if (linhasNaTela + 1 > 29)
                            limparRelatorio(linhasNaTela, cor, t);
                        gotoxy(44, t + linhasNaTela);
                        printf("ID da aposta: %d", apostas[i].idAposta);
                        linhasNaTela++;
                        if (linhasNaTela + 1 > 29)
                            limparRelatorio(linhasNaTela, cor, t);
                        gotoxy(44, t + linhasNaTela);
                        printf("CPF do apostador: %s", apostas[i].CPF);
                        linhasNaTela++;
                        if (linhasNaTela + 1 > 29)
                            limparRelatorio(linhasNaTela, cor, t);
                        gotoxy(44, t + linhasNaTela);
                        printf("Numeros acertados:");
                        for (int j = 0, espaco = 0; j < apostas[i].qtdeNumAcertado; j++, espaco += 4)
                        {
                            gotoxy(63 + espaco, t + linhasNaTela);
                            printf("[%d] ", apostas[i].numAcertado[j]);
                        }
                        linhasNaTela += 2;
                        cont++;
                    }
                }

                if (cont == 0)
                {
                    if (linhasNaTela + 1 > 29)
                        limparRelatorio(linhasNaTela, cor, t);
                    gotoxy(44, t + linhasNaTela);
                    printf("Nenhum apostador acertou uma quadra neste concurso!");
                    linhasNaTela += 2;
                }

                cont = 0;

                textcolor(cor);
                if (linhasNaTela + 2 > 29)
                    limparRelatorio(linhasNaTela, cor, t);
                gotoxy(44, t + linhasNaTela);
                printf("------------------------------------------------------------------");
                linhasNaTela++;
                if (linhasNaTela + 1 > 29)
                    limparRelatorio(linhasNaTela, cor, t);
                gotoxy(44, t + linhasNaTela);
                printf("Apostadores que fizeram quina:");
                linhasNaTela += 2;
                textcolor(cor - 1);
                for (i = 0; i < tla; i++)
                {
                    if (apostas[i].qtdeNumAcertado == 5 && concursos[l].idConc == apostas[i].idConc)
                    {
                        if (linhasNaTela + 1 > 29)
                            limparRelatorio(linhasNaTela, cor, t);
                        gotoxy(44, t + linhasNaTela);
                        printf("ID da aposta: %d", apostas[i].idAposta);
                        linhasNaTela++;
                        if (linhasNaTela + 1 > 29)
                            limparRelatorio(linhasNaTela, cor, t);
                        gotoxy(44, t + linhasNaTela);
                        printf("CPF do apostador: %s", apostas[i].CPF);
                        linhasNaTela++;
                        if (linhasNaTela + 1 > 29)
                            limparRelatorio(linhasNaTela, cor, t);
                        gotoxy(44, t + linhasNaTela);
                        printf("Numeros acertados:");
                        for (int j = 0, espaco = 0; j < apostas[i].qtdeNumAcertado; j++, espaco += 4)
                        {
                            gotoxy(63 + espaco, t + linhasNaTela);
                            printf("[%d] ", apostas[i].numAcertado[j]);
                        }
                        linhasNaTela += 2;
                        cont++;
                    }
                }
                if (cont == 0)
                {
                    if (linhasNaTela + 1 > 29)
                        limparRelatorio(linhasNaTela, cor, t);
                    gotoxy(44, t + linhasNaTela);
                    printf("Nenhum apostador acertou uma quina neste concurso!");
                    linhasNaTela += 2;
                }

                cor--;
            }
            limparRelatorio(linhasNaTela, cor, t);
            limparPainel(12, 13, 41, 24);
        }
    }
}

void relatorioQtdAcerto(typeConcurso concursos[TF], int tl, typeAposta apostas[TF], int tla, int qtdeApurado)
{
    int auxNum;
    textcolor(13);
    gotoxy(44,4);
    printf("--------------- Relatorio por quantidade de acerto ---------------");
    if (qtdeApurado == 0)
        msgErro("Ate o momento, nenhum concurso foi apurado!", 6);
    else
    {
        printf("Digite a quantidade de numeros acertados: ");
        scanf("%d",&auxNum);
    }
        
    getch();
}

int main(void)
{
    textcolor(14);
    printf("[INFO] Antes de usar o programa, aumente o tamanho da janela.\n\n\n");
    textcolor(10);
    printf("[OK]");
    textcolor(7);
    getch();
    srand(time(NULL));
    typeApostador apostadores[TF];
    typeConcurso concursos[TF];
    typeAposta apostas[TF];
    int tlp = 0, tlc = 0, tla = 0;
    int numAposta[60], numSorteio[60], dadoAposta = 0, dadoSorteio = 0;
    char opcao, subOpcao;
    do
    {

        opcao = menuInicial(numSorteio, dadoSorteio, numAposta, dadoAposta);
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
                    realizarConcurso(concursos, tlc, numSorteio, dadoSorteio);
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
                    cadastroApostas(apostas, tla, concursos, tlc, apostadores, tlp, numAposta, dadoAposta);
                    break;

                case 'B':
                    exibirTodasApostas(apostas, tla);
                    break;
                }
            } while (subOpcao != 27);
            break;

        case 'D':
            do
            {
                subOpcao = menuSubRelatorios();
                switch (subOpcao)
                {
                case 'A':
                    relatorioGanhadores(concursos, tlc, apostas, tla, dadoSorteio);
                    break;

                case 'B':
                    relatorioQtdAcerto(concursos, tlc, apostas, tla, dadoSorteio);
                    break;

                case 'C':

                    break;

                case 'D':
                    relatorioNumAposta(numAposta, dadoAposta);
                    break;
                }
            } while (subOpcao != 27);
            break;
        }
    } while (opcao != 27);
    return 0;
}
