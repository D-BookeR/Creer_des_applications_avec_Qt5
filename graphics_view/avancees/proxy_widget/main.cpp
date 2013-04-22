#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QStyleOptionButton>
#include <QTextEdit>
#include <QWebView>

class GraphicsButtonItem: public QGraphicsRectItem
{
public:
    GraphicsButtonItem(qreal x1, qreal y1, qreal w, qreal h) :
        QGraphicsRectItem(x1, y1, w, h),
        m_pressed(false)
    {
     this->setAcceptHoverEvents(true);
    }

void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QStyleOptionButton buttonStyle;
    buttonStyle.palette = option->palette;
    buttonStyle.rect = option->rect;
    buttonStyle.state = option->state;
    buttonStyle.text = "PushButton";

    if (m_pressed) {
        buttonStyle.state |= QStyle::State_Sunken;
    }

    QStyle *style = qApp->style();
    style->drawControl(QStyle::CE_PushButton, &buttonStyle, painter, widget);
}

void mousePressEvent(QGraphicsSceneMouseEvent *)
{
    m_pressed = true;
    update();
}

void mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    m_pressed = false;
    update();
}

private:
    bool m_pressed;
};

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QGraphicsScene scene;
	QGraphicsView view(&scene);
    view.setMinimumSize(1024, 768);

    GraphicsButtonItem *buttonItem = new GraphicsButtonItem(0.0, -100.0, 100.0, 50.0);
    scene.addItem(buttonItem);

    QTabWidget *tabWidget = new QTabWidget();
    QWebView *webView = new QWebView();
    QTextEdit *edit = new QTextEdit();
    webView->setUrl(QUrl("http://qt-project.org"));
    edit->setPlainText("Et voilà !\nLe QTextEdit est embarqué dans la scène");
    tabWidget->addTab(webView, "QWebView Tab");
    tabWidget->addTab(edit, "QTextEdit Tab");
    scene.addWidget(tabWidget);

	view.show();

	return a.exec();
}
