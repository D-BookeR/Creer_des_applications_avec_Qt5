#include <cmath>
#include <QDir>
#include <QGraphicsTextItem>
#include <QSplitter>
#include <QScrollBar>
#include <QDockWidget>
#include <QFormLayout>
#include <QMessageBox>
#include <QResizeEvent>
#include <QApplication>
#include <QThread>

#include "mainwindow.h"
#include "view.h"
#include "fileitem.h"
#include "diritem.h"

static void addDirTreeMap(QGraphicsScene *scene, DirData *d, QRectF bounds=QRect());
static void addSubDirs(QGraphicsScene *scene, DirData *d, QRectF bounds);
static void addDirFiles(DirItem *dirItem, QRectF bounds);

static void squarify(QVector<QRectF> &rects)
{
    QRectF currentLayer;
    int iStartLayer = 0;
    for (int i = 0; i < rects.size(); ++i) {
        if (currentLayer.isEmpty() || currentLayer.height() <= currentLayer.width()) {
            currentLayer = rects[i];
            iStartLayer = i;
        }
        else {
            qreal currentRatio, nextRatio = 1;
            if (currentLayer.width() != 0 && rects[i].width() != 0) {
                currentRatio = currentLayer.height() / currentLayer.width() / (i - iStartLayer);
                currentLayer.adjust(0, 0, rects[i].width(), 0);
                nextRatio = currentLayer.height() / currentLayer.width() / (1 + i - iStartLayer);
            }
            if (nextRatio != 0 && nextRatio < 1) {
                nextRatio = (1 / nextRatio);
            }
            if ((nextRatio > currentRatio) || (i == rects.size()-1)) {
                qreal x = currentLayer.x();
                qreal y = currentLayer.y();
                qreal w = currentLayer.width();
                for (int pos = iStartLayer; pos <= i; ++pos) {
                    QRectF rect = rects[pos];
                    qreal h = (rect.height() * rect.width()) / w;
                    rects.replace(pos, QRectF(x, y, w, h));
                    y += h;
                }
                currentLayer = QRect();
            }
        }
    }
}

MainWindow::MainWindow(QString dirName, QWidget *parent) :
    QMainWindow(parent)
{
    m_Timer.start();
    m_LoadingScene = new QGraphicsScene(this);
    m_LoadingView = new QGraphicsView(m_LoadingScene);
    setCentralWidget(m_LoadingView);
    m_LoaderThread = new QThread(this);
    DirLoader *pDirLoader = new DirLoader(&m_DirData, QDir(dirName).absolutePath());
    m_DirLoader = QSharedPointer<DirLoader>(pDirLoader);
    connect(m_LoaderThread, &QThread::started, pDirLoader, &DirLoader::load);
    connect(pDirLoader, &DirLoader::signalDirContentLoaded, this, &MainWindow::slotDirContentLoaded);
    connect(pDirLoader, &DirLoader::signalLoadFinished, this, &MainWindow::slotLoadFinished);
    m_DirLoader->moveToThread(m_LoaderThread);
    m_LoaderThread->start();
}

MainWindow::~MainWindow()
{}

void MainWindow::slotOnQuit()
{
    if (m_LoaderThread->isRunning()) {
        m_DirLoader->stop();
        m_LoaderThread->quit();
        m_LoaderThread->wait();
    }
}

