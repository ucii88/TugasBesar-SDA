#ifndef USER_H
#define USER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define MAX_STRING 50
#define CONSOLE_WIDTH 80

#include "Tree.h"
#include "Stack.h"
#include "Queue.h"

extern char current_user[MAX_STRING];

extern int dest_count;

int register_user();
int login_user();
void ambil_kodeLoket(char* destinasi, char* result, TreeNode* root);
int harga_tiket(char* destinasi, TreeNode* root);
void beli_tiket(TreeNode* root);

#endif