
#include <Enginio/enginioclient.h>
#include <Enginio/enginioreply.h>

#include <QJsonDocument>
#include <QJsonArray>

#include <QCoreApplication>
#include <QSettings>
#include <QFile>

#include <QFormLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QTabWidget>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QLabel>
#include <QFileDialog>
#include <QListWidget>
#include <QGroupBox>

#include "mainwindow.h"


//@extract-start Qt-commun-premiers_programmes-enginio-construct-1-mainwindow-cpp
MainWindow::MainWindow(QWidget *parent)
  : QDialog(parent)
{
//@extract-end

//@extract-start Qt-commun-premiers_programmes-enginio-construct-2-mainwindow-cpp
  QCoreApplication::setOrganizationName("DBooker");
  QCoreApplication::setOrganizationDomain("www.d-booker.fr");
  QCoreApplication::setApplicationName("Enginio Toolbox");
//@extract-end

//@extract-start Qt-commun-premiers_programmes-enginio-construct-3-mainwindow-cpp
  QHBoxLayout *outerLayout = new QHBoxLayout(this);
  QWidget *mainWidget = new QWidget;
  QVBoxLayout *mainWidgetLayout = new QVBoxLayout(mainWidget);

  mainWidgetLayout->addWidget(createSetupWidget());

  QTabWidget *actionWidget = new QTabWidget;
  actionWidget->setDisabled(true);
  addExportPage(actionWidget);
  addImportPage(actionWidget);
  addRemovePage(actionWidget);
  mainWidgetLayout->addWidget(actionWidget);

  outerLayout->addWidget(mainWidget);
  outerLayout->addWidget(createLogWidget());
//@extract-end

//@extract-start Qt-commun-premiers_programmes-enginio-construct-4-mainwindow-cpp
  mainWidget->setMaximumWidth(400);
//@extract-end

//@extract-start Qt-commun-premiers_programmes-enginio-construct-5-mainwindow-cpp
  connect (m_objectType, &QLineEdit::textChanged,
           [=](const QString &text){
                actionWidget->setDisabled(text.isEmpty());
           });

  connect(m_importFileButton, &QPushButton::clicked, this, &MainWindow::onImportFile);
  connect(m_importButton, &QPushButton::clicked, this, &MainWindow::onImport);
  connect(m_exportFileButton, &QPushButton::clicked, this, &MainWindow::onExportFile);
  connect(m_exportButton, &QPushButton::clicked, this, &MainWindow::onExport);
  connect(m_removeButton, &QPushButton::clicked, this, &MainWindow::onRemove);
//@extract-end

//@extract-start Qt-commun-premiers_programmes-enginio-construct-6-mainwindow-cpp
  m_client = new EnginioClient(this);

  connect(m_client, &EnginioClient::error, this, &MainWindow::enginioError);
  connect(m_client, &EnginioClient::finished, this, &MainWindow::enginioFinished);
//@extract-end
}

//@extract-start Qt-commun-premiers_programmes-enginio-fin-mainwindow-cpp
MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent ( QCloseEvent * event )
{
  Q_UNUSED (event);

  QSettings settings;
  settings.setValue("mainBackendId", m_backendId->text());
}
//@extract-end

//@extract-start Qt-commun-premiers_programmes-enginio-createSetupWidget-mainwindow-cpp
QWidget *MainWindow::createSetupWidget()
{
  QWidget *w = new QWidget;
  QFormLayout  *layout = new QFormLayout(w);

  QSettings settings;

  m_backendId = new QLineEdit(settings.value("mainBackendId").toString(), this);
  layout->addRow(tr("Backend ID"), m_backendId);

  m_objectType = new QLineEdit;
  layout->addRow(tr("Object type"), m_objectType);

  return w;
}
//@extract-end

//@extract-start Qt-commun-premiers_programmes-enginio-createLogWidget-mainwindow-cpp
QWidget *MainWindow::createLogWidget()
{
  QGroupBox *box = new QGroupBox(QObject::tr("Log"));
  box->setFlat(true);
  QVBoxLayout  *layout = new QVBoxLayout(box);

  m_debugMode = new QCheckBox(tr("Debug mode"));
  layout->addWidget(m_debugMode);

  m_log = new QPlainTextEdit(box);
  m_log->setCenterOnScroll(true);
  m_log->setMaximumBlockCount(10000);
  layout->addWidget(m_log);

  return box;
}
//@extract-end

//@extract-start Qt-commun-premiers_programmes-enginio-createFilterWidget-mainwindow-cpp
void createFilterWidget(QPlainTextEdit **edit, QLayout  *layout)
{
  QGroupBox *box = new QGroupBox(QObject::tr("JSON filter"));
  box->setFlat(true);
  QVBoxLayout  *boxLayout = new QVBoxLayout(box);

  *edit = new QPlainTextEdit;

  boxLayout->addWidget(*edit);
  layout->addWidget(box);
}
//@extract-end

