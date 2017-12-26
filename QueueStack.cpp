#include "QueueStack.hpp"

/********LIFO*********/

bool LIFO::push(Product* product,vector<Product*> & list_of_products)
    {
    if(product)
        {
        list_of_products.push_back(product);

        return true;
        }
    return false;
    }

Product* LIFO::pop(vector<Product*> & list_of_products)
    {
    if(!(list_of_products.empty()))
        {
        Product* product=list_of_products[list_of_products.size()-1];
        list_of_products.erase(list_of_products.end()-1);

        return product;
        }

    return nullptr;
    }

string LIFO::type()
    {
    return string("LIFO");
    }

/**********FIFO************/

bool FIFO::push(Product* product,vector<Product*> & list_of_products)
    {
    if(product)
        {
        list_of_products.push_back(product);

        return true;
        }
    return false;
    }

Product* FIFO::pop(vector<Product*> & list_of_products)
    {
    if(!(list_of_products.empty()))
        {
        Product* product=list_of_products[0];
        list_of_products.erase(list_of_products.begin());

        return product;
        }

    return nullptr;
    }

string FIFO::type()
    {
    return string("FIFO");
    }


/*********Koniec QueueStack.cpp**************/
