#include "transferserver.h"
#include "ui_transferserver.h"

TransferServer::TransferServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransferServer)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    move((QApplication::desktop()->width() - width()) / 4,
         (QApplication::desktop()->height() - height()) / 4);
}

TransferServer::~TransferServer()
{
    delete ui;
}

void TransferServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &TransferServer::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &TransferServer::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &TransferServer::socketDisconnected);

    m_clients << pSocket;
}

void TransferServer::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
        qDebug() << "Message received:" << message;
        QString PROstring = "Message received:";
        PROstring.append(message);
        ui->listWidget->addItem(PROstring);
    if (pClient) {
        pClient->sendTextMessage("i have receive");
    }
}

void TransferServer::processBinaryMessage(QByteArray message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
        qDebug() << "Binary Message received:" << message;
    if (pClient) {
        pClient->sendBinaryMessage(message);
    }
}

void TransferServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
        qDebug() << "socketDisconnected:" << pClient;
        QString DISstring = "socketDisconnected";
        ui->listWidget->addItem(DISstring);
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}

void TransferServer::on_pushButton_open_clicked()
{
    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("TransferServer"),QWebSocketServer::NonSecureMode, this);
    if (m_pWebSocketServer->listen(QHostAddress::Any, 1234))
    {
            qDebug() << "TransferServer listening on port：1234";
            ui->listWidget->addItem("TransferServer listening on port：1234");
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &TransferServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &TransferServer::closed);
    }
}

void TransferServer::on_pushButton_close_clicked()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
    ui->listWidget->addItem("Server Closed");
}

void TransferServer::on_pushButton_quit_clicked()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
    close();
}
