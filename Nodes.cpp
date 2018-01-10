#include "Nodes.hpp"

vector<int> Product::number_of_Products={}, Worker::number_of_Workers={},Ramp::number_of_Ramps={},Warehouse::number_of_Warehouse={};

/********ELEMENT**********/
void Element::setID(vector<int>& numbers_of_Elements)
    {
    if(numbers_of_Elements.empty())
        {
        ID=1;
        numbers_of_Elements.push_back(ID);

        return ;
        }

    std::sort(numbers_of_Elements.begin(),numbers_of_Elements.end());

    unsigned int i=0;
    for( ; i<numbers_of_Elements.size(); i++)
        {
         if(numbers_of_Elements[i]!=i+1)  /*sprawdz czy jest kolejny nr w numeracji*/
            {
            ID=i+1;
            numbers_of_Elements.push_back(ID);
            return ;
            }
        }

    ID=numbers_of_Elements[i-1]+1;
    numbers_of_Elements.push_back(ID);
    }


/**********PRODUCT*****/
Product::~Product()
    {
    for(unsigned int i=0; i<number_of_Products.size();i++)
        {
        if(number_of_Products[i]==this->ID)
            {
            number_of_Products.erase(number_of_Products.begin()+i);

            return ;
            }
        }
    }


/**********NODE*************/
bool Node::addProduct(Product* product)
    {
    if(product)
        {
        list_of_products.push_back(product);

        return true;
        }
    return false;
    }

Product* Node::removeProduct()
    {
    if(!(list_of_products.empty()))
        {
        Product* product=list_of_products[list_of_products.size()-1];
		list_of_products.pop_back();
        return product;
        }

    return nullptr;
    }


/**********DELIVERER****************/
void Deliverer::multipliProbabilityAdding(double prob,ReceiverAndProbability* rec)    //zak³adamy ¿e jest struktura ze wskaŸnikiem na
    {                                                                                                           //odbiorce jest dodana i zmieniamy tylko prawdopodobiñstwo
    double multiplier=1-prob;

    for(auto y : list_of_receivers)
        y->probability*=multiplier;

    rec->probability=prob;
    }

bool Deliverer::addReceiver(Receiver* receiver,double probability)
    {
    if(receiver==nullptr || probability>1 || probability<0)         //z³e prawdop./ null
        return false;

    if(list_of_receivers.size())
        for(auto x : list_of_receivers) //szukamy czy odbiorca nie jest dodany ewentualnie zmieniamy prawdop. i je przeliczamy.
            {
            if(x->receiver==receiver)
                {
                if(x->probability!=probability)
                    {
                    divideProbabilityRemoving(x->probability);
                    multipliProbabilityAdding(probability,x);
                    }
                return true;
                }
            }

    //odb. nie dodany tworzymy stukture i j¹ dodajemy do vectora, i przeliczamy prawdop.
    ReceiverAndProbability* receiverAndProb= new ReceiverAndProbability;
    receiverAndProb->receiver=receiver;

    list_of_receivers.push_back(receiverAndProb);


    if(list_of_receivers.size()==1)
        {
        list_of_receivers[0]->probability=1;

        return true;
        }

    multipliProbabilityAdding(probability,receiverAndProb);

    return true;
    }

bool Deliverer::addReceiver(Receiver* receiver)
    {
    if(receiver==nullptr)
        return false;

    ReceiverAndProbability* receiverAndProb= new ReceiverAndProbability;        //stworz strukture
    receiverAndProb->receiver=receiver;

    list_of_receivers.push_back(receiverAndProb);       //dodaj strukture

    double prob=1.0/list_of_receivers.size();

    for(auto x : list_of_receivers)         //ustaw praw. propprcjonalne
		x->probability=prob;

    return true;
    }

void Deliverer::divideProbabilityRemoving(double prob)
    {
    if(!list_of_receivers.size())
        return;

    double divider=1-prob;

    if(divider)
        {
        for(auto x : list_of_receivers)
            x->probability/=divider;
        return ;
        }

    divider=1.0/list_of_receivers.size();
    for(auto x : list_of_receivers)
        x->probability=divider;

    }

