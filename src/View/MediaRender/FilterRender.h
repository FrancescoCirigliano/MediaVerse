#ifndef FILTERRENDER_H
#define FILTERRENDER_H

#include <vector>
#include "../../Media/AbstractMedia.h"
#include "../../Media/ConstVisitor.h"

namespace View::ItemRender {

class FilterRender : public Media::ConstVisitor {
private:
    std::vector<const Media::AbstractMedia*> bookslist;
    std::vector<const Media::AbstractMedia*> filmlist;
    std::vector<const Media::AbstractMedia*> songlist;
public:
    virtual void visit(const Media::Book& book) override;
    virtual void visit(const Media::Film& film) override;
    virtual void visit(const Media::Song& song) override;

    const std::vector<const Media::AbstractMedia*>& getBooks() const;
    const std::vector<const Media::AbstractMedia*>& getFilms() const;
    const std::vector<const Media::AbstractMedia*>& getSongs() const;
};

}

#endif // FILTERRENDER_H
