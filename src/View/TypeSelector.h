#ifndef TYPESELECTOR_H
#define TYPESELECTOR_H

#include "../Media/ConstVisitor.h"
#include <QButtonGroup>

namespace View {

class TypeSelector : public Media::ConstVisitor {
private:
    QButtonGroup* group_box;
public:
    TypeSelector(QButtonGroup* group_box);
    virtual void visit(const Media::Book& book);
    virtual void visit(const Media::Film& film);
    virtual void visit(const Media::Song& song);
    QButtonGroup* getButtonGroup();
    TypeSelector& setComboBox(QButtonGroup* group_box);
};

} // View
#endif // TYPESELECTOR_H
