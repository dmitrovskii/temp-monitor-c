#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct TempStats {
    float current;
    float average;
    float min;
    float max;
};

void clear_string(int value) {
    for (int i = 0; i < value; i++) {
        printf("\x1b[1A\x1b[2K");
    }
    fflush(stdout);
}

void save_logs(struct TempStats data[], int count) {
    FILE *fptr;
    fptr = fopen("logs.txt", "a");

    if (fptr == NULL) {
        printf("Error open file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fptr, "TEMP: %.2f | AVG: %.2f | MIN: %.2f | MAX: %.2f\n", 
            data[i].current,
            data[i].average,
            data[i].min,
            data[i].max);
    }
    fclose(fptr);
}

double get_temperature() {
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

        double value = get_temperature();

        if (value != -1.0) {
            printf("TEMP: %.2f°C\n", value);
        }

        fflush(stdout);
        sleep(1);
        clear_string(1);
    }

    return 0;
}