#ifndef JSONVISITOR_H
#define JSONVISITOR_H

#include <QJsonObject>
#include "../Book.h"
#include "../Film.h"
#include "../Song.h"

#include "../ConstVisitor.h"

namespace Media::Converter::Json {

class JsonVisitor : public Media::ConstVisitor {
private:
    QJsonObject obj;
public:
    QJsonObject getObj() const;
    void visit(const Book& book);
    void visit(const Film& film);
    void visit(const Song& song);
};

} // Media::Converter::Json
#endif // JSONVISITOR_H
