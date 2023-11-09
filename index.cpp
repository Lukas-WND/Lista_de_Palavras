//
// Created by lukas on 11/10/2023.
//

#include <iostream>
#include <cstring>
#include <windows.h>

#define DICIONARIO "dicionario.txt"
#define MAX_PALAVRA 50
#define MAX_DESCRICAO 500

using namespace std;

// Definição dos tipos necessários para a implementação do sistema
typedef struct ListaPalavras
{
  char palavra[MAX_PALAVRA];
  char descricao[MAX_DESCRICAO];
  int relevancia;
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

// Método de navegação entre as linhas e colunas do terminal
void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Método responsavel pelo quadro mais externo do menu Principal. (1 a ser feito usando o goto)
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

// Método responsavel pelo quadeo do menu de pesquisar, alteração do quadroMP. (2 a ser criado com o goto)
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

// Método que recebe uma string e a exibe dentro de um espaço delimitado
void exibirMensagem(const char *frase)
{
  // responsavel por descobrir o tamanho da string que o metodo recebeu, o tamanho é usado para variar o tamanho do quadro de acordo com o tamanho da string
  int tamanho = strlen(frase);

  system("cls");

  // tamanho + 9 é usado para poder deixar centralizado a mensagem
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

// Método que valida uma string dígito por dígito, para saber se dentro dela contém apenas letras
bool validPalavra(char *palavra)
{
  int i = 0;

  while (palavra[i] != '\0')
  {

    // Verifica se o caracter está entre 'A' e 'Z' ou 'a' e 'z'
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

// Método procura uma letra dentro de uma lista e retorna o nó caso o encontre
ListaLetras *buscarLetra(ListaLetras *inicio, ListaLetras *fim, char letra)
{

  // Verifica se a lista está vazia
  if (inicio == NULL)
  {
    return NULL;
  } // Verifica se a letra está no começo da lista
  else if (inicio->letra == letra)
  {
    return inicio;
  } // Verifica se a letra está no fim da lista
  else if (fim->letra == letra)
  {
    return fim;
  } // Verifica se a letra está no meio da lista
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

  // Se nenhuma das condições forem satisfeitas, retorna NULL
  return NULL;
}

/* Método recebe uma lista de letras e na lista de palavras dentro dela
 * procura a string passada como parâmetro, se achar, retorna o ponteiro da mesma
 * */
ListaPalavras *buscarPalavra(ListaLetras *letra, char *palavra)
{

  // Verifica se o nó da letra existe
  if (letra == NULL)
  {
    return NULL;
  } // Verifica se a lista está vazia
  if (letra->inicioPalavras == NULL)
  {
    return NULL;
  } // Verifica se a palavra está no começo da lista
  else if (strcmp(letra->inicioPalavras->palavra, palavra) == 0)
  {
    return letra->inicioPalavras;
  } // Verifica se a palavra está no fim da lista
  else if (strcmp(letra->fimPalavras->palavra, palavra) == 0)
  {
    return letra->fimPalavras;
  } // Verifica se a palavra está no meio da lista
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

/* Método recebe uma lista de letras e na lista de palavras dentro dela
 * procura a string passada como parâmetro, se achar, retorna o ponteiro anterior à ela
 * */
ListaPalavras *buscarPalavraAnterior(ListaLetras *letra, char *palavra)
{

  // Verifica se a lista está vazia
  if (letra->inicioPalavras == NULL)
  {
    return NULL;
  } // Verifica se a palavra está no começo da lista
  else if (strcmp(letra->inicioPalavras->palavra, palavra) == 0)
  {
    return NULL;
  } // Verifica se a palavra está no meio da lista
  else
  {
    ListaPalavras *aux = letra->inicioPalavras;

    while (aux != NULL)
    {
      if (aux->proxPalavra == NULL) // Verifica se a proxima palavra nao existe
      {
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

// Método salva o conteúdo de uma lista na memória dentro de um arquivo de texto
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
        // Insere uma nova linha dentro do arquivo
        fprintf(arq, "%s/%s\n", palavra->palavra, palavra->descricao);
        palavra = palavra->proxPalavra;
      }
      aux = aux->proxLetra;
    }
  }

  fclose(arq);
}

// Método recebe uma letra como parâmetro e a insere no final de uma lista duplamente encadeada
void inserirLetra(ListaLetras **inicio, ListaLetras **fim, char letra)
{
  ListaLetras *novaLetra = new ListaLetras(); // Atribui uma nova região de memória à um ponteiro

  novaLetra->letra = toupper(letra); // A letra fica maiúscula
  novaLetra->qtdPalavras = 0;
  novaLetra->inicioPalavras = NULL;
  novaLetra->fimPalavras = NULL;

  // Verifica se a lista está vazia
  if ((*inicio) == NULL)
  {
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

// Método recece uma palavra e descrição como parâmetro e a insere dentro de uma lista simplesmente encadeada
void inserirPalavra(ListaLetras **inicio, ListaLetras **fim, char *palavra, char *descricao)
{

  // Faz a validação da string palavra passada como parâmetro
  if (validPalavra(palavra))
  {
    ListaLetras *letra;
    ListaPalavras *novaPalavra = new ListaPalavras(); // Atribui uma nova região de memória à um ponteiro

    palavra = strupr(palavra);            // A string torna todos os seus caracteres maiúsculos
    descricao[0] = toupper(descricao[0]); // O primeiro caracter da string se torna maiúsculo

    // Verifica se a primeira letra da palavra passada não existe na lista de letras
    if (buscarLetra(*inicio, *fim, palavra[0]) == NULL)
    {
      inserirLetra(inicio, fim, palavra[0]); // Cria um novo nó contendo essa letra
    }

    // Atribui o endereço do nó da lista a um ponteiro local
    letra = buscarLetra(*inicio, *fim, palavra[0]);

    novaPalavra->relevancia = 0;
    strcpy(novaPalavra->palavra, palavra);
    strcpy(novaPalavra->descricao, descricao);

    // Verifica se a lista de palavras está vazia
    if (letra->inicioPalavras == NULL)
    {
      letra->inicioPalavras = novaPalavra;
      letra->fimPalavras = novaPalavra;
      novaPalavra->proxPalavra = NULL;
    }
    else
    {
      letra->fimPalavras->proxPalavra = novaPalavra;
      letra->fimPalavras = letra->fimPalavras->proxPalavra;
      novaPalavra->proxPalavra = NULL;
    }

    letra->qtdPalavras++;
    // salvarArquivo(*inicio, *fim);
  } // Exibe uma mensagem de erro caso a palavra passada como parâmetro contenha um dígito inválido
  else
  {
    exibirMensagem("Palavra contem um digito invalido");
  }
}

// Método deleta uma letra da lista de letras
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

// Método deleta um nó da lista de palavras
void deletarPalavra(ListaLetras **inicio, ListaLetras **fim, char *palavra)
{
  // Faz a validação da palavra passada como parâmetro
  if (validPalavra(palavra))
  {

    palavra = strupr(palavra); // Todos os caracteres da string se tornam maiúsculos

    ListaLetras *letra = buscarLetra(*inicio, *fim, palavra[0]);

    // Verifica se a primeira letra da palavra existe na lista de letras
    if (letra != NULL)
    {
      ListaPalavras *pAtual = buscarPalavra(letra, palavra);
      ListaPalavras *pAnterior = buscarPalavraAnterior(letra, palavra);

      // Verifica se a palavra passada como parâmetro está contida na lista
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
        // salvarArquivo(*inicio, *fim);
      } // A palavra não está na lista
      else
      {
        exibirMensagem("Palavra nao encontrada");
      }

      // Caso a quantidade de palavras dentro de uma lista de letras seja 0, o nó da letra é deletado
      if (letra->qtdPalavras == 0)
      {
        deletarLetra(inicio, fim, letra);
      }
    }
    // A letra não existe na lista
    else
    {
      exibirMensagem("Palavra nao encontrada");
    }
  } // A palavra contém um dígito inválido
  else
  {
    exibirMensagem("Palavra contem um digito invalido");
  }
}

int exibirApenasPalavra(ListaLetras *inicio, ListaLetras *fim, const char *frase)
{ // Metodo responsavel por exibir as palavras em quadro que contem a letra inicial dessa palavra (maleavel)

  int y = 4;
  system("cls");
  if (inicio == NULL)
  {
    exibirMensagem("Nenhuma palavra cadastrada!"); // mensagem que será exibida em uma "caixa"
  }
  else
  {
    ListaLetras *auxLetras = inicio;
    gotoxy(2, 2);
    printf("%c", 254);
    gotoxy(4, 2);
    cout << frase;
    while (auxLetras != NULL)
    { // while responsavel por criar a "caixa" da letra e exibir a letra dentro dela até acabar os itens de letras
      gotoxy(1, y);
      printf("%c", 218);
      for (int i = 2; i <= 49; i++)
      {
        gotoxy(i, y);
        printf("%c", 196);
      }
      gotoxy(50, y);
      printf("%c", 191);
      for (int j = y + 1; j <= y + 3; j++)
      {
        gotoxy(50, j);
        printf("%c", 179);
      }
      for (int j = y + 1; j <= y + 3; j++)
      {
        gotoxy(1, j);
        printf("%c", 179);
      }
      gotoxy(1, y + 4);
      printf("%c", 195);
      gotoxy(50, y + 4);
      printf("%c", 180);
      for (int i = 2; i <= 49; i++)
      {
        gotoxy(i, y + 4);
        printf("%c", 196);
      }
      gotoxy(18, y + 2);
      cout << "Letra " << auxLetras->letra << " = " << auxLetras->qtdPalavras; // responsavel por exibir na tela a letra e a quantidade de palvras
      y = y + 5;
      if (auxLetras->inicioPalavras == NULL)
      {
        gotoxy(y, 15);
        cout << "Lisra de Palavras Vazias";
        y = y + 1;
      }
      else
      {
        ListaPalavras *auxPalavras = auxLetras->inicioPalavras;
        while (auxPalavras != NULL)
        { // while responsavel por exibir todas as palavras presentes na lista de palavras de um item da lista de letras
          gotoxy(1, y);
          printf("%c", 179);
          gotoxy(50, y);
          printf("%c", 179);
          gotoxy(2, y);
          cout << auxPalavras->palavra;
          auxPalavras = auxPalavras->proxPalavra;
          y = y + 1; // responsavel por "pular" uma linha
        }
        gotoxy(1, y);
        printf("%c", 192);
        gotoxy(50, y);
        printf("%c", 217);
        for (int i = 2; i <= 49; i++)
        {
          gotoxy(i, y);
          printf("%c", 196);
        }
      }
      y = y + 1;
      auxLetras = auxLetras->proxLetra; // responsavel por apontar para a proxima letra da lista de letras
    }
  }
  cout << endl;
  return y;
}

// metodo responsavel por exibir as letras, palavras e descrições (sem duvidas o mais complexo e complicado, maleavel)
void exibirPalavraeDescricao(ListaLetras *inicio, ListaLetras *fim, const char *frase)
{

  int y = 4;
  system("cls");
  if (inicio == NULL)
  {
    exibirMensagem("Nenhuma palavra cadastrada!"); // mensagem que será exibida em uma "caixa"
  }
  else
  {
    ListaLetras *auxLetras = inicio;

    gotoxy(26, 2);
    cout << frase;

    while (auxLetras != NULL)
    { // while responsavel pelo loop de letras ate que chegue a ultima letra dessa lista
      // Criação do "quadrado" de onde a exibição da letra vai ficar
      gotoxy(1, y);
      printf("%c", 218);
      for (int i = 2; i <= 60; i++)
      {
        gotoxy(i, y);
        printf("%c", 196);
      }
      gotoxy(61, y);
      printf("%c", 191);
      for (int j = y + 1; j <= y + 3; j++)
      {
        gotoxy(61, j);
        printf("%c", 179);
      }
      for (int j = y + 1; j <= y + 3; j++)
      {
        gotoxy(1, j);
        printf("%c", 179);
      }
      gotoxy(1, y + 4);
      printf("%c", 195);
      gotoxy(61, y + 4);
      printf("%c", 180);
      for (int i = 2; i <= 60; i++)
      {
        if (i == 31)
        {
          gotoxy(i, y + 4);
          printf("%c", 194);
        }
        else
        {
          gotoxy(i, y + 4);
          printf("%c", 196);
        }
      }
      gotoxy(23, y + 2);
      cout << "Letra " << auxLetras->letra << " - " << auxLetras->qtdPalavras;
      cout << " Palavras"; // exibir e posicionar a letra e quantidade de palavras dentro do quadrado
      y = y + 4;           // leva o "y" ate a linha inferior do quadrado
      if (auxLetras->inicioPalavras == NULL)
      {
        gotoxy(y, 15);
        cout << "Lista de Palavras Vazias";
        y = y + 1;
      }
      else
      {
        ListaPalavras *auxPalavras = auxLetras->inicioPalavras;
        while (auxPalavras != NULL)
        {             // while responsavel por criar o loop ate chegar ao fim da lista de palavras da letra atual da lista de letras
          int x = 32; // predefinicçao da posição x de descrição
          int yy = y; // variavel auxiliar para o a variavel y que representa a posição da vertical

          gotoxy(2, y + 1);
          cout << auxPalavras->palavra;
          y = y + 1;
          yy = y;

          // esse for é responsavel por "quebrar" a descrição a cada 28 caracteres, para caber dentro do quadrado de exibição
          for (int i = 0; i < 500 && auxPalavras->descricao[i] != '\0'; i++)
          {
            gotoxy(x, y);
            cout << auxPalavras->descricao[i];
            x++;
            if ((i + 1) % 29 == 0)
            { // responsavel por verificar se já chegou aos 29
              if ((auxPalavras->descricao[i] != ' '&&auxPalavras->descricao[i]!=',')&&(auxPalavras->descricao[i+1] != ' '&&auxPalavras->descricao[i+1]!=','))
              {
                gotoxy(x-1,y);cout<<"-";
                y++;
                x = 32;
                gotoxy(x,y);cout<< auxPalavras->descricao[i];
                x++;

              }
              else
              {
                y++;
                x = 32;
              }

            }
          }
          // variação das linhas do quadrado de acordo com a quantidade de vezes que a "quebra" da descrição aconteceu
          for (int i = yy; i <= y + 1; i++)
          {
            gotoxy(1, i);
            printf("%c", 179);
          }
          for (int i = yy; i <= y + 1; i++)
          {
            gotoxy(31, i);
            printf("%c", 179);
          }
          for (int i = yy; i <= y + 1; i++)
          {
            gotoxy(61, i);
            printf("%c", 179);
          }
          // goto que reescreve por cima da ultima linha escrita no while de palavra e descrição, para poder fechar o "quadrado"
          auxPalavras = auxPalavras->proxPalavra;
          y = y + 2;
          gotoxy(1, y);
          printf("%c", 195);
          gotoxy(61, y);
          printf("%c", 180);
          for (int i = 2; i <= 60; i++)
          {
            if (i == 31)
            {
              gotoxy(i, y);
              printf("%c", 197);
            }
            else
            {
              gotoxy(i, y);
              printf("%c", 196);
            }
          }
        }
        // goto que reescreve por cima da ultima linha escrita no while de palavra e descrição, para poder fechar o "quadrado"
        gotoxy(1, y);
        printf("%c", 192);
        gotoxy(61, y);
        printf("%c", 217);
        for (int i = 2; i <= 60; i++)
        {
          if (i == 31)
          {
            gotoxy(i, y);
            printf("%c", 193);
          }
          else
          {
            gotoxy(i, y);
            printf("%c", 196);
          }
        }
        y = y + 1;
      }
      auxLetras = auxLetras->proxLetra;
    }
  }

  cout << endl;
}

int contarSubstrings(const char *str, const char *substring)
{
  int count = 0;
  size_t substring_len = strlen(substring);
  size_t str_len = strlen(str);

  for (size_t i = 0; i <= str_len - substring_len; i++)
  {
    if (strncmp(str + i, substring, substring_len) == 0)
    {
      count++;
      i += substring_len - 1; // Pular a substring encontrada
    }
  }

  return count;
}

void exibirPorRelevancia(ListaLetras *inicio, ListaLetras *fim, char *palavra)
{
  if (validPalavra(palavra))
  {
    ListaLetras *auxLetras = inicio;
    ListaLetras *tempI = NULL, *tempF = NULL;

    while (auxLetras != NULL)
    {
      ListaPalavras *auxPalavras = auxLetras->inicioPalavras;

      while (auxPalavras != NULL)
      {
        auxPalavras->relevancia = contarSubstrings(auxPalavras->descricao, palavra);

        if (auxPalavras->relevancia != 0)
        {
          inserirPalavra(&tempI, &tempF, auxPalavras->palavra, auxPalavras->descricao);
          auxPalavras->relevancia = 0;
        }

        auxPalavras = auxPalavras->proxPalavra;
      }

      auxLetras = auxLetras->proxLetra;
    }

    exibirPalavraeDescricao(tempI, tempF, strupr(palavra));
    system("pause");

    // Limpar Memória
    auxLetras = tempI;

    while (auxLetras != NULL)
    {
      ListaPalavras *auxPalavras = auxLetras->inicioPalavras;
      ListaLetras *tempL = auxLetras->proxLetra;

      while (auxPalavras != NULL)
      {
        ListaPalavras *temp;
        temp = auxPalavras->proxPalavra;
        deletarPalavra(&tempI, &tempF, auxPalavras->palavra);
        auxPalavras = temp;
      }

      auxLetras = tempL;
    }
  }
  else
  {
    exibirMensagem("Palavra contem digito invalido");
  }
}

void menuExibir(ListaLetras *inicio, ListaLetras *fim)
{
  char menu = ' ';
  char palavra[MAX_PALAVRA];
  int y;

  while (menu != '0')
  {
    system("cls");
    quadro();
    gotoxy(42, 3);
    printf("%c", 191);
    for (int j = 4; j <= 9; j++)
    {
      gotoxy(3, j);
      printf("%c", 179);
    }
    for (int c = 4; c <= 9; c++)
    {
      gotoxy(42, c);
      printf("%c", 179);
    }
    gotoxy(3, 10);
    printf("%c", 192);
    gotoxy(42, 10);
    printf("%c", 217);
    for (int k = 4; k <= 41; k++)
    {
      gotoxy(k, 10);
      printf("%c", 196);
    }
    gotoxy(3, 3);
    printf("%c", 218);
    for (int i = 4; i <= 41; i++)
    {
      gotoxy(i, 3);
      printf("%c", 196);
    }
    gotoxy(15, 2);
    cout << "MENU DE PESQUISA";
    gotoxy(5, 5);
    cout << "[1] - Pesquisar por palavra   ";
    gotoxy(5, 6);
    cout << "[2] - Pesquisar por relevancia";
    gotoxy(5, 7);
    cout << "[0] - Voltar ao menu principal";
    gotoxy(5, 8);
    cout << "Selecione a opcao: ";
    cin >> menu;
    cin.ignore();

    switch (menu)
    {
    case '1':
      y = exibirApenasPalavra(inicio, fim, "Pesquisa por Palavra");
      gotoxy(3, y + 1);
      printf("%c", 254);
      cout << "Informe a palavra que deseja buscar: ";
      cin.getline(palavra, MAX_PALAVRA);

      if (validPalavra(palavra))
      {
        ListaLetras *letra = buscarLetra(inicio, fim, toupper(palavra[0]));

        if (letra == NULL)
        {
          exibirMensagem("Palavra nao encontrada");
        }
        else
        {
          ListaPalavras *aux = letra->inicioPalavras;

          if (aux == NULL)
          {
            exibirMensagem("Lista de palavras vazia");
          }
          else
          {
            while (aux != NULL)
            {
              if (aux->proxPalavra == NULL && strcmp(aux->palavra, strupr(palavra)) != 0)
              {
                exibirMensagem("Palavra nao encontrada");
              }
              else if (strcmp(aux->palavra, strupr(palavra)) == 0)
              {

                ListaLetras *tempI = NULL, *tempF = NULL;
                inserirPalavra(&tempI, &tempF, aux->palavra, aux->descricao);
                exibirPalavraeDescricao(tempI, tempF, palavra);
                system("pause");
                deletarPalavra(&tempI, &tempF, aux->palavra);

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

// Método recebe uma lista de letras, um ponteiro de um nó de uma palavra, uma nova palavra e descrição para atualizar
void atualizarPalavra(ListaLetras **inicio,
                      ListaLetras **fim,
                      ListaPalavras *palavra,
                      char *novaPalavra,
                      char *novaDescricao)
{

  novaPalavra = strupr(novaPalavra);
  novaDescricao[0] = toupper(novaDescricao[0]);

  // Verifica se a nova palavra é válida
  if (validPalavra(novaPalavra))
  {
    // Verifica se a primeira letra da palavra atual e da nova palavra são iguais
    if (palavra->palavra[0] == novaPalavra[0])
    {
      // Apenas atribui os novos valores ao nó passado como parâmetro
      strcpy(palavra->palavra, novaPalavra);
      strcpy(palavra->descricao, novaDescricao);
    } // Se a primeira letra das palavras forem diferentes
    else
    {
      deletarPalavra(inicio, fim, palavra->palavra);           // Deleta a palavra de sua lista
      inserirPalavra(inicio, fim, novaPalavra, novaDescricao); // Insere a nova palavra em uma outra lista
    }

    // salvarArquivo(*inicio, *fim); // As alterações são salvas no arquivo
  }
  else
  {
    // inserirErro();
  }
}

// Método transfere o conteúdo de um arquivo de texto para a memória do computador
void carregarArquivo(ListaLetras **inicio, ListaLetras **fim)
{
  FILE *arq;
  arq = fopen(DICIONARIO, "r");

  cout << "carregando arquivos" << endl;

  if (arq == NULL)
  {
    cout << "Erro ao abrir o arquivo" << endl;
  }
  else
  {
    char linha[MAX_PALAVRA + MAX_DESCRICAO + 2];

    while (fgets(linha, sizeof(linha), arq) != NULL)
    {
      // quebra a string fonte em duas partes, separadas pelo caracter de /
      char *palavra = strtok(linha, "/");
      char *descricao = strtok(NULL, "/");

      if (palavra && descricao)
      {
        // Remove caracteres de quebra de linha, se houver
        palavra = strtok(palavra, "\n");
        descricao = strtok(descricao, "\n");

        inserirPalavra(inicio, fim, palavra, descricao); // insere a palavra na lista
      }
      else
      {
        cout << "Erro ao processar linha: " << linha << endl;
      }
    }
  }

  fclose(arq);
}

void ordenarListaPalavras(ListaPalavras **inicio)
{
  ListaPalavras *atual = *inicio;
  ListaPalavras *novaLista = NULL;

  while (atual != NULL)
  {
    ListaPalavras *min = atual;
    ListaPalavras *temp = atual;

    while (temp != NULL)
    {
      if (strcmp(temp->palavra, min->palavra) < 0)
      {
        min = temp;
      }
      temp = temp->proxPalavra;
    }

    // Remove o nó mínimo da lista atual
    if (min == atual)
    {
      *inicio = min->proxPalavra;
    }
    else
    {
      temp = *inicio;
      while (temp->proxPalavra != min)
      {
        temp = temp->proxPalavra;
      }
      temp->proxPalavra = min->proxPalavra;
    }

    // Adiciona o nó mínimo à nova lista
    min->proxPalavra = NULL;
    if (novaLista == NULL)
    {
      novaLista = min;
    }
    else
    {
      temp = novaLista;
      while (temp->proxPalavra != NULL)
      {
        temp = temp->proxPalavra;
      }
      temp->proxPalavra = min;
    }

    atual = *inicio;
  }

  *inicio = novaLista;
}

void ordenarListaLetras(ListaLetras **inicio)
{
  ListaLetras *listaOrdenada = NULL;

  while (*inicio != NULL)
  {
    ListaLetras *min = *inicio;
    ListaLetras *temp = *inicio;

    while (temp != NULL)
    {
      if (temp->letra < min->letra)
      {
        min = temp;
      }

      temp = temp->proxLetra;
    }

    // Remove o nó mínimo da lista atual
    if (min == *inicio)
    {
      *inicio = min->proxLetra;
      if (*inicio)
        (*inicio)->antLetra = NULL;
    }
    else
    {
      min->antLetra->proxLetra = min->proxLetra;
      if (min->proxLetra)
        min->proxLetra->antLetra = min->antLetra;
    }

    // Adiciona o nó mínimo à nova lista
    min->antLetra = NULL;
    min->proxLetra = NULL;

    if (listaOrdenada == NULL)
    {
      listaOrdenada = min;
    }
    else
    {
      ListaLetras *temp = listaOrdenada;

      while (temp->proxLetra != NULL)
      {
        temp = temp->proxLetra;
      }

      temp->proxLetra = min;
      min->antLetra = temp;
    }

    ordenarListaPalavras(&(min->inicioPalavras));
  }

  *inicio = listaOrdenada;
}

int main()
{
  ListaLetras *inicio = NULL;
  ListaLetras *fim = NULL;
  char palavra[MAX_PALAVRA], descricao[MAX_DESCRICAO], opcao = ' ', menu = '!';
  int y = 0;

  carregarArquivo(&inicio, &fim);

  while (menu != '0')
  {
    system("cls");
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
    cout << "[6] - Exibir Dicionario " << endl;
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
      salvarArquivo(inicio, fim);
      system("cls");

      break;
    case '2':
      menuExibir(inicio, fim);

      break;
    case '3':
      // int y;
      system("cls");
      // listarDicionario(inicio, fim);
      y = exibirApenasPalavra(inicio, fim, "DELETAR");
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
      gotoxy(1, y + 1);
      printf("%c", 254);
      gotoxy(3, y + 1);
      cout << "Informe a palavra: ";
      cin.getline(palavra, MAX_PALAVRA);
      deletarPalavra(&inicio, &fim, palavra);
      salvarArquivo(inicio, fim);
      exibirMensagem("Palavra Deletada");
      system("cls");
      break;
    case '4':
      system("cls");
      // int l=0;
      y = exibirApenasPalavra(inicio, fim, "Atualizar");
      gotoxy(2, y);
      cout << "Informe a palavra que deseja atualizar: ";
      cin.getline(palavra, MAX_PALAVRA);
      system("cls");
      if (validPalavra(palavra))
      {
        ListaPalavras *palavraEncontrada = buscarPalavra(buscarLetra(inicio, fim, palavra[0]), strupr(palavra));

        if (palavraEncontrada != NULL)
        {
          char novaPalavra[MAX_PALAVRA];
          for (int j = 1; j <= 2; j++)
          {
            gotoxy(0, j);
            printf("%c", 179);
          }
          gotoxy(1, 1);
          printf("%c ", 254);
          cout << "Palavra atual: " << palavraEncontrada->palavra << endl;
          gotoxy(1, 2);
          printf("%c ", 254);
          cout << "Nova palavra: ";
          cin.getline(novaPalavra, MAX_PALAVRA);
          gotoxy(0, 3);
          printf("%c", 179);
          gotoxy(1, 3);
          printf("%c ", 254);
          cout << "Descricao: " << palavraEncontrada->descricao << "\n\n";
          cout << "Deseja atualizar a descricao de " << novaPalavra << "? [S/N]" << endl;
          cout << "Digite a opcao: ";
          cin >> opcao;
          cin.ignore();

          if (opcao == 'S' || opcao == 's')
          {
            system("cls");
            for (int j = 1; j <= 2; j++)
            {
              gotoxy(0, j);
              printf("%c", 179);
            }
            gotoxy(1, 1);
            printf("%c ", 254);
            cout << "Palavra: " << novaPalavra << endl;
            gotoxy(1, 2);
            printf("%c ", 254);
            cout << "Informe a nova descricao: ";
            cin.getline(descricao, MAX_DESCRICAO);
            atualizarPalavra(&inicio, &fim, palavraEncontrada, novaPalavra, descricao);
            exibirMensagem("Palavra e Descricao Atualizada");
          }
          else if (opcao == 'N' || opcao == 'n')
          {
            atualizarPalavra(&inicio, &fim, palavraEncontrada, novaPalavra, palavraEncontrada->descricao);
            salvarArquivo(inicio, fim);
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
      ordenarListaLetras(&inicio);
      salvarArquivo(inicio, fim);
      // listarDicionario(inicio, fim);
      exibirPalavraeDescricao(inicio, fim, "Dicionario ordenado");
      system("pause");
      exibirMensagem("Palavras ordenadas alfabeticamente com sucesso!");
      system("cls");
      break;
    case '6':
      exibirPalavraeDescricao(inicio, fim, "DICIONARIO");
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
