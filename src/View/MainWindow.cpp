#include "MainWindow.h"
#include "EditWidget.h"
#include "../Controller/Controller.h"
#include "MediaRender/Full.h"
#include "Grid.h"

#include <QAction>
#include <QToolBar>
#include <vector>
#include <QPixmap>
#include <QMenu>
#include <QMenuBar>
#include <QIcon>
#include <QFileDialog>
#include <QMessageBox>

namespace View {

MainWindow::MainWindow(QWidget *parent): QMainWindow{parent} {
    controller = new Controller::Controller(this);

    setupHeader();

    setupSidebar();

    setupUI();

    loadStyleSheet();

    card = new View::ItemRender::Card();
}

void MainWindow::setupUI() {
    stackedWidget = new QStackedWidget();
    centralWidget = new QWidget();
    this->setCentralWidget(stackedWidget);

    QVBoxLayout* mainContentLayout = new QVBoxLayout(centralWidget);
    mainContentLayout->setSpacing(20);
    mainContentLayout->setContentsMargins(0, 0, 0, 0);

    QLabel* booksTitle = new QLabel("Recently added books:");
    booksTitle->setObjectName("SectionTitle");
    booklistView = new QListWidget();

    booklistView->setViewMode(QListView::IconMode);
    booklistView->setFlow(QListView::LeftToRight);
    booklistView->setWrapping(true);
    booklistView->setResizeMode(QListView::Adjust);
    booklistView->setMovement(QListView::Static);
    booklistView->setSpacing(10);
    booklistView->setMinimumHeight(220);

    connect(booklistView, &QListWidget::itemClicked, this, &MainWindow::clickedCard);
    connect(booklistView, &QListWidget::doubleClicked, this, &MainWindow::doubleClickedCard);

    mainContentLayout->addWidget(booksTitle);
    mainContentLayout->addWidget(booklistView);

    QLabel* filmsTitle = new QLabel("Recently added movies:");
    filmsTitle->setObjectName("SectionTitle");
    filmlistView = new QListWidget();

    filmlistView->setViewMode(QListView::IconMode);
    filmlistView->setFlow(QListView::LeftToRight);
    filmlistView->setWrapping(true);
    filmlistView->setResizeMode(QListView::Adjust);
    filmlistView->setMovement(QListView::Static);
    filmlistView->setSpacing(10);
    filmlistView->setMinimumHeight(220);

    connect(filmlistView, &QListWidget::itemClicked, this, &MainWindow::clickedCard);
    connect(filmlistView, &QListWidget::doubleClicked, this, &MainWindow::doubleClickedCard);

    mainContentLayout->addWidget(filmsTitle);
    mainContentLayout->addWidget(filmlistView);

    QLabel* songsTitle = new QLabel("Recently added songs:");
    songsTitle->setObjectName("SectionTitle");
    songlistView = new QListWidget();

    songlistView->setViewMode(QListView::IconMode);
    songlistView->setFlow(QListView::LeftToRight);
    songlistView->setWrapping(true);
    songlistView->setResizeMode(QListView::Adjust);
    songlistView->setMovement(QListView::Static);
    songlistView->setSpacing(10);
    songlistView->setMinimumHeight(220);

    connect(songlistView, &QListWidget::itemClicked, this, &MainWindow::clickedCard);
    connect(songlistView, &QListWidget::doubleClicked, this, &MainWindow::doubleClickedCard);

    mainContentLayout->addWidget(songsTitle);
    mainContentLayout->addWidget(songlistView);

    mainContentLayout->addStretch();
    stackedWidget->addWidget(centralWidget);

}

void MainWindow::setupSidebar() {
    QToolBar* sidebar = addToolBar("Sidebar");
    sidebar->setObjectName("Sidebar");
    sidebar->setMovable(false);
    sidebar->setOrientation(Qt::Vertical);
    addToolBar(Qt::LeftToolBarArea, sidebar);

    QIcon homeButtonIcon(":/assets/icon/house-solid.svg");
    homeButton = new QPushButton("Home");
    homeButton->setIcon(homeButtonIcon);
    homeButton->setObjectName("CategoryButton");
    homeButton->setProperty("active", true);
    sidebar->addWidget(homeButton);

    QIcon booksButtonIcon(":/assets/icon/book-solid.svg");
    booksButton = new QPushButton("Books");
    booksButton->setIcon(booksButtonIcon);
    booksButton->setObjectName("CategoryButton");
    sidebar->addWidget(booksButton);

    QIcon filmsButtonIcon(":/assets/icon/film-solid.svg");
    filmsButton = new QPushButton("Films");
    filmsButton->setIcon(filmsButtonIcon);
    filmsButton->setObjectName("CategoryButton");
    sidebar->addWidget(filmsButton);

    QIcon songsButtonIcon(":/assets/icon/music-solid.svg");
    songsButton = new QPushButton("Songs");
    songsButton->setIcon(songsButtonIcon);
    songsButton->setObjectName("CategoryButton");
    sidebar->addWidget(songsButton);

    connect(homeButton, &QPushButton::clicked, this, &MainWindow::homeButtonClicked);
    connect(booksButton, &QPushButton::clicked, this, &MainWindow::bookButtonClicked);
    connect(filmsButton, &QPushButton::clicked, this, &MainWindow::filmButtonClicked);
    connect(songsButton, &QPushButton::clicked, this, &MainWindow::songButtonClicked);
}

void MainWindow::setupHeader() {
    QToolBar* header = addToolBar("Header");
    header->setObjectName("HeaderBar");
    header->setMovable(false);

    QPixmap pixmap(":/assets/image/logo.png");
    QLabel* logoLabel = new QLabel();
    logoLabel->setPixmap(pixmap.scaledToHeight(35, Qt::SmoothTransformation));

    header->addWidget(logoLabel);

    QWidget* logoButtonSpacer = new QWidget();
    logoButtonSpacer->setFixedWidth(120);
    header->addWidget(logoButtonSpacer);

    QIcon addButtonIcon(":/assets/icon/plus-solid.svg");
    addButton = new QPushButton("");
    addButton->setIcon(addButtonIcon);
    addButton->setObjectName("AddButton");
    addAction = header->addWidget(addButton);
    addButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    addButton->setToolTip("Create new Item");

    QIcon saveNewButtonIcon(":/assets/icon/save_new.svg");
    saveNewButton = new QPushButton("");
    saveNewButton->setIcon(saveNewButtonIcon);
    saveNewButton->setObjectName("SaveButton");
    saveNewAction = header->addWidget(saveNewButton);
    saveNewButton->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));
    saveNewButton->setToolTip("Save As");

    QIcon saveButtonIcon(":/assets/icon/floppy-disk-solid.svg");
    saveButton = new QPushButton("");
    saveButton->setIcon(saveButtonIcon);
    saveButton->setObjectName("SaveButton");
    saveAction = header->addWidget(saveButton);
    saveButton->setEnabled(false);
    saveButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    saveButton->setToolTip("Save");

    QIcon importButtonIcon(":/assets/icon/file-import-solid.svg");
    importButton = new QPushButton("");
    importButton->setIcon(importButtonIcon);
    importButton->setObjectName("ImportButton");
    importAction = header->addWidget(importButton);
    importButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    importButton->setToolTip("Import");

    QIcon newDatasetButtonIcon(":/assets/icon/file-solid.svg");
    newDatasetButton = new QPushButton("");
    newDatasetButton->setIcon(newDatasetButtonIcon);
    newDatasetButton->setObjectName("ImportButton");
    newDatasetButtonAction = header->addWidget(newDatasetButton);
    newDatasetButton->setEnabled(false);
    newDatasetButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    newDatasetButton->setToolTip("Import New Dataset");

    QIcon editButtonIcon(":/assets/icon/pencil-solid.svg");
    editButton = new QPushButton("");
    editButton->setIcon(editButtonIcon);
    editButton->setObjectName("EditButton");
    editAction = header->addWidget(editButton);
    editButton->setEnabled(false);
    editButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_E));
    editButton->setToolTip("Edit Item");

    QIcon deleteButtonIcon(":/assets/icon/trash-can-solid.svg");
    deleteButton = new QPushButton("");
    deleteButton->setIcon(deleteButtonIcon);
    deleteButton->setObjectName("DeleteButton");
    deleteAction = header->addWidget(deleteButton);
    deleteButton->setEnabled(false);
    deleteButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_R));
    deleteButton->setToolTip("Delete Item");

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    header->addWidget(spacer);

    searchLineEdit = new QLineEdit();
    searchLineEdit->setObjectName("SearchBox");
    searchLineEdit->setPlaceholderText("Typer for start to search");
    searchLineEdit->setFixedWidth(250);

    searchModel = new QStandardItemModel(this);

    searchCompleter = new QCompleter(searchModel, this);
    searchCompleter->setObjectName("SearchCompleter");
    searchCompleter->popup()->setObjectName("SearchPopup");
    searchCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    searchCompleter->setFilterMode(Qt::MatchContains);
    searchCompleter->setCompletionMode(QCompleter::PopupCompletion);
    searchLineEdit->setCompleter(searchCompleter);

    connect(searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::searchTextChanged);
    header->addWidget(searchLineEdit);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::createItem);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::save);
    connect(saveNewButton, &QPushButton::clicked, this, &MainWindow::saveAs);
    connect(importButton, &QPushButton::clicked, this, &MainWindow::load);
    connect(newDatasetButton, &QPushButton::clicked, this, &MainWindow::closeDataset);
    connect(editButton, &QPushButton::clicked, this, &MainWindow::editItem);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteItem);
    connect(searchCompleter, QOverload<const QModelIndex &>::of(&QCompleter::activated), this, &MainWindow::qCompleterClicked);

    connect(searchLineEdit, &QLineEdit::returnPressed, this, &MainWindow::SearchReturnPressed);
}

