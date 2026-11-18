#ifndef IMEDIARENDER_H
#define IMEDIARENDER_H

#include "../../Media/AbstractMedia.h"
#include "../../Media/ConstVisitor.h"
#include <QWidget>

namespace View::ItemRender {
class IMediaRender : public Media::ConstVisitor {
public:
    virtual QWidget* getWidget() const = 0;
};
}
#endif // IMEDIARENDER_H
