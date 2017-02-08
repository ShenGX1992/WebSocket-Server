#ifndef TRANSFERSERVER_H
#define TRANSFERSERVER_H

#include <QDialog>
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>
#include <QKeyEvent>
#include <QThread>
#include <QTimer>
#include <cmath>
#include <QDebug>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QWebSocketServer>
#include <QWebSocket>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

namespace Ui {
class TransferServer;
}

class TransferServer : public QDialog
{
    Q_OBJECT

public:
    explicit TransferServer(QWidget *parent = 0);
    ~TransferServer();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

    void on_pushButton_open_clicked();

    void on_pushButton_close_clicked();

    void on_pushButton_quit_clicked();

private:
    Ui::TransferServer *ui;
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
};

#endif // TRANSFERSERVER_H
