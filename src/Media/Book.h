#ifndef BOOK_H
#define BOOK_H

#include "AbstractMedia.h"

namespace Media {

class Book : public AbstractMedia {
private:
    std::string author;
    std::string description;
    unsigned int pages;
    std::string editor;
    std::string ISBN;
public:
    Book(unsigned int id,
         std::string title,
         unsigned int releaseYear,
         std::string image_path,
         std::string category,
         bool completed,
         std::string author,
         std::string description,
         unsigned int pages,
         std::string editor,
         std::string ISBN
         );

    const std::string& getAuthor() const;
    Book& setAuthor(const std::string description);
    const std::string& getDescription() const;
    Book& setDescription(const std::string author);
    unsigned int getPages() const;
    Book& setPages(const unsigned int pages);
    const std::string& getEditor() const;
    Book& setEditor(const std::string editor);
    const std::string& getISBN() const;
    Book& setISBN(const std::string ISBN);
    void accept(Visitor& vistor) override;
    void accept(ConstVisitor& visitor) const override;
};

} // Media
#endif // BOOK_H
