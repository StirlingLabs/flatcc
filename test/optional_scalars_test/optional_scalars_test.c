#include <assert.h>
#include <stdio.h>

#include "optional_scalars_test_builder.h"
#include "optional_scalars_test_json_printer.h"


#undef ns
#define ns(x) FLATBUFFERS_WRAP_NAMESPACE(optional_scalars, x)

// #define TEST_ASSERT

#ifdef TEST_ASSERT
#define test_assert(x) do { if (!(x)) { assert(0); return -1; }} while(0)
#else
#define test_assert(x) do { if (!(x)) { return -1; }} while(0)
#endif

int create_scalar_stuff(flatcc_builder_t *B)
{
    ns(ScalarStuff_start_as_root(B));

    ns(ScalarStuff_just_i8_add(B, 10));
    ns(ScalarStuff_maybe_i8_add(B, 11));
    ns(ScalarStuff_default_i8_add(B, 12));

    ns(ScalarStuff_just_i16_add(B, 42));
    ns(ScalarStuff_maybe_i16_add(B, 42));
    ns(ScalarStuff_default_i16_add(B, 42));

    ns(ScalarStuff_just_u32_add(B, 0));
    ns(ScalarStuff_maybe_u32_add(B, 0));
    ns(ScalarStuff_default_u32_add(B, 0));

    ns(ScalarStuff_just_f32_add(B, 42));
    ns(ScalarStuff_maybe_f32_add(B, 42));
    ns(ScalarStuff_default_f32_add(B, 42));

    ns(ScalarStuff_just_bool_add(B, 1));
    ns(ScalarStuff_maybe_bool_add(B, 1));
    ns(ScalarStuff_default_bool_add(B, 1));

    ns(ScalarStuff_just_enum_add)(B, ns(OptionalByte_One));
    ns(ScalarStuff_maybe_enum_add)(B, ns(OptionalByte_One));
    ns(ScalarStuff_default_enum_add)(B, ns(OptionalByte_One));

    ns(ScalarStuff_end_as_root(B));

    return 0;
}

int access_scalar_stuff(const void *buffer)
{
    ns(ScalarStuff_table_t) t = ns(ScalarStuff_as_root(buffer));
    flatbuffers_int8_option_t maybe_i8;
    flatbuffers_int16_option_t maybe_i16;
    flatbuffers_uint32_option_t maybe_u32;
    flatbuffers_uint8_option_t maybe_u8;
    flatbuffers_float_option_t maybe_f32;
    flatbuffers_bool_option_t maybe_bool;
    ns(OptionalByte_option_t) maybe_enum;

    test_assert(10 == ns(ScalarStuff_just_i8_get(t)));
    test_assert(11 == ns(ScalarStuff_maybe_i8_get(t)));
    test_assert(12 == ns(ScalarStuff_default_i8_get(t)));
    maybe_i8 = ns(ScalarStuff_maybe_i8_option(t));
    test_assert(!maybe_i8.is_null);
    test_assert(11 == maybe_i8.value);
    test_assert(ns(ScalarStuff_just_i8_is_present(t)));
    test_assert(ns(ScalarStuff_maybe_i8_is_present(t)));
    test_assert(ns(ScalarStuff_default_i8_is_present(t)));

    test_assert(0 == ns(ScalarStuff_just_u8_get(t)));
    test_assert(0 == ns(ScalarStuff_maybe_u8_get(t)));
    test_assert(42 == ns(ScalarStuff_default_u8_get(t)));
    maybe_u8 = ns(ScalarStuff_maybe_u8_option(t));
    test_assert(maybe_u8.is_null);
    test_assert(0 == maybe_u8.value);
    test_assert(!ns(ScalarStuff_just_u8_is_present(t)));
    test_assert(!ns(ScalarStuff_maybe_u8_is_present(t)));
    test_assert(!ns(ScalarStuff_default_u8_is_present(t)));

    test_assert(42 == ns(ScalarStuff_just_i16_get(t)));
    test_assert(42 == ns(ScalarStuff_maybe_i16_get(t)));
    test_assert(42 == ns(ScalarStuff_default_i16_get(t)));
    maybe_i16 = ns(ScalarStuff_maybe_i16_option(t));
    test_assert(!maybe_i16.is_null);
    test_assert(42 == maybe_i16.value);
    test_assert(ns(ScalarStuff_just_i16_is_present(t)));
    test_assert(ns(ScalarStuff_maybe_i16_is_present(t)));
    test_assert(!ns(ScalarStuff_default_i16_is_present(t)));

    test_assert(0 == ns(ScalarStuff_just_u32_get(t)));
    test_assert(0 == ns(ScalarStuff_maybe_u32_get(t)));
    test_assert(0 == ns(ScalarStuff_default_u32_get(t)));
    maybe_u32 = ns(ScalarStuff_maybe_u32_option(t));
    test_assert(!maybe_u32.is_null);
    test_assert(0 == maybe_u32.value);
    test_assert(!ns(ScalarStuff_just_u32_is_present(t)));
    test_assert(ns(ScalarStuff_maybe_u32_is_present(t)));
    test_assert(ns(ScalarStuff_default_u32_is_present(t)));

    test_assert(42 == ns(ScalarStuff_just_f32_get(t)));
    test_assert(42 == ns(ScalarStuff_maybe_f32_get(t)));
    test_assert(42 == ns(ScalarStuff_default_f32_get(t)));
    maybe_f32 = ns(ScalarStuff_maybe_f32_option(t));
    test_assert(!maybe_f32.is_null);
    test_assert(42 == maybe_f32.value);
    test_assert(ns(ScalarStuff_just_f32_is_present(t)));
    test_assert(ns(ScalarStuff_maybe_f32_is_present(t)));
    test_assert(!ns(ScalarStuff_default_f32_is_present(t)));

    test_assert(1 == ns(ScalarStuff_just_bool_get(t)));
    test_assert(1 == ns(ScalarStuff_maybe_bool_get(t)));
    test_assert(1 == ns(ScalarStuff_default_bool_get(t)));
    maybe_bool = ns(ScalarStuff_maybe_bool_option(t));
    test_assert(!maybe_bool.is_null);
    test_assert(1 == maybe_bool.value);
    test_assert(ns(ScalarStuff_just_bool_is_present(t)));
    test_assert(ns(ScalarStuff_maybe_bool_is_present(t)));
    test_assert(!ns(ScalarStuff_default_bool_is_present(t)));

    test_assert(1 == ns(ScalarStuff_just_enum_get(t)));
    maybe_enum = ns(ScalarStuff_maybe_enum_option(t));
    test_assert(1 == ns(ScalarStuff_default_enum_get(t)));
    test_assert(!maybe_enum.is_null);
    test_assert(maybe_enum.value == 1);
    test_assert(ns(ScalarStuff_just_enum_is_present(t)));
    test_assert(ns(ScalarStuff_maybe_enum_is_present(t)));
    test_assert(!ns(ScalarStuff_default_enum_is_present(t)));

    return 0;
}

