#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

#include "cstring.h"
#include "cfileutils.h"

#define BUFFER_SIZE 4096

int read_line(int filedes, p_cstring_t *_str) {
	char *buf = (char*)malloc((BUFFER_SIZE + 1)* sizeof(char));
	ssize_t bytes_read;
	char *nl_pos;
	int retcode = 0;
	*_str = new_string();
	p_cstring_t str = *_str;

	do {
		bytes_read = read(filedes, (void*)buf, BUFFER_SIZE);
		if (bytes_read < 0) {
			free(buf);
			delete_string(str);
			*_str = NULL;
			return bytes_read;
		} else if (bytes_read < BUFFER_SIZE) {
			retcode = 1;
		}
		buf[bytes_read] = 0;
		nl_pos = strchr(buf, '\n');
		if (nl_pos) {
			retcode = 0;
			*nl_pos = 0;
			off_t back_offset = strlen(nl_pos + 1);
			lseek(filedes, -back_offset, SEEK_CUR);
			bytes_read -= (back_offset + 1);
		}
		string_append_raw(str, buf, bytes_read);
	} while (bytes_read == BUFFER_SIZE);

	return retcode;
}

int read_line_s(int filedes, size_t limit, p_cstring_t *_str) {
	char *buf = (char*)malloc((BUFFER_SIZE + 1)* sizeof(char));
	ssize_t bytes_read, ammount_to_read;
	char *nl_pos;
	int retcode = 0;
	*_str = new_string();
	p_cstring_t str = *_str;

	do {
		ammount_to_read = limit > BUFFER_SIZE ? BUFFER_SIZE : limit;
		bytes_read = read(filedes, (void*)buf, ammount_to_read);
		if (bytes_read < 0) {
			free(buf);
			delete_string(str);
			*_str = NULL;
			return bytes_read;
		} else if (bytes_read < ammount_to_read) {
			retcode = 1;
		}
		buf[bytes_read] = 0;
		nl_pos = strchr(buf, '\n');
		if (nl_pos) {
			retcode = 0;
			*nl_pos = 0;
			off_t back_offset = strlen(nl_pos + 1);
			lseek(filedes, -back_offset, SEEK_CUR);
			bytes_read -= (back_offset + 1);
		}
		string_append_raw(str, buf, bytes_read);
		limit -= bytes_read;
	} while (limit > 0 && bytes_read == ammount_to_read);

	return retcode;
}
