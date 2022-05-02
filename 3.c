#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct
{
    int hp;
} Character;

// definicoes de funções para Sala

void printMap(int tam, char map[][tam])
{
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            if (map[i][j] != 'D')
            {
                printf("%c ", map[i][j]);
            }
            else
            {
                printf("_ ");
            }
        }
        printf("\n");
    }
}

void insertMap(int tam, char map[][tam], char entity, int qt)
{
    for (int i = 0; i < qt;)
    {
        int x = rand() % tam;
        int y = rand() % tam;

        if (map[x][y] == '_')
        {
            map[x][y] = entity;
            i++;
        }
    }
}

int isEmpty(int x, int y, int tam, char map[][tam])
{
    if (map[x][y] == '_')
    {
        return 1;
    }
    return 0;
}

char handleDirection(int *x, int *y, char dir, int tam, char map[][tam])
{
    switch (dir)
    {
    case 'w':
        if (*x - 1 >= 0 && isEmpty(*x - 1, *y, tam, map) == 1)
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
        if (*y - 1 >= 0 && isEmpty(*x, *y - 1, tam, map) == 1)
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
        if (*x + 1 < tam && isEmpty(*x + 1, *y, tam, map) == 1)
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
        if (*y + 1 < tam && isEmpty(*x, *y + 1, tam, map) == 1)
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

void removeEntity(int tam, char map[][tam], int x, int y, char dir)
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

int createPortal(Character *eleven)
{
    int rage_power;
    printf("Tentando criar Portal...\n");

    while (rage_power <= 0 || eleven->hp > 0)
    {
        rage_power = rand() % 101;

        if (rage_power < 60) // player1 - Jon Snow
        {
            printf(" Eleven nao conseguiu criar o Portal!\n");
            eleven->hp = eleven->hp - 20;

            if (eleven->hp <= 0)
            {
                printf("|Eleven morreu tentando criar o Portal!|\n");
                return 0;
            }
        }
        else
        {
            printf("\t|VIDA Eleven: %d|\n", eleven->hp);
            printf("\t|Taxa de Raiva: %d|\n", rage_power);
            return 1;
        }
        printf("\t|VIDA Eleven: %d|\n", eleven->hp);
        printf("\t|Taxa de Raiva: %d|\n", rage_power);
    }
}

void insertRadius(int ref_x, int ref_y, int range, int tam, char map[][tam], char entity, int qt)
{
    int x = -1, y = -1;

    for (int i = 0; i < qt;)
    {
        do
        {
            x = rand() % range + ref_x;
        } while (x < 0 || x > 9);

        do
        {
            y = rand() % range + ref_y;
        } while (y < 0 || y > 9);

        if (map[x][y] == '_')
        {
            map[x][y] = entity;
            i++;
        }
    }
}

int main()
{
    srand(time(NULL));
    int salaTam = 3;
    char sala[salaTam][salaTam];

    int upsideTam = 10;
    char upside[upsideTam][upsideTam];
    Character will, eleven;

    // Inicia o mapa da sala vazio
    for (int i = 0; i < salaTam; i++)
    {
        for (int j = 0; j < salaTam; j++)
        {
            sala[i][j] = '_';
        }
    }

    // Posicionamentos iniciais da sala
    int eleven_x = 0;
    int eleven_y = 0;
    sala[eleven_x][eleven_y] = 'E';
    eleven.hp = 100;

    char direction;
    char tried_pos;
    int rage_power, score = 0, try = 0, fail = 0;
    int met_portal = 0;

    printMap(salaTam, sala);
    printf("Vida: %d\n", eleven.hp);

    printf(">> ");
    scanf("%c", &direction);
    getchar();

    tried_pos = handleDirection(&eleven_x, &eleven_y, direction, salaTam, sala);
    sala[eleven_x][eleven_y] = 'E';

    if (createPortal(&eleven)) // condicao para quando ela consegue criar um portal!
    {
        printf("Eleven conseguiu criar o Portal!!\n");
        insertMap(salaTam, sala, 'O', 1);
    }

    while (eleven.hp > 0 && met_portal == 0)
    {
        printMap(salaTam, sala);
        printf("Vida: %d\n", eleven.hp);

        printf(">> ");
        scanf("%c", &direction);
        getchar();

        tried_pos = handleDirection(&eleven_x, &eleven_y, direction, salaTam, sala);
        sala[eleven_x][eleven_y] = 'E';

        switch (tried_pos)
        {
        case 'O':
            printf("Voce entrou no Mundo Invertido!!\n");
            met_portal = 1;
            break;
        }
    }
    // Eleven consegue sair da sala onde estava presa, agora começa a jornada para resgatar Will do Mundo Invertido!
    // Inicia o mapa do mundo invertido
    for (int i = 0; i < upsideTam; i++)
    {
        for (int j = 0; j < upsideTam; j++)
        {
            upside[i][j] = '_';
        }
    }

    // Posicionamentos iniciais
    eleven_x = 0; // zerar os valores
    eleven_y = 1;
    upside[eleven_x][eleven_y] = 'E';
    int will_x;
    int will_y;

    insertMap(upsideTam, upside, 'W', 1);
    for (int i = 0; i < upsideTam; i++) // de modo a pegar a posicao de will, para fazer seu movimento
    {
        for (int j = 0; j < upsideTam; j++)
        {
            if (upside[i][j] == 'W')
            {
                will_x = i;
                will_y = j;
                break;
            }
        }
    }
    upside[0][0] = 'S';

    // Populando o mapa com as entidades
    insertMap(upsideTam, upside, 'A', 10);
    insertMap(upsideTam, upside, 'C', 5);
    insertMap(upsideTam, upside, 'H', 5);
    insertMap(upsideTam, upside, 'D', 5);
    insertMap(upsideTam, upside, 'P', 10);

    // movimentacao
    int met_will = 0;
    int will_saved = 0;
    int dog_generate = 0;
    while (met_portal == 1 && will_saved == 0) // while (met_portal==1 && condicaoSaida)
    {
        printMap(upsideTam, upside);
        printf("Vida: %d\n", eleven.hp);

        printf(">> ");
        scanf("%c", &direction);
        getchar();

        tried_pos = handleDirection(&eleven_x, &eleven_y, direction, upsideTam, upside);
        upside[eleven_x][eleven_y] = 'E';

        if (met_will == 0)
        { // movimento do will quando nao estiver com 11
            char direcao[] = {'w', 'a', 's', 'd'};
            int pos_direcao = rand() % 4;
            handleDirection(&will_x, &will_y, direcao[pos_direcao], upsideTam, upside);
            upside[will_x][will_y] = 'W';
        }

        if (dog_generate == 0 && (will_x - eleven_x < 3 && will_y - eleven_y < 3))
        {
            printf("\n CUIDADO!! Demodogs APARECERAM!! \n");
            insertRadius(eleven_x, eleven_y, 4, upsideTam, upside, 'D', 2);
            dog_generate = 1;
        }

        switch (tried_pos)
        {
        case 'P':
            removeEntity(upsideTam, upside, eleven_x, eleven_y, direction);
            if (eleven.hp <= 95) // Implementei esta condicional para adicionar tbm quando for maior que 100 e menor que 195 pq, senao, fica 200
            {
                eleven.hp += 5;
            }
            else if (eleven.hp <= 100 && eleven.hp + 5 >= 100)
            {
                eleven.hp = 100;
            }
            break;
        case 'D':
            removeEntity(upsideTam, upside, eleven_x, eleven_y, direction);
            eleven.hp -= 10;
            break;
        case 'S':
            if (met_will == 0)
            {
                printf("\n Voce nao pode sair sem encontrar o WILL!\n");
            }
            else
            {
                printf("\n==SALVAMOS WILL!!==\n");
                will_saved = 1;
            }
            break;
        case 'W':
            removeEntity(upsideTam, upside, eleven_x, eleven_y, direction);
            met_will = 1;
            printf("\nEncontramos Will!!\n");
            break;
        }
    }
    return 0;
}
