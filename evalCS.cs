// Lecture du fichier des transactions immobilières
// Version en C#
// Création d'un exécutable : dotnet publish EvalCS.cs -c Release -r win-x64 --self-contained true /p:PublishSingleFile=true /p:PublishTrimmed=true -o .
// Exécution : evalCS.exe
// *****************************************************************************************************************************************************

using System;
using System.Diagnostics;
using System.IO;

class EvalCS
{
    static void Main()
    {
        var stopwatch = Stopwatch.StartNew();

        string filePath = @"./data/valeursfoncieres.txt";

        long totalVentes = 0;
        long montantTransactionEnCours = 0;
        long nbTransactions = 0;
        long nbRecords = 0;

        foreach (var line in File.ReadLines(filePath))
        {
            nbRecords++;

            ReadOnlySpan<char> span = line.AsSpan();

            int fieldIndex = 0;
            int pos = 0;

            // Parcourir jusqu'au 10ème séparateur '|'
            for (int i = 0; i < span.Length && fieldIndex < 10; i++)
            {
                if (span[i] == '|')
                {
                    fieldIndex++;
                    pos = i + 1;
                }
            }

            if (fieldIndex != 10 || pos >= span.Length)
                continue;

            // Extraire le champ 10 (Valeur fonciere)
            int endPos = span[pos..].IndexOf('|');
            if (endPos == -1) endPos = span.Length - pos;
            ReadOnlySpan<char> champ10 = span.Slice(pos, endPos);

            // Partie entière avant la virgule
            int commaIndex = champ10.IndexOf(',');
            if (commaIndex != -1) champ10 = champ10.Slice(0, commaIndex);

            if (!champ10.IsEmpty && long.TryParse(champ10, out long prix))
            {
                if (prix != montantTransactionEnCours)
                {
                    totalVentes += montantTransactionEnCours;
                    montantTransactionEnCours = prix;
                    nbTransactions++;
                }
            }
        }

        // Ajouter dernière transaction
        totalVentes += montantTransactionEnCours;

        stopwatch.Stop();

        Console.WriteLine($"Nb d'enregistrements du fichier : {nbRecords}");
        Console.WriteLine($"Nb de transactions immobilières : {nbTransactions}");
        Console.WriteLine($"Montant total des ventes        : {totalVentes / 1_000_000_000} milliards d'euros");
        Console.WriteLine($"Temps d'exécution en C#         : {stopwatch.ElapsedMilliseconds} ms");
    }
}
