# Algoritmi e Strutture Dati

## Introduzione

Progetto del corso di **Algoritmi e Strutture Dati** (Laurea Triennale in Informatica, UniTo, secondo anno).
Raccoglie tre esercizi di implementazione e confronto di algoritmi e strutture dati classici, in C e in Java. Il progetto è stato sviluppato in gruppo per il corso di ASD, insieme a due collaboratore.

## Tecnologie usate

* **C** (esercizi 1 e 2)
* **Java** (esercizio 3): generics, `Hashtable`, `ArrayList`
* Strutture dati generiche con puntatori `void\\\\\\\*` e funzioni di confronto passate come parametro

## Riassunto delle parti

### Esercizio 1 – Ordered Array: Quicksort e Binary Insertion Sort

Implementazione di un **array ordinato generico** in C (`Order\\\\\\\_Array.c`) e confronto di due algoritmi di ordinamento:

* **Quicksort**, con partizione sul primo elemento come perno
* **Binary Insertion Sort**, che usa la ricerca binaria per trovare la posizione di inserimento

Il programma di test (`Order\\\\\\\_Array\\\\\\\_Main.c`) legge da file CSV dei record (indice, stringa, intero, double), li ordina secondo il campo scelto (stringa, intero o double) con l'algoritmo scelto, misura i tempi di caricamento, ordinamento e scrittura e salva il risultato in un file CSV.

### Esercizio 2 – Skip List: correttore ortografico

Implementazione di una **Skip List** in C (`Skiplist.c`) con altezza dei nodi scelta in modo casuale, con inserimento e ricerca. La struttura è usata per realizzare un **correttore ortografico**: il programma carica un dizionario nella skip list, poi legge un testo, ne separa le parole togliendo la punteggiatura e stampa quelle che non si trovano nel dizionario.

### Esercizio 3 – Grafo e algoritmo di Dijkstra

Implementazione in Java di un **grafo generico** (diretto o non diretto, con nodi ed archi etichettati) basato su tabella hash e liste di adiacenza (`Graph`, `Node`, `Arc`), e di una **coda di priorità** come **heap minimo** con operazione di decremento della chiave (`HeapMinimo`).
Sopra queste strutture è implementato l'**algoritmo di Dijkstra** per il calcolo del cammino minimo. Il programma (`Main`) legge da un file CSV un grafo di città italiane con le relative distanze in metri e calcola la distanza tra due città (nell'esempio, Torino e Catania).

