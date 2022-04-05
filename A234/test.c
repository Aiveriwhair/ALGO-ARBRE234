#include "lire_affichage.c"

int main()
{
    Arbre234 a = lire_arbre("data/arbre14");
    printf("Nombre de cles : %d", NombreCles(a));
    return 0;
}

