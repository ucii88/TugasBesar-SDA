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

int register_user();
int login_user();

#endif