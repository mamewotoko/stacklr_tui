#ifndef LIST_H
#define LIST_H

typedef struct list_node {
  /* data type */
  char *data;
  struct list_node *next;
} list_node_t;

/**
 * create empty list
 */
list_node_t* list_new();

/**
 * get data by index (0 origin)
 */
char* list_get(list_node_t* node, int n);

/**
 * add new node with given data to head of list
 */
void list_push(list_node_t* node, char* new_data);

/**
 * add new node with given data to tail of list
 */
void list_add(list_node_t* node, char* new_data);

/**
 * remove node specified by index (0 origin)
 */
list_node_t* list_remove(list_node_t* node, int n);

/**
 * free one node
 * e.g. removed node
 */
void list_node_free(list_node_t* node);

/**
 * remove all node
 */
void list_free(list_node_t* node);

#endif
