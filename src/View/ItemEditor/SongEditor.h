#ifndef SONGEDITOR_H
#define SONGEDITOR_H

#include "AbstractItemEditor.h"
#include <QLineEdit>
#include <QSpinBox>
#include <QTimeEdit>
#include <QComboBox>
#include <QCheckBox>

namespace View::ItemEditor {

class SongEditor : public AbstractItemEditor {
private:
    QComboBox* format;
    QLineEdit* author;
    QLineEdit* album;
    QTimeEdit* duration;
    QSpinBox* bitrate;
    QCheckBox* lossless;
public:
    SongEditor(QWidget* parent = 0);
    virtual ~SongEditor();
    virtual Media::AbstractMedia* create(
            unsigned int id,
            const QString& title,
            const unsigned int releaseYear,
            const QString& image_path,
            const QString& category,
            const bool completed
            ) const override;
    void setValues(const Media::Song& song);

};

} // View::ItemEditor

#endif // SONGEDITOR_H
