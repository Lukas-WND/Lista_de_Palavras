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

void quadroMP()
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
    for (int c = 1; c <= 13; c++)
    {
        gotoxy(0, c);
        printf("%c", 186);
    }
    for (int j = 1; j <= 13; j++)
    {
        gotoxy(45, j);
        printf("%c", 186);
    }
    gotoxy(0, 14);
    printf("%c", 200);
    for (int i = 1; i <= 44; i++)
    {
        gotoxy(i, 14);
        printf("%c", 205);
    }
    gotoxy(45, 14);
    printf("%c", 188);
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

int exibirApenasPalavra(ListaLetras *inicio, ListaLetras *fim, const char *frase){

    int y = 4;
    system("cls");
    if (inicio == NULL){
        exibirMensagem("Nenhuma palavra cadastrada!");
    } else {
        ListaLetras *auxLetras = inicio;
        gotoxy(2,2);printf("%c",254);
        gotoxy(4,2); cout<< frase;
        while (auxLetras != NULL){
            gotoxy(1,y);printf("%c", 218);
            for (int i= 2; i<=49; i++){
                gotoxy(i,y); printf("%c", 196);
            }
            gotoxy(50,y); printf("%c", 191);
            for (int j=y+1; j<=y+3;j++){
                gotoxy(50,j); printf("%c", 179);
            }
            for (int j=y+1; j<=y+3;j++){
                gotoxy(1,j); printf("%c", 179);
            }
            gotoxy(1,y+4); printf("%c", 195);
            gotoxy(50,y+4); printf("%c", 180);
            for (int i= 2; i<=49; i++){
                gotoxy(i,y+4); printf("%c", 196);
            }
            gotoxy(18,y+2); cout << "Letra " << auxLetras->letra << " = "<< auxLetras-> qtdPalavras;
            y=y+5;
            if (auxLetras ->inicioPalavras ==NULL){
               gotoxy(y,15);cout << "Lisra de Palavras Vazias";
               y=y+1;
            } else {
                ListaPalavras *auxPalavras = auxLetras->inicioPalavras;
                while(auxPalavras != NULL){
                    gotoxy(1,y); printf("%c", 179);
                    gotoxy(50,y); printf("%c", 179);
                    gotoxy(2,y); cout << auxPalavras->palavra;
                    auxPalavras=auxPalavras->proxPalavra;
                    y=y+1;
                }
                gotoxy(1,y);printf("%c", 192);
                gotoxy(50,y);printf("%c", 217);
                for(int i=2;i<=49;i++){
                    gotoxy(i,y);printf("%c", 196);
                }
            }
            y=y+1;
            auxLetras = auxLetras->proxLetra;
        }

    }
    cout<< endl;
    return y;
}

int exibirPalavraeDescricao(ListaLetras *inicio, ListaLetras *fim, const char *frase){

    int y = 4;
    system("cls");
    if (inicio == NULL){
        exibirMensagem("Nenhuma palavra cadastrada!");
    } else{
        ListaLetras *auxLetras = inicio;

        gotoxy(26,2); cout<< frase;

        while(auxLetras != NULL){

            gotoxy(1,y);printf("%c", 218);
            for(int i=2;i<=60;i++){
                gotoxy(i,y); printf("%c", 196);
            }
            gotoxy(61,y); printf("%c", 191);
            for (int j=y+1; j<=y+3;j++){
                gotoxy(61,j); printf("%c", 179);
            }
            for (int j=y+1; j<=y+3;j++){
                gotoxy(1,j); printf("%c", 179);
            }
            gotoxy(1,y+4); printf("%c", 195);
            gotoxy(61,y+4); printf("%c", 180);
            for(int i=2;i<=60;i++){
                if (i==31){
                    gotoxy(i,y+4); printf("%c", 194);
                }else{
                    gotoxy(i,y+4); printf("%c", 196);
                }
            }
            gotoxy(25,y+2); cout << "Letra " << auxLetras->letra << " = "<< auxLetras-> qtdPalavras;
            y=y+4;
            if (auxLetras -> inicioPalavras == NULL){
                gotoxy(y,15);cout << "Lisra de Palavras Vazias";
                y=y+1;
            }else {
                ListaPalavras *auxPalavras = auxLetras->inicioPalavras;
                while(auxPalavras!=NULL){



                    //quando conseguir descobrir quantas quebras em descrições tera, altera esse gotoxy para um for usando o y anterior e y atual q é o com as quebras
                    gotoxy(1,y+1);printf("%c", 179);
                    gotoxy(31,y+1);printf("%c", 179);
                    gotoxy(61,y+1); printf("%c", 179);
                    //quando conseguir descobrir quantas quebras em descrições tera, altera esse gotoxy para um for usando o y anterior e y atual q é o com as quebras

                    gotoxy(2,y+1); cout << auxPalavras->palavra;

                    //Alteração necessaria para quebrar descrição
                    gotoxy(32,y+1);cout << auxPalavras->descricao;
                    //Alteração necessaria para quebrar descrição
                    auxPalavras=auxPalavras->proxPalavra;
                    y=y+2;
                    gotoxy(1,y);printf("%c", 195);
                    gotoxy(61,y); printf("%c", 180);
                    for(int i=2;i<=60;i++){
                        if (i==31){
                            gotoxy(i,y); printf("%c", 197);
                        }else{
                            gotoxy(i,y); printf("%c", 196);
                        }
                    }

                }
                gotoxy(1,y);printf("%c", 192);
                gotoxy(61,y);printf("%c", 217);
                for(int i=2;i<=60;i++){
                    if (i==31){
                        gotoxy(i,y); printf("%c", 193);
                    }else{
                        gotoxy(i,y); printf("%c", 196);
                    }
                }
                y=y+1;
            }
        auxLetras = auxLetras->proxLetra;
        }
    }

cout<< endl;
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
                        system("pause");
                    }

                    auxPalavras = auxPalavras->proxPalavra;
                }

                auxLetras = auxLetras->proxLetra;
            }
        } else {
        exibirMensagem("Nenhuma palavra cadastrada!");
        }
    } else {
        exibirMensagem("Digito invalido");
    }


}

