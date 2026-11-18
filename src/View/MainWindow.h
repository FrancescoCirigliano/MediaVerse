#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "EditWidget.h"
#include "MediaRender/IMediaRender.h"
#include "MediaRender/Card.h"

#include <QVBoxLayout>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QCompleter>
#include <QStackedWidget>
#include <QStandardItemModel>


namespace Controller {
class Controller;
}

namespace View::ItemRender {
class Full;
class Grid;
}

namespace View {
class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    const Media::AbstractMedia* subject = nullptr;
    Controller::Controller* controller;
    QLineEdit* searchLineEdit;
    QWidget* centralWidget;
    QWidget* detailedViewWidget;

    QStackedWidget* stackedWidget;

    // QAction for hide button
    QAction* addAction;
    QAction* saveNewAction;
    QAction* importAction;
    QAction* editAction;
    QAction* deleteAction;
    QAction* saveAction;
    QAction* newDatasetButtonAction;

    // ListWidget
    QListWidget* booklistView;
    QListWidget* filmlistView;
    QListWidget* songlistView;

    View::ItemRender::Grid* filteredBookView = nullptr;
    View::ItemRender::Grid* filteredFilmView = nullptr;
    View::ItemRender::Grid* filteredSongView = nullptr;

    // Header Button
    QPushButton* addButton;
    QPushButton* saveNewButton;
    QPushButton* importButton;
    QPushButton* editButton;
    QPushButton* deleteButton;
    QPushButton* saveButton;
    QPushButton* newDatasetButton;

    // SideBar button
    QPushButton* homeButton;
    QPushButton* booksButton;
    QPushButton* filmsButton;
    QPushButton* songsButton;

    QCompleter* searchCompleter;
    QStandardItemModel* searchModel;

    unsigned int max_media = 5;

    View::ItemRender::Card* card;
    View::ItemRender::Grid* searchGrid;
    unsigned int currentView;
    bool saved = true;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void setupSidebar();
    void setupHeader();
    void setupUI();
    void loadStyleSheet();
public slots:
    void createItem();
    void saveAs();
    void save();
    void load();
    void displayMedia(std::vector<const Media::AbstractMedia*>& booklist, std::vector<const Media::AbstractMedia*>& filmlist, std::vector<const Media::AbstractMedia*>& songlist);
    void clickedCard(QListWidgetItem* item);
    void editItem();
    void deleteItem();
    void homeButtonClicked();
    void bookButtonClicked();
    void filmButtonClicked();
    void songButtonClicked();
    void setBookView(View::ItemRender::Grid* view);
    void setFilmView(View::ItemRender::Grid* view);
    void setSongView(View::ItemRender::Grid* view);
    void searchTextChanged(const QString& text);
    void refreshButtonStyle();
    void doubleClickedCard();
    void qCompleterClicked(const QModelIndex& index);
    void setButton();
    void setButtonVisibility(bool state);
    void SearchReturnPressed();
    void setSaved(bool newState);
    void closeDataset();
};

} // View

#endif // MAINWINDOW_H
