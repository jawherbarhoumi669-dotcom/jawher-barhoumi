
import cv2
import mediapipe as mp
import time

# Importer les fonctions des autres fichiers
from gesture_recognition import reconnaitre_geste
from computer_control import executer_commande


# Initialisation de MediaPipe
mp_hands = mp.solutions.hands
mp_drawing = mp.solutions.drawing_utils

hands = mp_hands.Hands(
    static_image_mode=False,
    max_num_hands=1,
    min_detection_confidence=0.7,
    min_tracking_confidence=0.7
)


# Ouvrir la camera
cap = cv2.VideoCapture(0)

# Memoriser le dernier geste execute
dernier_geste = None

# Gestion du temps entre les commandes
dernier_temps = 0
delai = 1.5


while True:

    ret, frame = cap.read()

    if not ret:
        print("Erreur de lecture de la camera")
        break

    # Inverser horizontalement l'image
    frame = cv2.flip(frame, 1)

    # Convertir BGR vers RGB
    rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

    # Detecter la main
    results = hands.process(rgb)


    if results.multi_hand_landmarks:

        for hand_landmarks in results.multi_hand_landmarks:

            # Dessiner les points de la main
            mp_drawing.draw_landmarks(
                frame,
                hand_landmarks,
                mp_hands.HAND_CONNECTIONS
            )

            h, w, c = frame.shape


            # Afficher les numeros des points
            for id, lm in enumerate(hand_landmarks.landmark):

                cx = int(lm.x * w)
                cy = int(lm.y * h)

                cv2.putText(
                    frame,
                    str(id),
                    (cx, cy),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    0.5,
                    (0, 255, 0),
                    2
                )


            # Detection du pouce
            thumb_tip = hand_landmarks.landmark[4]
            thumb_ip = hand_landmarks.landmark[3]

            pouce = thumb_tip.x < thumb_ip.x


            # Detection des quatre autres doigts
            doigts = {
                "Index": (8, 6),
                "Majeur": (12, 10),
                "Annulaire": (16, 14),
                "Auriculaire": (20, 18)
            }

            etats = {}

            for nom, points in doigts.items():

                tip = hand_landmarks.landmark[points[0]]
                pip = hand_landmarks.landmark[points[1]]

                etats[nom] = tip.y < pip.y


            # Reconnaissance du geste
            geste = reconnaitre_geste(
                pouce,
                etats["Index"],
                etats["Majeur"],
                etats["Annulaire"],
                etats["Auriculaire"]
            )


            # Gestion du delai entre les commandes
            temps_actuel = time.time()

            if (
                geste != dernier_geste
                and geste != "GESTE_INCONNU"
                and temps_actuel - dernier_temps >= delai
            ):

                print("Geste reconnu :", geste)

                # Envoyer le geste vers computer_control.py
                executer_commande(geste)

                dernier_geste = geste
                dernier_temps = temps_actuel


            # Afficher l'etat du pouce
            cv2.putText(
                frame,
                "Pouce : " + ("Leve" if pouce else "Plie"),
                (10, 40),
                cv2.FONT_HERSHEY_SIMPLEX,
                0.6,
                (0, 255, 0),
                2
            )


            # Afficher les etats des autres doigts
            y = 75

            for nom, etat in etats.items():

                texte = nom + " : " + ("Leve" if etat else "Plie")

                cv2.putText(
                    frame,
                    texte,
                    (10, y),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    0.6,
                    (0, 255, 0),
                    2
                )

                y += 30


            # Afficher le geste reconnu
            cv2.putText(
                frame,
                "GESTE : " + geste,
                (10, 230),
                cv2.FONT_HERSHEY_SIMPLEX,
                0.8,
                (0, 0, 255),
                2
            )


    else:

        # Reinitialiser si aucune main n'est detectee
        dernier_geste = None

        cv2.putText(
            frame,
            "Aucune main detectee",
            (10, 40),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.8,
            (0, 0, 255),
            2
        )


    # Afficher la camera
    cv2.imshow("Reconnaissance des gestes", frame)


    # Quitter avec la touche Q
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


# Liberer les ressources
cap.release()
hands.close()
cv2.destroyAllWindows()
