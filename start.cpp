#include<iostream>
#include<vector>
#include<memory>

int product_id=1;
int object_id=1;

Class Object{
	const int id;
	std::vector<Product*> _list_of_products;
	
	public:
		int get_id(){return id;}
		void Add_Product(Product* _product){_list_of_products.push_back(_product)}
		void Delete_Product(Product* _product);
		void Delete_Product(int id);
		int get_amount_of_products(){return _list_of_products.size();}
};

Class Network{
	vector<Object*> _list_of_elements_in_network;
	
	public:
		void Add_element(Object* _object){_list_of_elements_in_network.push_back(_object)}
		void Remove_element(Object* _object);
		void Remove_element(int _id);
};

void Network::Remove_element(Object* _object)
{
	int i=0;
	while(_list_of_elements_in_network[i] != _object)
	{
		i++;
	}
	if(_list_of_elements_in_network[i] == _object)
	{
	_list_of_elements_in_network.erase(i);
	std::cout<<"element "<<i<<" usuniety"<<std::endl;
	}
}

void Network::Remove_element(int _id)
{
	int i=0;
	while(_list_of_elements_in_network[i]->get_id() != _id)
	{
		i++;
	}
	if(_list_of_elements_in_network[i]->get_id() == _id)
	{
	_list_of_elements_in_network.erase(i);
	std::cout<<"element "<<i<<" usuniety"<<std::endl;
	}
}

Class Receiver{
	public:
	virtual void being_added(){} //for now
};

Class Product{
	int id;
	int time_of_getting_to_warehouse;
	public:
		Product(){id=product_id;product_id++;time_of_getting_to_warehouse=0;}
		int get_id(){return id;}
		void Add_time(){time_of_getting_to_warehouse++;}
		int get_time(){return time_of_getting_to_warehouse;}
};

Class Ramp
	: public Object
{
	const int time_of_delivery;
	bool full;
	std::vector<float> probability;
	std::vector<Receiver*> _list_of_receivers;
	
	public:
		bool Isfull(){return full;}
		void Add_Receiver(Receiver* _receiver,float _probability);
};

void Ramp::Add_Receiver(Receiver* _receiver,float _probability)
{
	_list_of_receivers.push_back(_receiver);
	probability.push_back(_probability);
}

Class Worker
	: public Object
	: public Reciver
{
	const int time_of_production;
	std::vector<float> probability;
	std::vector<Receiver*> _list_of_receivers;
	//thing to do is to get the name and type of prefered way to do
	
	public:
		void Add_Receiver(Receiver* _receiver,float _probability);
};

void Worker::Add_Receiver(Receiver* _receiver,float _probability)
{
	_list_of_receivers.push_back(_receiver);
	probability.push_back(_probability);
}

Class Warehouse
	: public Object
	: public Reciver
{
	std::vector<Worker*> _list_of_delivers;
	
	public:
		void Add_Deliver(Worker* _deliver);
}

void Warehouse::Add_Deliver(Worker* _deliver)
{
	_list_of_delivers.push_back(_deliver);
}

Class Report{
	public:
		virtual std::stirnig Add_Report(Object*)=0;
};

Class Report_Worker
	: public Report
{
	public:
		std::string Add_Report(Worker*);
};

std::string Report_Worker::Add_Report(Worker*)
{
	std::string w;
	w<<"Worker id = "<<Worker->get_id()<<""
}

Class Report_Warehouse
	: public Report
{
	public:
		std::string Add_Report(Worker*);
};

Class Report_Ramp
	: public Report
{
	public:
		std::string Add_Report(Worker*);
};

Class Simulation{
	Network* _network;
	public:
		void start();
		void stop();
		int Create_Raport();
};

void Load_elements_from_file(std::string _path,Network& _network);
void Save_elements_to_file(std::string _path,const Network& _network);

void Create_Raport_State(const Network& _network);
void Create_Raport_Framework(const Network& _network);


