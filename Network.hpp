#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "QueueStack.hpp"
#include "Nodes.hpp"
#include "NetSimulation.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include<sstream>

using std::vector;
using std::string;
using std::ifstream;
using std::ostream;
using std::istream;
using std::string;

class Network
    {
    private:
        vector<Ramp*> list_of_Ramps;
        vector<Worker*> list_of_Workers;
        vector<Warehouse*> list_of_Warehouses;


    public:


        bool addRamp(Ramp* ramp);
        bool addWorker(Worker* worker);
        bool addWarehouse(Warehouse* warehouse);

        bool removeRamp(Ramp* ramp);
        bool removeWorker(Worker* worker);
        bool removeWarehouse(Warehouse* warehouse);

        Ramp* removeRamp();
        Worker* removeWorker();
        Warehouse* removeWarehouse();

        void removeAllNodes(); //tylko dla dynamicznie zaalokowanych produktow i wezlow
        void clearAllNodes();   //tylko dla dynamicznie zaalokowanych produktow

        bool addLink(Deliverer* deliverer, Receiver* receiver, double probability=-1);
        bool removeLink(Deliverer* deliverer, Receiver* receiver);

        Ramp* findRamp(int id);
        Worker* findWorker(int id);
        Warehouse* findWarehouse(int id);

        void print();

        bool loadElementsFromStream(istream& in);
        bool saveElementsToStream(ostream& out);

       friend class Simulation;
       friend class Report;
       friend bool isWarehouse(ReceiverAndProbability* testingobject,const Network* net);
    };

string veryfi_padding(string line, std::string::size_type & pos_start, std::string::size_type pos_end);//zwraca "" gdy zawiera tylko spacje i tabulacje, inaczej "Zly format"


#endif //NETWORK_HPP
