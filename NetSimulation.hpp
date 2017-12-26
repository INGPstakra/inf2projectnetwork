#ifndef NETSIMULATION_HPP
#define NETSIMULATION_HPP

#include "QueueStack.hpp"
#include "Nodes.hpp"
#include "Network.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

using std::vector;
using std::string;
using std::ostream;
using std::istream;


class Simulation
    {
    private:
        int number_of_cycles;
        vector<int> report_at_cycle;

        bool verify(Network* net);
        bool sendAll(int time);

    public:
        Simulation(int _number_of_cycles,vector<int>& _report_at_cycle);
        bool startSimulation(Network* net);
        bool finishSimulation(Network* net);
    };


class Report
    {
    private:
        vector<string*> list_of_reports;

    public:
        string* addReport(Ramp* ramp);
        string* addReport(Worker* worker);
        string* addReport(Warehouse* warehouse);
        string* addReport(Product* product);
        string* allReports();
        bool removeAll();
        bool reportFramework(const Network* net,ostream & out);
        bool reportState(const Network* net,ostream & out);
    };

#endif // NETSIMULATION_HPP

