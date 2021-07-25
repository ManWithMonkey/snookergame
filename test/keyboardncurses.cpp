// from https://stackoverflow.com/questions/4025891/create-a-function-to-check-for-key-press-in-unix-using-ncurses

#include <curses.h>
#include <unistd.h> /* only for sleep() */

int kbhit(void)
{
	int ch = getch();

	if (ch != ERR) {
		ungetch(ch);
		return 1;
	} else {
		return 0;
	}
}
#include <locale.h>

int main(void)
{
	setlocale(LC_ALL, "C.UTF-8");

	initscr();

	cbreak();
	noecho();
	// nodelay(stdscr, TRUE);
	halfdelay(8);
	scrollok(stdscr, TRUE);

	printw("|🍰|\n"); // unicode test

	while (1) {
		int ch = getch();
		if (ch != ERR) {
			printw("Key pressed! It was: %d\n", ch);
		} else {
			printw("No key pressed yet...\n");
		}
		refresh();

	}
}