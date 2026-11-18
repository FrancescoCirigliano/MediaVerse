#include "TypeSelector.h"
#include <QPushButton>
namespace View {

TypeSelector::TypeSelector(QButtonGroup* group_box): group_box(group_box) {}

void TypeSelector::visit(const Media::Book &book) {
    (void) book;
    if(group_box && group_box->button(0)) {
        group_box->button(0)->setChecked(true);
    }
}

void TypeSelector::visit(const Media::Film &film) {
    (void) film;
    if(group_box && group_box->button(1)) {
        group_box->button(1)->setChecked(true);
    }
}


void TypeSelector::visit(const Media::Song &song) {
    (void) song;
    if(group_box && group_box->button(2)) {
        group_box->button(2)->setChecked(true);
    }
}

QButtonGroup *TypeSelector::getButtonGroup() {
    return group_box;
}

TypeSelector& TypeSelector::setComboBox(QButtonGroup *group_box) {
    this->group_box = group_box;
    return *this;
}

} // View
