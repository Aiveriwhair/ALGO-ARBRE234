#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"file.h"
#include "pile.h"

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

int EstFeuille(Arbre234 a)
{
  if(a->t == 2) {
    for (int i = 1; i <= 2; i++)
    {
      if (a->fils[i]->t != 0)
      {
        return 0;
      }
    }
  } else {
    for (int i = 0; i < a->t; i++)
    {
      if (a->fils[i]->t != 0)
      {
        return 0;
      }
    }
  }
  return 1;
}

int hauteur (Arbre234 a)
{
  int h0, h1, h2, h3 ;
  
  if (a == NULL)
    return 0 ;

  if (a->t == 0)
    return 0 ;

  h0 = hauteur (a->fils [0]) ;
  h1 = hauteur (a->fils [1]) ;
  h2 = hauteur (a->fils [2]) ;
  h3 = hauteur (a->fils [3]) ;

  return 1 + max (max (h0,h1),max (h2,h3)) ;
} 

int NombreCles (Arbre234 a)
{
  if (EstFeuille(a))
  {
    return a->t - 1;
  }
  else
  {
    int keys = 0;
    keys += a->t - 1;
    if(a->t == 2) {
      for (int i = 1; i <= 2; i++)
      {
        if(a->fils[i]->t != 0)
          keys += NombreCles(a->fils[i]);
      }
    } else {
      for (int i = 0; i < a->t; i++)
      {
        if(a->fils[i]->t != 0)
          keys += NombreCles(a->fils[i]);
      }
    }
    return keys;
  }
}

int CleMax (Arbre234 a)
{
  //done
  int Cmax0, Cmax1, Cmax2, Cmax3 ;

  if (a == NULL)
    return NULL ;

  if (a->t == 0){
    return NULL;

    }
 
  Cmax0 = CleMax (a->fils [0]) ;
  Cmax1 = CleMax (a->fils [1]) ;
  Cmax2 = CleMax (a->fils [2]) ;
  Cmax3 = CleMax (a->fils [3]) ;

  int maximum;
   if (a->t == 2)
    maximum = a->cles[1];
   else {
    maximum = a->cles[0];
    for (int i = 1; i < a->t - 1; i ++){
      maximum = max(maximum,a->cles[i]);
    }
  }

  return max(maximum,(max (max (Cmax0,Cmax1),max (Cmax2,Cmax3))) )   ;

  
}

int CleMin (Arbre234 a)
{
  //done
  int Cmin0, Cmin1, Cmin2, Cmin3 ;

  if (a == NULL)
    return NULL ;

  if (a->t == 0)
    return NULL ;

  int minimum;
  if (a->t == 2)
    minimum = a->cles[1];
  else{ 
    minimum = a->cles[0];
    for (int i = 1; i < a->t - 1; i ++){
      minimum = min(minimum,a->cles[i]);
    }
  }

  Cmin0 = CleMin (a->fils [0]) ;
  if (Cmin0 == NULL){
    Cmin0 = minimum;
  }
  Cmin1 = CleMin (a->fils [1]) ;
  if (Cmin1 == NULL){
    Cmin1 = minimum;
  }
  Cmin2 = CleMin (a->fils [2]) ;
  if (Cmin2 == NULL){
    Cmin2 = minimum;
  }
  Cmin3 = CleMin (a->fils [3]) ;
  if (Cmin3 == NULL){
    Cmin3 = minimum;
  }

  return min(minimum,(min (min (Cmin0, Cmin1), min (Cmin2, Cmin3))));
}

Arbre234 RechercherCle (Arbre234 a, int cle)
{
  if(a == NULL)
    return NULL;

  if(a->t == 2) { //Dans le cas o?? t = 2 (2 fils), les cl??s commencent ?? 1 ainsi que les fils. ????
    if(a->cles[1] == cle)
      return a;

    for(int i = 1; i <= a->t; i++) {
      Arbre234 n = RechercherCle(a->fils[i], cle);
      if(n != NULL)
        return n;
    }
  } else {
    for(int i = 0; i < a->t - 1; i++) {
      if(a->cles[i] == cle)
        return a;
    }

    for(int i = 0; i < a->t; i++) {
      Arbre234 n = RechercherCle(a->fils[i], cle);
      if(n != NULL)
        return n;
    }
  }

  return NULL;
}

