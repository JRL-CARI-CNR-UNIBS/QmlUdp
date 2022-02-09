#include <QmlUdpSender.h>
#include <QDebug>
#include <iostream>

namespace UdpCom {
StringSender::StringSender(QObject *parent)
  : QObject(parent)
{
  std::cout << "p0" <<std::endl;
  connect( this, &StringSender::hostChanged, this, &StringSender::createSocket, Qt::ConnectionType::QueuedConnection );
  //connect( this, &TcpSender::portChanged, this, &TcpSender::createSocket, Qt::ConnectionType::QueuedConnection );
}

QString StringSender::host() const
{
  return host_;
}

void StringSender::setHost(QString host)
{
  host_=host;
  emit hostChanged();
}

QString StringSender::port() const
{
  return port_;
}
void StringSender::setPort(QString port)
{
  port_=port;
  emit portChanged();
}

QString StringSender::string() const
{
  return string_;
}
void StringSender::setString(QString string)
{
  string_=string;
  if (socket_)
  {
    socket_->sendString(string.toStdString());
    emit stringChanged();
  }
}

void StringSender::createSocket()
{
  if (host_.isEmpty() or port_.isEmpty())
    return;

  std::cout << host_.toStdString() << " : " << port_.toStdString() << std::endl;
  if (socket_)
  {
    std::cout << "1" <<std::endl;
    stop_flag_=true;
    if (write_thread_.joinable())
      write_thread_.join();
    stop_flag_=false;
//    socket_->close();
    socket_.reset();
  }
  std::cout << "2" <<std::endl;
  try {
    socket_=std::make_shared<tcp_helper::UdpSender>(host_.toStdString(), port_.toStdString(),stop_flag_);
    stop_flag_=false;
    connected_=true;
  }
  catch (std::exception& e)
  {
    std::cout << "3e" <<std::endl;
    std::cout << e.what() << std::endl;
    connected_=false;
    return;
  }
  std::cout << "3" <<std::endl;
  write_thread_=std::thread(&tcp_helper::UdpSender::thread,socket_);
  std::cout << "4" <<std::endl;
}

StringSender::~StringSender()
{
  stop_flag_=true;
  if (write_thread_.joinable())
    write_thread_.join();
  stop_flag_=false;

  if (socket_)
  {
//    socket_->close();
    socket_.reset();
  }
}
}
