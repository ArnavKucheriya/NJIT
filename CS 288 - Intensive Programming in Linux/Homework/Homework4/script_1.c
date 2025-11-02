#include <stdio.h>
#include <stdint.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    if (n < 0) n = 0;
    if (n > 100) n = 100;

    int32_t a[100], b[100];
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) { n = i; break; }
    }

    // Map signed to unsigned order by flipping the sign bit
    for (int i = 0; i < n; i++) a[i] ^= 0x80000000u;

    int32_t *src = a, *dst = b;

    // 8 passes 4 bits per pass
    for (int pass = 0; pass < 8; pass++) {
        int count[16] = {0};

        // Count digits
        for (int i = 0; i < n; i++) {
            unsigned d = (unsigned)(src[i] >> (pass * 4)) & 0xF;
            count[d]++;
        }
        // Prefix sums
        for (int d = 1; d < 16; d++) count[d] += count[d - 1];

        // Stable placement into dst
        for (int i = n - 1; i >= 0; i--) {
            unsigned d = (unsigned)(src[i] >> (pass * 4)) & 0xF;
            dst[--count[d]] = src[i];
        }

        int32_t *tmp = src; src = dst; dst = tmp;
    }

    // Flip sign bit
    for (int i = 0; i < n; i++) {
        int32_t val = src[i] ^ 0x80000000u;
        printf("%d\n", val);
    }
    return 0;
}
