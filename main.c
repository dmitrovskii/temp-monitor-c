#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void clear(int value) {
    for (int i = 0; i < value; i++) {
        printf("\x1b[1A\x1b[2K");
    }
    fflush(stdout);
}

double temperature() {
    FILE *fptr;
    int raw_temp;
    
    fptr = fopen("/sys/class/thermal/thermal_zone2/temp", "r");

    if (fptr == NULL) {
        printf("Error open file!\n");
        return -1.0; 
    }

    fscanf(fptr, "%d", &raw_temp);
    fclose(fptr);

    return raw_temp / 1000.0;
}

int main() {

    while (1) {

        double value = temperature();

        if (value != -1.0) {
            printf("TEMP: %.2f°C\n", value);
        }

        fflush(stdout);
        sleep(1);
        clear(1);
    }

    return 0;
}