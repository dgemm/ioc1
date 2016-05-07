
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include <stdint.h>

#define long_t int64_t
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
  // Constants
  const double phi_d = (1.0 + sqrt(5.0))/2.0;
  const double bottom_inv = 1.0/(2.0*phi_d - 1.0);

  const double top_left = pow(phi_d, n);
  const double top_right = pow(1.0 - phi_d, n);

  const double result = (top_left - top_right)*bottom_inv;

  return result;
}


void test(void)
{
  const int max = 20000;

  for (int kk = 0; kk <= max; kk++) {
    const long_t result_iter = fib_iter(kk);
    const long_t result_g = fib_g(kk);

    // How far to overflow?
    const double frac = ((double) result_iter)/long_t_max;

    printf("%d: %lld, %lld (%.10lf)\n", kk, result_iter, result_g, frac);

    assert(result_iter == result_g);
  }
}


int main()
{
  assert(sizeof(long_t) == sizeof(double));

  test();

  return 0;
}

