#include "Network.hpp"

bool Network::addRamp(Ramp* ramp)
    {
    if(ramp)
        {
        list_of_Ramps.push_back(ramp);

        return true;
        }


    return false;
    }

bool Network::addWorker(Worker* worker)
    {
    if(worker)
        {
        list_of_Workers.push_back(worker);

        return true;
        }


    return false;
    }

bool Network::addWarehouse(Warehouse* warehouse)
    {
    if(warehouse)
        {
        list_of_Warehouse.push_back(warehouse);

        return true;
        }


    return false;
    }


bool Network::removeRamp(Ramp* ramp)
    {
    if(!ramp)
        return false;

    for(int i=0;i<list_of_Ramps.size();i++)
        {
        if(list_of_Ramps[i]==ramp)
            {
            list_of_Ramps.erase(list_of_Ramps.begin()+i);

            return true;
            }
        }

    return false;
    }

bool Network::removeWorker(Worker* worker)
    {
    if(!worker)
        return false;

    for(int i=0;i<list_of_Workers.size();i++)
        {
        if(list_of_Workers[i]==worker)
            {
            list_of_Workers.erase(list_of_Workers.begin()+i);

            return true;
            }
        }

    return false;
    }

bool Network::removeWarehouse(Warehouse* warehouse)
    {
    if(!warehouse)
        return false;

    for(int i=0;i<list_of_Warehouses.size();i++)
        {
        if(list_of_Warehouses[i]==warehouse)
            {
            list_of_Warehouses.erase(list_of_Warehouses.begin()+i);

            return true;
            }
        }

    return false;
    }

Ramp* Network::removeRamp()
    {
    if(!list_of_Ramps.empty())
        return nullptr;

    Ramp* ramp=list_of_Ramps[list_of_Ramps.size()-1];

    list_of_Ramps.pop_back();

    return ramp;
    }

Worker* Network::removeWorker()
    {
    if(!list_of_Workers.empty())
        return nullptr;

    Worker* worker=list_of_Workers[list_of_Workers.size()-1];

    list_of_Workers.pop_back();

    return worker;
    }

Warehouse* Network::removeWarehouse()
    {
    if(!list_of_Warehouses.empty())
        return nullptr;

    Warehouse* warehouse=list_of_Warehouses[list_of_Warehouses.size()-1];

    list_of_Warehouses.pop_back();

    return warehouse;
    }







