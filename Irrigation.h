#ifndef IRRIGATION_H_INCLUDED
#define IRRIGATION_H_INCLUDED
#ifndef FICHIER_H
#define FICHIER_H
typedef struct
{
    int id_capteur;
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

void enregistrerReleve(int id_capteur, float humidite,Historique releves[], int *nbR);
void declencherReleve(capteur capteurs[], int nbc,parcelle parcelles[], int nbP,Historique releves[], int *nbR);
void simulerCampagne(parcelle parcelles[], int nbP,capteur capteurs[], int nbC,Historique releves[], int *nbR);
void afficherDernierEtat(capteur capteurs[], int nbC,Historique releves[], int nbR);

void consulterHistorique(Historique releves[],int nbR);
float calculerMoyenne(Historique releves[],int nbR);
float calculerMinimum(Historique releves[],int nbR);
float calculerMaximum(Historique releves[],int nbR);
void afficherParcellesPrioritaires(parcelle parcelles[], int nbP,capteur capteurs[], int nbC,Historique releves[], int nbR)
void trierReleves();
void rechercherCapteurParID(int id);
void rechercherCapteurParCoordonnes(float longitude,float latitude);

void sauvegarderParcelles();
void sauvegarderCapteurs();
void sauvegarderReleves();

void quitter();


#endif
#endif
