void MainWindow::createItem() {
    controller->requestCreateNewItem();
}

void MainWindow::saveAs() {
    QString path = QFileDialog::getSaveFileName(
                this,
                "Create new Dataset",
                "./",
                "JSON files *.json"
                );
    controller->requestSaveAs(path.toStdString());
}

void MainWindow::save() {
    controller->requestSave();
}

void MainWindow::load() {
    QString path;
    if(saved == false) {
        QMessageBox unsavedFile;
        unsavedFile.setText("There are unsaved changes, if you upload a new file these will be lost. Do you want to save them before proceeding?");
        unsavedFile.setInformativeText("Do you want save your changes?");
        unsavedFile.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel );
        unsavedFile.setDefaultButton(QMessageBox::Yes);
        int choise = unsavedFile.exec();
        switch(choise) {
            case QMessageBox::Yes:
                save();
                path = QFileDialog::getOpenFileName(
                            this,
                            "Create new Dataset",
                            "./",
                            "JSON files *.json"
                            );
                controller->requestLoad(path.toStdString());
                setButton();
            break;
        case QMessageBox::No:
                path = QFileDialog::getOpenFileName(
                            this,
                            "Create new Dataset",
                            "./",
                            "JSON files *.json"
                            );
                controller->requestLoad(path.toStdString());
                setButton();
            break;
        }
    } else {
        path = QFileDialog::getOpenFileName(
                    this,
                    "Create new Dataset",
                    "./",
                    "JSON files *.json"
                    );
        controller->requestLoad(path.toStdString());
        setButton();
    }
}

