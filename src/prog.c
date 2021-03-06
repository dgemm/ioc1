
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <quadmath.h>

#define long_t uint64_t
#define long_t_max (UINT64_MAX)

long_t fib_iter(int n) {
  assert(n >= 0);

  if (n == 0) return 0;
  if (n == 1) return 1;

  long_t prevPrev = 0;
  long_t prev = 1;
  long_t result = 0;

  for (int i = 2; i <= n; i++) {
    result = prev + prevPrev;
    prevPrev = prev;
    prev = result;
  }

  return result;
}


static const uint32_t magic[] = {
  0xc0605cee, 0x7c15f39c, 0x79b97f4a, 0x3fff9e37,  // (1 + sqrt(phi))/2
  0x670094af, 0x93565294, 0x5c5bfedd, 0x3ffdc9f2,  // 1/(2*phi - 1)
  0x00000000, 0x00000000, 0x00000000, 0x3fff0000   // 1
};


// Uses __float128 operations:
//   - multiply
//   - subtract
//   - cast to long_t
long_t fib_g(int n) {
  // 128-bit constants
  const __float128 *phi = (__float128 *) &magic[0];
  const __float128 *bottom = (__float128 *) &magic[4];
  const __float128 *one = (__float128 *) &magic[8];

  __float128 top_left = *one;
  __float128 top_right = *one;

  for (int kk = 0; kk < n; kk++) {
    top_left = *phi * top_left;
    top_right = (*one - *phi) * top_right;
  }

  const __float128 result = *bottom * (top_left - top_right);

  return (long_t) result;
}


void test(void)
{
  const int max = 20000;

  for (int kk = 0; kk <= max; kk++) {
    const long_t result_iter = fib_iter(kk);
    const long_t result_g = fib_g(kk);

    // How far to overflow?
    const double frac = ((double) result_iter)/long_t_max;

    printf("%d: %llu, %llu (%.10lf)\n", kk, result_iter, result_g, frac);

    assert(result_iter == result_g);
  }
}


int main()
{
  test();
  return 0;
}

