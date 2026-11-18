#include "JsonVisitor.h"
#include "QJsonArray"
#include <QString>
namespace Media::Converter::Json {

QJsonObject JsonVisitor::getObj() const {
    return obj;
}

void JsonVisitor::visit(const Book &book) {
    QJsonObject book_obj;
    book_obj.insert("id", QJsonValue::fromVariant(book.getID()));
    book_obj.insert("type", QJsonValue::fromVariant("book"));
    book_obj.insert("title", QJsonValue::fromVariant(QString::fromStdString(book.getTitle())));
    book_obj.insert("releaseYear", QJsonValue::fromVariant(book.get_release_year()));
    book_obj.insert("imagePath", QJsonValue::fromVariant(QString::fromStdString(book.getImagePath())));
    book_obj.insert("category", QJsonValue::fromVariant(QString::fromStdString(book.getCategory())));
    book_obj.insert("completed", QJsonValue::fromVariant(book.getCompleted()));
    book_obj.insert("author", QJsonValue::fromVariant(QString::fromStdString(book.getAuthor())));
    book_obj.insert("description", QJsonValue::fromVariant(QString::fromStdString(book.getDescription())));
    book_obj.insert("pages", QJsonValue::fromVariant((book.getPages())));
    book_obj.insert("editor", QJsonValue::fromVariant(QString::fromStdString(book.getEditor())));
    book_obj.insert("ISBN", QJsonValue::fromVariant(QString::fromStdString(book.getISBN())));
    obj = book_obj;
}

void JsonVisitor::visit(const Film& film) {
    QJsonArray actors;
    QJsonObject film_obj;
    film_obj.insert("id", QJsonValue::fromVariant(film.getID()));
    film_obj.insert("type", QJsonValue::fromVariant("film"));
    film_obj.insert("title", QJsonValue::fromVariant(QString::fromStdString(film.getTitle())));
    film_obj.insert("releaseYear", QJsonValue::fromVariant(film.get_release_year()));
    film_obj.insert("imagePath", QJsonValue::fromVariant(QString::fromStdString(film.getImagePath())));
    film_obj.insert("category", QJsonValue::fromVariant(QString::fromStdString(film.getCategory())));
    film_obj.insert("completed", QJsonValue::fromVariant(film.getCompleted()));
    film_obj.insert("quality", QJsonValue::fromVariant(film.getQuality()));
    film_obj.insert("director", QJsonValue::fromVariant(QString::fromStdString(film.getDirector())));
    film_obj.insert("duration", QJsonValue::fromVariant(film.getDuration()));
    for(std::vector<std::string>::const_iterator it = film.getActors().begin();
        it != film.getActors().end();
        it++)
    {
        actors.push_back(QString::fromStdString((*it)));
    }
    film_obj.insert("actors", actors);
    obj = film_obj;
}

void JsonVisitor::visit(const Song& song) {
    QJsonObject song_obj;
    song_obj.insert("id", QJsonValue::fromVariant(song.getID()));
    song_obj.insert("type", QJsonValue::fromVariant("song"));
    song_obj.insert("title", QJsonValue::fromVariant(QString::fromStdString(song.getTitle())));
    song_obj.insert("releaseYear", QJsonValue::fromVariant(song.get_release_year()));
    song_obj.insert("imagePath", QJsonValue::fromVariant(QString::fromStdString(song.getImagePath())));
    song_obj.insert("category", QJsonValue::fromVariant(QString::fromStdString(song.getCategory())));
    song_obj.insert("completed", QJsonValue::fromVariant(song.getCompleted()));
    song_obj.insert("audioFormat", QJsonValue::fromVariant(song.getFormat()));
    song_obj.insert("author", QJsonValue::fromVariant(QString::fromStdString(song.getAuthor())));
    song_obj.insert("album", QJsonValue::fromVariant(QString::fromStdString(song.getAlbum())));
    song_obj.insert("duration", QJsonValue::fromVariant(song.getDuration()));
    song_obj.insert("bitrate", QJsonValue::fromVariant(song.getBitrate()));
    song_obj.insert("lossless", QJsonValue::fromVariant(song.isLossLess()));
    obj = song_obj;
}

} // Media::Converter::Json
