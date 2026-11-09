#include "tema2.h"

list_file create_nod(int n,char *id, int scor, int nr_keyword, char **keyword_list)
{
    list_file new_nod=(list_file)malloc(sizeof(struct file));
    new_nod->keyword_list=(char **)malloc(nr_keyword*sizeof(char*));
    new_nod->id=(char *)malloc((n+1)*sizeof(char));
    strcpy(new_nod->id,id);
    new_nod->id[n]='\0';
    new_nod->scor=scor;
    new_nod->nr_keyword=nr_keyword;
    for(int i=0;i<new_nod->nr_keyword;i++)
    {
        new_nod->keyword_list[i]=(char *)malloc((strlen(keyword_list[i])+1)*sizeof(char));
        strcpy(new_nod->keyword_list[i],keyword_list[i]);
        new_nod->keyword_list[i][strlen(keyword_list[i])]='\0';
    }
    new_nod->next=NULL;
    new_nod->prev=NULL;
    return new_nod;
}

trie_nod createNode()
{
    trie_nod new_node=(trie_nod)malloc(sizeof(struct trie));
    new_node->count=0;
    new_node->nrfii=0;
    for(int i=0;i<26;i++)
    {
        new_node->child[i]=NULL;
    }
    new_node->file_ref=NULL;
    return new_node;
}
void insert_keyword(trie_nod root, char *s,list_file file)
{
    trie_nod current=root;
    int k=strlen(s);
    for(int i=0;i<k;i++)
    {
        int index=s[i]-'a';
        if(current->child[index]==NULL)
        {
            //dacă nu există încă niciun cuvânt care să fi trecut pe această direcție. trebuie să „construieșc un drum nou:
            //Alocă memorie pentru a crea un nod complet nou.
            //Atribuie noul nod cu poziției corespunzătoare din tabloul child.
            //Deoarece tocmai am adăugat o nouă ramură copil,
            //trebui sa cresc cu 1 variabila care numără copiii
            //(nrfii) a nodului current.
            current->child[index]=createNode();
            current->nrfii++;
        }
        //Dacă este diferit de NULL => drumul există deja
        //(deoarece un alt cuvânt cu același prefix l-a creat anterior).
        //Nu mai trebuie să creez nimic în plus.
        current=current->child[index];
    }
    current->count++;
    //pointerul current se află acum la ultima literă a cuvântului.
    //În acest moment, creste variabila count a nodului current
    //Scopul ei este să indice că:
    //în acest punct, tocmai s-a terminat un cuvânt complet
    
    list_reference new_ref=(list_reference)malloc(sizeof(struct referinta));
    //Creează și alocă memorie pentru nodul de referință
    new_ref->file_ptr=file;
    //pointeaza la fisier original
    new_ref->next=current->file_ref;
    current->file_ref=new_ref;
    //Adaugă acest nod la ÎNCEPUTUL listei file_ref a cuvantului curent
}
void add_file(list_file *listfile,int n,char *id, int scor, int nr_keyword, char **keyword_list,trie_nod root)
{
    list_file temp=(*listfile);
    while(temp !=NULL && strcmp(temp->id,id)!=0)
    {
        temp=temp->next;
    }
    if(temp==NULL) //inseamna ca nu exista inca identificatorul in lista
    {
        printf("OK\n");
        list_file new_file=create_nod(n,id,scor,nr_keyword,keyword_list);
        if(*listfile==NULL)
        {
            *listfile=new_file;
            (*listfile)->prev=NULL;
            (*listfile)->next=NULL;
        }
        else
        {
            list_file temp1=*listfile;
            while(temp1->next!=NULL)
            {
                temp1=temp1->next;
            }
            temp1->next=new_file;
            new_file->prev=temp1;
            new_file->next=NULL;
        }
        for(int i=0;i<new_file->nr_keyword;i++)
        {
            insert_keyword(root,new_file->keyword_list[i],new_file);
        }
    }
    else
        printf("EXISTS\n");
}


