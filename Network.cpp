#include "Network.hpp"

/************dodawanie wezla**********/

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

/************usuwanie danego wezla**********/
bool Network::removeRamp(Ramp* ramp)
    {
    if(!ramp)
        return false;

    for(int i=0;i<list_of_Ramps.size();i++)
        {
        if(list_of_Ramps[i]==ramp)
            {
            list_of_Ramps.erase(list_of_Ramps.begin()+i);

            ramp.removeFromReceiver();

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

            worker.removeFromDeliverer();
            worker.removeFromReceiver();

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

            warehouse.removeFromDeliverer();

            return true;
            }
        }

    return false;
    }

/************usuwanie ustatniego elementu z listy**********/
Ramp* Network::removeRamp()
    {
    if(!list_of_Ramps.empty())
        return nullptr;

    Ramp* ramp=list_of_Ramps[list_of_Ramps.size()-1];

    list_of_Ramps.pop_back();

    ramp.removeFromReceiver();

    return ramp;
    }

Worker* Network::removeWorker()
    {
    if(!list_of_Workers.empty())
        return nullptr;

    Worker* worker=list_of_Workers[list_of_Workers.size()-1];

    worker.removeFromDeliverer();
    worker.removeFromReceiver();

    list_of_Workers.pop_back();

    return worker;
    }

Warehouse* Network::removeWarehouse()
    {
    if(!list_of_Warehouses.empty())
        return nullptr;

    Warehouse* warehouse=list_of_Warehouses[list_of_Warehouses.size()-1];

    warehouse.removeFromDeliverer();

    list_of_Warehouses.pop_back();

    return warehouse;
    }

/************znajdowanie wezla*****************/
Ramp* Network::findRamp(int id)
    {
    if(id<=0)
        return nullptr;

    for(auto x : list_of_Ramps)
        if(x->getID()==id)
            return x;

    return nullptr;
    }

Worker* Network::findWorker(int id)
    {
    if(id<=0)
        return nullptr;

    for(auto x : list_of_Workers)
        if(x->getID()==id)
            return x;

    return nullptr;
    }

Warehouse* Network::findWarehouse(int id)
    {
    if(id<=0)
        return nullptr;

    for(auto x : list_of_Warehouses)
        if(x->getID()==id)
            return x;

    return nullptr;
    }

bool Network::addLink(Deliverer* deliverer, Receiver* receiver, double probability)
    {
    if(!deliverer || !receiver)
        return false;

    Receiver* r=nullptr;
    Deliverer* d=nullptr;

    for(auto x : list_of_Ramps)     //szukamy dostawcy
        if(x==deliverer)
           d=x;

    for(auto x : list_of_Workers)   //szukamy dustawcy i odbiorcy
        {
        if(x==receiver)
            r=x;
        else if(x==deliverer)
            d=x;
        }

    if(r==receiver && d=deliverer)  //jesli znalezieni
        {
        r->addDeliverer(d);
        if(probability!=-1)
            return d->addReceiver(r,probability);

        return d->addReceiver(r);
        }

    for(auto x : list_of_Warehouses)    //szukamy odbiorcy
        if(x==receiver)
            r=x;

    if(r==receiver && d=deliverer)      //jesli znalezieni
        {
        r->addDeliverer(d);
        if(probability!=-1)
            return d->addReceiver(r,probability);

        return d->addReceiver(r);
        }
    else                                //jesli nie znalezieni
        return false;

    }

bool Network::removeLink(Deliverer* deliverer, Receiver* receiver)
    {
    if(!deliverer && !receiver)
        return false;

    if(deliverer)
        deliverer->removeReceiver(receiver);

    if(receiver)
        receiver->removeDeliverer(deliverer);

    return true;
    }

bool loadElementsFromFile(istream& in)
    {
    const char r='r',w='w',s='s',link='l',errror='\0';
    char state=r;
    string line="";

    while(std::getline(in,line))
        {
        if(line=="; == LOADING RAMPS ==")       //sprawdzamy aktualn¹ kategorie danych
            {
            state=r;

            if(std::getline(in,line))
                {
                if(line=="")
                    continue;
                else
                    state=errror;
                }
            }
        else if(line=="; == WORKERS ==")
            {
            state=w;

            if(std::getline(in,line))
                {
                if(line=="")
                    continue;
                else
                    state=errror;
                }
            }
        else if(line=="; == STOREHOUSES ==")
            {
            state=s;

            if(std::getline(in,line))
                {
                if(line=="")
                    continue;
                else
                    state=errror;
                }
            }
        else if(line=="; == LINKS ==")
            {
            state=link;

            if(std::getline(in,line))
                {
                if(line=="")
                    continue;
                else
                    state=errror;
                }
            }

        if(state==errror)
            {
            removeAll();

            break;
            }
        else if()

        }
    }















