#include <iostream>
#include <string.h>
#include <windows.h>

#define DICIONARIO "DicionarioPalavras.txt"
#define MAX_PALAVRA 50
#define MAX_DESCRICAO 500

using namespace std;

typedef struct ListaPalavras {
    char palavra[MAX_PALAVRA];
    char descricao[MAX_DESCRICAO];
    int qtdPesquisas;
    ListaPalavras *proxPalavra;
} ListaPalavras;

typedef struct ListaLetras{
    char letra;
    int qtdPalavras;
    ListaPalavras *inicioPalavras, *fimPalavras;
    ListaLetras *proxLetra;
    ListaLetras *antLetra;
} ListaLetras;

void gotoxy(int x , int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void quadro (){

    gotoxy(0,0); printf("%c", 201);
    for (int i=1;i<=44;i++){
        gotoxy(i,0); printf("%c", 205);
    }
    gotoxy(45,0); printf("%c", 187);
    for (int c=1; c<=11; c++){
        gotoxy(0,c); printf("%c", 186);
    }
    for (int j=1; j<=11; j++){
        gotoxy(45,j); printf("%c", 186);
    }
    gotoxy(0,12); printf("%c", 200);
    for (int i=1;i<=44;i++){
        gotoxy(i,12); printf("%c", 205);
    }
    gotoxy(45,12); printf("%c", 188);
}
//printf("%c", 196);
void exibirMensagem (char *frase){
    int tamanho = strlen(frase);

    for (int i=4; i<=tamanho+9;i++){
        gotoxy(i,1);printf("%c", 196);
    }
    gotoxy(7,3);cout<<frase<< endl;
    gotoxy(3,1); printf("%c", 218);
    for (int j = 2; j<=4; j++){
        gotoxy(3,j); printf("%c", 179);
    }
    gotoxy(3,5); printf("%c", 192);
    for (int c=4; c<=tamanho+9;c++){
        gotoxy(c,5);printf("%c", 196);
    }
    gotoxy(tamanho+10,1);printf("%c", 191);
    gotoxy(tamanho+10,5);printf("%c", 217);
    for (int d = 2; d<=4; d++){
        gotoxy(tamanho+10,d); printf("%c", 179);
    }

    gotoxy(2,7);system("pause");
}



//strlen()

int main(){

    char palavra[MAX_PALAVRA], descricao[MAX_DESCRICAO], opcao = ' ', menu = '!';
    int y=4,x=2;

    cout << "Informe a descricao(MAX 500 caracteres):" << endl;
    cin.getline(descricao, MAX_DESCRICAO);

    for (int i = 0; i < 500 && descricao[i] != '\0'; i++) {
        gotoxy(x,y);cout << descricao[i];
        if ((i + 1) % 15 == 0) {
            if(descricao[i]==' '){
            i+1;
            y++;
            x=1;
            }else{if(descricao[i+1]==' '){
            i=i-1;
            y++;
            x=1;
            }else{
            y++;
            x=1;
            }
        }
        }
        x++;
    }

    return 0;
}

