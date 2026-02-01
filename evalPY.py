# Lecture du fichier des transactions immobilières
# Version en Python
# Exécution : python evalPY.py
# Mesure : environ 6" constatées
# Piste d'optimisation : compiler le code source avec nuitka pour obtenir un exécutable natif plus rapide.
#                        py -m nuitka --onefile --standalone evalpy.py
# ********************************************************************************************************

import time

start_time = time.perf_counter()  # début du chronométrage

total_ventes = 0
montant_transaction_en_cours = 0
nb_transactions = 0
nb_records = 0

# Chemin du fichier
fichier = r"./data/valeursfoncieres.txt"

with open(fichier, "r", encoding="utf-8") as f:
    for line in f:
        nb_records += 1
        fields = line.strip().split("|")
        if len(fields) <= 10:
            continue  # ligne mal formée ou incomplète

        # Champ 10 = Valeur fonciere
        valeur = fields[10].split(",")[0]  # prendre seulement la partie entière
        if not valeur.isdigit():
            continue  # champ vide ou non numérique

        prix = int(valeur)

        if prix != montant_transaction_en_cours:
            total_ventes += montant_transaction_en_cours
            montant_transaction_en_cours = prix
            nb_transactions += 1

# Ajouter la dernière transaction
total_ventes += montant_transaction_en_cours

end_time = time.perf_counter()  # fin du chronométrage
duree_ms = (end_time - start_time) * 1000  # convertir en millisecondes

# Affichage des résultats
print(f"Nb d'enregistrements du fichier : {nb_records}")
print(f"Nb de transactions immobilières : {nb_transactions}")
print(f"Montant total des ventes        : {total_ventes // 1_000_000_000} milliards d'euros")
print(f"Temps d'exécution en Python     : {round(duree_ms)} millisecondes")

