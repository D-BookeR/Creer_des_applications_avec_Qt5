#include <QtWidgets/qframe.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlistview.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qtoolbar.h>
#include <QtWidgets/qinputdialog.h>
#include <QtWidgets/qlayout.h>

#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>

#include <Enginio/enginioclient.h>
#include <Enginio/enginioreply.h>

// To get the backend right, we use a helper class in the example.
// Usually one would just insert the backend information below.
#include "backendhelper.h"

#include "mainwindow.h"
#include "todosmodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("Enginio TODO example"));

    QPair<QByteArray, QByteArray> backendData = backendIdAndSecret("todo");
    QByteArray EnginioBackendId = backendData.first;
    QByteArray EnginioBackendSecret = backendData.second;

    //![client]
    m_client = new EnginioClient(this);
    m_client->setBackendId(EnginioBackendId);
    m_client->setBackendSecret(EnginioBackendSecret);
    //![client]

    QObject::connect(m_client, &EnginioClient::error, this, &MainWindow::error);

    //![model]
    m_model = new TodosModel(this);
    m_model->setEnginio(m_client);

    QJsonObject query;
    query["objectType"] = QString::fromUtf8("objects.todos");
    m_model->setQuery(query);
    //![model]

    QToolBar *toolBar = new QToolBar(this);
    m_addNewButton = new QPushButton(toolBar);
    m_addNewButton->setText("&Add");
    QObject::connect(m_addNewButton, &QPushButton::clicked, this, &MainWindow::appendItem);

    m_removeButton = new QPushButton(toolBar);
    m_removeButton->setText("&Remove");
    m_removeButton->setEnabled(false);
    QObject::connect(m_removeButton, &QPushButton::clicked, this, &MainWindow::removeItem);

    m_toggleButton = new QPushButton(toolBar);
    m_toggleButton->setText("&Toggle Completed");
    m_toggleButton->setEnabled(false);
    QObject::connect(m_toggleButton, &QPushButton::clicked, this, &MainWindow::toggleCompleted);

    toolBar->addWidget(m_addNewButton);
    toolBar->addWidget(m_removeButton);
    toolBar->addWidget(m_toggleButton);

    m_view = new QTreeView(this);
    m_view->setAlternatingRowColors(true);
    QFrame *frame = new QFrame(this);
    QVBoxLayout *windowLayout = new QVBoxLayout(frame);
    windowLayout->addWidget(m_view);
    windowLayout->addWidget(toolBar);
    setCentralWidget(frame);

    //![assignModel]
    m_view->setModel(m_model);
    //![assignModel]

    m_view->setSelectionModel(new QItemSelectionModel(m_model, m_model));
    QObject::connect(m_view->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::selectionChanged);
}

QSize MainWindow::sizeHint() const
{
    return QSize(400, 600);
}

void MainWindow::error(EnginioReply *error)
{
    qWarning() << Q_FUNC_INFO << error;
}

//![removeItem]
void MainWindow::removeItem()
{
    QModelIndex index = m_view->currentIndex();
    EnginioReply *reply = m_model->remove(index.row());
    QObject::connect(reply, &EnginioReply::finished, reply, &EnginioReply::deleteLater);
}
//![removeItem]

//![appendItem]
void MainWindow::appendItem()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Create a new To Do")
                                         , tr("Title:"), QLineEdit::Normal
                                         , "", &ok);
    if (ok && !text.isEmpty()){
        QJsonObject object;
        object["title"] = text;
        object["completed"] = false; // By default a new To Do is not completed
        EnginioReply *reply = m_model->append(object);
        QObject::connect(reply, &EnginioReply::finished, reply, &EnginioReply::deleteLater);
    }
}
//![appendItem]

void MainWindow::toggleCompleted()
{
    QModelIndex index = m_view->currentIndex();
    bool completed = m_model->data(index, m_model->CompletedRole).toBool();
    EnginioReply *reply = m_model->setProperty(index.row(), "completed", !completed);
    QObject::connect(reply, &EnginioReply::finished, reply, &EnginioReply::deleteLater);
}

void MainWindow::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);
    bool value = selected.count();
    m_removeButton->setEnabled(value);
    m_toggleButton->setEnabled(value);
}
