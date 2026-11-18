#include "MediaInjector.h"

namespace View::ItemEditor {

MediaInjector::MediaInjector(BookEditor &bookEditor, FilmEditor &filmEditor, SongEditor &songEditor):
    bookEditor(bookEditor),
    filmEditor(filmEditor),
    songEditor(songEditor)
{}

void MediaInjector::visit(const Media::Book& book){
    bookEditor.setValues(book);
}

void MediaInjector::visit(const Media::Film& film){
    filmEditor.setValues(film);
}

void MediaInjector::visit(const Media::Song& song){
    songEditor.setValues(song);
}

} // View::ItemEditor
