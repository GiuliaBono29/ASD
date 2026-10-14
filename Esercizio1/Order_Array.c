#include <stdio.h>
#include <stdlib.h>
#include "Order_Array.h"

static unsigned long get_index_to_insert(OrderedArray *ORDERED_ARRAY, void* ELEMENT);
static void insert_element(OrderedArray *ORDERED_ARRAY, void* ELEMENT, unsigned long INDEX);

//It represents the internal structure of this implementation of ordered arrays
struct _OrderedArray{
  void** ARRAY;
  unsigned long EL_NUM;
  unsigned long ARRAY_CAPACITY;
  int (*PRECEDES)(void*,void*);
};

OrderedArray *ordered_array_create(int (*PRECEDES)(void*,void*)){

  OrderedArray *ORDERED_ARRAY = (OrderedArray *)malloc(sizeof(OrderedArray));
  if(ORDERED_ARRAY == NULL){
    fprintf(stderr, "ordered_array_create: unable to allocate memory for the ordered array");
    exit(EXIT_FAILURE);
  }
  ORDERED_ARRAY->ARRAY = (void**)malloc(INITIAL_CAPACITY*sizeof(void*));
  if(ORDERED_ARRAY->ARRAY == NULL){
    fprintf(stderr, "ordered_array_create: unable to allocate memory for the internal array");
    exit(EXIT_FAILURE);
  }
  ORDERED_ARRAY->EL_NUM = 0;
  ORDERED_ARRAY->ARRAY_CAPACITY =INITIAL_CAPACITY;
  ORDERED_ARRAY->PRECEDES = PRECEDES;
  
  return(ORDERED_ARRAY);
}


