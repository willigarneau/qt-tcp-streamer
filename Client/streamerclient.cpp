#include "streamerclient.h"
#include "ui_streamerclient.h"
#include "streamerthread.h"

#include <QTime>

TheStreamerClient::TheStreamerClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TheStreamerClient)
{
    ui->setupUi(this);

    StreamerThread *thread = new StreamerThread(this);
    connect(thread, SIGNAL(signalNouvelleImage(QByteArray)), this, SLOT(slotNouvelleImage(QByteArray)));
    connect(this, SIGNAL(signalQuit()), thread, SLOT(slotQuit()));
    thread->start();
}

TheStreamerClient::~TheStreamerClient()
{
    emit(signalQuit());

    QTime dieTime = QTime::currentTime().addMSecs( 100 );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }

    delete ui;
}

void TheStreamerClient::slotNouvelleImage(QByteArray baImage)
{
    QPixmap pixImage;
    QImage image;

    if (!pixImage.loadFromData(baImage, "JPG"))
        return;
    image = pixImage.toImage();
    if (image.pixel(image.width() - 1, image.height() - 1 ) == 4286611584 &&
            image.pixel(image.width() / 2, image.height() - 1) == 4286611584  &&
            image.pixel(0, image.height() - 1) == 4286611584)
        return;

    ui->lblImage->setPixmap(pixImage);
}
