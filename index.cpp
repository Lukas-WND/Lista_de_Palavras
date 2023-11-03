//
// Created by lukas on 11/10/2023.
//

#include <iostream>
#include <string.h>
#include <windows.h>

#define DICIONARIO "dicionario.txt"
#define MAX_PALAVRA 50
#define MAX_DESCRICAO 500

using namespace std;

typedef struct ListaPalavras
{
    char palavra[MAX_PALAVRA];
    char descricao[MAX_DESCRICAO];
    int qtdPesquisas;
    ListaPalavras *proxPalavra;
} ListaPalavras;

typedef struct ListaLetras
{
    char letra;
    int qtdPalavras;
    ListaPalavras *inicioPalavras, *fimPalavras;
    ListaLetras *proxLetra;
    ListaLetras *antLetra;
} ListaLetras;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void quadro()
{

    gotoxy(0, 0);
    printf("%c", 201);
    for (int i = 1; i <= 44; i++)
    {
        gotoxy(i, 0);
        printf("%c", 205);
    }
    gotoxy(45, 0);
    printf("%c", 187);
    for (int c = 1; c <= 11; c++)
    {
        gotoxy(0, c);
        printf("%c", 186);
    }
    for (int j = 1; j <= 11; j++)
    {
        gotoxy(45, j);
        printf("%c", 186);
    }
    gotoxy(0, 12);
    printf("%c", 200);
    for (int i = 1; i <= 44; i++)
    {
        gotoxy(i, 12);
        printf("%c", 205);
    }
    gotoxy(45, 12);
    printf("%c", 188);
}

void exibirMensagem(const char *frase)
{
    int tamanho = strlen(frase);

    system("cls");

    for (int i = 4; i <= tamanho + 9; i++)
    {
        gotoxy(i, 3);
        printf("%c", 196);
    }
    gotoxy(7, 5);
    cout << frase << endl;
    gotoxy(3, 3);
    printf("%c", 218);
    for (int j = 4; j <= 6; j++)
    {
        gotoxy(3, j);
        printf("%c", 179);
    }
    gotoxy(3, 7);
    printf("%c", 192);
    for (int c = 4; c <= tamanho + 9; c++)
    {
        gotoxy(c, 7);
        printf("%c", 196);
    }
    gotoxy(tamanho + 10, 3);
    printf("%c", 191);
    gotoxy(tamanho + 10, 7);
    printf("%c", 217);
    for (int d = 4; d <= 6; d++)
    {
        gotoxy(tamanho + 10, d);
        printf("%c", 179);
    }

    gotoxy(2, 9);
    system("pause");
}

bool validPalavra(char *palavra) { // Verifica se o caracter está entre 'A' e 'Z' ou 'a' e 'z'
    int i = 0;

    while (palavra[i] != '\0') {

        if ((palavra[i] < 65 || palavra[i] > 122) || (palavra[i] > 90 && palavra[i] < 97))
        {
            return false;
        }
        else
        {
            i++;
        }
    }

    return true;
}

ListaLetras *buscarLetra(ListaLetras *inicio, ListaLetras *fim, char letra)
{

    if (inicio == NULL)
    {
        return NULL;
    }
    else if (inicio->letra == letra)
    {
        return inicio;
    }
    else if (fim->letra == letra)
    {
        return fim;
    }
    else
    {
        ListaLetras *aux = inicio;

        while (aux != NULL)
        {
            if (aux->letra == letra)
            {
                return aux;
            }
            aux = aux->proxLetra;
        }
    }

    return NULL;
}

ListaPalavras *buscarPalavra(ListaLetras *letra, char *palavra)
{

    if (letra == NULL)
    {
        return NULL;
    }
    if (letra->inicioPalavras == NULL)
    {
        return NULL;
    }
    else if (strcmp(letra->inicioPalavras->palavra, palavra) == 0)
    {
        return letra->inicioPalavras;
    }
    else if (strcmp(letra->fimPalavras->palavra, palavra) == 0)
    {
        return letra->fimPalavras;
    }
    else
    {
        ListaPalavras *aux = letra->inicioPalavras;

        while (aux != NULL)
        {
            if (strcmp(aux->palavra, palavra) == 0)
            {
                return aux;
            }
            else
            {
                aux = aux->proxPalavra;
            }
        }
    }

    return NULL;
}

