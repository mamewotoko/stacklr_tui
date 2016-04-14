#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <menu.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define MAX_ROWS 20

typedef struct list_node {
  char *data;
  struct list_node *next;
} list_node_t;

//TODO: get from android values.xml
const char *groups[] = {
  "To buy list",
  "Stock",
  "Shelf",
  "History",
  "Later"
};

const char* tobuy_items[] = { "  clean room",  "  water plant",  (char*)NULL };
const char* stock_items[] = { "  milk",  "  banana",  (char*)NULL };
const char* shelf_items[] = { (char*)NULL };
const char* history_items[] = { "  tea",   (char*)NULL };
const char* later_items[] =  { (char*)NULL };

//init data for each group
char** init_items[] = {
  tobuy_items,
  stock_items,
  shelf_items,
  history_items,
  later_items
};

int main(int argc,char *argv[])
{
  ITEM **menu_items;
  MENU *menu;
  MENU *to_buy_submenu;
  int i, j;
  int view_index;
  int c;
  int n_groups;
  int n_to_buy_items;
  WINDOW *subwin;
  char *itemname;
  
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  
  n_groups = ARRAY_SIZE(groups);
  menu_items = (ITEM **)calloc(MAX_ROWS, sizeof(ITEM *));
  view_index = 0;
  /* TODO: covert to linked list */
  for(i = 0; i < n_groups; i++){
    menu_items[view_index] = new_item(groups[i], NULL);
    view_index++;
    if(NULL == init_items[i]){
      continue;
    }
    for(j = 0; ; j++){
      itemname = init_items[i][j];
      if(NULL == itemname){
	break;
      }
      menu_items[view_index] = new_item(itemname, NULL);
      view_index++;
    }
  }
  menu_items[view_index] = NULL;

  menu = new_menu((ITEM **)menu_items);
  
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

  //child
  for(i = 0; i < view_index; i++){
    free_item(menu_items[i]);
  }
  free_menu(menu);
  endwin();
  free(menu_items);

  return 0;
}
