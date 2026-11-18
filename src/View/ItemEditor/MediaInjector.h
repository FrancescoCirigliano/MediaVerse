#ifndef MEDIAINJECTOR_H
#define MEDIAINJECTOR_H

#include "../../Media/ConstVisitor.h"
#include "BookEditor.h"
#include "FilmEditor.h"
#include "SongEditor.h"

namespace View::ItemEditor {

class MediaInjector : public Media::ConstVisitor {
private:
    BookEditor& bookEditor;
    FilmEditor& filmEditor;
    SongEditor& songEditor;
public:
    MediaInjector(BookEditor& bookEditor, FilmEditor& filmEditor, SongEditor& songEditor);
    virtual void visit(const Media::Book& book);
    virtual void visit(const Media::Film& film);
    virtual void visit(const Media::Song& song);
};

} // View::ItemEditor

#endif // MEDIAINJECTOR_H
