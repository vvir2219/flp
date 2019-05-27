#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "cpersoana.h"
#include "cstring.h"
#include "cfileutils.h" // cfileutils trebuie sa fie dupa cstring intotdeauna

static char *copy_str(const char *input) {
	char *str = (char*)malloc(sizeof(char) * (strlen(input) + 1));
	return strcpy(str, input);
}

p_persoana_t new_persoana(size_t id, const char* nume, const char* nr_telefon, const char* email) {
	p_persoana_t pers = (p_persoana_t)malloc(sizeof(persoana_t));
	pers->id = id;
	pers->nume = copy_str(nume);
	pers->nr_telefon = copy_str(nr_telefon);
	pers->email = copy_str(email);

	return pers;
}
void delete_persoana(p_persoana_t p) {
	free(p->nume);
	free(p->nr_telefon);
	free(p->email);
	free(p);
}

static int next_token(char *start, int c, char **next) {
    *next = strchr(start, c);
    if (!*next) {
        return -1;
    }

    **next = 0;
    (*next) ++;
    return 0;
}

// returns -1 on error, 0 on success and 1 on success but with eof
int read_persoana(int fd, p_persoana_t *_persoana) {
    p_cstring_t tempstr;

	int retcode = read_line(fd, &tempstr);
    int err = 0;
    if (retcode >= 0) {
        char *start = tempstr->data;
        char *stop, *nume, *nr_telefon, *email;
        size_t id;

        err = next_token(start, ';', &stop);
        if (err) goto out;
        sscanf(start, "%lu", &id);
        start = stop;

        err = next_token(start, ';', &stop);
        if (err) goto out;
        nume = start;
        start = stop;

        err = next_token(start, ';', &stop);
        if (err) goto out;
        nr_telefon = start;
        start = stop;

        err = next_token(start, ';', &stop);
        if (err) goto out;
        email = start;
        start = stop;
        
        // aci am o persoana pe bucati
        *_persoana = new_persoana(id, nume, nr_telefon, email);
    }
out:
    delete_string(tempstr);
    if (err) retcode = err;
    return retcode;
}

// returns 0 or non-zero error-code
int write_persoana(int fd, p_persoana_t persoana) {
	p_cstring_t buf = new_string();
	char temp[sizeof(persoana->id) * ((CHAR_BIT + 2) / 3)];
	sprintf(temp, "%lu", persoana->id);

	string_append_c(buf, temp);
	string_append_char(buf, ';');


	string_append_c(buf, persoana->nume);
	string_append_char(buf, ';');
	
	string_append_c(buf, persoana->nr_telefon);
	string_append_char(buf, ';');

	string_append_c(buf, persoana->email);
	string_append_char(buf, ';');

	int retval = write(fd, buf->data, buf->size);

	delete_string(buf);
	return retval;
}
