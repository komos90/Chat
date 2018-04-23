#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <thread>
#include <iostream>
#include <array>
#include <memory>
#include "tcp_server.h"
#include "tcp_connection.h"
#include "tcp_client.h"

using boost::asio::ip::tcp;
namespace ba = boost::asio;

void server() {
    std::cout << "server()" << std::endl;

    boost::asio::io_service ioService;
    TcpServer server(ioService, 8000);
    ioService.run();
}

void client() {
    boost::asio::io_service ioService;
    TcpClient client(ioService, "localhost", "8000");
    ioService.run();
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string arg = argv[1];
        std::cout << (arg == "-c") << std::endl;
        if (arg == "-c") { 
            client();
        }
    } else {
        server();
    }
    return 0;
}

