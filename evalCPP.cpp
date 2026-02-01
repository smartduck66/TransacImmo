// Lecture du fichier des transactions immobilières
// Version en C++ 'classic'
// Compilation avec LLVM : clang -O3 evalCPP.cpp -o evalCPP.exe
// Exécution : evalCPP.exe
// https://github.com/llvm/llvm-project/releases
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
    int MontantTransactionEnCours = 0;
    int NbTransactions = 0;
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
                    const int prix=std::stoll(line.substr(pos, endPos - pos));
                    // On vérifie si le prix est différent du montant de la transaction en cours : si c'est le cas,
                    // on a changé de transaction et on peut donc ajouter le montant de la transaction précédente au total
                    if (prix != MontantTransactionEnCours) {
                        totalVentes += MontantTransactionEnCours;
                        MontantTransactionEnCours = prix;
                        ++NbTransactions;
          }
                } catch (...) {
                    // Ignorer les valeurs invalides
                }
            }
        }
    }
    
    file.close();
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    
    std::cout << "Nb d'enregistrements du fichier : " << nbRecords << std::endl;
    std::cout << "Nb de transactions immobilieres : " << NbTransactions << std::endl;
    std::cout << "Montant total des ventes        : " << (totalVentes / 1000000000) << " milliards d'euros" << std::endl;
    std::cout << "Temps d'execution en C++        : " << duration.count() << " millisecondes" << std::endl;
    
    return 0;
}