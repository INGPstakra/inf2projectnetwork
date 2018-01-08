#include "Network.hpp"

/************dodawanie wezla**********/

bool Network::addRamp(Ramp* ramp)
    {
    if(ramp)
        {
        list_of_Ramps.push_back(ramp);

        return true;
        }


    return false;
    }

bool Network::addWorker(Worker* worker)
    {
    if(worker)
        {
        list_of_Workers.push_back(worker);

        return true;
        }


    return false;
    }

bool Network::addWarehouse(Warehouse* warehouse)
    {
    if(warehouse)
        {
        list_of_Warehouse.push_back(warehouse);

        return true;
        }


    return false;
    }

/************usuwanie danego wezla**********/
bool Network::removeRamp(Ramp* ramp)
    {
    if(!ramp)
        return false;

    for(int i=0;i<list_of_Ramps.size();i++)
        {
        if(list_of_Ramps[i]==ramp)
            {
            list_of_Ramps.erase(list_of_Ramps.begin()+i);

            ramp.removeFromReceiver();

            return true;
            }
        }

    return false;
    }

bool Network::removeWorker(Worker* worker)
    {
    if(!worker)
        return false;

    for(int i=0;i<list_of_Workers.size();i++)
        {
        if(list_of_Workers[i]==worker)
            {
            list_of_Workers.erase(list_of_Workers.begin()+i);

            worker.removeFromDeliverer();
            worker.removeFromReceiver();

            return true;
            }
        }

    return false;
    }

bool Network::removeWarehouse(Warehouse* warehouse)
    {
    if(!warehouse)
        return false;

    for(int i=0;i<list_of_Warehouses.size();i++)
        {
        if(list_of_Warehouses[i]==warehouse)
            {
            list_of_Warehouses.erase(list_of_Warehouses.begin()+i);

            warehouse.removeFromDeliverer();

            return true;
            }
        }

    return false;
    }

/************usuwanie ustatniego elementu z listy**********/
Ramp* Network::removeRamp()
    {
    if(!list_of_Ramps.empty())
        return nullptr;

    Ramp* ramp=list_of_Ramps[list_of_Ramps.size()-1];

    list_of_Ramps.pop_back();

    ramp.removeFromReceiver();

    return ramp;
    }

Worker* Network::removeWorker()
    {
    if(!list_of_Workers.empty())
        return nullptr;

    Worker* worker=list_of_Workers[list_of_Workers.size()-1];

    worker.removeFromDeliverer();
    worker.removeFromReceiver();

    list_of_Workers.pop_back();

    return worker;
    }

Warehouse* Network::removeWarehouse()
    {
    if(!list_of_Warehouses.empty())
        return nullptr;

    Warehouse* warehouse=list_of_Warehouses[list_of_Warehouses.size()-1];

    warehouse.removeFromDeliverer();

    list_of_Warehouses.pop_back();

    return warehouse;
    }

/************usuwanie wszystkiego************/
void Network::removeAllNodes()
    {
    try
        {
        for(Ramp* x : list_of_Ramps)
            {
            Product* p=nullptr;
            while(p=x->removeProduct())
                delete p;

            delete x;
            }
        list_of_Ramps.clear();

        for(Worker* x : list_of_Workers)
            {
            Product* p=nullptr;
            while(p=x->removeProduct())
                delete p;

            delete x;
            }
        list_of_Workers.clear();

        for(Warehouse* x : list_of_Warehouses)
            {
            Product* p=nullptr;
            while(p=x->removeProduct())
                delete p;
            }
        list_of_Warehouses.clear();
        }
    catch(string s)
        std::cout<<"\nblad usuwania produktow\n"<<s;
    catch(...)
        std::cout<<"\nblad usuwania produktow\n";
    }

void Network::clearAllNodes()
    {
    try
        {
        for(Ramp* x : list_of_Ramps)
            {
            Product* p=nullptr;
            while(p=x->removeProduct())
                delete p;
            }

        for(Worker* x : list_of_Workers)
            {
            Product* p=nullptr;
            while(p=x->removeProduct())
                delete p;
            }

        for(Warehouse* x : list_of_Warehouses)
            {
            Product* p=nullptr;
            while(p=x->removeProduct())
                delete p;
            }
        }
    catch(string s)
        std::cout<<"\nblad usuwania produktow\n"<<s;
    catch(...)
        std::cout<<"\nblad usuwania produktow\n";
    }


