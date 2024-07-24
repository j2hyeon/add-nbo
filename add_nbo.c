#include <stdint.h>   // for uint32_t
#include <stdio.h>    // for printf, fopen, fread, fclose
#include <stdlib.h>   // for exit, EXIT_FAILURE, EXIT_SUCCESS


uint32_t my_ntohl(uint32_t net) {
    return ((net & 0xFF000000) >> 24) |
           ((net & 0x00FF0000) >> 8) |
           ((net & 0x0000FF00) << 8) |
           ((net & 0x000000FF) << 24);
}


uint32_t readFile(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "error: unable to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    uint32_t number;
    size_t bytesRead = fread(&number, sizeof(uint32_t), 1, fp);
    fclose(fp);

    if (bytesRead != 1) {
        fprintf(stderr, "error: unable to read 4 bytes from file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    return my_ntohl(number);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *fp1 = argv[1];
    const char *fp2 = argv[2];

    uint32_t num1 = readFile(fp1);
    uint32_t num2 = readFile(fp2);
    uint32_t sum = num1 + num2;

    printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n", num1, num1, num2, num2, sum, sum);

    return EXIT_SUCCESS;
}

