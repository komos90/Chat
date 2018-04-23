#pragma once

#include <boost/asio.hpp>

using boost::asio::ip::tcp;
namespace ba = boost::asio;

void printStreamBufLine(ba::streambuf& sb);
