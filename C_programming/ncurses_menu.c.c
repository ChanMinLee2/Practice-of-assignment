#include <ncurses.h>

int main(int argc, char ** argv)
{
	// open mode of ncurses, no echo, input by one character not string
	initscr();
	noecho();
	cbreak();

	// get basic window's height ,width 
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	// make new window to menu system 
	WINDOW * menuwin = newwin(9, xMax - 12, yMax - 8, 5);
	box(menuwin, 0, 0);
	refresh();
	wrefresh(menuwin);

	// allocate fn key
	keypad(menuwin, true);

	// menu string array, control valiables 
	char* choices[5] = {"1. manual", "2. search", "3. add","4. delete","5. list"};
	int choice;
	int highlight = 0;

	// menu control of window cursor
	while(1)
	{
		for(int i = 0; i < 5; i++)
		{
			if(i == highlight)
				wattron(menuwin, A_REVERSE);
			mvwprintw(menuwin, i+1, 1, choices[i]);
			wattroff(menuwin, A_REVERSE);
		}
		// use control valiable choice 
		choice = wgetch(menuwin);
		
		// control menu by highlight(current), choice(moving)
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

