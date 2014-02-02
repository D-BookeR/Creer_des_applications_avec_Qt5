#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QPointer>

class QComboBox;
class QPushButton;
class QLineEdit;
class QPlainTextEdit;
class QTabWidget;
class QListWidget;
class QFormLayout;
class QCheckBox;
class QRadioButton;
class EnginioClient;
class EnginioReply;
class QJsonObject;

class MainWindow : public QDialog
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

protected:
  virtual void	closeEvent ( QCloseEvent * event );

private:

  QLineEdit       *m_backendId;
  QLineEdit       *m_objectType;
  QPushButton     *m_objectTypeTest;
  QPushButton     *m_importFileButton;
  QLineEdit       *m_importFile;
  QRadioButton    *m_importCreate;
  QRadioButton    *m_importUpdate;
  QPushButton     *m_importButton;
  QPushButton     *m_exportFileButton;
  QLineEdit       *m_exportFile;
  QPlainTextEdit  *m_exportFilter;
  QPushButton     *m_exportButton;
  QPlainTextEdit  *m_removeFilter;
  QPushButton     *m_removeButton;
  QCheckBox       *m_debugMode;
  QPlainTextEdit  *m_log;

  EnginioClient *m_client;
  QPointer<EnginioReply> m_exportReply;
  QPointer<EnginioReply> m_queryForRemovalReply;

  void log(const QString &msg);
  void logError(const QString &error);
  void logDebug(const QString &msg);
  void enginioError(EnginioReply *enginioError);
  void enginioFinished(EnginioReply *msg);

  void setClientBackend();
  void setObjectType(QJsonObject *o);
  bool setObjectFilter(QJsonObject *o, const QString &filterText);

  QWidget *createSetupWidget();
  QWidget *createLogWidget();
  void addImportPage(QTabWidget *tabWidget);
  void addExportPage(QTabWidget *tabWidget);
  void addRemovePage(QTabWidget *tabWidget);

private slots:
  void onImportFile();
  void onExportFile();
  void onImport();
  void onExport();
  void onRemove();
};

#endif // MAINWINDOW_H