ListaPalavras *buscarPalavraAnterior(ListaLetras *letra, char *palavra)
{

    if (letra->inicioPalavras == NULL)
    { // lista vazia
        return NULL;
    }
    else if (strcmp(letra->inicioPalavras->palavra, palavra) == 0)
    { // palavra no começo da lista
        return NULL;
    }
    else
    {
        ListaPalavras *aux = letra->inicioPalavras;

        while (aux != NULL)
        {
            if (aux->proxPalavra == NULL)
            { // se a proxima palavra nao existe
                return NULL;
            }
            else if (strcmp(aux->proxPalavra->palavra, palavra) == 0)
            { // se proxima palavra é igual à passada como parâmetro
                return aux;
            }
            else
            {
                aux = aux->proxPalavra;
            }
        }
    }

    return NULL;
}

void salvarArquivo(ListaLetras *inicio, ListaLetras *fim)
{
    FILE *arq;

    arq = fopen(DICIONARIO, "w");

    if (arq == NULL)
    {
        exibirMensagem("Erro ao abrir arquivo");
    }
    else
    {
        ListaLetras *aux = inicio;

        while (aux != NULL)
        {
            ListaPalavras *palavra = aux->inicioPalavras;

            while (palavra != NULL)
            {
                fprintf(arq, "%s/%s\n", palavra->palavra, palavra->descricao);
                palavra = palavra->proxPalavra;
            }
            aux = aux->proxLetra;
        }
    }

    fclose(arq);
}

void inserirLetra(ListaLetras **inicio, ListaLetras **fim, char letra) {
    ListaLetras *novaLetra = new ListaLetras();

    novaLetra->letra = toupper(letra);
    novaLetra->qtdPalavras = 0;
    novaLetra->inicioPalavras = NULL;
    novaLetra->fimPalavras = NULL;

    if ((*inicio) == NULL)
    { // Lista Vazia
        (*inicio) = novaLetra;
        (*fim) = novaLetra;
        novaLetra->antLetra = NULL;
        novaLetra->proxLetra = NULL;
    }
    else
    {
        (*fim)->proxLetra = novaLetra;
        (*fim)->proxLetra->antLetra = (*fim);
        (*fim) = (*fim)->proxLetra;
        novaLetra->proxLetra = NULL;
    }
}

void inserirPalavra(ListaLetras **inicio, ListaLetras **fim, char *palavra, char *descricao)
{

    if (validPalavra(palavra))
    {
        ListaLetras *letra;
        ListaPalavras *novaPalavra = new ListaPalavras();

        palavra = strupr(palavra);
        descricao[0] = toupper(descricao[0]);

        if (buscarLetra(*inicio, *fim, palavra[0]) == NULL) {
            inserirLetra(inicio, fim, palavra[0]);
        }

        letra = buscarLetra(*inicio, *fim, palavra[0]);

        novaPalavra->qtdPesquisas = 0;
        strcpy(novaPalavra->palavra, palavra);
        strcpy(novaPalavra->descricao, descricao);

        if (letra->inicioPalavras == NULL) {
            letra->inicioPalavras = novaPalavra;
            letra->fimPalavras = novaPalavra;
            novaPalavra->proxPalavra = NULL;
        } else {
            letra->fimPalavras->proxPalavra = novaPalavra;
            letra->fimPalavras = letra->fimPalavras->proxPalavra;
            novaPalavra->proxPalavra = NULL;
        }

        letra->qtdPalavras++;
        salvarArquivo(*inicio, *fim);
    }
    else
    {
        exibirMensagem("Palavra contem um digito invalido");
    }
}

void exibirLetras(ListaLetras *inicio, ListaLetras *fim)
{
    ListaLetras *aux = inicio;

    if (inicio == NULL)
    {
        exibirMensagem("Nenhuma letra disponivel");
    }
    else
    {
        while (aux != NULL)
        {
            cout << aux->letra << " " << aux->qtdPalavras << "; ";
            aux = aux->proxLetra;
        }
    }
}