void exibirPalavra(ListaPalavras palavra){
    system("cls");
    cout << palavra.palavra << ": " << palavra.descricao << endl;
    system("pause");
}

void listarDicionario(ListaLetras *inicio, ListaLetras *fim){

    system("cls");

    if(inicio == NULL){
        exibirMensagem("Nenhuma palavra cadastrada!");
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
    int y;

    while(menu != '0'){
        system("cls");
        quadro();
        gotoxy(42,3);printf("%c", 191);
        for (int j = 4; j <= 9; j++)
        {
            gotoxy(3,j);printf("%c", 179);
        }
        for (int c = 4; c <= 9; c++)
        {
            gotoxy(42,c);printf("%c", 179);
        }
        gotoxy(3,10);printf("%c", 192);
        gotoxy(42,10);printf("%c", 217);
        for (int k = 4; k <= 41; k++)
        {
            gotoxy(k,10);printf("%c", 196);
        }
        gotoxy(3, 3);printf("%c", 218);
        for (int i = 4; i <= 41; i++)
        {
            gotoxy(i, 3);
            printf("%c", 196);
        }
        gotoxy(15,2);cout << "MENU DE PESQUISA";
        gotoxy(5,5);cout << "[1] - Pesquisar por palavra   " ;
        gotoxy(5,6);cout << "[2] - Pesquisar por relevancia" ;
        gotoxy(5,7);cout << "[0] - Voltar ao menu principal" ;
        gotoxy(5,8);cout << "Selecione a opcao: ";
        cin >> menu;
        cin.ignore();

        switch (menu) {
            case '1':
                y=exibirApenasPalavra(inicio,fim, "Pesquisa por Palavra");
                gotoxy(3,y+1);printf("%c",254);
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
                system("cls");
                cout << "Informe a palavra que deseja buscar: ";
                cin.getline(palavra, MAX_PALAVRA);
                exibirPorRelevancia(inicio, fim, palavra);
                break;
        }
    }
    system("cls");
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



int compararPalavras(const void *a, const void *b) {
    return strcmp(((ListaPalavras *)a)->palavra, ((ListaPalavras *)b)->palavra);
}

void ordenarAlfabeticamente(ListaLetras *inicio, ListaLetras *fim) {
    int totalPalavras = 0;

    ListaLetras *letra = inicio;

    // Conta o número total de palavras
    while (letra != NULL) {
        totalPalavras += letra->qtdPalavras;
        letra = letra->proxLetra;
    }

    if (totalPalavras == 0) {
        exibirMensagem("Nenhuma palavra cadastrada para ordenar.");
        return;
    }

    // Aloca um vetor de palavras
    ListaPalavras *palavrasOrdenadas = new ListaPalavras[totalPalavras];
    int index = 0;

    letra = inicio;

    // Copia as palavras para o vetor
    while (letra != NULL) {
        ListaPalavras *palavra = letra->inicioPalavras;

        while (palavra != NULL) {
            strcpy(palavrasOrdenadas[index].palavra, palavra->palavra);
            strcpy(palavrasOrdenadas[index].descricao, palavra->descricao);
            palavrasOrdenadas[index].qtdPesquisas = palavra->qtdPesquisas;
            index++;
            palavra = palavra->proxPalavra;
        }

        letra = letra->proxLetra;
    }

    // Ordena o vetor alfabeticamente
    qsort(palavrasOrdenadas, totalPalavras, sizeof(ListaPalavras), compararPalavras);

    // Exibe as palavras ordenadas
    system("cls");
    cout << "Palavras ordenadas alfabeticamente:\n\n";
    for (int i = 0; i < totalPalavras; i++) {
        cout << palavrasOrdenadas[i].palavra << ": " << palavrasOrdenadas[i].descricao << endl;
    }

    delete[] palavrasOrdenadas;
    system("pause");
}



int main()
{
    ListaLetras *inicio = NULL;
    ListaLetras *fim = NULL;
    char palavra[MAX_PALAVRA], descricao[MAX_DESCRICAO], opcao = ' ', menu = '!';
    int y=0;

    carregarArquivo(&inicio, &fim);

    while (menu != '0')
    {
        quadroMP();
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
        cout << "[1] - Adicionar palavra           " << endl;
        gotoxy(5, 5);
        cout << "[2] - Pesquisar palavras " << endl;
        gotoxy(5, 6);
        cout << "[3] - Deletar palavra             " << endl;
        gotoxy(5, 7);
        cout << "[4] - Atualizar palavra           " << endl;
        gotoxy(5, 8);
        cout << "[5] - Ordenar alfabeticamente" << endl;
        gotoxy(5, 9);
        cout << "[6] - Exibir Dicionario "<< endl;
        gotoxy(5, 10);
        cout << "[0] - Sair do programa                " << endl;

        gotoxy(42, 3);
        printf("%c", 191);
        for (int j = 4; j <= 10; j++)
        {
            gotoxy(3, j);
            printf("%c", 179);
        }
        for (int c = 4; c <= 10; c++)
        {
            gotoxy(42, c);
            printf("%c", 179);
        }
        gotoxy(3, 11);
        printf("%c", 192);
        gotoxy(42, 11);
        printf("%c", 217);
        for (int k = 4; k <= 41; k++)
        {
            gotoxy(k, 11);
            printf("%c", 196);
        }
        gotoxy(4, 12);
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
                //int y;
                system("cls");
                //listarDicionario(inicio, fim);
                y=exibirApenasPalavra(inicio,fim,"DELETAR");
                y++;
                // cin.ignore();
                for (int i = 1; i <= 24; i++)
                {
                    gotoxy(i, y);
                    printf("%c", 196);
                }
                gotoxy(25, y);
                cout << " DELETAR\n\n\n";
                for (int v = 34; v <= 60; v++)
                {
                    gotoxy(v, y);
                    printf("%c", 196);
                }
                gotoxy(1, y+1);
                printf("%c", 254);
                gotoxy(3, y+1);
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
                //int l=0;
                y=exibirApenasPalavra(inicio,fim,"Atualizar");
                gotoxy(2,y);
                cout << "Informe a palavra que deseja atualizar: ";
                cin.getline(palavra, MAX_PALAVRA);
                system("cls");
                if (validPalavra(palavra))
                {
                    ListaPalavras *palavraEncontrada = buscarPalavra(buscarLetra(inicio, fim, palavra[0]), strupr(palavra));

                    if (palavraEncontrada != NULL)
                    {
                        char novaPalavra[MAX_PALAVRA];
                        for(int j=1;j<=2;j++){
                            gotoxy(0,j);printf("%c",179);
                        }
                        gotoxy(1,1);printf("%c ", 254);cout << "Palavra atual: " << palavraEncontrada->palavra << endl;
                        gotoxy(1,2);printf("%c ", 254);cout << "Nova palavra: ";
                        cin.getline(novaPalavra, MAX_PALAVRA);
                        gotoxy(0,3);printf("%c", 179);
                        gotoxy(1,3);printf("%c ", 254);cout << "Descricao: " << palavraEncontrada->descricao << "\n\n";
                        cout << "Deseja atualizar a descricao de " << novaPalavra << "? [S/N]" << endl;
                        cout << "Digite a opcao: ";
                        cin >> opcao;
                        cin.ignore();

                        if (opcao == 'S' || opcao == 's')
                        {
                            system("cls");
                            for(int j=1;j<=2;j++){
                                gotoxy(0,j);printf("%c",179);
                            }
                            gotoxy(1,1);printf("%c ", 254);cout << "Palavra: " << novaPalavra << endl;
                            gotoxy(1,2);printf("%c ", 254);cout << "Informe a nova descricao: ";
                            cin.getline(descricao, MAX_DESCRICAO);
                            atualizarPalavra(&inicio, &fim, palavraEncontrada, novaPalavra, descricao);
                            exibirMensagem("Palavra e Descricao Atualizada");
                        }
                        else if (opcao == 'N' || opcao == 'n')
                        {
                            atualizarPalavra(&inicio, &fim, palavraEncontrada, novaPalavra, palavraEncontrada->descricao);
                            exibirMensagem("Palavra Atualizada");
                        }
                        else
                        {
                            exibirMensagem("Opcao nao identificada");
                        }
                    }
                    else
                    {
                        exibirMensagem("Palavra nao encontrada");
                    }
                }
                else
                {
                    exibirMensagem("Palavra Invalida");
                }
                system("cls");

                break;
            case '5':
                system("cls");
                ordenarAlfabeticamente(inicio, fim);
                exibirMensagem("Palavras ordenadas alfabeticamente com sucesso!");
                system("cls");
                break;
            case '6':
                exibirPalavraeDescricao(inicio,fim,"DICIONARIO");
                system("pause");
                system("cls");
                break;
            case '0':
                system("cls");
                exibirMensagem("Ate a proxima!");
                system("cls");
                break;
            default:
                system("cls");
                exibirMensagem("Opcao invalida, tente novamente");
                system("cls");
                break;
        }
    }
}
