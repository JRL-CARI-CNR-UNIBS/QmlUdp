#ifndef QML_TCP_REC
#define QML_TCP_REC

#include <QObject>
#include <QString>
#include <include/tcp_classes.h>

namespace UdpCom {
class StringReceiver : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString port    READ port    WRITE setPort NOTIFY portChanged)
  Q_PROPERTY(QString rstring READ rstring               NOTIFY stringChanged)
  Q_PROPERTY(QString name    READ name    WRITE setName NOTIFY stringChanged)
public:
  explicit StringReceiver(QObject *parent = nullptr);
  ~StringReceiver();
  QString port() const;
  void setPort(QString port);

  QString name() const;
  void setName(QString name);

  QString rstring() const;


  protected slots:
  void createSocket();
signals:
  void portChanged();
  void hostChanged();
  void stringChanged();
protected:
  QString port_;
  QString name_;
  QString rstring_;
  bool connected_=false;
  std::shared_ptr<tcp_helper::UdpReceiver> socket_;
  bool stop_flag_=false;
  std::thread thread_;
  std::thread read_thread_;

  void readThread();
};

}

#endif // QML_TCP_REC
