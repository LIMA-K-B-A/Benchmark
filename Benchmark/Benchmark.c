#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerarArquivo(int quantidade, int min, int max) {
    FILE *arquivo = fopen("numeros.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        exit(1);
    }

    srand(time(NULL));

    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d ", rand() % (max - min + 1) + min);
    }

    fclose(arquivo);
}

void buscaLinear(int elemento) {
    FILE *arquivo = fopen("numeros.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    int numero;
    int posicao = 1;
    int encontrado = 0;

    while (fscanf(arquivo, "%d", &numero) != EOF) {
        if (numero == elemento) {
            printf("Elemento encontrado na posição %d.\n", posicao);
            encontrado = 1;
        }
        posicao++;
    }

    if (!encontrado) {
        printf("Elemento não encontrado.\n");
    }

    fclose(arquivo);
}

void buscaSentinela(int elemento) {
    FILE *arquivo = fopen("numeros.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    int numero;
    int posicao = 1;

    fscanf(arquivo, "%d", &numero); // Lê o primeiro número

    // Define o último número do arquivo como o sentinela
    while (fscanf(arquivo, "%d", &numero) != EOF) {
        posicao++;
    }
    fseek(arquivo, -sizeof(int), SEEK_END); // Volta para o último número

    if (numero != elemento) {
        printf("Elemento não encontrado.\n");
        fclose(arquivo);
        return;
    }

    printf("Elemento encontrado na posição %d.\n", posicao);

    fclose(arquivo);
}

void buscaBinaria(int elemento) {
    FILE *arquivo = fopen("numeros.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    int numero;
    int posicao = 1;
    int inicio = 1;
    int fim;
    int meio;

    // Determina o tamanho do arquivo
    fseek(arquivo, 0, SEEK_END);
    fim = ftell(arquivo) / sizeof(int);

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        fseek(arquivo, (meio - 1) * sizeof(int), SEEK_SET);
        fscanf(arquivo, "%d", &numero);

        if (numero == elemento) {
            printf("Elemento encontrado na posição %d.\n", meio);
            fclose(arquivo);
            return;
        } else if (numero < elemento) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("Elemento não encontrado.\n");

    fclose(arquivo);
}

void timer(void (*funcao)(int), int parametro) {
    clock_t inicio = clock();
    funcao(parametro);
    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f segundos\n", tempo);
}

void insertionSort() {
    FILE *arquivo = fopen("numeros.txt", "r+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    int numeros[100]; // Supondo um limite de 100 números
    int quantidade = 0;
    int temp, j;

    while (fscanf(arquivo, "%d", &numeros[quantidade]) != EOF) {
        quantidade++;
    }

    for (int i = 1; i < quantidade; i++) {
        temp = numeros[i];
        j = i - 1;
        while (j >= 0 && numeros[j] > temp) {
            numeros[j + 1] = numeros[j];
            j = j - 1;
        }
        numeros[j + 1] = temp;
    }

    rewind(arquivo);
    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d ", numeros[i]);
    }

    fclose(arquivo);
}

void bubbleSort() {
    FILE *arquivo = fopen("numeros.txt", "r+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    int numeros[100]; // Supondo um limite de 100 números
    int quantidade = 0;
    int temp;

    while (fscanf(arquivo, "%d", &numeros[quantidade]) != EOF) {
        quantidade++;
    }

    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = 0; j < quantidade - i - 1; j++) {
            if (numeros[j] > numeros[j + 1]) {
                temp = numeros[j];
                numeros[j] = numeros[j + 1];
                numeros[j + 1] = temp;
            }
        }
    }

    rewind(arquivo);
    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d ", numeros[i]);
    }

    fclose(arquivo);
    printf("Bubble Sort concluído.\n");
}

void quickSortRecursivo(int numeros[], int inicio, int fim) {
    if (inicio < fim) {
        int pivo = particiona(numeros, inicio, fim);
        quickSortRecursivo(numeros, inicio, pivo - 1);
        quickSortRecursivo(numeros, pivo + 1, fim);
    }
}

int particiona(int numeros[], int inicio, int fim) {
    int pivo = numeros[fim];
    int i = inicio - 1;

    for (int j = inicio; j <= fim - 1; j++) {
        if (numeros[j] < pivo) {
            i++;
            int temp = numeros[i];
            numeros[i] = numeros[j];
            numeros[j] = temp;
        }
    }

    int temp = numeros[i + 1];
    numeros[i + 1] = numeros[fim];
    numeros[fim] = temp;
    return i + 1;
}

void quickSort() {
    FILE *arquivo = fopen("numeros.txt", "r+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    int numeros[100]; // Supondo um limite de 100 números
    int quantidade = 0;

    while (fscanf(arquivo, "%d", &numeros[quantidade]) != EOF) {
        quantidade++;
    }

    quickSortRecursivo(numeros, 0, quantidade - 1);

    // Atualiza o arquivo com os números ordenados
    rewind(arquivo);
    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d ", numeros[i]);
    }

    printf("Quick Sort concluído.\n");
    fclose(arquivo);
}

int main() {
    int escolha;
    int elemento;
    int quantidade;
    int min, max;

    printf("Digite a quantidade de números a serem gerados: ");
    scanf("%d", &quantidade);

    printf("Digite o valor mínimo para os números gerados: ");
    scanf("%d", &min);

    printf("Digite o valor máximo para os números gerados: ");
    scanf("%d", &max);

    gerarArquivo(quantidade, min, max);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Busca Linear\n");
        printf("2. Busca Sentinela\n");
        printf("3. Busca Binária\n");
        printf("4. Insertion Sort\n");
        printf("5. Bubble Sort\n");
        printf("6. Quick Sort\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("Digite o elemento a ser buscado: ");
                scanf("%d", &elemento);
                timer(buscaLinear, elemento);
                break;
            case 2:
                printf("Digite o elemento a ser buscado: ");
                scanf("%d", &elemento);
                timer(buscaSentinela, elemento);
                break;
            case 3:
                printf("Digite o elemento a ser buscado: ");
                scanf("%d", &elemento);
                timer(buscaBinaria, elemento);
                break;
            case 4:
                timer(insertionSort, 0);
                break;
            case 5:
                timer(bubbleSort, 0);
                break;
            case 6:
                timer(quickSort, 0);
                break;
            case 0:
                return 0;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}

