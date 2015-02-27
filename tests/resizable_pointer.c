#include <check.h>
#include <metaresc.h>
#include <regression.h>

#define CMP_RPTR(TYPE, X, Y, ...) (((X)->size != (Y)->size) || memcmp ((X)->data, (Y)->data, (X)->size))

/********************************************************************************************************/

TYPEDEF_STRUCT (resizable_array_t,
		(int8_t *, data, , , { "size" }, "char"),
		int size,
		);

MR_START_TEST (resizable_array, "test pointer as a resizable array casted by name of size field as char[]") {
  resizable_array_t orig = 
    {
      .data = (__typeof__ (orig.data[0])[]){ -1, 1, },
      .size = 2 * sizeof (orig.data[0]),
    };
  ALL_METHODS (ASSERT_SAVE_LOAD, resizable_array_t, &orig, CMP_RPTR);
} END_TEST

/********************************************************************************************************/

TYPEDEF_STRUCT (resizable_array_size_as_bool_t,
		(int8_t *, data, , , { "size" }, "char"),
		bool size,
		);

MR_START_TEST (resizable_array_size_as_bool, "test pointer as a resizable array with size typed as bool") {
  resizable_array_size_as_bool_t orig = 
    {
      .data = (__typeof__ (orig.data[0])[]){ -1, },
      .size = 1,
    };
  ALL_METHODS (ASSERT_SAVE_LOAD, resizable_array_size_as_bool_t, &orig, CMP_RPTR);
} END_TEST

/********************************************************************************************************/

TYPEDEF_STRUCT (resizable_array_size_as_int8_t,
		(int8_t *, data, , , { "size" }, "char"),
		int8_t size,
		);

MR_START_TEST (resizable_array_size_as_int8, "test pointer as a resizable array with size typed as int8_t") {
  resizable_array_size_as_int8_t orig = 
    {
      .data = (__typeof__ (orig.data[0])[]){ -1, 1, },
      .size = 2 * sizeof (orig.data[0]),
    };
  ALL_METHODS (ASSERT_SAVE_LOAD, resizable_array_size_as_int8_t, &orig, CMP_RPTR);
} END_TEST

/********************************************************************************************************/

TYPEDEF_STRUCT (resizable_array_size_as_int16_t,
		(int8_t *, data, , , { "size" }, "char"),
		int16_t size,
		);

MR_START_TEST (resizable_array_size_as_int16, "test pointer as a resizable array with size typed as int16_t") {
  resizable_array_size_as_int16_t orig = 
    {
      .data = (__typeof__ (orig.data[0])[]){ -1, 1, },
      .size = 2 * sizeof (orig.data[0]),
    };
  ALL_METHODS (ASSERT_SAVE_LOAD, resizable_array_size_as_int16_t, &orig, CMP_RPTR);
} END_TEST

/********************************************************************************************************/

TYPEDEF_STRUCT (resizable_array_size_as_int32_t,
		(int8_t *, data, , , { "size" }, "char"),
		int32_t size,
		);

MR_START_TEST (resizable_array_size_as_int32, "test pointer as a resizable array with size typed as int32_t") {
  resizable_array_size_as_int32_t orig = 
    {
      .data = (__typeof__ (orig.data[0])[]){ -1, 1, },
      .size = 2 * sizeof (orig.data[0]),
    };
  ALL_METHODS (ASSERT_SAVE_LOAD, resizable_array_size_as_int32_t, &orig, CMP_RPTR);
} END_TEST

/********************************************************************************************************/

TYPEDEF_STRUCT (resizable_array_size_as_int64_t,
		(int8_t *, data, , , { "size" }, "char"),
		int64_t size,
		);

MR_START_TEST (resizable_array_size_as_int64, "test pointer as a resizable array with size typed as int64_t") {
  resizable_array_size_as_int64_t orig = 
    {
      .data = (__typeof__ (orig.data[0])[]){ -1, 1, },
      .size = 2 * sizeof (orig.data[0]),
    };
  ALL_METHODS (ASSERT_SAVE_LOAD, resizable_array_size_as_int64_t, &orig, CMP_RPTR);
} END_TEST