int test()
{
    flatcc_builder_t builder;
    void  *buf;
    size_t size;

    flatcc_builder_init(&builder);
    test_assert(0 == create_scalar_stuff(&builder));
    buf = flatcc_builder_finalize_aligned_buffer(&builder, &size);
    test_assert(0 == access_scalar_stuff(buf));
    flatcc_builder_aligned_free(buf);
    flatcc_builder_clear(&builder);

    return 0;
}

const char *expected_json =
"{\"just_i8\":10,\"maybe_i8\":11,\"default_i8\":12,\"just_i16\":42,\"maybe_i16\":42,\"maybe_u32\":0,\"default_u32\":0,\"just_f32\":42,\"maybe_f32\":42,\"just_bool\":true,\"maybe_bool\":true,\"just_enum\":\"One\",\"maybe_enum\":\"One\"}";

int test_json()
{
    flatcc_builder_t builder;
    void  *buf;
    size_t size;
    flatcc_json_printer_t printer;
    char *json_buf;
    size_t json_size;

    flatcc_builder_init(&builder);
    test_assert(0 == create_scalar_stuff(&builder));
    buf = flatcc_builder_finalize_aligned_buffer(&builder, &size);
    test_assert(0 == access_scalar_stuff(buf));
    flatcc_builder_clear(&builder);
    flatcc_json_printer_init_dynamic_buffer(&printer, 0);
    test_assert(ns(ScalarStuff_print_json_as_root)(&printer, buf, size, NULL));
    flatcc_builder_aligned_free(buf);
    json_buf = flatcc_json_printer_get_buffer(&printer, &json_size);
    printf("%.*s\n", (int)json_size, json_buf);
    test_assert(strlen(expected_json) == json_size);
    test_assert(0 == memcmp(expected_json, json_buf, json_size));
    flatcc_json_printer_clear(&printer);
    return 0;
}

int main(int argc, char *argv[])
{
    /* Silence warnings. */
    (void)argc;
    (void)argv;

    if (test()) {
        printf("optional scalars test failed");
        return 1;
    }
    if (test_json()) {
        printf("optional scalars json test failed");
        return 1;
    }
    printf("optional scalars test passed");
    return 0;
}