void AnalyseStructureArbre (Arbre234 a, int *feuilles, int *noeud2, int *noeud3, int *noeud4)
{
  if (EstFeuille(a))
  {
    *feuilles += 1;
    if (a->t == 2)
      *noeud2 += 1;
    if (a->t == 3)
      *noeud3 += 1;
    if (a->t == 4)
      *noeud4 += 1;
      return;
  }

    if (a->t == 2)
      *noeud2 += 1;
    if (a->t == 3)
      *noeud3 += 1;
    if (a->t == 4)
      *noeud4 += 1;

    if (a->t == 2)
    {
      AnalyseStructureArbre(a->fils[1], feuilles, noeud2, noeud3, noeud4);
      AnalyseStructureArbre(a->fils[2], feuilles, noeud2, noeud3, noeud4);
    }
    else
    {
      for (int i = 0; i < a->t; i++)
      {
      AnalyseStructureArbre(a->fils[i], feuilles, noeud2, noeud3, noeud4);
      }
    }   
}

int sommeCles(Arbre234 a){
  int somme = 0;
  if (a->t == 2)
  {
    return a->cles[1];
  }
  
  for (int i = 0; i < a->t - 1; i++)
  {
    somme += a->cles[i];
  }
  return somme;
}

Arbre234 noeud_max (Arbre234 a)
{
  Arbre234 max = a;
  pfile_t file = creer_file();
  enfiler(file, a);
  while (!file_vide(file))
  {
    Arbre234 noeud = defiler(file);
    if(sommeCles(noeud) > sommeCles(max))
      max = noeud;
    if (noeud->t == 2)
    {
     for (int i = 1; i < 3; i++)
     {
       if (noeud->fils[i] != NULL)
       {
         enfiler(file, noeud->fils[i]);
       }
     }
    }
    else
    {
      for (int i = 0; i < noeud->t; i++)
      {
        if (noeud->fils[i] != NULL)
       {
         enfiler(file, noeud->fils[i]);
       }
      }
    } 
  }
  return max;
}

void afficher_noeud(Arbre234 noeud){
  if (noeud->t == 0)
  {
    return;
  }

  printf("( ");
  if (noeud->t == 2)
  {
    printf("%d ", noeud->cles[1]);
  }
  else
  {
    for (int i = 0; i < noeud->t - 1; i++)
    {
      printf("%d ", noeud->cles[i]);
    }
  }
  printf(")\n");
}

void Afficher_Cles_Largeur (Arbre234 a)
{
  pfile_t file = creer_file();
  enfiler(file, a);
  while (!file_vide(file))
  {
    Arbre234 noeud = defiler(file);
    afficher_noeud(noeud);

    if (noeud->t == 2)
    {
     for (int i = 1; i < 3; i++)
     {
       if (noeud->fils[i] != NULL)
       {
         enfiler(file, noeud->fils[i]);
       }
     }
    }
    else
    {
      for (int i = 0; i < noeud->t; i++)
      {
        if (noeud->fils[i] != NULL)
       {
         enfiler(file, noeud->fils[i]);
       }
      }
    } 
  }
}

void Lister_Cles(Arbre234 a, int* cles, int* pos)
{
  /*
    Retourne les cles de l'arbre a dans le tableau cles
    et le nombre de cles dans nb_cles
  */

  if(a == NULL)
    return;

  if(a->t == 2) { //Dans le cas o?? t = 2 (2 fils), les cl??s commencent ?? 1 ainsi que les fils. ????
    cles[*pos] = a->cles[1];
    (*pos)++;

    for(int i = 1; i <= a->t; i++) {
      Lister_Cles(a->fils[i], cles, pos);
      //pos+=a->fils[i]->t;
    }
  } else {
    for(int i = 0; i < a->t - 1; i++) {
      cles[*pos] = a->cles[i];
      (*pos)++;
    }

    for(int i = 0; i < a->t; i++) {
      Lister_Cles(a->fils[i], cles, pos);
      //pos+=a->fils[i]->t;
    }
  }
}

