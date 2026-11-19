#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Irrigation.h"
#include <time.h>
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
   scanf("%f",&parcelles[s*nbp].seuil_irrigation_min);
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


void enregistrerReleve(int id_capteur, float humidite,Historique releves[], int *nbR)
{
    time_t secondes;
    struct tm instant;

    releves[*nbR].id_releve = *nbR + 1;
    releves[*nbR].id_capteur = id_capteur;
    releves[*nbR].val_hum = humidite;
    time(&secondes);
    instant = *localtime(&secondes);
    sprintf(releves[*nbR].date_hr,"%02d/%02d/%04d %02d:%02d:%02d",instant.tm_mday,instant.tm_mon + 1,instant.tm_year + 1900,instant.tm_hour,instant.tm_min,instant.tm_sec);
    (*nbR)++;
}
void declencherReleve(capteur capteurs[], int nbc,parcelle parcelles[], int nbP,Historique releves[], int *nbR);
{
    int id, i, j;
    int positionCapteur = -1;
    int positionParcelle = -1;
    float humidite;

    printf("Donner l'ID du capteur : ");
    scanf("%d", &id);
    /* Rechercher le capteur */
    for (i = 0; i < nbC; i++)
    {
        if (capteurs[i].id_capt == id)
        {
            positionCapteur = i;
            break;
        }
    }

    if (positionCapteur == -1)
    {
        printf("Capteur introuvable !\n");
        return;
    }
    /* Rechercher la parcelle du capteur */
    for (j = 0; j < nbP; j++)
    {
        if (parcelles[j].id_parcelle ==capteurs[positionCapteur].id_parcelle)
        {
            positionParcelle = j;
            break;
        }
    }
    if (positionParcelle == -1)
    {
        printf("Parcelle associee introuvable !\n");
        return;
    }
    /* Verifier la capacite de l'historique */
    if (*nbR >= MAX_RELEVES)
    {
        printf("Historique plein !\n");
        return;
    }
    /* Generer une humidite entre 0 et 100 */
    humidite = (float)(rand() % 101);
    printf("\nHumidite mesuree : %.2f %%\n", humidite);
    printf("Seuil minimal : %.2f %%\n",parcelles[positionParcelle].seuil_irrigation_min);

    /* Comparer avec le seuil */
    if (humidite < parcelles[positionParcelle].seuil_irrigation_min)
    {printf("Diagnostic : Irrigation necessaire !\n");}
    else
    {printf("Diagnostic : Humidite suffisante.\n");}

    /* Enregistrer dans l'historique */
    enregistrerReleve(id, humidite, releves, nbR);
    printf("Releve enregistre avec succes !\n");
}

void simulerCampagne(parcelle parcelles[], int nbP,capteur capteurs[], int nbC,Historique releves[], int *nbR)
{
    int id, i, j;
    int positionParcelle = -1;
    int nombreTrouve = 0;
    float humidite;
    float seuil;
    printf("Donner l'ID de la parcelle : ");
    scanf("%d", &id);

    /* Recherche de la parcelle */
    for (i = 0; i < nbP; i++)
    {
        if (parcelles[i].id_parcelle == id)
        {
            positionParcelle = i;
            break;
        }
    }

    if (positionParcelle == -1)
    {
        printf("Parcelle introuvable !\n");
        return;
    }
    seuil = parcelles[positionParcelle].seuil_irrigation_min;
    printf("Parcelle : %s\n",parcelles[positionParcelle].nom_parcelle);
    /* Parcourir tous les capteurs */
    for (j = 0; j < nbC; j++)
    {
        if (capteurs[j].id_parcelle == id)
        {
            nombreTrouve++;

            if (*nbR >= MAX_RELEVES)
            {
                printf("Historique plein !\n");
                return;
            }

            humidite = (float)(rand() % 101);
            printf("\nCapteur ID : %d\n", capteurs[j].id_capt);
            printf("Humidite : %.2f %%\n", humidite);
            if (humidite < seuil)
            {
                printf("Irrigation necessaire !\n");
            }
            else
            {
                printf("Humidite suffisante.\n");
            }

            enregistrerReleve(capteurs[j].id_capt,humidite,releves,nbR);
        }
    }

    if (nombreTrouve == 0)
    {
        printf("Aucun capteur dans cette parcelle.\n");
    }
    else
    {
        printf("\nCampagne terminee !\n");
        printf("Nombre de releves effectues : %d\n", nombreTrouve);
    }
}