void MainWindow::displayMedia(std::vector<const Media::AbstractMedia*>& booklist, std::vector<const Media::AbstractMedia*>& filmlist, std::vector<const Media::AbstractMedia*>& songlist) {
    booklistView->clear();
    filmlistView->clear();
    songlistView->clear();

    unsigned int cout = 0;
    for(std::vector<const Media::AbstractMedia*>::const_reverse_iterator it = booklist.rbegin();
        it != booklist.rend() && cout < max_media;
        it++
        )
    {
        (*it)->accept(*card);
        QWidget* itemWidget = card->getWidget();
        QListWidgetItem* item = new QListWidgetItem(booklistView);
        item->setSizeHint(itemWidget->minimumSize());
        const Media::AbstractMedia* itemPtr = *it;
        item->setData(Qt::UserRole, QVariant::fromValue(itemPtr));
        booklistView->setItemWidget(item, itemWidget);
        cout++;
    }

    cout = 0;
    for(std::vector<const Media::AbstractMedia*>::const_reverse_iterator it = filmlist.rbegin();
        it != filmlist.rend() && cout < max_media;
        it++
        )
    {
        (*it)->accept(*card);
        QWidget* itemWidget = card->getWidget();
        QListWidgetItem* item = new QListWidgetItem(filmlistView);
        item->setSizeHint(itemWidget->minimumSize());
        const Media::AbstractMedia* itemPtr = (*it);
        item->setData(Qt::UserRole, QVariant::fromValue(itemPtr));
        filmlistView->setItemWidget(item, itemWidget);
        cout++;
    }
    cout = 0;
    for(std::vector<const Media::AbstractMedia*>::const_reverse_iterator it = songlist.rbegin();
        it != songlist.rend() && cout < max_media;
        it++
        )
    {
        (*it)->accept(*card);
        QWidget* itemWidget = card->getWidget();
        QListWidgetItem* item = new QListWidgetItem(songlistView);
        item->setSizeHint(itemWidget->minimumSize());
        const Media::AbstractMedia* itemPtr = (*it);
        item->setData(Qt::UserRole, QVariant::fromValue(itemPtr));
        songlistView->setItemWidget(item, itemWidget);
        cout++;
    }
}

