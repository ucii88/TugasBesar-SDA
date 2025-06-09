#include "Admin.h"
#include <stdlib.h> 


char destinasi[][MAX_STRING] = {
    "A1", "A2", "A3", // Singapura, Tokyo, Seoul
    "B1", "B2", "B3", "B4", "B5", // Dubai, Cairo, Istanbul, Berlin, Paris
    "C1", "C2", "C3", "C4", "C5" // Doha, London, NY, LA, Toronto
};

int dest_count = 13;

void tampil_antrian_perloket() {
    system("cls");
    char main_loket[2];
    printf("\n==========================================\n");
    printf("        LIHAT ANTRIAN BERDASARKAN LOKET   \n");
    printf("==========================================\n");
    printf("Loket utama A, B, atau C : ");
    scanf("%1s", main_loket);

    if (main_loket[0] != 'A' && main_loket[0] != 'B' && main_loket[0] != 'C') {
        printf("Kode loket utama tidak valid!\n");
        return;
    }

    printf("\n==========================================\n");
    printf("        ANTRIAN LOKET UTAMA %c             \n", main_loket[0]);
    printf("==========================================\n");

    int found = 0;
    int i;
    for (i = 0; i < dest_count; i++) {
        if (destinasi[i][0] == main_loket[0]) {
            char queue_filename[MAX_STRING];
            sprintf(queue_filename, "./queues/queue_%s.txt", destinasi[i]);

            FILE* file = fopen(queue_filename, "r");
            if (file != NULL) {
                char line[200];
                int count = 0;

                printf("\n--- Sub-Loket %s ---\n", destinasi[i]);
                printf("----------------------------------------\n");

                while (fgets(line, sizeof(line), file)) {
                    line[strcspn(line, "\n")] = 0;
                    if (strlen(line) == 0) continue;

                    char username[MAX_STRING], destinasi[MAX_STRING], kode_loket[MAX_STRING], jadwal[MAX_STRING], time_str[MAX_STRING];
                    int tiket, harga;

                    int parsed = sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%[^\n]", 
                                      username, destinasi, kode_loket, jadwal, &tiket, &harga, time_str);
                    if (parsed == 7) {
                        count++;
                        found = 1;
                        printf("  %d. User: %s\n", count, username);
                        printf("     Destinasi: %s | Loket: %s\n", destinasi, kode_loket);
                        printf("     Tiket: %d | Harga: Rp %d\n", tiket, harga);
                        printf("     Jadwal: %s | Waktu: %s\n", jadwal, time_str);
                        printf("----------------------------------------\n");
                    } else {
                        printf("  [Error parsing baris: %s]\n", line);
                    }
                }

                if (count == 0) {
                    printf("  [Antrian Kosong]\n");
                }

                fclose(file);
            } else {
                printf("\n--- Sub-Loket %s: [Antrian Kosong] (File tidak ditemukan) ---\n", destinasi[i]);
            }
        }
    }

    if (!found) {
        printf("Tidak ada antrian aktif untuk loket utama %c.\n", main_loket[0]);
    }

    printf("==========================================\n");
}

void admin_login() {
    system("cls"); 
    char username[MAX_STRING], password[MAX_STRING];
    printf("\n============================================\n");
    printf("     SELAMAT DATANG DI ADMIN PANEL TIKET    \n");
    printf("\n==========================================\n");
    printf("               LOGIN ADMIN                \n");
    printf("==========================================\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("\n Login Berhasil! Selamat datang, Admin. \n");
    } else {
        printf("\n Login Gagal! Username atau Password salah. \n");
        exit(1);
    }
}