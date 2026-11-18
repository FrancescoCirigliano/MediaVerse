#include "FilterRender.h"
#include <QPixmap>
#include <QIcon>

#include "../../Media/Book.h"
#include "../../Media/Film.h"
#include "../../Media/Song.h"

namespace View::ItemRender {

void FilterRender::visit(const Media::Book& book) {
    bookslist.push_back(&book);
}

void FilterRender::visit(const Media::Film &film) {
    filmlist.push_back(&film);
}

void FilterRender::visit(const Media::Song &song) {
    songlist.push_back(&song);
}

const std::vector<const Media::AbstractMedia *> &FilterRender::getBooks() const {
    return bookslist;
}

const std::vector<const Media::AbstractMedia *> &FilterRender::getFilms() const {
    return filmlist;
}

const std::vector<const Media::AbstractMedia *> &FilterRender::getSongs() const {
    return songlist;
}

}
