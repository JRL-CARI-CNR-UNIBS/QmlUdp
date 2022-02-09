#ifndef QML_TCP_SENDER
#define QML_TCP_SENDER

#include <QObject>
#include <QString>
#include <include/tcp_classes.h>

namespace UdpCom {
class StringSender : public QObject
{
  Q_PROPERTY(QString host    READ host    WRITE setHost   NOTIFY hostChanged )
  Q_PROPERTY(QString port    READ port    WRITE setPort   NOTIFY portChanged)
  Q_PROPERTY(QString string  READ string  WRITE setString NOTIFY stringChanged)
  Q_OBJECT
public:
  explicit StringSender(QObject *parent = nullptr);
  ~StringSender();
  QString host() const;
  void setHost(QString ip);

  QString port() const;
  void setPort(QString port);

  QString string() const;
  void setString(QString string);

  protected slots:
  void createSocket();
signals:
  void portChanged();
  void hostChanged();
  void stringChanged();
protected:
  QString host_;
  QString port_;
  QString string_;
  bool connected_=false;
  std::shared_ptr<tcp_helper::UdpSender> socket_;
  bool stop_flag_=false;
  std::thread write_thread_;

  void writeThread();
};

}

#endif // QML_TCP_REC
