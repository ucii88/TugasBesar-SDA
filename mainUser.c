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

void display_main_menu(const char* time_str) {
    system("cls");
    
	printf("\n\n\n\n                                 =========================================================\n");
    printf("                                 |  !!  LAYANAN PENERBANGAN MASKAPAI G O M o 0 o D   !!  |\n");
    printf("                                 |-------------------------------------------------------|\n");

    char time_buffer[CONSOLE_WIDTH];
    sprintf(time_buffer, "                                            %s ", time_str);
    printf(time_buffer);
    
    printf("\n                                 |-------------------------------------------------------|\n");
    printf("                                 |                      MENU UTAMA                       |\n");
    printf("                                 |               (1.) Registrasi Akun Baru               |\n");
    printf("                                 |               (2.) Login ke Akun Anda                 |\n");
    printf("                                 |               (3.) Keluar dari Aplikasi               |\n");
    printf("                                 |-------------------------------------------------------|\n");
    printf("                                                            = ");
}

int main() {
    buat_ruteTree(&root);

    int choice;
    while (1) {
        time_t t = time(NULL);
        struct tm* tm = localtime(&t);
        char time_str[50];
        strftime(time_str, sizeof(time_str), "%I:%M %p, %A, %d %B %Y", tm);

        display_main_menu(time_str);

        scanf("%d", &choice);
        while (getchar() != '\n'); 

        switch (choice) {
            case 1:
                system("cls"); 
				register_user();
                getchar();
                break;
            case 2:
                system("cls"); 
                if (login_user()) {
                    user_menu(root); 
                } 
                getchar();
                break;
            case 3:
                system("cls"); 
                printf("\n\n\n\n                                 ==========================================================\n");
                printf("                                      Terima kasih telah menggunakan layanan GOMo0oD!\n");
                printf("                                                 Sampai Jumpa Kembali!\n");
                printf("                                 ==========================================================\n\n");
                exit(0);
            default:
                system("cls"); 
                printf("\n                               ===========================================================\n");
                printf("                                    Pilihan tidak valid! Mohon input angka 1, 2, atau 3.\n");
                printf("                                 ===========================================================\n");
                getchar();
        }
    }
    return 0;
}
