#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include "cstring.h"
#include "cpersoana.h"
#include "cfileutils.h"


void test_strings()
{
    p_cstring_t str = new_string();
    p_cstring_t str2 = new_string();

    string_append_char(str, 'a');
    string_append_char(str, 'n');
    string_append_char(str, 'a');

    string_append_c(str2, " are mere");
    string_append(str, str2);

    printf("%s\n", str->data);

    string_clear(str);
    string_append_c(str, "ana are mereuntoahunthtunheonuuoeauoeaueoaueoauoauoeauoeaueoaueoauoauoeauoeaueoaueoauoauoeauoeaueoaueoauoauoeauoeaueoaueoauoaeeeee");
    printf("%s\n", str->data);

    string_truncate(str, strlen("ana are mere"));
    printf("%s\n", str->data);

    string_shift_left(str, strlen("ana "));
    printf("%s\n", str->data);

    string_append_c(str, " ana?");
    printf("%s\n", str->data);

    delete_string(str);
    delete_string(str2);
}

void test_file_read()
{
    int fd = open("./data.txt", O_RDONLY);
    if (fd) {
        p_cstring_t str;
        int err;
        do {
            err = read_line(fd, &str);
            if (err >= 0) {
                printf("Gasit: %s\n", str->data);
                delete_string(str);
            }
        } while (err == 0);
        close(fd);
    }
}

void test_persoana()
{
    p_persoana_t p = new_persoana(1, "Andrei Vasile", "0752637020", "andrei_vasile@yahoo.com");

    int fd = open("./persoane.txt", O_RDWR | O_CREAT); 
    if (fd) {
        write_persoana(fd, p);
        lseek(fd, 0, SEEK_SET);
        p_persoana_t p2;
        int err = read_persoana(fd, &p2);
        if (err >= 0) {
            printf("id : %lu\nnume : %s\nnr_telefon : %s\nemail : %s\n\n", p2->id, p2->nume, p2->nr_telefon, p2->email);
            delete_persoana(p2);
        }
        close(fd);
    }
    delete_persoana(p);
}

int main(int argc, char *argv[])
{
    test_strings();
    test_file_read();
    test_persoana();
    return 0;
}
