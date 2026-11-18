#ifndef ABSTRACTITEMEDITOR_H
#define ABSTRACTITEMEDITOR_H
#include "../../Media/AbstractMedia.h"

#include <QWidget>

namespace View::ItemEditor {

class AbstractItemEditor : public QWidget {
    Q_OBJECT
public:
    AbstractItemEditor(QWidget *parent = nullptr);
    virtual ~AbstractItemEditor();
    virtual Media::AbstractMedia* create(
            unsigned int id,
            const QString& title,
            const unsigned int releaseYear,
            const QString& image_path,
            const QString& category,
            const bool completed
   ) const =0;
};

} // View::ItemEditor

#endif // ABSTRACTITEMEDITOR_H
