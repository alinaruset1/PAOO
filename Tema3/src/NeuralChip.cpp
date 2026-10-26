#include "NeuralChip.hpp"
#include "ExempleGresite.hpp"

namespace cyberpunk {

NeuralChip::NeuralChip(std::string region, size_t synapses)
    : brainRegion(region), activeSynapses(synapses), synapticWeights(new int[synapses]{0}) {
    ++ContorHeap::blocuriActive;
    std::cout << "  [+] CONSTRUCTOR : " << brainRegion << " (Alocare. Heap activ: " << ContorHeap::blocuriActive << ")\n";
}

NeuralChip::~NeuralChip() {
    --ContorHeap::blocuriActive; // Scadem contorul inainte de afisare ca sa arate bine in log
    std::cout << "  [-] DESTRUCTOR  : " << brainRegion << " (Curatare. Heap activ: " << ContorHeap::blocuriActive << ")\n";
    delete[] synapticWeights; 
}

NeuralChip::NeuralChip(const NeuralChip& other)
    : brainRegion(other.brainRegion + " (Clona)"), 
      activeSynapses(other.activeSynapses), 
      synapticWeights(new int[other.activeSynapses]) {
    ++ContorHeap::blocuriActive;
    std::cout << "  [C] COPY CONST. : Deep Copy pt '" << other.brainRegion << "'. (Heap activ: " << ContorHeap::blocuriActive << ")\n";
    
    for (size_t i = 0; i < activeSynapses; ++i) {
        synapticWeights[i] = other.synapticWeights[i];
    }
}

NeuralChip::NeuralChip(NeuralChip&& other) noexcept
    : brainRegion(std::move(other.brainRegion)), 
      activeSynapses(other.activeSynapses), 
      synapticWeights(other.synapticWeights) {
    
    std::cout << "  [M] MOVE CONST. : Resurse furate si mutate instant, fara extra alocari!\n";
    other.synapticWeights = nullptr;
    other.activeSynapses = 0;
    other.brainRegion = "Gol";
}

void NeuralChip::printStatus() const {
    std::cout << "      -> Status [" << brainRegion << "]: ";
    if (synapticWeights && activeSynapses > 0) {
        std::cout << "Valoare = " << synapticWeights[0] << " | Adresa = " << synapticWeights;
    } else {
        std::cout << "Dezactivat / Fara memorie";
    }
    std::cout << "\n";
}

void NeuralChip::modifySynapse(size_t index, int weight) {
    if (index < activeSynapses && synapticWeights != nullptr) {
        synapticWeights[index] = weight;
    }
}

} // namespace cyberpunk