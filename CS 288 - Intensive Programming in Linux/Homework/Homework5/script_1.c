#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Convert float to 32-bit unsigned and back (bitwise)
static inline uint32_t float_to_u32(float f) {
    uint32_t u; memcpy(&u, &f, sizeof(u)); return u;
}
static inline float u32_to_float(uint32_t u) {
    float f; memcpy(&f, &u, sizeof(f)); return f;
}

int main(void) {
    size_t n;
    if (scanf("%zu", &n) != 1) return 0;

    uint32_t *src = malloc(n * sizeof(uint32_t));
    uint32_t *dst = malloc(n * sizeof(uint32_t));
    if (!src || !dst) return 0;

    // Read floats and transform to sortable unsigned ints
    for (size_t i = 0; i < n; ++i) {
        float f;
        if (scanf("%f", &f) != 1) { n = i; break; }
        uint32_t b = float_to_u32(f);
        // Flip sign bit for proper total ordering
        src[i] = (b & 0x80000000u) ? (b ^ 0xFFFFFFFFu) : (b ^ 0x80000000u);
    }

    // Radix sort: 8 passes (4 bits per pass, 16 buckets)
    for (int pass = 0; pass < 8; ++pass) {
        unsigned count[16] = {0};
        for (size_t i = 0; i < n; ++i)
            count[(src[i] >> (pass * 4)) & 0xF]++;

        size_t start[16];
        start[0] = 0;
        for (int d = 1; d < 16; ++d)
            start[d] = start[d - 1] + count[d - 1];

        uint32_t *ptrs[16];
        for (int d = 0; d < 16; ++d)
            ptrs[d] = dst + start[d];

        // Place elements into buffer using pointer array
        for (size_t i = 0; i < n; ++i) {
            unsigned d = (src[i] >> (pass * 4)) & 0xF;
            *ptrs[d]++ = src[i];
        }

        uint32_t *tmp = src; src = dst; dst = tmp;
    }

    // Reverse bit transform and print sorted floats
    for (size_t i = 0; i < n; ++i) {
        uint32_t k = src[i];
        uint32_t b = (k & 0x80000000u) ? (k ^ 0x80000000u) : (k ^ 0xFFFFFFFFu);
        printf("%.9g\n", u32_to_float(b));
    }

    free(src);
    free(dst);
    return 0;
}
