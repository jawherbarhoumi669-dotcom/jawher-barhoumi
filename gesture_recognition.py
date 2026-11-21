
def reconnaitre_geste(pouce, index, majeur, annulaire, auriculaire):

    # Main ouverte
    if pouce and index and majeur and annulaire and auriculaire:
        return "MAIN_OUVERTE"

    # Poing ferme
    if not pouce and not index and not majeur and not annulaire and not auriculaire:
        return "POING_FERME"

    # Un seul doigt leve
    if pouce and not index and not majeur and not annulaire and not auriculaire:
        return "POUCE_LEVE"

    if index and not pouce and not majeur and not annulaire and not auriculaire:
        return "INDEX_LEVE"

    if majeur and not pouce and not index and not annulaire and not auriculaire:
        return "MAJEUR_LEVE"

    if annulaire and not pouce and not index and not majeur and not auriculaire:
        return "ANNULAIRE_LEVE"

    if auriculaire and not pouce and not index and not majeur and not annulaire:
        return "AURICULAIRE_LEVE"

    # Deux doigts leves
    if index and majeur and not pouce and not annulaire and not auriculaire:
        return "INDEX_MAJEUR_LEVES"

    if index and auriculaire and not pouce and not majeur and not annulaire:
        return "INDEX_AURICULAIRE_LEVES"

    if pouce and auriculaire and not index and not majeur and not annulaire:
        return "POUCE_AURICULAIRE_LEVES"

    # Autres combinaisons
    doigts = []

    if pouce:
        doigts.append("POUCE")

    if index:
        doigts.append("INDEX")

    if majeur:
        doigts.append("MAJEUR")

    if annulaire:
        doigts.append("ANNULAIRE")

    if auriculaire:
        doigts.append("AURICULAIRE")

    if doigts:
        return "_".join(doigts) + "_LEVES"

    return "GESTE_INCONNU"