trie_nod search_keyword(trie_nod root,char *s)
{
    trie_nod current=root;
    int k=strlen(s);
    for(int i=0;i<k;i++)
    {
        int index=s[i]-'a';
        if(current->child[index]==NULL)
        {
            return NULL;
        }
        current=current->child[index];
    }
    // Bucla s-a terminat, pointerul se află la ultima literă.
    // Returnează nodul "current" contine ultima literă.
    return current;
}
//Funcția recursivă returnează 1 dacă nodul copil poate fi șters,și returnează 0 dacă trebuie păstrat.
int del_word(trie_nod current, char *word, int nivel)
{

    //safe case
    if(current==NULL)
        return 0;
    int k=strlen(word);
    //cazul in care s-a ajuns la bază(la nivel de nodul frunza) 
    // (s-a parcurs întreaga lungime a cuvântului cheie)
    if(nivel==k)
    {
       //Deoarece count a fost deja decrementat în del_file,trebuie doar să verificăm dacă poate fi șters.
        if(current->count==0 && current->nrfii==0)
        {
            return 1; //putem sa l stergem
        }
        return 0; //Nu se poate șterge (de exemplu, acest nod încă se ramifică spre alte cuvinte)
    }
    // continuam sa coboram la nivel mai jos
    int index=word[nivel]-'a';
    //Dacă funcția recursivă a nodului copil returnează 1 (adică nodul copil trebuie șters)
    if(del_word(current->child[index],word,nivel+1)==1)
    {
        //stergem nodul cpoil
        free(current->child[index]);
        current->child[index]=NULL;
        current->nrfii--; //Scade cu 1 numărul de ramuri copil ale nodului curent

        //DUPĂ ȘTERGEREA COPILULUI, verifică din nou nodul curent (nodul părinte)
        //OBS: Nu trebuie niciodată să raportez ștergerea ROOT-ului (nivel == 0)
        if(nivel>0 && current->count==0 && current->nrfii==0)
        {
            return 1; //daca count==0 si nrfii=0 , putem sa l stergem
        }
    }
    return 0;// Dacă nu sunt îndeplinite condițiile=>nodul trebuie păstrat
}
void del_file(list_file *listfile,char *file_id,trie_nod root)
{
    list_file current=*listfile;
    while(current!=NULL && strcmp(current->id,file_id)!=0)
    {
        current=current->next;
    }
    if(current==NULL)
    {
        printf("NOT FOUND\n");
    }
    else
    {
        printf("OK\n");
        // Șterge referința din arborele Trie
        for(int i=0;i<current->nr_keyword;i++)
        {
            trie_nod endofword=search_keyword(root, current->keyword_list[i]);
            list_reference list_file_ref=endofword->file_ref;
            
            if(strcmp(list_file_ref->file_ptr->id,file_id)==0)
            {
                list_reference temp=list_file_ref;
                endofword->file_ref=temp->next;
                free(temp);
            }
            else
            {
                while(list_file_ref->next!=NULL && strcmp(list_file_ref->next->file_ptr->id,file_id)!=0)
                {
                    list_file_ref=list_file_ref->next;
                }
                if(list_file_ref->next!=NULL)
                {
                    list_reference temp=list_file_ref->next;
                    list_file_ref->next=list_file_ref->next->next;
                    free(temp);
                }
            }
            endofword->count--;
            //daca cuvantul nu se ma leaga cu niciun fisier=>stergem cuvantul
            if(endofword->count==0)
            {
                del_word(root,current->keyword_list[i],0);
            }
        }

        //acum stergem fisier ala in lista de fisiere
        list_file temp_file=current;
        if(current->prev==NULL)
        {
            *listfile=current->next;
            if(*listfile!=NULL)
                (*listfile)->prev=NULL;
        }
        else if(current->next==NULL)
        {
            current->prev->next=NULL;
        }
        else
        {
            current->prev->next=current->next;
            current->next->prev=current->prev;
        }
        free(temp_file->id);
        for(int i=0;i<temp_file->nr_keyword;i++)
        {
            free(temp_file->keyword_list[i]);
        }
        free(temp_file->keyword_list);
        free(temp_file);
    }
}

void add_keyword(list_file listfile,char *word,char *file_id,trie_nod root)
{
    list_file curent=listfile;
    while(curent!=NULL && strcmp(curent->id,file_id)!=0)
    {
        curent=curent->next;
    }
    if(curent==NULL)
    {
        printf("NOT FOUND\n");
    }
    else
    {
        printf("OK\n");
        int already_exist=0;
        for(int i=0;i<curent->nr_keyword;i++)
        {
            if(strcmp(curent->keyword_list[i],word)==0)
            {
                already_exist=1;
                break;
            }
        }
        if(already_exist==0)
        {
            insert_keyword(root,word,curent);
            //add new keyword to vector keyword_list;
            curent->nr_keyword++;
            curent->keyword_list=(char**)realloc(curent->keyword_list,curent->nr_keyword*sizeof(char*));
            //Alocă memorie pentru noul cuvânt la ultima poziție și copiază-l în acesta
            int index=curent->nr_keyword-1;
            curent->keyword_list[index]=(char *)malloc((strlen(word)+1)*sizeof(char));
            strcpy(curent->keyword_list[index],word);
        }
    }
}

