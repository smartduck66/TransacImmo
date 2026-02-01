// Lecture du fichier des transactions immobilières
// Version en C++ 'fast' avec chargement mémoire du fichier .txt
// Compilation avec LLVM : clang++ evalCPP_fast.cpp -O3 -march=native -mtune=native -flto -fuse-ld=lld -DNDEBUG -o evalCPP_fast.exe
// Exécution : evalCPP_fast.exe
// https://github.com/llvm/llvm-project/releases
// ********************************************************************************************************************************

#include <windows.h>
#include <iostream>
#include <cstdint>
#include <chrono>

int main() {
    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();

    const char* filename = "./data/valeursfoncieres.txt";

    // Ouvrir le fichier
    HANDLE hFile = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier\n";
        return 1;
    }

    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(hFile, &fileSize)) {
        std::cerr << "Erreur : impossible de connaître la taille du fichier\n";
        CloseHandle(hFile);
        return 1;
    }

    // Créer le mapping
    HANDLE hMap = CreateFileMappingA(hFile, nullptr, PAGE_READONLY, 0, 0, nullptr);
    if (!hMap) {
        std::cerr << "Erreur : CreateFileMapping échoué\n";
        CloseHandle(hFile);
        return 1;
    }

    // Mapper tout le fichier en mémoire
    const char* data = (const char*)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
    if (!data) {
        std::cerr << "Erreur : MapViewOfFile échoué\n";
        CloseHandle(hMap);
        CloseHandle(hFile);
        return 1;
    }

    uint64_t totalVentes = 0;
    uint64_t MontantTransactionEnCours = 0;
    uint64_t NbTransactions = 0;
    uint64_t nbRecords = 0;

    size_t fieldIndex = 0;
    uint64_t prix = 0;
    bool readingPrix = false;

    const char* ptr = data;
    const char* end = data + fileSize.QuadPart;

    while (ptr < end) {
        char c = *ptr++;

        if (c == '|') {
            fieldIndex++;
            continue;
        }

        if (c == '\n' || c == '\r') {
            if (readingPrix && prix != MontantTransactionEnCours) {
                totalVentes += MontantTransactionEnCours;
                MontantTransactionEnCours = prix;
                NbTransactions++;
            }
            fieldIndex = 0;
            prix = 0;
            readingPrix = false;
            nbRecords++;
            continue;
        }

        // Champ 10 = Valeur fonciere
        if (fieldIndex == 10) {
            if (c >= '0' && c <= '9') {
                readingPrix = true;
                prix = prix * 10 + (c - '0');
            } else if (c == ',' && readingPrix) {
            // fin de la partie entière
            fieldIndex++; // on passe à un autre champ pour ne plus toucher prix
        }
}

    }

    // dernière transaction si pas de newline à la fin
    if (readingPrix && prix != MontantTransactionEnCours) {
        totalVentes += MontantTransactionEnCours;
        NbTransactions++;
    }

    // Nettoyage
    UnmapViewOfFile(data);
    CloseHandle(hMap);
    CloseHandle(hFile);

    auto endTime = clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - start);

    std::cout << "Nb d'enregistrements du fichier : " << nbRecords << '\n';
    std::cout << "Nb de transactions immobilieres : " << NbTransactions << '\n';
    std::cout << "Montant total des ventes        : " << (totalVentes / 1000000000) << " milliards d'euros\n";
    std::cout << "Temps d'execution en C++        : " << duration.count() << " ms\n";

    return 0;
}
