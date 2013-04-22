#include <QApplication>
#include <QGraphicsView>

#include "fileitembasic.h"
#include "fileitemadvanced.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QGraphicsScene scene;
	QGraphicsView view(&scene);
    view.setMinimumSize(1024, 768);

    // FileItem sélectionnable et changeant de couleur à la séléction
    // Clique gauche pour sélectionner et clique droit pour désélectionner
    {
        FileItemBasic *item = new FileItemBasic();
        item->setFlag(QGraphicsItem::ItemIsSelectable);
        scene.addItem(item);
    }

    // FileItem pouvant être déplacé, faite un clique gauche
    // sur le fichier et déplacer le dans la scène
    {
        FileItemBasic *item = new FileItemBasic();
        item->setPos(150.0, 0.0);
        item->setFlag(QGraphicsItem::ItemIsMovable);
        scene.addItem(item);
    }

    // FileItem gérant le survol de la souris, un "+"
    // sera dessiné au survol de cet élément
    {
        FileItemBasic *item = new FileItemBasic();
        item->setPos(0.0, 150.0);
        item->setAcceptHoverEvents(true);
        scene.addItem(item);
    }

    // FileItem gérant le glissé/déposé sur lequel du
    // texte extérieur à l'application peut être ajouté
    {
        FileItemAdvanced *item = new FileItemAdvanced();
        item->setPos(150.0, 150.0);
        scene.addItem(item);
    }

    view.show();

	return a.exec();
}