void del_keyword(list_file *listfile,char *word,char *file_id,trie_nod root)
{
    list_file curent=*listfile;
    while(curent!=NULL && strcmp(curent->id,file_id)!=0)
    {
        curent=curent->next;
    }
    if(curent==NULL)
    {
        printf("NOT FOUND\n");
    }
    else
    {
        printf("OK\n");
        int exist=0;
        int index=-1;
        for(int i=0;i<curent->nr_keyword;i++)
        {
            if(strcmp(curent->keyword_list[i],word)==0)
            {
                exist=1;
                index=i;
                break;
            }
        }
        if(exist==1)
        {
            trie_nod endofword=search_keyword(root,word);
            list_reference list_ref=endofword->file_ref;
            if(strcmp(list_ref->file_ptr->id,file_id)==0)
            {
                list_reference temp=list_ref;
                endofword->file_ref=temp->next;
                free(temp);
            }
            else
            {
                while(list_ref->next!=NULL && strcmp(list_ref->next->file_ptr->id,file_id)!=0)
                {
                    list_ref=list_ref->next;
                }
                if(list_ref->next!=NULL)
                {
                    list_reference temp=list_ref->next;
                    list_ref->next=list_ref->next->next;
                    free(temp);
                }
            }
            endofword->count--;
            if(endofword->count==0)
            {
                del_word(root,word,0);
            }
            //ȘTERGE KEYWORD DIN ARRAY-UL FIȘIERULUI(keyword_list)
            free(curent->keyword_list[index]);
            //Mută elementele din dreapta in stanga ( de la drepata de tot pana la index)pentru a acoperi golul
            for(int i=index;i<curent->nr_keyword-1;i++)
            {
                curent->keyword_list[i]=curent->keyword_list[i+1];
            }
            curent->nr_keyword--;
            
            if(curent->nr_keyword==0)
            {
                list_file temp_file=curent;
                if(curent->prev==NULL)
                {
                    *listfile=curent->next;
                    if(*listfile!=NULL)
                        (*listfile)->prev=NULL;
                }
                else if(curent->next==NULL)
                {
                    curent->prev->next=NULL;
                }
                else
                {
                    curent->prev->next=curent->next;
                    curent->next->prev=curent->prev;
                }
                free(temp_file->id);
                free(temp_file->keyword_list);
                free(temp_file);
            }
        }
    }
}

void swap(char *a, char *b)
{
    char aux[100];
    strcpy(aux,a);
    strcpy(a,b);
    strcpy(b,aux);
}
void find_keyword(trie_nod root,char *word)
{
    int nr_total_file=0;
    trie_nod endofword=search_keyword(root,word);
    if(endofword==NULL || endofword->count==0 || endofword->file_ref==NULL)
    {
        printf("EMPTY\n");
        return;
    }
    list_reference list_ref=endofword->file_ref;
    list_reference temp=list_ref;
    while(temp!=NULL)
    {
        nr_total_file++;
        temp=temp->next;
    }

    //sortam lista referinta fisier
    char s[nr_total_file][100];
    int k=0;
    list_reference head= list_ref;
    while(head!=NULL)
    {
        strcpy(s[k++],head->file_ptr->id);
        head=head->next;
    }
    for(int i=0;i<k-1;i++)
    {
        for(int j=0;j<k-i-1;j++)
        {
            if(strcmp(s[j],s[j+1])>0)
            {
                swap(s[j],s[j+1]);
            }
        }
    }
    printf("%d ",nr_total_file);
    for(int i=0;i<k;i++)
    {
        printf("%s ",s[i]);
    }
    printf("\n");
}

void print_sorted_list(list_reference list_ref, int nr_total_file)
{
    char s[nr_total_file][100];
    int k=0;
    list_reference head= list_ref;
    while(head!=NULL)
    {
        strcpy(s[k++],head->file_ptr->id);
        head=head->next;
    }
    for(int i=0;i<k-1;i++)
    {
        for(int j=0;j<k-i-1;j++)
        {
            if(strcmp(s[j],s[j+1])>0)
            {
                swap(s[j],s[j+1]);
            }
        }
    }
    printf("%d ",nr_total_file);
    for(int i=0;i<k;i++)
    {
        printf("%s ",s[i]);
    }
    printf("\n");
}
void print_arbore(trie_nod root,char *aux,int k)
{
    trie_nod curent=root;
    if(curent==NULL)
    {
        printf("EMPTY\n");
        return;
    }
    //condiția de oprire a funcției recursive: atunci când se găsește un cuvânt complet și se afișează
    if(curent->count!=0)
    {
        aux[k]='\0'; //închide șirul obținut după recursie pentru a-l afișa
        printf("%s ",aux);
        int nr_total_file=curent->count;
        print_sorted_list(curent->file_ref,nr_total_file);
    }
    //Continuă să cobori pe ramurile copil în ordine de la 'a' la 'z'
    for(int i=0;i<26;i++)
    {
        if(curent->child[i]!=NULL)
        {
            aux[k]=i+'a';
            print_arbore(root->child[i],aux,k+1);//Continuă să coboare mai jos
            //când deschizi ușa i (current->child[i]),
            //trebuie să pășești în acea cameră pentru a continua explorarea.
        }
    }
}


