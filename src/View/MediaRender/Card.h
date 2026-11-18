#ifndef CARD_H
#define CARD_H

#include "IMediaRender.h"

namespace View::ItemRender {

class Card : public IMediaRender {
private:
    QWidget* widget;
public:
    Card();
    virtual void visit(const Media::Book& book);
    virtual void visit(const Media::Film& film);
    virtual void visit(const Media::Song& song);
    virtual QWidget* getWidget() const;
};
}

#endif // CARD_H
