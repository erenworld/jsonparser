#include <criterion/criterion.h>
#include "../json.h"

// Test simple key/value parse
Test(json_tests, parse_simple_json) {
    string input = "{\"name\":\"Alice\"}";

    JSON_OBJECT *obj = parseJSON(input);

    cr_assert_not_null(obj, "parseJSON returned NULL");

    cr_assert_eq(obj->count, 1, "Expected one key/value pair");

    cr_assert_str_eq(obj->pairs[0].key, "name");
    cr_assert_eq(obj->pairs[0].type, JSON_STRING_VALUE);
    cr_assert_str_eq(obj->pairs[0].value->string_value, "Alice");

    freeJSON(obj);
}

// Test two keys
Test(json_tests, parse_two_values) {
    string input = "{\"name\":\"Alice\",\"city\":\"NYC\"}";

    JSON_OBJECT *obj = parseJSON(input);
    cr_assert_not_null(obj);

    cr_assert_eq(obj->count, 2);

    cr_assert_str_eq(obj->pairs[0].key, "name");
    cr_assert_str_eq(obj->pairs[0].value->string_value, "Alice");

    cr_assert_str_eq(obj->pairs[1].key, "city");
    cr_assert_str_eq(obj->pairs[1].value->string_value, "NYC");

    freeJSON(obj);
}

// Test malformed JSON (your code should fail)
Test(json_tests, malformed_json_returns_null) {
    string bad = "{\"name\":\"Alice\",\"city\":\"NYC\"}}";  // extra }

    JSON_OBJECT *obj = parseJSON(bad);

    cr_assert_null(obj, "Parser should return NULL on malformed JSON");
}
