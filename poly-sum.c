#include <gmp.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  uint32_t deg;
  mpq_t coeff[];
} Poly;

static void *safe_malloc(size_t n) {
  void *ptr = malloc(n);
  if (!ptr) {
    perror("malloc failed");
    exit(EXIT_FAILURE);
  }
  return ptr;
}

static Poly *new_poly(uint32_t deg) {
  Poly *p = safe_malloc(sizeof(Poly) + (deg + 1) * sizeof p->coeff[0]);
  p->deg = deg;
  for (uint32_t i = 0; i <= deg; i++)
    mpq_init(p->coeff[i]);
  return p;
}

static void destroy_poly(Poly *p) {
  for (uint32_t i = 0; i <= p->deg; i++)
    mpq_clear(p->coeff[i]);
  free(p);
}

static void eval_poly(mpq_t out, const Poly *p, const mpq_t x) {
  uint32_t n = p->deg;
  mpq_set(out, p->coeff[n]);
  while (n--) {
    mpq_mul(out, out, x);
    mpq_add(out, out, p->coeff[n]);
  }
}

// p *= (X + z)
static void add_lin_coeff(Poly *p, mpq_t z) {
  for (uint32_t i = p->deg; i > 0; i--) {
    mpq_mul(p->coeff[i], z, p->coeff[i]);
    mpq_add(p->coeff[i], p->coeff[i], p->coeff[i - 1]);
  }
  mpq_mul(p->coeff[0], z, p->coeff[0]);
}

static Poly *poly_sum(const Poly *p) {
  uint32_t r = p->deg;
  mpq_t q1;
  mpq_init(q1);

  mpq_t *pt = safe_malloc((r + 1) * sizeof pt[0]);
  mpq_t *fac = safe_malloc((r + 1) * sizeof fac[0]);
  mpq_init(fac[0]);
  mpq_set_ui(fac[0], 1, 1);
  for (uint32_t k = 0; k <= r; k++) {
    mpq_set_ui(q1, k, 1);
    mpq_init(pt[k]);
    eval_poly(pt[k], p, q1);
    if (k > 0) {
      mpq_init(fac[k]);
      mpq_mul(fac[k], q1, fac[k - 1]);
    }
  }

  mpq_t *d = safe_malloc((r + 1) * sizeof d[0]);
  for (uint32_t i = 0; i <= r; i++) {
    mpq_init(d[i]);
    for (uint32_t k = 0; k <= i; k++) {
      mpq_inv(q1, fac[k]);
      mpq_div(q1, q1, fac[i - k]);
      mpq_mul(q1, q1, pt[k]);
      if ((i - k) % 2 == 0)
        mpq_add(d[i], d[i], q1);
      else
        mpq_sub(d[i], d[i], q1);
    }
    mpq_set_ui(q1, i + 1, 1);
    mpq_div(d[i], d[i], q1);
  }
  for (uint32_t i = 0; i <= r; i++) {
    mpq_clear(pt[i]);
    mpq_clear(fac[i]);
  }
  free(pt);
  free(fac);

  Poly *q = new_poly(r + 1);
  for (int32_t i = r; i >= 0; i--) {
    mpq_add(q->coeff[0], q->coeff[0], d[i]);
    mpq_set_si(q1, 1 - i, 1);
    add_lin_coeff(q, q1);
  }
  for (uint32_t i = 0; i <= r; i++)
    mpq_clear(d[i]);
  free(d);
  mpq_clear(q1);

  return q;
}

int main(void) {
  uint32_t r;
  int ret = scanf("%" PRIu32 "\n", &r);
  if (ret == EOF && ferror(stdin)) {
    perror("scanf failed");
    return EXIT_FAILURE;
  } else if (ret != 1) {
    fprintf(stderr, "expected a degree (non-negative integer).\n");
    return EXIT_FAILURE;
  }
  Poly *p = new_poly(r);
  for (uint32_t i = 0; i <= r; i++) {
    ret = gmp_scanf("%Qd\n", p->coeff[i]);
    if (ret == EOF && ferror(stdin)) {
      perror("gmp_scanf failed");
      return EXIT_FAILURE;
    } else if (ret != 1) {
      fprintf(stderr,
              "expected the coefficient p_%" PRIu32 " (rational number)\n", i);
      return EXIT_FAILURE;
    }
  }
  Poly *q = poly_sum(p);
  destroy_poly(p);
  printf("%" PRIu32 "\n", q->deg);
  for (uint32_t i = 0; i <= q->deg; i++)
    gmp_printf("%Qd\n", q->coeff[i]);
  destroy_poly(q);
  return EXIT_SUCCESS;
}
