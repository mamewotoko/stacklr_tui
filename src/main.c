#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <menu.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

//TODO: get from android values.xml
char *groups[] = {
  "To buy list",
  "Stock",
  "Shelf",
  "History",
  "Later"
};

int main(int argc,char *argv[])
{
  ITEM **group_items;
  MENU *menu;
  int i;
  int c;
  int n_groups;
  
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  
  n_groups = ARRAY_SIZE(groups);
  group_items = (ITEM **)calloc(n_groups+1, sizeof(ITEM *));
  for(i = 0; i < n_groups; i++){
    group_items[i] = new_item(groups[i], groups[i]);
  }
  group_items[n_groups] = (ITEM *)NULL;
  menu = new_menu((ITEM **)group_items);
  post_menu(menu);
  refresh();
  
  while((c = getch()) != KEY_F(1)) {
    switch(c) {
    case KEY_DOWN:
      menu_driver(menu, REQ_DOWN_ITEM);
      break;
    case KEY_UP:
      menu_driver(menu, REQ_UP_ITEM);
      break;
    }
  }
  
  free_item(group_items[0]);
  free_item(group_items[1]);
  free_menu(menu);
  endwin();

  return 0;
}
