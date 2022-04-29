#include <stdio.h>

int aux=1;

typedef struct{
    char nome[30];
    char cpf[11];
    int salario;
}Funcionario;

Funcionario cadastrar(Funcionario funcionarios[], int tam) //Recursividade implementada no cadastro!!
{
    if (tam-1<=0){ //Resolvida o prob da pilha
        printf("Informe o nome do funcionario %d: ", aux); //ultimo
        scanf("%s", funcionarios[aux-1].nome);
        getchar();
        printf("Informe o cpf de %s: ", funcionarios[aux-1].nome);
        scanf("%s", funcionarios[aux-1].cpf);
        getchar();
        printf("Informe o salario de %s: ", funcionarios[aux-1].nome);
        scanf("%d", &funcionarios[aux-1].salario);
        getchar();

        return funcionarios[0];
    }else{
        printf("Informe o nome do funcionario %d: ", aux);
        scanf("%s", funcionarios[aux-1].nome);
        getchar();
        printf("Informe o cpf de %s: ", funcionarios[aux-1].nome);
        scanf("%s", funcionarios[aux-1].cpf);
        getchar();
        printf("Informe o salario de %s: ", funcionarios[aux-1].nome);
        scanf("%d", &funcionarios[aux-1].salario);
        getchar();
        aux++;
        return cadastrar(funcionarios,tam-1);
    }
}

int calcular_total(Funcionario funcionarios[], int tam){  //RECURSIVIDADE AQUI NA SOMA DOS SALARIOS!!
    if (tam-1<=0) //seria o primeiro
    {
        return funcionarios[0].salario;
    }else //enquanto isso, vai somando com o resto
    {
        return funcionarios[tam-1].salario + calcular_total(funcionarios, tam-1); //funcionarios[tam-1].salario, o -1 serve para transformar o "tam" em numero de index, para que não dê erro quando fizermos a recurssão!!
    }
}

int main()
{
    int n;

    printf("Informe o numero de funcionarios que deseja cadastrar: ");
    scanf("%d", &n);

    Funcionario funcionarios[n];

    cadastrar(funcionarios, n);
    calcular_total(funcionarios,n);

    //cabeçalho
    printf("\n|| FUNCIONARIOS ||\n");
    printf("\n||NOME||     ||CPF||\t||SALARIO||\t\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s", funcionarios[i].nome);
        printf("\t   %s", funcionarios[i].cpf);
        printf("\t R$ %d\n", funcionarios[i].salario);
    }
    printf("\n||SOMA DOS SALARIOS||\t\n");
    printf("\tR$ %d",calcular_total(funcionarios,n));
    return 0;
}