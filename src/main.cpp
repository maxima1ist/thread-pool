#include "ThreadPool.hpp"

#include <boost/asio.hpp>

#include <iostream>

using namespace boost::asio;

using ip::tcp;

using std::string;
using std::cout;
using std::endl;

string readFromSocket(tcp::socket& socket)
{
    streambuf buff;
    read_until(socket, buff, "\n");
    string data = buffer_cast<const char*>(buff.data());
    return data;
}

void writeToSocket(tcp::socket& socket, const string& message)
{
    const string msg = message + "\n";
    write(socket, buffer(message));
}

auto runServer(int port)
{
    return [port]()
    {
        io_service io_service;

        while (true)
        {
            // listen for new connection
            tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), port));

            // socket creation
            tcp::socket socket_(io_service);

            cout << "Server: I'm wating..." << endl;
            // waiting for connection
            acceptor_.accept(socket_);
            cout << "Server: Oh, new Client!" << endl;

            // read operation
            string message = readFromSocket(socket_);
            cout << "Client: " << message;

            // write operation
            writeToSocket(socket_, "Hello From Server!");
            cout << "Servent sent Hello message to Client!" << endl;
        }
    };
}

int main()
{
    ThreadPool threadPool;
    for (int i = 0; i < threadPool.getCount(); ++i)
    {
        threadPool.push(runServer(1234 + i));
    }

    return 0;
}