/************znajdowanie wezla*****************/
Ramp* Network::findRamp(int id)
    {
    if(id<=0)
        return nullptr;

    for(auto x : list_of_Ramps)
        if(x->getID()==id)
            return x;

    return nullptr;
    }

Worker* Network::findWorker(int id)
    {
    if(id<=0)
        return nullptr;

    for(auto x : list_of_Workers)
        if(x->getID()==id)
            return x;

    return nullptr;
    }

Warehouse* Network::findWarehouse(int id)
    {
    if(id<=0)
        return nullptr;

    for(auto x : list_of_Warehouses)
        if(x->getID()==id)
            return x;

    return nullptr;
    }

/***********po³¹czenia********/

bool Network::addLink(Deliverer* deliverer, Receiver* receiver, double probability)
    {
    if(!deliverer || !receiver)
        return false;

    Receiver* r=nullptr;
    Deliverer* d=nullptr;

    for(auto x : list_of_Ramps)     //szukamy dostawcy
        if(x==deliverer)
           d=x;

    for(auto x : list_of_Workers)   //szukamy dustawcy i odbiorcy
        {
        if(x==receiver)
            r=x;
        else if(x==deliverer)
            d=x;
        }

    if(r==receiver && d=deliverer)  //jesli znalezieni
        {
        r->addDeliverer(d);
        if(probability!=-1)
            return d->addReceiver(r,probability);

        return d->addReceiver(r);
        }

    for(auto x : list_of_Warehouses)    //szukamy odbiorcy
        if(x==receiver)
            r=x;

    if(r==receiver && d=deliverer)      //jesli znalezieni
        {
        r->addDeliverer(d);
        if(probability!=-1)
            return d->addReceiver(r,probability);

        return d->addReceiver(r);
        }
    else                                //jesli nie znalezieni
        return false;

    }

bool Network::removeLink(Deliverer* deliverer, Receiver* receiver)
    {
    if(!deliverer && !receiver)
        return false;

    if(deliverer)
        deliverer->removeReceiver(receiver);

    if(receiver)
        receiver->removeDeliverer(deliverer);

    return true;
    }

/***********wczytywanie********************/

string veryfi_padding(string line, std::string::size_type pos_start, std::string::size_type pos_end)
    {
    string error="";

    for(auto i=pos_start;i<=pos_end;++i)
        if(line[i]!=' ' && line[i]!='\t')   //moze zaczynac sie spacja lub tab
            {
            error="/nZly format";

            break;
            }
    return error;
    }

