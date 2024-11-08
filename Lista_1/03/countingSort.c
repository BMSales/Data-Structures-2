#include <stdio.h>
#include <stdlib.h>

void countingSort(int arr[], int n, int max) {
    int i;
    int *count = (int *)malloc((max + 1) * sizeof(int));
    int *output = (int *)malloc(n * sizeof(int));

    // Inicializa o array de contagem
    for (i = 0; i <= max; i++) {
        count[i] = 0;
    }

    // Conta a ocorrência de cada valor
    for (i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    // Modifica count[i] para conter a posição correta de cada valor
    for (i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    // Constrói o array de saída
    for (i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Copia o array de saída para o original
    for (i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(count);
    free(output);
}

int main() {
    int arr[] = {4, 2, 0, 8, 3, 0, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int max = 8; // Valor máximo no array

    countingSort(arr, n, max);

    printf("Array ordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
