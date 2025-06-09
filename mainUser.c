#include "user.h"
#include <time.h>
#include <stdlib.h> 

TreeNode* root = NULL;
char current_user[MAX_STRING] = "";
char destinasi[][MAX_STRING] = {
    "A1", "A2", "A3", // Singapura, Tokyo, Seoul
    "B1", "B2", "B3", "B4", "B5", // Dubai, Cairo, Istanbul, Berlin, Paris
    "C1", "C2", "C3", "C4", "C5" // Doha, London, NY, LA, Toronto
};

int dest_count = 13;