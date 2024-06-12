#include <iostream>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/placeholders.hpp>
#include <cstdio>

using boost::asio::ip::udp;

/*
Server echoes each datagram that receives
*/
class UdpServer {
public:
  UdpServer(boost::asio::io_context& io_context) : socket_(io_context, udp::endpoint(udp::v4(), 13)) {
    start_receive();
  }

private:
  udp::socket socket_;
  udp::endpoint remote_endpoint_;
  std::array<char, 1024> recv_buffer_;

  void start_receive(){
    socket_.async_receive_from(
      boost::asio::buffer(recv_buffer_), remote_endpoint_,
      std::bind(&UdpServer::handle_receive, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred
      )
    );
  }

  void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred) {
    if (error) {
      throw std::runtime_error("Error receiving request: " + error.message());
    }

    std::shared_ptr<std::string> message(
      new std::string(recv_buffer_.data(), bytes_transferred));

    socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
      std::bind(&UdpServer::handle_send, this, message,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred
      )
    );

    start_receive();
  }

  void handle_send(std::shared_ptr<std::string> /*message*/, const boost::system::error_code& /*error*/, std::size_t /*bytes_transferred*/) {}
};


int main()
{
  try
  {
    boost::asio::io_context io_context(1);
    UdpServer server(io_context);
    io_context.run();
  }
  catch (std::exception& e)
  {
    std::printf("Exception: %s\n", e.what());
  }
}