void Tri_Selection(int* T, int N)
{
  /*
    Tri par selection
  */

  int i,j,c;
  for(i=0;i<N-1;i++) {
    for(j=i+1;j<N;j++) {
      if(T[i]>T[j]) {
        c=T[i];
        T[i]=T[j];
        T[j]=c;
      }
    }
  }
}

void Affichage_Cles_Triees_Recursive (Arbre234 a)
{
  /* 
     Afficher les cles en ordre croissant
     Cette fonction sera recursive
  */
  int nb_cles = NombreCles(a);
  int* cles = malloc(sizeof(int) * nb_cles);
  int pos = 0;
  Lister_Cles(a, cles, &pos);
  Tri_Selection(cles, nb_cles);
  for(int i = 0; i < nb_cles; i++)
    printf("%d ", cles[i]);
  printf("\n");
  free(cles);
}

void Affichage_Cles_Triees_NonRecursive (Arbre234 a)
{
    /* 
     Afficher les cles en ordre croissant
     Cette fonction ne sera pas recursive
     Utiliser une pile
  */
  int nb_cles = NombreCles(a);
  int* cles = malloc(sizeof(int) * nb_cles);
  int pos = 0;
  ppile_t pile = creer_pile();
  empiler(pile, a);
  while(!pile_vide(pile)) {
    Arbre234 noeud = depiler(pile);
    if(noeud->t == 2) {
      cles[pos] = noeud->cles[1];
      pos++;
      for (int i = 1; i < 3; i++) {
        if (noeud->fils[i] != NULL) {
          empiler(pile, noeud->fils[i]);
        }
      }
    } else {
      for(int i = 0; i < noeud->t - 1; i++) {
        cles[pos] = noeud->cles[i];
        pos++;
      }
      for (int i = 0; i < noeud->t; i++) {
        if (noeud->fils[i] != NULL) {
          empiler(pile, noeud->fils[i]);
        }
      }
    }
  }
  Tri_Selection(cles, nb_cles);
  for(int i = 0; i < nb_cles; i++)
    printf("%d ", cles[i]);
  printf("\n");
  free(cles);
}


void Detruire_Cle (Arbre234 *a, int cle)
{
  /*
    retirer la cle de l'arbre a
  */

  return ;
}


void test_AnalyseStructureArbre(Arbre234 a){
  int nbFeuilles = 0;
  int nbNoeud2 = 0;
  int nbNoeud3 = 0;
  int nbNoeud4 = 0;
  AnalyseStructureArbre(a, &nbFeuilles, &nbNoeud2, &nbNoeud3, &nbNoeud4);
  printf("Structure de l'arbre :\n");
  printf("  Nombre de feuilles : %d\n", nbFeuilles);
  printf("  Nombre de noeud 2 : %d\n", nbNoeud2);
  printf("  Nombre de noeud 3 : %d\n", nbNoeud3);
  printf("  Nombre de noeud 4 : %d\n", nbNoeud4);
}


int main (int argc, char **argv)
{
  Arbre234 a;

  if (argc != 2)
    {
      fprintf (stderr, "il manque le parametre nom de fichier\n") ;
      exit (-1) ;
    }

  a = lire_arbre (argv [1]) ;

  printf ("==== Afficher arbre ====\n") ;  
  afficher_arbre (a, 0) ;
  afficher_noeud(noeud_max(a));

  Affichage_Cles_Triees_NonRecursive(a);

//  test_AnalyseStructureArbre(a);
  //printf("Nombre de cles : %d\n", NombreCles(a));

  // Arbre234 recherche = RechercherCle(a, 13);
  // if(recherche == NULL) {
  //   printf("La cle n'existe pas\n");
  // }
  // else {
  //   printf("La cle existe\n");
  // }

   
    // printf ("cl?? max : %d \n", CleMax(a));
    // printf ("cl?? min : %d \n", CleMin(a));
}
