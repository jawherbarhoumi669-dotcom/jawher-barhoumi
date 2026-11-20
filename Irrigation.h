#ifndef IRRIGATION_H_INCLUDED
#define IRRIGATION_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



/* ==================== STRUCTURES ==================== */
typedef struct
{
    int id_capteur;
    float longitude;
    float latitude;
    int id_parcelle;
    int etat;
} capteur;

typedef struct
{
    int id_parcelle;
    char nom_parcelle[20];
    capteur capteurs[10];
    float seuil_irrigation_min;
    int nb_capteur;
} parcelle;

typedef struct
{
    int id_releve;
    int id_capteur;
    char date_hr[20];
    float val_hum;
} Historique;

/* ==================== GESTION DES PARCELLES ==================== */
int rechercherParcelleParID(parcelle parcelles[], int nbp, int id);
void ajouterParcelle(parcelle parcelles[],int*nbp);
void modifierParcelle(parcelle parcelles[], int nbp);
void supprimerParcelle(parcelle parcelles[], int *nbp, int pos);
void afficherParcelles(parcelle parcelles[],int nbp,capteur capteurs[],int nbC);

/* ==================== GESTION DES CAPTEURS ==================== */
void ajouterCapteur(capteur capteurs[],int *nb_capteur);
void modifierCapteur(capteur capteurs[], int nb_capteur);
void supprimerCapteur(capteur capteurs[],int *nb_capteur,int pos);
void afficherCapteurs(capteur capteurs[],int nb_capteur);

/* ==================== RELEVES ET SIMULATION ==================== */

void enregistrerReleve(int id_capteur, float humidite,Historique releves[], int *nbR);
void declencherReleve(capteur capteurs[], int nbc,parcelle parcelles[], int nbP,Historique releves[], int *nbR);
void simulerCampagne(parcelle parcelles[], int nbP,capteur capteurs[], int nbC,Historique releves[], int *nbR);
void afficherDernierEtat(capteur capteurs[], int nbC,Historique releves[], int nbR);

/* ==================== STATISTIQUES ET HISTORIQUE ==================== */
void consulterHistorique(Historique releves[],int nbR);
float calculerMoyenne(Historique releves[],int nbR);
float calculerMinimum(Historique releves[],int nbR);
float calculerMaximum(Historique releves[],int nbR);
void afficherParcellesPrioritaires(parcelle parcelles[], int nbP,capteur capteurs[], int nbC,Historique releves[], int nbR);
void trierReleves(Historique releves[], int nbR);
void rechercherCapteurParID(int id,capteur capteurs[], int nbC);
void rechercherCapteurParCoordonnes(float longitude,float latitude,capteur capteurs[], int nbC);

/* ==================== SAUVEGARDE ==================== */
void sauvegarderParcelles(parcelle parcelles[], int nbp);
void sauvegarderCapteurs(capteur capteurs[], int nbC);
void sauvegarderReleves(Historique releves[],int nbR);

void quitter(parcelle parcelles[], int nbP, capteur capteurs[], int nbC, Historique releves[], int nbR);


#endif

















