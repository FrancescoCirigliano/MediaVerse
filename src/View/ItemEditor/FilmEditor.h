#ifndef FILMEDITOR_H
#define FILMEDITOR_H

#include "AbstractItemEditor.h"
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QTimeEdit>
#include <QListWidget>

namespace View::ItemEditor {

class FilmEditor : public AbstractItemEditor {
private:
    QComboBox* quality;
    QLineEdit* director;
    QTimeEdit* duration;
    QListWidget* actorsList;
    QLineEdit* actorName;
    std::vector<std::string> actors;

public:
    FilmEditor(QWidget* parent = 0);
    virtual ~FilmEditor();
    virtual Media::AbstractMedia* create(
            unsigned int id,
            const QString& title,
            const unsigned int releaseYear,
            const QString& image_path,
            const QString& category,
            const bool completed
            ) const override;
    void setValues(const Media::Film& film);

public slots:
    void addActor();
};

} // View::ItemEditor

#endif // FILMEDITOR_H
