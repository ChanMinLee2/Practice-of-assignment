#include <ncurses.h>

int main(int argc, char ** argv)
{
	initscr();
	noecho();
	cbreak();

	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	WINDOW * menuwin = newwin(9, xMax - 12, yMax - 8, 5);
	box(menuwin, 0, 0);
	refresh();
	wrefresh(menuwin);

	keypad(menuwin, true);
	char* choices[5] = {"1. manual", "2. search", "3. add","4. delete","5. list"};
	int choice;
	int highlight = 0;
	while(1)
	{
		for(int i = 0; i < 5; i++)
		{
			if(i == highlight)
				wattron(menuwin, A_REVERSE);
			mvwprintw(menuwin, i+1, 1, choices[i]);
			wattroff(menuwin, A_REVERSE);
		}
		choice = wgetch(menuwin);
		
		switch(choice)
		{
			case KEY_UP:
				highlight--;
				if(highlight == -1)
					highlight = 0;
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight == 5)
					highlight = 4;
				break;
			default:
				break;
		}
		if(choice == 10)
			break;
	}
	printw("Your choices was : %s", choices[highlight]);

	getch();
	endwin();

	return 0;
}

