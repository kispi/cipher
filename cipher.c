#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int BYTE_MAX = 255;

void write_bytes(int value, int num_bytes) {
    FILE* fp = fopen("NONAME", "ab");
    for (int i = 0; i < num_bytes; i++) {
        int num_to_write = value;
        if (value == -1) {
            num_to_write = rand() % (BYTE_MAX + 1);
        }
        fwrite(&num_to_write, 1, 1, fp);
    }
    fclose(fp);
}

void doThreePass() {
    clock_t t;
    t = clock();

    write_bytes(0, 100);
    double elapsed_time = ((double)(clock() - t) / CLOCKS_PER_SEC);
    printf("Elapsed Time (Zero Fill): %f\n", elapsed_time);

    write_bytes(BYTE_MAX, 100);
    elapsed_time = ((double)(clock() - t) / CLOCKS_PER_SEC);
    printf("Elapsed Time (Complementary Fill): %f\n", elapsed_time);

    write_bytes(-1, 100);
    elapsed_time = ((double)(clock() - t) / CLOCKS_PER_SEC);
    printf("Elapsed Time (Random Byte Fill): %f\n", elapsed_time);
}

int main() {
    srand(time(NULL));
    doThreePass();

    return 0;
}
