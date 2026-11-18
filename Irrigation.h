#ifndef IRRIGATION_H_INCLUDED
#define IRRIGATION_H_INCLUDED
#ifndef FICHIER_H
#define FICHIER_H
typedef struct
{
    int id_capt;
    float longtitude;
    float latitude;
    int id_parcelle;
    int etat;
}capteur;

typedef struct
{
    int id_parcelle;
    char nom_parcelle[20];
    capteur tabcapteurs[10];
    float seuil_irrigation_min;
    int nb_capteur;
}parcelle;

typedef struct
{
    int id_releve;
    int id_captuer;
    char date_hr[20];
    float val_hum;
}Historique;


int rechercherParcelleParID(parcelle parcelles[], int n, int id)
void ajouterParcelle(parcelle parcelles[],int*nbp);
void modifierParcelle(parcelle parcelles[], int nbp);
void supprimerParcelle(parcelle parcelles[], int *nbp, int pos);
void afficherParcelles(parcelle parcelles[],int nbp);

int rechercherCapteurParID(capteur capteurs[], int n, int id)
void ajouterCapteur(capteur capteurs[],int *nbc);
void modifierCapteur(capteur capteurs[], int nbCapteurs);
void supprimerCapteur(capteur capteurs[],int *nbc,int pos);
void afficherCapteurs(capteur capteurs[],int nbc);

void declencherReleve();
void simulerCampagne();
void afficherDernierEtat();

void consulterHistorique();
float calculerMoyenne();
float calculerMinimum();
float calculerMaximum();
void trierReleves();
void rechercherCapteurParID(int id);
void rechercherCapteurParCoordonnes(float longitude,float latitude);



void sauvegarderParcelles();
void sauvegarderCapteurs();
void sauvegarderReleves();

void quitter();


#endif
#endif


















