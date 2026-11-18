#include "Grid.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

namespace View::ItemRender {

Grid::Grid(QWidget *parent): QWidget{parent} {
    setupUI();
    card = new View::ItemRender::Card();
}

void Grid::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    this->setLayout(mainLayout);

    grid = new QListWidget();
    grid->setViewMode(QListView::IconMode);
    grid->setFlow(QListView::LeftToRight);
    grid->setWrapping(true);
    grid->setResizeMode(QListView::Adjust);
    grid->setSpacing(10);
    grid->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(grid, &QListWidget::itemClicked, this, &Grid::clickedItems);
    connect(grid, &QListWidget::doubleClicked, this, &Grid::doubleclick);
    mainLayout->addWidget(grid, 1);

}

void Grid::displayData(std::vector<const Media::AbstractMedia *> &collections) {
    for(std::vector<const Media::AbstractMedia*>::const_iterator it = collections.begin();
        it != collections.end();
        it++
        )
    {
        (*it)->accept(*card);
        QWidget* itemWidget = card->getWidget();
        QListWidgetItem* item = new QListWidgetItem(grid);
        item->setSizeHint(itemWidget->minimumSize());
        Media::AbstractMedia* itemPtr = const_cast<Media::AbstractMedia*>(static_cast<const Media::AbstractMedia*>(*it));
        item->setData(Qt::UserRole, QVariant::fromValue(itemPtr));
        grid->setItemWidget(item, itemWidget);
    }

}

void Grid::clickedItems(QListWidgetItem* item) {
    if(!item) {
        return;
    }
    emit currentItems(item);
}

}
