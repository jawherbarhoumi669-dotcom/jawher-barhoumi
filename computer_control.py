
import pyautogui
import os

def executer_commande(geste):

    if geste == "MAIN_OUVERTE":
        os.startfile("powerpnt")
        print("PowerPoint ouvert")

    elif geste == "POUCE_LEVE":
        os.startfile("chrome")
        print("Chrome ouvert")

    elif geste == "INDEX_LEVE":
        os.startfile("calc")
        print("Calculatrice ouverte")

    elif geste == "MAJEUR_LEVE":
        os.startfile("notepad")
        print("Bloc-notes ouvert")

    elif geste == "POING_FERME":
        pyautogui.hotkey("alt", "f4")
        print("Fenetre active fermee")

    elif geste == "ANNULAIRE_LEVE":
        pyautogui.hotkey("win", "down")
        print("Fenetre reduite")

    elif geste == "AURICULAIRE_LEVE":
        pyautogui.hotkey("alt", "tab")
        print("Changement d'application")

    else:
        print("Geste reconnu :", geste)
        print("Aucune commande associee")
