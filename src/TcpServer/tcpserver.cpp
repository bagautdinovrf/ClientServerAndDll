

#include "tcpserver.h"


#include <QTcpServer>
#include <QTcpSocket>
#include <QtDebug>


TcpServer::TcpServer(QObject *parent) :
    QObject(parent),
    mTcpServer(0),
    mServerStatus(false)
{
    //
}


TcpServer::~TcpServer()
{
    //
}

/**
 * @brief TcpServer::serverStart
 * @return
 */
bool TcpServer::serverStart()
{
    start();
    return mServerStatus;
}

/**
 * @brief TcpServer::start
 */
void TcpServer::start()
{
    mTcpServer = new QTcpServer(this);
    mTcpServer->setMaxPendingConnections( 2 );
    connect( mTcpServer, &QTcpServer::newConnection, &TcpServer::slot_newConnection );

    if( !mTcpServer->listen(QHostAddress::Any, 11111 ) && false == mServerStatus ) {
        qDebug() <<  QString("Невозможно запустить сервер: %1.").arg(mTcpServer->errorString() );
        mServerStatus = false;
    } else {
        qDebug() << "Сервер запущен!";
        qDebug() << "Прослушиваемый порт:" << mTcpServer->serverPort();
        qDebug() << "Количество доступных соединений:" << mTcpServer->maxPendingConnections();
        mServerStatus = true;
    }
}

/**
 * @brief TcpServer::slot_newConnection
 */
void TcpServer::slot_newConnection()
{
    if( false == mServerStatus )
        return;

    QTcpSocket *socket = mTcpServer->nextPendingConnection();
    if( socket ) {
        connect( socket, &QTcpSocket::readyRead, &TcpServer::slot_dataRead );
        connect( socket, &QTcpSocket::disconnected, &TcpServer::slot_clientDisconnect );
        connect( socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater );

        qDebug() << "Новый клиент:" << socket->peerAddress().toString();// << "\nОт:" << socket->localAddress().toString();
        emit signal_info( "Новый клиент: " + socket->peerAddress().toString() );
    }
}

/**
 * @brief TcpServer::slot_dataRead
 */
void TcpServer::slot_dataRead()
{
    QByteArray data = ((QTcpSocket*)sender())->readAll();
    emit signal_geodata( data );
}

/**
 * @brief TcpServer::slot_clientDisconnect
 */
void TcpServer::slot_clientDisconnect()
{
    qDebug() << "Клиент отсоединился:" << ((QTcpSocket*)sender())->peerAddress().toString();
    emit signal_info( "Клиент отсоединился: " + ((QTcpSocket*)sender())->peerAddress().toString() );
}
