#include <stdio.h>
#include <stdlib.h>

#define BUCKETS 10

struct Node {
    float data;
    struct Node *next;
};

void insert(struct Node **bucket, float value) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = value;
    new_node->next = NULL;

    if (*bucket == NULL) {
        *bucket = new_node;
    } else {
        struct Node *temp = *bucket;
        struct Node *prev = NULL;
        while (temp != NULL && temp->data < value) {
            prev = temp;
            temp = temp->next;
        }
        if (prev == NULL) {
            new_node->next = *bucket;
            *bucket = new_node;
        } else {
            new_node->next = prev->next;
            prev->next = new_node;
        }
    }
}

void bucketSort(float arr[], int n) {
    struct Node *buckets[BUCKETS] = {NULL};

    // Distribui os elementos nos baldes
    for (int i = 0; i < n; i++) {
        int bucket_index = arr[i] * BUCKETS;
        insert(&buckets[bucket_index], arr[i]);
    }

    // Concatena os baldes ordenados no array
    int index = 0;
    for (int i = 0; i < BUCKETS; i++) {
        struct Node *temp = buckets[i];
        while (temp != NULL) {
            arr[index++] = temp->data;
            temp = temp->next;
        }
    }
}

int main() {
    float arr[] = {0.42, 0.32, 0.23, 0.52, 0.25, 0.47, 0.51};
    int n = sizeof(arr) / sizeof(arr[0]);

    bucketSort(arr, n);

    printf("Array ordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%f ", arr[i]);
    }

    return 0;
}