bool Deliverer::removeReceiver(Receiver* receiver)
    {
    if(receiver==nullptr)
        return false;

    double removed_probability;

    for(int i=0; i<list_of_receivers.size();++i)
        if(list_of_receivers[i]->receiver==receiver)
            {
            removed_probability=list_of_receivers[i]->probability;
            ReceiverAndProbability* removed_stucture=list_of_receivers[i];

            list_of_receivers.erase(list_of_receivers.begin()+i);
            delete removed_stucture;

            divideProbabilityRemoving(removed_probability);

            return true;
            }

    return false;
    }

bool Deliverer::removeReceiver()
    {
    if(!list_of_receivers.size())
        return false;

    ReceiverAndProbability* removed_stucture=list_of_receivers[list_of_receivers.size()-1];
    double removed_probability=removed_stucture->probability;


    list_of_receivers.pop_back();
    delete removed_stucture;

    divideProbabilityRemoving(removed_probability);

    return true;

    }

bool Deliverer::setProbability(double* probability_tab, int length)
    {
    try
        {
        if(length==list_of_receivers.size() || probability_tab!=nullptr)
            {
            double sum=0;
            for(int i=0;i<length;++i)
                sum+=probability_tab[i];

            if(sum!=1)
                return false;

            for(int i=0;i<length;++i)
                (list_of_receivers[i])->probability=probability_tab[i];

            return true;
            }
        }
    catch(string s)
        {
        return false;
        }
    }

Receiver* Deliverer::randomReceiver()
    {
    double random=((double)std::rand())/RAND_MAX, sum=0;

    int ending=random*8;
	for(int i=0;i<ending;++i)			//petla o losowej liczbie iteracji
		{
		std::srand((random*(double)time(NULL)));		//losowa wartosc seed
		random=((double)std::rand())/RAND_MAX;			//losowa wartośc 0 do 1
		}

    for(int i=0;i<list_of_receivers.size();++i)
        {
        sum+=list_of_receivers[i]->probability;	//dodajemy kolejne prawdopodobiñstwa

        if(sum>=random)							//sprawdzamy czy sum>= wylosowana wartośc
            return list_of_receivers[i]->receiver;
        }

    return nullptr;
    }

void Deliverer::addTimeInProducts()
    {
    for(auto x : list_of_products)
        x->addTimeOfGettingWarehouse();
    }

void Deliverer::removeFromReceiver()
    {
    for(auto x : list_of_receivers)
        {
        x->receiver->removeDeliverer(this);
        }
    }

double Deliverer::getProbability(Receiver* receiver)
    {
    for(ReceiverAndProbability* x : list_of_receivers)
        if(x->receiver==receiver)
            return x->probability;

    return 0.0;
    }

/********RECEIVER********/
bool Receiver::addDeliverer(Deliverer* deliverer)
    {
    if(deliverer)
        {
        list_of_deliverer.push_back(deliverer);
        return true;
        }
    return false;
    }

bool Receiver::removeDeliverer(Deliverer* deliverer)
    {
    if(!deliverer)
        return false;

    for(int i=0; i<list_of_deliverer.size();i++)
        {
        if(list_of_deliverer[i]==deliverer)
            {
            list_of_deliverer.erase(list_of_deliverer.begin()+i);

            return true;
            }
        }

    return false;
    }

bool Receiver::removeDeliverer()
    {
     if(list_of_deliverer.size())
        {
        list_of_deliverer.pop_back();

        return true;
        }

    return false;
    }

void Receiver::removeFromDeliverer()
    {
    for(auto x : list_of_deliverer)
        {
        x->removeReceiver(this);
        }
    }

/************RAMP**************/
Ramp::Ramp(int _TIME_OF_DELIVERY,int id)
    {
    if(_TIME_OF_DELIVERY)
        TIME_OF_DELIVERY=_TIME_OF_DELIVERY;
    else
        TIME_OF_DELIVERY=1;

    if(id<=0)
        setID(number_of_Ramps);
    else
        {
        if(find(number_of_Ramps.begin(),number_of_Ramps.end(),id)==number_of_Ramps.end())
            {
            ID=id;
            number_of_Ramps.push_back(id);
            }
        else
            setID(number_of_Ramps);
        }
    }

Ramp::~Ramp()
    {
    for(int i=0;i<number_of_Ramps.size();++i)
        if(number_of_Ramps[i]==this->ID)
            {
            number_of_Ramps.erase(number_of_Ramps.begin()+i);

            removeFromReceiver();

            return;
            }
    }

bool Ramp::createProduct(int time)
    {
    if(!(time%TIME_OF_DELIVERY))
        {
        return addProduct(new Product);
        }
    return false;
    }

