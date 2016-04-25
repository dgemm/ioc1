
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>

#define T long long int

T fib_iter(int n) {
  assert(n >= 0);

  if (n == 0) return 0;
  if (n == 1) return 1;

  T prevPrev = 0;
  T prev = 1;
  T result = 0;

  for (int i = 2; i <= n; i++)
  {
      result = prev + prevPrev;
      prevPrev = prev;
      prev = result;
  }

  return result;
}





double fib_g(int n) {



  const double phi_d = (1.0 + sqrt(5.0))/2.0;

  const double top_left = pow(phi_d, n);
  const double top_right = pow(1.0 - phi_d, n);

  const double bottom = 2.0*phi_d - 1.0;

  const double result = (top_left - top_right)/bottom;





  const double bias = 2.3461048565937045e-15;

  const double offset = result*bias;
  
  const double offset_result = result - offset;




  const double rounded = floor(offset_result + 0.1);

  printf("\n");
  printf("Result %lf\n", result);
  printf("Offset %lf\n", offset);
  printf("Offset result %lf\n", offset_result);

  return rounded;

}





void test(void)
{
  const int max = 20000;

  for (int kk = 0; kk <= max; kk++) {
    const T result_iter = fib_iter(kk);
    const double result_g = fib_g(kk);

    printf("%d: %lld, %lf (%lld)\n", kk, result_iter, result_g, (T) result_g);

    assert(result_iter == (T) result_g);
  }
}


int main()
{
  assert(sizeof(T) == sizeof(int64_t));
  assert(sizeof(T) == sizeof(double));

  test();

  return 0;
}

