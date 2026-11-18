#include "FilmEditor.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTimeEdit>
#include <QLabel>
#include "../../Media/Film.h"


namespace View::ItemEditor {

FilmEditor::FilmEditor(QWidget *parent): AbstractItemEditor(parent) {
    QFormLayout* form = new QFormLayout(this);

    quality = new QComboBox();
    QLabel* qualityLabel = new QLabel("QUALITY");

    quality->addItem("HD"); quality->addItem("FullHD"); quality->addItem("UltraHD");
    form->addRow(qualityLabel, quality);

    director = new QLineEdit();
    QLabel* directorLabel = new QLabel("DIRECTED BY");
    form->addRow(directorLabel, director);

    duration = new QTimeEdit();
    duration->setDisplayFormat("hh:mm");
    QLabel* durationLabel = new QLabel("DURATION (hh:mm)");
    form->addRow(durationLabel, duration);

    actorsList = new QListWidget();
    QVBoxLayout* actors_vbox = new QVBoxLayout();
    actorName = new QLineEdit();
    QPushButton* addActorButton = new QPushButton("Add Actor");
    addActorButton->setProperty("class", "secondaryButton");
    QHBoxLayout* actors_hbox = new QHBoxLayout();
    actors_hbox->addWidget(actorName);
    actors_hbox->addWidget(addActorButton);
    actors_vbox->addLayout(actors_hbox);
    actors_vbox->addWidget(actorsList);
    form->addRow(actors_vbox);

    connect(addActorButton, &QPushButton::clicked, this, &FilmEditor::addActor);

}

FilmEditor::~FilmEditor() {};

void FilmEditor::addActor() {
    actorsList->addItem(actorName->text());
    actors.push_back(actorName->text().toStdString());
    actorName->clear();
}

Media::AbstractMedia *FilmEditor::create(unsigned int id, const QString &title, const unsigned int releaseYear, const QString &image_path, const QString &category, const bool completed) const {
    QTime durationTime = duration->time();
    float durationSeconds = QTime(0,0,0).secsTo(durationTime);
    return new Media::Film(
                id,
                title.toStdString(),
                releaseYear,
                image_path.toStdString(),
                category.toStdString(),
                completed,
                static_cast<Media::Film::quality>(quality->currentIndex()),
                director->text().toStdString(),
                durationSeconds,
                actors
                );
}

void FilmEditor::setValues(const Media::Film &film){
    quality->setCurrentIndex(film.getQuality());
    director->setText(QString::fromStdString(film.getDirector()));
    float durationSeconds = film.getDuration();
    QTime durationTime = QTime::fromMSecsSinceStartOfDay(static_cast<int>(durationSeconds)*1000);
    duration->setTime(durationTime);
    std::vector<std::string> actors = film.getActors();
    for(std::vector<std::string>::const_iterator it = actors.begin(); it != actors.end(); it++) {
        actorsList->addItem(QString::fromStdString(*it));
    }
}

} // View::ItemEditor
