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
        bool sendAll(Network* net);
        bool createAll(int time,Network* net);
        void processAll(Network* net);


		bool isWarehouse(ReceiverAndProbability* testingobject,Network* net);
		
    public:
        Simulation(unsigned int _number_of_cycles,vector<int>& _report_at_cycle);
        Simulation(unsigned int _number_of_cycles,unsigned int period=0);
        bool startSimulation(Network* net);
        bool finishSimulation(Network* net);
    };


/*class Report
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
        virtual bool report()=0;
    };
	
	class ReportFramework : public Report
	{
	public:
		virtual bool report(const Network* net,ostream & out) override;
	
	};
	
	class ReportState : public Report
	{
	public:
		virtual bool report(const Network* net,ostream & out) override;
	
	};
	
	*/

#endif // NETSIMULATION_HPP

