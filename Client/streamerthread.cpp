#include "streamerthread.h"

StreamerThread::StreamerThread(QObject *parent)
{
    m_quit = 0;
}

void StreamerThread::run()
{
}

void StreamerThread::slotQuit()
{
    m_quit = 1;
}
