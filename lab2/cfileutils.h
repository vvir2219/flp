// reads line (until \n or end of file)
// returns -1 on error, 0 on good read (reached \n) and 1 on eof
int read_line(int filedes, p_cstring_t *_str);

// reads line or until given size(which comes first
// same as above
int read_line_s(int filedes, size_t limit, p_cstring_t *_str);
