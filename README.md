# Transactions Immobilières - WIP

> **Simulation de performance entre langages de programmation**<br>
> Langages concernés : Javascript, C++, Cobol, Zig<br>
> Environnement d'exécution : Windows 11<br>
> Derniers travaux : 26 janvier 2026<br>


## Les fonctionnalités

La simulation consiste à compter le nombre d'enregistrements d'un fichier conséquent (plus de 3,7 millions de lignes) et de sommer les valeurs d'un champ particulier (le montant en € d'une vente immobilière). La console affiche les valeurs calculées ainsi que la durée du traitement (excepté en GNU Cobol).


## Description du contenu des répertoires principaux de l'application

- root : evalJS.js/evalJS.exe | evalCPP.cpp/evalCPP.exe | evalCOBOL.cbl/evalCOBOL.exe | evalZig.zig/EvalZig.exe
- data : contient le fichier des transactions immobilières françaises de l'année 2023 issu de 
         https://www.data.gouv.fr/fr/datasets/demandes-de-valeurs-foncieres/<br>
-   // Champs ci-dessous pour chaque ligne de ce fichier --------------------------------------
    // Code service CH
    // Reference document
    // 1 Articles CGI
    // 2 Articles CGI
    // 3 Articles CGI
    // 4 Articles CGI
    // 5 Articles CGI
    // No disposition
    // Date mutation
    // Nature mutation
    // Valeur fonciere
    // No voie
    // B
    // T
    // Q
    // Type de voie
    // Code voie
    // Voie
    // Code postal
    // Commune
    // Code departement
    // Code commune
    // Prefixe de section
    // Section
    // No plan
    // No Volume
    // 1er lot
    // Surface Carrez du 1er lot
    // 2eme lot
    // Surface Carrez du 2eme lot
    // 3eme lot
    // Surface Carrez du 3eme lot
    // 4eme lot
    // Surface Carrez du 4eme lot
    // 5eme lot
    // Surface Carrez du 5eme lot
    // Nombre de lots
    // Code type local
    // Type local
    // Identifiant local
    // Surface reelle bati
    // Nombre pieces principales
    // Nature culture
    // Nature culture speciale
    // Surface terrain


## Compilateurs nécessaires à l'application

Chaque fichier source contient un en-tête précisant la ligne de commande de compilation et le site où charger les compilateurs. 

Voici les versions téléchargées au 25 janvier 2026 :

- Javascript : node (v24.11.1) et bun (v1.3.6 - Exécutable JS autonome)
- C++ : llvm (clang v21.1.8)
- Cobol : GNUCobol (v3.3)
- Zig : Zig (v0.15.2)

