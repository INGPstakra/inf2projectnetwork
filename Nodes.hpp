#ifndef NODES_HPP
#define NODES_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <time.h>
#include "QueueStack.hpp"

using std::vector;
using std::string;
using std::ostream;
using std::istream;

class Receiver;
class QueueStack;
class LIFO;
class FIFO;


typedef struct receiverAndProbability
    {
    Receiver* receiver;
    double probability;
    }ReceiverAndProbability;


class Element
    {
    protected:
        int ID;

        void setID(vector<int>& numbers_of_Elements);

    public:
        int getID(){return ID;}
    };


class Product : public Element
    {
    protected:
        int time_of_getting_warehouse=0;
        static vector<int> number_of_Products;

    public:
        void addTimeOfGettingWarehouse(){time_of_getting_warehouse++;};
        Product(){this->setID(number_of_Products);}
        ~Product();
        int getTimeOfGettingWarehouse(){return time_of_getting_warehouse;}
    };

class Node : public Element
    {
    protected:
        vector<Product*> list_of_products;

    public:
        //~Node();
        int numberOfProducts() {return list_of_products.size();}
        virtual bool addProduct(Product* product);        //def. w ramp, worker, warehouse
        virtual Product* removeProduct();    //def. w ramp, worker, warehouse
    };


class Deliverer : public Node
    {
    protected:
        vector<ReceiverAndProbability*> list_of_receivers;

        void multipliProbabilityAdding(double prob,ReceiverAndProbability* rec); //met. pomocnicza mnożenie prawdopodobienstw
        void divideProbabilityRemoving(double prob);                             //met. pom. dzielenie prawdopodbienstw
        Receiver* randomReceiver();     //losowanie jednego z listy odbiorców

    public:
        //~Deliverer();
        bool addReceiver(Receiver* receiver,double probability);
        bool addReceiver(Receiver* receiver);
        bool removeReceiver(Receiver* receiver);
        bool setProbability(double* probability_tab, int length);   //ustawienie prawdop. z tablicy
        virtual bool giveProduct(int time)=0;         //def. w ramp i worker
        int numberOfReceiver() {return list_of_receivers.size();}
    };

class Receiver
    {
    private:
        vector<Deliverer*> list_of_deliverer;

    public:
        bool addDeliverer(Deliverer* deliverer);
        virtual bool takeProduct(Product* product);
        bool removeDelieverer(Deliverer* deliverer);
        int numberOfDeliverer() {return list_of_deliverer.size();}
    };


class Ramp : public Deliverer
    {
    protected:
        int TIME_OF_DELIVERY;                       //czas dostaw
        static vector<int> number_of_Ramps;         //vector z nr id

    public:
        Ramp(int _TIME_OF_DELIVERY);    /*************/
        ~Ramp();
        bool createProduct(int time);
        int getTimeOfDelivery(){return TIME_OF_DELIVERY;}
        virtual bool giveProduct(int time);         //def. w ramp i worker
    };

class Worker : public Deliverer, public Receiver
    {
    protected:
        int PROCESSING_TIME;                        //czas przetwarzania
        static vector<int> number_of_Workers;       //vector z ID
        QueueStack* type_of_taking_products;        //obiekt typu przechowywania
        Product* product_in_processing=nullptr;     //aktualny przetwarzany product
		int time_of_processing=0;                   //czas przetwarzania aktualnego produktu<PROCESSING_TIME

		void addtime(){time_of_processing++;}

    public:
        Worker(int _PROCESSING_TIME, QueueStack* type);
        ~Worker();
        virtual bool addProduct(Product* product);        //def. w ramp, worker, warehouse
        virtual Product* removeProduct();
        virtual bool takeProduct(Product* product);
        virtual bool giveProduct(int time);
    };

class Warehouse : public Node, public Receiver
    {
    protected:
        static vector<int> number_of_Warehouse;    //vector ID

    public:
        Warehouse(){this->setID(number_of_Warehouse);}
        ~Warehouse();
        virtual bool takeProduct(Product* product);
    };

#endif // NODES_HPP
