#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>

class QPushButton;
class EnginioClient;
class EnginioReply;
class TodosModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    virtual QSize sizeHint() const;

private slots:
    void error(EnginioReply *error);

    void removeItem();
    void appendItem();
    void toggleCompleted();
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

private:
    void queryTodos();

    // The Enginio client object used in all enginio operations
    EnginioClient *m_client;

    // Enginio object model containing todos objects
    TodosModel *m_model;

    // The list view showing contents of m_model
    QTreeView *m_view;

    QPushButton *m_addNewButton;
    QPushButton *m_removeButton;
    QPushButton *m_toggleButton;
};

#endif // MAINWINDOW_H
