NGUYEN DINH PHONG PHAT-311CC
PUNCTAL OBTINUT: 120/120
I,STRUCTURI

+)typedef struct file:
    este o structura de lista dublu inlantuita in care reprezenta un nod in lista de fisiere, care pt fiecare fisier, stocheaza:identificatorul,scor de relevant,nr de keyword si un vector de sir pt a stoca keywords
+)typedef struct referinta
    este o structura de lista simplpu inlanuita care reprezenta  referinta spre fisier(care folosim in trie pt fiecare cuvant)
    ,fiecare nod contine un pointer indice la fisier corespunzator
+)typedef struct trie
    este o structura pt arbore multicai (prefix tree) care stocheaza keywords, si pe fiecare nodul frunza se leaga cu un vector de pointer care indice la fisiere contina cuvantul dat.
+)typedef struct Heap
    este o structura pt heap care contine nr total de noduri in heap, si un vector de tip struct file, care contine lista de fisiere care contine un keyword dat

II,FUNCTII

+)list_file create_nod(int n,char id[], int scor, int nr_keyword, char **keyword_list);
    
    returneaza un nod nou in lista de fisiere,folosim alocare dinamica pt a aloca memmorie pentru new_nod,respectivsir de caractere "new_nod->id" si un vector de sir de caracter "new_nod->keyword_list"care contine keywords legata de fisier.
    in loop "for" pt a adauga siruri in "new_nod->keyword_list" de la vectorul dat ca argument "keyword_list" trebuie sa facem alocare dinamica pt fiecare element in vector
    la inceput, nodul nou nu se leaga cu nimeni ( st di dr indica la NULL)

+)trie_nod createNode()
    
    returneaza nodul root la arbore trie prefix, functia de initializare
    nodul "root" al lui arbore de prefix nu contine nimic, nrfii=0, nici nu se leaga cu niciun fisier file_ref=NULL
    "count"este folosita ca counter nr total de fisier care este legat de cuvantul, de asemenea, se marcheaza sfarsitul fiecare cuvantul (nodul_frunze->count==1 daca este un cuvant)
+)void insert_keyword(trie_nod root, char *s,list_file file)
    
    fucntie ne ajuta sa insertam un keyword "s" nou in arbore de regasire precum si legam în nodul terminal corespunzător cuvântului se adaugă o referintă către fisier.
    Folosim o buclă for pentru a parcurge toată lungimea cuvântului care trebuie inserat în arbore. Știm că literel de la a -> z sunt marcate astfel: a - index 0, b - index 1, ..., z - index 25. De aceea, calculăm poziția literei s[i]
    folosind expresia: s[i] - 'a'.
    dacă nu există încă niciun cuvânt care să fi trecut pe această direcție. trebuie să „construieșc un drum nou:
    Alocă memorie pentru a crea un nod complet nou.
    Atribuie noul nod cu poziției corespunzătoare din tabloul child.
    Deoarece tocmai am adăugat o nouă ramură copil,
    trebui sa cresc cu 1 variabila care numără copiii
    (nrfii) a nodului current.

    Dacă este diferit de NULL => drumul există deja (deoarece un alt cuvânt cu același prefix l-a creat anterior). Nu mai trebuie să creez nimic în plus.

    pointerul current se află acum la ultima literă a cuvântului.În acest moment, creste variabila count a nodului current Scopul ei este să indice că: în acest punct, tocmai s-a terminat un cuvânt complet

    acum dupa ce am adaugat keyword in arbore=>legam în nodul terminal corespunzător cuvântului se adaugă o referintă către fisier.
    - Creează și alocă memorie pentru nodul de referință
    -nodul tocmat am creat trebuie sa pointeaza la fisier original
    -Adaugă acest nod la ÎNCEPUTUL listei file_ref a cuvantului curent

