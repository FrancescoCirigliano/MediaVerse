#ifndef CONSTVISITOR_H
#define CONSTVISITOR_H

namespace Media{
class Book;
class Film;
class Song;

class ConstVisitor {
public:
    virtual ~ConstVisitor() {};
    virtual void visit(const Book& book) =0;
    virtual void visit(const Film& film) =0;
    virtual void visit(const Song& song) =0;
};

} // Media

#endif // CONSTVISITOR_H
