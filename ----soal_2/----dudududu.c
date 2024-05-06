#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <math.h>
#include <time.h>

// Fungsi untuk mengubah angka menjadi kata
void numberToWords(int num, char *words) {
	//Array untuk menyimpan kata-kata dasar
    char *ones[] = {"", "satu", "dua", "tiga", "empat", "lima", "enam", "tujuh", "delapan", "sembilan"};
    	//Array untuk menyimpan kata-kata puluhan 
    char *tens[] = {"", "sepuluh", "dua puluh", "tiga puluh", "empat puluh", "lima puluh", "enam puluh", "tujuh puluh", "delapan puluh", "sembilan puluh"};
    	//Array untuk menyimpan kata-kata belasan
    char *teens[] = {"sepuluh", "sebelas", "dua belas", "tiga belas", "empat belas", "lima belas", "enam belas", "tujuh belas", "delapan belas", "sembilan belas"};
    
	//Jika angka kurang dari 10 
    if (num < 10) {
        strcpy(words, ones[num]);//Salin kata dasar dari array ones
    } 
    	//Jika angka di antara 10 dan 20 
    else if (num < 20) {
        strcpy(words, teens[num - 10]); //salin kata dasar dari array teens
    } 
    	//Jika angka lebih dari 10 dan 20
    else {
        int tens_digit = num / 10; //Ambil digit puluhan
        int ones_digit = num % 10; //Ambil digit satuan
        //Jika digit satuan adalah 0
        if (ones_digit == 0) {
            strcpy(words, tens[tens_digit]); //Salin kata puluhan dari array tens
        } else {
        // Gabungkan kata puluhan dan kata dasar menjadi satu kata
            sprintf(words, "%s %s", tens[tens_digit], ones[ones_digit]); 
        }
    }
}

int main(int argc, char *argv[]) {
    // Cek jumlah argumen
    if (argc != 2) {
        printf("Usage: %s [operation]\n", argv[0]);
        printf("Operations:\n");
        printf("-kali     : multiplication\n");
        printf("-tambah   : addition\n");
        printf("-kurang   : subtraction\n");
        printf("-bagi     : division\n");
        return 1;
    }

    // Simpan operasi yang diminta
    char *operation = argv[1];

    // Pipe untuk komunikasi antara parent dan child
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork process
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // Parent process
    if (pid > 0) {
        // Tutup file descriptor yang tidak digunakan
        close(pipefd[0]);

        // Baca input dari pengguna
        char input[50];
        printf("Masukkan dua angka (contoh: tiga tujuh): ");
        fgets(input, sizeof(input), stdin);

        // Kirim input ke child process
        write(pipefd[1], input, strlen(input) + 1);

        // Tutup file descriptor
        close(pipefd[1]);

        // Tunggu child process selesai
        wait(NULL);
    } 
    // Child process
    else {
        // Tutup file descriptor yang tidak digunakan
        close(pipefd[1]);

        // Baca input dari parent process
        char input[50];
        read(pipefd[0], input, sizeof(input));

        // Parse input menjadi dua angka
        char *token = strtok(input, " \n");
        int num1, num2;
        if (token != NULL) {
            // Konversi kata pertama menjadi angka
            if (strcmp(token, "satu") == 0)
                num1 = 1;
            else if (strcmp(token, "dua") == 0)
                num1 = 2;
            else if (strcmp(token, "tiga") == 0)
                num1 = 3;
            else if (strcmp(token, "empat") == 0)
                num1 = 4;
            else if (strcmp(token, "lima") == 0)
                num1 = 5;
            else if (strcmp(token, "enam") == 0)
                num1 = 6;
            else if (strcmp(token, "tujuh") == 0)
                num1 = 7;
            else if (strcmp(token, "delapan") == 0)
                num1 = 8;
            else if (strcmp(token, "sembilan") == 0)
                num1 = 9;
            else {
                printf("ERROR\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, " \n");
        if (token != NULL) {
            // Konversi kata kedua menjadi angka
            if (strcmp(token, "satu") == 0)
                num2 = 1;
            else if (strcmp(token, "dua") == 0)
                num2 = 2;
            else if (strcmp(token, "tiga") == 0)
                num2 = 3;
            else if (strcmp(token, "empat") == 0)
                num2 = 4;
            else if (strcmp(token, "lima") == 0)
                num2 = 5;
            else if (strcmp(token, "enam") == 0)
                num2 = 6;
            else if (strcmp(token, "tujuh") == 0)
                num2 = 7;
            else if (strcmp(token, "delapan") == 0)
                num2 = 8;
            else if (strcmp(token, "sembilan") == 0)
                num2 = 9;
            else {
                printf("ERROR\n");
                exit(EXIT_FAILURE);
            }
        }

        // Hitung hasil operasi
        int result;
        char message[100];
        if (strcmp(operation, "-kali") == 0) {
            result = num1 * num2;
            numberToWords(result, message);
            printf("hasil perkalian %s dan %s adalah %s.\n", strtok(input, " \n"), strtok(NULL, " \n"), message);
        } else if (strcmp(operation, "-tambah") == 0) {
            result = num1 + num2;
            numberToWords(result, message);
            printf("hasil penjumlahan %s dan %s adalah %s.\n", strtok(input, " \n"), strtok(NULL, " \n"), message);
        } else if (strcmp(operation, "-kurang") == 0) {
            result = num1 - num2;
            if (result < 0) {
                printf("ERROR\n");
                exit(EXIT_FAILURE);
            } else {
                numberToWords(result, message);
                printf("hasil pengurangan %s dan %s adalah %s.\n", strtok(input, " \n"), strtok(NULL, " \n"), message);
            }
        } else if (strcmp(operation, "-bagi") == 0) {
            if (num2 == 0) {
                printf("ERROR\n");
                exit(EXIT_FAILURE);
            } else {
                result = floor((float)num1 / num2);
                numberToWords(result, message);
                printf("hasil pembagian %s dan %s adalah %s.\n", strtok(input, " \n"), strtok(NULL, " \n"), message);
            }
        } else {
            printf("Invalid operation\n");
            exit(EXIT_FAILURE);
        }

        // Buka file log
        FILE *logFile = fopen("histori.log", "a");
        if (logFile == NULL) {
            perror("histori.log");
            exit(EXIT_FAILURE);
        }

        // Tulis log
        char date[20];
        time_t t = time(NULL);
        strftime(date, sizeof(date), "%d/%m/%y %H:%M:%S", localtime(&t));
        fprintf(logFile, "[%s] ", date);
        if (strcmp(operation, "-kali") == 0)
            fprintf(logFile, "[KALI] ");
        else if (strcmp(operation, "-tambah") == 0)
            fprintf(logFile, "[TAMBAH] ");
        else if (strcmp(operation, "-kurang") == 0)
            fprintf(logFile, "[KURANG] ");
        else if (strcmp(operation, "-bagi") == 0)
            fprintf(logFile, "[BAGI] ");
        fprintf(logFile, "%s %s %s adalah %s.\n", strtok(input, " \n"), operation + 1, strtok(NULL, " \n"), message);

        // Tutup file log
        fclose(logFile);

        // Tutup file descriptor
        close(pipefd[0]);
    }

    return 0;
}

