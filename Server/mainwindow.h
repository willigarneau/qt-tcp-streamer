#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Added library for Putting image in label
#include <QPixmap>
//Added library for time
#include <QTimer>
// Added libraby to debug program
#include <QDebug>
// Added library to manage strings
#include <string>
// Added library to listen the video
#include <QSound>
// Added library to control strings
#include <QLabel>
// Added library to convert TCP Server
#include <QTcpServer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_btnFS_clicked();

    void on_btnQuit_clicked();

    void Display(int index);

    void Tick();

    void Play();

    void Stop();

    void tickManager(int speed);

    void on_slidVideo_sliderMoved(int position);

    void on_btnLecture_clicked();

    void on_spnVitesse_valueChanged(int arg1);

    QString convertIndex(int index);

private:
    Ui::MainWindow *ui;

    // Member variables
    bool _isFullScreen = false;
    QTimer *timer;
    QLabel *clock;
    int _speed = 1;
    bool _isPlaying = false;
    int _imgIndex = 0;
};

#endif // MAINWINDOW_H