+)void add_file(list_file *listfile,int n,char *id, int scor, int nr_keyword, char **keyword_list,trie_nod root)

    functie ne ajuta sa adaugam un nou fisier în sistem, in care trebuie sa adaugam fisier cu info de id si scor in lista de fisiere, si toate keywords fisierului trebuie sa fiu insertat in arbore de regasire

    afisam "OK"daca este functionat cu success
    dacă identificatorul există deja, operatia esuează=>afisam "EXISTS"

    cand insertam new_file in lista de fisiere, trebuie sa consideram 2 cazuri: daca initial lista este NULL sau cazul normal
    dupa folosim un loop for pt a adauga toate keywords in arbore cu ajutorul functia "insert_keyword"

+)trie_nod search_keyword(trie_nod root,char *s)

    functia foloseste un for care merge pe toate litere in cuvantul s, si incerca sa gaseste keyword "s"in arbore, se duce de la root pana la nivel de nodul fruze cu conditie ca:"current->child[index]!=NULL"

    cand bucla s-a terminat, pointerul "curent" se află la ultima literă.
    Returnează nodul "current" contine ultima literă.

+)int del_word(trie_nod current, char *word, int nivel)
    
    Funcția recursivă returnează 1 dacă nodul copil poate fi șters,și returnează 0 dacă trebuie păstrat.
    avem safe case ca nodul current este NULL
    ->cand am ajuns la nivel de nodul frunza(nivel==strlen(word))=>verificam daca nr de fisier lagat de word si nr de ramuri a lui nodul curent egal cu 0 sau nu, DACA sunt egal cu 0, ATUNCI returnam 1, adica putem sa l stergem
    
    acum pt fiecare index=word[nivel]-'a' unde nivel merge de la 0 pana la strlen(word)=> mergem recursiv pana la sfarsitul arbore(noduri frunze) cu del_word(current->child[index],word,nivel+1)

    si verificam de la nodul frunze pana la nodul inceput recursiv cu conditie:
        if(del_word(current->child[index],word,nivel+1)==1)
    ->daca egal cu 1 atunci stergem pe nodul copil asta
    DUPĂ ȘTERGEREA COPILULUI, verifică din nou nodul curent (nodul părinte)
    si daca nivel>0 && current->count==0 && current->nrfii==0.ATUNCI returneaza 1,si putem sa l stergem pe el la pasul urmator

+)void del_file(list_file *listfile,char *file_id,trie_nod root)
    functie ne ajuta sa stergem un fisier în sistem, identificator file_id,
    avem 2 lucrui de facut:
        ->stergem referinta fisierului care se leaga cu keywords in arbore prefix(adica sterge pointer indica la fisier in lista de referinta al cuvantului)
        si daca dupa stergere referinta , cuvantul ala nu mai are nicio referinta (endofword->count==0)=>atunci stergem pe cuvantul ala in arbore
        ->stergem fisier in lista de fisier
    pasul_1: gasim fisier de sters dupa pargurere prin lista de fisiere si se compara id -ul fiecare fisiere cu file_id dat
    pasul_2: pt fiecare keywords al lui fisier de sters, noi trebuie sa stergem referinta fisierului care se leaga cu ei in nodul terminal in arbore prefix trie
    =>facem un loop for prin toate element in curent->keyword_list si folosim search_keyword pt a gasi fiecare keyword in arbore
    list_file_ref etse lista de reference al lui keyword[i]
    verificam primul element in list_file_ref daca este fisier de sters sau nu,daca este, stergem de el si endofword->file_ref=temp->next;
    dupa ce am sters pe referinta fisierului de sters al keyword[i], atunci scadam count "endofword->count--;"
    si daca dupa stergere referinta , cuvantul ala nu mai are nicio referinta (endofword->count==0)=>atunci stergem pe cuvantul ala in arbore,folosim functie "del_word"
    pasul_3:acum stergem pe fisier in lista de fisiere, care tre sa consideram 3 cazul care daca fisiere este primul nod in lista sau ultimul nod sau nodul in mijloc
    ->si cand dam free la fisier, trebuie intai sa dam free la campul "Id" si vecorul de sir de caracter keyword_list + toate elemente in vector(folosim loop for)