void afficherDernierEtat(capteur capteurs[], int nbC,Historique releves[], int nbR)
{
    int i, j;
    int trouve;
    for (i = 0; i < nbC; i++)
    {
        trouve = 0;
        for (j = nbR - 1; j >= 0; j--)
        {
            if (releves[j].id_capteur == capteurs[i].id_capt)
            {
                printf("\nCapteur ID : %d\n", capteurs[i].id_capt);
                printf("Derniere humidite : %.2f %%\n",releves[j].val_hum);
                printf("Date : %s\n", releves[j].date_hr);
                trouve = 1;
                break;
            }
        }
        if (trouve == 0)
            printf("Aucun releve disponible.\n");
    }
}


void consulterHistorique(Historique releves[], int nbR)
{
    int i;
    int jour, mois, annee;
    int j1, m1, a1;
    int j2, m2, a2;
    int dateReleve, debut, fin;

    char dateDebut[20];
    char dateFin[20];

    printf("Donner la date de debut (jj/mm/aaaa) : ");
    scanf("%19s", dateDebut);*

    printf("Donner la date de fin (jj/mm/aaaa) : ");
    scanf("%19s", dateFin);

    sscanf(dateDebut, "%d/%d/%d", &j1, &m1, &a1);
    sscanf(dateFin, "%d/%d/%d", &j2, &m2, &a2);

    debut = a1 * 10000 + m1 * 100 + j1;
    fin = a2 * 10000 + m2 * 100 + j2;

    for (i = 0; i < nbR; i++)
    {
        sscanf(releves[i].date_hr, "%d/%d/%d",&jour, &mois, &annee);
        dateReleve = annee * 10000 + mois * 100 + jour;
        if (dateReleve >= debut && dateReleve <= fin)
        {
            printf("ID capteur : %d\n", releves[i].id_capteur);
            printf("Date : %s\n", releves[i].date_hr);
            printf("Humidite : %.2f %%\n", releves[i].val_hum);
        }
    }
}
void calculerMoyenne(Historique releves[], int nbR)
{
    int i;
    float S = 0;
    float m;
    if (nbR == 0)
    {
        printf("Aucun releve disponible !\n");
        return;
    }
    for (i = 0; i < nbR; i++)
    {
        s=s+ releves[i].val_hum;
    }
    m = s / nbR;
    printf("Moyenne d'humidite : %.2f %%\n", m);
}
float calculerMinimum(Historique releves[],int nbR)
{
    float min;
    if(nbR==0)
    {
        printf("aucun releve disponible");
        return ;
    }
    min=releves[0].val_hum;
    for(int i=0;i<nbR;i++)
    {
        if(releves[i].val_hum<min)
        {
            min=releves[i].val_him;
        }
    }
     printf("Humidite minimale : %.2f %%\n", minimum);
}
float calculerMaximum(Historique releves[],int nbR)
{
    float min;
    if(nbR==0)
    {
        printf("aucun releve disponible");
        return ;
    }
    max=releves[0].val_hum;
    for(int i=0;i<nbR;i++)
    {
        if(releves[i].val_hum>max)
        {
            max=releves[i].val_him;
        }
    }
     printf("Humidite maximale : %.2f %%\n", minimum);
}
void afficherParcellesPrioritaires(parcelle parcelles[], int nbP,capteur capteurs[], int nbC,Historique releves[], int nbR)




































