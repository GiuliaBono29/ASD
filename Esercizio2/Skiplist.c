#include "Skiplist.h"
#define MAX_HEIGHT 20 //il massimo numero di puntatori che possono esserci in un singolo nodo
#define BUF_SIZE 1024
int CASUAL = 1;

//PROF
struct SkipList { //struttura lista
  Node *HEAD;
  unsigned int MAX_LEVEL; //determina il massimo attuale tra i vari size dei nodi
  int (*COMPARE)(void*, void*);
};

struct Node { //struttura nodo
  struct Node **NEXT; //array di puntatori (il numero è indicato da size ed è randomico)
  unsigned int SIZE; //il numero di puntatori in un dato nodo
  void *ITEM; /*codice prof*/
};

int record_string(void* RECORD1,void* RECORD2){

  if(RECORD1 == NULL){
    fprintf(stderr,"precedes_string: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if(RECORD2 == NULL){
    fprintf(stderr,"precedes_string: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }

  return strcmp(((char *)RECORD1), ((char *)RECORD2));
}

Node *create_node(void* ELEMENT, int SIZE){ //creazione nodo
    Node *NEW_NODE = (Node*)malloc(sizeof(Node)); //malloc per il nodo
    NEW_NODE->NEXT=(Node **)malloc(sizeof(Node**)*SIZE); //malloc per il next
    void *STRING= (void *)malloc(sizeof(void)*BUF_SIZE); //malloc per la posizione in cui salvare le varie stringhe e non sovrascrivere gli indirizzi
    strcpy(STRING,ELEMENT);
    if(NEW_NODE!=NULL){
        NEW_NODE->SIZE=SIZE;
        NEW_NODE->ITEM=STRING;
        for(int i=0;i<NEW_NODE->SIZE;i++){
            NEW_NODE->NEXT[i]=NULL;
        }
    }
    else{
        printf("Error: create_node\n");
    }
    return NEW_NODE;
}

SkipList *create_list(int (*COMPARE)(void*, void*)){ //creazione lista
    SkipList *NEW_LIST = (SkipList*)malloc(sizeof(SkipList));
    NEW_LIST->HEAD=(Node *)malloc(sizeof(Node));
    NEW_LIST->HEAD->NEXT=(Node**)malloc(sizeof(Node*)*MAX_HEIGHT);
    if(NEW_LIST!=NULL){
        NEW_LIST->HEAD->SIZE=MAX_HEIGHT;
        for(int i=0;i<NEW_LIST->HEAD->SIZE;i++){
            NEW_LIST->HEAD->NEXT[i]=NEW_LIST->HEAD;
        }
        NEW_LIST->MAX_LEVEL=0;
        NEW_LIST->COMPARE=COMPARE;
    }
    else{
        printf("Error: create_list\n");
    }
    return NEW_LIST;
}

void remove_list(SkipList *LIST){ //rimozione lista
    Node *X=LIST->HEAD->NEXT[0];
    Node *Y;
    while(X!=LIST->HEAD){ //cancello HEAD e nodi
        Y=X->NEXT[0];
        free(X);
        X=Y;
    }
    free(X);
    free(LIST); //cancello LIST
}

void print_node(Node *NODE){ //printf nodi
    printf("|%s|%d|", (char*)NODE->ITEM, NODE->SIZE);
}

void print_list(SkipList *LIST){ //printf lista
    Node *NODE = LIST->HEAD->NEXT[0];
    while(NODE!=LIST->HEAD){
        print_node(NODE);
        printf("-->");
        NODE=NODE->NEXT[0];
    }
    printf("NULL\n");
}

int random_level(){ //determina il numero di puntatori da mettere in un nodo
    int LEVEL = 1;
    CASUAL ++;
    srand((unsigned int)time(NULL)*CASUAL);
    // random() returns a random value in [0...1)
    while((float)rand()/(float)(RAND_MAX/1) < 0.5 && LEVEL < MAX_HEIGHT){ //Stackoverflow
        LEVEL++;
    }
    return LEVEL;
} //N.B. Spiegare il vantaggio di questo algoritmo nella relazione da consegnare con l'esercizio


void insert_skiplist(SkipList *LIST, void *ELEMENT){ //inserisce I nella skiplist LIST
    Node *NEW_NODE = create_node(ELEMENT, random_level(ELEMENT));
    if (NEW_NODE->SIZE > LIST->MAX_LEVEL){
        LIST->MAX_LEVEL = NEW_NODE->SIZE;
    }
    Node *x = LIST->HEAD;
    for(int i = LIST->MAX_LEVEL-1; i>=0; i--){ //inserisco NEW_NODE nella skiplist... i=1 perchè deve avere minimo un puntatore
        if (x->NEXT[i] == LIST->HEAD || LIST->COMPARE(x->NEXT[i]->ITEM, ELEMENT)>0){ //x[i]->next[i] == NULL || I < x[i]->next[i]->item
            if (i < NEW_NODE->SIZE) {
            	NEW_NODE->NEXT[i] = x->NEXT[i];
            	x->NEXT[i] = NEW_NODE;
            }
        }
        else{
            x = x->NEXT[i];
            i++;
        }
    }
}

SkipList *load_dictionary(const char *FILE_NAME, SkipList *LIST){//creo il dizionario
    FILE *FILE_PATH;
    char BUFFER[BUF_SIZE];
    char * TOKEN;
    FILE_PATH = fopen(FILE_NAME,"r");
    if(FILE_PATH==NULL){
        printf("Error print\n");
        exit(EXIT_FAILURE);
    }
    while(fgets(BUFFER,BUF_SIZE,FILE_PATH)!=NULL){
        TOKEN=strtok(BUFFER,"\n");
        insert_skiplist(LIST, TOKEN);
    }
    fclose(FILE_PATH);
    return LIST;
}

int search_skiplist(SkipList *LIST, void* ELEMENT){
    Node *NODE=LIST->HEAD;
    for(int i=(LIST->MAX_LEVEL)-1; i>=0; i--){
        while((NODE->NEXT[i]!=LIST->HEAD)&&(LIST->COMPARE(NODE->NEXT[i]->ITEM, ELEMENT)<0)){
            NODE=NODE->NEXT[i];
        }
    }
    NODE=NODE->NEXT[0];
    if(LIST->COMPARE(NODE->ITEM, ELEMENT)==0){
        return 0;
    }
    else{
        return 1;
    }
}

void is_dot(SkipList *DICTIONARY, void * TOKEN){ //controllo della punteggiatura e inserimento
    char DOTS[7] = {'.',',',';',':','?','!','\n'}; //arrei punteggiatura
    void *SUB_TOKEN=(void*)calloc(BUF_SIZE,sizeof(void)); //stringa contenente la sottostringa della parola
    int SHIFT=0, NUMBER_LETTERS=0, SHIFT_LETTERS=32;
    int FLAG_DOT=0, FLAG_NOT_DOT=0;
    while(*((char*)TOKEN+SHIFT)!='\0'){
        for(int j=0; j<7; j++){
            if(*((char*)TOKEN+SHIFT)==DOTS[j]){
                FLAG_DOT=1;
                FLAG_NOT_DOT=1;
            }
        }
        if(FLAG_DOT==1){
            if(NUMBER_LETTERS>0 && search_skiplist(DICTIONARY, SUB_TOKEN)==1){
                printf("%s\n",(char*)SUB_TOKEN);
            }
            FLAG_DOT=0;
            SHIFT++;
            NUMBER_LETTERS=0;
        }
        else{
            if(*((char*)TOKEN+SHIFT)>='A'&&*((char*)TOKEN+SHIFT)<='Z'){
                *((char*)SUB_TOKEN+SHIFT)=*((char*)TOKEN+SHIFT)+SHIFT_LETTERS;
            }
            else{
                *((char*)SUB_TOKEN+SHIFT)=*((char*)TOKEN+SHIFT);
            }
            SHIFT++;
            NUMBER_LETTERS++;
        }
    }
    if(FLAG_NOT_DOT==0){
        if(search_skiplist(DICTIONARY, SUB_TOKEN)==1){
            printf("%s\n",(char*)SUB_TOKEN);
        }
    }
    free((char*)SUB_TOKEN);
}

void load_to_correct(const char *FILE_NAME, SkipList *DICTIONARY){//creo la correzione
    FILE *FILE_PATH;
    char BUFFER[BUF_SIZE];
    void * TOKEN;
    FILE_PATH = fopen(FILE_NAME,"r");
    if(FILE_PATH==NULL){
        printf("Error print\n");
        exit(EXIT_FAILURE);
    }
    while(fgets(BUFFER,BUF_SIZE,FILE_PATH)!=NULL){
        TOKEN=strtok(BUFFER," ");
        while(TOKEN!=NULL){
            is_dot(DICTIONARY, TOKEN);
            TOKEN=strtok(NULL," ");
        }
    }
    fclose(FILE_PATH);
}