#include <stdio.h>

typedef struct
{
    char nome[30];
    int codigo_produto;
    int qtd;
    int vendas;
    int compras;
    float preco;
    int status;
} Produto;

int partition_vendas(Produto A[], int l, int r)
{
    int pivot = A[l].vendas;
    int i = l;

    for (int j = l + 1; j <= r; j++)
    {
        // Checa se a posicao j e menor do que o pivot ou igual a ele
        if (A[j].vendas >= pivot)
        {
            // Incrementa a posicao i para que troque a posicao verificada com o j
            // e nao o pivot
            i++;
            Produto temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }

    // Coloca o pivot na posicao i achada
    Produto temp = A[i];
    A[i] = A[l];
    A[l] = temp;

    return i;
}

void quicksort_vendas(Produto A[], int l, int r)
{
    if (l < r)
    {
        int pivot_index = partition_vendas(A, l, r);
        quicksort_vendas(A, l, pivot_index - 1);
        quicksort_vendas(A, pivot_index + 1, r);
    }
}

int partition_compras(Produto A[], int l, int r)
{
    int pivot = A[l].compras;
    int i = l;

    for (int j = l + 1; j <= r; j++)
    {
        // Checa se a posicao j e menor do que o pivot ou igual a ele
        if (A[j].compras >= pivot)
        {
            // Incrementa a posicao i para que troque a posicao verificada com o j
            // e nao o pivot
            i++;
            Produto temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }

    // Coloca o pivot na posicao i achada
    Produto temp = A[i];
    A[i] = A[l];
    A[l] = temp;

    return i;
}

void quicksort_compras(Produto A[], int l, int r)
{
    if (l < r)
    {
        int pivot_index = partition_compras(A, l, r);
        quicksort_compras(A, l, pivot_index - 1);
        quicksort_compras(A, pivot_index + 1, r);
    }
}

int inserir(Produto *produtos, int tamanho, int posicao, Produto novo)
{
    // Cadastrando o Produto novo
    printf("Informe o nome do produto %d: ", posicao + 1);
    scanf("%s", novo.nome);
    getchar();
    printf("Informe o codigo do produto %d: ", posicao + 1);
    scanf("%d", &novo.codigo_produto);
    getchar();

    // Verificar se o codigo do novo ja existe em algum produto
    for (int i = 0; i < posicao; i++)
    {
        // strcmp(novo.codigo_produto, produtos[i].codigo_produto)
        if (produtos[i].codigo_produto == novo.codigo_produto)
        {
            printf("O codigo de produto informado ja existe\n");
            return 0; // Se ja existir, retorna zero e termina a funcao
        }
    }

    printf("Informe o preco do produto %d: ", posicao + 1);
    scanf("%f", &novo.preco);
    getchar();
    novo.vendas = 0;
    novo.compras = 0;
    novo.status = 1;
    novo.qtd = 0;

    // Se nao existir, coloca novo na posicao informada
    produtos[posicao] = novo;
    printf("\t|Produto cadastrado com sucesso!!|\n");
    return 1;
}

int remover(Produto *produtos, int tamanho, int codigo)
{
    printf("Informe o codigo do produto a ser deletado: ");
    scanf("%d", &codigo);
    getchar();

    // Procura no vetor se ha algum codigo igual
    for (int i = 0; i < tamanho; i++)
    {
        if (produtos[i].codigo_produto == codigo)
        {
            produtos[i].status = 0;
            printf("\t|Produto removido com sucesso!|\n");
            return 1;
        }
    }
    printf("O codigo informado nao pode ser achado. Tente novamente.\n");
    return 0;
}

int buscar(Produto *produtos, int tamanho, int codigo)
{
    printf("Informe o codigo do produto a ser buscado: ");
    scanf("%d", &codigo);
    getchar();

    // Procura no vetor se ha algum codigo igual
    for (int i = 0; i < tamanho; i++)
    {
        if (produtos[i].codigo_produto == codigo)
        {
            printf("|Produto encontrado com sucesso!|\n");
            return i;
        }
    }
    printf("\t|Nao achamos um produto com o codigo informado. Tente novamente.|\n");
    return -1;
}

int comprar(Produto *produtos, int tamanho, int codigo)
{
    printf("Informe o codigo do produto a ser comprado: ");
    scanf("%d", &codigo);
    getchar();

    int qtd;
    printf("Informe a quantidade do produto a ser comprada: ");
    scanf("%d", &qtd);
    getchar();

    // Procura no vetor se ha algum codigo igual
    for (int i = 0; i < tamanho; i++)
    {
        if (produtos[i].codigo_produto == codigo)
        {
            produtos[i].qtd = produtos[i].qtd + qtd;
            produtos[i].compras = produtos[i].compras + qtd;
            printf("|Produto comprado com sucesso!|\n");
            return 1;
        }
    }
    printf("O codigo informado nao pode ser achado. Tente novamente.\n");
    return 0;
}

int vender(Produto *produtos, int tamanho, int codigo)
{
    printf("Informe o codigo do produto a ser vendido: ");
    scanf("%d", &codigo);
    getchar();

    int qtd;
    do
    {
        printf("Informe a quantidade do produto a ser vendida: ");
        scanf("%d", &qtd);
        getchar();
        if (qtd <= 0)
        {
            printf("\nInforme uma quantidade valida\n");
        }
    } while (qtd <= 0);

    // Procura no vetor se ha algum codigo igual
    for (int i = 0; i < tamanho; i++)
    {
        if (produtos[i].codigo_produto == codigo)
        {
            if (produtos[i].qtd >= qtd)
            {
                produtos[i].qtd = produtos[i].qtd - qtd;
                produtos[i].vendas = produtos[i].vendas + qtd;
                printf("\t|Produto vendido com sucesso!|\n");
                return 1;
            }
            else if (produtos[i].qtd == 0)
            {
                printf("\t|Produto indisponivel!|\n");
                return 0;
            }
            else
            {
                printf("\t|Ha apenas %d produtos %s no estoque, e voce tentou vender %d|", produtos[i].qtd, produtos[i].nome, qtd);
                return 0;
            }
        }
    }
    printf("O codigo informado nao pode ser achado. Tente novamente.\n");
    return 0;
}

void imprime_produto(Produto *produtos, int i)
{
    printf(" Nome: %s\n", produtos[i].nome);
    printf(" Codigo do Produto: %d\n", produtos[i].codigo_produto);
    printf(" Quantidade: %d\n", produtos[i].qtd);
    printf(" Vendas: %d\n", produtos[i].vendas);
    printf(" Compras: %d\n", produtos[i].compras);
    printf(" Preco: R$%.2f\n", produtos[i].preco);
}

float calcular_extrato(Produto *produtos, int tamanho)
{
    float soma_vendas = 0.0;

    for (int i = 0; i < tamanho; i++)
    {
        soma_vendas += (float)produtos[i].vendas * produtos[i].preco;
    }
    float soma_compras = 0.0;

    for (int i = 0; i < tamanho; i++)
    {
        soma_compras += (float)produtos[i].compras * produtos[i].preco;
    }
    return soma_vendas - soma_compras;
}

int main()
{
    int tam = 10;
    Produto produtos[tam];

    int option = 1;
    int pos = 0;
    Produto novo;
    int result;
    int codigo;
    while (option != 0)
    {
        printf("\n\t\t== SISTEMA DE CADASTRO DE PRODUTOS DA PADARIA07 ==\n");
        printf("     MENU: \n\t1 - Inserir Produto\n\t2 - Remover Produto\n\t3 - Buscar Produto\n\t4 - Comprar Produto\n\t5 - Vender Produto\n\t0 - Relatorio sobre os Produtos\nO que deseja fazer?\n>> ");
        scanf("%d", &option);
        getchar();

        switch (option)
        {
        case 0:
            printf("|Gerando relatorio...\n\n");
            break;
        case 1:
            // Insere o produto
            result = inserir(produtos, tam, pos, novo);
            // Caso seja valido, aumenta uma posicao
            if (result == 1)
            {
                pos++;
            }
            break;
        case 2:
            // Remove o produto
            remover(produtos, pos, codigo);
            break;
        case 3:
            // Busca o produto
            result = buscar(produtos, pos, codigo);
            if (result != -1 && produtos[result].status == 1)
            {
                imprime_produto(produtos, result);
            }
            else if (result != -1 && produtos[result].status == 0)
            {
                printf("...mas esse produto foi removido\n");
            }
            break;
        case 4:
            // Compra um produto
            comprar(produtos, pos, codigo);
            break;
        case 5:
            // Vende um produto
            vender(produtos, pos, codigo);
            break;
        default:
            printf("Nao entendi o que voce digitou\n");
            break;
        }
    }

    // Relatorio
    // Lista ordenada dos produtos mais vendidos
    printf("|Produtos mais vendidos|\n");
    Produto produtos_vendas[pos];

    for (int i = 0; i < pos; i++)
    {
        produtos_vendas[i] = produtos[i];
    }

    quicksort_vendas(produtos_vendas, 0, pos - 1);

    for (int i = 0; i < pos; i++)
    {
        printf(" Nome do produto: %s\nVendas: %d\n", produtos_vendas[i].nome, produtos_vendas[i].vendas);
    }
    printf("\n");

    // lista ordenada dos produtos mais comprados
    printf("|Produtos mais comprados|\n");
    Produto produtos_compras[pos];

    for (int i = 0; i < pos; i++)
    {
        produtos_compras[i] = produtos[i];
    }

    quicksort_compras(produtos_compras, 0, pos - 1);

    for (int i = 0; i < pos; i++)
    {
        printf(" Nome do produto: %s\nCompras: %d\n", produtos_compras[i].nome, produtos_compras[i].compras);
    }
    printf("\n");

    // extrato da conta da padaria
    printf("|Extrato da padaria|\n");
    printf("R$: %.2f\n", calcular_extrato(produtos, pos));

    // produtos em estoque
    printf("\n|Produtos em estoque|\n");
    int tem_estoque = 0;

    for (int i = 0; i < pos; i++)
    {
        if (produtos[i].qtd > 0)
        {
            printf("Nome: %s\n", produtos[i].nome);
            tem_estoque = 1;
        }
    }
    if (tem_estoque == 0)
    {
        printf("Nao ha nenhum produto no estoque\n");
    }

    return 0;
}
