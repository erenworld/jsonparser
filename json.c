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

int main() 
{
    printf("Welcome to Jason!\n");

    return 0;
}