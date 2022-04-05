#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a234.h"

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))


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
  if (a->fils == NULL)
  {
    return a->t;
  }
  else
  {
    int keys = 0;
    for (int i = 0; i < a->t + 1; i++)
    {
      keys += a->t + NombreCles(a->fils[i]);
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

  if (a->t == 0)
    return a ->cles[0] ;
 
  Cmax0 = CleMax (a->fils [0]) ;
  Cmax1 = CleMax (a->fils [1]) ;
  Cmax2 = CleMax (a->fils [2]) ;
  Cmax3 = CleMax (a->fils [3]) ;

  /*int max = cles[0];
  for (int i = 2; i <= a->t; i ++){
    max = max(max,cle[i-1]);
  }*/
  return max (max (Cmax0,Cmax1),max (Cmax2,Cmax3));
  
}

int CleMin (Arbre234 a)
{
  //done
  int Cmin0, Cmin1, Cmin2, Cmin3 ;

  if (a == NULL)
    return NULL ;

  if (a->t == 0)
    return a ->cles[0] ;
 
  Cmin0 = CleMin (a->fils [0]) ;
  Cmin1 = CleMin (a->fils [1]) ;
  Cmin2 = CleMin (a->fils [2]) ;
  Cmin3 = CleMin (a->fils [3]) ;

  /*int min = cles[0];
  for (int i = 2; i <= a->t; i ++){
    min = min(min,cle[i-1]);
  }*/
  return min (min (Cmin0, Cmin1), min (Cmin2, Cmin3));
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
  /* 
     calculer le nombre de feuilles, de 2-noeuds, 3-noeuds,et 4-noeuds
  */
}

Arbre234 noeud_max (Arbre234 a)
{
  /*
    Retourne le noeud avec la somme maximale des cles internes
  */
  
  return NULL ;
}


void Afficher_Cles_Largeur (Arbre234 a)
{
  /*
    Afficher le cles de l'arbre a avec
    un parcours en largeur
  */

  return ;
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




int main (int argc, char **argv)
{
  Arbre234 a ;

  if (argc != 2)
    {
      fprintf (stderr, "il manque le parametre nom de fichier\n") ;
      exit (-1) ;
    }

  a = lire_arbre (argv [1]) ;

  printf ("==== Afficher arbre ====\n") ;  
  afficher_arbre (a, 0) ;

  // Arbre234 recherche = RechercherCle(a, 13);
  // if(recherche == NULL) {
  //   printf("La cle n'existe pas\n");
  // }
  // else {
  //   printf("La cle existe\n");
  // }

}
