// Lecture du fichier des transactions immobilières
// Version en C++ - OPTIMISÉE
// Compilation avec LLVM : clang -O3 evalCPP.cpp -o evalCPP.exe
// https://github.com/llvm/llvm-project/releases
// Mesure : environ 2,6" constatées
// ***********************************************************************************************

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cstring>

int main() {
    auto startTime = std::chrono::high_resolution_clock::now();
    
    std::ifstream file("./data/valeursfoncieres.txt");
    file.sync_with_stdio(false);  // Désactiver la synchro avec C stdio
    
    if (!file.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier ./data/valeursfoncieres.txt" << std::endl;
        return 1;
    }
    
    int nbRecords = 0;
    long long totalVentes = 0;
    std::string line;
    line.reserve(1000);  // Pré-allouer pour éviter les réallocations
    
    while (std::getline(file, line)) {
        ++nbRecords;
        
        // Extraction directe du champ 10 sans stringstream
        int fieldIndex = 0;
        size_t pos = 0;
        size_t nextPos = 0;
        
        // Parcourir jusqu'au 10ème séparateur
        while (fieldIndex < 10 && pos < line.length()) {
            nextPos = line.find('|', pos);
            if (nextPos == std::string::npos) {
                break;
            }
            pos = nextPos + 1;
            fieldIndex++;
        }
        
        // Extraire le champ 10 (prix)
        if (fieldIndex == 10 && pos < line.length()) {
            nextPos = line.find('|', pos);
            if (nextPos == std::string::npos) {
                nextPos = line.length();
            }
            
            // Extraire jusqu'à la virgule
            size_t commaPos = line.find(',', pos);
            size_t endPos = (commaPos != std::string::npos && commaPos < nextPos) 
                ? commaPos 
                : nextPos;
            
            if (endPos > pos) {
                try {
                    totalVentes += std::stoll(line.substr(pos, endPos - pos));
                } catch (...) {
                    // Ignorer les valeurs invalides
                }
            }
        }
    }
    
    file.close();
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    
    std::cout << "Nombre d'enregistrements : " << nbRecords << std::endl;
    std::cout << "Montant total des ventes : " << (totalVentes / 1000000000) << " milliards d'euros" << std::endl;
    std::cout << "Evaluation en C++        : " << duration.count() << " millisecondes" << std::endl;
    
    return 0;
}