#include "tema2.h"

int main()
{
    list_file headlist= NULL;

    trie_nod root =createNode();

    FILE *f;
    f=fopen("indexare.in","r");//deschide indexare.in in read-mode only
    if(f==NULL)//verificam daca am deschis bine fisier
    {
        printf("ERROR\n");
        return 1;
    }
    
    FILE *f_out;
    f_out=freopen("indexare.out","w",stdout);//se pune toate ouput-uri in stdout in fisier indexare.out
    if(f_out==NULL)
    {
        printf("ERROR\n");
        return 1;
    }

    int nr_comenzi;
    fscanf(f,"%d",&nr_comenzi);//citeste un nr intreg in fisier indexare.in in var nr_comezi care este nr total de comenzi
    for(int i=0;i<nr_comenzi;i++)
    {
        char command_titlu[50];
        fscanf(f,"%s",command_titlu);
        if(strcmp(command_titlu,"ADD")==0)
        {
            char identificator[100];
            fscanf(f,"%s",identificator);
            int scor;
            fscanf(f,"%d",&scor);
            int nr_keyword;
            fscanf(f,"%d",&nr_keyword);
            char **vect_sir=(char**)malloc(nr_keyword*sizeof(char*));
            int nr_word_unic=0; //Se numără numărul de keywords reale (fără duplicate)
            for(int j=0;j<nr_keyword;j++)
            {
                char temp[100];
                fscanf(f, "%s",temp);
                
                //Dacă la ADD apar cuvinte duplicate în aceeași comandă, ele vor fi considerate o singură dată
                int repetat=0;
                for(int k=0;k<nr_word_unic;k++)
                {
                    if(strcmp(vect_sir[k],temp)==0)
                    {
                        repetat=1;
                        break;
                    }
                }
                
                if(!repetat)
                {
                    int a=strlen(temp);
                    vect_sir[nr_word_unic]=(char*)malloc((a+1)*sizeof(char));
                    strcpy(vect_sir[nr_word_unic],temp);
                    nr_word_unic++;
                }
            }
            int lungime=strlen(identificator);
            add_file(&headlist,lungime,identificator,scor,nr_word_unic,vect_sir,root);
            for(int i=0;i<nr_word_unic;i++)
            {
                free(vect_sir[i]);
            }
            free(vect_sir);
        }
        if(strcmp(command_titlu,"DEL")==0)
        {
            char identificator[100];
            fscanf(f,"%s",identificator);
            del_file(&headlist,identificator,root);
        }
        if(strcmp(command_titlu,"ADDKW")==0)
        {
            char identificator[100];
            fscanf(f,"%s",identificator);
            char word[100];
            fscanf(f,"%s",word);
            add_keyword(headlist,word,identificator,root);
        }
        if(strcmp(command_titlu,"DELKW")==0)
        {
            char identificator[100];
            fscanf(f,"%s",identificator);
            char word[100];
            fscanf(f,"%s",word);
            del_keyword(&headlist,word,identificator,root);
        }
        if(strcmp(command_titlu,"FIND")==0)
        {
            char word[100];
            fscanf(f,"%s",word);
            find_keyword(root,word);
        }
        if(strcmp(command_titlu,"PRINT")==0)
        {
            //verifica daca arbore Trie este gol sau nu
            if(root->nrfii==0)
            {
                printf("EMPTY\n");
            }
            else
            {
                char aux[100];
                int k=0;
                print_arbore(root,aux,k);
            }
        }
        if(strcmp(command_titlu,"TOPK")==0)
        {
            char word[100];
            fscanf(f,"%s",word);
            int k;
            fscanf(f,"%d",&k);
            topk(root,word,k);
        }
        if(strcmp(command_titlu,"PREFIX")==0)
        {
            char prefix[50];
            fscanf(f,"%s",prefix);
            find_dupa_prefix(root,prefix);
        }
    }
    free_file_list(headlist);
    free_trie(root);
    fclose(f);//inchidem fisier indexare.in
    fclose(f_out);//inchidem fisier indexare.out
    return 0;
}