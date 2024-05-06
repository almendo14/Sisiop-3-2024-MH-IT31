#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "actions.c" // Include actions.c to use its functions

// Function to log the conversation
void log_conversation(const char* source, const char* command, const char* info) {
    FILE *fp = fopen("race.log", "a");
    if (fp != NULL) {
        fprintf(fp, "[%s] [%s]: [%s] [%s]\n", source, __DATE__, command, info);
        fclose(fp);
    }
}

/// Function to handle commands from driver.c
void handle_command(const char* command, const char* info) {
    char response[100];

    if (strcmp(command, "Gap") == 0) {
        float distance = atof(info);
        strcpy(response, gap(distance));
    } else if (strcmp(command, "Fuel") == 0) {
        float fuel_percentage = atof(info);
        strcpy(response, fuel(fuel_percentage));
    } else if (strcmp(command, "Tire") == 0) {
        int tire_usage = atoi(info);
        strcpy(response, tire(tire_usage));
    } else if (strcmp(command, "Tire Change") == 0) {
        // Salin nilai info ke dalam variabel yang dapat dimodifikasi
        char tire_type[20]; // Misalnya, alokasikan buffer untuk menyalin nilai info
        strcpy(tire_type, info); // Salin nilai info ke buffer
        strcpy(response, tire_change(tire_type)); // Gunakan buffer yang sudah dikopi
    } else {
        strcpy(response, "Invalid command");
    }

    printf("[Paddock] [%s]: [%s] [%s]\n", __DATE__, command, response);
    log_conversation("Paddock", command, response);


}

int main() {
    // Example command
    handle_command("Fuel", "55%");
    return 0;
}

