cls
g++ -c -std=c++11 Nodes.cpp -o Nodes.o
g++ -c -std=c++11 QueueStack.cpp -o QueueStack.o
g++ -c -std=c++11 test.cpp -o test.o
g++ -c -std=c++11 Network.cpp -o Network.o
g++ -c -std=c++11 netSimulation.cpp -o netSimulation.o
g++ test.o Nodes.o QueueStack.o Network.o netSimulation.o -o test.exe
test.exe