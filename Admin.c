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

void proses_tiket() {
    system("cls"); 

    char main_loket[2];
    printf("\n==========================================\n");
    printf("          PROSES TIKET ANTRIAN            \n");
    printf("==========================================\n");
    printf("Loket utama yang akan diproses (A, B, atau C): ");
    scanf("%1s", main_loket);

    if (main_loket[0] != 'A' && main_loket[0] != 'B' && main_loket[0] != 'C') {
        printf("Kode loket utama tidak valid! Gunakan A, B, atau C.\n");
        return;
    }

    printf("\nPilih sub-loket yang akan diproses %c:\n", main_loket[0]);
    int sub_loket_count = 0;
    int i;
    for (i = 0; i < dest_count; i++) {
        if (destinasi[i][0] == main_loket[0]) {
            sub_loket_count++;
            printf("%d. %s\n", sub_loket_count, destinasi[i]);
        }
    }

    if (sub_loket_count == 0) {
        printf("Tidak ada sub-loket yang tersedia untuk loket utama %c.\n", main_loket[0]);
        return;
    }

    int choice;
    printf("Pilih nomor sub-loket (1-%d): ", sub_loket_count);
    scanf("%d", &choice);

    if (choice < 1 || choice > sub_loket_count) {
        printf("Pilihan tidak valid! Harus antara 1 dan %d.\n", sub_loket_count);
        return;
    }

    char pilihan_loket[MAX_STRING];
    int current_index = 0;
    for (i = 0; i < dest_count; i++) {
        if (destinasi[i][0] == main_loket[0]) {
            current_index++;
            if (current_index == choice) {
                strcpy(pilihan_loket, destinasi[i]);
                break;
            }
        }
    }

    char queue_filename[MAX_STRING];
    sprintf(queue_filename, "./queues/queue_%s.txt", pilihan_loket);

    FILE* file = fopen(queue_filename, "r");
    if (file == NULL) {
        printf("Tidak ada antrian untuk loket %s saat ini!\n", pilihan_loket);
        return;
    }

    char line[200];
    if (!fgets(line, sizeof(line), file)) {
        fclose(file);
        printf("Antrian untuk sub-loket %s kosong.\n", pilihan_loket);
        return;
    }

    line[strcspn(line, "\n")] = 0;

    if (strlen(line) == 0) {
        fclose(file);
        printf("Antrian kosong atau data tidak valid.\n");
        return;
    }

    char username[MAX_STRING], destinasi[MAX_STRING], kode_loket[MAX_STRING], jadwal[MAX_STRING], time_str[MAX_STRING];
    int tiket, harga;

    int sscanf_result = sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%[^\n]", 
                              username, destinasi, kode_loket, jadwal, &tiket, &harga, time_str);
    if (sscanf_result != 7) {
        printf("Error: Gagal membaca data tiket. Jumlah elemen yang diparsing: %d\n", sscanf_result);
        fclose(file);
        return;
    }
    
    system("cls"); 
    printf("\n==========================================\n");
    printf("              DETAIL TIKET         \n");
    printf("==========================================\n");
    printf("  Username  : %s\n", username);
    printf("  Destinasi : %s\n", destinasi);
    printf("  Loket     : %s\n", kode_loket);
    printf("  Jadwal    : %s\n", jadwal);
    printf("  Tiket     : %d\n", tiket);
    printf("  Total Harga: Rp %d\n", harga);
    printf("  Waktu     : %s\n", time_str);
    printf("------------------------------------------\n");

    int proses;
    printf("(1.) Approve Tiket\n");
    printf("(2.) Reject Tiket\n");
    printf("     = ");
    scanf("%d", &proses);

    char new_status[MAX_STRING];
    if (proses == 1) {
        strcpy(new_status, "Sudah Melakukan Check-In");
        printf("\n Tiket berhasil di-APPROVE!\n");
    } else if (proses == 2) {
        strcpy(new_status, "Rejected");
        printf("\n Tiket berhasil di-REJECT!\n");
    } else {
        printf("\nInput tidak valid. Pembatalan proses.\n");
        fclose(file);
        return;
    }

    char user_filename[MAX_STRING];
    sprintf(user_filename, "%s.txt", username);

    FILE* user_file = fopen(user_filename, "r");
    FILE* temp_file = fopen("temp.txt", "w");

    if (user_file != NULL && temp_file != NULL) {
        char line[200];
        while (fgets(line, sizeof(line), user_file)) {
            char dest[MAX_STRING], sched[MAX_STRING], stat[MAX_STRING], timestr[MAX_STRING];
            int tix, pri;
            if (sscanf(line, "%[^|]|%[^|]|%d|%d|%[^|]|%[^\n]", 
                      dest, sched, &tix, &pri, stat, timestr) == 6) {
                if (strcmp(dest, destinasi) == 0 && 
                    strcmp(sched, jadwal) == 0 && 
                    tix == tiket && 
                    pri == harga && 
                    strcmp(timestr, time_str) == 0 && 
                    strcmp(stat, "Dalam Antrian Check-In") == 0) {
                    fprintf(temp_file, "%s|%s|%d|%d|%s|%s\n", 
                            dest, jadwal, tiket, harga, new_status, time_str);
                } else {
                    fprintf(temp_file, "%s", line);
                }
            } else {
                fprintf(temp_file, "%s", line);
            }
        }
        
        fclose(user_file);
        fclose(temp_file);
        remove(user_filename);
        rename("temp.txt", user_filename);
    } else {
        printf("Error: Gagal membuka file user atau file sementara.\n");
    }

    fclose(file);
    file = fopen(queue_filename, "r");
    temp_file = fopen("temp.txt", "w");

    if (file != NULL && temp_file != NULL) {
        char line[200];
        int first = 1;
        while (fgets(line, sizeof(line), file)) {
            if (first) {
                first = 0;
                continue;
            }
            fprintf(temp_file, "%s", line);
        }
        fclose(file);
        fclose(temp_file);
        remove(queue_filename);
        rename("temp.txt", queue_filename);
    } else {
        printf("Error: Gagal membuka file antrian atau file sementara.\n");
    }

    printf("\nProses selesai!\n");
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