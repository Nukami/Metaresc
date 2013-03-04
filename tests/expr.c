#include <math.h>
#include <complex.h>

#include <check.h>
#include <metaresc.h>
#include <regression.h>

#define ASSERT_LOAD_TYPE(METHOD, TYPE, VALUE)				\
  ck_assert_msg (((TYPE)(VALUE) == MR_LOAD_ ## METHOD (TYPE, #VALUE)),	\
		 "restored value mismatched original for method " #METHOD " on type " #TYPE)

MR_START_TEST (parse_bool_true, "parse bool TRUE = (0)") { ASSERT_LOAD_TYPE (CINIT, bool, TRUE); } END_TEST
MR_START_TEST (parse_int_zero, "parse int 1") { ASSERT_LOAD_TYPE (CINIT, int, 1); } END_TEST
MR_START_TEST (parse_int_paren, "parse int x = (1)") { ASSERT_LOAD_TYPE (CINIT, int, (1)); } END_TEST
MR_START_TEST (parse_int_sum, "parse int x = 1 + 1") { ASSERT_LOAD_TYPE (CINIT, int, 1 + 1); } END_TEST
MR_START_TEST (parse_complex_sum, "parse float complex x = 1 + 1i") { ASSERT_LOAD_TYPE (CINIT, complex float, 1 + 1i); } END_TEST

MAIN ();
