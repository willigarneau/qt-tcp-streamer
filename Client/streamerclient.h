#ifndef STREAMERCLIENT_H
#define STREAMERCLIENT_H

#include <QMainWindow>

namespace Ui {
class TheStreamerClient;
}

class TheStreamerClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit TheStreamerClient(QWidget *parent = 0);
    ~TheStreamerClient();

private:
    Ui::TheStreamerClient *ui;

private slots:
    void slotNouvelleImage(QByteArray baImage); // Slot appelé lors de la réception d'une nouvelle image.

signals:
    void signalQuit(); // Signal émis lors de la fermeture de l'application.
};

#endif // STREAMERCLIENT_H
