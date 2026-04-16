//
// Created by Алексей Подоплелов on 16.04.2026.
//

#include "../include/Server.h"

Server::Server(boost::asio::io_context& io_context, short port) :
    m_socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
{
    std::cout << "Server started on port " << port << std::endl;
    this->start_receive();
}