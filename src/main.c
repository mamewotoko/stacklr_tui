#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <menu.h>
#include <locale.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define MAX_ROWS 20
#define MAX_ITEM_NAME 100

typedef struct list_node {
  char *data;
  struct list_node *next;
} list_node_t;

//TODO: get from android values.xml
char *groups[5][2] = {
  { "To buy list", "To_buy_list.txt" },
  { "Stock", "Stock.txt" },
  { "Shelf", "Shelf.txt" },
  { "History", "History.txt" },
  { "Later", "Later.txt" }
};

int main(int argc,char *argv[])
{
  ITEM **menu_items;
  MENU *menu = NULL;
  MENU *to_buy_submenu;
  int i, j, cindex, item_name_index;
  int view_index;
  int c;
  int n_groups;
  int n_to_buy_items;
  WINDOW *subwin;
  char *itemname;
  char *group_filename;
  char *line = NULL;
  FILE *file;
  char item_name[MAX_ITEM_NAME];
  char* item_name_indent;
  char* item_name_list[MAX_ROWS];

  setlocale(LC_ALL, "");
  for(i = 0; i < MAX_ROWS; i++){
    item_name_list[i] = NULL;
  }
  
  n_groups = ARRAY_SIZE(groups);
  menu_items = (ITEM **)calloc(MAX_ROWS, sizeof(ITEM *));
  view_index = 0;
  item_name_index = 0;
  /* TODO: covert to linked list */
  for(i = 0; i < n_groups; i++){
    menu_items[view_index] = new_item(groups[i][0], NULL);
    view_index++;
    group_filename = groups[i][1];

    file = fopen(group_filename, "r");
    if(NULL == file){
      /* display error message */
      fprintf(stderr, "cannot open file: %s\n", group_filename);
      continue;
    }
    while(fgets(item_name, MAX_ITEM_NAME, file) != NULL){
      cindex = 0;
      do {
	if(item_name[cindex] == '\0' || item_name[cindex] == '\n'){
	  item_name[cindex] = '\0';
	  break;
	}
	cindex++;
      }
      while(TRUE);
      if(cindex == 0){
	/* empty line */
	continue;
      }
      item_name_indent = (char*)malloc(strlen(item_name)+10);
      sprintf(item_name_indent, "  %s", item_name);
      /* TODO: manage by linked list */
      item_name_list[item_name_index] = item_name_indent;
      item_name_index++;
      menu_items[view_index] = new_item(item_name_indent, NULL);
      view_index++;
    }
    fclose(file);
  }
  menu_items[view_index] = NULL;

  menu = new_menu((ITEM **)menu_items);

  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  
  post_menu(menu);
  refresh();
  
  while(TRUE){
    c = getch();
    if(c == KEY_F(1)
       || c == 'q') {
      break;
    }
    switch(c) {
    case KEY_DOWN:
      menu_driver(menu, REQ_DOWN_ITEM);
      break;
    case KEY_UP:
      menu_driver(menu, REQ_UP_ITEM);
      break;
    default:
      break;
    }
  }

 finalize:
  //child
  for(i = 0; i < view_index; i++){
    free_item(menu_items[i]);
  }
  if(NULL != menu){
    free_menu(menu);
  }
  endwin();
  free(menu_items);
  for(i = 0; i < item_name_index; i++){
    free(item_name_list[i]);
  }
  
  return 0;
}
