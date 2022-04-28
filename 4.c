#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define W_SIDE 10

typedef struct
{
    int hp;
} Character;

typedef struct
{
    int hp;
} King;

void printMap(char map[][W_SIDE])
{
    for (int i = 0; i < W_SIDE; i++)
    {
        for (int j = 0; j < W_SIDE; j++)
        {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

void insertMap(char map[][W_SIDE], char entity, int qt)
{
    for (int i = 0; i < qt;)
    {
        int x = rand() % W_SIDE;
        int y = rand() % W_SIDE;

        if (map[x][y] == '_')
        {
            map[x][y] = entity;
            i++;
        }
    }
}

int isEmpty(int x, int y, char map[][W_SIDE])
{
    if (map[x][y] == '_')
    {
        return 1;
    }
    return 0;
}

/*
Funcao que checa se o movimento e possivel e altera os valores caso sim
Essa funcao retorna a posicao que o personagem tentou acessar
Apesar dessa funcao possuir duas funcionalidades, achamos que valia a pena
manter dessa forma para economizar linhas de código
*/

char handleDirection(int *x, int *y, char dir, char map[][W_SIDE])
{
    switch (dir)
    {
    case 'w':
        if (*x - 1 >= 0 && isEmpty(*x - 1, *y, map) == 1)
        {
            map[*x][*y] = '_';
            *x = *x - 1;
            return map[*x][*y];
        }
        else
        {
            return map[*x - 1][*y];
        }
        break;
    case 'a':
        if (*y - 1 >= 0 && isEmpty(*x, *y - 1, map) == 1)
        {
            map[*x][*y] = '_';
            *y = *y - 1;
            return map[*x][*y];
        }
        else
        {
            return map[*x][*y - 1];
        }

        break;
    case 's':
        if (*x + 1 < W_SIDE && isEmpty(*x + 1, *y, map) == 1)
        {
            map[*x][*y] = '_';
            *x = *x + 1;
            return map[*x][*y];
        }
        else
        {
            return map[*x + 1][*y];
        }
        break;
    case 'd':
        if (*y + 1 < W_SIDE && isEmpty(*x, *y + 1, map) == 1)
        {
            map[*x][*y] = '_';
            *y = *y + 1;
            return map[*x][*y];
        }
        else
        {
            return map[*x][*y + 1];
        }
        break;
    }
}

void removeEntity(char map[][W_SIDE], int x, int y, char dir)
{
    switch (dir)
    {
    case 'w':
        map[x - 1][y] = '_';
        break;
    case 'a':
        map[x][y - 1] = '_';
        break;
    case 's':
        map[x + 1][y] = '_';
        break;
    case 'd':
        map[x][y + 1] = '_';
        break;
    }
}

void warWithCersei()
{
    printf("Implementar guerra\n");
}

void warWithNightKing()
{
    printf("Implementar guerra\n");
}

int main()
{
    srand(time(NULL));
    char westeros[W_SIDE][W_SIDE];
    Character jon_snow, cersei;
    King night_king;

    // Inicia o mapa de westeros
    for (int i = 0; i < W_SIDE; i++)
    {
        for (int j = 0; j < W_SIDE; j++)
        {
            westeros[i][j] = '_';
        }
    }

    // Posicionamentos iniciais
    westeros[0][0] = 'W';
    westeros[4][4] = 'C';
    westeros[9][9] = 'N';
    westeros[0][1] = 'J'; // ?
    int jon_x = 0, jon_y = 1;
    jon_snow.hp = 100;
    cersei.hp = 100;
    night_king.hp = 200;

    // Populando o mapa com as entidades
    insertMap(westeros, 'I', 20);
    insertMap(westeros, 'O', 10);
    insertMap(westeros, 'P', 10);

    char direction;
    char tried_pos;
    int negotiating_power, score = 0, try = 0;
    int met_cersei = 0;
    while (jon_snow.hp > 0)
    {
        printMap(westeros);
        printf("Vida: %d\n", jon_snow.hp);

        printf(">> ");
        scanf("%c", &direction);
        getchar();

        tried_pos = handleDirection(&jon_x, &jon_y, direction, westeros);
        westeros[jon_x][jon_y] = 'J';
        switch (tried_pos)
        {
        case 'W':
            printf("Voce nao pode voltar para winterfell\n");
            break;
        case 'C':
            printf("Negociando com Cersei...\n");
            int negotiating_power = rand() % 101;
            printf("Taxa de negociacao: %d/100\n", negotiating_power);

            if (negotiating_power >= 60)
            {
                score++;
                printf("Voce agora tem %d ponto(s)\n", score);
            }
            else
            {
                printf("Voce tem %d tentativa(s) restante(s)\n", 4 - try);
            }

            try++;

            if (score == 3 && try <= 5)
            {
                jon_snow.hp += 100;
                printf("Cersei se uniu a voce\n");
                westeros[4][4] = '_';
                met_cersei = 1;
            }
            else if (score < 3 && try >= 5)
            {
                warWithCersei();
                westeros[4][4] = '_';
                met_cersei = 1;
            }
            break;
        case 'N':
            if (met_cersei == 0)
            {
                printf("Voce nao pode enfrentar o rei da noite antes de se encontrar com Cersei\n");
            }
            else
            {
                warWithNightKing();
            }
            break;
        case 'P':
            removeEntity(westeros, jon_x, jon_y, direction);

            if (jon_snow.hp <= 95)
            {
                jon_snow.hp += 5;
            }
            else if (jon_snow.hp + 5 >= 100)
            {
                jon_snow.hp = 100;
            }
            break;
        case 'I':
            removeEntity(westeros, jon_x, jon_y, direction);
            jon_snow.hp -= 1;
            break;
        }
    }

    if (jon_snow.hp == 0)
    {
        printf("Character Snow morreu. Tente novamente.\n");
    }

    return 0;
}
