#include <check.h>
#include <metaresc.h>
#include <regression.h>

#include <int.h>

TYPEDEF_STRUCT (struct_uint32_t, uint32_t x)
TYPEDEF_STRUCT (struct_int32_t, int32_t x)

START_TEST (zero_u_int32_t) { ALL_METHODS (ASSERT_SAVE_LOAD_INT, 32, 0); } END_TEST
START_TEST (all_bits_u_int32_t) { ALL_METHODS (ASSERT_SAVE_LOAD_INT, 32, -1); } END_TEST
START_TEST (max_signed_u_int32_t) { ALL_METHODS (ASSERT_SAVE_LOAD_INT, 32, (1ULL << (32 - 1)) - 1); } END_TEST
START_TEST (min_signed_u_int32_t) { ALL_METHODS (ASSERT_SAVE_LOAD_INT, 32, (1ULL << (32 - 1))); } END_TEST
START_TEST (random_u_int32_t) { ALL_METHODS (ASSERT_SAVE_LOAD_INT, 32, 0x12345678); } END_TEST

MAIN_TEST_SUITE ((zero_u_int32_t, "zero [u]int32_t"),
		 (all_bits_u_int32_t, "all bits set [u]int32_t"),
		 (max_signed_u_int32_t, "max signed [u]int32_t"),
		 (min_signed_u_int32_t, "min signed [u]int32_t"),
		 (random_u_int32_t, "random [u]int32_t")
		 );