+)void add_keyword(list_file listfile,char *word,char *file_id,trie_nod root)

    Adaugă un cuvânt-cheie unui fisier existent.
    Dacă fisierul nu există, operatia esuează. Dacă fisierul există deja si are deja asociat acel cuvânt-cheie, operatia nu modifică sistemul, dar este considerată reusită.=>afisam OK daca este reusit
    -daca keyword vrem sa l adaugam deja exista=> nu facem nimic
    ->folosim insert_keyword pt a inserta keyword nou in arbore
    ->realloc size nou pt keyword_list
    curent->nr_keyword++;
    curent->keyword_list=(char**)realloc(curent->keyword_list curent->nr_keyword*sizeof(char*));
    ->Alocă memorie pentru noul cuvânt la ultima poziție in keyword_list și copiază-l în acesta

+)void del_keyword(list_file *listfile,char *word,char *file_id,trie_nod root)

    Sterge un cuvânt-cheie dintr-un fisier existent.Dacă fisierul nu există, operatia esuează. Dacă fisierul există, dar nu are asociat acel cuvântcheie, operatia nu modifică sistemul, dar este considerată reusită.

    Verifică existența cuvântului-cheie: parcurge vectorul keyword_list al fișierului pentru a găsi poziția (indexul) cuvântului-cheie. Dacă acesta nu există în fișier, sistemul nu face nicio modificare.
    Trie Update:
    Localizează nodul frunză (sfârșit de cuvânt) al cuvântului-cheie în arborele Trie.
    Găsește și elimină eticheta de referință (list_reference) care indică fișierul curent din lista file_ref. Eliberează memoria acestei referințe.
    Decrementează contorul de fișiere care conțin cuvântul-cheie (count--).

    Actualizare date fișier :
    Eliberează memoria (free) pentru șirul cuvântului-cheie de la poziția index din vectorul keyword_list.
    Mută toate cuvintele-cheie din dreapta poziției index cu o poziție la stânga pentru a umple golul.Decrementează numărul total de cuvinte-cheie (nr_keyword--)

    Verifică dacă fișierul a devenit complet gol după ștergere (nr_keyword == 0).
    Dacă este gol, deconectează fișierul din lista dublu înlănțuită
    (gestionând corect cazurile: început, mijloc sau final de listă)
    Eliberează complet toate resursele fișierului (șirul id, vectorul keyword_list și structura list_file).

+)void swap(char *a, char *b)

    interschimbare 2 sir de caractere(ne ajuta pt sortare dupa)

+)void find_keyword(trie_nod root,char *word)
    gasim toate fisierele care contin cuvant "word"
    Căutarea în Trie: Apelează funcția search_keyword pentru a naviga în arborele multicăi de regăsire și a localiza nodul terminal (end-of-word) corespunzător cuvântului-cheie.

    Validarea rezultatulul: Verifică dacă nodul terminal este valid. Dacă nodul nu există (NULL), dacă nu este un cuvânt finalizat (count == 0), sau dacă nu are niciun fișier asociat (file_ref == NULL), se afișează EMPTY și execuția funcției se oprește.

    Colectarea datelor: Parcurge lista simplu înlănțuită de referințe (file_ref) pentru a număra totalul fișierelor care conțin cuvântul (nr_total_file).

    Extrage identificatorii (id) fișierelor din lista de referințe și îi stochează într-un tablou bidimensional alocat local (char s[nr_total_file][100]).

    Sortarea alfabetică: Aplică algoritmul Bubble Sort pe tabloul de șiruri de caractere. Se folosește funcția strcmp pentru a compara identificatorii și funcția swap pentru a-i interschimba, obținându-se astfel o ordine lexicografică strictă.

    Afișarea: Tipărește la consolă (sau în fișierul de ieșire) numărul total de fișiere, urmat de identificatorii acestora parcurgând tabloul sortat, respectând formatul impus de cerință

