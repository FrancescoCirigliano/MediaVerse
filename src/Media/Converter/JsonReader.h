#ifndef JSONREADER_H
#define JSONREADER_H

#include <map>
#include <QJsonObject>
#include "MReader.h"

namespace Media::Converter::Json {

class JsonReader : public MReader {
private:
    std::map<unsigned int, AbstractMedia*> cache;
    AbstractMedia* readBook(const QJsonObject& obj) const;
    AbstractMedia* readFilm(const QJsonObject& obj) const;
    AbstractMedia* readSong(const QJsonObject& obj) const;

public:
    const std::map<unsigned int, AbstractMedia*>& getCache() const;
    JsonReader& clear();
    virtual AbstractMedia* read(const QJsonObject& obj);
};

} // Media::Converter::JSon

#endif // JSONREADER_H
