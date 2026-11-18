#ifndef FULL_H
#define FULL_H

#include <QWidget>
#include "IMediaRender.h"

namespace View::ItemRender {

class Full : public IMediaRender {
private:
    QWidget* widget;
    void loadStyleSheet();
public:
    Full();
    virtual QWidget* getWidget() const override;
    virtual void visit(const Media::Book& book) override;
    virtual void visit(const Media::Film& film) override;
    virtual void visit(const Media::Song& song) override;
};

}

#endif // FULL_H
