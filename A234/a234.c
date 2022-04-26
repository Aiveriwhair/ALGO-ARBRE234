#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"file.h"

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

  if(a->t == 2) { //Dans le cas où t = 2 (2 fils), les clés commencent à 1 ainsi que les fils. ????
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


Arbre234 noeud_max (Arbre234 a)
{
  
}

void afficher_noeud(Arbre234 noeud){
  if (noeud->t == 0)
  {
    return;
  }

  printf("( ");
  if (noeud->t == 2)
  {
    printf("%d %d ",noeud->cles[0], noeud->cles[1]);
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
  int isRoot = 1;
pfile_t file = creer_file();
  enfiler(file, a);
  while (!file_vide(file))
  {
    Arbre234 noeud = defiler(file);
    if (!isRoot)
      afficher_noeud(noeud);
    else
      printf("( %d )\n", noeud->cles[1]); isRoot = 0;
    

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

void Affichage_Cles_Triees_Recursive (Arbre234 a)
{
  /* 
     Afficher les cles en ordre croissant
     Cette fonction sera recursive
  */
     
}

void Affichage_Cles_Triees_NonRecursive (Arbre234 a)
{
    /* 
     Afficher les cles en ordre croissant
     Cette fonction ne sera pas recursive
     Utiliser une pile
  */

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

  Afficher_Cles_Largeur(a);

//  test_AnalyseStructureArbre(a);
  //printf("Nombre de cles : %d\n", NombreCles(a));

  // Arbre234 recherche = RechercherCle(a, 13);
  // if(recherche == NULL) {
  //   printf("La cle n'existe pas\n");
  // }
  // else {
  //   printf("La cle existe\n");
  // }

   
    // printf ("clé max : %d \n", CleMax(a));
    // printf ("clé min : %d \n", CleMin(a));
}
