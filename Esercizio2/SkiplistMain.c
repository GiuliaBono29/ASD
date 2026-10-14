#include "Skiplist.h"
#define MAX_HEIGHT 10
#define BUF_SIZE 1024

int main(int ARGC, char const *ARGV[]){
    printf("Creo il dizionario\n");
    SkipList * DICTIONARY=create_list(record_string);
    DICTIONARY=load_dictionary((const char *)ARGV[1],DICTIONARY);
    printf("Dizionario creato\n");
    printf("Controllo ortografico\n");
    load_to_correct((const char *)ARGV[2], DICTIONARY);
    printf("FINITO\n");
    remove_list(DICTIONARY);
}