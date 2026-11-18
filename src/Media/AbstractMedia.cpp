#include "AbstractMedia.h"

namespace Media {
    AbstractMedia::AbstractMedia(
            unsigned int id,
            std::string title,
            unsigned int releaseYear,
            std::string image_path,
            std::string category,
            bool completed
            ) :
            id(id),
            title(title),
            releaseYear(releaseYear),
            image_path(image_path),
            category(category),
            completed(completed)
    {}

    const unsigned int& AbstractMedia::getID() const  {
        return id;
    }

    AbstractMedia& AbstractMedia::setID(const unsigned int id) {
        this->id = id;
        return *this;
    }

    const std::string& AbstractMedia::getTitle() const {
        return title;
    }

    AbstractMedia& AbstractMedia::setTitle(const std::string title) {
        this->title = title;
        return *this;
    }

    unsigned int AbstractMedia::get_release_year() const {
       return releaseYear;
    }

    AbstractMedia& AbstractMedia::set_release_year(const unsigned int releaseYear) {
        this->releaseYear = releaseYear;
        return *this;
    }

    const std::string& AbstractMedia::getImagePath() const {
        return image_path;
    }

    AbstractMedia& AbstractMedia::setImagePath(const std::string image_path) {
        this->image_path = image_path;
        return *this;
    }

    const std::string& AbstractMedia::getCategory() const {
        return category;
    }

    AbstractMedia& AbstractMedia::setCategory(const std::string category) {
        this->category = category;
        return *this;
    }

    bool AbstractMedia::getCompleted() const {
        return completed;
    }

    AbstractMedia& AbstractMedia::setCompleted(bool status) {
        this->completed = status;
        return *this;
    }

} // Media
