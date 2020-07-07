#include <cstdio>
#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <cstring>


using namespace std;

struct Player_info {
  char name[256];
  unsigned count_point;
};

void show_stat(Player_info mass[], int n)
{
  Player_info max_elem;
  for (int i = 0.0; i < n - 1; i++) {
    for ( int j = 0.0; j < n - i - 1; j++ ) {
      if (mass[j].count_point < mass[j + 1].count_point) {
        max_elem = mass[j];
        mass[j] = mass[j + 1];
        mass[j + 1] = max_elem;
      }
    }
  }

  for (int i = 0.0; i < n; i++) {
    printw("%s", mass[i].name);
    printw(" %d", mass[i].count_point);
    printw("\n");
  }
}

int main()
{

  unsigned number_player, choice, coin;
  Player_info max_elem;
  const unsigned max_count_level = 3;
  bool game = true;
  char unit = '@';
  unsigned number_lvl = 1.0;
  unsigned steps = 30.0;
  int n_p = 0.0;

  cout << "Enter count of players\n";
  cin >> number_player;
  Player_info *player_mass = new Player_info[number_player];

initscr();
{

  while ( game ) {

    bool motion = true;
    ifstream file;


    switch (number_lvl) {
      case 1:
        file.open("levels//level1.txt");
        coin = 2.0;
        break;
      case 2:
        file.open("levels//level2.txt");
        coin = 5.0;
        break;
    }

    char *str = new char[256];
    int row = 0.0, col;

    while ( !file.eof() ) {
      file >> str;
      col = strlen(str);
      ++row;
    }
    delete [] str;

    file.clear();
    file.seekg(0);
    col += 1;
    row -= 1;

    char *buff = new char [col];
    char lvl[row][col];

    for ( int i = 0.0; i < row; i++ ) {
      file >> buff;
      for ( int j = 0.0; j < col; j++ ) {
        lvl[i][j] = buff[j];
      }
    }
    delete [] buff;

  curs_set(0);
  keypad(stdscr, true);
  unsigned x = 1.0, y = 1.0;

  while ( motion ) {

    clear();
    for ( unsigned k = 1.0; k < row + 1; k++ ) {
      for ( unsigned n = 1.0; n < col; n++ ) {
        printw("%c", lvl[k - 1][n - 1]);
        refresh();
      }
      printw("\n");
      refresh();
    }

  mvprintw(y, x, "%c", unit);
  mvprintw(20.0, 10.0, "%d%s", steps, " Steps");

  switch ( getch() ) {

    case KEY_UP:
      if (lvl[y - 1][x] != '#') {
        if (lvl[y - 1][x] == '$') {
          steps += coin;
          lvl[y - 1][x] = '.';
        }
        mvprintw(y - 1, x, "%c", unit);
        refresh();
        y--;
        steps--;
      }
      break;

    case KEY_DOWN:
      if ( lvl[y + 1][x] != '#' ) {
        if (lvl[y + 1][x] == '$') {
          steps += coin;
          lvl[y + 1][x] = '.';
        }
        mvprintw(y + 1, x, "%c", unit);
        refresh();
        y++;
        steps--;
      }
      break;

    case KEY_LEFT:
      if ( (lvl[y][x - 1] != '#') && (lvl[y][x - 1] != '<') ) {
        if (lvl[y][x - 1] == '$') {
          steps += coin;
          lvl[y][x - 1] = '.';
        }
        mvprintw(y, x - 1, "%c", unit);
        refresh();
        x--;
        steps--;
      }
      break;

    case KEY_RIGHT:
      if (lvl[y][x + 1] == '>') {
        clear();
        mvprintw(0.0, 0.0, "Next level\n");
        getch();
        number_lvl++;
        motion = false;
        steps += 10;
      }
      else if ( lvl[y][x + 1] != '#' ) {
        if (lvl[y][x + 1] == '$') {
          steps += coin;
          lvl[y][x + 1] = '.';
        }
        mvprintw(y, x + 1, "%c", unit);
        refresh();
        x++;
        steps--;
      }
      break;

    case KEY_BACKSPACE:
      clear();
      printw("Game over");
      getch();
      game = false;
      motion = false;
      break;
  }


    if (steps == 0.0) {
      number_lvl = 1.0;
      clear();
      mvprintw(0.0, 0.0, "Game over\n");
      getch();
      printw("Enter name\n");
      refresh();
      scanw("%s", player_mass[n_p].name);
      n_p++;
      player_mass[n_p].count_point = steps;
      if (n_p == number_player) {
        printw("Enter 1 - <top> or 2 - <end game>\n");
        scanw("%d", &choice);

        switch (choice) {
          case 1:
            show_stat(player_mass, number_player);
            getch();
            game = false;
            break;

          case 2:
            game = false;
            motion = false;
            break;
        }
      }
      steps = 30.0;
      motion = false;
    }
  }

    if (number_lvl == max_count_level) {
      clear();
      mvprintw(0.0, 0.0, "You Win\n");
      getch();
      printw("Enter Name\n");
      scanw("%s", player_mass[n_p].name);
      player_mass[n_p].count_point = steps;
      n_p++;

      number_lvl = 1.0;
      steps = 30.0;

      if (n_p == number_player) {
        printw("Enter 1 - <top> or 2 - <end game>\n");
        scanw("%d", &choice);

        if (choice == 1) {
          show_stat(player_mass, number_player);
          getch();
          game = false;
        } else {
          game = false;
        }

      }
    }

    file.close();
  }

}
endwin();

return 0;
}
