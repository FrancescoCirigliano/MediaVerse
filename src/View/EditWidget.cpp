#include "EditWidget.h"
#include "../Controller/Controller.h"
#include "ItemEditor/BookEditor.h"
#include "ItemEditor/FilmEditor.h"
#include "ItemEditor/SongEditor.h"
#include "TypeSelector.h"
#include "ItemEditor/MediaInjector.h"

#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QButtonGroup>
#include <QScrollArea>

namespace View {

EditWidget::EditWidget(Controller::Controller* controller, const Media::AbstractMedia* subject, QWidget *parent): QWidget{parent}, subject(subject), controller(controller) {
    this->setWindowTitle("Add New Media");
    this->setMinimumWidth(900);
    this->setObjectName("createWidget");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout* contentLayout = new QHBoxLayout();

    QWidget* previewSection = new QWidget();
    previewSection->setObjectName("previewSection");
    previewSection->setFixedWidth(300);
    QVBoxLayout* previewLayout = new QVBoxLayout(previewSection);
    previewLayout->setAlignment(Qt::AlignCenter);

    imagePreview = new QLabel();
    imagePreview->setObjectName("previewContainer");
    imagePreview->setAlignment(Qt::AlignCenter);
    imagePreview->setMinimumSize(200, 300);
    imagePreview->setWordWrap(true);

    if (subject != nullptr && !subject->getImagePath().empty()) {
       pixmap = new QPixmap(QString::fromStdString(subject->getImagePath()));
       imagePreview->setPixmap(pixmap->scaled(200, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
       imagePreview->setProperty("hasImage", true);
    } else {
       pixmap = new QPixmap();
       imagePreview->setText("Click the button to upload");
       imagePreview->setProperty("hasImage", false);
    }

    previewLayout->addStretch();
    previewLayout->addWidget(imagePreview);

    QPushButton* selectPath = new QPushButton("Upload Cover");
    selectPath->setObjectName("uploadButton");
    selectPath->setCursor(Qt::PointingHandCursor);
    previewLayout->addWidget(selectPath);
    previewLayout->addStretch();

    contentLayout->addWidget(previewSection);

    QWidget* formSection = new QWidget();
    formSection->setObjectName("formSection");
    QVBoxLayout* formSectionLayout = new QVBoxLayout(formSection);

    QWidget* tabsContainer = new QWidget();
    tabsContainer->setObjectName("tabsContainer");
    QHBoxLayout* tabsLayout = new QHBoxLayout(tabsContainer);

    QPushButton* bookTab = new QPushButton("Book");
    QPushButton* filmTab = new QPushButton("Film");
    QPushButton* musicTab = new QPushButton("Song");
    bookTab->setCheckable(true);
    filmTab->setCheckable(true);
    musicTab->setCheckable(true);

    bookTab->setProperty("class", "tabButton");
    filmTab->setProperty("class", "tabButton");
    musicTab->setProperty("class", "tabButton");

    QButtonGroup* type_selector = new QButtonGroup(this);
    type_selector->addButton(bookTab, 0);
    type_selector->addButton(filmTab, 1);
    type_selector->addButton(musicTab, 2);

    tabsLayout->addWidget(bookTab);
    tabsLayout->addWidget(filmTab);
    tabsLayout->addWidget(musicTab);
    formSectionLayout->addWidget(tabsContainer);

    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setObjectName("formScrollArea");

    QWidget* formWidget = new QWidget();
    QFormLayout* formLayout = new QFormLayout(formWidget);

    formLayout->setRowWrapPolicy(QFormLayout::WrapAllRows);
    formLayout->setLabelAlignment(Qt::AlignLeft);
    formLayout->setFormAlignment(Qt::AlignTop | Qt::AlignLeft);
    formLayout->setVerticalSpacing(25);

    titleInput = new QLineEdit();

    if(subject != nullptr) {
        titleInput->setText(QString::fromStdString(subject->getTitle()));
    }

    QLabel* titleLabel = new QLabel("TITLE");
    titleLabel->setProperty("class", "formLabel");
    formLayout->addRow(titleLabel, titleInput);

    releaseYearInput = new QSpinBox();
    releaseYearInput->setMinimum(1895);
    releaseYearInput->setMaximum(QDate::currentDate().year());

    if(subject != nullptr) {
        releaseYearInput->setValue(subject->get_release_year());
    }

    QLabel* yearLabel = new QLabel("YEAR OF PUBLICATION");
    yearLabel->setProperty("class", "formLabel");
    formLayout->addRow(yearLabel, releaseYearInput);

    categoryInput = new QLineEdit();

    if(subject != nullptr) {
        categoryInput->setText(QString::fromStdString(subject->getCategory()));
    }
    QLabel* categoryLabel = new QLabel("CATEGORY");
    categoryLabel->setProperty("class", "formLabel");
    formLayout->addRow(categoryLabel, categoryInput);

    completed = new QCheckBox("I have already seen/watched/listened");
    if(subject != nullptr) {
        completed->setChecked(subject->getCompleted());
    }
    formLayout->addRow("", completed);

    if(subject != nullptr){
        image_path = QString::fromStdString(subject->getImagePath());
    }

    QFrame* separator = new QFrame();
    separator->setFrameShape(QFrame::HLine);
    separator->setObjectName("separator");
    formLayout->addRow(separator);

    stacked_layout = new QStackedLayout();

    // New Media

    ItemEditor::BookEditor* book_editor = new ItemEditor::BookEditor();
    book_editor->setObjectName("customFieldsContainer");
    stacked_layout->addWidget(book_editor);
    editors.push_back(book_editor);

    ItemEditor::FilmEditor* film_editor = new ItemEditor::FilmEditor();
    film_editor->setObjectName("customFieldsContainer");
    stacked_layout->addWidget(film_editor);
    editors.push_back(film_editor);

    ItemEditor::SongEditor* song_editor = new ItemEditor::SongEditor();
    song_editor->setObjectName("customFieldsContainer");
    stacked_layout->addWidget(song_editor);
    editors.push_back(song_editor);

    formLayout->addRow(stacked_layout);

    scrollArea->setWidget(formWidget);
    formSectionLayout->addWidget(scrollArea);

    contentLayout->addWidget(formSection);

    QWidget* footer = new QWidget();
    footer->setObjectName("modalFooter");
    QHBoxLayout* actionsLayout = new QHBoxLayout(footer);
    actionsLayout->addStretch();

    cancelButton = new QPushButton("Cancel");
    cancelButton->setObjectName("btnCancel");
    cancelButton->setCursor(Qt::PointingHandCursor);

    acceptButton = new QPushButton("Save");
    acceptButton->setObjectName("btnSave");
    acceptButton->setCursor(Qt::PointingHandCursor);

    actionsLayout->addWidget(cancelButton);
    actionsLayout->addWidget(acceptButton);

    mainLayout->addLayout(contentLayout);
    mainLayout->addWidget(footer);

    if (subject != nullptr) {
        ItemEditor::MediaInjector media_injector(*book_editor, *film_editor, *song_editor);
        subject->accept(media_injector);
        TypeSelector editType(type_selector);
        subject->accept(editType);
    } else {
        bookTab->setChecked(true);
    }

    showType(type_selector->checkedId());

    // Connect
    connect(type_selector, qOverload<int>(&QButtonGroup::idClicked), this, &EditWidget::showType);
    connect(acceptButton, &QPushButton::clicked, this, &EditWidget::apply);
    connect(selectPath, &QPushButton::clicked, this, &EditWidget::selectImage);
    connect(cancelButton, &QPushButton::clicked, this, &EditWidget::cancel);

    loadStyleSheet();

}

void EditWidget::loadStyleSheet() {
    QFile file(":/assets/styles/edit_style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        this->setStyleSheet(styleSheet);
    }
}

void EditWidget::selectImage() {
    QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), "./", tr("Image Files (*.png *.jpg *.bmp)"));
    if(path.isEmpty()) {
        qWarning("Path is not valid");
        return;
    }
    image_path = path;
    pixmap = new QPixmap(path);
    imagePreview->setPixmap(pixmap->scaled(200, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    imagePreview->setProperty("hasImage", true);
    imagePreview->setText("");

    style()->unpolish(imagePreview);
    style()->polish(imagePreview);
}

void EditWidget::apply() {
    QString title = titleInput->text();
    int releaseYear = releaseYearInput->value();
    QString category = categoryInput->text();
    bool completedStatus = completed->isChecked();

    // MessageBox for empty fields
    if(title.isEmpty() || category.isEmpty()) {
        QMessageBox emptyFieldError;
        emptyFieldError.setIcon(QMessageBox::Critical);
        emptyFieldError.setText("Empty field are not accepted, please fill to proced");
        emptyFieldError.setStandardButtons(QMessageBox::Ok);
        emptyFieldError.setDefaultButton(QMessageBox::Ok);
        emptyFieldError.exec();
    } else {

        ItemEditor::AbstractItemEditor* editor = editors[stacked_layout->currentIndex()];
        if(subject == nullptr) {
            // New Item
            Media::AbstractMedia* item = editor->create(controller->requestNextID(), title, releaseYear, image_path, category, completedStatus);
            controller->editCompleted(item);
        } else {
            // Edit
            Media::AbstractMedia* item = editor->create(subject->getID(), title, releaseYear, image_path, category, completedStatus);
            controller->editCompleted(item);
        }
        this->close();
    }
}


void EditWidget::cancel() {
    QMessageBox cancelAller;
    cancelAller.setText("Unsaved Changes");
    cancelAller.setInformativeText("Do you want save your changes?");
    cancelAller.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    cancelAller.setDefaultButton(QMessageBox::Save);
    int choise = cancelAller.exec();
    switch(choise) {
        case QMessageBox::Save:
            apply();
        break;
    case QMessageBox::Discard:
        this->close();
        break;
    }
}

void EditWidget::showType(int index) {
    stacked_layout->setCurrentIndex(index);
}

} // View
