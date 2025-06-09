#ifndef QUEUE_H
#define QUEUE_H

#define MAX_STRING 50

typedef struct {
    char username[MAX_STRING];
    char destinasi[MAX_STRING];
    char kode_loket[MAX_STRING]; // Menyimpan kode loket seperti A3, B4, dll.
    char jadwal[MAX_STRING];
    int tiket;
    int harga;
    char waktu_beli[MAX_STRING];
} QueueItem;

typedef struct Node {
    QueueItem* data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int count;
} Queue;

Queue* createQueue();
void enqueue(Queue* q, char* username, char* destinasi, char* kode_loket, char* jadwal, int tiket, int harga, char* waktu_beli);
int dequeue(Queue* q, QueueItem* item);
int isQueueEmpty(Queue* q);
void freeQueue(Queue* q);
void saveQueueToFile(Queue* q, const char* filename);
void loadQueueFromFile(Queue* q, const char* filename);

#endif
