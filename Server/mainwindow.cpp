// Video Player
// By William Garneau

#include "mainwindow.h"
#include "ui_mainwindow.h"

#pragma region AppBuilder


QSound sound("/home/administrateur/Bureau/VPlayer/sound/sintel_trailer-audio.wav");

// MainWindow Builder
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // UI Instanciation
    ui->setupUi(this);

    // Displaying the img and scaling for the label
    Display(_imgIndex);

    // Timer instanciation
    timer = new QTimer(this);

    // Connect object timer with method
    connect(timer, SIGNAL(timeout()), this, SLOT(Tick()));

    // Creating label for realtime clock
    clock = new QLabel();
    clock->setText("0 / 0");
    ui->sbTimer->addWidget(clock);

    // Adding TCP Server ressources
    server = new TCPServer();
    // Server-client
    connect(server, SIGNAL(Connect()), this, SLOT(on_clientConnection()));
    connect(server, SIGNAL(Disconnect()), this, SLOT(on_clientDisconnection()));
}
#pragma endregion AppBuilder;

#pragma region Events
// Function To Go FullScreen
void MainWindow::on_btnFS_clicked()
{
    if (!_isFullScreen) // If not on fullscreen
    {
        MainWindow::showFullScreen(); // Full Screen mode
    }
    else // If on full screen
    {
        MainWindow::showNormal(); // Put it off
    }
    _isFullScreen = !_isFullScreen; // Change the value of the var at the end
}

// Exit when btnQuit is clicked
void MainWindow::on_btnQuit_clicked()
{
    exit(0);
}

void MainWindow::Display(int index)
{
    // Convert img number to string (ex : 1 = 0001)
    QString noImg = convertIndex(index);

    // Var for time incrementation
    QString actualTime, totalTime;

    // Condition to put img on the label if the index is in file range
    if (index > 0 && index <= 1253)
    {
        QPixmap img = QPixmap("/home/administrateur/Bureau/VPlayer/img/sintel_trailer_" + noImg + ".jpg");
        ui->lblVideo->setPixmap(QPixmap(img).scaled(QSize(1280,720), Qt::KeepAspectRatio));
        QByteArray bImage;
        QBuffer bBuffer(&bImage);
        bBuffer.open(QIODevice::ReadWrite);
        img.save(&bBuffer, "jpg");
        server->is_newImg(bImage);

    }
    else
    {
        ui->lblVideo->setPixmap(QPixmap("/home/administrateur/Bureau/VPlayer/img/sintel-title.jpg").scaled(QSize(1280,720),Qt::KeepAspectRatio));
    }

    // Convert actual time to actual speed of the video
    actualTime = QString::number(index / (_speed * 24));
    // Change time to fit with speed
    totalTime = QString::number((1253 / (_speed * 24)) + 1);
    // Display realtime clock on form
    ui->sbTimer->showMessage(QString(actualTime + " / " + totalTime));
}

void MainWindow::Tick()
{
    _imgIndex++; // Index incrementation
    if (_imgIndex == 1254) // If the last file is about to be played
    {
        if (ui->ckLoop->isChecked() == false) // Check is we want to loop
        {
            _imgIndex = 0; // If we don't want to loop, stop the video
            Stop();
            Display(_imgIndex);
        }
        else // If we do, get back the img index at 1 and restart the video
        {
            _imgIndex = 1;
            sound.play();
        }
    }
    Display(_imgIndex); // Display the image corresponding to the index
    ui->slidVideo->setValue(_imgIndex); // Send back the value of the index to restart or continue
}

void MainWindow::tickManager(int speed)
{
    // Stopping the timer if it is still active
    if (timer->isActive())
        timer->stop();
    // If the video is on pause, stop the timer
    if (speed < 0 || _isPlaying == false)
        return;
    // If the video should play, start the timer at the right tick speed
    if (speed != 0)
    {
        timer->start(1000 / (24 * speed));
    }
}

// Follow the video progression and synchronize with the slider
void MainWindow::on_slidVideo_sliderMoved(int position)
{
    _imgIndex = position;
    Display(_imgIndex);
}

// When play button is clicked, start the video
void MainWindow::on_btnLecture_clicked()
{
    if (!_isPlaying)
        Play();
    else
        Stop();
}

// When changing the value of the speed
void MainWindow::on_spnVitesse_valueChanged(int arg1)
{
    _speed = arg1;
    tickManager(_speed);
}

// Function to start the video and tick
void MainWindow::Play()
{
    _isPlaying = true;
    ui->btnLecture->setText("Pause");
    sound.play();
    if (!timer->isActive())
    {
        tickManager(_speed);
    }
}
// Function to stop the video and tick
void MainWindow::Stop()
{
    _isPlaying = false;
    ui->btnLecture->setText("Lecture");
    sound.stop();
    if (timer->isActive())
    {
        timer->stop();
    }
}
// Convert the # of index to a string for searching in file
QString MainWindow::convertIndex(int index)
{ // Ex : 1 == "0001"
    if (index < 10)
        return "000" + QString::number(index);
    else
        if (index < 100)
            return "00" + QString::number(index);
        else
            if (index < 1000)
                return "0" + QString::number(index);
            else
                return QString::number(index);
}

// Display client count when connecting
void MainWindow::on_clientConnection()
{
    ui->lblClientCount->setText(QString::number(ui->lblClientCount->text().toInt()+1));
}
// Display client count when disconnecting
void MainWindow::on_clientDisconnection()
{
    ui->lblClientCount->setText(QString::number(ui->lblClientCount->text().toInt() -1));
}

#pragma endregion Events

#pragma region AppDestructor
MainWindow::~MainWindow()
{
    delete ui;
}
#pragma endregion AppDestructor
