/* Minimale Systemaufrufe fuer die C-Bibliothek (newlib-nano).
 * Ohne Betriebssystem gibt es keine Dateien – die Funktionen tun nichts. */
#include <sys/stat.h>
#include <errno.h>

int _close(int fd)                       { (void)fd; return -1; }
int _lseek(int fd, int ptr, int dir)     { (void)fd; (void)ptr; (void)dir; return 0; }
int _read(int fd, char *buf, int len)    { (void)fd; (void)buf; (void)len; return 0; }
int _write(int fd, char *buf, int len)   { (void)fd; (void)buf; return len; }
int _fstat(int fd, struct stat *st)      { (void)fd; st->st_mode = S_IFCHR; return 0; }
int _isatty(int fd)                      { (void)fd; return 1; }
