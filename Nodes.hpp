#ifndef NODES_HPP
#define NODES_HPP

#include "Receiver.hpp"

class Element
    {
    private:

        const int ID;

        virtual void setID()=0;

    public:
        int getID();
    };

class Product : public Element
    {
    private:
        int time_of_getting_warehouse;
        static vector<int> numbers_of_products;
    public:
        void addTimeOfGettingWarehouse();
        int getTimeOfGettingWarehouse();
    };

class Node : public Element
    {
    private:
        vector<Product*> list_of_products
    public:
        void addProduct(const Product*);
        void removeProduct(const Products*);
    };

class Deliverer : public Node
    {
    private:
        vector<ReceiverAndProbability*> list_of_receivers;

    public:
        virtual void addReceiver(Receiver* receiver,double);
        virtual void addReceiver(Receiver* receiver);
        void removeReceiver(Receiver* receiver);
        void setProbability(double* probability_tab);
        virtual bool giveProduct();
    };

class Ramp : public Deliverer
    {
    private:
        const int TIME_OF_DELIVERY;
        static vector<int> number_of_Ramps;

    public:
        Ramp(int _TIME_OF_DELIVERY);
    };

class Worker : public Deliverer, public Receiver
    {
    private:
        const int PROCESSING_TIME;
        static vector<int> number_of_Workers;
        QueueStack* type_of_taking_products;

    public:
        Worker(int _PROCESSING_TIME, QueueStack* type);
    };

class Warehouse : public Deliverer, public Receiver
    {
    private:
        static vector<int> numbers_of_Warehouse;
    };

#endif // NODES_HPP
