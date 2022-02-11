#pragma once
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <queue>
#include <mutex>
using boost::asio::ip::tcp;
using boost::asio::ip::udp;

namespace tcp_helper
{

typedef boost::asio::detail::socket_option::integer<SOL_SOCKET, SO_RCVTIMEO> rcv_timeout_option; //somewhere in your headers to be used everywhere you need it

typedef std::shared_ptr<tcp::socket> socket_ptr;
typedef std::shared_ptr<udp::socket> udp_socket_ptr;
inline std::string make_string(boost::asio::streambuf& streambuf)
{
  return {buffers_begin(streambuf.data()),
        buffers_end(streambuf.data())};
}

class TcpClient
{
protected:
  boost::asio::io_context io_context;
  tcp::socket s;
  tcp::resolver resolver;
  bool& stop_;
  std::queue<std::string> queue_;
  std::mutex mtx;

public:

  TcpClient(std::string hostname, std::string port, bool& stop_flag):
    s(io_context),
    resolver(io_context),
    stop_(stop_flag)
  {
    boost::asio::connect(s, resolver.resolve(hostname, port));
  };

  std::string read()
  {
    boost::asio::streambuf b;
    try {
      boost::asio::read_until(s, b, '\n');
    }
    catch (...)
    {

    }

    std::string str=make_string(b);
    if (str.size()>0)
    {
      mtx.lock();
      queue_.push(str);
      mtx.unlock();
    }
    return str;
  }


  bool isUnreadStringAvailable()
  {
    return  (not queue_.empty());
  }

  std::string getString()
  {
    std::string str="";
    mtx.lock();
    if (queue_.size()>0)
    {
      str=queue_.front();
      queue_.pop();
    }
    return str;
  }

  void thread()
  {
    while (not stop_)
    {
      read();
      usleep(1000);
    }
  }
};


class TcpServer
{
protected:
  boost::asio::io_service io_service;
  tcp::acceptor a;
  socket_ptr sock;
  bool& stop_;
  std::queue<std::string> queue;
  std::mutex mtx;
public:
  TcpServer(int port, bool& stop_flag):
    a(io_service, tcp::endpoint(tcp::v4(), port)),
    stop_(stop_flag)
  {
    sock=std::make_shared<tcp::socket>(io_service);
  }

  void sendString(const std::string& str)
  {
    mtx.lock();
    queue.push(str);
    mtx.unlock();
  }

  bool hasEmptyQueue()
  {
    return queue.empty();
  }

  void thread()
  {
    a.accept(*sock);
    while (not stop_)
    {
      mtx.lock();
      if (not queue.empty())
      {
        std::string str=queue.front();
        queue.pop();
        mtx.unlock();
        try
        {
          boost::asio::write(*sock, boost::asio::buffer(str, str.length()));
        }
        catch (std::exception& e)
        {
          std::cerr << "Exception in thread: " << e.what() << "\n";
          sock=std::make_shared<tcp::socket>(io_service);
          a.accept(*sock);
        }
      }
      else
        mtx.unlock();

      usleep(1e4);
    }
  }
};

class UdpSender
{
protected:
  boost::asio::io_service io_service;
  boost::asio::io_context io_context;
  udp::endpoint remote_endpoint;
  udp::resolver resolver;
  udp_socket_ptr sock;
  std::string hostname_;
  std::string port_;
  bool& stop_;
  std::queue<std::string> queue;
  std::mutex mtx;
public:
  UdpSender(std::string hostname, std::string port, bool& stop_flag):
    hostname_(hostname),
    resolver(io_context),
    port_(port),
    stop_(stop_flag)
  {
    boost::system::error_code error;
    udp::resolver::iterator iter = resolver.resolve(hostname, port,error);
    assert(!error);
    remote_endpoint = *iter;

    sock=std::make_shared<udp::socket>(io_service, udp::endpoint(udp::v4(), 0));

  }

  void sendString(const std::string& str)
  {
    mtx.lock();
    queue.push(str);
    mtx.unlock();
  }

  bool hasEmptyQueue()
  {
    return queue.empty();
  }

  void thread()
  {
    boost::system::error_code err;
    while (not stop_)
    {
      mtx.lock();
      if (not queue.empty())
      {
        std::string str=queue.front();
        queue.pop();
        mtx.unlock();
        try
        {
          auto sent = sock->send_to(boost::asio::buffer(str,str.size()), remote_endpoint, 0, err);
        }
        catch (std::exception& e)
        {
          //remote_endpoint = udp::endpoint(boost::asio::ip::address::from_string(hostname_), port_);
          std::cerr << "Exception in thread: " << e.what() << "\n";
        }
      }
      else
        mtx.unlock();

      usleep(1e4);
    }
  }
};




class UdpReceiver
{
protected:
  udp::endpoint local_endpoint_;
  udp::endpoint sender_endpoint_;
  boost::asio::io_service io_service_;
  udp_socket_ptr sock_;
  std::string port_;
  std::queue<std::string> queue_;
  std::mutex mtx_;
  std::thread read_thread_;
  char buffer_[1024]={};

  void handle_receive_from(const boost::system::error_code& error,
                           size_t bytes_recvd)
  {
    if (!error && bytes_recvd > 0)
    {
      std::string str=std::string(buffer_, bytes_recvd);
      mtx_.lock();
      queue_.push(str);
      mtx_.unlock();
    }
    sock_->async_receive_from(
          boost::asio::buffer(buffer_), sender_endpoint_,
          boost::bind(&UdpReceiver::handle_receive_from, this,
                      boost::asio::placeholders::error,
                      boost::asio::placeholders::bytes_transferred));
  }

  void read()
  {
    io_service_.run();
  }



public:

  UdpReceiver(std::string port):
    port_(port)
  {
    boost::system::error_code error;
    int port_int=std::stoi(port);
    assert(!error);
    local_endpoint_ = boost::asio::ip::udp::endpoint(
          udp::v4(), port_int);
    sock_=std::make_shared<udp::socket>(io_service_,local_endpoint_);

    sock_->async_receive_from(
          boost::asio::buffer(buffer_), sender_endpoint_,
          boost::bind(&UdpReceiver::handle_receive_from, this,
                      boost::asio::placeholders::error,
                      boost::asio::placeholders::bytes_transferred));
    read_thread_=std::thread(&tcp_helper::UdpReceiver::read,this);
  }

  ~UdpReceiver()
  {
    if (read_thread_.joinable())
      read_thread_.join();
  }
  bool isUnreadStringAvailable()
  {
    return  (not queue_.empty());
  }

  std::string getString()
  {
    std::string str="";
    mtx_.lock();
    if (queue_.size()>0)
    {
      str=queue_.front();
    }
    mtx_.unlock();
    return str;
  }

  void clearQueue()
  {
    mtx_.lock();
    while (queue_.size()>0)
    {
      queue_.pop();
    }
    mtx_.unlock();
  }

  void close()
  {
    sock_->close();
  }

};

}

