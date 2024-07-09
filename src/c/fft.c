#include <c.h>
#include <define.h>
#include <osapi.h>
#include <type.h>

static complex   fft_wn[64] = {};
static complex   aft_wn[64] = {};
static atom bool fft_inited = false;

static void fft_init() {
  if (atom_tas(&fft_inited)) return;
  double n = 1;
  for (int i = 0; i < 64; i++) {
    complex x  = 6.283185307179586232i * n;
    fft_wn[i]  = __builtin_cexp(x);
    aft_wn[i]  = __builtin_cexp(-x);
    n         *= .5;
  }
}

#define bit_rev(n) (bit_reverse((u64)(n)) >> (64 - log_n))

complex *fft(complex *s, size_t l, bool r) {
  if (!fft_inited) fft_init();

  int    log_n = 64 - clz(l) - !(l & (l - 1));
  size_t n     = 1 << log_n;

  complex *x = malloc(n * sizeof(complex));

  for (int i = 0; i < l; i++)
    x[bit_rev(i)] = s[i];
  for (int i = l; i < n; i++)
    x[bit_rev(i)] = 0;

  complex *_wn = (r ? aft_wn : fft_wn);
  complex  w, wn;

  for (int s = 1; s <= log_n; s++) {
    int m = 1 << s;
    wn    = _wn[s];
    for (int k = 0; k < n; k += m) {
      w = 1;
      for (int j = 0; j < m / 2; j++) {
        complex t         = w * x[k + j + m / 2];
        complex u         = x[k + j];
        x[k + j]          = u + t;
        x[k + j + m / 2]  = u - t;
        w                *= wn;
      }
    }
  }

  if (!r) {
    double d = 1. / n;
    for (int i = 0; i < n; i++)
      x[i] *= d;
  }

  return x;
}

double *fft_r2r(double *s, size_t l, bool r) {
  if (!fft_inited) fft_init();

  int    log_n = 64 - clz(l) - !(l & (l - 1));
  size_t n     = 1 << log_n;

  complex *x = malloc(n * sizeof(complex));

  if (!r) {
    for (int i = 0; i < l; i++)
      x[bit_rev(i)] = s[i];
    for (int i = l; i < n; i++)
      x[bit_rev(i)] = 0;
  } else {
    x[0] = s[0];
    x[1] = s[1];
    for (int i = 1; i < l / 2; i++)
      x[bit_rev(i)] = ((complex *)s)[i];
    for (int i = l / 2 + 1; i < n; i++)
      x[bit_rev(i)] = 0;
  }

  complex *_wn = (r ? aft_wn : fft_wn);
  complex  w, wn;

  for (int s = 1; s <= log_n; s++) {
    size_t m = 1 << s;
    wn       = _wn[s];
    for (size_t k = 0; k < n; k += m) {
      w = 1;
      for (size_t j = 0; j < m / 2; j++) {
        complex t         = w * x[k + j + m / 2];
        complex u         = x[k + j];
        x[k + j]          = u + t;
        x[k + j + m / 2]  = u - t;
        w                *= wn;
      }
    }
  }

  if (!r) {
    ((double *)x)[0] /= n;
    ((double *)x)[1]  = __real__ x[n / 2] / n;
    double d          = 2. / n;
    for (int i = 1; i < n / 2; i++)
      x[i] *= d;
  } else {
    double *y = (double *)x;
    for (int i = 0; i < n; i++)
      y[i] = __real__ x[i];
  }

  return (double *)x;
  // return realloc(x, n * sizeof(double));
}

complex *fft_r2c(double *s, size_t l) {
  if (!fft_inited) fft_init();

  int    log_n = 64 - clz(l) - !(l & (l - 1));
  size_t n     = 1 << log_n;

  complex *x = malloc(n * sizeof(complex));

  for (int i = 0; i < l; i++)
    x[bit_rev(i)] = s[i];
  for (int i = l; i < n; i++)
    x[bit_rev(i)] = 0;

  complex w, wn;

  for (int s = 1; s <= log_n; s++) {
    int m = 1 << s;
    wn    = fft_wn[s];
    for (int k = 0; k < n; k += m) {
      w = 1;
      for (int j = 0; j < m / 2; j++) {
        complex t         = w * x[k + j + m / 2];
        complex u         = x[k + j];
        x[k + j]          = u + t;
        x[k + j + m / 2]  = u - t;
        w                *= wn;
      }
    }
  }

  x[0]     /= n;
  double d  = 2. / n;
  for (int i = 1; i < n / 2; i++)
    x[i] *= d;
  x[n / 2] /= n;

  return x;
}

double *fft_c2r(complex *s, size_t l) {
  if (!fft_inited) fft_init();

  int    log_n = 64 - clz(l) - !(l & (l - 1));
  size_t n     = 1 << log_n;

  complex *x = malloc(n * sizeof(complex));

  for (int i = 0; i <= l / 2; i++)
    x[bit_rev(i)] = s[i];
  for (int i = l / 2 + 1; i < n; i++)
    x[bit_rev(i)] = 0;

  complex w, wn;

  for (int s = 1; s <= log_n; s++) {
    int m = 1 << s;
    wn    = aft_wn[s];
    for (int k = 0; k < n; k += m) {
      w = 1;
      for (int j = 0; j < m / 2; j++) {
        complex t         = w * x[k + j + m / 2];
        complex u         = x[k + j];
        x[k + j]          = u + t;
        x[k + j + m / 2]  = u - t;
        w                *= wn;
      }
    }
  }

  double *y = (void *)x;
  for (int i = 1; i < n; i++)
    y[i] = __real__ x[i];

  return y;
}

#undef bit_rev
