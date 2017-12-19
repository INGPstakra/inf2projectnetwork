#ifndef RECEIVERER_HPP
#define RECEIVERER_HPP

#include "Nodes.hpp"
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::ostream;
using std::istream;

class Receiverer
    {
    private:
        vector<Deliverer*> list_of_deliverer;
        
    public:
        void addDeliverer(Deliverer* deliverer);
        virtual void takeProduct(Product* product);
    };

typedef struct receivererAndPrbability
    {
    Receiverer* receiverer;
    double probability;
    }ReceivererAndPrbability;

class QueueStack
    {
    public:
        virtual bool push(Product* product,vector<Product*> & list_of_products)=0;
        virtual Product* pop(vector<Product*> & list_of_products)=0;
        virtual string type()=0;
    };

class LIFO : public QueueStack
    {
		bool push(Product* product,vector<Product*> & list_of_products);
		Product* pop(vector<Product*> & list_of_products);
		string type(){return string("LIFO");}
    };

class FIFO : public QueueStack
    {
		bool push(Product* product,vector<Product*> & list_of_products);
		Product* pop(vector<Product*> & list_of_products);
		string type(){return string("FIFO");}
    };

#endif // RECEIVERER_HPP
