all:run/client

run/client:make_o/client.o make_o/register.o
	g++ -o run/client make_o/client.o make_o/register.o -llua54

make_o/client.o:bin/client/cpp/client.cpp
	g++ -c bin/client/cpp/client.cpp -o make_o/client.o -llua54

make_o/register.o:bin/client/cpp/register.cpp
	g++ -c bin/client/cpp/register.cpp -o make_o/register.o -llua54

