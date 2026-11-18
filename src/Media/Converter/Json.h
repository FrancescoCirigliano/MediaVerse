#ifndef JSON_H
#define JSON_H
#include "MReader.h"
#include <QJsonObject>
#include "../AbstractMedia.h"

namespace Media::Converter::Json {

class Json {
private:
    MReader& reader;

public:
    Json(MReader& reader);
    const MReader& getReader() const;
    QJsonObject fromObj(const AbstractMedia& item) const;
    AbstractMedia* toObj(const QJsonObject& json) const;
};

} // Media::Converter::Json

#endif // JSON_H
