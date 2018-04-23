#include "tcp_server.h"


void TcpServer::start_accept() {
    auto new_connection = TcpConnection::create(m_acceptor.get_io_service(), *this);
    m_acceptor.async_accept(new_connection->socket(),
        boost::bind(&TcpServer::handle_accept,
            this,
            new_connection,
            boost::asio::placeholders::error));
    openConnections.push_back(std::weak_ptr<TcpConnection>(new_connection));
}

void TcpServer::handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code& error) {
    if (!error) {
        new_connection->start();
    }
    start_accept();
}

void TcpServer::broadcastToAll(std::string message) {
    m_messageLog.push_back(message);
    for (int i = 0; i < openConnections.size(); ++i) {
        auto connection = openConnections[i];
        if (auto sharedConn = connection.lock()) {
            sharedConn->sendMessage(m_messageLog.back());
        } else {
            openConnections[i] = openConnections[openConnections.size() - 1];
            openConnections.pop_back();
        }
    }
}

TcpServer::TcpServer(boost::asio::io_service& io_service, int port)
    : m_acceptor(io_service, tcp::endpoint(tcp::v4(), port))
{
    start_accept();
}
