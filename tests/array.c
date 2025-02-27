#include <check.h>
#include <metaresc.h>
#include <regression.h>

TYPEDEF_ENUM (packed_enum_t, ATTRIBUTES (__attribute__ ((packed))), ZERO, ONE, TWO, THREE)
TYPEDEF_STRUCT (char_array_t, (char, x, [2]))
TYPEDEF_STRUCT (packed_enum_array_t, (packed_enum_t, x, [2]))
TYPEDEF_STRUCT (int8_array_t, (int8_t, x, [2]))
TYPEDEF_STRUCT (int16_array_t, (int16_t, x, [2]))
TYPEDEF_STRUCT (int32_array_t, (int32_t, x, [2]))
TYPEDEF_STRUCT (int64_array_t, (int64_t, x, [2]))
TYPEDEF_STRUCT (float_array_t, (float, x, [2]))
TYPEDEF_STRUCT (double_array_t, (double, x, [2]))
TYPEDEF_STRUCT (ld_array_t, (long double, x, [2]))
TYPEDEF_STRUCT (string_array_t, (string_t, x, [2]))
TYPEDEF_STRUCT (packed_enum_array2d_t, (packed_enum_t, x, [2][2]))
TYPEDEF_STRUCT (string_array2d_t, (string_t, x, [2][2]))
TYPEDEF_STRUCT (int_array2d_t, (int, x, [2][2]))

TYPEDEF_STRUCT (int_ptr_array_t, (int *, x, [2]))
TYPEDEF_STRUCT (enum_ptr_array_t, (packed_enum_t *, x, [2]))

TYPEDEF_UNION (union_int32_float_t, float _float, int32_t _int32)

TYPEDEF_ENUM (discriminator_t,
	      (UD_FLOAT, , "_float"),
	      (UD_INT32, , "_int32"),
	      )

TYPEDEF_STRUCT (union_ptr_array_t,
		(union_int32_float_t *, x, [2], "discriminator"),
		(discriminator_t, discriminator)
		)

#define OVERRIDE				\
  (mr_ud_override_t[]){				\
    {UD_FLOAT, "_int32"},			\
      {UD_INT32, "_float"},			\
	}

TYPEDEF_STRUCT (ud_overrided_ptr_array_t,
		(union_int32_float_t *, x, [2], "discriminator", { OVERRIDE }, "mr_ud_override_t", sizeof (OVERRIDE)),
		(discriminator_t, discriminator)
		)

#define ASSERT_SAVE_LOAD_ARRAY(METHOD, TYPE, ...) ({	\
      TYPE x = { { 1, 2 } };				\
      ASSERT_SAVE_LOAD (METHOD, TYPE, &x, __VA_ARGS__);	\
    })

START_TEST (numeric_array_int8) { ALL_METHODS (ASSERT_SAVE_LOAD_ARRAY, int8_array_t); } END_TEST
START_TEST (numeric_array_int16) { ALL_METHODS (ASSERT_SAVE_LOAD_ARRAY, int16_array_t); } END_TEST
START_TEST (numeric_array_int32) { ALL_METHODS (ASSERT_SAVE_LOAD_ARRAY, int32_array_t); } END_TEST
START_TEST (numeric_array_int64) { ALL_METHODS (ASSERT_SAVE_LOAD_ARRAY, int64_array_t); } END_TEST
START_TEST (numeric_array_float) { ALL_METHODS (ASSERT_SAVE_LOAD_ARRAY, float_array_t); } END_TEST
START_TEST (numeric_array_double) { ALL_METHODS (ASSERT_SAVE_LOAD_ARRAY, double_array_t); } END_TEST
START_TEST (numeric_array_long_double) { ALL_METHODS (ASSERT_SAVE_LOAD_ARRAY, ld_array_t); } END_TEST

START_TEST (char_array) {
  char_array_t orig = { { 'a', 'b' }, };
  ALL_METHODS (ASSERT_SAVE_LOAD, char_array_t, &orig);
} END_TEST

