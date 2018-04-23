#include <iostream> 
#include "tcp_client.h"
#include "util.h"

void TcpClient::handel_read(const boost::system::error_code& err, size_t bytes_transferred) {
    printStreamBufLine(m_buf);
    boost::asio::async_read_until(m_socket,
        m_buf,
        '\n',
        boost::bind(&TcpClient::handel_read,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void TcpClient::handel_write(const boost::system::error_code& err, size_t bytes_transferred) {
    std::getline(std::cin, m_inBuf);
    m_inBuf.append("\n");
    boost::asio::async_write(m_socket,
        boost::asio::buffer(m_inBuf),
        boost::bind(&TcpClient::handel_write,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void TcpClient::start() {
    boost::asio::async_read_until(m_socket,
        m_buf,
        '\n',
        boost::bind(&TcpClient::handel_read,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));

    std::getline(std::cin, m_inBuf);
    m_inBuf.append("\n");
    boost::asio::async_write(m_socket,
        boost::asio::buffer(m_inBuf),
        boost::bind(&TcpClient::handel_write,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

TcpClient::TcpClient(boost::asio::io_service& ioService, const std::string& server, const std::string& port)
    : m_socket(ioService)
{
    tcp::resolver resolver(ioService);
    tcp::resolver::query query("localhost", "8000");
    tcp::resolver::iterator endpoints(resolver.resolve(query));

    try {
        boost::asio::connect(m_socket, endpoints);
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
    }
    start();
}
