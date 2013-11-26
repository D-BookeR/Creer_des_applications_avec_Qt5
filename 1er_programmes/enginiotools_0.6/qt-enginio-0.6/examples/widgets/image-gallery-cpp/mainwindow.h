#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QModelIndex>

class EnginioClient;
class ImageModel;
class EnginioReply;
class ImageDownloader;
class ImageObject;
class QFileDialog;
class QListView;
class QNetworkReply;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    virtual QSize sizeHint() const;

private slots:
    void queryImages();
    void error(EnginioReply *error);
    void beginUpload(EnginioReply *reply);
    void fileSelected(const QString &file);

private:
    // The Enginio client object used in all enginio operations
    EnginioClient *m_client;

    // Enginio object model containing image objects
    ImageModel *m_model;

    // The list view showing contents of m_model
    QListView *m_view;
    QPushButton *m_uploadButton;
    QFileDialog *m_fileDialog;
};

#endif // MAINWINDOW_H
