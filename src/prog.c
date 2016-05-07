
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <quadmath.h>

#define long_t uint64_t
#define long_t_max (INT64_MAX)

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


long_t fib_g(int n) {
  // Constants (128 bit)
  const __float128 one_q = 1.0Q;
  const __float128 two_q = 2.0Q;
  const __float128 five_q = 5.0Q;

  const __float128 phi_q = (one_q + sqrtq(five_q))/two_q;
  const __float128 bottom_inv = one_q/(two_q*phi_q - one_q);

  const __float128 top_left = powq(phi_q, n);
  const __float128 top_right = powq(one_q - phi_q, n);

  const __float128 result = (top_left - top_right)*bottom_inv;

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
  assert(sizeof(long_t) == sizeof(double));

  test();

  return 0;
}

