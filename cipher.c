#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int BYTE_MAX = 255;

void write_bytes(int value) {
    FILE* fp = fopen("NONAME", "wb"); // TODO: filename's better be UUIDV4 or sth like that in order to prevent deleting existing important user file.
    int written = -1;
    while (written != 0) {
        int num_to_write = value;
        if (value == -1) {
            num_to_write = rand() % (BYTE_MAX + 1);
        }
        written = fwrite(&num_to_write, 1, 1, fp);
    }
    fclose(fp);
}

void do_three_pass() {
    clock_t t;
    t = clock();

    write_bytes(0);
    double elapsed_time = ((double)(clock() - t) / CLOCKS_PER_SEC);
    printf("Elapsed Time (Zero Fill): %f\n", elapsed_time);

    write_bytes(BYTE_MAX);
    elapsed_time = ((double)(clock() - t) / CLOCKS_PER_SEC);
    printf("Elapsed Time (Complementary Fill): %f\n", elapsed_time);

    write_bytes(-1);
    elapsed_time = ((double)(clock() - t) / CLOCKS_PER_SEC);
    printf("Elapsed Time (Random Byte Fill): %f\n", elapsed_time);
}

int main() {
    srand(time(NULL));
    do_three_pass();

    return 0;
}
