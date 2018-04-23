#include <iostream>
#include "tcp_connection.h"
#include "tcp_server.h"

TcpConnection::TcpConnection(boost::asio::io_service& io_service, TcpServer& server)
    : m_socket(io_service)
    , m_server(server)
{
}

void TcpConnection::handle_write(const boost::system::error_code& err, size_t bytes_transferred) {

}

void TcpConnection::handle_read(const boost::system::error_code& err, size_t bytes_transferred) {
    std::istream is(&m_readBuf);
    std::string s;
    std::getline(is, s);
    s += '\n';
    std::cout << s;
    m_server.broadcastToAll(s);
    boost::asio::async_read_until(m_socket,
        m_readBuf,
        '\n',
        boost::bind(&TcpConnection::handle_read,
            shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

TcpConnection::pointer TcpConnection::create(boost::asio::io_service& ioService, TcpServer& server) {
    return pointer(new TcpConnection(ioService, server));
}

tcp::socket& TcpConnection::socket() {
    return m_socket;
}

void TcpConnection::sendMessage(const std::string& message) {
    boost::asio::async_write(m_socket,
        boost::asio::buffer(message),
        boost::bind(&TcpConnection::handle_write,
            shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void TcpConnection::start() {
    boost::asio::async_write(m_socket,
        boost::asio::buffer(m_message),
        boost::bind(&TcpConnection::handle_write,
            shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    boost::asio::async_read_until(m_socket,
        m_readBuf,
        '\n',
        boost::bind(&TcpConnection::handle_read,
            shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}
