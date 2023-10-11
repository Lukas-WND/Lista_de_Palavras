//
// Created by lukas on 11/10/2023.
//

#include <iostream>
#include <string.h>

#define MAX_PALAVRA 50

using namespace std;

typedef struct ListaPalavras {
    char palavra[MAX_PALAVRA];
    ListaPalavras *proxPalavra;
} ListaPalavras;

typedef struct ListaLetras{
    char letra;
    ListaPalavras *inicioPalavras, *fimPalavras;
    ListaLetras *proxLetra;
    ListaLetras *antLetra;
} ListaLetras;

ListaLetras *buscarLetra(ListaLetras *inicio, ListaLetras *fim, char letra){

    if(inicio == NULL){
        return NULL;
    } else if(inicio->letra == letra){
        return inicio;
    } else if(fim->letra == letra){
        return fim;
    } else {
        ListaLetras *aux = inicio;

        while(aux != NULL){
            if(aux->letra == letra){
                return aux;
            }
            aux = aux->proxLetra;
        }
    }

    return NULL;
}

void adicionarLetra(ListaLetras **inicio, ListaLetras **fim, char letra){
    ListaLetras *novaLetra = new ListaLetras();

    novaLetra->letra = letra;
    novaLetra->inicioPalavras = NULL;
    novaLetra->fimPalavras = NULL;

    if(*inicio == NULL){ // Lista Vazia
        (*inicio) = novaLetra;
        (*fim) = novaLetra;
        novaLetra->antLetra = NULL;
        novaLetra->proxLetra = NULL;
    } else {
        ListaLetras *aux = *fim;

        (*fim)->proxLetra = novaLetra;
        (*fim) = (*fim)->proxLetra;
        novaLetra->antLetra = aux;
        novaLetra->proxLetra = NULL;
    }
}

void adicionarPalavra(ListaLetras **inicio, ListaLetras **fim){
    char palavra[MAX_PALAVRA];
    ListaLetras *letra = *inicio;
    ListaPalavras *novaPalavra = new ListaPalavras();

    system("cls");
    cout << "ADICIONAR PALAVRA A LISTA" << endl;
    cout << "Digite a palavra: ";
    cin.getline(palavra, MAX_PALAVRA);

    letra = buscarLetra(*inicio, *fim, palavra[0]);

    if(letra == NULL){
        adicionarLetra(inicio, fim, palavra[0]);
        letra = buscarLetra(*inicio, *fim, palavra[0]);
    }

    strcpy(novaPalavra->palavra, palavra);

    if(letra->inicioPalavras == NULL){ // Lista de palavras vazia
        letra->inicioPalavras = novaPalavra;
        letra->fimPalavras = novaPalavra;
        novaPalavra->proxPalavra = NULL;
    } else {
        letra->fimPalavras->proxPalavra = novaPalavra;
        letra->fimPalavras = letra->fimPalavras->proxPalavra;
        novaPalavra->proxPalavra = NULL;
    }
}

void exibirLetras(ListaLetras *inicio, ListaLetras *fim){
    ListaLetras *aux = inicio;

    if(inicio == NULL){
        cout << "Nenhuma letra esta disponivel!\n\n";
    } else {
        while(aux != NULL){
            cout << aux->letra << " ";
            aux = aux->proxLetra;
        }
    }
}

void exibirPalavras(ListaLetras *inicio, ListaLetras *fim){
    char letra;

    ListaLetras *letraE;

    system("cls");

    if(inicio == NULL){
        cout << "Nenhuma palavra foi cadastrada ainda!\n\n";
    } else {
        cout << "Letras disponiveis para consulta\n\n";
        exibirLetras(inicio, fim);
        cout << "\n\n";

        cout << "Informe a letra que deseja consultar: ";
        cin >> letra;

        letraE = buscarLetra(inicio, fim, letra);

        if(letraE == NULL){
            cout << "\nOpcao nao identificada\n\n";
        } else {
            ListaPalavras *aux = letraE->inicioPalavras;

            cout << "Palavras cadastradas:\n\n";
            while(aux != NULL){
                cout << aux->palavra << endl;
                aux = aux->proxPalavra;
            }
            cout << "\n\n";
        }
    }
    system("pause");
    system("cls");
}

int main(){
    ListaLetras *inicio= NULL;
    ListaLetras *fim = NULL;
    int menu = 1;

    while(menu != 0){
        cout << "************ MENU PRINCIPAL ************\n\n";
        cout << "****************************************" << endl;
        cout << "* [1] - Adicionar uma palavra          *" << endl;
        cout << "* [2] - Exibir as palavras existentes  *" << endl;
        cout << "* [0] - Sair do programa               *" << endl;
        cout << "****************************************" << endl;
        cout << "Selecione uma opcao: ";
        cin >> menu;
        cin.ignore();

        switch (menu) {
            case 1:
                adicionarPalavra(&inicio, &fim);
                break;
            case 2:
                exibirPalavras(inicio, fim);
                break;
            case 0:
                system("cls");
                cout << "Ate a proxima!";
                break;
            default:
                system("cls");
                cout << "Opcao invalida, tente novamente\n\n";
                break;
        }
    }

    system("pause");
}
