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

void ambil_kodeLoket(char* destinasi, char* result, TreeNode* root) {
    strcpy(result, "");

    
    void search_node(TreeNode* node, char* dest, char* res) {
        if (node == NULL) return;

        if (strcmp(node->city, dest) == 0) {
            strcpy(res, node->kode_loket);
            return;
        }

        search_node(node->first_son, dest, res);
        
        if (strlen(res) > 0) return;

        search_node(node->next_brother, dest, res);
    }
    
     search_node(root, destinasi, result);
}

int harga_tiket(char* destinasi, TreeNode* root) {
    Stack rute_stack;
    init_stack(&rute_stack);
    if (cari_rute(root, destinasi, &rute_stack)) {
        return (rute_stack.top + 1) * 1000000; 
    }
    return -1;
}

void beli_tiket(TreeNode* root) {
    system("cls"); 
    if (strlen(current_user) == 0) {
        printf("   Silahkan login terlebih dahulu untuk membeli tiket!\n");
        return;
    }

    printf("                                 ================================================\n");
    printf("                                 |            PEMBELIAN TIKET PESAWAT           |\n");
    printf("                                 ------------------------------------------------\n");
    printf("                                           Kemana tujuanmu ?? : ");
    char dest[MAX_STRING];
    scanf("%s", dest);
    while (getchar() != '\n');

    Stack rute_stack;
    init_stack(&rute_stack);
    if (!cari_rute(root, dest, &rute_stack)) {
        printf("\n                                 ------------------------------------------------\n");
        printf("                                 |    Tidak ada destinasi ke negara tujuanmu    |\n");
        printf("                                 ================================================\n");
        return;
    }


    printf("                                 ------------------------------------------------\n");
    printf("                                 | Berikut rute perjalananmu :                  |\n");
    printf("                                 ------------------------------------------------\n");

    char tampil_rute[200] = "";
    int i;
    for (i = 0; i <= rute_stack.top; i++) {
        strcat(tampil_rute, rute_stack.items[i].rute);
        if (i < rute_stack.top) strcat(tampil_rute, " -> ");
    }
    printf("                                  %s \n", tampil_rute);
    printf("                                 ---------------------------------------------------\n");

    char transit_info[50];
    sprintf(transit_info, "                   Total Transit: %d kali", rute_stack.top - 1);
    printf("                                  %s \n", transit_info);
    printf("                                 ------------------------------------------------\n");


    printf("                                 |          Pilih jadwal penerbanganmu:         |\n");
    printf("                                 |           1. 09.30                           |\n");
    printf("                                 |           2. 15.10                           |\n");
    printf("                                 |           3. 21.50                           |\n");
    printf("                                 ------------------------------------------------\n");
    printf("                                                 = ");

    int jadwal_choice;
    scanf("%d", &jadwal_choice);
    
    while (getchar() != '\n');
    char jadwal[MAX_STRING];
    switch (jadwal_choice) {
        case 1: strcpy(jadwal, "09.30"); break;
        case 2: strcpy(jadwal, "15.10"); break;
        case 3: strcpy(jadwal, "21.50"); break;
        default: strcpy(jadwal, "Tidak Valid");
    }
    if (strcmp(jadwal, "Tidak Valid") == 0) {
        printf("                                    Mohon pilih antara 1, 2, atau 3.\n");
    	printf("                                 ===============================================\n");
        return;
    }

    char kode_loket[MAX_STRING];
    ambil_kodeLoket(dest, kode_loket, root);
    if (strlen(kode_loket) == 0) {
        printf("                                    Tidak ada loket untuk destinasi ini.\n");
        printf("                                 ===============================================\n");
        return;
    }

    int harga = harga_tiket(dest, root);
    if (harga < 0) {
         printf("                                    Harga tiket error, silahkan coba lagi! \n");
        printf("                                 ===============================================\n");
        return;
    }

    printf("                                    Jumlah tiket : ");
    int tiket;
    scanf("%d", &tiket);
    while (getchar() != '\n');

    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    char time_str[50];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm);

    char filename[MAX_STRING];
    sprintf(filename, "%s.txt", current_user);
    FILE* file = fopen(filename, "a");
    if (file != NULL) {
        fprintf(file, "%s|%s|%d|%d|Dalam Antrian Check-In|%s\n", dest, jadwal, tiket, harga * tiket, time_str);
        fclose(file);

        char queue_filename[MAX_STRING];
        sprintf(queue_filename, "./queues/queue_%s.txt", kode_loket);
        file = fopen(queue_filename, "a");
        if (file != NULL) {
            fprintf(file, "%s|%s|%s|%s|%d|%d|%s\n", current_user, dest, kode_loket, jadwal, tiket, harga * tiket, time_str);
            fclose(file);
        } else {
           printf("                                    Hubungi admin untuk masuk ke antrian loket.\n");
        }

        char kode_penerbangan[10];
        sprintf(kode_penerbangan, "%s-%03d", kode_loket, (int)(time(NULL) % 1000)); 
    
        // Tampilan tiket pemesanan tiket
        system("cls");
        printf("\n            =========================================================\n");
        printf("                                TIKET PESAWAT                       \n");
        printf("            =========================================================\n");
        printf("            Nama Penumpang    : %s\n", current_user);
        printf("            Kode Penerbangan  : %s\n", kode_penerbangan);
        printf("            Rute              : %s\n", tampil_rute);
        printf("            Jadwal            : %s\n", jadwal);
        printf("            Jumlah Tiket      : %d\n", tiket);
        printf("            Total Harga       : Rp %d\n", harga * tiket);
        printf("            Waktu Pemesanan   : %s\n", time_str);
        printf("            Status            : %s\n", "Dalam Antrian Check-In");
        printf("            Loket Check-In    : %s\n", kode_loket);
        printf("            ========================================================="); getchar();
        printf("             Tiket berada dalam antrian Check-In di loket %s !\n", kode_loket);
        printf("            =========================================================\n");
    } else {
        printf("             Gagal menyimpan data tiket! Mohon coba lagi.\n");
 }
} 