void exibirPorRelevancia(ListaLetras *inicio, ListaLetras *fim, char *palavra){
    if(validPalavra(palavra)){
        if(inicio != NULL){
            ListaLetras *auxLetras = inicio;

            while(auxLetras != NULL){
                ListaPalavras *auxPalavras = auxLetras->inicioPalavras;

                while(auxPalavras != NULL){
                    char *achou;

                    achou = strstr(auxPalavras->descricao, palavra);

                    if(achou != NULL){
                        cout << auxPalavras->palavra << ": " << auxPalavras->descricao << endl;
                    }

                    auxPalavras = auxPalavras->proxPalavra;
                }

                auxLetras = auxLetras->proxLetra;
            }
        }
    } else {
        exibirMensagem("Digito invalido");
    }

    system("pause");
}

void exibirPalavra(ListaPalavras palavra){
    system("cls");
    cout << palavra.palavra << ": " << palavra.descricao << endl;
    system("pause");
}

void listarDicionario(ListaLetras *inicio, ListaLetras *fim){

    system("cls");

    if(inicio == NULL){
        cout << "Nenhuma palavra cadastrada!" << endl;
    } else {
        ListaLetras *auxLetras = inicio;

        while(auxLetras != NULL){
            cout << auxLetras->letra << "              " << auxLetras->qtdPalavras << endl;
            cout << "----------------" << endl;

            if(auxLetras->inicioPalavras == NULL){
                cout << "Lista de Palavras vazia" << endl;
            } else {
                ListaPalavras *auxPalavras = auxLetras->inicioPalavras;

                while(auxPalavras != NULL){
                    cout << auxPalavras->palavra << endl;

                    auxPalavras = auxPalavras->proxPalavra;
                }
            }

            cout << "\n\n";
            auxLetras = auxLetras->proxLetra;
        }
    }
}

void menuExibir(ListaLetras *inicio, ListaLetras *fim){
    char menu = ' ';
    char palavra[MAX_PALAVRA];

    while(menu != '0'){
        system("cls");
        cout << "MENU DE PESQUISA" << endl;
        cout << "[1] - Pesquisar por palavra   " << endl;
        cout << "[2] - Pesquisar por relevancia" << endl;
        cout << "[0] - Voltar ao menu principal" << endl;
        cout << "Selecione a opcao: ";
        cin >> menu;
        cin.ignore();

        switch (menu) {
            case '1':
                listarDicionario(inicio, fim);
                cout << "Informe a palavra que deseja buscar: ";
                cin.getline(palavra, MAX_PALAVRA);

                if(validPalavra(palavra)){
                    ListaLetras *letra = buscarLetra(inicio, fim, toupper(palavra[0]));

                    if(letra == NULL){
                        exibirMensagem("Palavra nao encontrada");
                    } else {
                        ListaPalavras *aux = letra->inicioPalavras;

                        if(aux == NULL){
                            exibirMensagem("Lista de palavras vazia");
                        } else {
                            while(aux != NULL){
                                if(aux->proxPalavra == NULL && strcmp(aux->palavra, strupr(palavra)) != 0){
                                    exibirMensagem("Palavra nao encontrada");
                                } else if(strcmp(aux->palavra, strupr(palavra)) == 0){
                                    exibirPalavra(*aux);
                                    break;
                                }

                                aux = aux->proxPalavra;
                            }
                        }
                    }
                }
                break;
            case '2':
                cout << "Informe a palavra que deseja buscar: ";
                cin.getline(palavra, MAX_PALAVRA);
                exibirPorRelevancia(inicio, fim, palavra);
                break;
        }
    }
}

void deletarLetra(ListaLetras **inicio, ListaLetras **fim, ListaLetras *letra)
{
    if ((*inicio) == letra && (*fim) == letra)
    {
        (*inicio) = NULL;
        (*fim) = NULL;
        delete (letra);
    }
    else if ((*inicio) == letra)
    {
        (*inicio) = letra->proxLetra;
        (*inicio)->antLetra = NULL;
        delete (letra);
    }
    else if ((*fim) == letra)
    {
        (*fim) = letra->antLetra;
        (*fim)->proxLetra = NULL;
        delete (letra);
    }
    else
    {
        letra->antLetra->proxLetra = letra->proxLetra;
        letra->proxLetra->antLetra = letra->antLetra;
        delete (letra);
    }
}

