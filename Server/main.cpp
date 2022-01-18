#include <ThreadPool.hpp>

#include <boost/asio.hpp>

#include <chrono>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>

using boost::asio::ip::tcp;

std::string readDataFromClient(tcp::socket& socket, boost::system::error_code& errorCode)
{
    std::array<char, 120> buffer;
    size_t len = socket.read_some(boost::asio::buffer(buffer), errorCode);
    return std::string(buffer.data(), len);
}

void tokenize(const std::string& string, char delim, std::vector<std::string> &tokenized)
{
    std::stringstream stringstream(string); 
 
    std::string buffer;
    while (std::getline(stringstream, buffer, delim))
    { 
        tokenized.push_back(buffer); 
    } 
} 

void processing(int& start, int end)
{
    ThreadPool threadPool;
    std::mutex mutex;
    for (int i = 0; i < threadPool.getCount(); ++i)
    {
        threadPool.push([&mutex, &start, end, i] ()
        {
            while (start < end)
            {
                mutex.lock();
                if (start >= end)
                {
                    mutex.unlock();
                    break;
                }
                ++start;
                std::cout << i  << " thread is working, "
                    << "value is " << start << '\n';
                mutex.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        });
    }
}

int main()
{
    try
    {
        boost::asio::io_context ioContext;

        tcp::acceptor acceptor(ioContext, tcp::endpoint(tcp::v4(), 1234));

        while (true)
        {
            std::cout << "Accepting the connection on the port 1234!\n";
            tcp::socket socket(ioContext);

            std::cout << "Waiting for the connection!\n";
            acceptor.accept(socket);
            
            boost::system::error_code errorCode;
            const std::string messageFromClient(readDataFromClient(socket, errorCode));

            // splitting the message of client in ' ' char
            std::vector<std::string> out;
            tokenize(messageFromClient, ' ', out); 

            // start "powerful" processing
            int start = atoi(out[0].c_str()), end = atoi(out[1].c_str());
            processing(start, end);
            std::string messageToClient(std::to_string(start));

            std::cout << "The processing done.\n";

            boost::asio::write(socket, boost::asio::buffer(messageToClient), errorCode);

        }
    }
    catch (const std::exception& exception)
    {
        std::cerr << exception.what() << '\n';
    }
    
    return 0;
}