+)void print_sorted_list(list_reference list_ref, int nr_total_file)

    functie afiseaza toate fisiere in lista de referinta unui cuvant in ordine lexicografica
    folosim un vector bidimensional pt a stoca lista de file_id
    folosim algoritm buble sort pt a sorta
    folosim functia swap pt a interschimba sirul in vector bidimensional
+)void print_arbore(trie_nod root,char *aux,int k)
    va afisa toate cuvintele-cheie existente în arbore, în ordine lexicografică. Pentru fiecare cuvânt-cheie se vor afisa:
    1. cuvântul-cheie;
    2. numărul de fisiere asociate;
    3. identificatorii acestor fisiere în ordine lexicografică\
    foosim un sir de caracter aux initializat in main ca argument care ne ajuta sa stocheaza cuvantul obtinut

    condiția de oprire a funcției recursive: atunci când se găsește un cuvânt complet și se afișează(curent->count!=0)
    dupa ce afisam pe sirul/cuvantul "aux" folosim functie print_sorted_list pt a afisa toate fisiere legata de cuvantul "aux" in ordine cerut

    functie recursive intr-un loop for sa verifice toate litere de la a->z, sa se aduce pana la jos la nivel de nod frunza cu conditii:
     if(curent->child[i]!=NULL)
        {
            aux[k]=i+'a';
            print_arbore(root->child[i],aux,k+1);//Continuă să coboare mai jos
            //când deschizi ușa i (current->child[i]),
            //trebuie să pășești în acea cameră pentru a continua explorarea.
        }

+)heap init_heap(int cap)
    functia pt a initializa heapul pt functie TOPK, care stocheaza 
    un array h->vect_ele =>Vectorul vect_ele din Heap-ul este folosit pentru a stoca pointeri către fișiere (list_file),
    (nu pentru a stoca toate datele fișierelor , DOAR POINTER)
    nr_elemente de inceput este 0
    Se alocă un tablou de pointeri, deci dimensiunea trebuie să fie dimensiunea unui pointer, nu a întregii structuri.
+)void swap_nod(list_file *a, list_file *b)

    interschime 2 pointer de tip list_file(folosim in modificare heap)

+)int compare_nod(list_file a,list_file b)

    se compara 2 elemente in heap dupa scorul ei , 
    daca a->scor mai mare return 1
    daca b->scor mai  mare return 0
    daca sunt egal
        =>comparam ID, dupa ordine lexicografica , mai mic sta in fata

+)void heapify(heap h, int current)

    Scopul este de a restabili proprietatea de Max Heap pentru un subarbore cu rădăcina în current. care este ca nod parinti trebuie sa fiu mai mare decat noduri copii
    
    ->Se determină pozițiile în tablou (array) ale celor doi copii ai nodului curent: fiul stâng (2 * current + 1) și fiul drept (2 * current + 2).

    ->Căutarea maximului local: Se presupune inițial că nodul curent (current) este maximul.
    Se verifică fiul stâng: dacă există în limitele heap-ului și este "mai mare" (având o prioritate superioară conform funcției compare_nod) decât maximul actual, acesta devine noul maxim.
    Se verifică fiul drept similar, actualizând indexmax dacă este cazul.

    ->Dacă maximul găsit nu este nodul curent (indexmax != current), înseamnă că proprietatea de Max-Heap a fost încălcată/stricata. Se interschimbă referințele fișierelor între nodul curent și copilul maxim apelând swap_nod.

    ->Propagarea recursivă (Sinking):Deoarece elementul curent(curent) a fost interschimbat (swap) într-o poziție mai joasă, funcția heapify este apelată recursiv pe noul indice max(indexmax) pentru a asigura că elementul continuă să fie mutat în jos până ajunge în poziția corectă, menținând astfel integritatea întregului Max-Heap.

