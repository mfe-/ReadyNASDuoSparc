/*
 * sdiv-test.c - compares the hardware SPARC V8 "sdiv" instruction with a
 * software reference on random operands. On the ReadyNAS NV+ v1 (IT3107)
 * sdiv returns results that are off by 1..2 for some negative dividends,
 * while udiv/umul/smul are correct.
 *
 * Build (whole program as v7, only the inline asm uses sdiv):
 *   sparc-linux-gcc -O2 -mcpu=v7 -static -o sdiv-test sdiv-test.c
 * Run it on the real NAS. QEMU's qemu-sparc also miscomputes sdiv with
 * negative operands, so emulator results are meaningless.
 */
#include <stdio.h>
#include <stdlib.h>

static int hw_sdiv(int a, int b)
{
    int q;
    __asm__ volatile(
        "wr   %1, 0, %%y\n\t"        /* Y = upper 32 bits of the dividend (sign) */
        "nop\n\tnop\n\tnop\n\t"      /* Y write delay */
        "sdiv %2, %3, %0\n\t"
        : "=r"(q) : "r"(a >> 31), "r"(a), "r"(b));
    return q;
}

static int sw_sdiv(int a, int b)
{
    unsigned ua = a < 0 ? 0u - (unsigned)a : (unsigned)a;
    unsigned ub = b < 0 ? 0u - (unsigned)b : (unsigned)b;
    unsigned q = ua / ub;                    /* v7: .udiv, known good */
    return ((a < 0) != (b < 0)) ? -(int)q : (int)q;
}

static unsigned rng = 2463534242u;
static unsigned xorshift(void)
{
    rng ^= rng << 13; rng ^= rng >> 17; rng ^= rng << 5;
    return rng;
}

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 500000, i, err = 0;
    for (i = 0; i < n; i++) {
        int a = (int)xorshift(), b;
        do {    /* mix of small and large divisors */
            b = (int)xorshift() >> (xorshift() % 31);
        } while (b == 0 || (a == (int)0x80000000 && b == -1));
        if (hw_sdiv(a, b) != sw_sdiv(a, b)) {
            if (err < 10)
                printf("SDIV %d/%d  hw=%d  sw=%d\n", a, b, hw_sdiv(a, b), sw_sdiv(a, b));
            err++;
        }
    }
    printf("Tests: %ld  sdiv errors: %ld\n", n, err);
    return err != 0;
}
