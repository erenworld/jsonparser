# jsonparser

Json parser in C

## Features

- Structured Data (JSONObject, JSONPair, JSONValue)
- Recursive JSON parsing
- Count of key-value pairs of current JSON

## Usage

```c

#include "json.h"

int main()
{
    const char *json_string = "{\"hello\":\"world\",\"key\":\"value\"}";

    json_object *json = parse_json(json_string);
    if (json == NULL) {
        return -1;
    }

    printf("Count: %i\n", json->count);
    
}

```
