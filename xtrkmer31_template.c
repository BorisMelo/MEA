#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#define SIZE_KMER 31

#include "generator.h"

#include "uthash.h"

int main (int argc, char *argv[])
{   
 int nb_read = 0;
 char READ[SIZE_READ];

 FILE* fichier = fopen("kmer31.txt", "r+");

//char *tableau_kmer[];
char valeur_kmer[31];

int i,j,k;

 k=0;  
 initGenerator();

    // table de hashage
    struct tab_kmer {
        char kmer[31];                    /* key */
        int occurence;
        UT_hash_handle hh;         /* makes this structure hashable */
    };

    struct tab_kmer *tableau_kmer = NULL;
    struct tab_kmer *s;
    

    //ajouter un item
    void add_kmer(char *val_kmer, int occ) {
     
        struct tab_kmer *tabKmer;
        tabKmer = (struct tab_kmer *)malloc(sizeof *tabKmer);

        strcpy(tabKmer->kmer, val_kmer);
       
        tabKmer->occurence = occ;
       
           HASH_ADD_STR( tableau_kmer, kmer, tabKmer);

    }

    struct tab_kmer *find_kmer(char* kmer) {
           struct tab_kmer *tabKmer;

           HASH_FIND_STR(tableau_kmer, kmer, tabKmer );
       return tabKmer;
    }

    /*struct tab_kmer *find_kmer_FB(char* kmer) {
           struct tab_kmer *tabKmer;

           HASH_FIND_STR(FB, kmer, tabKmer );
       return tabKmer;
    }*/

struct tab_kmer *kmer_found;
int cpt_nb_read = 0;

 while (getRead(READ))
   {
     nb_read = nb_read + 1;
     //if (nb_read%100 == 0){
    cpt_nb_read++;
    //printf ("%s\n",READ);

     for(i=0; i<SIZE_READ; i++){
       if((SIZE_READ-i)>=31){
        for(j=i; j<i+31; j++){
           valeur_kmer[j-i] = READ[j];
          // tableau_kmer[l][j] = READ[j];
        }

        kmer_found = find_kmer(valeur_kmer);
        if(kmer_found->kmer == NULL){
            //printf("kmer non trouvé");
            //printf("\n");
            add_kmer(valeur_kmer,1);
        }else{
            //printf("kmer trouvé");
            //printf("\n");
            kmer_found->occurence++;
    
            //printf("compteur kmer %s est %d",kmer_found->kmer, kmer_found->occurence );
            //printf("\n");
        }   

        //l++;  
        k++;        
        valeur_kmer[0]='\0';

       }
     }
    k=0;

   }

   for(s=tableau_kmer; s != NULL; s=(struct tab_kmer*)(s->hh.next)) {
	if (s->occurence >= 10) {
       		fprintf(fichier,"valeur kmer: %s \n occurrence: %d\n", s->kmer, s->occurence);
	}
   }
   fclose(fichier);

 exit (0);
}





