#ifndef NETSIMULATION_HPP
#define NETSIMULATION_HPP

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
    };

class Simulation
    {
    private:
        int number_of_cycles;
        vector<int> report_at_cycle;

        bool verify(Network* net);

    public:
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

