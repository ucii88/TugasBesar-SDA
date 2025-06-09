#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        printf("Error! Gagal mengalokasikan memori untuk queue\n");
        exit(1);
    }
    q->front = NULL;
    q->rear = NULL;
    q->count = 0;
    return q;
}

void enqueue(Queue* q, char* username, char* destinasi, char* kode_loket, char* jadwal, int tiket, int harga, char* waktu_beli) {
    QueueItem* item = (QueueItem*)malloc(sizeof(QueueItem));
    if (item == NULL) {
        printf("Error! Gagal mengalokasikan memori untuk item\n");
        exit(1);
    }
    strcpy(item->username, username);
    strcpy(item->destinasi, destinasi);
    strcpy(item->kode_loket, kode_loket);
    strcpy(item->jadwal, jadwal);
    item->tiket = tiket;
    item->harga = harga;
    strcpy(item->waktu_beli, waktu_beli);

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error! Gagal mengalokasikan memori untuk node\n");
        free(item);
        exit(1);
    }
    newNode->data = item;
    newNode->next = NULL;

    if (isQueueEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->count++;
}

int dequeue(Queue* q, QueueItem* item) {
    if (isQueueEmpty(q)) {
        printf("Antrian kosong!\n");
        return 0;
    }

    Node* temp = q->front;
    *item = *(temp->data);
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp->data);
    free(temp);
    q->count--;
    return 1;
}

int isQueueEmpty(Queue* q) {
    return q->count == 0;
}

void freeQueue(Queue* q) {
    while (!isQueueEmpty(q)) {
        QueueItem item;
        dequeue(q, &item);
    }
    free(q);
}

void saveQueueToFile(Queue* q, const char* filename) {
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error Tidak dapat membuka file %s \n", filename);
        return;
    }

    Node* current = q->front;
    while (current != NULL) {
        QueueItem* item = current->data;
        fprintf(file, "%s|%s|%s|%s|%d|%d|%s\n",
                item->username, item->destinasi, item->kode_loket,
                item->jadwal, item->tiket, item->harga, item->waktu_beli);
        current = current->next;
    }
    fclose(file);
}

void loadQueueFromFile(Queue* q, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error Tidak dapat membuka file %s untuk pembacaan\n", filename);
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char username[MAX_STRING], destinasi[MAX_STRING], kode_loket[MAX_STRING], jadwal[MAX_STRING], time_str[MAX_STRING];
        int tiket, harga;

        if (sscanf( "%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%[^\n]", username, destinasi, kode_loket, jadwal, &tiket, &harga, time_str) == 7) {
            enqueue(q, username, destinasi, kode_loket, jadwal, tiket, harga, time_str);
        }
    }
    fclose(file);
}
