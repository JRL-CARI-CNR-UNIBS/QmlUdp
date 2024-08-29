#include <QmlBinaryUdpReceiver.h>
#include <QDebug>
#include <iostream>

namespace UdpCom {
BinaryReceiver::BinaryReceiver(QObject *parent)
  : QObject(parent)
{
  connect( this, &BinaryReceiver::portChanged, this, &BinaryReceiver::createSocket, Qt::ConnectionType::QueuedConnection );
}

QString BinaryReceiver::port() const
{
  return port_;
}
void BinaryReceiver::setPort(QString port)
{
  port_=port;
  emit portChanged();
}

QString BinaryReceiver::name() const
{
  return name_;
}
void BinaryReceiver::setName(QString name)
{
  name_=name;
}

int BinaryReceiver::size() const
{
  return size_;
}
void BinaryReceiver::setSize(int size)
{
  size_=size;
  data_.resize(size_);
  if (socket_)
    socket_->setDataSize(size);
}


void BinaryReceiver::readThread()
{
  if (not socket_)
    return;
  std::cout << "[" << name_.toStdString() <<": " << port_.toStdString() << "]" << " start read thread" << std::endl;
  while (not stop_flag_)
  {
    if (socket_->isUnreadDataAvailable())
    {
      std::vector<double> v=socket_->getData();
      data_=QVector<qreal>::fromStdVector(v);
      socket_->clearQueue();
      emit dataChanged();
    }
    usleep(1000);
  }
  socket_.reset();
}

void BinaryReceiver::createSocket()
{
  if (port_.isEmpty())
    return;

  if (socket_)
  {
    stop_flag_=true;
    if (thread_.joinable())
      thread_.join();

    stop_flag_=false;
    socket_.reset();
  }
  try {
    socket_=std::make_shared<udp_binary_helper::Receiver>( port_.toStdString());
    stop_flag_=false;
    connected_=true;
  }
  catch (std::exception& e)
  {
    std::cout << e.what() << std::endl;
    connected_=false;
    return;
  }
  thread_=std::thread(&BinaryReceiver::readThread,this);


}

BinaryReceiver::~BinaryReceiver()
{
  stop_flag_=true;
  if (thread_.joinable())
    thread_.join();

}
}
