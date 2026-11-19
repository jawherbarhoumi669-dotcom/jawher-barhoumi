#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Irrigation.h"
#define MAX_PARCELLES 50
#define MAX_CAPTEURS 100
#define MAX_RELEVES 1000


void gestiondesparcellesetchamps(parcelle parcelles[], int *nbP);
void gestiondescapteursdhumidite(capteur capteurs[], int *nbC));
void Relevesetsimulationdirrigation(capteur capteurs[], int nbC,parcelle parcelles[], int nbP,Historique releves[], int *nbR);
void Statistiquesethistorique(capteur capteurs[], int nbC,Historique releves[], int nbR);
void Quitter(parcelle parcelles[], int nbP,capteur capteurs[], int nbC,Historique releves[], int nbR);


int main()
{
    parcelle parcelles[MAX_PARCELLES];
    capteur capteurs[MAX_CAPTEURS];
    Historique releves[MAX_RELEVES];

    int nbP = 0;
    int nbC = 0;
    int nbR = 0;

    time_t secondes;
    struct tm instant;

     int choix;
    {
        time(&secondes);
        instant = *localtime(&secondes);
        printf("\n===== MENU PRINCIPAL - IRRIGATION INTELLIGENTE =====\n");
        printf("\n *** %d/%d/%d *** %d:%d:%d ***\n",instant.tm_mday,instant.tm_mon+1,instant.tm_year+1900,instant.tm_hour,instant.tm_min,instant.tm_sec);
        printf("1. Gestion des parcelles et champs\n");
        printf("2. Gestion des capteurs dhumidite\n");
        printf("3. Releves et simulation dirrigation\n");
        printf("4. Statistiques et historique\n");
        printf("0. Quitter\n");

        printf("\nDonner votre choix : ");
        scanf("%d", &choix);

        switch(choix)
        {
            case 1:
                gestiondesparcellesetchamps();
                break;

            case 2:
                gestiondescapteursdhumidite();
                break;

            case 3:
                Relevesetsimulationdirrigation();
                break;

            case 4:
                Statistiquesethistorique();
                break;

            case 0:
                Quitter();
                break;

            default:
                printf("Choix invalide !\n");
        }

    }

return 0;
}
void gestiondesparcellesetchamps()
{
    int choix;
    printf("\n===== GESTION DES PARCELLES =====\n");
    printf("1. Ajouter une parcelle\n");
    printf("2. Modifier une parcelle\n");
    printf("3. Supprimer une parcelle\n");
    printf("4. Afficher les parcelles\n");
    printf("0. Retour au menu principal\n");

    printf("Donner votre choix : ");
    scanf("%d", &choix);

    switch(choix)
        {
            case 1:
                ajouterParcelle();
                break;

            case 2:
                modifierParcelle();
                break;

            case 3:
                supprimerParcelle();
                break;

            case 4:
                afficherParcelles();
                break;

            case 0:
                printf("Retour au menu principal...\n");
                break;

            default:
                printf("Choix invalide !\n");
}}

void gestiondescapteursdhumidite()
{
    int choix;
    int id;
    float longitude,latitude;
    printf("\n===== GESTION DES CAPTEURS =====\n");
    printf("1. Ajouter un capteur d'humidité\n");
    printf("2. Modifier la position GPS ou la parcelle rattachée a un capteur\n");
    printf("3. Supprimer un capteur\n");
    printf("4. Afficher tous les capteurs ou filtrer les capteurs par parcelle\n");
    printf("0. Retour au menu principal\n");

    printf("Donner votre choix : ");
    scanf("%d", &choix);

    switch(choix)
        {
            case 1:
                ajouterCapteur();
                break;

            case 2:
                modifierpositon();
                break;

            case 3:
                supprimerCapteur();
                break;

            case 4:
                afficherCapteurs();
                break;

            case 0:
                printf("Retour au menu principal...\n");
                break;

            default:
                printf("Choix invalide !\n");}

}
void Relevesetsimulationdirrigation()
{
    int choix;
    printf("\n===== RELEVES ET SIMULATION =====\n");
    printf("1. Déclencher un relevé d'humidité\n");
    printf("2. Simuler une campagne de relevés\n");
    printf("3. Afficher le dernier état d'humidité enregistré pour chaque capteur.\n");
    printf("0. Retour au menu principal\n");

    printf("Donner votre choix : ");
    scanf("%d", &choix);
    switch(choix)
    {
       case 1:
                declencherReleve();
                break;

       case 2:
                simulerCampagne();
                break;

       case 3:
                afficherDernierEtat();
                break;
       case 0:
                printf("Retour au menu principal...\n");
                break;
       default:
                printf("Choix invalide !\n");

    }

}
void Statistiquesethistorique()
{
    int choix;
    printf("\n=====Statistiquesethistorique =====\n");
    printf("1.Consulter l'historique des relevés d'humidité sur une période donnée \n");
    printf("2. Calculer la moyenne\n");
    printf("3. Calculer le minimum\n");
    printf("4. Calculer le maximum\n");
    printf("5. Trier les releves\n");
    printf("6. Afficher les parcelles prioritaires\n");
    printf("7. Rechercher un capteur par ID ou GPS\n");
    printf("0.Retour au menu principal\n");

    printf("Donner votre choix : ");
    scanf("%d", &choix);
    switch(choix)
        {
            case 1:
                consulterHistorique();
                break;

            case 2:
                calculerMoyenne();
                break;

            case 3:
                calculerMinimum();
                break;

            case 4:
                calculerMaximum();
                break;

            case 5:
                trierReleves();
                break;
            case 6;
            afficherParcellesPrioritaires();
                break;           
            case 7:
                int id;
                printf("Donner l'ID du capteur : ");
                scanf("%d", &id);
                rechercherCapteurParID(id);
            case 8:
                float longitude,latitude;
                printf("Donner la longitude : ");
                scanf("%f", &longitude);

                printf("Donner la latitude : ");
                scanf("%f", &latitude);

                rechercherCapteurParCoordonnes(longitude,latitude);

            case 0:
                printf("Retour au menu principal...\n");
                break;

            default:
                printf("Choix invalide !\n");
        }
}

void Quitter()
{
    sauvegarderParcelles();
    sauvegarderCapteurs();
    sauvegarderReleves();

    printf("\nSauvegarde terminee !");
    printf("\nFermeture de l'application...");

}



