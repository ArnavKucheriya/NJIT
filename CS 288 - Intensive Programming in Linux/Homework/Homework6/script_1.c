#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define PTR_BYTES 8   // print 8 bytes per line (64-bit pointers)

void print_pointer_bytes(const char *label, void *address_of_var) {
    unsigned char *p = (unsigned char *)address_of_var;

    // print label (argv or argv[i])
    printf("%-7s| ", label);

    // print bytes in MSB-left order
    for (int i = PTR_BYTES - 1; i >= 0; --i) {
        printf("%02hhx ", *(p + i));
    }

    // show address of the pointer variable
    printf("| %p\n", address_of_var);
}

int main(int argc, char *argv[]) {

    print_pointer_bytes("argv", (void *)&argv);

    printf("\n\n");

    for (int i = 0; i < argc; ++i) {
        char label[32];
        snprintf(label, sizeof(label), "argv[%d]", i);
        print_pointer_bytes(label, (void *)&argv[i]);
    }

    printf("\n\n");

    unsigned char *min_ptr = (unsigned char *)argv[0];
    unsigned char *max_end = (unsigned char *)argv[0] + strlen(argv[0]) + 1;

    for (int i = 1; i < argc; ++i) {
        unsigned char *p = (unsigned char *)argv[i];
        if (p < min_ptr) min_ptr = p;
        unsigned char *end = p + strlen(argv[i]) + 1;
        if (end > max_end) max_end = end;
    }

    // align 8-byte boundaries
    uintptr_t start_addr = (uintptr_t)min_ptr & ~((uintptr_t)0x7);
    uintptr_t end_addr   = ((uintptr_t)max_end + 7) & ~((uintptr_t)0x7);

    // print 8 bytes per line
    unsigned char *ptr = (unsigned char *)start_addr;
    for (; (uintptr_t)ptr < end_addr; ptr += PTR_BYTES) {

        printf("        |");

        // print 8 bytes in MSB-left order
        for (int i = PTR_BYTES - 1; i >= 0; --i) {
            unsigned char c = *(ptr + i);

            printf("%02hhx(", c);

            if (isprint(c)) printf("%c", c);
            else if (c == '\0') printf("\\0");
            else printf("\\x%02x", c);

            printf(")  ");
        }

        printf("|%p\n", (void *)ptr);
    }

    return 0;
}