heap init_heap(int cap)
{
    heap h=(heap)malloc(sizeof(struct Heap));
    h->cap_maxima=cap;
    h->nr_elemente=0;
    //Vectorul vect_ele din Heap-ul este folosit pentru a stoca pointeri către fișiere (list_file),
    //(nu pentru a stoca toate datele fișierelor , DOAR POINTER)
    h->vect_ele=(list_file*)malloc(cap*sizeof(list_file));
    //Se alocă un tablou de pointeri, deci dimensiunea trebuie să fie dimensiunea unui pointer, nu a întregii structuri.
    return h;
}
void swap_nod(list_file *a, list_file *b)
{
    list_file aux=*a;
    *a=*b;
    *b=aux;
}
int compare_nod(list_file a,list_file b)
{
    if(a->scor > b->scor)
        return 1;
    if(a->scor < b->scor)
        return 0;
    //Dacă scor sunt egale, ID-ul mai mic (care apare mai devreme în ordine alfabetică) este considerat mai mare.
    if(strcmp(a->id,b->id)<0)
        return 1;
    return 0;
}
//Scopul este de a restabili proprietatea de Max Heap pentru un subarbore cu rădăcina în current.
// care este ca nod parinti trebuie sa fiu mai mare decat noduri copii
void heapify(heap h, int current)
{
    int left =2*current+1; //index copil parte stanga in array
    int right=2*current+2; //index copil parte dreapta in array
    int indexmax=current;
    if(left<h->nr_elemente && compare_nod(h->vect_ele[left],h->vect_ele[indexmax])==1)
    {
        indexmax=left;
    }
    if(right< h->nr_elemente && compare_nod(h->vect_ele[right],h->vect_ele[indexmax])==1)
    {
        indexmax=right;
    }
    if(indexmax!=current)
    {
        swap_nod(&h->vect_ele[current],&h->vect_ele[indexmax]);
        heapify(h, indexmax);
    }
}
void create_max_heap(heap h, list_reference ref_file)
{
    //put all element in ref_file in heap first
    int k=0;
    list_reference temp=ref_file;
    while(temp!=NULL)
    {
        k++;
        temp=temp->next;
    }
    h->nr_elemente=k;
    for(int i=0;i<k;i++)
    {
        h->vect_ele[i]=ref_file->file_ptr;
        ref_file=ref_file->next;
    }
    
    //now transform heap into max-heap base on scor
    int n=h->nr_elemente;
    for(int i=(n-1)/2;i>=0;i--)
    {
        heapify(h,i);
    }
}
list_file extragere(heap h)
{
    if(!h || h->nr_elemente==0)
    {
        printf("EMPTY\n");
        return NULL;
    }
    list_file ans;
    ans=h->vect_ele[0];
    h->vect_ele[0]=h->vect_ele[h->nr_elemente-1]; // Lấy thằng cuối lên đầu
    h->nr_elemente--;
    heapify(h,0); // Đẩy nó chìm xuống đúng vị trí
    return ans;
}
void topk(trie_nod root,char *word,int k)
{
    trie_nod endofword=search_keyword(root,word);
    if(endofword==NULL)
    {
        printf("EMPTY\n");
        return;
    }

    //INIȚIALIZAREA UNUI HEAP EXACT DIMENSIONAT (Capacitatea este egală exact cu numărul de fișiere)
    heap h=init_heap(endofword->count);

    list_reference ref_file=endofword->file_ref;

    create_max_heap(h,ref_file);

    if(!h || h->nr_elemente==0)
    {
        printf("EMPTY\n");
    }
    else if(h->nr_elemente<k)
    {
        printf("%d ",h->nr_elemente);
        int n=h->nr_elemente;
        for(int i=0;i<n;i++)
        {
            list_file nod=extragere(h);
            printf("%s ",nod->id);
        }
        printf("\n");
    }
    else
    {
        printf("%d ",k);
        for(int i=0;i<k;i++)
        {
            list_file nod;
            nod=extragere(h);
            printf("%s ",nod->id);
        }
        printf("\n");
    }
    free(h->vect_ele);//Eliberarea tabloului de pointeri
    free(h); // Eliverarea heap
}

