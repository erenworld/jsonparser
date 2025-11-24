#ifndef JSON_H
#define JSON_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef char*                               string;

#ifndef __cplusplus
typedef unsigned char                       bool;
#define true                                (1)    
#define false                               (0)
#define TRUE                                true
#define FALSE                               false
#endif 

#define new(x)                              (x *) malloc(sizeof(x))
#define new_with_size(x, y)                 (x *) malloc(y * sizeof(x))
#define renew_with_size(x, y, z)            (y *) realloc(x, z * sizeof(y))
#define is_white_space(x)                   x == '\r' || x == ' ' || x == '\t' || x == '\n'
#define remove_white_space(x)               while(is_white_space(*x)) x++
#define remove_white_space_offset(x, y)     while(is_white_space(*x)) { x++; y++; }

typedef char                                character;

struct json_object;
struct json_pair;
union  json_value;

typedef enum {
    JSON_STRING_VALUE = 0,
    JSON_OBJECT_VALUE
} JSON_VALUE_TYPE;

typedef struct json_object {
    struct json_pair *pairs;
    int count;
} JSON_OBJECT;

typedef struct json_pair {
    string key;
    union json_value *value;
    JSON_VALUE_TYPE type;
} JSON_PAIR;

typedef union json_value {
    string string_value;
    struct json_object *json_object;
} JSON_VALUE;

#endif 