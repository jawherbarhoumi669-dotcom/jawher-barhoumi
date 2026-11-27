#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "irrigation.h"

#define MAX_PARCELLES 50
#define MAX_CAPTEURS 100
#define MAX_RELEVES 1000

void gestiondesparcellesetchamps(parcelle parcelles[], int *nbP, capteur capteurs[], int *nbC);
void gestiondescapteursdhumidite(capteur capteurs[], int *nbC, parcelle parcelles[], int nbP);
void Relevesetsimulationdirrigation(capteur capteurs[], int nbC, parcelle parcelles[], int nbP, Historique releves[], int *nbR);
void Statistiquesethistorique(parcelle parcelles[], int nbP, capteur capteurs[], int nbC, Historique releves[], int nbR);

int main(void)
{
    parcelle parcelles[MAX_PARCELLES];
    capteur capteurs[MAX_CAPTEURS];
    Historique releves[MAX_RELEVES];

    int nbP = 0;
    int nbC = 0;
    int nbR = 0;
    int choix;

    srand((unsigned int)time(NULL));

    do
    {
        time_t secondes;
        time(&secondes);
        struct tm instant = *localtime(&secondes);

        printf("\n===== MENU PRINCIPAL - IRRIGATION INTELLIGENTE =====\n");
        printf("*** %02d/%02d/%04d *** %02d:%02d:%02d ***\n",instant.tm_mday,instant.tm_mon + 1,instant.tm_year + 1900,instant.tm_hour,instant.tm_min,instant.tm_sec);
        printf("1. Gestion des parcelles et champs\n");
        printf("2. Gestion des capteurs d'humidite\n");
        printf("3. Releves et simulation d'irrigation\n");
        printf("4. Statistiques et historique\n");
        printf("0. Quitter\n");

        printf("\nDonner votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
            case 1:
                gestiondesparcellesetchamps(parcelles, &nbP, capteurs, &nbC);
                break;

            case 2:
                gestiondescapteursdhumidite(capteurs, &nbC, parcelles, nbP);
                break;

            case 3:
                Relevesetsimulationdirrigation(capteurs, nbC, parcelles, nbP, releves, &nbR);
                break;

            case 4:
                Statistiquesethistorique(parcelles, nbP, capteurs, nbC, releves, nbR);
                break;

            case 0:
                quitter(parcelles, nbP, capteurs, nbC, releves, nbR);
                break;

            default:
                printf("Choix invalide !\n");
        }
    } while (choix != 0);

    return 0;
}

/* ==================== 1. GESTION DES PARCELLES ==================== */
void gestiondesparcellesetchamps(parcelle parcelles[], int *nbP, capteur capteurs[], int *nbC)
{
    int choix;
    do
    {
        printf("\n===== GESTION DES PARCELLES =====\n");
        printf("1. Ajouter une parcelle\n");
        printf("2. Modifier une parcelle\n");
        printf("3. Supprimer une parcelle\n");
        printf("4. Afficher les parcelles\n");
        printf("0. Retour au menu principal\n");

        printf("Donner votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
            case 1:
                ajouterParcelle(parcelles, nbP, MAX_PARCELLES);
                break;

            case 2:
                modifierParcelle(parcelles, *nbP);
                break;

            case 3:
                supprimerParcelle(parcelles, nbP, capteurs, nbC);
                break;

            case 4:
                afficherParcelles(parcelles, *nbP, capteurs, *nbC);
                break;

            case 0:
                printf("Retour au menu principal...\n");
                break;

            default:
                printf("Choix invalide !\n");
        }
    } while (choix != 0);
}

/* ==================== 2. GESTION DES CAPTEURS ==================== */
void gestiondescapteursdhumidite(capteur capteurs[], int *nbC, parcelle parcelles[], int nbP)
{
    int choix;
    do
    {
        printf("\n===== GESTION DES CAPTEURS =====\n");
        printf("1. Ajouter un capteur\n");
        printf("2. Modifier un capteur\n");
        printf("3. Supprimer un capteur\n");
        printf("4. Afficher les capteurs\n");
        printf("0. Retour au menu principal\n");

        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
            case 1:
                ajouterCapteur(capteurs, nbC, MAX_CAPTEURS, parcelles, nbP);
                break;

            case 2:
                modifierCapteur(capteurs, *nbC);
                break;

            case 3:
                supprimerCapteur(capteurs, nbC, parcelles, nbP);
                break;

            case 4:
                afficherCapteurs(capteurs, *nbC);
                break;

            case 0:
                printf("Retour au menu principal...\n");
                break;

            default:
                printf("Choix invalide !\n");
        }
    } while (choix != 0);
}

/* ==================== 3. RELEVES ET SIMULATION ==================== */
void Relevesetsimulationdirrigation(capteur capteurs[], int nbC, parcelle parcelles[], int nbP, Historique releves[], int *nbR)
{
    int choix;
    do
    {
        printf("\n===== RELEVES ET SIMULATION =====\n");
        printf("1. Declencher un releve d'humidite\n");
        printf("2. Simuler une campagne de releves\n");
        printf("3. Afficher le dernier etat d'humidite enregistre pour chaque capteur\n");
        printf("0. Retour au menu principal\n");

        printf("Donner votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
            case 1:
                declencherReleve(capteurs, nbC, parcelles, nbP, releves, nbR, MAX_RELEVES);
                break;

            case 2:
                simulerCampagne(parcelles, nbP, capteurs, nbC, releves, nbR, MAX_RELEVES);
                break;

            case 3:
                afficherDernierEtat(capteurs, nbC, releves, *nbR);
                break;

            case 0:
                printf("Retour au menu principal...\n");
                break;

            default:
                printf("Choix invalide !\n");
        }
    } while (choix != 0);
}

/* ==================== 4. STATISTIQUES ET HISTORIQUE ==================== */
void Statistiquesethistorique(parcelle parcelles[], int nbP, capteur capteurs[], int nbC, Historique releves[], int nbR)
{
    int choix;
    do
    {
        printf("\n===== STATISTIQUES ET HISTORIQUE =====\n");
        printf("1. Consulter l'historique des releves sur une periode donnee\n");
        printf("2. Calculer la moyenne\n");
        printf("3. Calculer le minimum\n");
        printf("4. Calculer le maximum\n");
        printf("5. Afficher les parcelles prioritaires\n");
        printf("6. Trier les releves\n");
        printf("7. Rechercher un capteur par ID\n");
        printf("8. Rechercher un capteur par coordonnees\n");
        printf("0. Retour au menu principal\n");

        printf("Donner votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
            case 1:
                consulterHistorique(releves, nbR);
                break;

            case 2:
                calculerMoyenne(releves, nbR);
                break;

            case 3:
                calculerMinimum(releves, nbR);
                break;

            case 4:
                calculerMaximum(releves, nbR);
                break;

            case 5:
                afficherParcellesPrioritaires(parcelles, nbP, capteurs, nbC, releves, nbR);
                break;

            case 6:
                trierReleves(releves, nbR);
                break;

            case 7:
            {
                int id;
                printf("Donner l'ID du capteur : ");
                scanf("%d", &id);
                rechercherCapteurParID(id, capteurs, nbC);
                break;
            }

            case 8:
            {
                float longitude, latitude;
                printf("Donner la longitude : ");
                scanf("%f", &longitude);
                printf("Donner la latitude : ");
                scanf("%f", &latitude);
                rechercherCapteurParCoordonnes(longitude, latitude, capteurs, nbC);
                break;
            }

            case 0:
                printf("Retour au menu principal...\n");
                break;

            default:
                printf("Choix invalide !\n");
        }
    } while (choix != 0);
}