/********************************************************************************************************/

TYPEDEF_STRUCT (resizable_array_size_as_bitfield_t,
		(int8_t *, data, , , { "size" }, "char"),
		BITFIELD (int8_t, size, :3),
		);

MR_START_TEST (resizable_array_size_as_bitfield, "test pointer as a resizable array with size typed as bitfield") {
  resizable_array_size_as_bitfield_t orig = 
    {
      .data = (__typeof__ (orig.data[0])[]){ -1, 1, },
      .size = 2 * sizeof (orig.data[0]),
    };
  ALL_METHODS (ASSERT_SAVE_LOAD, resizable_array_size_as_bitfield_t, &orig, CMP_RPTR);
} END_TEST

/********************************************************************************************************/

TYPEDEF_ENUM (array_size_t,
	      (ZERO, = 0),
	      (ONE, = sizeof (int8_t)),
	      (TWO, = 2 * sizeof (int8_t)),
	      );

TYPEDEF_STRUCT (resizable_array_size_as_enum_t,
		(int8_t *, data, , , { "size" }, "char"),
		(array_size_t, size),
		);

MR_START_TEST (resizable_array_size_as_enum, "test pointer as a resizable array with size typed as enum") {
  resizable_array_size_as_enum_t orig = 
    {
      .data = (__typeof__ (orig.data[0])[]){ -1, 1, },
      .size = TWO,
    };
  ALL_METHODS (ASSERT_SAVE_LOAD, resizable_array_size_as_enum_t, &orig, CMP_RPTR);
} END_TEST

/********************************************************************************************************/

#define CMP_RPTR_SIZEPTR(TYPE, X, Y, ...) ((*(X)->size != *(Y)->size) || memcmp ((X)->data, (Y)->data, *(X)->size))

TYPEDEF_STRUCT (resizable_array_size_as_int_ptr_t,
		(int8_t *, data, , , { "size" }, "char"),
		(int *, size),
		);

MR_START_TEST (resizable_array_size_as_int_ptr, "test pointer as a resizable array with size typed as pointer to int") {
  resizable_array_size_as_int_ptr_t orig = 
    {
      .data = (__typeof__ (orig.data[0])[]){ -1, 1, },
      .size = (int[]) { 2 * sizeof (orig.data[0]) },
    };
  ALL_METHODS (ASSERT_SAVE_LOAD, resizable_array_size_as_int_ptr_t, &orig, CMP_RPTR_SIZEPTR);
} END_TEST

  /********************************************************************************************************/

TYPEDEF_STRUCT (resizable_array_without_size_t,
		(int8_t *, data, , , { "size" }, "char"),
		VOID (int, size),
		);

MR_START_TEST (resizable_array_without_size, "test pointer as a resizable array with non-serializable size casted by size as a string") {
  resizable_array_without_size_t orig = 
    {
      .data = (__typeof__ (orig.data[0])[]){ -1, 1, },
      .size = 2 * sizeof (orig.data[0]),
    };
  ALL_METHODS (ASSERT_SAVE_LOAD, resizable_array_without_size_t, &orig, CMP_RPTR);
} END_TEST

  /********************************************************************************************************/

TYPEDEF_STRUCT (resizable_array_casted_by_offset_t,
		(int8_t *, data, , , { .offset = offsetof (resizable_array_casted_by_offset_t, size) }, "offset"),
		int size,
		);

MR_START_TEST (resizable_array_casted_by_offset, "test pointer as a resizable array casted by offset of the size field") {
  resizable_array_casted_by_offset_t orig = 
    {
      .data = (__typeof__ (orig.data[0])[]){ -1, 1, },
      .size = 2 * sizeof (orig.data[0]),
    };
  ALL_METHODS (ASSERT_SAVE_LOAD, resizable_array_casted_by_offset_t, &orig, CMP_RPTR);
} END_TEST

  /********************************************************************************************************/

