#include "NeuralChip.hpp"
#include "ExempleGresite.hpp"
#include <iostream>

using namespace cyberpunk;

NeuralChip genereazaImplantExperimental() {
    NeuralChip temp("Cortex_Vizual", 100);
    temp.modifySynapse(0, 999);
    return temp; 
}

int main() {
    std::cout << "\n======================================================\n";
    std::cout << "   PARTEA 1: ANTI-PATTERNS (Cum sa NU scrii cod)      \n";
    std::cout << "======================================================\n";
    
    {
        std::cout << "\n--- Test 1: MEMORY LEAK (Lipsa Destructor) ---\n";
        ChipFaraDestructor leak("Implant_Ieftin", 50);
    }
    std::cout << "  [!] REZULTAT TEST 1: Iesire din scope. Blocuri active blocate pe Heap: " << ContorHeap::blocuriActive << "\n";


    {
        std::cout << "\n--- Test 2: SHALLOW COPY (Lipsa Copy Constructor) ---\n";
        ChipFaraCopyCtor original("Cip_Original", 10);
        original.modificaData(0, 50);
        
        ChipFaraCopyCtor clona = original; 
        
        std::cout << "  * Se modifica valoarea clonei la 99...\n";
        clona.modificaData(0, 99);
        
        original.afiseaza("Original:");
        clona.afiseaza("Clona   :");
        std::cout << "  [!] REZULTAT TEST 2: Modificarea clonei a stricat si originalul! (Aceeasi adresa)\n";
        
        clona.date_ = nullptr; // Prevenire crash (Double Free)
    }

    std::cout << "\n\n======================================================\n";
    std::cout << "   PARTEA 2: IMPLEMENTARE CORECTA    \n";
    std::cout << "======================================================\n";

    {
        std::cout << "\n--- Pas 1: Alocare Normala ---\n";
        NeuralChip patientZero("Cortex_Motor", 500);
        patientZero.modifySynapse(0, 42);

        std::cout << "\n--- Pas 2: DEEP COPY (Copy Constructor) ---\n";
        NeuralChip clonaBuna = patientZero;
        
        std::cout << "  * Se modifica valoarea clonei la 77...\n";
        clonaBuna.modifySynapse(0, 77); 

        patientZero.printStatus(); // 42
        clonaBuna.printStatus();   // 77

        std::cout << "\n--- Pas 3: MUTARE (Move Constructor) ---\n";
        NeuralChip superImplant = std::move(genereazaImplantExperimental());
        superImplant.printStatus();
        
        std::cout << "\n--- Pas 4: Curatarea automata (Destructor) ---\n";
    }
    
    std::cout << "\n======================================================\n";
    std::cout << "   FINAL: Blocuri active pe Heap = " << ContorHeap::blocuriActive << " (Doar Leak-ul initial)\n";
    std::cout << "======================================================\n\n";

    return 0;
}