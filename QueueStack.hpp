#ifndef QUEUESTACK_HPP
#define QUEUESTACK_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include "Nodes.hpp"

using std::vector;
using std::string;
using std::ostream;
using std::istream;

class Product;

class QueueStack
    {
    public:
        virtual bool push(Product* product,vector<Product*> & list_of_products)=0;
        virtual Product* pop(vector<Product*> & list_of_products)=0;
        virtual string type()=0;
    };

class LIFO : public QueueStack
    {
    public:
        virtual bool push(Product* product,vector<Product*> & list_of_products);
        virtual Product* pop(vector<Product*> & list_of_products);
        virtual string type();
    };

class FIFO : public QueueStack
    {
    public:
        virtual bool push(Product* product,vector<Product*> & list_of_products);
        virtual Product* pop(vector<Product*> & list_of_products);
        virtual string type();
    };

#endif // QUEUESTACK_HPP
