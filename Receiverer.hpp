#ifndef RECEIVERER_HPP
#define RECEIVERER_HPP

#include "Nodes.hpp"

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
        virtual void push(Product* product,vector<Product*> & list_of_products)=0;
        virtual Product* pop(vector<Product*> & list_of_products)=0;
    };

class LIFO : public QueueStack
    {

    };

class LIFO : public QueueStack
    {

    };

#endif // RECEIVERER_HPP
