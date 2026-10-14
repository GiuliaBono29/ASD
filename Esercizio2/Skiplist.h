#ifndef SKIPLIST_H_HAHAHAHAHAHAHA
#define SKIPLIST_H_HAHAHAHAHAHAHA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct Node Node;
typedef struct SkipList SkipList;

int record_string(void *RECORD1, void *RECORD2);

Node *create_node(void* ELEMENT, int SIZE);

SkipList *create_list(int (*COMPARE)(void*, void*));

void remove_list(SkipList *LIST);

void print_node(Node *NODE);

void print_list(SkipList *LIST);

int random_level();

void insert_skiplist(SkipList *LIST, void *ELEMENT);

SkipList *load_dictionary(const char *FILE_NAME, SkipList *LIST);

int search_skiplist(SkipList *LIST, void* ELEMENT);

void is_dot(SkipList *DICTIONARY, void * TOKEN);

void load_to_correct(const char *FILE_NAME, SkipList *DICTIONARY);

//void search_in_file_skiplist(const char *FILE_NAME, SkipList *LIST);

#endif