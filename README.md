# Transactions Immobilières

> **Simulation de performance entre langages de programmation**<br>
> Langages concernés : Javascript, C++, Cobol, Zig, Python, C#<br>
> Environnement d'exécution : Windows 11<br>
> Derniers travaux : 1er février 2026<br>


## Les fonctionnalités

La simulation consiste à compter le nombre d'enregistrements d'un fichier conséquent (plus de 3,7 millions de lignes) et de sommer les valeurs d'un champ particulier (le montant en € d'une vente immobilière). La console affiche les valeurs calculées ainsi que la durée du traitement (excepté en GNU Cobol).


## Description du contenu des répertoires principaux de l'application

- root : code source des diverses implémentations -> evalJS.js | evalCPP.cpp | evalCOBOL.cbl | evalZig.zig
- data : doit contenir le fichier des transactions immobilières françaises
  

### Structure des champs du fichier

| Ordre | Nom du champ |
|------:|--------------|
| 1 | Code service CH |
| 2 | Référence document |
| 3 | Article CGI 1 |
| 4 | Article CGI 2 |
| 5 | Article CGI 3 |
| 6 | Article CGI 4 |
| 7 | Article CGI 5 |
| 8 | N° disposition |
| 9 | Date mutation |
| 10 | Nature mutation |
| 11 | Valeur foncière |
| 12 | N° voie |
| 13 | B |
| 14 | T |
| 15 | Q |
| 16 | Type de voie |
| 17 | Code voie |
| 18 | Voie |
| 19 | Code postal |
| 20 | Commune |
| 21 | Code département |
| 22 | Code commune |
| 23 | Préfixe de section |
| 24 | Section |
| 25 | N° plan |
| 26 | N° volume |
| 27 | 1er lot |
| 28 | Surface Carrez du 1er lot |
| 29 | 2e lot |
| 30 | Surface Carrez du 2e lot |
| 31 | 3e lot |
| 32 | Surface Carrez du 3e lot |
| 33 | 4e lot |
| 34 | Surface Carrez du 4e lot |
| 35 | 5e lot |
| 36 | Surface Carrez du 5e lot |
| 37 | Nombre de lots |
| 38 | Code type local |
| 39 | Type local |
| 40 | Identifiant local |
| 41 | Surface réelle bâtie |
| 42 | Nombre de pièces principales |
| 43 | Nature culture |
| 44 | Nature culture spéciale |
| 45 | Surface terrain |



## Compilateurs nécessaires à l'application

Chaque fichier source contient un en-tête précisant la ligne de commande de compilation et le site où charger les compilateurs. 

Voici les versions téléchargées au 1er février 2026 :

| Rang | Langage     | Runtime / Compilateur | Version |
|-----:|-------------|------------------------|---------|
| 1 | C++         | LLVM / Clang           | v21.1.8 |
| 2 | Zig         | Zig                    | v0.15.2 |
| 3 | C#          | .NET                   | v10 (C# 14) |
| 4 | JavaScript  | Node.js                | v24.11.1 |
| 5 | JavaScript  | Bun (exécutable autonome) | v1.3.6 |
| 6 | Python      | Python                 | v3.14.2 |
| 7 | Cobol       | GnuCOBOL               | v3.3 |




## Fonctionnement de l'application

1/ Vous devez créer un répertoire /data et y stocker le fichier valeursfoncieres.txt récupérable à l'adresse suivante : https://www.data.gouv.fr/fr/datasets/demandes-de-valeurs-foncieres/. L'année importe peu : les tests ont été réalisés avec les transactions immobilières de l'année 2023.

2/ Vous devez compiler chaque source avec le compilateur fourni. Ex : après avoir téléchargé Clang, vous lancez la commande 'clang -O3 evalCPP.cpp -o evalCPP.exe' pour le code source C++ 'classic'.

3/ Vous pouvez alors lancer chaque exécutable (ex : evalCPP.exe)


## Évaluations du temps d'exécution moyen sur un PC Windows 11 — 2,8 GHz, Intel Core i9-10900F (10 cœurs), 64 Go de RAM

| Langage / Implémentation        | Temps moyen | Taille de l'exécutable (ko) |
|---------------------------------|-------------|-----------------------------|
| C++ (version *fast*)            | 750 ms      | 267                         |
| Zig                             | 785 ms      | 258                         |
| C#                              | 800 ms      | 1 246                       |
| JavaScript (Node.js)            | 2 400 ms    | N/A (runtime externe)       |
| JavaScript (Bun)                | 2 600 ms    | 110 486                     |
| C++ (version *classic*)         | 2 500 ms    | 281                         |
| Python                          | 6 000 ms    | N/A (interpréteur requis)   |
| Cobol                           | 17 000 ms   | 66                         |

