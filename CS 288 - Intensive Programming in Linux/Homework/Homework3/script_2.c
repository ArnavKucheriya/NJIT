// Arnav Kucheriya - script_2.c

#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

static void print_byte(int idx, unsigned b) {
    printf("Byte %d: Hex: 0x%02X Char: ", idx, b);
    if (isprint(b)) printf("%c\n", (char)b);
    else            printf("\\%u\n", b);
}

int main(void) {
    const char *path = "./matrix.bin";
    FILE *fp = fopen(path, "rb");
    if (!fp) { perror("matrix.bin"); return 1; }

    uint32_t x;
    while (fread(&x, sizeof(uint32_t), 1, fp) == 1) {
        // Print the whole integer (hex & decimal)
        printf("Integer: Hex: 0x%08X Dec: %u\n", x, x);

        // Print bytes in MSB -> LSB order, per assignment
        unsigned b1 = (x >> 24) & 0xFF;  // most significant byte
        unsigned b2 = (x >> 16) & 0xFF;
        unsigned b3 = (x >>  8) & 0xFF;
        unsigned b4 = (x      ) & 0xFF;  // least significant byte

        print_byte(1, b1);
        print_byte(2, b2);
        print_byte(3, b3);
        print_byte(4, b4);
    }

    if (!feof(fp)) { fprintf(stderr, "Read error before EOF.\n"); fclose(fp); return 1; }
    fclose(fp);
    return 0;
}
