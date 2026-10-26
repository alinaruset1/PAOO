#ifndef NEURAL_CHIP_HPP
#define NEURAL_CHIP_HPP

#include <string>
#include <iostream>

namespace cyberpunk {

class NeuralChip {
private:
    std::string brainRegion;
    size_t activeSynapses;
    int* synapticWeights; 

public:
    NeuralChip(std::string region, size_t synapses);
    ~NeuralChip();
    NeuralChip(const NeuralChip& other);
    NeuralChip(NeuralChip&& other) noexcept;

    void printStatus() const;
    void modifySynapse(size_t index, int weight);
};

} // namespace cyberpunk

#endif