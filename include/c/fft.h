#include <define.h>
#include <osapi.h>
#include <type.h>

dlimport complex *fft(complex *s, size_t l, bool r);
dlimport double  *fft_r2r(double *s, size_t l, bool r);
dlimport complex *fft_r2c(double *s, size_t l);
dlimport double  *fft_c2r(complex *s, size_t l);
