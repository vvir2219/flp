struct cstring_t {
    char *data; // always a zero terminated string
    size_t size; // does not include null terminator
    size_t capacity; // all alocated size, includes all
};

typedef struct cstring_t cstring_t;
typedef cstring_t *p_cstring_t;

p_cstring_t new_string();
void delete_string(p_cstring_t str);

void string_clear(p_cstring_t str);

int string_append_raw(p_cstring_t str, char* ot, size_t ot_len);
int string_append(p_cstring_t str, p_cstring_t ot);
int string_append_c(p_cstring_t str, char * ot);
int string_append_char(p_cstring_t str, char c);

int string_truncate(p_cstring_t str, size_t len);
int string_shift_left(p_cstring_t str, size_t ammount);
