#include <stdio.h>
#include <stdlib.h>
#include <termcap.h>
#include <unistd.h>

// Tests whether current terminal's file descriptor
// is associated with a terminal.
int
istty()
{
	FILE* fp;
	int fd, tty;

	fp = fopen("/dev/tty", "r");
	if (!fp)
		return -1;

	fd = fileno(fp);
	if (fd < 0)
		return -1;

	tty = isatty(fd);
	fclose(fp);

	// associated with terminal
	return tty == 1;
}

// Returns number of colors supported by current terminal,
// or -1 if no colors are supported.
//
// The routine considers colors to be unsupported if
// the current file descriptor isn't a terminal,
// or if the TERM environmental variable is unset,
// or if unable to load the terminfo database.
int
numcolors()
{
	int n, tty;
	char *c = "Co";
	char *term, tbuf[1024];

	if ((tty = istty()) != 1 || !(term = getenv("TERM")) || tgetent(tbuf, term) != 1)
		return -1;

	if ((n = tgetnum(c)) != 1)
		return n;
	return -1;
}
