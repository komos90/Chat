#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;
namespace ba = boost::asio;

class TcpServer;

class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
    tcp::socket m_socket;
    std::string m_message = "Connected to server.\n";
    boost::asio::streambuf m_readBuf;
    TcpServer& m_server;

    explicit TcpConnection(boost::asio::io_service& io_service, TcpServer& server);
    void handle_write(const boost::system::error_code& err, size_t bytes_transferred);
    void handle_read(const boost::system::error_code& err, size_t bytes_transferred);

public:
    using pointer = std::shared_ptr<TcpConnection>;

    static pointer create(boost::asio::io_service& ioService, TcpServer& server);
    tcp::socket& socket();
    void sendMessage(const std::string& message);
    void start();
};