//@extract-start Qt-commun-premiers_programmes-enginio-createFileWidget-mainwindow-cpp
void createFileWidget(QPushButton **button, QLineEdit **edit, QLayout  *layout)
{
  QWidget *fileWidget = new QWidget;
  QHBoxLayout  *fileLayout = new QHBoxLayout(fileWidget);

  *button = new QPushButton(QObject::tr("File"));
  fileLayout->addWidget(*button);

  *edit =  new QLineEdit;
  fileLayout->addWidget(*edit);

  layout->addWidget(fileWidget);
}
//@extract-end

//@extract-start Qt-commun-premiers_programmes-enginio-addImportPage-mainwindow-cpp
void MainWindow::addImportPage(QTabWidget *tabWidget)
{
  QWidget *pageWidget = new QWidget;
  QVBoxLayout  *layout = new QVBoxLayout(pageWidget);

  createFileWidget(&m_importFileButton, &m_importFile, layout);

  m_importCreate = new QRadioButton(tr("Create"));
  m_importCreate->setChecked(true);
  layout->addWidget(m_importCreate);
  m_importUpdate = new QRadioButton(tr("Update"));
  layout->addWidget(m_importUpdate);

  m_importButton = new QPushButton(tr("Import"));
  layout->addWidget(m_importButton);

  tabWidget->addTab(pageWidget, tr("Import"));
}
//@extract-end

//@extract-start Qt-commun-premiers_programmes-enginio-addExportPage-mainwindow-cpp
void MainWindow::addExportPage(QTabWidget *tabWidget)
{
  QWidget *pageWidget = new QWidget;
  QVBoxLayout  *layout = new QVBoxLayout(pageWidget);

  createFilterWidget(&m_exportFilter, layout);
  createFileWidget(&m_exportFileButton, &m_exportFile, layout);

  m_exportButton = new QPushButton(tr("Export"));
  layout->addWidget(m_exportButton);

  tabWidget->addTab(pageWidget, tr("Export"));
}
//@extract-end

//@extract-start Qt-commun-premiers_programmes-enginio-addRemovePage-mainwindow-cpp
void MainWindow::addRemovePage(QTabWidget *tabWidget)
{
  QWidget *pageWidget = new QWidget;
  QVBoxLayout  *layout = new QVBoxLayout(pageWidget);

  createFilterWidget(&m_removeFilter, layout);

  m_removeButton = new QPushButton(tr("Remove"));
  layout->addWidget(m_removeButton);

  tabWidget->addTab(pageWidget, tr("Remove"));
}
//@extract-end

//@extract-start Qt-commun-premiers_programmes-enginio-log-mainwindow-cpp
void MainWindow::log(const QString &msg)
{
  m_log->appendHtml(QString("<p style='color:black'>%1</p>").arg(msg));
}
//@extract-end

//@extract-start Qt-commun-premiers_programmes-enginio-logError-mainwindow-cpp
void MainWindow::logError(const QString &error)
{
  m_log->appendHtml(QString("<p style='color:red'>%1</p>").arg(error));
}
//@extract-end

//@extract-start Qt-commun-premiers_programmes-enginio-logDebug-mainwindow-cpp
void MainWindow::logDebug(const QString &msg)
{
  if(m_debugMode->isChecked()) {
    m_log->appendHtml(QString("<p style='color:blue'>%1</p>").arg(msg));
  }
}
//@extract-end 

//@extract-start Qt-commun-premiers_programmes-enginio-enginioError-mainwindow-cpp
void MainWindow::enginioError(EnginioReply *error)
{
  logError(error->errorString());
}
//@extract-end 

//@extract-start Qt-commun-premiers_programmes-enginio-enginioFinished-mainwindow-cpp
void MainWindow::enginioFinished(EnginioReply *msg)
{
  if(msg->errorType() != Enginio::ErrorType::NoError) {
    return;
  }

  logDebug(QJsonDocument(msg->data()).toJson());

  if(msg == m_exportReply) {
    QJsonArray jsonArray(m_exportReply->data().value("results").toArray());
    QByteArray jsonText = QJsonDocument(jsonArray).toJson();
    QFile exportFile(m_exportFile->text());
    bool ok = exportFile.open(QIODevice::WriteOnly);
    if(ok) {
      exportFile.write(jsonText);
      log(tr("%1 object(s) exported to %2").arg(jsonArray.size()).arg(exportFile.fileName()));
    }
    else {
      logError(tr("Error %1 opening file %2").arg(exportFile.error()).arg(exportFile.fileName()));
    }
  }
//@extract-end 
//@extract-start Qt-commun-premiers_programmes-enginio-enginioFinished-2-mainwindow-cpp
  if(msg == m_queryForRemovalReply) {
    QJsonArray jsonArray(m_queryForRemovalReply->data().value("results").toArray());
    foreach(const QJsonValue &v, jsonArray) {
      QJsonObject removeObject(v.toObject());
      setObjectType(&removeObject);
      m_client->remove(removeObject);
    }
    log(tr("Request to remove %1 object(s)").arg(jsonArray.size()));
  }

  msg->deleteLater();
}
//@extract-end 

