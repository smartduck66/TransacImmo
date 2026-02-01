      *
      * Lecture du fichier des transactions immobilières
      * La version COBOL ne contient pas de mesure de la performance.
      * GnuCOBOL sous Windows ne fournit PAS d’API native, fiable 
      * et monotone en millisecondes.
      * Le compilateur GnuCOBOL est libre et gratuit.
      * Téléchargement via https://superbol.eu/resources/windows-aio-32/
      * Compilation : cobc -x evalCOBOL.cob
      * Exécution : evalCOBOL.exe
      * 
       IDENTIFICATION DIVISION.
       PROGRAM-ID. EVALCOBOL.

       ENVIRONMENT DIVISION.
       INPUT-OUTPUT SECTION.
       FILE-CONTROL.
           SELECT F-VENTES ASSIGN TO "data/valeursfoncieres.txt"
               ORGANIZATION IS LINE SEQUENTIAL.

       DATA DIVISION.
       FILE SECTION.
       FD  F-VENTES.
       01  REC-VENTE           PIC X(1000).

       WORKING-STORAGE SECTION.

       77  WS-NB-RECORDS       PIC 9(9) VALUE 0.
       77  WS-NB-TRANSACTIONS  PIC 9(9) VALUE 0.
       77  WS-TOTAL-VENTES     PIC 9(15) VALUE 0.
       77  WS-EOF              PIC X VALUE 'N'.

       01  WS-FIELDS.
           05 WS-FIELD         OCCURS 11 TIMES
                               PIC X(100).

       77  WS-PRIX-INT         PIC 9(15).
       77  WS-TR-CUR-INT       PIC 9(15).

       PROCEDURE DIVISION.

       MAIN-PROGRAM.
           OPEN INPUT F-VENTES

           PERFORM UNTIL WS-EOF = 'Y'
               READ F-VENTES
                   AT END
                       MOVE 'Y' TO WS-EOF
                   NOT AT END
                       ADD 1 TO WS-NB-RECORDS
                       PERFORM TRAITER-LIGNE
               END-READ
           END-PERFORM

           CLOSE F-VENTES

           DISPLAY "Nb d'enregistrements du fichier : "
                   WS-NB-RECORDS
       
           DISPLAY "Nb de transactions immobilieres : "
                   WS-NB-TRANSACTIONS

           DISPLAY "Montant total des ventes        : "
                   FUNCTION INTEGER(WS-TOTAL-VENTES / 1000000000)
                   " milliards d'euros"

           STOP RUN.

       TRAITER-LIGNE.
           UNSTRING REC-VENTE
               DELIMITED BY "|"
               INTO WS-FIELD (1)
                    WS-FIELD (2)
                    WS-FIELD (3)
                    WS-FIELD (4)
                    WS-FIELD (5)
                    WS-FIELD (6)
                    WS-FIELD (7)
                    WS-FIELD (8)
                    WS-FIELD (9)
                    WS-FIELD (10)
                    WS-FIELD (11)
           END-UNSTRING

           IF WS-FIELD (11) NOT = SPACES
               UNSTRING WS-FIELD (11)
                   DELIMITED BY ","
                   INTO WS-FIELD (11)
               END-UNSTRING
               
               COMPUTE WS-PRIX-INT = 
                   FUNCTION NUMVAL(WS-FIELD (11))

               IF WS-PRIX-INT NOT = 0 AND 
                  WS-PRIX-INT NOT = WS-TR-CUR-INT
                   ADD WS-PRIX-INT TO WS-TOTAL-VENTES
                   MOVE WS-PRIX-INT TO WS-TR-CUR-INT
                   ADD 1 TO WS-NB-TRANSACTIONS
               END-IF
        
           END-IF.
