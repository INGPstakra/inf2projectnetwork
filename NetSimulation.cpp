#include "NetSimulation.hpp"


Simulation::Simulation(unsigned int _number_of_cycles,vector<int>& _report_at_cycle)
{
	number_of_cycles=_number_of_cycles;
	
	if(number_of_cycles!=0 && report_at_cycles.size()!=0) 
	{
		std::sort(_report_at_cycles.begin(),_report_at_cycles.end()); //sortowanie wektora znaczników raportu
		
		if(_report_at_cycles[_report_at_cycles.size()-1]<=_number_of_cycles) //sprawdzanie maksimum wektora
		{
			_report_at_cycles.erase(std::unique(_report_at_cycles.begin(),_report_at_cycles.end()),_report_at_cycles.end());  //usuwanie duplikatów
			report_at_cycles=_report_at_cycles;
		}
	}
}

Simulation::Simulation(unsigned int _number_of_cycles,unsigned int period=0)
{
	number_of_cycles=_number_of_cycles;
	
	if(number_of_cycles!=0 && period>0 && period<number_of_cycles)  //tworzenie wektora znaczników raportu dla podanego okresu
	{
		for(int i=0;i<number_of_cycles/period;i++)
		{
			report_at_cycle.pushback(i*period);
		}
	}
}

bool Simulation::verify(Network* net)
{
	int rampsize=net->list_of_Ramps.size();
	int workersize=net->list_of_Workers.size();
}