void deletarPalavra(ListaLetras **inicio, ListaLetras **fim, char *palavra)
{
    if (validPalavra(palavra))
    {

        palavra = strupr(palavra);

        ListaLetras *letra = buscarLetra(*inicio, *fim, palavra[0]);

        if (letra != NULL)
        {
            ListaPalavras *pAtual = buscarPalavra(letra, palavra);
            ListaPalavras *pAnterior = buscarPalavraAnterior(letra, palavra);

            if (pAtual != NULL)
            {
                if (letra->inicioPalavras == pAtual)
                {
                    letra->inicioPalavras = pAtual->proxPalavra;
                }
                else if (letra->fimPalavras == pAtual)
                {
                    pAnterior->proxPalavra = NULL;
                }
                else
                {
                    pAnterior->proxPalavra = pAtual->proxPalavra;
                }

                delete (pAtual);
                letra->qtdPalavras--;
                salvarArquivo(*inicio, *fim);
            }
            else
            {
                // palavra nao encontrada
                // inserirErro();
            }

            if (letra->qtdPalavras == 0)
            {
                deletarLetra(inicio, fim, letra);
            }
        }
        else
        {
            // letra nao encontrada
            // inserirErro();
        }
    }
    else
    {
        // inserirErro();
    }
}

void atualizarPalavra(ListaLetras **inicio,
                      ListaLetras **fim,
                      ListaPalavras *palavra,
                      char *novaPalavra,
                      char *novaDescricao)
{

    novaPalavra = strupr(novaPalavra);
    novaDescricao[0] = toupper(novaDescricao[0]);

    if (validPalavra(novaPalavra))
    { // nova palavra é válida
        if (palavra->palavra[0] == novaPalavra[0])
        {
            strcpy(palavra->palavra, novaPalavra);
            strcpy(palavra->descricao, novaDescricao);
        }
        else
        {
            deletarPalavra(inicio, fim, palavra->palavra);
            inserirPalavra(inicio, fim, novaPalavra, novaDescricao);
        }
        salvarArquivo(*inicio, *fim);
    }
    else
    {
        // inserirErro();
    }
}

void carregarArquivo(ListaLetras **inicio, ListaLetras **fim) {
    FILE *arq;
    arq = fopen(DICIONARIO, "r");

    if (arq == NULL) {
        cout << "Erro ao abrir o arquivo" << endl;
    }
    else {
        char linha[MAX_PALAVRA + MAX_DESCRICAO + 2];

        while (fgets(linha, sizeof(linha), arq) != NULL) {
            char *palavra = strtok(linha, "/");
            char *descricao = strtok(NULL, "/");

            if (palavra && descricao) {
                // Remove caracteres de quebra de linha, se houver
                palavra = strtok(palavra, "\n");
                descricao = strtok(descricao, "\n");

                inserirPalavra(inicio, fim, palavra, descricao);
            }
            else {
                cout << "Erro ao processar linha: " << linha << endl;
            }
        }
    }

    fclose(arq);
}