bool loadElementsFromFile(istream& in)
    {
    std::string::size_type ptr=nullptr;
    const char R='r', W='w', S='s',L='l';
    char current_flag=R, possibly_flag=R;
    string error="",line="";
    unsigned int f=0;
    const string ramp="LOADING_RAMP id=", delivery_interwal=" delivery-interval=", worker="WORKER id=", processing_time=" processing-time=",
                 queue=" queue-type=", type_lifo="LIFO", type_fifo="FIFO", warehouse="STOREHOUSE id=", link="LINK src=", src_ramp="ramp-",
                 src_dest_worker="worker-", dest=" dest=", dest_warehouse="store-", probability=" p=";
    int line_number=0;

    while(std::getline(in,line))        //glowana petla odczytu danych
        {
        if(line[0]==';' || line[0]=="")
            continue;
        else if((f=line.find(ramp,0))!=std::string::npos)   //jesli znaleziono lancuch ramp
            {
            if(current_flag!=R && possibly_flag!=R)
                {
                error="Blad kolejnosci!/nPoprawna kolejnosc: Rampa, Pracownik, Magazyn, Polaczenia.\n";
                break;
                }

            try
                {
                if(f!=0)                //jesli nie rozpoczyna sie od poczatku wiersza
                    {
                    error=veryfi_padding(line,0,f);     //sprawdzamy czy wypelnieniem sa spacje i abulacje
                    if(error!="")
                        throw "format";
                    }

                std::string::size_type ptr=nullptr;             //ptr intex na miejsce za liczba od poczatku tej liczby
                int id=std::stoi(&(line[f+ramp.length()]),ptr); //wyciagniecie id z napisu
                ptr+=f+ramp.length();

                /***********************/
                if(f=line.find(delivery_interwal,ptr))          //czy kontynuacja od ptr zawiera lancuch delivery_interwal
                    {
                    if(f!=ptr)              //jesli nie zaczyna sie od razu
                        {
                        error=veryfi_padding(line,ptr,f);
                        if(error!="")
                            throw "format";
                        }

                    int time_of_delivery=std::stoi(&(line[f+delivery_interwal.length()]),ptr);    //wyciagniecie wartosci czestosci dostaw
                    ptr+=f+delivery_interwal.length();          //index

                    /***********************/
                    if(line[ptr]!='\0')
                        throw "dodatkowe znaki na koncu";

                    Ramp* ra=new Ramp(time_of_delivery,id);

                    if(!addRamp(ra))
                        throw "Blad przy dodawaniu rampy";
                    }
                else
                    throw "blad";
                }
            catch(string s)
                {
                if(s=="format")
                    error+="w wierszu\n"+to_string(line_number)+": "+line+'\n';
                else if(s=="blad")
                    error=s+"w wierszu\n"+to_string(line_number)+": "+line+'\n';
                else
                    error="Nieznany blad:\n"+s+"\nw wierszu:\n"+to_string(line_number)+": "+line+'\n';

                break;
                }
            catch(...)
                {
                error="Nieznany blad w wierszu:\n"+to_string(line_number)+": "+line+'\n';
                break;
                }
            else
                {
                error="Nieznany blad w wierszu:\n"+to_string(line_number)+": "+line+'\n';
                break;
                }


            possibly_flag=W;
            }
        else if((f=line.find(worker,0))!=std::string::npos)   //jesli znaleziono lancuch worker
            {
            if(current_flag!=W && possibly_flag!=W)
                {
                error="Blad kolejnosci!/nPoprawna kolejnosc: Rampa, Pracownik, Magazyn, Polaczenia.\n";
                break;
                }

            try
                {
                if(f!=0)                //jesli nie rozpoczyna sie od poczatku wiersza
                    {
                    error=veryfi_padding(line,0,f);     //sprawdzamy czy wypelnieniem sa spacje i tabulacje
                    if(error!="")
                        throw "format";
                    }

                ptr=nullptr;             //ptr intex na miejsce za liczba od poczatku tej liczby
                int id=std::stoi(&(line[f+worker.length()]),ptr); //wyciagniecie id z napisu
                ptr+=f+worker.length();

                /***********************/
                if(f=line.find(processing_time,ptr))          //czy kontynuacja od ptr zawiera lancuch processing_time
                    {
                    if(f!=ptr)              //jesli nie zaczyna sie od razu
                        {
                        error=veryfi_padding(line,ptr,f);
                        if(error!="")
                            throw "format";
                        }

                    int processing=std::stoi(&(line[f+processing_time.length()]),ptr);    //wyciagniecie wartosci czasu przetwarzania
                    ptr+=f+processing_time.length();          //index

                    /***********************/
                    if(f=line.find(queue,ptr))          //czy kontynuacja od ptr zawiera lancuch queue
                        {
                        if(f!=ptr)              //jesli nie zaczyna sie od razu
                            {
                            error=veryfi_padding(line,ptr,f);
                            if(error!="")
                                throw "format";
                            }

                        ptr+=f+queue.length();

                        string type_queue="";

                        // sprawdzanie typu kolejki
                        if(f=line.find(type_fifo,ptr))  //FIFO
                            {
                             if(f!=ptr)              //jesli nie zaczyna sie od razu
                                {
                                error=veryfi_padding(line,ptr,f);
                                if(error!="")
                                    throw "format";
                                }

                            type_queue=type_fifo;
                            ptr+=f+type_fifo.length();
                            }
                        else if(f=line.find(type_lifo,ptr)) //LIFO
                            {
                             if(f!=ptr)              //jesli nie zaczyna sie od razu
                                {
                                error=veryfi_padding(line,ptr,f);
                                if(error!="")
                                    throw "format";
                                }

                            type_queue=type_lifo;
                            ptr+=f+type_lifo.length();
                            }
                        else
                            throw "blad";

                        /***********************/
                        if(line[ptr]!='\0')
                            throw "dodatkowe znaki na koncu";

                        Worker* employee=new Worker(type_queue,processing,id);

                        if(!addWorker(employee))
                            throw "Blad przy dodawaniu pracownika";

                        }
                    else
                        throw "blad";
                    }
                else
                    throw "blad";
                }
            catch(string s)
                {
                if(s=="format")
                    error+="w wierszu\n"+to_string(line_number)+": "+line+'\n';
                else if(s=="blad")
                    error=s+"w wierszu\n"+to_string(line_number)+": "+line+'\n';
                else
                    error="blad:\n"+s+"\nw wierszu:\n"+to_string(line_number)+": "+line+'\n';

                break;
                }
            catch(...)
                {
                error="Nieznany blad w wierszu:\n"+to_string(line_number)+": "+line+'\n';
                break;
                }
            else
                {
                error="Nieznany blad w wierszu:\n"+to_string(line_number)+": "+line+'\n';
                break;
                }

            possibly_flag=S;
            }
        else if((f=line.find(warehouse,0))!=std::string::npos)   //jesli znaleziono lancuch warehouse
            {
            if(current_flag!=S && possibly_flag!=S)
                {
                error="Blad kolejnosci!/nPoprawna kolejnosc: Rampa, Pracownik, Magazyn, Polaczenia.\n";
                break;
                }

            try
                {
                if(f!=0)                //jesli nie rozpoczyna sie od poczatku wiersza
                    {
                    error=veryfi_padding(line,0,f);     //sprawdzamy czy wypelnieniem sa spacje i tabulacje
                    if(error!="")
                        throw "format";
                    }

                ptr=nullptr;             //ptr intex na miejsce za liczba od poczatku tej liczby
                int id=std::stoi(&(line[f+warehouse.length()]),ptr); //wyciagniecie id z napisu
                ptr+=f+warehouse.length();

                /***********************/
                if(line[ptr]!='\0')
                    throw "dodatkowe znaki na koncu";

                Warehouse* storehouse=new Warehouse(id);

                if(!addWarehouse(storehouse))
                    throw "Blad przy dodawaniu magazynu";

                }
            catch(string s)
                {
                if(s=="format")
                    error+="w wierszu\n"+to_string(line_number)+": "+line+'\n';
                else if(s=="blad")
                    error=s+"w wierszu\n"+to_string(line_number)+": "+line+'\n';
                else
                    error="blad:\n"+s+"\nw wierszu:\n"+to_string(line_number)+": "+line+'\n';

                break;
                }
            catch(...)
                {
                error="Nieznany blad w wierszu:\n"+to_string(line_number)+": "+line+'\n';
                break;
                }
            else
                {
                error="Nieznany blad w wierszu:\n"+to_string(line_number)+": "+line+'\n';
                break;
                }

            possibly_flag=L;
            }
        else if((f=line.find(link,0))!=std::string::npos)   //jesli znaleziono lancuch link
            {
            if(current_flag!=L && possibly_flag!=L)
                {
                error="Blad kolejnosci!/nPoprawna kolejnosc: Rampa, Pracownik, Magazyn, Polaczenia.\n";
                break;
                }

            try
                {
                if(f!=0)                //jesli nie rozpoczyna sie od poczatku wiersza
                    {
                    error=veryfi_padding(line,0,f);     //sprawdzamy czy wypelnieniem sa spacje i tabulacje
                    if(error!="")
                        throw "format";
                    }

                ptr=f+link.length();

                /******************/
                Deliverer* deliverer=nullptr;

                if(f=line.find(src_ramp,ptr))  //src==ramp-
                    {
                     if(f!=ptr)              //jesli nie zaczyna sie od razu
                        {
                        error=veryfi_padding(line,ptr,f);
                        if(error!="")
                            throw "format";
                        }

                    int id=std::stoi(&(line[f+src_ramp.length()]),ptr); //wyciagniecie id z napisu
                    ptr+=f+src_ramp.length();

                    deliverer=findRamp(id);
                    }
                else if(f=line.find(src_dest_worker,ptr)) //src==worker-
                    {
                     if(f!=ptr)              //jesli nie zaczyna sie od razu
                        {
                        error=veryfi_padding(line,ptr,f);
                        if(error!="")
                            throw "format";
                        }

                    int id=std::stoi(&(line[f+src_dest_worker.length()]),ptr); //wyciagniecie id z napisu
                    ptr+=f+src_dest_worker.length();

                    deliverer=findWorker(id);
                    }
                else
                    throw "blad";

                if(!deliverer)
                    throw "blad zrodla polaczenia";

                /********************/


                if(f=line.find(dest,ptr))          //czy kontynuacja od ptr zawiera lancuch dest
                    {
                    if(f!=ptr)              //jesli nie zaczyna sie od razu
                        {
                        error=veryfi_padding(line,ptr,f);
                        if(error!="")
                            throw "format";
                        }

                    ptr=f+dest.length();
                    }
                else
                    throw "blad";

                /*******************/

                Receiver* receiver=nullptr;

                if(f=line.find(dest_warehouse,ptr))  //dest==wstorehouse-
                    {
                     if(f!=ptr)              //jesli nie zaczyna sie od razu
                        {
                        error=veryfi_padding(line,ptr,f);
                        if(error!="")
                            throw "format";
                        }

                    int id=std::stoi(&(line[f+dest_warehouse.length()]),ptr); //wyciagniecie id z napisu
                    ptr+=f+dest_warehouse.length();

                    receiver=findWarehouse(id);
                    }
                else if(f=line.find(src_dest_worker,ptr)) //dest==worker-
                    {
                     if(f!=ptr)              //jesli nie zaczyna sie od razu
                        {
                        error=veryfi_padding(line,ptr,f);
                        if(error!="")
                            throw "format";
                        }

                    int id=std::stoi(&(line[f+src_dest_worker.length()]),ptr); //wyciagniecie id z napisu
                    ptr+=f+src_dest_worker.length();

                    receiver=findWorker(id);
                    }
                else
                    throw "blad";

                if(!receiver)
                    throw "blad konca polaczenia";

                /******************************/
                double p=0;

                if(f=line.find(probability,ptr))  // p=
                    {
                     if(f!=ptr)              //jesli nie zaczyna sie od razu
                        {
                        error=veryfi_padding(line,ptr,f);
                        if(error!="")
                            throw "format";
                        }

                    p=std::stoi(&(line[f+probability.length()]),ptr); //wyciagniecie wartosci prawdopodobienstwa poloczenia z napisu
                    ptr+=f+dest_warehouse.length();
                    }
                else
                    throw "blad prawdopodobienstwa";

                /***********************/
                if(line[ptr]!='\0')
                    throw "dodatkowe znaki na koncu";

                /**********************/

                if(deliverer->addReceiver(deliverer,p))
                        if(!receiver->addDeliverer(deliverer))
                            deliverer->removeReceiver(receiver);
                else
                    throw "blad dodawania polaczenia w wezlach";
                }
            catch(string s)
                {
                if(s=="format")
                    error+="w wierszu\n"+to_string(line_number)+": "+line+'\n';
                else if(s=="blad")
                    error=s+"w wierszu\n"+to_string(line_number)+": "+line+'\n';
                else
                    error="blad:\n"+s+"\nw wierszu:\n"+to_string(line_number)+": "+line+'\n';

                break;
                }
            catch(...)
                {
                error="Nieznany blad w wierszu:\n"+to_string(line_number)+": "+line+'\n';
                break;
                }
            else
                {
                error="Nieznany blad w wierszu:\n"+to_string(line_number)+": "+line+'\n';
                break;
                }

            possibly_flag=L;
            }
        else
            {
            error="\nnieznany blad w wierszu:\n"+to_string(line_number)+'\n'+line+'\n';
            }

        line_number++;          //aktualna wczytana linia juz nastepna
        }

     if(error!="")
            {
            removeAllNodes();
            cout<<error;
            return false;
            }


    return true;
    }















