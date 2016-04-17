#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <menu.h>
#include <locale.h>

#include "stacklr.h"
#include "list.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define MAX_ROWS 40
#define MAX_ITEM_NAME 100

//TODO: get from android values.xml
char *groups[NUM_GROUPS][2] = {
  { "To buy list", DATADIR "To_buy_list.txt" },
  { "Stock",  DATADIR "Stock.txt" },
  { "Shelf",  DATADIR "Shelf.txt" },
  { "History",  DATADIR "History.txt" },
  { "Later",  DATADIR "Later.txt" }
};

list_node_t* item_list[NUM_GROUPS];
ITEM* all_menu_item[MAX_ROWS];

const int NEXT[NUM_GROUPS] = {
  STOCK,
  TO_BUY,
  TO_BUY,
  TO_BUY,
  HISTORY
};

void init_item_list(){
  int i;
  int str_len;
  char item_name[1024];
  char item_name_with_indent[1024];
  char *group_filename;
  FILE *file;
  
  for(i = 0; i < NUM_GROUPS; i++){
    item_list[i] = list_new();
    group_filename = groups[i][1];
    
    file = fopen(group_filename, "r");
    if(NULL == file){
      /* TODO: output as log file */
      fprintf(stderr, "cannot open file: %s\n", group_filename);
      continue;
    }
    while(fgets(item_name, MAX_ITEM_NAME, file) != NULL){
      str_len = strlen(item_name);
      if(0 == str_len){
	continue;
      }
      if('\n' == item_name[str_len-1]){
	if(1 == str_len){
	  continue;
	}
	item_name[str_len-1] = '\0';
      }
      sprintf(item_name_with_indent, "  %s", item_name);
      list_add(item_list[i], item_name_with_indent);
    }
    fclose(file);
  }
}

/* TODO: cache menu */
void make_menu(){
  int menu_index = 0;
  int i;
  list_node_t *current;
  
  for(i = 0; i < NUM_GROUPS; i++){
    all_menu_item[menu_index] = new_item(groups[i][0], NULL);
    menu_index++;
    /* TODO: iterate api */
    current = item_list[i];
    while(TRUE){
      current = current->next;
      if(NULL == current){
	break;
      }
      all_menu_item[menu_index] = new_item(current->data, NULL);
      menu_index++;
    }
  }
  all_menu_item[menu_index] = NULL;
}

int main(int argc,char *argv[])
{
  MENU *menu = NULL;
  int i;
  int c;

  setlocale(LC_ALL, "");
  
  init_item_list();
  make_menu();
  
  menu = new_menu(all_menu_item);

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

  /* finalize: */
  for(i = 0; i < MAX_ROWS; i++){
    if(NULL == all_menu_item[i]){
      break;
    }
    free_item(all_menu_item[i]);
  }
  
  if(NULL != menu){
    free_menu(menu);
  }
  endwin();

  /* free(menu_items); */
  for(i = 0; i < NUM_GROUPS; i++){
    list_free(item_list[i]);
  }
  
  return 0;
}