+)void create_max_heap(heap h, list_reference ref_file)

    scopul e sa transformam un heap random intr-un heap de forma max_heap cu proprietatea ca nodul parinte trebuie sa fie mai mare decat noduri copii

    dar inainte sa transformam heap , trebuie sa adaugam toate pointeri de fisier in lista de referinta (ref_file) in heap
    h->nr_elemente=nr total de pointer fisier in lista
    si facem un for de la o pana la h->nr_elemente sa copiem fiecare care pointer de fisier in h->vect_ele

    dupa ce am adaugat toate elemente de la ref_file in heap
    facem cu un for inverse de la i=(n-1)/2 pana la i=0 si pentru fiecare pas, apelam fucntie heapify(h,i) pe pozitia i

    traversam invers doar pe juma de array pt ca stim ca in array de heap,juma de array este nodul frunze, dar noi vrem sa apelam heapify doar pe nodul parinti, care sunt cu index de la 0 pana la (n-1)/2
    si traversam invers pt ca nodul cu index 0 este root, atucni daca vrem sa lucrem bottom up- trebuie sa facem loop inverse

+)list_file extragere(heap h)

    Extrage și returnează fișierul cu cea mai mare prioritate (rădăcina) din Max-Heap. Această funcție este esențială pentru comanda TOPK, permițând obținerea pe rând a celor mai relevante fișiere.

    Verifică dacă heap-ul este alocat și conține elemente. Dacă este gol, afișează EMPTY și se oprește.
    Salvează fișierul cu scorul maxim, care se află întotdeauna pe prima poziție (vect_ele[0])
    Mută ultimul element din heap pe prima poziție și scade dimensiunea totală a heap-ului (nr_elemente--).
    Apelează funcția heapify(h, 0) pentru a coborî noua rădăcină pe poziția corectă, restabilind astfel proprietatea fundamentală de Max-Heap pentru restul elementelor.

+)void topk(trie_nod root,char *word,int k)

    Determină și afișează primele k fișiere cu cel mai mare scor de relevanță asociate unui cuvânt-cheie dat, utilizând o structură de date de tip Max-Heap.

    ->Caută nodul terminal al cuvântului în arborele Trie folosind search_keyword. Dacă respectivul cuvânt nu este găsit, afișează EMPTY și oprește execuția.
    ->: Creează un Max-Heap (init_heap) cu o capacitate perfect adaptată la numărul de fișiere asociate cuvântului (endofword->count).
    ->transformam heapul care tocmai am alocat intre max_heap cu functie create_max_heap(h, ref_life) list_reference ref_file=endofword->file_ref;
    -> Extragerea rezultatelor:
    Gestionează cazurile:
    -dacă heap-ul este gol, afișează EMPTY.
    -Dacă numărul de fișiere care conțin cuvântul este mai mic decât k, extrage și afișează toate fișierele disponibile.
    -În caz contrar, apelează succesiv funcția extragere pentru a scoate exact primele k fișiere.
    
    ->Odată ce rezultatele au fost afișate, eliberează imediat memoria alocată temporar pentru tabloul intern al heap-ului (vect_ele) și pentru structura în sine

+)trie_nod search_prefix(trie_nod root,char *prefix)

    fucntioneaza exact la fel ca functie search_keyword
    dar in loc sa mergem pana la sfarsitul cuvantul, megrem doar pana la ultima litere al lui prefix, si functia returneaza ultima litera in prefix

