
#include "Nodes.hpp"
#include "Nodes.cpp"
#include "QueueStack.hpp"
#include "QueueStack.cpp"


int main()
    {
    Product* el=new Product[3];

    std::cout<<el[0].getID()<<el[1].getID()<<el[2].getID();

    delete [] el;
    return 0;
    }
