#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QMimeDatabase>
#include <QLabel>
#include <QElapsedTimer>

#include "dirdata.h"
#include "dirloader.h"

class QDir;
class QThread;
class QGraphicsView;
class QGraphicsScene;
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QString dirName, QWidget *parent = 0);
    ~MainWindow();

    void setFileProperties(const FileData *file);
    void setDirProperties(const DirData *file);

public slots:
    void slotDirContentLoaded(qint64 size);
    void slotLoadFinished(QString path);
    void slotOnQuit();

private:
    void createChartWidget();
    void createPropertiesWidget();

    QElapsedTimer               m_Timer;
    DirData                     m_DirData;
    QSharedPointer<DirLoader>   m_DirLoader;
    QLabel                      m_DirName;
    QLabel                      m_FileName;
    QLabel                      m_FileType;
    QThread                    *m_LoaderThread;
    QGraphicsView              *m_LoadingView;
    QGraphicsScene             *m_LoadingScene;
};

#endif // MAINWINDOW_H
