#ifndef BOOKEDITOR_H
#define BOOKEDITOR_H

#include "AbstractItemEditor.h"
#include <QLineEdit>
#include <QSpinBox>

namespace View::ItemEditor {

class BookEditor : public AbstractItemEditor{
private:
    QLineEdit* authorInput;
    QLineEdit* descriptionInput;
    QSpinBox* pagesInput;
    QLineEdit* editorInput;
    QLineEdit* ISBNInput;

public:
    BookEditor(QWidget* parent = 0);
    virtual ~BookEditor();
    virtual Media::AbstractMedia* create(
            unsigned int id,
            const QString& title,
            const unsigned int releaseYear,
            const QString& image_path,
            const QString& category,
            const bool completed
            ) const override;
    void setValues(const Media::Book& book);
};

} // View::ItemEditor

#endif // BOOKEDITOR_H