void MainWindow::slotDirContentLoaded(qint64 size)
{
    if (size == 0) {
        return;
    }

    int s = sqrt((double)size);
    QRectF dirRect = QRectF(0, 0, s, s);
    QColor color = QColor::fromHsl(0, 0, qrand() % 255);
    m_LoadingScene->addRect(dirRect, QPen(), QBrush(color));
    m_LoadingScene->setBackgroundBrush(QBrush(color));

    qreal totalArea = (m_LoadingView->sceneRect().height() * m_LoadingView->sceneRect().width()) + size;
    QRectF contentsRect = QRectF(0, 0, sqrt(totalArea), sqrt(totalArea));
    qreal x = contentsRect.left();

    QVector<QRectF> dirRects;

    foreach (QGraphicsItem *item, m_LoadingScene->items()) {
        qreal itemArea = item->boundingRect().height() * item->boundingRect().width();
        qreal w = (itemArea * contentsRect.width()) / totalArea;
        dirRects.append(QRectF(x, contentsRect.top(), w, contentsRect.height()));
        x += w;
    }

    squarify(dirRects);

    int i = 0;
    foreach (QGraphicsItem *item, m_LoadingScene->items()) {
        QGraphicsRectItem *rectItem = dynamic_cast<QGraphicsRectItem *>(item);
        if (rectItem) {
            rectItem->setRect(dirRects.at(i++));
        }
    }

    m_LoadingView->fitInView(m_LoadingView->sceneRect(), Qt::KeepAspectRatio);

    setWindowTitle(tr("%1 - %2 directories").arg(m_DirData.name()).arg(m_LoadingScene->items().size()));
}

void MainWindow::slotLoadFinished(QString path)
{
    QGraphicsScene *dirTreeScene = new QGraphicsScene(this);
    addDirTreeMap(dirTreeScene, &m_DirData);
    View *view = new View(dirTreeScene);
    setCentralWidget(view);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    createChartWidget();
    createPropertiesWidget();

    connect(view, &View::dirChanged, this, &MainWindow::setDirProperties);
    connect(view, &View::fileChanged, this, &MainWindow::setFileProperties);

    delete m_LoadingView;
    delete m_LoadingScene;

    m_LoaderThread->quit();

    setWindowTitle(tr("%1 - %2 files - %3 ms").arg(path).arg(m_DirData.fileCount()).arg(m_Timer.elapsed()));
}

static void addDirTreeMap(QGraphicsScene *scene, DirData *d, QRectF bounds)
{
    qint64 dirSize = d->size();
    if (dirSize == 0) {
        return;
    }

    QRectF dirRect = bounds;
    if (dirRect.isNull()) {
        int s = sqrt((double)dirSize);
        dirRect = QRectF(0, 0, s, s);
    }

    DirItem *dirItem = new DirItem(d, dirRect);
    scene->addItem(dirItem);

    qint64 filesSize = d->filesSize();

    QRectF filesRect = dirRect;
    filesRect.setHeight((dirRect.height() * filesSize) / dirSize);
    addDirFiles(dirItem, filesRect);

    QRectF subDirRect = dirRect;
    subDirRect.setTop(filesRect.bottom());
    addSubDirs(scene, d, subDirRect);
}

void addDirFiles(DirItem *dirItem, QRectF bounds)
{
    const DirData *d = dirItem->dirData();
    QRectF filesRect = bounds;
    qreal deltaX = filesRect.width()/25;
    qreal deltaY = filesRect.height()/25;
    filesRect.adjust(deltaX, deltaY, -deltaX, -deltaY);

    qreal x = filesRect.left();
    qint64 filesSize = d->filesSize();

    QVector<QRectF> fileRects;

    foreach (const FileData &f, d->files()) {
        qreal w = (f.size() * filesRect.width()) / filesSize;
        fileRects.append(QRectF(x, filesRect.top(), w, filesRect.height()));
        x += w;
    }

    squarify(fileRects);

    int pos = 0;
    foreach (const FileData &f, d->files()) {
        new FileItem(&f, fileRects[pos++], dirItem);
    }
}

void addSubDirs(QGraphicsScene *scene, DirData *d, QRectF bounds)
{
    qint64 subDirsSize = d->size() - d->filesSize();
    if (subDirsSize == 0) {
        return;
    }
    qreal x = bounds.left();

    QVector<QRectF> subDirRects;

    foreach (DirData *subdir, d->subdirs()) {
        qreal w = (subdir->size() * bounds.width()) / subDirsSize;
        subDirRects.append(QRectF(x, bounds.top(), w, bounds.height()));
        x += w;
    }

    squarify(subDirRects);

    int pos = 0;
    foreach (DirData *subdir, d->subdirs()) {
        addDirTreeMap(scene, subdir, subDirRects[pos++]);
    }
}

