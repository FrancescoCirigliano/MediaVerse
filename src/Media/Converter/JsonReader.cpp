#include "JsonReader.h"
#include <QJsonArray>
#include "../Book.h"
#include "../Film.h"
#include "../Song.h"

namespace Media::Converter::Json {

const std::map<unsigned int, AbstractMedia *> &JsonReader::getCache() const {
    return cache;
}

JsonReader& JsonReader::clear() {
    cache.clear();
    return *this;
}

AbstractMedia* JsonReader::read(const QJsonObject& obj) {
    QJsonValue type = obj.value("type");
    if(type.isUndefined()){
        throw std::string("Missing item type.");
    }
    const unsigned int identifier = obj.value("id").toInt();
    if(cache.count(identifier) > 0) {
        return cache[identifier];
    }
    else if (type.toString().toStdString().compare("book") == 0) {
        cache[identifier] = readBook(obj);
    }
    else if (type.toString().toStdString().compare("film") == 0) {
        cache[identifier] = readFilm(obj);
    }
    else if (type.toString().toStdString().compare("song") == 0) {
        cache[identifier] = readSong(obj);
    } else {
        throw std::string("Unknown type.");
    }
    return cache[identifier];
}

AbstractMedia* JsonReader::readBook(const QJsonObject &obj) const {
    return new Book (
                obj.value("id").toInt(),
                obj.value("title").toString().toStdString(),
                obj.value("releaseYear").toInt(),
                obj.value("imagePath").toString().toStdString(),
                obj.value("category").toString().toStdString(),
                obj.value("completed").toBool(),
                obj.value("author").toString().toStdString(),
                obj.value("description").toString().toStdString(),
                obj.value("pages").toInt(),
                obj.value("editor").toString().toStdString(),
                obj.value("ISBN").toString().toStdString()
                );
}

AbstractMedia* JsonReader::readFilm(const QJsonObject &obj) const {
    std::vector<std::string> actors;
    QJsonArray json_actors = obj.value("actors").toArray();
    for(auto value : json_actors) {
       actors.push_back(value.toString().toStdString());
    }
    return new Film (
                obj.value("id").toInt(),
                obj.value("title").toString().toStdString(),
                obj.value("releaseYear").toInt(),
                obj.value("imagePath").toString().toStdString(),
                obj.value("category").toString().toStdString(),
                obj.value("completed").toBool(),
                static_cast<Media::Film::quality>(obj.value("quality").toInt()),
                obj.value("director").toString().toStdString(),
                obj.value("duration").toInt(),
                actors
                );
}

AbstractMedia* JsonReader::readSong(const QJsonObject &obj) const {
    return new Song (
                obj.value("id").toInt(),
                obj.value("title").toString().toStdString(),
                obj.value("releaseYear").toInt(),
                obj.value("imagePath").toString().toStdString(),
                obj.value("category").toString().toStdString(),
                obj.value("completed").toBool(),
                static_cast<Media::Song::format>(obj.value("audioFormat").toInt()),
                obj.value("author").toString().toStdString(),
                obj.value("album").toString().toStdString(),
                obj.value("duration").toInt(),
                obj.value("bitrate").toDouble(),
                obj.value("lossless").toBool()
                );
}

} // Media::Converter::Json
