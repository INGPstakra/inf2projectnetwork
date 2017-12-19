#ifndef NODES_HPP
#define NODES_HPP

#include "Receiver.hpp"
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::ostream;
using std::istream;

class Element
    {
    private:

        const int ID;

        void setID(vector<int>& numbers_of_Elements);

    public:
        int getID(){return ID;}
    };

class Product : public Element
    {
    private:
        int time_of_getting_warehouse=0;
        static vector<int> numbers_of_Products;
        
        void addTimeOfGettingWarehouse(){time_of_getting_warehouse++;};
        
    public:
        Product(){this->setID(numbers_of_Products);}
        ~Product();
        int getTimeOfGettingWarehouse(){return time_of_getting_warehouse;}
    };

class Node : public Element
    {
    private:
        vector<Product*> list_of_products;
    public:
        ~Node();
        int numberOfProducts(){return list_of_products.size();}
        void addProduct(const Product*);
        void removeProduct(const Products*);
    };

class Deliverer : public Node
    {
    private:
        vector<ReceiverAndProbability*> list_of_receivers;

    public:
        ~Deliverer();
        virtual void addReceiver(Receiver* receiver,double probability);
        virtual void addReceiver(Receiver* receiver);
        bool removeReceiver(Receiver* receiver);
        bool setProbability(double* probability_tab);
        virtual bool giveProduct(int time);
    };

class Ramp : public Deliverer
    {
    private:
        const int TIME_OF_DELIVERY;
        static vector<int> number_of_Ramps;
        
    public:
        Ramp(int _TIME_OF_DELIVERY);
        ~Ramp();
        int getTimeOfDelivery(){return TIME_OF_DELIVERY;}
    };

class Worker : public Deliverer, public Receiver
    {
    private:
        const int PROCESSING_TIME;
        static vector<int> number_of_Workers;
        QueueStack* type_of_taking_products;
        Product* product_in_processing=nullptr;
		int time_of_processing=0;
        
		void addtime(){time_of_processing++;}
        
    public:
        Worker(int _PROCESSING_TIME, QueueStack* type);
        ~Worker();
    };

class Warehouse : public Node, public Receiver
    {
    private:
        static vector<int> numbers_of_Warehouse;
    public:
        Warehouse(){this->setID(numbers_of_Warehouse);}
        ~Warehouse();
    };

#endif // NODES_HPP
