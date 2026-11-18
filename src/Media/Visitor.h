#ifndef VISITOR_H
#define VISITOR_H

namespace Media{
class Book;
class Film;
class Song;

class Visitor {
public:
    virtual ~Visitor() {};
    virtual void visit(Book& book) =0;
    virtual void visit(Film& film) =0;
    virtual void visit(Song& song) =0;
};

} // Media

#endif // VISITOR_H
