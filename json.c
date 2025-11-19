#include "json.h"

JSON_OBJECT *parseJSON(string json_string) {
    int32_t offset = 0;
    JSON_OBJECT *temp_obj = _parseJSON(json_string, &offset);

    return temp_obj;
}

int main() {
    printf("Welcome to Jason!\n");

    return 0;
}