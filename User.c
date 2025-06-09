#include "User.h"
#include <time.h>
#include <stdlib.h>

extern char current_user[MAX_STRING];

int register_user() {
    system("cls"); 
    printf("\n\n\n\n                                 =========================================================\n");
    printf("                                 |                REGISTRASI PENGGUNA BARU               |\n");
    printf("                                 =========================================================\n");
    printf("\n                                                    Username baru: ");
    char username[MAX_STRING];
    scanf("%s", username);
    while (getchar() != '\n');

    char filename[MAX_STRING];
    sprintf(filename, "%s.txt", username);
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        printf("\n                                 =========================================================\n");
        printf("                                 |           Username sudah terdaftar sebelumnya         |\n");
        printf("                                 =========================================================\n");
        return 0; 
    }

    file = fopen("databaselogin.txt", "a");
    if (file != NULL) {
        printf("                                                    Password: ");
        char password[MAX_STRING];
        scanf("%s", password);
        while (getchar() != '\n');
        fprintf(file, "%s|%s\n", username, password);
        fclose(file);

        file = fopen(filename, "w");
        if (file != NULL) {
            fprintf(file, "%s|default|0|0|Dalam Antrian Check-In|%s\n", username, "1970-01-01 00:00:00");
            fclose(file);
            strcpy(current_user, username);
            printf("\n                                 =========================================================\n");
            printf("                                            Registrasi berhasil! Halo, %s               \n", current_user);
            printf("                                 =========================================================\n");
            return 1;
        }
    }
    printf("\n                                 =========================================================\n");
    printf("                                 |          Registrasi gagal! Silahkan coba lagi.        |\n");
    printf("                                 =========================================================\n");
    return 0;
}

int login_user() {
    system("cls"); 
	printf("                                 ========================================\n");
    printf("                                              LOGIN PENGGUNA             \n");
    printf("                                 ========================================\n");
    printf("                                    Username: ");
    char username[MAX_STRING];
    scanf("%s", username);
    while (getchar() != '\n');

    printf("                                    Password: ");
    char password[MAX_STRING];
    scanf("%s", password);
    while (getchar() != '\n');

    char filename[MAX_STRING] = "databaselogin.txt";
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        char line[100], stored_username[MAX_STRING], stored_password[MAX_STRING];
        while (fgets(line, sizeof(line), file)) {
            if (sscanf(line, "%[^|]|%[^\n]", stored_username, stored_password) == 2) {
                if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0) {
                    fclose(file);
                    strcpy(current_user, username);
                    printf("                                   Login berhasil! Selamat datang, %s!\n", current_user);
                    printf("                                 ========================================\n");
                    return 1;
                }
            }
        }
        fclose(file);
    }
    printf("                                    Username atau password salah! Silahkan coba lagi.\n");
    printf("                                 ========================================\n");
    return 0;
}