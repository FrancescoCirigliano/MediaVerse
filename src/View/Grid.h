#ifndef GRID_H
#define GRID_H
#include <QWidget>
#include <QListWidget>
#include "MediaRender/Card.h"

namespace View::ItemRender {

class Grid : public QWidget {
    Q_OBJECT
private:
    QListWidget* grid;
    View::ItemRender::Card* card;
public:
    explicit Grid(QWidget *parent = nullptr);
    void setupUI();
    void displayData(std::vector<const Media::AbstractMedia*>& collections);
public slots:
    void clickedItems(QListWidgetItem* item);
signals:
    void currentItems(QListWidgetItem* item);
    void doubleclick();
};

}

#endif // GRID_H
