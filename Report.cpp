#include #include "NetSimulation.hpp"

*string* addReport(Worker* worker){
    std::stringstream ss;
    ss << "Worker #" <<worker->getID()<<"\n"<<"Processing time:"<<worker->getPROCESSING_TIME()<<"\n"<<
    "Queue type:" <<worker->type<<"\n" << "Receivers: ";
    auto vctr=worker->receiverProbability();
    for(int i=0; i<vctr.size(); i++){
        ss<<vctr[i].receiver<<"\n":
    }
    string s = ss.str();
    string* rep=&s;
    return rep;
}

string* addReport(Ramp* ramp){
    std::stringstream ss;
    ss << "LOADING RAMP #" <<ramp->getID()<<"\n"<<"Delivery interval:"<<ramp->getTimeOfDelivery()<<"\n"<<"Receivers: ";
    auto vctr=ramp->receiverProbability();
    for(int i=0; i<vctr.size(); i++){
        ss<<vctr[i].receiver<<"\n":
    }
    string s = ss.str();
    string* rep=&s;
    return rep;
}
string* addReport(Warehouse* warehouse){
    std::stringstream ss;
    ss << "STOREHOUSE #" <<warehouse->getID();
    string s = ss.str();
    string* rep=&s;
    return rep;
}

string* addReport(Product* product){
    std::stringstream ss;
    ss << "PRODUCT #" <<product->getID();<<"\n"<<
    "Time to getting to warehouse: " <<product->getTimeOfGettingWarehouse();
    string s = ss.str();
    string* rep=&s;
    return rep;
}