void MainWindow::loadStyleSheet() {
    QFile file(":/assets/styles/style.qss");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
         qWarning("Styleshet not applied");
    }

    QString styleSheet = QLatin1String(file.readAll());
    file.close();
    this->setStyleSheet(styleSheet);

    if(searchCompleter)
        searchCompleter->popup()->setStyleSheet(styleSheet);
}

void MainWindow::editItem() {
    if(subject == nullptr)
        return;
    controller->requestEditItem(subject);
}

void MainWindow::deleteItem() {
    if(subject==nullptr){
        return;
    }
    controller->requestRemoveItem(subject);
}

void MainWindow::homeButtonClicked() {
    currentView = 0;
    stackedWidget->setCurrentWidget(centralWidget);
    homeButton->setProperty("active", true);
    booksButton->setProperty("active", false);
    filmsButton->setProperty("active", false);
    songsButton->setProperty("active", false);
    refreshButtonStyle();
    setButtonVisibility(true);
}

void MainWindow::bookButtonClicked() {
    if(stackedWidget->indexOf(filteredBookView) == -1) {
        return;
    }
    currentView = 1;
    stackedWidget->setCurrentWidget(filteredBookView);
    booksButton->setProperty("active", true);
    homeButton->setProperty("active", false);
    filmsButton->setProperty("active", false);
    songsButton->setProperty("active", false);
    refreshButtonStyle();
    setButtonVisibility(true);
}

void MainWindow::filmButtonClicked() {
    if(stackedWidget->indexOf(filteredFilmView) == -1) {
        return;
    }
    currentView = 2;
    stackedWidget->setCurrentWidget(filteredFilmView);
    filmsButton->setProperty("active", true);
    homeButton->setProperty("active", false);
    booksButton->setProperty("active", false);
    songsButton->setProperty("active", false);
    refreshButtonStyle();
    setButtonVisibility(true);
}

void MainWindow::songButtonClicked() {
    if(stackedWidget->indexOf(filteredSongView) == -1) {
        return;
    }
    currentView = 3;
    stackedWidget->setCurrentWidget(filteredSongView);
    songsButton->setProperty("active", true);
    homeButton->setProperty("active", false);
    booksButton->setProperty("active", false);
    filmsButton->setProperty("active", false);
    refreshButtonStyle();
    setButtonVisibility(true);
}

void MainWindow::setBookView(View::ItemRender::Grid *view) {
    if(filteredBookView){
        stackedWidget->removeWidget(filteredSongView);
        delete filteredBookView;
    }
    filteredBookView = view;
    stackedWidget->addWidget(filteredBookView);
    if(currentView == 1) {
        stackedWidget->setCurrentWidget(filteredBookView);
    }
    connect(filteredBookView, &View::ItemRender::Grid::currentItems, this, &MainWindow::clickedCard);
    connect(filteredBookView, &View::ItemRender::Grid::doubleclick, this, &MainWindow::doubleClickedCard);
}

void MainWindow::setFilmView(View::ItemRender::Grid *view) {
    if(filteredFilmView){
        stackedWidget->removeWidget(filteredFilmView);
        delete filteredFilmView;
    }
    filteredFilmView = view;
    stackedWidget->addWidget(filteredFilmView);
    if(currentView == 2) {
        stackedWidget->setCurrentWidget(filteredFilmView);
    }
    connect(filteredFilmView, &View::ItemRender::Grid::currentItems, this, &MainWindow::clickedCard);
    connect(filteredFilmView, &View::ItemRender::Grid::doubleclick, this, &MainWindow::doubleClickedCard);
}

void MainWindow::setSongView(View::ItemRender::Grid *view) {
    if(filteredSongView){
        stackedWidget->removeWidget(filteredSongView);
        delete filteredSongView;
    }
    filteredSongView = view;
    stackedWidget->addWidget(filteredSongView);
    if(currentView == 3) {
        stackedWidget->setCurrentWidget(filteredSongView);
    }
    connect(filteredSongView, &View::ItemRender::Grid::currentItems, this, &MainWindow::clickedCard);
    connect(filteredSongView, &View::ItemRender::Grid::doubleclick, this, &MainWindow::doubleClickedCard);
}


void MainWindow::clickedCard(QListWidgetItem* item) {
    if(!item) {
        return;
        qDebug() << "No item";
    }

    QListWidget* listSender = item->listWidget();
    if(listSender == booklistView) {
        filmlistView->clearSelection();
        songlistView->clearSelection();
    } else if(listSender == filmlistView) {
        booklistView->clearSelection();
        songlistView->clearSelection();
    } else if(listSender == songlistView) {
        booklistView->clearSelection();
        filmlistView->clearSelection();
    }

    const Media::AbstractMedia* itemPtr = item->data(Qt::UserRole).value<const Media::AbstractMedia*>();
    if(itemPtr) {
        subject = itemPtr;
    }
    else
        return;
}