START_TEST (enum_array) {
  packed_enum_array_t orig = { { ONE, TWO }, };
  ALL_METHODS (ASSERT_SAVE_LOAD, packed_enum_array_t, &orig);
} END_TEST

START_TEST (string_array) {
  string_array_t orig = { { "ONE", "TWO" }, };
  ALL_METHODS (ASSERT_SAVE_LOAD, string_array_t, &orig);
} END_TEST

START_TEST (two_dimensional_array_enum) {
  packed_enum_array2d_t packed_enum_array2d = { { { ZERO, ONE, }, { TWO, THREE, }, } };
  ALL_METHODS (ASSERT_SAVE_LOAD, packed_enum_array2d_t, &packed_enum_array2d);
} END_TEST

START_TEST (two_dimensional_array_string) {
  string_array2d_t string_array2d = { { { "ZERO", "ONE", }, { "TWO", "THREE", }, } };
  ALL_METHODS (ASSERT_SAVE_LOAD, string_array2d_t, &string_array2d);
} END_TEST

START_TEST (two_dimensional_array_duplicated_strings) {
  string_array2d_t string_array2d_duplicate = { { { "ZERO", "ONE", }, { "ZERO", "ONE", }, } };
  ALL_METHODS (ASSERT_SAVE_LOAD, string_array2d_t, &string_array2d_duplicate);
} END_TEST

START_TEST (two_dimensional_array_int) {
  int_array2d_t int_array2d = { { { 0, 1, }, { 2, 3, }, } };
  ALL_METHODS (ASSERT_SAVE_LOAD, int_array2d_t, &int_array2d);
} END_TEST

static void
mr_ra_ptrdes_eq (mr_ra_ptrdes_t * ptrs, mr_ptrdes_t * expected, size_t expected_size)
{
  ck_assert_msg (ptrs->size == expected_size, "size mismatch %zd != %zd", ptrs->size, expected_size);
  int i, count = expected_size / sizeof (*expected);
  for (i = 0; i < count; ++i)
    {
      ck_assert_msg (strcmp (ptrs->ra[i].tdp->type.str, expected[i].tdp->type.str) == 0,
		     "[%d] type %s != %s", i, ptrs->ra[i].tdp->type.str, expected[i].tdp->type.str);
      ck_assert_msg (strcmp (ptrs->ra[i].name, expected[i].name) == 0,
		     "[%d] type %s != %s", i, ptrs->ra[i].name, expected[i].name);
      ck_assert_msg (ptrs->ra[i].mr_type == expected[i].mr_type,
		     "[%d] type %d != %d", i, ptrs->ra[i].mr_type, expected[i].mr_type);
      ck_assert_msg (ptrs->ra[i].first_child == expected[i].first_child,
		     "[%d] type %d != %d", i, ptrs->ra[i].first_child, expected[i].first_child);
      ck_assert_msg (ptrs->ra[i].next == expected[i].next,
		     "[%d] type %d != %d", i, ptrs->ra[i].next, expected[i].next);
    }
}

#define ASSERT_MR_SAVE(TYPE, S_PTR, EXPECTED) ({			\
      mr_ra_ptrdes_t ptrs = MR_SAVE (TYPE, S_PTR);			\
      ck_assert_msg (ptrs.ra != NULL, "Failed to MR_SAVE");		\
      mr_ra_ptrdes_eq (&ptrs, EXPECTED, sizeof (EXPECTED));		\
      MR_FREE (ptrs.ra);						\
    })