int main()
{
    ListaLetras *inicio = NULL;
    ListaLetras *fim = NULL;
    char palavra[MAX_PALAVRA], descricao[MAX_DESCRICAO], opcao = ' ', menu = '!';

    carregarArquivo(&inicio, &fim);

    while (menu != '0')
    {
        quadro();
        gotoxy(1, 2);
        cout << "               MENU PRINCIPAL             \n\n\n";
        gotoxy(3, 3);
        printf("%c", 218);
        for (int i = 4; i <= 41; i++)
        {
            gotoxy(i, 3);
            printf("%c", 196);
        }
        gotoxy(5, 4);
        cout << "[1] - Adicionar uma palavra           " << endl;
        gotoxy(5, 5);
        cout << "[2] - Exibir as palavras existentes   " << endl;
        gotoxy(5, 6);
        cout << "[3] - Deletar uma palavra             " << endl;
        gotoxy(5, 7);
        cout << "[4] - Atualizar uma palavra           " << endl;
        gotoxy(5, 8);
        cout << "[0] - Sair do programa                " << endl;

        gotoxy(42, 3);
        printf("%c", 191);
        for (int j = 4; j <= 8; j++)
        {
            gotoxy(3, j);
            printf("%c", 179);
        }
        for (int c = 4; c <= 8; c++)
        {
            gotoxy(42, c);
            printf("%c", 179);
        }
        gotoxy(3, 9);
        printf("%c", 192);
        gotoxy(42, 9);
        printf("%c", 217);
        for (int k = 4; k <= 41; k++)
        {
            gotoxy(k, 9);
            printf("%c", 196);
        }
        gotoxy(4, 10);
        cout << "Selecione uma opcao: ";
        cin >> menu;
        cin.ignore();

        switch (menu)
        {
            case '1':
                system("cls");

                gotoxy(27, 2);
                cout << "               MENU ADICIONAR             \n\n\n";
                for (int i = 4; i <= 90; i++)
                {
                    gotoxy(i, 3);
                    printf("%c", 196);
                }
                gotoxy(5, 4);
                printf("%c", 254);
                gotoxy(7, 4);
                cout << "Informe a palavra(MAX 50 caracteres): " << endl;
                gotoxy(44, 4);
                cin.getline(palavra, MAX_PALAVRA);
                gotoxy(5, 5);
                printf("%c", 254);
                gotoxy(7, 5);
                cout << "Informe a descricao(MAX 500 caracteres):" << endl;
                gotoxy(48, 5);
                cin.getline(descricao, MAX_DESCRICAO);
                inserirPalavra(&inicio, &fim, palavra, descricao);
                system("cls");

                break;
            case '2':
                menuExibir(inicio, fim);

                break;
            case '3':
                system("cls");
                listarDicionario(inicio, fim);
                // cin.ignore();
                for (int i = 4; i <= 27; i++)
                {
                    gotoxy(i, 2);
                    printf("%c", 196);
                }
                gotoxy(28, 2);
                cout << " MENU DELETAR\n\n\n";
                for (int v = 42; v <= 63; v++)
                {
                    gotoxy(v, 2);
                    printf("%c", 196);
                }
                gotoxy(4, 3);
                printf("%c", 254);
                gotoxy(6, 3);
                cout << "Informe a palavra: ";
                cin.getline(palavra, MAX_PALAVRA);
                // cout << "PALAVRA DELETADA";

                deletarPalavra(&inicio, &fim, palavra);
                system("cls");
                exibirMensagem("PALAVRA DELETADA");
                system("cls");
                break;
            case '4':
                system("cls");

                cout << "Informe a palavra que deseja atualizar: ";
                cin.getline(palavra, MAX_PALAVRA);

                if (validPalavra(palavra))
                {
                    ListaPalavras *palavraEncontrada = buscarPalavra(buscarLetra(inicio, fim, palavra[0]), strupr(palavra));

                    if (palavraEncontrada != NULL)
                    {
                        char novaPalavra[MAX_PALAVRA];

                        cout << "Palavra atual: " << palavraEncontrada->palavra << endl;
                        cout << "Nova palavra: ";
                        cin.getline(novaPalavra, MAX_PALAVRA);

                        cout << "\nDescricao atual: " << palavraEncontrada->descricao << "\n\n";
                        cout << "Deseja atualizar a descricao de " << novaPalavra << "? [S/N]" << endl;
                        cout << "Digite a opcao: ";
                        cin >> opcao;
                        cin.ignore();

                        if (opcao == 'S' || opcao == 's')
                        {
                            cout << "\nInforme a nova descricao: ";
                            cin.getline(descricao, MAX_DESCRICAO);
                            atualizarPalavra(&inicio, &fim, palavraEncontrada, novaPalavra, descricao);
                        }
                        else if (opcao == 'N' || opcao == 'n')
                        {
                            atualizarPalavra(&inicio, &fim, palavraEncontrada, novaPalavra, palavraEncontrada->descricao);
                        }
                        else
                        {
                            cout << "\nOpcao nao identificada" << endl;
                        }
                    }
                    else
                    {
                        cout << "\nPalavra nao encontrada" << endl;
                    }
                }
                else
                {
                    cout << "\nPalavra Invalida" << endl;
                    // inserirErro();
                }

                system("pause");
                system("cls");

                break;
            case '5':
                system("cls");
                cout << "Informe a palavra: ";
                cin.getline(palavra, MAX_PALAVRA);
                exibirPorRelevancia(inicio, fim, palavra);
            case '0':
                system("cls");
                cout << "Ate a proxima!";
                break;
            default:
                system("cls");
                cout << "Opcao invalida, tente novamente\n\n";
                system("pause");
                break;
        }
    }

    system("pause");
}
