#ifndef ORDER_ARRAY_H_HAHAHAHAHAHAHAHAH
#define ORDER_ARRAY_H_HAHAHAHAHAHAHAHAH

#define INITIAL_CAPACITY 20
#define BUF_SIZE 1024

typedef struct _OrderedArray OrderedArray;

OrderedArray *ordered_array_create(int (*precedes)(void *, void *));

int ordered_array_is_empty(OrderedArray *);

unsigned long ordered_array_size(OrderedArray *);

void ordered_array_add(OrderedArray *, void*);

void* ordered_array_get(OrderedArray *, unsigned long);

void ordered_array_free_memory(OrderedArray *);

//-----------------------------------------------------------------------

int partition(OrderedArray *ARRAY, long START, long END);

void quicksort_ric(OrderedArray *ARRAY, long START, long END);

void quicksort(OrderedArray *ARRAY, long LENGTH);

int binary_search(void *x, OrderedArray *ARRAY, int START, int END);

int binary_call(void *x, OrderedArray *ARRAY, int START, int END, int MEDIUM);

void binary_insertion_sort_ric(OrderedArray *ARRAY, int END);

void binary_insertion_sort(OrderedArray *ARRAY, int LENGTH);

#endif