START_TEST (int_ptr_array)
{
  int_ptr_array_t orig = { { (int[]){ 0x12345678 }, NULL } };
  mr_ptrdes_t expected[] =
    {
      {
	.tdp = (mr_td_t[]){{ .type = { "int_ptr_array_t" }}},
	.name = "orig",
	.mr_type = MR_TYPE_STRUCT,
	.first_child = 1,
	.next = -1
      }
      ,
      {
	.tdp = (mr_td_t[]){{ .type = { "int" }}},
	.name = "x",
	.mr_type = MR_TYPE_ARRAY,
	.first_child = 2,
	.next = -1
      }
      ,
      {
	.tdp = (mr_td_t[]){{ .type = { "int" }}},
	.name = "x",
	.mr_type = MR_TYPE_POINTER,
	.first_child = 4,
	.next = 3
      }
      ,
      {
	.tdp = (mr_td_t[]){{ .type = { "int" }}},
	.name = "x",
	.mr_type = MR_TYPE_POINTER,
	.first_child = -1,
	.next = -1
      }
      ,
      {
	.tdp = (mr_td_t[]){{ .type = { "int" }}},
	.name = "x",
	.mr_type = MR_TYPE_INT32,
	.first_child = -1,
	.next = -1
      }
      ,
    };
  ASSERT_MR_SAVE (int_ptr_array_t, &orig, expected);
  ALL_METHODS (ASSERT_SAVE_LOAD, int_ptr_array_t, &orig);
} END_TEST

START_TEST (enum_ptr_array)
{
  enum_ptr_array_t orig = { { (packed_enum_t[]){ TWO }, NULL } };
  mr_ptrdes_t expected[] =
    {
      {
	.tdp = (mr_td_t[]){{ .type = { "enum_ptr_array_t" }}},
	.name = "orig",
	.mr_type = MR_TYPE_STRUCT,
	.first_child = 1,
	.next = -1
      }
      ,
      {
	.tdp = (mr_td_t[]){{ .type = { "packed_enum_t" }}},
	.name = "x",
	.mr_type = MR_TYPE_ARRAY,
	.first_child = 2,
	.next = -1
      }
      ,
      {
	.tdp = (mr_td_t[]){{ .type = { "packed_enum_t" }}},
	.name = "x",
	.mr_type = MR_TYPE_POINTER,
	.first_child = 4,
	.next = 3
      }
      ,
      {
	.tdp = (mr_td_t[]){{ .type = { "packed_enum_t" }}},
	.name = "x",
	.mr_type = MR_TYPE_POINTER,
	.first_child = -1,
	.next = -1
      }
      ,
      {
	.tdp = (mr_td_t[]){{ .type = { "packed_enum_t" }}},
	.name = "x",
	.mr_type = MR_TYPE_ENUM,
	.first_child = -1,
	.next = -1
      }
      ,
    };
  ASSERT_MR_SAVE (enum_ptr_array_t, &orig, expected);
  ALL_METHODS (ASSERT_SAVE_LOAD, enum_ptr_array_t, &orig);
} END_TEST

START_TEST (union_ptr_array)
{
  union_ptr_array_t orig = { { (union_int32_float_t[]){ { ._float = 1.2345678 } }, NULL }, UD_FLOAT };
  mr_ptrdes_t expected[] =
    {
      {
	.tdp = (mr_td_t[]){{ .type = { "union_ptr_array_t" }}},
	.name = "orig",
	.mr_type = MR_TYPE_STRUCT,
	.first_child = 1,
	.next = -1
      }
      ,
      {
	.tdp = (mr_td_t[]){{ .type = { "union_int32_float_t" }}},
	.name = "x",
	.mr_type = MR_TYPE_ARRAY,
	.first_child = 2,
	.next = 4
      }
      ,
      {
	.tdp = (mr_td_t[]){{ .type = { "union_int32_float_t" }}},
	.name = "x",
	.mr_type = MR_TYPE_POINTER,
	.first_child = 5,
	.next = 3
      }
      ,
      {
	.tdp = (mr_td_t[]){{ .type = { "union_int32_float_t" }}},
	.name = "x",
	.mr_type = MR_TYPE_POINTER,
	.first_child = -1,
	.next = -1
      }
      ,
      {
	.tdp = (mr_td_t[]){{ .type = { "discriminator_t" }}},
	.name = "discriminator",
	.mr_type = MR_TYPE_ENUM,
	.first_child = -1,
	.next = -1
      }
      ,
      {
	.tdp = (mr_td_t[]){{ .type = { "union_int32_float_t" }}},
	.name = "x",
	.mr_type = MR_TYPE_UNION,
	.first_child = 6,
	.next = -1
      }
      ,
      {
	.tdp = (mr_td_t[]){{ .type = { "float" }}},
	.name = "_float",
	.mr_type = MR_TYPE_FLOAT,
	.first_child = -1,
	.next = -1
      }
      ,
    };      
  ASSERT_MR_SAVE (union_ptr_array_t, &orig, expected);
  ALL_METHODS (ASSERT_SAVE_LOAD, union_ptr_array_t, &orig);
} END_TEST

