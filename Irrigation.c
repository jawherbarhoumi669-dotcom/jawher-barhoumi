#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Irrigation.h"
int rechercherParcelleParID(parcelle parcelles[], int nbp, int id)
 {
    for (int i = 0; i < nbp; i++)
     {
        if (parcelles[i].id_parcelle == id)
        return i;
     }
 }

void ajouterParcelle(parcelle parcelles[],int *nbp)
{
   printf("donner lidentifiant du parcelle :  ");
   scanf("%d",&parcelles[*nbp].id_parcelle);
   printf("donner nom parcelle :  ");
   scanf("%s",&parcelles[*nbp].nom_parcelle);
   printf(" donner seuil_irrigation_min:  ");
   scanf("%f",&parcelle[s*nbp].seuil_irrigation_min);
   parcelles[*nbp].nbcapteur=0;
   (*nbp)++;
   printf("parcelle ajouter/n");
}

void modifierParcelle(parcelle parcelles[], int nbp)
{
   int id;
   printf("entrer l'id d'une parcelle");
   scanf("%d",&id);
   int indice=rechercherParcelleParID(parcelle , n,  id) ;
   if(indice ==-1)
   {
       printf("indice introuvable");
       return ;
   }
   printf("Parcelle actuelle : %s , Seuil : %.2f\n",parcelle[indice].nom_parcelle, parcelle[indice].seuil_irrigation_min);
   printf("donner le nouveau nom : /n");
   scanf("%s",parcelle[indice].nom_parcelle);
   printf("donner le nouveau seuil_irrigation_min : ");
   scanf("%f", &parcelles[index].seuil_irrigation_min);
   printf("modification avec succes\n ");
}

void supprimerParcelle(parcelle tab[], int *nbp, int pos)
{
    int i;

    if (pos == -1)
    {
        printf("Parcelle introuvable !");
        return;
    }

    for (i = pos; i < *nbp - 1; i++)
    {
        tab[i] = tab[i + 1];
    }

    (*nbp)--;
     printf("Parcelle supprimee avec succes !");
}
void afficherParcelles(parcelle parcelles[],int nbp,capteur capteurs[],int nbC));
{
    for(int i=0,i<n,i++)
    {
        printf("ID : %d\n", parcelles[i].id_parcelle);
        printf("Nom : %s\n", parcelles[i].nom_parcelle);
        printf("Seuil : %.2f\n", parcelles[i].seuil_irrigation_min);
        printf("Nombre de capteurs : %d\n",parcelles[i].nb_capteur);
        for(j = 0; j < parcelle[i].nbc; j++)
        {
            if(capteurs[j].id_parcelle ==parcelles[i].id_parcelle)
            {
                printf("ID capteur : %d\n",capteurs[j].id_capt);
                printf("Longitude : %.2f\n",capteurs[j].longtitude);
                printf("Latitude : %.2f\n",capteurs[j].latitude);
                printf("Etat : %d\n",capteurs[j].etat);
            }
        }
    }
}
int rechercherCapteurParID(capteur capteurs[], int n, int id)
{
    int i;

    for(i = 0; i < n; i++)
    {
        if(capteurs[i].id_capt == id)
            return i;
    }
}
void ajouterCapteur(capteur capteurs[],int*nbc)
{
    printf("Donner l'identifiant du capteur : ");
    scanf("%d", &capteurs[*nbc].id_capt);
    printf("Donner la longitude : ");
    scanf("%f", &capteurs[*nbc].longtitude);
    printf("Donner la latitude : ");
    scanf("%f", &capteurs[*nbc].latitude);
    printf("Donner l'identifiant de la parcelle : ");
    scanf("%d", &capteurs[*nbc].id_parcelle);
    printf("Donner l'etat du capteur (1: actif, 0: inactif) : ");
    scanf("%d", &capteurs[*nbc].etat);
    (*nbc)++;
    printf("\nCapteur ajoute avec succes !\n");
}
void modifierCapteur(capteur tab[], int nbCapteurs)