+)void going_to_the_end(trie_nod curent, char ***s,int *capac,int *nr_file)

    Parcurge (DFS) subarborele Trie pornind de la un nod specific (reprezentând sfârșitul unui prefix) pentru a colecta toți identificatorii unici ai fișierelor care conțin cuvinte derivate din acel prefix.
    ->Dacă nodul curent marchează sfârșitul unui cuvânt complet (count > 0), funcția îi accesează lista de referințe către fișiere (file_ref).
    ->Pentru fiecare fișier găsit, se verifică dacă identificatorul acestuia (id) a fost deja salvat în tabloul rezultatelor (s). Acest pas asigură respectarea cerinței: dacă un fișier apare prin mai multe cuvinte-cheie cu același prefix, el va fi salvat/afișat o singură dată.
    ->Tabloul de șiruri de caractere este gestionat dinamic prin pointeri multipli (char ***s).
    -Când numărul de fișiere găsite (*nr_file) atinge capacitatea curentă (*capac), capacitatea este dublată automat utilizând realloc.
    -Odată spațiul asigurat, se alocă memorie cu malloc pentru noul șir și se copiază id-ul fișierului.

    ->Funcția continuă să se auto-apeleze pentru toți copiii nenuli ai nodului curent (pe cele 26 de litere posibile), coborând până la baza arborelui pentru a găsi absolut toate extensiile posibile ale prefixului inițial.

+)void find_dupa_prefix(trie_nod root,char *prefix)

    Identifică și afișează toate fișierele unice care conțin cel puțin un cuvânt-cheie ce începe cu un prefix specificat, ordonând rezultatele lexicografic.

    ->Apelează funcția search_prefix pentru a găsi în arborele Trie nodul corespunzător ultimului caracter din prefix. Dacă prefixul nu există, se afișează EMPTY și funcția se oprește.
    ->Alocă dinamic un tablou de pointeri (char s) cu o capacitate inițială minimă (2), conceput pentru a stoca eficient identificatorii fișierelor.
    ->Apelează funcția ajutătoare going_to_the_end, care parcurge întregul subarbore pornind de la nodul prefixului. Aceasta extrage referințele fișierelor asociate cuvintelor complete și le stochează în tabloul dinamic s, asigurându-se că un fișier este salvat o singură dată (deduplicare).
    ->: Dacă au fost găsite fișiere, se aplică algoritmul Bubble Sort pe tabloul s pentru a ordona identificatorii strict lexicografic.
    ->Tipărește numărul total de fișiere găsite, urmat de lista identificatorilor sortați

+) void free_trie(trie_nod root)
    eliberam memorie pt arbore trie care am folosit de la inceput
    ->Funcția utilizează recursivitatea pentru a parcurge arborele în adâncime. Aceasta vizitează și eliberează mai întâi toți copiii (cele 26 de ramuri posibile) înainte de a procesa nodul părinte, garantând că nicio legătură nu este "tăiată" prematur.
    ->Eliberează lista de referințe (file_ref) din acest nod (dacă există).
    ->Se eliberează doar pointer referințelor, NU fișierul original (temp_ref->file_ptr).

+)void free_file_list(list_file filelist)

    eliberam memorie pt lista dublu inlantuita de fisiere care am folosit de la inceput
    ->eliberam sirul id
    ->eliberam vector bidimensional care stocheaza toate keywords:
        p1: eliberam intai fiecare keyword in vectori
        p2: eliberam vector

III, MAIN

    ->Creează structurile de bază (lista dublu înlănțuită și rădăcina arborelui Trie). 
    Deschide indexare.in pentru citire și folosește freopen pentru a redirecționa automat tot output-ul standard (printf) în fișierul indexare.out
    ->Citește numărul total de operații și parcurge fiecare linie. 
    Folosește un set de instrucțiuni condiționale (if cu strcmp) pentru a identifica tipul comenzii (ADD, DEL, ADDKW, FIND, TOPK, PRINT, PREFIX),
     a extrage argumentele necesare și a apela funcția corespunzătoare.
    ->La finalizarea tuturor comenzilor, apelează funcțiile globale de curățare (free_file_list și free_trie), închide fișierele