bool Ramp::giveProduct()
    {
    if(!(list_of_products.empty()))
        {
        Receiver* rec=randomReceiver();

        if(rec)
            return rec->takeProduct(removeProduct());

        return false;
        }

    return false;
    }


/********WORKER***********/
bool Worker::addProduct(Product* product)
    {
    if(type_of_taking_products)
        return type_of_taking_products->push(product, list_of_products);

    return false;
    }

Product* Worker::removeProduct()
    {
    if(product_in_processing)
        return product_in_processing;

    if(type_of_taking_products)
        return type_of_taking_products->pop(list_of_products);

    return nullptr;
    }

bool Worker::takeProduct(Product* product)
    {
    return addProduct(product);
    }

Worker::Worker(QueueStack* type, int _PROCESSING_TIME, int id)
    {
    if(!_PROCESSING_TIME)
        PROCESSING_TIME=1;
    else
        PROCESSING_TIME=abs(_PROCESSING_TIME);

    type_of_taking_products=type;

    if(id<=0)
        setID(number_of_Workers);
    else
        {
        if(find(number_of_Workers.begin(),number_of_Workers.end(),id)==number_of_Workers.end())
            {
            ID=id;
            number_of_Workers.push_back(id);
            }
        else
            setID(number_of_Workers);
        }
    }

Worker::~Worker()
    {
    for(int i=0;i<number_of_Workers.size();++i)
        if(number_of_Workers[i]==this->ID)
            {
            number_of_Workers.erase(number_of_Workers.begin()+i);

            removeFromDeliverer();
            removeFromReceiver();

            return;
            }
    }

bool Worker::giveProduct()              // przekazanie produktu
    {
    if(!(time_of_processing%=PROCESSING_TIME))               //modulo ==0 => product gotowy lub nie było przetwarzania
        {
        if(product_in_processing)                           //aktualnie przetwarzany jest produkt i jest to koniec obróbki
            {
            Receiver* rec=randomReceiver();
            if(rec->takeProduct(product_in_processing))      //odbiorca odebrał product poprawnie
                {
                product_in_processing=nullptr;
                }
            else
                return false;

            time_of_processing=0;
            if(!(list_of_products.empty()))                   //po przekazaniu produktu rozpoczęcie przetwarzania nowego produktu
                {
                product_in_processing=type_of_taking_products->pop(list_of_products);
                time_of_processing=1;
                }

            return true;
            }
        else                                                //nic nie jest przetwarzane
            {
            if(!(list_of_products.empty()))                   //są zgromadzone jakieś produkty
                {
                product_in_processing=type_of_taking_products->pop(list_of_products);
                time_of_processing=1;
                return false;
                }
            else                                            //nic nie przetwarzane i nie zgromadzne
                return false;
            }
        }
    else                            //czas przetwarzania !=0
        {
        if(product_in_processing)   //produkt jest przetwarzany dodaj czas przetwarzania
            {
            time_of_processing++;
            return false;
            }
        else                        //czas przetwarzania !=0 i nic nie jest przetwarzane => błąd
            {
            time_of_processing=0;
            return false;
            }
        }
    }

std::string Worker::type()
    {
    return (type_of_taking_products->type());
    }

void Worker::addTimeInProducts()
    {
    for(auto x : list_of_products)
        x->addTimeOfGettingWarehouse();

    if(product_in_processing)
        product_in_processing->addTimeOfGettingWarehouse();
    }

/***********WAREHOUSE***********/
Warehouse::Warehouse(int id)
    {
    if(id<=0)
        setID(number_of_Warehouse);
    else
        {
        if(find(number_of_Warehouse.begin(),number_of_Warehouse.end(),id)==number_of_Warehouse.end())
            {
            ID=id;
            number_of_Warehouse.push_back(id);
            }
        else
            setID(number_of_Warehouse);
        }
    }

Warehouse::~Warehouse()
    {
    for(int i=0;i<number_of_Warehouse.size();++i)
        if(number_of_Warehouse[i]==this->ID)
            {
            number_of_Warehouse.erase(number_of_Warehouse.begin()+i);

            removeFromDeliverer();

            return;
            }
    }

bool Warehouse::takeProduct(Product* product)
    {
    if(product)
        {
        list_of_products.push_back(product);
        return true;
        }

    return false;
    }


/*************Koniec Nodes.cpp******************/

