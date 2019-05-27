struct persoana_t {
	size_t id;
	char *nume;
	char *nr_telefon;
	char *email;
};

typedef struct persoana_t persoana_t;
typedef persoana_t *p_persoana_t;

p_persoana_t new_persoana(size_t id, const char* nume, const char* nr_telefon, const char* email);
void delete_persoana(p_persoana_t p);

// returns -1 on error, 0 on success and 1 on success but with eof
int read_persoana(int fd, p_persoana_t *_persoana);

// returns 0 or non-zero error-code
int write_persoana(int fd, p_persoana_t persoana);