void MainWindow::searchTextChanged(const QString& text) {
    searchModel->clear();

    if(text.isEmpty()){
        return;
    }

    std::vector<const Media::AbstractMedia*> results;
    controller->search(results, text.toStdString());
    for(std::vector<const Media::AbstractMedia*>::const_iterator it = results.begin();
        it != results.end();
        it++)
    {
        QStandardItem* item = new QStandardItem();
        item->setData(QString::fromStdString((*it)->getTitle()), Qt::DisplayRole);
        item->setData(QVariant::fromValue(*it), Qt::UserRole);
        searchModel->appendRow(item);
    }
}

void MainWindow::refreshButtonStyle() {
    style()->unpolish(homeButton);
    style()->polish(homeButton);

    style()->unpolish(booksButton);
    style()->polish(booksButton);

    style()->unpolish(filmsButton);
    style()->polish(filmsButton);

    style()->unpolish(songsButton);
    style()->polish(songsButton);
}

void MainWindow::doubleClickedCard() {
    if(detailedViewWidget) {
        stackedWidget->removeWidget(detailedViewWidget);
    }
    View::ItemRender::Full detailedView;
    subject->accept(detailedView);
    detailedViewWidget = detailedView.getWidget();
    stackedWidget->addWidget(detailedViewWidget);
    stackedWidget->setCurrentWidget(detailedViewWidget);
    songsButton->setProperty("active", false);
    homeButton->setProperty("active", false);
    booksButton->setProperty("active", false);
    filmsButton->setProperty("active", false);
    setButtonVisibility(false);
    refreshButtonStyle();

}

void MainWindow::qCompleterClicked(const QModelIndex &index) {
    if(!index.isValid()){
        return;
    }
    QVariant ptr = index.data(Qt::UserRole);
    subject = ptr.value<const Media::AbstractMedia*>();
    searchCompleter->popup()->hide();
    searchLineEdit->clear();
    doubleClickedCard();
}

void MainWindow::setButton() {
    bool hasItems = (controller->getSize() > 0);
    saveButton->setEnabled(hasItems);
    newDatasetButton->setEnabled(true);
    deleteButton->setEnabled(hasItems);
    editButton->setEnabled(hasItems);

}

void MainWindow::setButtonVisibility(bool state) {
    addAction->setVisible(state);
    saveAction->setVisible(state);
    saveNewAction->setVisible(state);
    importAction->setVisible(state);
    newDatasetButtonAction->setVisible(state);
    editAction->setVisible(state);
    deleteAction->setVisible(state);
}

void MainWindow::SearchReturnPressed() {
    if(searchGrid) {
        stackedWidget->removeWidget(searchGrid);
    }
    QWidget* searchWidget = new QWidget();
    QVBoxLayout* searchLayout = new QVBoxLayout(searchWidget);
    QString searchTitle = QString("Results for %1").arg(searchLineEdit->text());
    QLabel* searchLabel = new QLabel(searchTitle);
    searchLabel->setObjectName("SectionTitle");
    searchLayout->addWidget(searchLabel);

    searchGrid = new View::ItemRender::Grid();
    std::vector<const Media::AbstractMedia*> results;
    controller->search(results, (searchLineEdit->text()).toStdString());
    searchGrid->displayData(results);
    searchLayout->addWidget(searchGrid);
    searchLineEdit->clear();
    stackedWidget->addWidget(searchWidget);
    stackedWidget->setCurrentWidget(searchWidget);
}

void MainWindow::setSaved(bool newState) {
    saved = newState;
}

void MainWindow::closeDataset() {
    if(saved == false) {
        QMessageBox unsavedFile;
        unsavedFile.setText("There are unsaved changes, if you upload a new file these will be lost. Do you want to save them before proceeding?");
        unsavedFile.setInformativeText("Do you want save your changes?");
        unsavedFile.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        unsavedFile.setDefaultButton(QMessageBox::Yes);
        int choise = unsavedFile.exec();
        switch(choise) {
            case QMessageBox::Yes:
                save();
                controller->requestEmptyDataset();
            break;
        case QMessageBox::No:
                controller->requestEmptyDataset();
            break;
        }
    } else {
        controller->requestEmptyDataset();
    }
    setButton();
}

} // View
