#include <boost/asio.hpp>

#include <iostream>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
    try
    {
        boost::asio::io_context ioContext;

        tcp::resolver resolver(ioContext);
        auto endpoints = resolver.resolve("127.0.0.1", "1234");

        tcp::socket socket(ioContext);
        boost::asio::connect(socket, endpoints);

        while (true)
        {
            boost::system::error_code errorCode;
            const std::string messageToServer = "42 142";
            boost::asio::write(socket, boost::asio::buffer(messageToServer), errorCode);
            
            std::array<char, 120> buffer;
            size_t len = socket.read_some(boost::asio::buffer(buffer), errorCode);

            if (errorCode == boost::asio::error::eof)
            {
                // Clean connection cut off
                break;
            }
            else if (errorCode)
            {
                throw boost::system::system_error(errorCode);
            }

            std::cout.write(buffer.data(), len);
            std::cout << '\n';
        }

    }
    catch (const std::exception& exception)
    {
        std::cerr << exception.what() << '\n';
    }
    
    return 0;
}