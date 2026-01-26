// Lecture du fichier des transactions immobilières
// Version en Javascript - OPTIMISÉE
// Exécution : node evalJS.js ou bun evalJS.js
// Création d'un exécutable à partir de bun : bun build evalJS.js --compile puis ./evalJS.exe
// Mesure : environ 2,5" constatées
// ***********************************************************************************************

import { open } from "fs/promises"; // Pour lecture d'un fichier texte ligne à ligne

(async function () {
  var startTime = performance.now();
  var nbRecords = 0;
  var totalVentes = 0;

  // On lit le fichier des valeurs
  const ventes_immo = await open("./data/valeursfoncieres.txt");

  for await (const vente of ventes_immo.readLines()) {
    ++nbRecords;

    // Optimisation : parcourir directement sans split()
    // qui crée un tableau coûteux
    let fieldCount = 0;
    let pos = 0;
    let nextPos = 0;
    
    // Trouver le 10ème séparateur
    while (fieldCount < 10 && pos < vente.length) {
      nextPos = vente.indexOf("|", pos);
      if (nextPos === -1) break;
      pos = nextPos + 1;
      fieldCount++;
    }
    
    // Extraire le champ 10 (prix)
    if (fieldCount === 10 && pos < vente.length) {
      nextPos = vente.indexOf("|", pos);
      if (nextPos === -1) nextPos = vente.length;
      
      // Trouver la virgule
      const commaPos = vente.indexOf(",", pos);
      const endPos = (commaPos !== -1 && commaPos < nextPos) ? commaPos : nextPos;
      
      if (endPos > pos) {
        const prix = Number(vente.substring(pos, endPos));
        if (!isNaN(prix)) {
          totalVentes += prix;
        }
      }
    }
  }

  // ******************************************************************************************************************************************************************************
  var endTime = performance.now();
  console.log(`Nombre d'enregistrements : ${nbRecords}`)
  console.log(`Montant total des ventes : ${Math.round(totalVentes/1000000000)} milliards d'euros`)
  console.log(`Evaluation en Javascript  : ${Math.round(endTime - startTime)} millisecondes`);
})();