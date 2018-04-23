#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;
namespace ba = boost::asio;

class TcpClient {
    tcp::socket m_socket;
    boost::asio::streambuf m_buf;
    std::string m_inBuf;

    void handel_read(const boost::system::error_code& err, size_t bytes_transferred);
    void handel_write(const boost::system::error_code& err, size_t bytes_transferred);
    void start();

public:
    TcpClient(boost::asio::io_service& ioService, const std::string& server, const std::string& port);
};