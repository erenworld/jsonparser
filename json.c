#include "json.h"

JSON_OBJECT *parseJSON(string json_string) 
{
    int offset = 0;
    JSON_OBJECT *temp_obj = _parseJSON(json_string, &offset);

    return temp_obj;
}

static int str_next_occurence(string str, char ch)
{
    int pos = 0;

    if (str == NULL) {
        return -1;
    }

    while (*str != ch && *str != '\0') {
        str++;
        pos++;
    }

    return (*str == '\0') ? -1 : pos;
}

void freeJSON(JSON_OBJECT *obj) {
    int i;

    if (obj == NULL) {
        return;
    }

    if (obj->pairs == NULL) {
        free(obj);
        return;
    }

    for (i = 0; i < obj->count; i++) {
        if (obj->pairs[i].key != NULL)
            free(obj->pairs[i].key);
        
        if (obj->pairs[i].value != NULL) {
            switch (obj->pairs[i].type) {
                case JSON_STRING:
                    free(obj->pairs[i].value->string_value);
                    break;
                case JSON_OBJECT_VALUE:
                    free(obj->pairs[i].value->json_object);
            }
            free(obj->pairs[i].value);
        }
    }
}

int main() 
{
    printf("Welcome to Jason!\n");

    return 0;
}