static void addDirPieChart(QGraphicsScene *scene, DirData *d)
{
    qint64 totalSize = d->size();
    QMap<QString,qint64> sizes = d->typeSizes();

    if (totalSize == 0) {
        return;
    }

    QMultiMap<qint64, QString> sortedSizes;
    QMapIterator<QString, qint64> itSizes(sizes);
    while (itSizes.hasNext()) {
        itSizes.next();
        sortedSizes.insert(itSizes.value(), itSizes.key());
    }

    qreal pieSize = 300;
    QPointF center(pieSize / 2, pieSize / 2);
    qreal currentAngle = 0;
    int yPos = center.y() + (pieSize / 2) + 30;

    QMapIterator<qint64, QString> itSortedSizes(sortedSizes);
    itSortedSizes.toBack();
    while (itSortedSizes.hasPrevious()) {
        itSortedSizes.previous();

        qint64 typeSize = itSortedSizes.key();
        QString typeName = itSortedSizes.value();

        QGraphicsPathItem *slice = new QGraphicsPathItem();
        QPainterPath slicePath;
        qreal sliceAngle = (qreal)(360 * typeSize) / totalSize;
        slicePath.moveTo(center);
        slicePath.arcTo(center.x() - pieSize / 2, center.y() - pieSize / 2, pieSize, pieSize, currentAngle, sliceAngle);
        currentAngle += sliceAngle;
        slice->setPath(slicePath);

        QBrush brush(Qt::SolidPattern);
        brush.setColor(FileItem::colorFromType(typeName));
        scene->addPath(slicePath, QPen(), brush);

        double typePercentage = ((double)typeSize * 100) / totalSize;
        QString legendText = QString("%1% \t%2").arg(typePercentage, 0, 'g', 2).arg(typeName);
        QGraphicsTextItem * text = scene->addText(legendText);
        text->setPos(text->boundingRect().height() + 10, yPos);

        int rectSize = text->boundingRect().height();
        QRect typeRect(text->x() - rectSize - 5, text->y(), rectSize, rectSize);
        scene->addRect(typeRect, QPen(), brush);

        yPos += 40;
    }

    scene->setSceneRect(scene->itemsBoundingRect().adjusted(-10, -10, 10, 10));
}

void MainWindow::createChartWidget()
{
    QGraphicsScene* scene = new QGraphicsScene(this);
    addDirPieChart(scene, &m_DirData);

    QGraphicsView* dirChartView = new QGraphicsView(scene);
    dirChartView->verticalScrollBar()->setValue(dirChartView->verticalScrollBar()->minimum());
    dirChartView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    dirChartView->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    QDockWidget* chartDock = new QDockWidget(tr("MIME types"), this);
    chartDock->setFeatures(QDockWidget::DockWidgetFloatable);
    chartDock->setWidget(dirChartView);
    addDockWidget(Qt::RightDockWidgetArea, chartDock);
}

void MainWindow::createPropertiesWidget()
{
    QWidget *content = new QWidget;
    QFormLayout* layout = new QFormLayout;
    layout->addRow(tr("Directory"), &m_DirName);
    layout->addRow(tr("File"), &m_FileName);
    layout->addRow(tr("MIME Type"), &m_FileType);
    content->setLayout(layout);

    QDockWidget* propertiesWidget = new QDockWidget(tr("Properties"), this);
    propertiesWidget->setFeatures(QDockWidget::DockWidgetFloatable);
    propertiesWidget->setWidget(content);
    addDockWidget(Qt::BottomDockWidgetArea, propertiesWidget);
}

static void setElidedText(QLabel *label, QString text)
{
    QFontMetrics metrics(label->font());
    QString elidedText = metrics.elidedText(text, Qt::ElideMiddle, label->width());
    label->setText(elidedText);
}

void MainWindow::setFileProperties(const FileData *file)
{
    setElidedText(&m_FileName, file ? file->name() : "");
    setElidedText(&m_FileType, file ? file->name() : "");
}

void MainWindow::setDirProperties(const DirData *dir)
{
    setElidedText(&m_DirName, dir ? dir->path() : "");
}
