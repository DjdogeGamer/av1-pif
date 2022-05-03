#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct
{
    int hp;
    int pos;
} Character;

// prof, se der erro é pela IDE, que não suporta cores. Testar pelo VSCODE, todos que testamos funcionou :3
void blue()
{ // usar a cor no print
    printf("\033[1;34m");
}

void green()
{ // usar a cor no print
    printf("\033[1;32m");
}

void yellow()
{
    printf("\033[1;33m");
}

void white()
{
    printf("\033[1;37m");
}

void black()
{
    printf("\033[1;30m");
}

void red()
{
    printf("\033[1;31m");
}

// cor Player1
void cyan()
{
    printf("\033[1;36m");
}
// cor Player1
void purple()
{
    printf("\033[1;35m");
}

void reset()
{ // resetar a cor
    printf("\033[0m");
}

int rollDices()
{
    return rand() % 6 + 1;
}

void insertCases(int tam, char tab[tam])
{
    tab[0] = 'S';
    tab[1] = 'W';
    tab[2] = 'R';
    tab[3] = 'G';
    tab[4] = 'W';
    tab[5] = 'B';
    tab[6] = 'W';
    tab[7] = 'Y';
    tab[8] = 'W';
    tab[9] = 'R';

    tab[10] = 'G';
    tab[11] = 'b';
    tab[12] = 'B';
    tab[13] = 'W';
    tab[14] = 'W';
    tab[15] = 'R';

    tab[16] = 'G';
    tab[17] = 'W';
    tab[18] = 'Y';
    tab[19] = 'W';
    tab[20] = 'R';
    tab[21] = 'G';
    tab[22] = 'W';
    tab[23] = 'B';
    tab[24] = 'R';

    tab[25] = 'Y';
    tab[26] = 'G';
    tab[27] = 'E';
}

void printMatrix(char matrix[7][10])
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            switch (matrix[i][j])
            {
            case 'W':
                white(); // cor da posicao
                printf("|_| ");
                reset();
                break;

            case 'R':
                red();
                printf("|_| ");
                reset();
                break;

            case 'Y':
                yellow();
                printf("|_| ", matrix[i][j]);
                reset();
                break;

            case 'G':
                green();
                printf("|_| ", matrix[i][j]);
                reset();
                break;

            case 'B':
                blue();
                printf("|_| ", matrix[i][j]);
                reset();
                break;

            case 'b':
                black();
                printf("|_| ", matrix[i][j]);
                reset();
                break;

            case 'S':
                black();
                printf("|_| ", matrix[i][j]);
                reset();
                break;

            case 'E':
                black();
                printf("|_| ", matrix[i][j]);
                reset();
                break;

            case '1':
                cyan();
                printf("|%c| ", matrix[i][j]);
                reset();
                break;
            case '2':
                purple();
                printf("|%c| ", matrix[i][j]);
                reset();
                break;
            case '3':
                printf("\033[1;37m"); // branco em negrito
                printf("|%c| ", matrix[i][j]);
                reset();
                break;
            default:
                printf(" %c  ", matrix[i][j]);
                break;
            }
        }
        printf("\n");
    }
}

void fillMatrix(char tabuleiro[])
{
    char matrix[7][10];

    // Preenche matriz como nula
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            matrix[i][j] = ' ';
        }
    }

    for (int i = 0; i < 10; i++)
    {
        matrix[0][i] = tabuleiro[i];
    }
    for (int i = 1; i < 7; i++)
    {
        matrix[i][9] = tabuleiro[9 + i];
    }
    for (int i = 0; i < 9; i++)
    {
        matrix[6][i] = tabuleiro[24 - i];
    }

    for (int i = 0; i < 3; i++)
    {
        matrix[3 + i][0] = tabuleiro[27 - i];
    }

    printMatrix(matrix);
}

void updateValues(int tam, char tab[tam], int pos1, int pos2)
{
    char aux_array[tam];

    for (int i = 0; i <= tam; i++)
    {
        if (i == pos1 && pos1 == pos2)
        {
            aux_array[i] = '3';
        }
        else if (i == pos1)
        {
            aux_array[i] = '1';
        }
        else if (i == pos2)
        {
            aux_array[i] = '2';
        }
        else
        {
            aux_array[i] = tab[i];
        }
    }

    fillMatrix(aux_array);
}

int main()
{
    int tam = 27;
    char board[tam];
    char matrix[7][10];

    insertCases(tam, board);

    srand(time(NULL));

    updateValues(tam, board, NULL, NULL);

    Character p1, p2;
    p1.hp = 10;
    p1.pos = 0;
    p2.hp = 10;
    p2.pos = 0;

    int tried_pos;

    // implementar quem começa primeiro
    int p1_wins = 0;
    int p2_wins = 0;
    int value1;
    int value2;

    do
    { // pegar quem vai ser o primeiro
        sleep(1);
        value1 = rollDices() + rollDices();
        printf("Dados Player1: %d\n", value1);

        sleep(1);
        value2 = rollDices() + rollDices();
        printf("Dados Player2: %d\n", value2);
        if (value1 == value2)
        {
            printf("Deu igual, rodando mais uma vez...\n");
        }
    } while (value1 == value2);

    int temp;
    if (value1 > value2)
    {
        temp = 0;
        printf("\n |Player1 INICIA|\n");
    }
    else
    {
        temp = 1;
        printf("\n |Player2 INICIA|\n");
    }

    while (p1_wins != 1 && p2_wins != 1)
    {
        temp++;
        system("pause");
        Character *p;

        if (temp % 2 == 1)
        {
            p = &p1;
            printf("\nPlayer 1: \n");
        }
        else
        {
            p = &p2;
            printf("\nPlayer 2: \n");
        }

        tried_pos = rollDices();
        p->pos = p->pos + tried_pos;
        // printf("= %d =\n", p->pos);

        if (p->pos > 27)
        {
            p->pos = 27;
        }

        switch (board[p->pos]) // implementar no "geral"
        {
        case 'W':
            break;

        case 'R':
            p->hp -= 3;
            break;

        case 'G':
            if ((p->hp += 1) >= 10)
            {
                p->hp = 10;
            }
            else
            {
                p->hp += 1;
            }
            break;
        case 'Y': // mudar
            temp -= 2;
            break;

        case 'B': // mudar
            temp++;
            break;
        case 'b':
            p->pos = 1;
            // printf("= %d =\n", p->pos); saber a posicao
            break;
        case 'E':
            // printf("\nFim de jogo!\n"); saber a posicao
            break;
        }

        if (p1.pos >= 27 || p2.hp == 0)
        {
            p1_wins = 1;
        }
        else if (p2.pos >= 27 || p1.hp == 0)
        {
            p2_wins = 1;
        }

        updateValues(tam, board, p1.pos, p2.pos);
        printf("DADO: %d\n\n", tried_pos);
        printf(" |Vida P1: %d\n", p1.hp);
        printf(" |Vida P2: %d\n", p2.hp);
    }

    if (p1_wins == 1)
    {
        printf("\n\t| PLAYER1 GANHOU!! |\n");
    }
    else if (p2_wins == 1)
    {
        printf("\n\t| PLAYER2 GANHOU!! |\n");
    }

    return 0;
}