#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "stack.h"

TreeNode* create_node(char* city, char* kode_loket, int level) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    strcpy(node->city, city);
    strcpy(node->kode_loket, kode_loket);
    node->first_son = NULL;
    node->next_brother = NULL;
    node->level = level;
    return node;
}

void add_child(TreeNode* parent, TreeNode* child) {
    if (parent->first_son == NULL) {
        parent->first_son = child;
    } else {
        TreeNode* sibling = parent->first_son;
        while (sibling->next_brother != NULL) {
            sibling = sibling->next_brother;
        }
        sibling->next_brother = child;
    }
}

void buat_ruteTree(TreeNode** root) {
    *root = create_node("JKT", "", 0);
    
    TreeNode* spore = create_node("Singapura", "A1", 1);
    TreeNode* dubai = create_node("Dubai", "B1", 1);
    TreeNode* doha = create_node("Doha", "C1", 1);
    
    add_child(*root, spore);
    add_child(*root, dubai);
    add_child(*root, doha);
    
    TreeNode* tokyo = create_node("Tokyo", "A2", 2);
    TreeNode* seoul = create_node("Seoul", "A3", 2);
    add_child(spore, tokyo);
    add_child(spore, seoul);
    
    TreeNode* cairo = create_node("Cairo", "B2", 2);
    TreeNode* istanbul = create_node("Istanbul", "B3", 2);
    add_child(dubai, cairo);
    add_child(dubai, istanbul);
    
    TreeNode* london = create_node("London", "C2", 2);
    add_child(doha, london);
    
    TreeNode* berlin = create_node("Berlin", "B4", 3);
    TreeNode* paris = create_node("Paris", "B5", 3);
    add_child(istanbul, berlin);
    add_child(istanbul, paris);
    
    TreeNode* ny = create_node("NY", "C3", 3);
    add_child(london, ny);
    
    TreeNode* LA = create_node("LA", "C4", 4);
    TreeNode* toronto = create_node("Toronto", "C5", 4);
    add_child(ny, LA);
    add_child(ny, toronto);
}

int cari_rute(TreeNode* node, char* destinasi, Stack* rute_stack) {
    if (node == NULL) return 0;
    
    push(rute_stack, node->city, node->level);
    
    if (strcmp(node->city, destinasi) == 0) {
        return 1;
    }
    
    TreeNode* child = node->first_son;
    while (child != NULL) {
        if (cari_rute(child, destinasi, rute_stack)) {
            return 1;
        }
        child = child->next_brother;
    }
    
    pop(rute_stack);
    return 0;
}

void tampil_rute(char* destinasi, TreeNode* root) {
    Stack rute_stack;
    init_stack(&rute_stack);
    
    if (cari_rute(root, destinasi, &rute_stack)) {
        printf("\n=== RUTE PERJALANAN ===\n");
        int i;
        for (i = 0; i <= rute_stack.top; i++) {
            printf("%s", rute_stack.items[i].rute);
            if (i < rute_stack.top) {
                printf(" -> ");
            }
        }
        printf("\n");
        
        int total_transit = rute_stack.top - 1;
        if (total_transit < 0) {
            total_transit = 0;
        }
        
        printf("Total Transit: %d kali\n", total_transit);
    } else {
        printf("Destinasi tidak ditemukan!\n");
    }
}