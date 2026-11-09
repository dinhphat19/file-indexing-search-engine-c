//NGUYEN DINH PHONG PHAT-311CC
#ifndef TEMA2_H
#define TEMA2_H

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

//lista de fisiere
typedef struct file
{
    char *id;
    int scor;
    int nr_keyword;
    char **keyword_list; //vector allocat dinamica
    struct file *next;
    struct file *prev;
}*list_file; //lista dublu inlantuita

//struct pt lista de referintele spre fisiere
typedef struct referinta
{
    list_file file_ptr; //pointer indica la file 
    struct referinta *next;
}*list_reference;

//arbore de prefix pt a stoca cuvintele
typedef struct trie
{
    int count,nrfii;
    struct trie* child[26];
    list_reference file_ref; //lista cu referintele spre fisiere
}*trie_nod;

typedef struct Heap
{
    int cap_maxima;
    int nr_elemente;
    list_file *vect_ele;
}*heap;

list_file create_nod(int n,char id[], int scor, int nr_keyword, char **keyword_list);
trie_nod createNode();

void insert_keyword(trie_nod root, char *s,list_file file);
void add_file(list_file *listfile,int n,char id[], int scor, int nr_keyword, char **keyword_list,trie_nod root);

trie_nod search_keyword(trie_nod root,char *s);
int del_word(trie_nod current, char *word, int nivel);
void del_file(list_file *listfile,char *file_id,trie_nod root);

void add_keyword(list_file listfile,char *word,char *file_id,trie_nod root);

void del_keyword(list_file *listfile,char *word,char *file_id,trie_nod root);

void swap(char *a, char *b);
void find_keyword(trie_nod root,char *word);

void print_sorted_list(list_reference list_ref, int nr_total_file);
void print_arbore(trie_nod root,char *aux,int k);

heap init_heap(int cap);
void swap_nod(list_file *a, list_file *b);
int compare_nod(list_file a,list_file b);
void heapify(heap h, int current);
void create_max_heap(heap h, list_reference ref_file);
list_file extragere(heap h);
void topk(trie_nod root,char *word,int k);

trie_nod search_prefix(trie_nod root,char *prefix);
void going_to_the_end(trie_nod curent, char ***s,int *capac,int *nr_file);
void find_dupa_prefix(trie_nod root,char *prefix);

void free_trie(trie_nod root);
void free_file_list(list_file filelist);
#endif