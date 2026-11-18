#include "JsonFile.h"
#include "../Converter/JsonReader.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

namespace Media::DataMapper {

JsonFile::JsonFile(const std::string& path, Converter::Json::Json& converter): path(path), converter(converter) {}

JsonFile JsonFile::fromPath(const std::string& path) {
    Converter::Json::JsonReader reader;
    Converter::Json::Json converter(reader);
    JsonFile data_mapper(path, converter);
    return data_mapper;
}

const std::string& JsonFile::getPath() const {
    return path;
}

JsonFile& JsonFile::setPath(const std::string& path) {
    this->path = path;
    return *this;
}

const Converter::Json::Json& JsonFile::getConverter() const {
    return converter;
}

JsonFile& JsonFile::store(const std::vector<AbstractMedia*> items) {
    QJsonArray json_items;
    for(std::vector<AbstractMedia*>::const_iterator it = items.begin();
         it!=items.end();
         it++
        )
    {
        json_items.push_back(converter.fromObj(**it));
    }
    QJsonDocument document(json_items);
    QFile json_file(path.c_str());
    json_file.open(QFile::WriteOnly);
    json_file.write(document.toJson());
    json_file.close();
    return *this;
}

std::vector<AbstractMedia*> JsonFile::load() {
    std::vector<AbstractMedia*> items;
    QFile json_file(path.c_str());
    json_file.open(QFile::ReadOnly);
    QByteArray data = json_file.readAll();
    json_file.close();

    QJsonDocument document = QJsonDocument::fromJson(data);
    QJsonArray json_items = document.array();


    for(const QJsonValue& value : json_items) {
        QJsonObject json_obj = value.toObject();
        items.push_back(converter.toObj(json_obj));
    }
    return items;
}

} // Media::DataMapper