//@extract-start Qt-commun-premiers_programmes-enginio-onImportFile-mainwindow-cpp
void MainWindow::onImportFile()
{
  QString selectedFileName = QFileDialog::getOpenFileName();
  if (!selectedFileName.isNull()) {
      m_importFile->setText(selectedFileName);
  }
}
//@extract-end 

//@extract-start Qt-commun-premiers_programmes-enginio-onExportFile-mainwindow-cpp
void MainWindow::onExportFile()
{
  QString selectedFileName = QFileDialog::getSaveFileName();
  if (!selectedFileName.isNull()) {
      m_exportFile->setText(selectedFileName);
  }
}
//@extract-end 

//@extract-start Qt-commun-premiers_programmes-enginio-setClientBackend-mainwindow-cpp
void MainWindow::setClientBackend()
{
  m_client->setBackendId(m_backendId->text().toUtf8());
}
//@extract-end 

//@extract-start Qt-commun-premiers_programmes-enginio-setObjectType-mainwindow-cpp
void MainWindow::setObjectType(QJsonObject *o)
{
  QString objectType = m_objectType->text();

  QLatin1String objectPrefix("objects.");
  if(!objectType.startsWith(objectPrefix)) {
    objectType.prepend(objectPrefix);
  }
  o->insert("objectType", objectType);
}
//@extract-end 

//@extract-start Qt-commun-premiers_programmes-enginio-setObjectFilter-mainwindow-cpp
bool MainWindow::setObjectFilter(QJsonObject *o, const QString &filterText)
{
  if(!filterText.isEmpty()) {
    QJsonParseError parseError;
    QJsonDocument filter = QJsonDocument::fromJson(filterText.toUtf8(), &parseError);
    if(parseError.error != QJsonParseError::NoError) {
      logError(tr("Filter is not a JSON object: %1").arg(parseError.errorString()));
      return false;
    }
    o->insert("query", filter.object());
  }
  return true;
}
//@extract-end 

//@extract-start Qt-commun-premiers_programmes-enginio-onImport-mainwindow-cpp
void MainWindow::onImport()
{
  setClientBackend();

  QFile importFile(m_importFile->text());
  bool ok = importFile.open(QIODevice::ReadOnly);
  if(!ok) {
    logError(tr("Error %1 opening file %2").arg(importFile.error()).arg(importFile.fileName()));
    return;
  }
  QJsonParseError parseError;
  QJsonDocument jsonDoc = QJsonDocument::fromJson(importFile.readAll(), &parseError);
  if(parseError.error != QJsonParseError::NoError) {
    logError(parseError.errorString());
    return;
  }
//@extract-end 
//@extract-start Qt-commun-premiers_programmes-enginio-onImport-2-mainwindow-cpp
  QJsonArray jsonArray(jsonDoc.array());

  bool create = m_importCreate->isChecked();

  foreach(const QJsonValue &v, jsonArray) {
    if(v.isObject()) {
      QJsonObject object(v.toObject());
      setObjectType(&object);
      object.remove("createdAt");
      object.remove("updatedAt");
      if(create) {
        object.remove("id");
        m_client->create(object);
      }
      else {
        m_client->update(object);
      }
    }
  }

  log(create ? m_importCreate->text() : m_importUpdate->text());
  log(tr("Request to import %1 object(s)").arg(jsonArray.size()));
}
//@extract-end 

//@extract-start Qt-commun-premiers_programmes-enginio-onExport-mainwindow-cpp
void MainWindow::onExport()
{
  setClientBackend();

  QJsonObject queryObject;
  setObjectType(&queryObject);
  bool ok = setObjectFilter(&queryObject, m_exportFilter->toPlainText());
  if(!ok) {
    return;
  }

  m_exportReply = m_client->query(queryObject);
}
//@extract-end 

//@extract-start Qt-commun-premiers_programmes-enginio-onRemove-mainwindow-cpp
void MainWindow::onRemove()
{
  setClientBackend();

  QJsonObject queryObject;
  setObjectType(&queryObject);
  bool ok = setObjectFilter(&queryObject, m_removeFilter->toPlainText());
  if(!ok) {
    return;
  }

  m_queryForRemovalReply = m_client->query(queryObject);
}
//@extract-end 
