#include "list.h"
#include <stdlib.h>
#include <string.h>

/* make empty list*/
list_node_t* list_new(){
  /* dummy head */
  list_node_t* node = malloc(sizeof(list_node_t));
  node->data = NULL;
  node->next = NULL;
  return node;
}

/**
 * return: char* if len(node) 
 */
char* list_get(list_node_t* node, int n){
  int i;
  list_node_t *current = node->next;

  for(i = 0; i < n; i++){
    if(NULL == current){
      return NULL;
    }
    current = current->next;
  }
  return current->data;
}

/* add to head */
void list_push(list_node_t* node, char* new_data){
  list_node_t *new_node = malloc(sizeof(list_node_t));
  /* allocate new data */
  new_node->data = malloc(strlen(new_data)+1);
  strcpy(new_node->data, new_data);
  new_node->next = node->next;
  node->next = new_node;
}

void list_push_node(list_node_t* node, list_node_t* target){
  target->next = node->next;
  node->next = target;
}

/* use pointer to tail node */
void list_add(list_node_t* node, char* new_data){
  list_node_t *new_node = malloc(sizeof(list_node_t));
  list_node_t *prev;
  /* allocate new data */
  new_node->data = malloc(strlen(new_data)+1);
  new_node->next = NULL;
  strcpy(new_node->data, new_data);

  prev = node;
  while(NULL != prev->next){
    prev = prev->next;
  }
  prev->next = new_node;
}

list_node_t* list_remove_by_index(list_node_t* node, int n){
  int i;
  list_node_t *prev = node;
  list_node_t *current;

  for(i = 0; i < n; i++){
    if(NULL == prev->next){
      return NULL;
    }
    prev = prev->next;
  }
  current = prev->next;
  prev->next = current->next;
  current->next = NULL;
  return current;
}

void list_remove_by_node(list_node_t* node, list_node_t* target){
  list_node_t *prev = node;
  while(NULL != prev->next){
    if(prev->next == target){
      prev->next = prev->next->next;
      prev->next->next = NULL;
    }
    prev = prev->next;
  }
  /* node is not found */
}

void list_node_free(list_node_t* node){
  free(node->data);
  free(node);
}

void list_free(list_node_t* node){
  if(NULL != node->next){
    list_free(node->next);
  }
  list_node_free(node);
}
