#ifndef STREAMERTHREAD_H
#define STREAMERTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

class StreamerThread : public QThread
{
    Q_OBJECT

public:
    StreamerThread(QObject *parent);
    void run();
    QTcpSocket *socket;

private:
    QByteArray m_baImage; // Variable contenant l'image reçue.
    bool m_quit; // Variable permettant de savoir que l'application est en cours de fermeture.

private slots:
    void slotQuit(); // Slot appelé lors de la fermeture de l'application.

signals:
    void signalNouvelleImage(QByteArray baImage); // Signal émis lors de la réception d'une nouvelle image.

};

#endif // STREAMERTHREAD_H
