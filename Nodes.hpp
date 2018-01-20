#ifndef NODES_HPP
#define NODES_HPP

#include <iostream>
#include <vector>
#include <string>
#include <memory>
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


typedef struct ReceiverAndProbability
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
        ~Node();
        int IdOfProduct(int iterator){ return list_of_products[iterator]->getID();}
        int numberOfProducts() {return list_of_products.size();}
        virtual bool addProduct(Product* product);        //def. w worker
        virtual Product* removeProduct();    //def. w  worker
        virtual void deleteAllProducts();
        friend class Report;
    };


class Deliverer : public Node
    {
    protected:
        vector<ReceiverAndProbability*> list_of_receivers;

        void multipliProbabilityAdding(double prob,ReceiverAndProbability* rec); //met. pomocnicza mno¿enie prawdopodobienstw
        void divideProbabilityRemoving(double prob);                             //met. pom. dzielenie prawdopodbienstw
        Receiver* randomReceiver();     //losowanie jednego z listy odbiorców

    public:
        //~Deliverer();
        bool addReceiver(Receiver* receiver,double probability);
        bool addReceiver(Receiver* receiver);
        bool removeReceiver(Receiver* receiver);
        bool removeReceiver();
        void removeFromReceiver();  /******************************/
        bool setProbability(double* probability_tab,unsigned int length);   //ustawienie prawdop. z tablicy
        virtual bool giveProduct()=0;         //def. w ramp i worker
        int numberOfReceiver() {return list_of_receivers.size();}
        double getProbability(Receiver* receiver);
        const std::vector<ReceiverAndProbability*> & receiverProbability(){return list_of_receivers;}
        virtual void addTimeInProducts();  /*****/     //wyo³uje metode addTimeOfGettingWarehouse() w przechowywanych produktach
    };

class Receiver
    {
    protected:
        vector<Deliverer*> list_of_deliverer;

    public:
        bool addDeliverer(Deliverer* deliverer);
        bool removeDeliverer(Deliverer* deliverer);
        bool removeDeliverer();
        void removeFromDeliverer();  /******************************/
        virtual bool takeProduct(Product* product)=0;
        virtual int getID2()=0;
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
        virtual bool giveProduct() override;
    };

class Worker : public Deliverer, public Receiver
    {
    protected:
        int PROCESSING_TIME;                        //czas przetwarzania
        static vector<int> number_of_Workers;       //vector z ID
        QueueStack* type_of_taking_products;        //obiekt typu przechowywania
        Product* product_in_processing=nullptr;     //aktualny przetwarzany product
		int time_of_processing;                   //czas przetwarzania aktualnego produktu<=PROCESSING_TIME

    public:
        Worker(QueueStack* type, int _PROCESSING_TIME=1, int id=0);
        ~Worker();
        virtual bool addProduct(Product* product) override;
        virtual Product* removeProduct() override;
        virtual bool takeProduct(Product* product);
        virtual bool giveProduct() override;
        int IDOfProcessingProduct();
        int getPROCESSING_TIME() {return PROCESSING_TIME;}
        int timeOfProcessing() {return time_of_processing;}
        void addTimeOfProcessing() {time_of_processing++;this->addTimeInProducts();}
        string type();
        virtual void addTimeInProducts() override;/******/
        virtual int getID2() override {return ID;}
        virtual void deleteAllProducts() override;

        friend class Report;
    };

class Warehouse : public Node, public Receiver
    {
    protected:
        static vector<int> number_of_Warehouse;    //vector ID

    public:
        Warehouse(int id=0);
        ~Warehouse();
        virtual bool takeProduct(Product* product) override;
        virtual int getID2() override {return ID;}
    };



#endif // NODES_HPP
