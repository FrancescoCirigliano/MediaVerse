#ifndef EDITWIDGET_H
#define EDITWIDGET_H

#include <QLineEdit>
#include <QSpinBox>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QStackedLayout>
#include <QPushButton>
#include <QCheckBox>

#include "ItemEditor/AbstractItemEditor.h"

namespace Controller {
class Controller;
}

namespace View {

class EditWidget : public QWidget {
    Q_OBJECT
private:
    QLineEdit* titleInput;
    QSpinBox* releaseYearInput;
    QLineEdit* categoryInput;
    QLabel* imagePreview;
    QPixmap* pixmap;
    QString image_path;

    QStackedLayout* stacked_layout;
    QVector<ItemEditor::AbstractItemEditor*> editors;
    const Media::AbstractMedia* subject;
    QPushButton* acceptButton;
    QPushButton* cancelButton;
    QCheckBox* completed;
    Controller::Controller* controller;
public:
    explicit EditWidget(Controller::Controller* controller, const Media::AbstractMedia* subject = nullptr, QWidget *parent = nullptr);
    void loadStyleSheet();
public slots:
    void showType(int index);
    void apply();
    void selectImage();
    void cancel();
};

} // View

#endif // EDITWIDGET_H
