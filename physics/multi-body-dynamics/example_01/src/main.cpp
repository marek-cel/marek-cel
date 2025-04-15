#include <iostream>

#include <Simulation.h>

int main()
{
    std::cout << "Multibody Dynamics Simulation" << std::endl;
    Simulation sim;
    sim.simulate();
    std::cout << "Simulation completed." << std::endl;
    return 0;
}