#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "Receiver.hpp"
#include "Nodes.hpp"
#include "NetSimulation.hpp"
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::ostream;
using std::istream;

class Network
    {
    private:
        vector<Ramp*> list_of_Ramps;
        vector<Worker*> list_of_Workers;
        vector<Warehouse*> list_of_Warehouse;
        
    public:
        bool addRamp(Ramp* ramp);
        bool addWorker(Worker* worker);
        bool addWarehouse(Warehouse* warehouse);

        bool removeRamp(Ramp* ramp);
        bool removeWorker(Worker* worker);
        bool removeWarehouse(Warehouse* warehouse);

        bool loadElementsFromFile(istream& in);
        bool saveElementsToFile(ostream& out);
        friend class Simulation;
        friend class Report;
    };

#endif //NETWORK_HPP