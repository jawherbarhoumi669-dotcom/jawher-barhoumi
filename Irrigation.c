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
    return -1;
 }

void ajouterParcelle(parcelle parcelles[], int *nbP)
{
    int id ;
    printf("donner id parcelles :");
    scanf("%d",&id);
    if (rechercherParcelleParID(parcelles, *nbP, id) != -1)
    {
        printf("La parcelle existe deja.\n");
        return;
    }
        parcelles[*nbP].id_parcelle = id;
        printf("donner nom parcelle");
        scanf("%19s",&parcelles[*nbP].nom_parcelle);
        printf("donner seuil d'iirrig min");
        scanf("%f",&parcelles[*nbP].seuil_irrigation_min);
        parcelles[*nbP].nb_capteur = 0;
        (*nbP)++;
        printf("parcelle ajoute avec succe");
}
void modifierParcelle(parcelle parcelles[], int nbP )
{
    int id ;
    printf("donner l'identifiant du parcellle que tu veus modifier");
    scanf("%d",&id);
    int index=rechercherParcelleParID( parcelles, nbP,  id);
    if (index== -1){
        printf("identifiant introuvable");
        return;
    }
    while (getchar() != '\n'); // Vider le buffer avant fget

    printf("donner nouveau nom");
    fgets(parcelles[index].nom_parcelle,20,stdin);
    parcelles[index].nom_parcelle[strcspn(parcelles[index].nom_parcelle, "\n")] = '\0'; // Retirer le \n
    printf("donner nouveau seuil irrig mmin");
    scanf("%f",&parcelles[index].seuil_irrigation_min);
    printf("Parcelle modifiee avec succes.\n");
}
void supprimerParcelle(parcelle parcelles[],int *nbP,int pos)
{
    int id;
    printf("donner l'identifiant du parcellle que tu veus supprimer");
    scanf("%d",&id);
    int index=rechercherParcelleParID( parcelles, *nbP,  id);
    if (index==-1){
        printf("parcelle deja introuvable");
        return  ;
    }
    for (int i=index; i<(*nbP)-1;i++){
        parcelles[i]=parcelles[i+1];
    }
    (*nbP)--;
}
void afficherParcelles(parcelle parcelles[],int nbP,capteur capteurs[],int nbC)
{
    for(int i=0;i<nbP;i++)
    {
        printf("ID : %d\n", parcelles[i].id_parcelle);
        printf("Nom : %s\n", parcelles[i].nom_parcelle);
        printf("Seuil : %.2f\n", parcelles[i].seuil_irrigation_min);
        printf("Nombre de capteurs : %d\n",parcelles[i].nb_capteur);
        for(int j = 0; j < nbC; j++)
        {
            if(capteurs[j].id_parcelle ==parcelles[i].id_parcelle)
            {
                printf("ID capteur : %d\n",capteurs[j].id_capteur);
                printf("Longitude : %.2f\n",capteurs[j].longitude);
                printf("Latitude : %.2f\n",capteurs[j].latitude);
                printf("Etat : %d\n",capteurs[j].etat);
            }
        }
    }
}
void ajouterCapteur(capteur capteurs[],int *nbC)
{
    int id;
    printf("Donner ID capteur : ");
    scanf("%d", &id);
    for (int i = 0; i < *nbC; i++)
    {
        if (capteurs[i].id_capteur == id)
        {
            printf("Le capteur existe deja.\n");
            return;
        }
    }
    capteurs[*nbC].id_capteur= id;
    printf("Donner ID de la parcelle associee : ");
    scanf("%d", &capteurs[*nbC].id_parcelle);
    printf("Donner longitude du capteur : ");
    scanf("%f", &capteurs[*nbC].longitude);
    printf("Donner latitude du capteur : ");
    scanf("%f", &capteurs[*nbC].latitude);
    printf("Donner etat du capteur (1 = actif, 0 = inactif) : ");
    scanf("%d", &capteurs[*nbC].etat);
    (*nbC)++;
    printf("Capteur ajoute avec succes.\n");
}
void modifierCapteur(capteur capteurs[],int nbC)
{
    int trouve=0;
    int id_parc ;
    printf("donner l'id du parcelle rattache au capteur  tu veux modifier son position GPS");
    scanf("%d",&id_parc);
    for (int i=0;i<nbC;i++)
        {
        if (capteurs[i].id_parcelle==id_parc)
        {
            printf("donner la nouveau latitude\n");
            scanf("%f",&capteurs[i].latitude);
            printf("donner la nouveau longitude\n");
            scanf("%f",&capteurs[i].longitude);
            trouve =1;
        }

}
     if (trouve==0){
        printf("aucune capteur trouve pour ce idb de parcelle");
     }
}
void supprimercapteur(capteur capteurs[], int *nbC)
{
    int index = -1;
    int id;
    printf("Donner ID du capteur que vous voulez supprimer : ");
    scanf("%d", &id);
    for (int i = 0; i < *nbC; i++)
    {
        if (capteurs[i].id_capteur == id)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        printf("Ce capteur n'existe pas.\n");
        return;
    }
    for (int i = index; i < (*nbC) - 1; i++)
    {
        capteurs[i] = capteurs[i + 1];
    }
    (*nbC)--;
    printf("Capteur supprime avec succes.\n");
}
void afficherCapteursParParcelle(capteur capteurs[], int nbC)
{
    if (nbC== 0) {
        printf("\nAucun capteur enregistre.\n");
        return;
    }
    int id_parc, trouve = 0;
    printf("Donner l'ID de la parcelle : ");
    scanf("%d", &id_parc);

    printf("\n--- Capteurs de la parcelle ID %d ---\n", id_parc);
    for (int i = 0; i < nbC; i++) {
        if (capteurs[i].id_parcelle == id_parc)
            {
            printf("ID Capteur : %d | GPS : (%.4f, %.4f)\n", capteurs[i].id_capteur, capteurs[i].latitude, capteurs[i].longitude);
            trouve = 1;
            }
    }
    if (trouve == 0)
    {
        printf("Aucun capteur rattache a cette parcelle.\n");
    }
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
void declencherReleve(capteur capteurs[], int nbC,parcelle parcelles[], int nbP,Historique releves[], int *nbR)
{   int MAX_RELEVES;
    int id, i, j;
    int positionCapteur = -1;
    int positionParcelle = -1;
    float humidite;
    printf("Donner l'ID du capteur : ");
    scanf("%d", &id);
    /* Rechercher le capteur */
    for (i = 0; i < nbC; i++)
    {
        if (capteurs[i].id_capteur == id)
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
{   int MAX_RELEVES;
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
            printf("\nCapteur ID : %d\n", capteurs[j].id_capteur);
            printf("Humidite : %.2f %%\n", humidite);
            if (humidite < seuil)
            {
                printf("Irrigation necessaire !\n");
            }
            else
            {
                printf("Humidite suffisante.\n");
            }
            enregistrerReleve(capteurs[j].id_capteur,humidite,releves,nbR);
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
            if (releves[j].id_capteur == capteurs[i].id_capteur)
            {
                printf("\nCapteur ID : %d\n", capteurs[i].id_capteur);
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
    scanf("%19s", dateDebut);

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
float calculerMoyenne(Historique releves[], int nbR)
{
    int i;
    float S = 0;
    float m;
    if (nbR == 0)
    {
        printf("Aucun releve disponible !\n");
        return 0;
    }
    for (i = 0; i < nbR; i++)
    {
        S=S+ releves[i].val_hum;
    }
    m = S/ nbR;
    printf("Moyenne d'humidite : %.2f %%\n", m);
}
float calculerMinimum(Historique releves[],int nbR)
{
    float min;
    if(nbR==0)
    {
        printf("aucun releve disponible");
        return 0;
    }
    min=releves[0].val_hum;
    for(int i=0;i<nbR;i++)
    {
        if(releves[i].val_hum<min)
        {
            min=releves[i].val_hum;
        }
    }
     printf("Humidite minimale : %.2f %%\n", min);
}
float calculerMaximum(Historique releves[],int nbR)
{
    float max;
    if(nbR==0)
    {
        printf("aucun releve disponible");
        return 0 ;
    }
    max=releves[0].val_hum;
    for(int i=0;i<nbR;i++)
    {
        if(releves[i].val_hum>max)
        {
            max=releves[i].val_hum;
        }
    }
     printf("Humidite maximale : %.2f %%\n", max);
}

void afficherprioritaire(parcelle parcelles[], int nbP,capteur capteurs[], int nb_capteur,Historique releves[], int nbR)
{
    int trouve;
    int prioritaire = 0;
    if (nbR == 0)
    {
        printf("Aucun releve disponible.\n");
        return;
    }
    printf("\n===== PARCELLES PRIORITAIRES =====\n");
    for (int i = 0; i < nbP; i++)
    {
        trouve = 0;
        /* Parcourir les capteurs de la parcelle */
        for (int j = 0; j < parcelles[i].nb_capteur; j++)
        {
            int id = parcelles[i].capteurs[j].id_capteur;

            /* Chercher le dernier releve de ce capteur */
            for (int k = nbR - 1; k >= 0; k--)
            {
                if (releves[k].id_capteur == id)
                {
                    if (releves[k].val_hum <parcelles[i].seuil_irrigation_min)
                    {
                        trouve = 1;
                    }

                    break;
                }
            }

            if (trouve == 1)
                break;
        }
        /* Afficher la parcelle si elle est prioritaire */
        if (trouve == 1)
        {
            printf("ID parcelle : %d\n",
                   parcelles[i].id_parcelle);

            printf("Nom : %s\n",
                   parcelles[i].nom_parcelle);

            printf("Seuil minimal : %.2f %%\n",
                   parcelles[i].seuil_irrigation_min);

            printf("Cette parcelle necessite une irrigation.\n\n");

            prioritaire = 1;
        }
    }
    if (prioritaire == 0)
    {
        printf("Aucune parcelle prioritaire.\n");
    }
}


void trierReleves(Historique releves[], int nbR)
{
    int i, j, choix;
    int j1, m1, a1, j2, m2, a2;
    int date1, date2;
    Historique temp;

    if (nbR == 0)
    {
        printf("Aucun releve disponible !\n");
        return;
    }
    printf("\n===== TRI DES RELEVES =====\n");
    printf("1. Trier par date\n");
    printf("2. Trier par humidite croissante\n");
    printf("3. Trier par humidite decroissante\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    for (i = 0; i < nbR - 1; i++)
    {
        for (j = 0; j < nbR - 1 - i; j++)
        {
            if (choix == 1)
            {
                sscanf(releves[j].date_hr, "%d/%d/%d",&j1, &m1, &a1);
                sscanf(releves[j + 1].date_hr, "%d/%d/%d",&j2, &m2, &a2);

                date1 = a1 * 10000 + m1 * 100 + j1;
                date2 = a2 * 10000 + m2 * 100 + j2;

                if (date1 > date2)
                {
                    temp = releves[j];
                    releves[j] = releves[j + 1];
                    releves[j + 1] = temp;
                }
            }
            else if (choix == 2)
            {
                if (releves[j].val_hum >releves[j + 1].val_hum)
                {
                    temp = releves[j];
                    releves[j] = releves[j + 1];
                    releves[j + 1] = temp;
                }
            }

            else if (choix == 3)
            {
                if (releves[j].val_hum <releves[j + 1].val_hum)
                {
                    temp = releves[j];
                    releves[j] = releves[j + 1];
                    releves[j + 1] = temp;
                }
            }
        }
    }

    if (choix < 1 || choix > 3)
    {
        printf("Choix invalide !\n");
        return;
    }
    for (i = 0; i < nbR; i++)
    {
        printf("ID : %d | Humidite : %.2f %% | Date : %s\n",releves[i].id_releve,releves[i].val_hum,releves[i].date_hr);
    }
}
void rechercherCapteurParID(int id, capteur capteurs[], int nbC)
{
    int i;
    int trouve = 0;
    for (i = 0; i < nbC; i++)
    {
        if (capteurs[i].id_capteur == id)
        {
            printf("\nCapteur trouve !\n");
            printf("ID : %d\n", capteurs[i].id_capteur);
            printf("Longitude : %.6f\n", capteurs[i].longitude);
            printf("Latitude : %.6f\n", capteurs[i].latitude);
            printf("ID parcelle : %d\n", capteurs[i].id_parcelle);

            trouve = 1;
            break;
        }
    }
    if (trouve == 0)
    {
        printf("Capteur introuvable !\n");
    }
}
void rechercherCapteurParCoordonnes(float longitude, float latitude,capteur capteurs[], int nbC)
{
    int i;
    int trouve = 0;
    for (i = 0; i < nbC; i++)
    {
        if (capteurs[i].longitude == longitude && capteurs[i].latitude == latitude)
        {
            printf("\nCapteur trouve !\n");
            printf("ID : %d\n", capteurs[i].id_capteur);
            printf("Longitude : %.6f\n", capteurs[i].longitude);
            printf("Latitude : %.6f\n", capteurs[i].latitude);
            printf("ID parcelle : %d\n", capteurs[i].id_parcelle);
            trouve = 1;
            break;
        }
    }
    if (trouve == 0)
    {
        printf("Capteur introuvable !\n");
    }
}
void sauvegarderParcelles(parcelle parcelles[], int nbp)
{
    FILE *f;
    int i;
    f = fopen("parcelles.txt", "w");
    if (f == NULL)
    {
        printf("Erreur ouverture fichier !");
        return;
    }
    for (i = 0; i < nbp; i++)
    {
        fprintf(f, "%d %s %.2f %d\n",parcelles[i].id_parcelle,parcelles[i].nom_parcelle,parcelles[i].seuil_irrigation_min,parcelles[i].nb_capteur);
    }
    fclose(f);
    printf("Sauvegarde des parcelles terminee !\n");
}
void sauvegarderCapteurs(capteur capteurs[], int nbC)
{
    FILE *f;
    int i;
    f = fopen("capteurs.txt", "w");
    if (f == NULL)
    {
        printf("Erreur ouverture fichier !");
        return;
    }
    for (i = 0; i < nbC; i++)
    {
        fprintf(f, "%d %.2f %.2f %d %d\n",capteurs[i].id_capteur,capteurs[i].longitude,capteurs[i].latitude,capteurs[i].id_parcelle,capteurs[i].etat);
    }
    fclose(f);
    printf("Sauvegarde des capteurs terminee !\n");
}
void sauvegarderReleves(Historique releves[], int nbR)
{
    FILE *f;
    int i;
    f = fopen("releves.txt", "w");
    if (f == NULL)
    {
        printf("Erreur ouverture fichier !");
        return;
    }
    for (i = 0; i < nbR; i++)
    {
        fprintf(f, "%d %d %s %.2f\n",releves[i].id_releve,releves[i].id_capteur,releves[i].date_hr,releves[i].val_hum);
    }
    fclose(f);
    printf("Sauvegarde des releves terminee !\n");
}
void quitter(parcelle parcelles[], int nbP, capteur capteurs[], int nbC, Historique releves[], int nbR)
{
    sauvegarderParcelles(parcelles, nbP);
    sauvegarderCapteurs(capteurs, nbC);
    sauvegarderReleves(releves, nbR);

    printf("Au revoir !");
}




