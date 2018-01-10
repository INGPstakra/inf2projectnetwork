#include "Nodes.hpp"
#include "QueueStack.hpp"
#include "Network.hpp"
#include <iostream>
#include <fstream>



int main()
    {
    std::srand(time(NULL));

//    /*****************************************************************************************/
//    //test product
//    using namespace std;
//
//	cout<<"test product\n";
//    Product* a= new Product;
//	Product* b= new Product;
//	Product* c= new Product;
//
//    cout<<"\na->getID();  "<<
//    a->getID();
//    cout<<"\nb->getID();  "<<
//    b->getID();
//    cout<<"\nc->getID();  "<<
//    c->getID();
//
//    cout<<"\ndelete b;  ";
//    delete b;
//
//    cout<<"\na->getID();  "<<
//    a->getID();
//    cout<<"\nc->getID();  "<<
//    c->getID();
//
//	cout<<"\nProduct* d = new Product;  ";
//	Product* d = new Product;
//
//    cout<<"\na->getID();  "<<
//    a->getID();
//    cout<<"\nc->getID();  "<<
//    c->getID();
//    cout<<"\nd->getID();  "<<
//    d->getID();
//
//	delete a, delete c, delete d;
//    //koniec test product
//
//    /*****************************************************************************************/
//	//test node
//	cout<<"\n\ntest node\n";
//    Product p[2];
//	Node n;
//
//
//	cout<<"\nn.addProduct(p);  "<<
//	n.addProduct(p);
//	cout<<"\nn.addProduct(p+1);  "<<
//	n.addProduct(p+1);
//	cout<<"\nn.numberOfProducts();  "<<
//	n.numberOfProducts();
//
//	cout<<"\na=n.removeProduct();  ";
//	a=n.removeProduct();
//	cout<<"\nb=n.removeProduct();  ";
//	b=n.removeProduct();
//
//	cout<<"\na->getID();  "<<
//	a->getID();
//	cout<<"\nb->getID();  "<<
//	b->getID();
//
//	cout<<"\nn.numberOfProducts();  "<<
//	n.numberOfProducts();
//    //koniec test node
//
//    /*****************************************************************************************/
//
//	//test  Ramp, Worker, lifo fifo
//	cout<<"\n\ntest Ramp, worker i fifo, lifo\n";
//	FIFO fifo;
//	LIFO lifo;
//	Ramp r=Ramp(3);
//	Worker w =Worker(&lifo,3), w2=Worker(&fifo,2);
//	vector<Product*> removed_products{};
//
//	cout<<"\nr.createProduct(3);  "<<
//	r.createProduct(3);
//	cout<<"\nr.numberOfProducts();  "<<
//	r.numberOfProducts();
//
//	cout<<"\nr.addReceiver(&w);  "<<
//	r.addReceiver(&w);
//	cout<<"\nr.addReceiver(&w2);  "<<
//	r.addReceiver(&w2);
//
//	cout<<"\nr.receiverProbability()  :   "<<'\n';
//	for(auto x : r.receiverProbability())
//        cout<<"&worker "<<x->receiver<<'\t'<<"Probalility :"<<x->probability<<'\n';
//
//    cout<<"\nr.giveProduct();  "<<
//    r.giveProduct();
//
//	cout<<"\nr.numberOfProducts();  "<<
//	r.numberOfProducts();
//
//
//	cout<<"\nw.numberOfProducts();  "<<
//	w.numberOfProducts();
//	cout<<"\nw.type();  "<<
//	w.type();
//	cout<<"\nw2.numberOfProducts();  "<<
//	w2.numberOfProducts();
//	cout<<"\nw2.type();  "<<
//	w2.type();
//
//	cout<<"worker 1/2 removeProduct()"<<"\n\n";
//	if (c=w.removeProduct())
//		{
//        removed_products.push_back(c);
//        cout<<"worker1 c.getID():  "<<c->getID()<<'\n'<<'\n';
//        }
//	else if(c=w.removeProduct())
//        {
//        removed_products.push_back(c);
//        cout<<"worker2 c.getID():  "<<c->getID()<<'\n'<<'\n';
//        }
//
//	cout<<"\nw.numberOfProducts();  "<<
//	w.numberOfProducts();
//	cout<<"\nw2.numberOfProducts();  "<<
//	w2.numberOfProducts();
//
//
//	cout<<"\nr.numberOfReceiver();  "<<
//	r.numberOfReceiver();
//	cout<<"\nr.removeReceiver(&w);  "<<
//	r.removeReceiver(&w);
//
//	cout<<"\nr.numberOfReceiver();  "<<
//	r.numberOfReceiver();
//	cout<<"\nr.removeReceiver(&w2);  "<<
//	r.removeReceiver(&w2);
//
//	cout<<"\nr.numberOfReceiver();  "<<
//	r.numberOfReceiver();
//
//
//
//    /**************************/
//	/****ustalone prawdopodobienstwo ***/
//
//    cout<<"\n\nPrawdopodobienstwo przekazania ustalone: \n";
//
//	cout<<"\nr.addReceiver(&w,0.2);  "<<
//	r.addReceiver(&w,0.2);
//	cout<<"\nr.addReceiver(&w2,0.4);  "<<
//	r.addReceiver(&w2,0.4);
//	cout<<"\nr.receiverProbability()  :   "<<'\n';
//
//	for(auto x : r.receiverProbability())
//        cout<<"worker"<<x->receiver<<'\t'<<"Probalility :"<<x->probability<<"\n\n";
//
//
//
//    cout<<"Ustawienie prawdopodobienstwa tablica: ";
//    cout<<"\ndouble probability_tab[]{0.3,0.7};  ";
//    double probability_tab[]{0.3,0.7};
//    cout<<"\nr.setProbability(probability_tab,2);  "<<
//    r.setProbability(probability_tab,2);
//
//	cout<<"\nr.receiverProbability()  :   "<<'\n';
//	for(auto x : r.receiverProbability())
//        cout<<"worker"<<x->receiver<<'\t'<<"Probalility :"<<x->probability<<"\n\n";
//
//	cout<<"\nr.removeReceiver();  "<<
//	r.removeReceiver();
//	cout<<"\nr.removeReceiver();  "<<
//	r.removeReceiver();
//
//	/********************************************/
//	//test addTimeProducts()
//	cout<<"\n\nTest addTimeProducts :"<<
//	"for(int i=0;i<5;i++)\n{\nr.createProduct(3);\nr.addTimeInProducts();}\nfor(int i=0;i<5;++i)\n{\nif(c=r.removeProduct())\n{\nremoved_products.push_back(c);\ncout<<c->getTimeOfGettingWarehouse();\n}\n}";
//
//    for(int i=0;i<5;i++)
//        {
//        r.createProduct(3);
//        r.addTimeInProducts();
//        }
//    for(int i=0;i<5;++i)
//        {
//        if(c=r.removeProduct())
//            {
//            removed_products.push_back(c);
//            cout<<c->getTimeOfGettingWarehouse();
//            }
//        }
//
//    /*************************************/
//    //~Ramp()
//    cout<<"\n\n test ~Ramp(), Ramp() :\n";
//    cout<<"\nRamp* r1=new Ramp(2);  ";
//    Ramp* r1=new Ramp(2);
//    cout<<"\nRamp* r2=new Ramp(4);  ";
//    Ramp* r2=new Ramp(4);
//
//    cout<<"\nr1->getID();  "<<
//    r1->getID();
//    cout<<"\nr2->getID();  "<<
//    r2->getID();
//
//    cout<<"\ndelete r1;  ";
//    delete r1;
//    cout<<"\nr2->getID();  "<<
//    r2->getID();
//
//    cout<<"\nr1=new Ramp(6);  ";
//    r1=new Ramp(6);
//    cout<<"\nr1->getID();  "<<
//    r1->getID();
//    cout<<"\nr2->getID();  "<<
//    r2->getID();
//
//    delete r1,delete r2;
//
//    /************************************/
//    //~Worker()
//    cout<<"\n\n test ~Worker(), Worker() :\n";
//    cout<<"\nWorker* w1=new Worker(&lifo,2);  ";
//    Worker* w1=new Worker(&lifo,2);
//    cout<<"\nWorker* w3=new Worker(&fifo,4);  ";
//    Worker* w3=new Worker(&fifo,4);
//
//    cout<<"\nw1->getID();  "<<
//    w1->getID();
//    cout<<"\nw3->getID();  "<<
//    w3->getID();
//
//    cout<<"\ndelete w1;  ";
//    delete w1;
//    cout<<"\nw3->getID();  "<<
//    w3->getID();
//
//    cout<<"\nw1=new Worker(6,&fifo);  ";
//    w1=new Worker(&fifo,6);
//    cout<<"\nw1->getID();  "<<
//    w1->getID();
//    cout<<"\nw3->getID();  "<<
//    w3->getID();
//
//    delete w1,delete w3;
//
//    /*****************************************************************************************/
//    //Test Warehouse i Receiver
//    cout<<"\n\n test Warehouse i Receiver\n";
//
//    Ramp r5(3);
//    Worker w5(&fifo,2);
//    Warehouse war1,war2;
//    Product p1,p2;
//
//    cout<<"Dodawanie nadawcy i odbiorcy: \nr5.addReceiver(&w5);  "<<
//    r5.addReceiver(&w5);
//    cout<<"\nw5.addDeliverer(&r5);  "<<
//    w5.addDeliverer(&r5);
//    cout<<"\nw5.addReceiver(&war1);  "<<
//    w5.addReceiver(&war1);
//    cout<<"\nw5.addReceiver(&war2);  "<<
//    w5.addReceiver(&war2);
//    cout<<"\nwar1.addDeliverer(&w5);  "<<
//    war1.addDeliverer(&w5);
//    cout<<"\nwar2.addDeliverer(&w5);  "<<
//    war2.addDeliverer(&w5);
//
//    /**********************/
//    cout<<"\n\nLiczby odbiorcow i nadawcow:\nr5.numberOfReceiver();  "<<
//    r5.numberOfReceiver();
//    cout<<"\nw5.numberOfReceiver();  "<<
//    w5.numberOfReceiver();
//    cout<<"\nw5.numberOfDeliverer();  "<<
//    w5.numberOfDeliverer();
//    cout<<"\nwar1.numberOfDeliverer();  "<<
//    war1.numberOfDeliverer();
//    cout<<"\nwar2.numberOfDeliverer();  "<<
//    war2.numberOfDeliverer();
//    /**dodawanie i usuwanie nadawcow z warehouse**/
//    cout<<"\n\nUsuwanie i dodawnie nadawcy:";
//    cout<<"\nwar1.removeDeliverer(&w5);  "<<
//    war1.removeDeliverer(&w5);
//    cout<<"\nwar1.numberOfDeliverer();  "<<
//    war1.numberOfDeliverer();
//    cout<<"\nwar2.removeDeliverer();  "<<
//    war2.removeDeliverer();
//    cout<<"\nwar2.numberOfDeliverer();  "<<
//    war2.numberOfDeliverer();
//    cout<<"\nwar1.addDeliverer(&w5);  "<<
//    war1.addDeliverer(&w5);
//    cout<<"\nwar1.numberOfDeliverer();  "<<
//    war1.numberOfDeliverer();
//    cout<<"\nwar2.addDeliverer(&w5);  "<<
//    war2.addDeliverer(&w5);
//    cout<<"\nwar2.numberOfDeliverer();  "<<
//    war2.numberOfDeliverer();
//
//    /**************************************/
//    /**przekazywanie produktu z worker->Warehouse**/
//    cout<<"\n\nPrzekazywanie productu worker->Warehouse:";
//    cout<<"\np1.getID();  "<<
//    p1.getID();
//    cout<<"\nw5.takeProduct(&p1);  "<<
//    w5.takeProduct(&p1);
//    cout<<"\nw5.timeOfProcessing() :  "<<w5.timeOfProcessing();
//
//    cout<<"\nw5.giveProduct();  "<<
//    w5.giveProduct();
//    cout<<"\nw5.timeOfProcessing() :  "<<w5.timeOfProcessing();
//    cout<<"\nw5.giveProduct();  "<<
//    w5.giveProduct();
//    cout<<"\nw5.timeOfProcessing() :  "<<w5.timeOfProcessing();
//
//    cout<<"\np2.getID();  "<<
//    p2.getID();
//    cout<<"\nw5.takeProduct(&p2);  "<<
//    w5.takeProduct(&p2);
//
//
//    cout<<"\nw5.giveProduct();  "<<
//    w5.giveProduct();
//    cout<<"\nw5.timeOfProcessing() :  "<<w5.timeOfProcessing();
//    cout<<"\nw5.giveProduct();  "<<
//    w5.giveProduct();
//    cout<<"\nw5.timeOfProcessing() :  "<<w5.timeOfProcessing();
//    cout<<"\nw5.giveProduct();  "<<
//    w5.giveProduct();
//    cout<<"\nw5.timeOfProcessing() :  "<<w5.timeOfProcessing();
//    cout<<"\nw5.giveProduct();  "<<
//    w5.giveProduct();
//    cout<<"\nw5.timeOfProcessing() :  "<<w5.timeOfProcessing();
//    cout<<"\nw5.giveProduct();  "<<
//    w5.giveProduct();
//    cout<<"\nw5.timeOfProcessing() :  "<<w5.timeOfProcessing();
//
//    cout<<"\nwar1.numberOfProducts();  "<<
//    war1.numberOfProducts();
//    cout<<"\nwar2.numberOfProducts();  "<<
//    war2.numberOfProducts();
//
//    if(c=war1.removeProduct())
//        {
//        cout<<"\nc=war1.removeProduct();  "<<
//        c->getID();
//        }
//    else if(c=war2.removeProduct())
//        {
//        cout<<"\nc=war2.removeProduct();  "<<
//        c->getID();
//        }
//    else
//        {
//        cout<<"\nblad\n";
//        }
//
//    cout<<"\nwar1.numberOfProducts();  "<<
//    war1.numberOfProducts();
//    cout<<"\nwar2.numberOfProducts();  "<<
//    war2.numberOfProducts();
//
//    war1.takeProduct(nullptr);
//
//    /**************************************/
//    //test ~Warehouse()
//    cout<<"\n\n test ~Warehouse() :  ";
//    cout<<"\nWarehouse* war3=new Warehouse();  ";
//    Warehouse* war3=new Warehouse();
//    cout<<"\nWarehouse* war4=new Warehouse();  ";
//    Warehouse* war4=new Warehouse();
//    cout<<"\nwar3->getID();  "<<
//    war3->getID();
//    cout<<"\nwar4->getID();  "<<
//    war4->getID();
//    cout<<"\ndelete war3;  ";
//    delete war3;
//    cout<<"\nwar4->getID();  "<<
//    war4->getID();
//    cout<<"\nwar3=new Warehouse();  ";
//    war3=new Warehouse();
//    cout<<"\nwar4->getID();  "<<
//    war4->getID();
//    cout<<"\nwar3->getID();  "<<
//    war3->getID()<<"\n\n\n";
//
//
//    delete war3,delete war4;

    /**********Network***************/

    Network net;

    std::ifstream plik;
    plik.open( "struct-input.txt", std::ios::in | std::ios::out );

    net.loadElementsFromFile(plik);
    plik.close();
    net.print();
    net.removeAllNodes();








//
//
//	for(auto x : removed_products)
//        delete x;

	string z;
//	getline(cin,z);
//	string::size_type* ptr;
//    double num=std::stoi(z,ptr);
//    cout<<to_string(num);
    std::cin>>z;



    return 0;
    }
