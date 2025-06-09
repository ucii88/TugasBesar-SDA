#ifndef TREE_H
#define TREE_H
#include <string.h>
#define MAX_STRING 50
#include "stack.h"

typedef struct TreeNode {
    char city[MAX_STRING];
    char kode_loket[MAX_STRING]; // Kode loket seperti A1, A2, dll.
    struct TreeNode* first_son;
    struct TreeNode* next_brother;
    struct TreeNode* parent;
    int level;
} TreeNode;

TreeNode* create_node(char* city, char* kode_loket, int level);
void add_child(TreeNode* parent, TreeNode* child);
int cari_rute(TreeNode* node, char* destinasi, Stack* rute_stack);
void buat_ruteTree(TreeNode** root);
void tampil_rute(char* destinasi, TreeNode* root);

#endif