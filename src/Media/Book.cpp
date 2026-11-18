#include "Book.h"

namespace Media {

    Book::Book(
         unsigned int id,
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
         ):
        AbstractMedia(id, title, releaseYear, image_path, category, completed),
        author(author),
        description(description),
        pages(pages),
        editor(editor),
        ISBN(ISBN)
    {}

    const std::string& Book::getAuthor() const {
        return author;
    }

    Book& Book::setAuthor(const std::string author) {
        this->author = author;
        return *this;
    }

    const std::string& Book::getDescription() const {
        return description;
    }

    Book& Book::setDescription(const std::string description) {
        this->description = description;
        return *this;
    }

    unsigned int Book::getPages() const {
        return pages;
    }

    Book& Book::setPages(const unsigned int pages) {
        this->pages = pages;
        return *this;
    }

    const std::string& Book::getEditor() const {
        return editor;
    }

    Book& Book::setEditor(const std::string editor) {
        this->editor = editor;
        return *this;
    }

    const std::string& Book::getISBN() const {
        return ISBN;
    }

    Book& Book::setISBN(const std::string ISBN) {
        this->ISBN = ISBN;
        return *this;
    }

    void Book::accept(Visitor& visitor) {
        visitor.visit(*this);
    }

    void Book::accept(ConstVisitor& visitor) const {
        visitor.visit(*this);
    }
} // Media
