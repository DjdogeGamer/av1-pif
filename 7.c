#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void preencherMatriz(int tam, char vetor[tam][tam])
{
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            vetor[i][j] = 'L';
        }
    }
}

void matrizAssento(int tam, int vetor[tam][tam])
{
    int num = 1;
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            vetor[i][j] = num;
            num++;
        }
    }
}

void printarMatriz(int tam, char vetor[tam][tam])
{
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            printf("%c ", vetor[i][j]);
        }

        printf("\n");
    }
}

void printarMatrizInt(int tam, int vetor[tam][tam])
{
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            printf("%d ", vetor[i][j]);
        }

        printf("\n");
    }
}

int verificarVagas(int tam, char vetor[tam][tam])
{
    int vagas = 0;
    for (int i = 0; i <= tam + 1; i++)
    {
        for (int j = 0; j <= tam + 1; j++)
        {
            if (vetor[i][j] == 'L')
            {
                vagas++;
            }
        }
    }
    if (vagas > 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

typedef struct
{
    int posX;
    int posY;
} Lugar;

Lugar escolherLugar(int tam, char vetor[tam][tam], Lugar lugar)
{
    int posL;
    int posC;
    do
    {
        printf("\nDigite o assento que deseja selecionar: ");
        scanf("%d %d", &posL, &posC);
        if (vetor[posL][posC] == 'L')
        {
            lugar.posX = posL;
            lugar.posY = posC;
            vetor[posL][posC] = 'X';
            break;
        }
        else
        {
            printf("Lugar nao esta livre selecione outro");
        }

    } while (1);

    return lugar;
}

typedef struct
{
    char nome_filme[30];
    char id[20];
    char categoria[20];
    int entrada;
    int assento;
    double valor;
} Compra;

void meiaInteira(int m, int inte, int tam, Compra compra[tam])
{
    for (int i = 0; i < tam; i++)
    {
        if (compra[i].entrada == 1)
        {
            m++;
        }
        else
        {
            inte++;
        }
    }
    printf("Total de meias e inteiras:\nmeia: %d\ninteira: %d\n", m, inte);
    printf("-----------------------------------\n");
}

void registrarCompra(Compra compra, int ind, Compra compras[ind])
{

    compras[ind] = compra;
}

void printarCompra(char filme[], char categoria[], Compra compra)
{
    printf("-----------------------------------\n");
    printf("nome do filme: %s\n", filme);
    printf("categoria: %s\n", categoria);
    printf("CPF: %s\n", compra.id);
    printf("Entrada( 1= meia, 2= inteira): %d\n\n", compra.entrada);
    printf("Numero do assento: %d\n\n", compra.assento);
    printf("Valor do ingresso: R$%.2lf\n\n", compra.valor);
    printf("-----------------------------------\n");
}

void printarCompras(char filme[], char categoria[], int tam, Compra compras[tam])
{
    for (int i = 0; i < tam; i++)
    {
        printf("-----------------------------------\n");
        printf("Compra de numero %d\n", i + 1);
        printf("nome do filme: %s\n", filme);
        printf("categoria: %s\n", categoria);
        printf("CPF: %s\n", compras[i].id);
        printf("Entrada( 1= meia, 2= inteira): %d\n\n", compras[i].entrada);
        printf("Numero do assento: %d\n\n", compras[i].assento);
        printf("Valor do ingresso: R$%.2lf\n\n", compras[i].valor);
        printf("-----------------------------------\n");
    }
}

int main(int argc, char const *argv[])
{
    Lugar lugar;
    int tam =  2;
    char vetor[tam][tam];
    int vetor_int[tam][tam];
    int tamCompras = (tam * 2);

    Compra compras[tamCompras], compra;

    preencherMatriz(tam, vetor);
    matrizAssento(tam, vetor_int);

    int indice = 0;
    int vagas = -1;

    char filme[30];
    char categoria[20];

    printf("\n\t== CINEMA CESAR ==\n");
    printf("\n|A sessao prime sera aberta!!| \n   digite o nome do filme: ");
    fgets(filme, 30, stdin);
    printf("   Digite a categoria do filme: ");
    fgets(categoria, 20, stdin);

    do
    {
        Compra compra = {0};

        printf("\n");
        printarMatriz(tam, vetor);

        setbuf(stdin, 0);
        lugar = escolherLugar(tam, vetor, lugar);

        setbuf(stdin, 0);
        printf(" Digite seu cpf: ");
        fgets(compra.id, 20, stdin);

        setbuf(stdin, 0);
        printf(" Meia(1) ou Inteira(2): ");
        scanf("%d", &compra.entrada);

        if (compra.entrada == 1)
        {
            compra.valor = 10.0;
        }
        else
        {
            compra.valor = 20.0;
        }

        compra.assento = vetor_int[lugar.posX][lugar.posY];

        printf("\nCompra Registrada!!!\n\n");

        printarCompra(filme, categoria, compra);

        registrarCompra(compra, indice, compras);
        indice++;

        vagas = verificarVagas(tam, vetor);
    } while (vagas == 1);

    printf("Vagas completas\n");
    printf("REGISTRO DO DIA: \n");

    printarCompras(filme, categoria, tamCompras, compras);
    int meia = 0, inteira = 0;
    meiaInteira(meia, inteira, tamCompras, compras);

    return 0;
}