int ordered_array_is_empty(OrderedArray *ORDERED_ARRAY){
  if(ORDERED_ARRAY == NULL){
    fprintf(stderr,"ordered_array_is_empty: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if(ORDERED_ARRAY->EL_NUM == 0)
    return(1);
  return(0);
}


unsigned long ordered_array_size(OrderedArray *ORDERED_ARRAY){
  if(ORDERED_ARRAY == NULL){
    fprintf(stderr,"ordered_array_size: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  return(ORDERED_ARRAY->EL_NUM);
}


void ordered_array_add(OrderedArray *ORDERED_ARRAY, void* ELEMENT){
  if(ORDERED_ARRAY == NULL){
    fprintf(stderr,"add_ordered_array_element: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if(ELEMENT == NULL){
    fprintf(stderr,"add_ordered_array_element: element parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  
  if(ORDERED_ARRAY->EL_NUM >= ORDERED_ARRAY->ARRAY_CAPACITY){
    ORDERED_ARRAY->ARRAY = (void**)realloc(ORDERED_ARRAY->ARRAY,2*(ORDERED_ARRAY->ARRAY_CAPACITY)*sizeof(void*));
    if(ORDERED_ARRAY->ARRAY == NULL){
      fprintf(stderr,"ordered_array_add: unable to reallocate memory to host the new element");
      exit(EXIT_FAILURE);
    }
    ORDERED_ARRAY->ARRAY_CAPACITY = 2*ORDERED_ARRAY->ARRAY_CAPACITY;
  }
  
  ORDERED_ARRAY->ARRAY[ORDERED_ARRAY->EL_NUM] = ELEMENT;
  ORDERED_ARRAY->EL_NUM++;
  
}


void* ordered_array_get(OrderedArray *ORDERED_ARRAY, unsigned long i){
  if(ORDERED_ARRAY == NULL){
    fprintf(stderr,"ordered_array_get: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if(i>=ORDERED_ARRAY->EL_NUM){
    fprintf(stderr,"ordered_array_get: Index %lu is out of the array bounds",i);
    exit(EXIT_FAILURE);
  }
  return(ORDERED_ARRAY->ARRAY)[i];
}


void ordered_array_free_memory(OrderedArray *ORDERED_ARRAY){
  if(ORDERED_ARRAY == NULL){
    fprintf(stderr,"ordered_array_free_memory: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  free(ORDERED_ARRAY->ARRAY);
  free(ORDERED_ARRAY);
}

//---------------------------------------------------------------------------

void swap(void ** FIRST, void ** SECOND){
	void * TEMP;
	TEMP = *FIRST;
	*FIRST = *SECOND;
	*SECOND = TEMP;
}

int partition(OrderedArray * ARRAY, long START, long END) {
	int INDEX1=START+1, INDEX2=END;
	while(INDEX1<=INDEX2){
			switch (ARRAY->PRECEDES(ARRAY->ARRAY[INDEX1],ARRAY->ARRAY[START])){
			case 1:
				INDEX1++;
				break;
			case 0:
				switch (ARRAY->PRECEDES(ARRAY->ARRAY[INDEX2],ARRAY->ARRAY[START])){
				case 1:
					swap(&ARRAY->ARRAY[INDEX1],&ARRAY->ARRAY[INDEX2]);
					INDEX1++;
					INDEX2--;
					break;
				case 0:
					INDEX2--;
					break;
				default:
					printf("\nerror\n");
					exit(EXIT_FAILURE);
					break;
				}
				break;
			default:
				printf("\nerror\n");
				exit(EXIT_FAILURE);
				break;
			}

	}
	swap(&ARRAY->ARRAY[START], &ARRAY->ARRAY[INDEX2]);
	return INDEX2; //ritorna il perno
}

void quicksort_ric(OrderedArray * ARRAY, long START, long END) {
	int PIVOT, START2, END2;
		if(START!=END){ //già ordinato
			PIVOT=partition(ARRAY, START, END);
			if(PIVOT-START>=2){ //può presentare elementi da ordinare
				END2=PIVOT-1;
				quicksort_ric(ARRAY, START, END2);
			}
			if(END-PIVOT>=2){ //può presentare elementi da ordinare
				START2=PIVOT+1;
				quicksort_ric(ARRAY, START2, END);
			}
		}
}

void quicksort(OrderedArray * ARRAY, long LENGTH){
	LENGTH--;
	quicksort_ric(ARRAY, 0, LENGTH);
}

int binary_call(void *x, OrderedArray *ARRAY, int START, int END, int MEDIUM){
    switch (MEDIUM)
        {
        case 0:
            switch (ARRAY->PRECEDES(ARRAY->ARRAY[MEDIUM],x))
            {
            case 1:
                return binary_search(x, ARRAY, MEDIUM+1, END);
                break;

            default:
                return MEDIUM;
                break;
            }
            break;
        default:
            switch (ARRAY->PRECEDES(ARRAY->ARRAY[MEDIUM],x))
            {
            case 1:
                return binary_search(x, ARRAY, MEDIUM+1, END);
                break;
            default:
                if(START>(MEDIUM-1)){
                    return MEDIUM;
                }
                else{
                return binary_search(x, ARRAY, START, MEDIUM-1);
                }
                break;
            }
            break;
        }
}

int binary_search(void *x, OrderedArray *ARRAY, int START, int END){
	int MEDIUM;
	if(START==END){
		switch (ARRAY->PRECEDES(ARRAY->ARRAY[START], x))
		{
		case 1:
			return START+1;
			break;
		default:
			return START;
			break;
		}
	}
	else if(START<END){
		MEDIUM=(START+END)/2;
		if(ARRAY->ARRAY[MEDIUM]==x){
			return MEDIUM;
		}

		binary_call(x, ARRAY, START,END, MEDIUM);
	}
	else{
		return -1;
	}
}

void binary_insertion_sort_ric(OrderedArray *ARRAY, int END){
	int BINARY, START=0, END2;
	void *x;    //SERVE?
	switch (END){
	case 0:
		printf("Vettore vuoto.\n");
		break;
	default:
		for(int i=1; i<=END; i++){
			END2=i-1;
			BINARY=binary_search(ARRAY->ARRAY[i], ARRAY, START, END2);
			switch (BINARY){
			case -1:
				printf("errore\n");
				break;
			
			default:
				for(int j=i; j>BINARY; j--){
					swap(&ARRAY->ARRAY[j-1], &ARRAY->ARRAY[j]);
				}
				break;
			}
		}
		break;
	}
}

void binary_insertion_sort(OrderedArray *ARRAY, int LENGTH){
	LENGTH--;
	binary_insertion_sort_ric(ARRAY, LENGTH);
}