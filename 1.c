#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char tabuleiro[8][8];

int torre(int lp, int la, int cp, int ca)
{
    if (lp == la || cp == ca)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int peao(int lp, int la, int cp, int ca)
{
    if (lp == la + 1 || lp == la - 1)
    {
        if (cp == ca + 1 || cp == ca - 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int cavalo(int lp, int la, int cp, int ca)
{
    if (((lp == la + 1 && cp == ca + 2 || lp == la + 1 && cp == ca - 2) || (lp == la + 2 && cp == ca + 1 || lp == la + 2 && cp == ca - 1)) || ((lp == la - 1 && cp == ca - 2 || lp == la - 1 && cp == ca + 2) || (lp == la - 2 && cp == ca - 1 || lp == la - 2 && cp == ca + 1)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int bispo(int lp, int la, int cp, int ca)
{
    int eat;

    for (int i = lp + 1, j = cp + 1; i < 8 && j < 8; i++, j++)
    { // Diagonal pra cima - Direita
        if (i == la && j == ca)
        {
            eat = 1;
        }
    }

    for (int i = lp - 1, j = cp + 1; i >= 0 && j < 8; i--, j++)
    { // Diagonal pra baixo- Direita
        if (i == la && j == ca)
        {
            eat = 1;
        }
    }

    for (int i = lp + 1, j = cp - 1; i < 8 && j >= 0; i++, j--)
    { // Diagonal pra cima - Esquerda
        if (i == la && j == ca)
        {
            eat = 1;
        }
    }

    for (int i = lp - 1, j = cp - 1; i >= 0 && j >= 0; i--, j--)
    { // Diagonal pra baixo - Esquerda
        if (i == la && j == ca)
        {
            eat = 1;
        }
    }

    if (eat == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int rainha(int lp, int la, int cp, int ca)
{
    int eat;

    if (lp == la || cp == ca)
    {
        eat = 1;
    }
    else
    {
        eat = 1;
    }

    for (int i = lp + 1, j = cp + 1; i < 8 && j < 8; i++, j++)
    { // Diagonal pra cima - Direita
        if (i == la && j == ca)
        {
            eat = 1;
        }
    }

    for (int i = lp - 1, j = cp + 1; i >= 0 && j < 8; i--, j++)
    { // Diagonal pra baixo- Direita
        if (i == la && j == ca)
        {
            eat = 1;
        }
    }

    for (int i = lp + 1, j = cp - 1; i < 8 && j >= 0; i++, j--)
    { // Diagonal pra cima - Esquerda
        if (i == la && j == ca)
        {
            eat = 1;
        }
    }

    for (int i = lp - 1, j = cp - 1; i >= 0 && j >= 0; i--, j--)
    { // Diagonal pra baixo - Esquerda
        if (i == la && j == ca)
        {
            eat = 1;
        }
    }

    if (eat == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int rei(int lp, int la, int cp, int ca)
{
    if ((lp == la && cp == ca + 1 || lp == la && cp == ca - 1) || (lp == la + 1 && cp == ca || lp == la - 1 && cp == ca) || (lp == la + 1 && cp == ca + 1 || lp == la + 1 && cp == ca - 1) || (lp == la - 1 && cp == ca + 1 || lp == la - 1 && cp == ca - 1))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void main(void)
{
    srand(time(NULL));

    char p1, p2, r;
    unsigned int l1, c1, l2, c2;
    int t, i;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            tabuleiro[i][j] = '-';
        }
    }

    for (t = 0; t < 8; ++t)
    {

        for (i = 0; i < 8; ++i)
        {
            printf("%3c", tabuleiro[t][i]);
        }

        printf("\n");
    }

    printf("\nLegenda:\nT - Torre\nC - Cavalo\nB - Bispo\nr - Rainha\nR - Rei\nP - Peao\n");

    printf("Digite a primeira a peca que deseja colocar:  ");
    scanf("%c", &p1);
    getchar();

    printf("Digite a segunda a peca que deseja colocar:  ");
    scanf("%c", &p2);
    getchar();

    l1 = rand() % 8;
    c1 = rand() % 8;

    tabuleiro[l1][c1] = p1;

    l2 = rand() % 8;
    c2 = rand() % 8;

    tabuleiro[l2][c2] = p2;

    system("cls");

    for (t = 0; t < 8; ++t)
    {

        for (i = 0; i < 8; ++i)
        {
            printf("%3c", tabuleiro[t][i]);
        }

        printf("\n");
    }

    printf("A peca 1 eh a %c e:\n", p1);
    switch (p1)
    {
    case 'T':
        r = torre(l1, l2, c1, c2);
        if (r == 1)
        {
            printf("E possivel comer em um movimento com a Torre.");
        }
        else
        {
            printf("Nao e possivel comer em um movimento com a Torre.");
        }
        break;

    case 'P':
        r = peao(l1, l2, c1, c2);
        if (r == 1)
        {
            printf("E possivel comer em um movimento com a Peao.");
        }
        else
        {
            printf("Nao e possivel comer em um movimento com a Peao.");
        }
        break;

    case 'C':
        r = cavalo(l1, l2, c1, c2);
        if (r == 1)
        {
            printf("E possivel comer em um movimento com a Cavalo.");
        }
        else
        {
            printf("Nao e possivel comer em um movimento com a Cavalo.");
        }
        break;

    case 'B':
        r = bispo(l1, l2, c1, c2);
        if (r == 1)
        {
            printf("E possivel comer em um movimento com a Bispo.");
        }
        else
        {
            printf("Nao e possivel comer em um movimento com a Bispo.");
        }
        break;

    case 'R':
        r = rei(l1, l2, c1, c2);
        if (r == 1)
        {
            printf("E possivel comer em um movimento com o Rei.");
        }
        else
        {
            printf("Nao e possivel comer em um movimento com o Rei.");
        }
        break;

    case 'r':
        r = rainha(l1, l2, c1, c2);
        if (r == 1)
        {
            printf("E possivel comer em um movimento com a Rainha.");
        }
        else
        {
            printf("Nao e possivel comer em um movimento com a Rainha.");
        }
        break;
    }

    printf("A peca 2 eh a %c e:\n", p1);
    switch (p2)
    {
    case 'T':
        r = torre(l2, l1, c2, c1);
        if (r == 1)
        {
            printf("E possivel comer em um movimento com a Torre.");
        }
        else
        {
            printf("Nao e possivel comer em um movimento com a Torre.");
        }
        break;

    case 'P':
        r = peao(l2, l1, c2, c1);
        if (r == 1)
        {
            printf("E possivel comer em um movimento com a Peao.");
        }
        else
        {
            printf("Nao e possivel comer em um movimento com a Peao.");
        }
        break;

    case 'C':
        r = cavalo(l2, l1, c2, c1);
        if (r == 1)
        {
            printf("E possivel comer em um movimento com a Cavalo.");
        }
        else
        {
            printf("Nao e possivel comer em um movimento com a Cavalo.");
        }
        break;

    case 'B':
        r = bispo(l2, l1, c2, c1);
        if (r == 1)
        {
            printf("E possivel comer em um movimento com a Bispo.");
        }
        else
        {
            printf("Nao e possivel comer em um movimento com a Bispo.");
        }
        break;

    case 'R':
        r = rei(l2, l1, c2, c1);
        if (r == 1)
        {
            printf("E possivel comer em um movimento com o Rei.");
        }
        else
        {
            printf("Nao e possivel comer em um movimento com o Rei.");
        }
        break;

    case 'r':
        r = rainha(l2, l1, c2, c1);
        if (r == 1)
        {
            printf("E possivel comer em um movimento com a Rainha.");
        }
        else
        {
            printf("Nao e possivel comer em um movimento com a Rainha.");
        }
        break;
    }
}