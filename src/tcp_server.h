#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "tcp_connection.h"

using boost::asio::ip::tcp;
namespace ba = boost::asio;

class TcpServer {
    tcp::acceptor m_acceptor;
    std::vector<std::weak_ptr<TcpConnection>> openConnections;
    std::vector<std::string> m_messageLog;

    void start_accept();
    void handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code& error);

public:
    explicit TcpServer(boost::asio::io_service& io_service, int port);
    void broadcastToAll(std::string message);
};