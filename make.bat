g++ -c Nodes.cpp -o Nodes.o
g++ -c QueueStack.cpp -o QueueStack.o
g++ -c test.cpp -o test.o
g++ test.o Nodes.o QueueStack.o -o test.exe
test.exe