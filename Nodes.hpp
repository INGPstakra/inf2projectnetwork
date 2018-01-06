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
        virtual bool addProduct(Product* product);        //def. w worker
        virtual Product* removeProduct();    //def. w  worker
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
        bool removeReceiver();
        bool setProbability(double* probability_tab, int length);   //ustawienie prawdop. z tablicy
        virtual bool giveProduct()=0;         //def. w ramp i worker
        int numberOfReceiver() {return list_of_receivers.size();}
        const std::vector<ReceiverAndProbability*> & receiverProbability(){return list_of_receivers;}
        virtual void addTimeInProducts();       //ywołuje metode addTimeOfGettingWarehouse() w przechowywanych produktach
    };

class Receiver
    {
    private:
        vector<Deliverer*> list_of_deliverer;

    public:
        bool addDeliverer(Deliverer* deliverer);
        virtual bool takeProduct(Product* product)=0;
        bool removeDelieverer(Deliverer* deliverer);
        bool removeDelieverer();
        int numberOfDeliverer() {return list_of_deliverer.size();}
        const std::vector<Deliverer*> & listOfDeliverer(){return list_of_deliverer;}
    };


class Ramp : public Deliverer
    {
    protected:
        int TIME_OF_DELIVERY;                       //czas dostaw
        static vector<int> number_of_Ramps;         //vector z nr id

    public:
        Ramp(int _TIME_OF_DELIVERY=1,int id=0);
        ~Ramp();
        bool createProduct(int time);
        int getTimeOfDelivery(){return TIME_OF_DELIVERY;}
        virtual bool giveProduct();
    };

class Worker : public Deliverer, public Receiver
    {
    protected:
        int PROCESSING_TIME;                        //czas przetwarzania
        static vector<int> number_of_Workers;       //vector z ID
        QueueStack* type_of_taking_products;        //obiekt typu przechowywania
        Product* product_in_processing=nullptr;     //aktualny przetwarzany product
		int time_of_processing=0;                   //czas przetwarzania aktualnego produktu<=PROCESSING_TIME

    public:
        Worker(QueueStack* type, int _PROCESSING_TIME=1, int id=0);
        ~Worker();
        virtual bool addProduct(Product* product);
        virtual Product* removeProduct();
        virtual bool takeProduct(Product* product);
        virtual bool giveProduct();
        int timeOfProcessing() {return time_of_processing;}
        string type();
        virtual void addTimeInProducts();
    };

class Warehouse : public Node, public Receiver
    {
    protected:
        static vector<int> number_of_Warehouse;    //vector ID

    public:
        Warehouse(int id=0);
        ~Warehouse();
        virtual bool takeProduct(Product* product);
    };


#endif // NODES_HPP
