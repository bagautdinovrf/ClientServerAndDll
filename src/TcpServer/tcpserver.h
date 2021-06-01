#ifndef TCPSERVER_H
#define TCPSERVER_H


#include <QObject>
#include <QTcpServer>
//#include <QScopedPointer>



class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0);
    ~TcpServer();

    /**
     * @brief serverStart
     * @return
     */
    bool serverStart();

public slots:
    /**
     * @brief start
     * @return
     */
    void start();

private slots:
    /**
     * @brief slot_newConnection
     */
    void slot_newConnection();

    /**
     * @brief slot_dataRead
     */
    void slot_dataRead();

    /**
     * @brief slot_clientDisconnect
     */
    void slot_clientDisconnect();


signals:
    /**
     * @brief signal_geodata
     * @param data
     */
    void signal_geodata( QByteArray data );

    void signal_info(QString text);

private:
    /// /
    QTcpServer                          * mTcpServer;

    bool                                mServerStatus;

};

#endif // TCPSERVER_H
