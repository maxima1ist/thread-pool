#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;

using ip::tcp;

using std::string;
using std::cout;
using std::cerr;
using std::endl;

boost::system::error_code send_(tcp::socket& socket, const string& msg)
{
    // request / message from client
    boost::system::error_code error_;
    write(socket, buffer(msg), error_);
    return error_;
}

int main(int argc, char** argv)
{
    io_service io_service;

    // socket creation
    tcp::socket socket(io_service);

    // find out port or use default
    int port = 1234;
    if (argc > 1)
    {
        port = atoi(argv[1]);
    }

    // connection
    socket.connect(tcp::endpoint(ip::address::from_string("127.0.0.1"), port));

    // request/message from client
    boost::system::error_code error_ = send_(socket, "Hello from Client!\n");
    if(!error_)
    {
        cout << "Client: " << "Sent hello message!" << endl;
    }
    else
    {
        cerr << "Send failed: " << error_.message() << endl;
    }

    // getting response from server
    streambuf receive_buffer;
    read(socket, receive_buffer, transfer_all(), error_);
    if(error_ && error_ != error::eof)
    {
        cerr << "Receive failed: " << error_.message() << endl;
    }
    else
    {
        const char* data = buffer_cast<const char*>(receive_buffer.data());
        cout << "Server: " << data << endl;
    }

    return 0;
}