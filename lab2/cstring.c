#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "cstring.h"

#define INITIAL_CAPACITY 20

p_cstring_t initialize(p_cstring_t str) {
    str->size = 0;
    str->capacity = INITIAL_CAPACITY;
    str->data = (char*)malloc(str->capacity * sizeof(char));
    memset(str->data, 0, str->capacity * sizeof(char));

    return str;
}

p_cstring_t new_string() {
    return initialize((p_cstring_t)malloc(sizeof(cstring_t)));
}

void string_clear(p_cstring_t str) {
    free(str->data);
    initialize(str);
}

void delete_string(p_cstring_t str) {
    free(str->data);
    free(str);
}

static void scale_to_capacity(p_cstring_t str) {
    str->data = (char*)realloc(str->data, str->capacity * sizeof(char));
}

static void resize_up(p_cstring_t str) {
    str->capacity *= 2;
    scale_to_capacity(str);
}

static void resize_down(p_cstring_t str) {
    str->capacity /= 2;
    scale_to_capacity(str);
}

static void resize_if_needed(p_cstring_t str) {
    if (str->size + 1 == str->capacity)
        resize_up(str);
    else if (str->capacity > 20 && (str->size +1) * 2 <= str->capacity)
        resize_down(str);
}

static int append(p_cstring_t str, char *ot, size_t ot_len) {
    size_t space_needed = ot_len - (str->capacity - (str->size + 1));
    if (space_needed > 0) {
        str->capacity += space_needed;
        scale_to_capacity(str);
    }
    strcat(str->data + str->size, ot);
    str->size += ot_len;
    return 0;
}

int string_append_raw(p_cstring_t str, char* ot, size_t ot_len) {
    return append(str, ot, ot_len);
}

int string_append_c(p_cstring_t str, char * ot) {
    return append(str, ot, strlen(ot));
}

int string_append(p_cstring_t str, p_cstring_t ot) {
    return append(str, ot->data, ot->size);
}

int string_append_char(p_cstring_t str, char c) {
    resize_if_needed(str);
    str->data[str->size] = c;
    str->size++;
    str->data[str->size] = 0;
    return 0;
}

int string_truncate(p_cstring_t str, size_t len) {
    if (len >= str-> size)
        return -1;
    str->size = len;
    str->data[str->size] = 0;
    resize_if_needed(str);
    return 0;
}

int string_shift_left(p_cstring_t str, size_t ammount) {
    if (ammount >= str->size) {
        string_clear(str);
        return 0;
    }

    str->size = str->size - ammount;
    str->data = (char*)memmove(str->data, str->data + ammount, str->size + 1);
    resize_if_needed(str);
    return 0;
}
