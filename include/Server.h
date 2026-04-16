//
// Created by Алексей Подоплелов on 16.04.2026.
//

#ifndef MIL_SERVER_H
#define MIL_SERVER_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <memory>
#include <array>

class Server
{
private:
    boost::asio::ip::udp::socket    m_socket;
    boost::asio::ip::udp::endpoint  m_remote_endpoint;
    std::array<char, 1024>          m_recv_buffer;
private:
    void start_receive()
    {
        m_socket.async_receive_from(
            boost::asio::buffer(m_recv_buffer),
            m_remote_endpoint,
            boost::bind(&Server::handle_receive, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    }
    void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
    {
        if (!error) {
            std::string received(m_recv_buffer.data(), bytes_transferred);
            std::cout << "Received from " << m_remote_endpoint.address().to_string()
                      << ":" << m_remote_endpoint.port() << " -> " << received << std::endl;

            // Эхо-ответ - отправляем то же самое обратно
            std::string response = "Echo: " + received;
            m_socket.async_send_to(
                boost::asio::buffer(response),
                m_remote_endpoint,
                boost::bind(&Server::handle_send, this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
        } else {
            std::cerr << "Receive error: " << error.message() << std::endl;
        }

        // Продолжаем слушать следующие сообщения
        this->start_receive();
    }
    void handle_send(const boost::system::error_code& error, std::size_t /*bytes_transferred*/)
    {
        if (error) {
            std::cerr << "Send error: " << error.message() << std::endl;
        }
    }
public:
    Server(boost::asio::io_context& io_context, short port);
};


#endif //MIL_SERVER_H