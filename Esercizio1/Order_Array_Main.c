#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Order_Array.h"

typedef struct record{
  int INDEX_FIELD;
  char* STRING_FIELD;
  int INTEGER_FIELD;
  double DOUBLE_FIELD;
}Records;

typedef struct timespec Time;

static Time start_t(){
  Time BEGIN;
  clock_gettime(CLOCK_REALTIME, &BEGIN);

  return BEGIN;
}

static double stop_t(Time BEGIN){
  Time END;
  clock_gettime(CLOCK_REALTIME, &END);

  long SECONDS = END.tv_sec - BEGIN.tv_sec;
  long NANOSECONDS = END.tv_nsec - BEGIN.tv_nsec;
  double ELAPSED = (double) SECONDS + (double) NANOSECONDS*1e-9;

  return ELAPSED;
}

static int record_integer(void* RECORD1,void* RECORD2){
  if(RECORD1 == NULL){
    fprintf(stderr,"precedes_record_int_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if(RECORD2 == NULL){
    fprintf(stderr,"precedes_record_int_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Records *REC1 = (Records*)RECORD1;
  Records *REC2 = (Records*)RECORD2;
  if(REC1->INTEGER_FIELD <= REC2->INTEGER_FIELD){
    return(1);
  }
  return(0);
}


static int record_string(void* RECORD1,void* RECORD2){
  if(RECORD1 == NULL){
    fprintf(stderr,"precedes_string: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if(RECORD2 == NULL){
    fprintf(stderr,"precedes_string: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Records *REC1 = (Records*)RECORD1;
  Records *REC2 = (Records*)RECORD2;

  return strcmp(REC1->STRING_FIELD,REC2->STRING_FIELD) < 0;
}

static int record_double(void* RECORD1,void* RECORD2){
  if(RECORD1 == NULL){
    fprintf(stderr,"precedes_record_int_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if(RECORD2 == NULL){
    fprintf(stderr,"precedes_record_int_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Records *REC1 = (Records*)RECORD1;
  Records *REC2 = (Records*)RECORD2;
  if(REC1->DOUBLE_FIELD <= REC2->DOUBLE_FIELD){
    return(1);
  }
  return(0);
}


static  void free_array(OrderedArray* ARRAY) {
  unsigned long  EL_NUM =  ordered_array_size(ARRAY);
  for(unsigned long i=0;i<EL_NUM;i++){
    Records *ARRAY_ELEMENT = (Records *)ordered_array_get(ARRAY, i);
    free(ARRAY_ELEMENT->STRING_FIELD);
    free(ARRAY_ELEMENT);
  }
  ordered_array_free_memory(ARRAY);
}

static  void print_array(OrderedArray* ARRAY, int CHOISE){
  unsigned long EL_NUM =  ordered_array_size(ARRAY);
  FILE *FILE_PATH;
  switch (CHOISE)
  {
  case 1:
    FILE_PATH = fopen("Result_string.csv", "w");
    break;
  case 2:
    FILE_PATH = fopen("Result_int.csv", "w");
    break;
  case 3:
    FILE_PATH = fopen("Result_double.csv", "w");
    break;
  default:
    printf("\nError\n");
    exit(EXIT_FAILURE);
    break;
  } 
  Records *ARRAY_ELEMENT;
  
  for(unsigned long i=0;i<EL_NUM;i++){
    ARRAY_ELEMENT = (Records *)ordered_array_get(ARRAY, i);
    fprintf(FILE_PATH,"%d,%s,%d,%f\n",ARRAY_ELEMENT->INDEX_FIELD,ARRAY_ELEMENT->STRING_FIELD,ARRAY_ELEMENT->INTEGER_FIELD, ARRAY_ELEMENT->DOUBLE_FIELD);
  }
  fclose(FILE_PATH);
}

Records * Memorization_data(Records * RECORD, char * INDEX, char * STRING, char * INTEGER, char * DOUBLE){

    RECORD->INDEX_FIELD = atoi(INDEX);

    RECORD->STRING_FIELD = malloc((strlen(STRING)+1) * sizeof(char));
    if (RECORD->STRING_FIELD == NULL) {
      fprintf(stderr,"main: unable to allocate memory for the string field of the read record");
      exit(EXIT_FAILURE);
    }
    strcpy(RECORD->STRING_FIELD, STRING);

    RECORD->INTEGER_FIELD = atoi(INTEGER);

    RECORD->DOUBLE_FIELD = atof(DOUBLE);

    return RECORD;
}



static void load_array(const char* FILE_NAME, OrderedArray* ARRAY){
  char BUFFER[BUF_SIZE];
  FILE *FILE_PATH;
  printf("\nLoading data from file...\n");
  FILE_PATH = fopen(FILE_NAME,"r");
  if(FILE_PATH == NULL){
    fprintf(stderr,"main: unable to open the file\n");
    exit(EXIT_FAILURE);
  }
  while(fgets(BUFFER,BUF_SIZE,FILE_PATH) != NULL){
    Records *RECORD = malloc(sizeof(Records));
    if(RECORD == NULL){
      fprintf(stderr,"main: unable to allocate memory for the read record\n");
      exit(EXIT_FAILURE);
    }  
    /* Reading the fields of the record */ 
    char *INDEX_FIELD = strtok(BUFFER, " ,");
    char *STRING_FIELD = strtok(NULL, " ,");
    char *INTEGER_FIELD = strtok(NULL, " ,");
    char *DOUBLE_FIELD = strtok(NULL, " ,");

    RECORD = Memorization_data(RECORD, INDEX_FIELD, STRING_FIELD, INTEGER_FIELD, DOUBLE_FIELD);
    ordered_array_add(ARRAY, (void*)RECORD);
  }
  fclose(FILE_PATH);
}

static  void test_with_comparison_function(const char* FILE_NAME, int ALGORITM, int CRITERIA, int (*COMPARE)(void*, void*)) {
  Time START;
  double TIME_TOT;
  OrderedArray* ARRAY;

  START = start_t(START);
  ARRAY = ordered_array_create(COMPARE);
  load_array(FILE_NAME, ARRAY);
  printf("\ntime for loading %.3f seconds.\n", stop_t(START));
  printf("Data uploaded.\n");
  TIME_TOT += (stop_t(START)/60);

  switch (ALGORITM)
  {
  case 0:
    START = start_t(START);
    quicksort(ARRAY, ordered_array_size(ARRAY));
    break;
  case 1:
    START = start_t(START);
    binary_insertion_sort(ARRAY, ordered_array_size(ARRAY));
    break;
  default:
    break;
  }
  printf("\ntime for sorting %.3f seconds.\n", stop_t(START));
  printf("Data sorted.\n");
  TIME_TOT += (stop_t(START)/60);

  START = start_t(START);
  print_array(ARRAY, CRITERIA);
  free_array(ARRAY);
  printf("\ntime for printing %.3f seconds.\n", stop_t(START));
  printf("Data wrinted.\n");
  TIME_TOT += (stop_t(START)/60);

  printf("\nTotal Time %.3f\n", TIME_TOT);
}



int main(int ARGC, char const *ARGV[]){
//argv[1] = file_path
//argv[2] = criterio
//argv[3] = algoritmo

  int CRITERIA = atoi(ARGV[2]);
  int ALGORITM = atoi(ARGV[3]);

	if(ARGC < 3){
		exit(EXIT_FAILURE);
	}
  if(ALGORITM != 1 && ALGORITM != 0){
    exit(EXIT_FAILURE);
  }
  if(CRITERIA<0 || CRITERIA>3){
    exit(EXIT_FAILURE);
  }

  switch (CRITERIA){
    case 0:
        test_with_comparison_function(ARGV[1], ALGORITM, 1, record_string);
        test_with_comparison_function(ARGV[1], ALGORITM, 2, record_integer);
        test_with_comparison_function(ARGV[1], ALGORITM, 3, record_double);
      break;

    case 1:
        test_with_comparison_function(ARGV[1], ALGORITM, CRITERIA, record_string);
      break;

    case 2:
        test_with_comparison_function(ARGV[1], ALGORITM, CRITERIA, record_integer);
      break;

    case 3:
        test_with_comparison_function(ARGV[1], ALGORITM, CRITERIA, record_double);
      break;
    
    default:
      fprintf(stderr,"main: unable to select the sorting criteria");
      exit(EXIT_FAILURE);
      break;
  }

  return EXIT_SUCCESS;
}