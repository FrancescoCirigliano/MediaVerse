#ifndef ABSTRACTMEDIA_H
#define ABSTRACTMEDIA_H
#include "ConstVisitor.h"
#include "Visitor.h"
#include <string>

namespace Media {

class AbstractMedia {
private:
    unsigned int id;
    std::string title;
    unsigned int releaseYear;
    std::string image_path;
    std::string category;
    bool completed;
public:
    AbstractMedia(unsigned int id, std::string title, unsigned int releaseYear, std::string image_path, std::string category, bool completed = false);
    virtual ~AbstractMedia() = default;
    const unsigned int& getID() const;
    AbstractMedia& setID(const unsigned int id);
    const std::string& getTitle() const;
    AbstractMedia& setTitle(const std::string title);
    unsigned int get_release_year() const;
    AbstractMedia& set_release_year(const unsigned int releaseYear);
    const std::string& getImagePath() const;
    AbstractMedia& setImagePath(const std::string image_path);
    const std::string& getCategory() const;
    AbstractMedia& setCategory(const std::string category);
    bool getCompleted() const;
    AbstractMedia& setCompleted(bool status);
    virtual void accept(ConstVisitor& visitor) const = 0;
    virtual void accept(Visitor& visitor) = 0;
};

} // Media

#endif // ABSTRACTMEDIA_H
