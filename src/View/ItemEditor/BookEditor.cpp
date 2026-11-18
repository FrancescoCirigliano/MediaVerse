#include "BookEditor.h"
#include "../../Media/Book.h"

#include <QFormLayout>
#include <QLabel>

namespace View::ItemEditor {

BookEditor::BookEditor(QWidget* parent): AbstractItemEditor(parent) {

    QFormLayout* form = new QFormLayout();

    authorInput = new QLineEdit();
    QLabel* authorLabel = new QLabel("AUTHOR");
    form->addRow(authorLabel, authorInput);

    descriptionInput = new QLineEdit();
    QLabel* descriptionLabel = new QLabel("DESCRIPTION");
    form->addRow(descriptionLabel, descriptionInput);

    pagesInput = new QSpinBox();
    pagesInput->setMinimum(0);
    pagesInput->setMaximum(5000);
    QLabel* pagesLabel = new QLabel("PAGES");
    form->addRow(pagesLabel, pagesInput);

    editorInput = new QLineEdit();
    QLabel* editorLabel = new QLabel("EDITOR");
    form->addRow(editorLabel, editorInput);

    ISBNInput = new QLineEdit();
    QLabel* ISBNLabel = new QLabel("ISBN");
    form->addRow(ISBNLabel, ISBNInput);

    setLayout(form);

}

BookEditor::~BookEditor() {};

Media::AbstractMedia* BookEditor::create(unsigned int id, const QString& title, const unsigned int releaseYear, const QString& image_path, const QString& category, const bool completed) const {
    return new Media::Book(
                id,
                title.toStdString(),
                releaseYear,
                image_path.toStdString(),
                category.toStdString(),
                completed,
                authorInput->text().toStdString(),
                descriptionInput->text().toStdString(),
                pagesInput->value(),
                editorInput->text().toStdString(),
                ISBNInput->text().toStdString()
                );
}

void BookEditor::setValues(const Media::Book &book) {
    authorInput->setText(QString::fromStdString(book.getAuthor()));
    descriptionInput->setText(QString::fromStdString(book.getDescription()));
    pagesInput->setValue(book.getPages());
    editorInput->setText(QString::fromStdString(book.getEditor()));
    ISBNInput->setText(QString::fromStdString(book.getISBN()));
}

} // View::ItemEditor