TYPEDEF_STRUCT (resizable_array_without_size_casted_by_offset_t,
		(int8_t *, data, , , { .offset = offsetof (resizable_array_without_size_casted_by_offset_t, size) }, "offset"),
		VOID (int, size),
		);

MR_START_TEST (resizable_array_without_size_casted_by_offset, "test pointer as a resizable array with non-serializable size casted by offset of the size field") {
  resizable_array_without_size_casted_by_offset_t orig = 
    {
      .data = (__typeof__ (orig.data[0])[]){ -1, 1, },
      .size = 2 * sizeof (orig.data[0]),
    };
  ALL_METHODS (ASSERT_SAVE_LOAD, resizable_array_without_size_casted_by_offset_t, &orig, CMP_RPTR);
} END_TEST

  /********************************************************************************************************/

TYPEDEF_STRUCT (resizable_array_casted_by_string_t,
		(int8_t *, data, , , { "size" }, "string"),
		int size,
		);

MR_START_TEST (resizable_array_casted_by_string, "test pointer as a resizable array casted by name of the size field as string") {
  resizable_array_casted_by_string_t orig = 
    {
      .data = (__typeof__ (orig.data[0])[]){ -1, 1, },
      .size = 2 * sizeof (orig.data[0]),
    };
  ALL_METHODS (ASSERT_SAVE_LOAD, resizable_array_casted_by_string_t, &orig, CMP_RPTR);
} END_TEST

  /********************************************************************************************************/

TYPEDEF_STRUCT (resizable_array_without_size_casted_by_string_t,
		(int8_t *, data, , , { "size" }, "string"),
		VOID (int, size),
		);

MR_START_TEST (resizable_array_without_size_casted_by_string, "test pointer as a resizable array with non-serializable size casted by name of the size field as string") {
  resizable_array_without_size_casted_by_string_t orig = 
    {
      .data = (__typeof__ (orig.data[0])[]){ -1, 1, },
      .size = 2 * sizeof (orig.data[0]),
    };
  ALL_METHODS (ASSERT_SAVE_LOAD, resizable_array_without_size_casted_by_string_t, &orig, CMP_RPTR);
} END_TEST

  /********************************************************************************************************/

TYPEDEF_STRUCT (resizable_mr_ptr_t,
		(mr_ptr_t, data, , "dynamic_type"),
		int MR_SIZE,
		(char *, dynamic_type),
		);

MR_START_TEST (resizable_mr_ptr, "test mr_ptr_t as a resizable array") {
  resizable_mr_ptr_t orig = 
    {
      .data = { (resizable_mr_ptr_t[]){ { { NULL }, 0, "mr_ptr_t", }, { { NULL }, 0, "string_t", }, } },
      .MR_SIZE = 2 * sizeof (resizable_mr_ptr_t),
      .dynamic_type = "resizable_mr_ptr_t",
    };
  ALL_METHODS (ASSERT_SAVE_LOAD, resizable_mr_ptr_t, &orig);
} END_TEST

  /********************************************************************************************************/

#undef TEST_METHODS
#define TEST_METHODS XDR

#define CMP_OPAQUE_DATA(TYPE, X, Y, ...) CMP_SERIALIAZED (resizable_array_t, ((resizable_array_t*)X), ((resizable_array_t*)Y), __VA_ARGS__)

TYPEDEF_STRUCT (resizable_array_as_opaque_data_t,
		(int8_t *, MR_OPAQUE_DATA, , , { "size" }, "char"),
		VOID (int, size),
		);

MR_START_TEST (resizable_array_as_opaque_data, "test pointer as a resizable array as opaque data") {
  resizable_array_as_opaque_data_t orig = 
    {
      .MR_OPAQUE_DATA = (__typeof__ (orig.MR_OPAQUE_DATA[0])[]){ -1, 1, },
      .size = 2 * sizeof (orig.MR_OPAQUE_DATA[0]),
    };
  ALL_METHODS (ASSERT_SAVE_LOAD, resizable_array_as_opaque_data_t, &orig, CMP_OPAQUE_DATA);
} END_TEST

  /********************************************************************************************************/

MAIN ();
