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

class Report
    {
    private:
        vector<string*> list_of_reports;
		
		virtual string* addReport(Ramp* ramp,const Network* net) =0;
        virtual string* addReport(Worker* worker,const Network* net)=0;
        virtual string* addReport(Warehouse* warehouse)=0;
        virtual string* addReport(Product* product)=0;
        string* allReports(const Network* net);
        
    public:
    	
        bool removeAll();
        string* getReport(unsigned int iterator);
        string& print(unsigned int iterator);
        bool report(const Network* net,const vector<int>& report_cycles,int time);
    };
	
class ReportFramework : public Report
	{
	public:
		virtual string* addReport(Ramp* ramp,const Network* net) override;
        virtual string* addReport(Worker* worker,const Network* net) override;
        virtual string* addReport(Warehouse* warehouse) override;
        virtual string* addReport(Product* product) override;
	
	};
	
class ReportState : public Report
	{
	public:
		virtual string* addReport(Ramp* ramp,const Network* net) override;
        virtual string* addReport(Worker* worker,const Network* net) override;
        virtual string* addReport(Warehouse* warehouse) override;
        virtual string* addReport(Product* product) override;
	
	};
	
class Simulation
    {
    private:
        int number_of_cycles;
        vector<int> report_at_cycle;
		
		
        bool verify(Network* net);
        bool sendAll(Network* net);
        bool createAll(int time,Network* net);
        void processAll(Network* net);

		
    public:
        Simulation(unsigned int _number_of_cycles,vector<int>& _report_at_cycle);
        Simulation(unsigned int _number_of_cycles,unsigned int period=0);
        bool startSimulation(Network* net,Report& rep);
        bool finishSimulation(Network* net);
    };


	

#endif // NETSIMULATION_HPP

