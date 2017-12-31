#include "Nodes.hpp"
#include "QueueStack.hpp"


int main()
    {
	std::cout<<"test product\n";
    Product* a= new Product;
	Product* b= new Product;
	Product* c= new Product;

    std::cout<<(a->getID())<<'\n'<<(b->getID())<<'\n'<<(c->getID())<<'\n'<<'\n';

    delete b;
	
	std::cout<<(a->getID())<<'\n'<<(c->getID())<<'\n'<<'\n';

	Product* d = new Product;
	
    std::cout<<(a->getID())<<'\n'<<(c->getID())<<'\n'<<(d->getID())<<'\n'<<'\n';

	delete a;
	
	std::cout<<"test node\n";
	
	Node* n= new Node;
	n->addProduct(c);
	n->addProduct(d);
	std::cout<<n->numberOfProducts()<<'\n'<<'\n';
	a=n->removeProduct();
	b=n->removeProduct();
	std::cout<<a->getID()<<'\n'<<b->getID()<<'\n'<<'\n';
	std::cout<<n->numberOfProducts()<<'\n'<<'\n';

	
	
	using std::cout;
	
	cout<<"test Ramp i worker i fifo\n";
	FIFO* fifo=new FIFO;
	Ramp* r = new Ramp(3);
	Worker* w = new Worker(3,fifo);
	Worker* w2 = new Worker(2,fifo);
	
	cout<<"rampa->createProduct() : "<<r->createProduct(3)<<'\n'<<"rampa->numberOfProduct()"<<r->numberOfProducts()<<'\n'<<'\n';
	cout<<"rampa->adReceiver(worker1) (worker2)"<<r->addReceiver(w)<<r->addReceiver(w2)<<"\n\n";
	cout<<"rampa->giveProduct()"<<r->giveProduct()<<'\n'<<'\n';
	
	cout<<"rampa->numberOfProducts(): "<<r->numberOfProducts()<<'\n'<<'\n';
	
	
	cout<<"worker1->numberOfProducts():  "<<w->numberOfProducts()<<'\n'<<'\n';
	cout<<"worker2->numberOfProducts():  "<<w2->numberOfProducts()<<'\n'<<'\n';
	
	cout<<"worker 1/2 removeProduct()"<<"\n\n";
	if (c=w->removeProduct())
		cout<<"worker1 c->getID():  "<<c->getID()<<'\n'<<'\n';
	else if(c=w2->removeProduct())
		cout<<"worker2 c->getID():  "<<c->getID()<<'\n'<<'\n';
	
	cout<<"worker1->numberOfProducts():  "<<w->numberOfProducts()<<'\n'<<'\n';
	cout<<"worker2->numberOfProducts():  "<<w2->numberOfProducts()<<'\n'<<'\n';
	
	
	cout<<"rampa->numberOfReceiver() i usuniecie: "<<r->numberOfReceiver()<<'\n'<<'\n';
	r->removeReceiver(w);
	
	cout<<"rampa->numberOfReceiver() i usuniecie: "<<r->numberOfReceiver()<<'\n'<<'\n';
	r->removeReceiver(w2);
	
	cout<<"rampa->numberOfReceiver(): "<<r->numberOfReceiver()<<'\n'<<'\n';
	
	
	
	
	
	
	
	delete a,b,n,fifo,r,w,w2,c;
    return 0;
    }
