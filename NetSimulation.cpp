#include "NetSimulation.hpp"


Simulation::Simulation(unsigned int _number_of_cycles,vector<int>& _report_at_cycles)
{
	number_of_cycles=_number_of_cycles;
	
	if(number_of_cycles!=0 && _report_at_cycles.size()!=0) 
	{
		std::sort(_report_at_cycles.begin(),_report_at_cycles.end()); //sortowanie wektora znaczników raportu
		
		if(_report_at_cycles[_report_at_cycles.size()-1]<=_number_of_cycles) //sprawdzanie maksimum wektora
		{
			_report_at_cycles.erase(std::unique(_report_at_cycles.begin(),_report_at_cycles.end()),_report_at_cycles.end());  //usuwanie duplikatów
			report_at_cycle=_report_at_cycles;
		}
	}
}

Simulation::Simulation(unsigned int _number_of_cycles,unsigned int period)
{
	number_of_cycles=_number_of_cycles;
	
	if(number_of_cycles!=0 && period>0 && period<number_of_cycles)  //tworzenie wektora znaczników raportu dla podanego okresu
	{
		for(int i=0;i<number_of_cycles/period;i++)
		{
			report_at_cycle.push_back(i*period);
		}
	}
}

typedef struct testedlist
    {
    Worker* receiver;
    bool goodconection;
   }testedlist;

bool Simulation::isWarehouse(ReceiverAndProbability* testingobject,Network* net)
{
	for(int i=0;i<net->list_of_Warehouses.size();i++)
	{
		if(net->list_of_Warehouses[i]==testingobject->receiver && testingobject->probability!=0) return true;
		bool gool;
	}
	return false;
}

int badConection(vector<testedlist> list)
{
	int suma=0;
	for(int i=0;i<list.size();i++)
	{
		if(list[i].goodconection==false) suma++;
	}
	return suma;
}

bool Simulation::verify(Network* net)
{
	int workersize=net->list_of_Workers.size();
	for(auto x : net->list_of_Ramps)
	{
		if(x->numberOfReceiver()==0) return false;
		double suma=0;
		const vector<ReceiverAndProbability*>& testinglist=x->receiverProbability();
		for(int j=0;j<testinglist.size();j++)
		{
			if(testinglist[j]->probability>1 || testinglist[j]->probability<0) return false;
			suma+=testinglist[j]->probability;
		}
		if(suma!=1) return false;
	}
	vector<testedlist> list;
	int i=0;
	for(auto x : net->list_of_Workers)
	{
		if(x->numberOfReceiver()==0) return false;
		const vector<ReceiverAndProbability*>& testinglist=x->receiverProbability();
		double suma=0;
		bool isConectedToWarehouse=false;
		for(int j=0;j<testinglist.size();j++)
		{
			if(testinglist[j]->probability>1 || testinglist[j]->probability<0) return false;
			suma+=testinglist[j]->probability;
			bool con=isWarehouse(testinglist[j],net);
			if(con) isConectedToWarehouse=true;
		}
		if(suma!=1) return false;
		testedlist ele;
		ele.receiver=x;
		ele.goodconection=isConectedToWarehouse;
		list.push_back(ele);
		
	}
	for(int x=0;x<badConection(list);x++)
	{
		for(auto x : net->list_of_Workers)
		{
			const vector<ReceiverAndProbability*>& testinglist=x->receiverProbability();
			if(list[i].goodconection==false)
			{
				for(int j=0;j<testinglist.size();j++)
				{
					for(int k=0;k<list.size();k++)
					{
						if(testinglist[j]->receiver==list[j].receiver && list[j].goodconection) list[i].goodconection=true;
					}
				}
			}
		}
	}
	if(badConection(list)!=0) return false;
	return true;
}

bool Simulation::sendAll(Network* net)
{
	for(auto x : net->list_of_Ramps)
	{
		x->giveProduct();
	}
	for(auto x : net->list_of_Workers)
	{
		x->giveProduct();
	}
	return true;
}

bool Simulation::createAll(int time,Network* net)
{
	for(auto x : net->list_of_Ramps)
	{
		x->createProduct(time);
	}
	return true;
}

void Simulation::processAll(Network* net)
{
	for(auto x : net->list_of_Workers)
	{
		x->addTimeOfProcessing();
	}
}


bool Simulation::startSimulation(Network* net)
{
	if(verify(net)){
	for(int time=0;time<number_of_cycles;time++)
	{
		createAll(time,net);
		sendAll(net);
		processAll(net);
		std::cout<<"end\n";
	}
	finishSimulation(net);
	}
	else return false;
}

bool Simulation::finishSimulation(Network* net)
{
	return true;
}
