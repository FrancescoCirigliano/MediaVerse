#ifndef MREADER_H
#define MREADER_H

#include <QJsonObject>
#include "../AbstractMedia.h"

namespace Media::Converter::Json {

class MReader {
public:
    virtual ~MReader() = default;
    virtual AbstractMedia* read(const QJsonObject& obj) = 0;
};

} // Media::Converter::Json

#endif // MREADER_H