trie_nod search_prefix(trie_nod root,char *prefix)
{
    trie_nod current=root;
    int k=strlen(prefix);
    for(int i=0;i<k;i++)
    {
        int index=prefix[i]-'a';
        if(current->child[index]==NULL)
        {
            return NULL;
        }
        current=current->child[index];
    }
    //Bucla se încheie, pointerul se află la ultima literă.
    //Se returnează ultima literă a acelui prefix.
    return current;
}

/*
Deoarece funcția recursivă poate modifica pointerul s și variabila capac, este obligatoriu să transmiți adresele acestora în funcție.
Asta înseamnă că capac devine int *capac, iar char s va deveni char ***s.
*/
void going_to_the_end(trie_nod curent, char ***s,int *capac,int *nr_file)
{
    if(curent==NULL)
        return;
    if(curent->count>0)//Înseamnă că nodul curent conține ultima literă a unui cuvânt complet.
    {
        list_reference temp=curent->file_ref;
        while(temp!=NULL)
        {
           //Se verifică dacă fișierul există deja în tabloul s (pentru a evita duplicatele)
            int ok=1;
            for(int i=0;i<(*nr_file);i++)
            {
                if(strcmp((*s)[i],temp->file_ptr->id)==0)
                {
                    ok=0;
                    break;
                }
            }
            if(ok)
            {
                //(*nr_file) atinge capacitatea curentă (*capac),
                //  capacitatea este dublată automat utilizând realloc.
                if(*nr_file==*capac)
                {
                    (*capac)*=2;
                    (*s)=(char **)realloc(*s, (*capac)*sizeof(char*));
                }
                //se alocă memorie cu malloc pentru noul șir și se copiază id-ul fișierului.
                (*s)[*nr_file]=(char*)malloc(100*sizeof(char));
                strcpy((*s)[*nr_file],temp->file_ptr->id);
                (*nr_file)++;
            }
            temp=temp->next;
        }
    }
    //coboram mai jos pt toti copii nenuli ai nodul curent(intre a->z)
    for(int i=0;i<26;i++)
    {
        if(curent->child[i]!=NULL)
        {
            going_to_the_end(curent->child[i],s,capac,nr_file);
        }
    }
}
void find_dupa_prefix(trie_nod root,char *prefix)
{
    trie_nod endofprefix=search_prefix(root,prefix);
    if(endofprefix==NULL)
    {
        printf("EMPTY\n");
        return;
    }
    int nr_file=0;
    
    // Inițializarea capacității inițiale
    int capac=2;
    char **s=(char **)malloc(capac*sizeof(char*));

    going_to_the_end(endofprefix,&s,&capac,&nr_file);
    
    if(nr_file==0)
    {
        printf("EMPTY\n");
        free(s);
        return;
    }
    printf("%d ",nr_file);

    for(int i=0;i<nr_file-1;i++)
    {
        for(int j=0;j<nr_file-i-1;j++)
        {
            if(strcmp(s[j],s[j+1])>0)
            {
                swap(s[j],s[j+1]);
            }
        }
    }
    for(int i=0;i<nr_file;i++)
    {
        printf("%s ",s[i]);
        free(s[i]);// După afișare, eliberăm fiecare șir
    }
    printf("\n");
    free(s);// La final eliberăm vectorul de pointeri
}

void free_trie(trie_nod root)
{
    if(root==NULL)
        return;
    for(int i=0;i<26;i++)
    {
        if(root->child[i]!=NULL)
        {
            free_trie(root->child[i]);
        }
    }
    //Eliberează lista de referințe (file_ref) din acest nod (dacă există).
    list_reference curent_ref=root->file_ref;
    while(curent_ref!=NULL)
    {
        list_reference temp=curent_ref;
        curent_ref=curent_ref->next;
        //Se eliberează doar pointer referințelor, NU fișierul original (temp_ref->file_ptr).
        free(temp);
    }
    free(root);
}

void free_file_list(list_file filelist)
{
    list_file curent=filelist;
    while(curent!=NULL)
    {
        list_file temp=curent;
        curent=curent->next;
        //elibereaza ID
        if(temp->id!=NULL)
            free(temp->id);
        //elibereaza vector bidimensional de keywords
        for(int i=0;i<temp->nr_keyword;i++)
        {
            // elibereaza fiecare cuvant keyword in vector
            free(temp->keyword_list[i]);
        }
        free(temp->keyword_list);
        free(temp);
    }
}