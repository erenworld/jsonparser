#include "json.h"

static JSON_OBJECT * _parseJSON(string str, int *offset);
static int str_next_occurence(string str, char ch);

JSON_OBJECT *parseJSON(string json_string) 
{
    int offset = 0;
    return _parseJSON(json_string, &offset);
}


static int str_next_occurence(string str, char ch)
{
    int pos = 0;

    if (!str) {
        return -1;
    }

    while (str[pos] != '\0' && str[pos] != ch) {
        pos++;
    }

    return (str[pos] == '\0') ? -1 : pos;
}

void freeJSON(JSON_OBJECT *obj)
{
    if (!obj) return;

    if (obj->pairs) {
        for (int i = 0; i < obj->count; i++) {

            if (obj->pairs[i].key)
                free(obj->pairs[i].key);

            if (obj->pairs[i].value) {
                switch (obj->pairs[i].type) {
                    case JSON_STRING_VALUE:
                        free(obj->pairs[i].value->string_value);
                        break;

                    case JSON_OBJECT_VALUE:
                        freeJSON(obj->pairs[i].value->json_object);
                        break;
                }
                free(obj->pairs[i].value);
            }
        }
        free(obj->pairs);
    }

    free(obj);
}

static JSON_OBJECT * _parseJSON(string str, int *offset)
{
    int _offset = 0;

    JSON_OBJECT *obj = new(JSON_OBJECT);
    obj->count = 1;
    obj->pairs = new_with_size(JSON_PAIR, 1);


    while (*str != '\0') {

        remove_white_space_offset(str, _offset);
        char c = *str;

        switch (c) {
            case '{':
                str++;
                _offset++;
                break;
            case '"': {
                str++;
                _offset++;
        
                int key_len = str_next_occurence(str, '"');
                if (key_len <= 0) {
                    freeJSON(obj);
                    return NULL;
                }
        
                JSON_PAIR *pair = &obj->pairs[obj->count - 1];
        
                pair->key = new_with_size(character, key_len + 1);
                memcpy(pair->key, str, key_len);
                pair->key[key_len] = '\0';
        
                str += key_len + 1;
                _offset += key_len + 1;
        
                remove_white_space_offset(str, _offset);
        
                if (*str != ':') {
                    printf("DEBUG: Expected ':' at offset %d\n", _offset);
                    freeJSON(obj);
                    return NULL;
                }
        
                str++;
                _offset++;
        
                remove_white_space_offset(str, _offset);
        
                if (*str == '{') {
        
                    pair->value = new(JSON_VALUE);
                    pair->type = JSON_OBJECT_VALUE;
        
                    int consumed = 0;
                    pair->value->json_object = _parseJSON(str, &consumed);
        
                    if (!pair->value->json_object) {
                        printf("DEBUG: Failed nested object at offset=%d\n", _offset);
                        freeJSON(obj);
                        return NULL;
                    }
        
                    str += consumed;
                    _offset += consumed;
                }
        
                else if (*str == '"') {
        
                    str++;
                    _offset++;
        
                    int val_len = str_next_occurence(str, '"');
                    if (val_len < 0) {
                        freeJSON(obj);
                        return NULL;
                    }
        
                    pair->value = new(JSON_VALUE);
                    pair->type = JSON_STRING_VALUE;
        
                    pair->value->string_value = new_with_size(character, val_len + 1);
                    memcpy(pair->value->string_value, str, val_len);
                    pair->value->string_value[val_len] = '\0';
        
                    str += val_len + 1;
                    _offset += val_len + 1;
                }
        
                obj->pairs[obj->count - 1] = *pair;
                break;
            }
            case ',':
                obj->count++;
                obj->pairs = renew_with_size(obj->pairs, JSON_PAIR, obj->count);
                str++;
                _offset++;
                break;
            case '}':
                *offset = _offset + 1;
                return obj;
            default:
                freeJSON(obj);
                return NULL;
        }
    }

    freeJSON(obj);
    return NULL;
}


int main()
{
    printf("Welcome to Jason!\n");

    string json_text = "{\"name\":\"Alice\",\"info\":{\"city\":\"NYC\"}}";

    JSON_OBJECT *root = parseJSON(json_text);

    if (!root) {
        printf("Parse error!\n");
        return 1;
    }


    for (int i = 0; i < root->count; i++) {
        printf("Key: %s\n", root->pairs[i].key);

        if (root->pairs[i].type == JSON_STRING_VALUE) {
            printf("  Value: \"%s\"\n", root->pairs[i].value->string_value);
        }
        else {
            JSON_OBJECT *sub = root->pairs[i].value->json_object;
            printf("  Value: <object with %d pairs>\n", sub->count);
            for (int j = 0; j < sub->count; j++) {
                printf("    %s : \"%s\"\n",
                    sub->pairs[j].key,
                    sub->pairs[j].value->string_value);
            }
        }
    }

    freeJSON(root);
    return 0;
}