START_TEST (ud_overrided_ptr_array)
{
  ud_overrided_ptr_array_t orig = { { (union_int32_float_t[]){ { ._float = 1.2345678 } }, NULL }, UD_INT32 };
  mr_ptrdes_t expected[] =
    {
      {
	.tdp = (mr_td_t[]){{ .type = { "ud_overrided_ptr_array_t" }}},
	.name = "orig",
	.mr_type = MR_TYPE_STRUCT,
	.first_child = 1,
	.next = -1
      }
      ,
      {
	.tdp = (mr_td_t[]){{ .type = { "union_int32_float_t" }}},
	.name = "x",
	.mr_type = MR_TYPE_ARRAY,
	.first_child = 2,
	.next = 4
      }
      ,
      {
	.tdp = (mr_td_t[]){{ .type = { "union_int32_float_t" }}},
	.name = "x",
	.mr_type = MR_TYPE_POINTER,
	.first_child = 5,
	.next = 3
      }
      ,
      {
	.tdp = (mr_td_t[]){{ .type = { "union_int32_float_t" }}},
	.name = "x",
	.mr_type = MR_TYPE_POINTER,
	.first_child = -1,
	.next = -1
      }
      ,
      {
	.tdp = (mr_td_t[]){{ .type = { "discriminator_t" }}},
	.name = "discriminator",
	.mr_type = MR_TYPE_ENUM,
	.first_child = -1,
	.next = -1
      }
      ,
      {
	.tdp = (mr_td_t[]){{ .type = { "union_int32_float_t" }}},
	.name = "x",
	.mr_type = MR_TYPE_UNION,
	.first_child = 6,
	.next = -1
      }
      ,
      {
	.tdp = (mr_td_t[]){{ .type = { "float" }}},
	.name = "_float",
	.mr_type = MR_TYPE_FLOAT,
	.first_child = -1,
	.next = -1
      }
      ,
    };      
  ASSERT_MR_SAVE (ud_overrided_ptr_array_t, &orig, expected);
  ALL_METHODS (ASSERT_SAVE_LOAD, ud_overrided_ptr_array_t, &orig);
} END_TEST

MAIN_TEST_SUITE ((numeric_array_int8, "array of numerics"),
		 (numeric_array_int16, "array of numerics"),
		 (numeric_array_int32, "array of numerics"),
		 (numeric_array_int64, "array of numerics"),
		 (numeric_array_float, "array of numerics"),
		 (numeric_array_double, "array of numerics"),
		 (numeric_array_long_double, "array of numerics"),
		 (char_array, "array of chars"),
		 (enum_array, "array of enums"),
		 (string_array, "array of strings"),
		 (two_dimensional_array_enum, "array2d"),
		 (two_dimensional_array_string, "array2d"),
		 (two_dimensional_array_duplicated_strings, "array2d"),
		 (two_dimensional_array_int, "array2d"),
		 (int_ptr_array, "array of int pointers"),
		 (enum_ptr_array, "array of pointers on enums"),
		 (union_ptr_array, "array of union pointers"),
		 (ud_overrided_ptr_array, "array of union pointers with overrides")
		 );
