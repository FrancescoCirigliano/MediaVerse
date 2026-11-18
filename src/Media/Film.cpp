#include "Film.h"

namespace Media {

    Film::Film(unsigned int id,
               std::string title,
               unsigned int releaseYear,
               std::string image_path,
               std::string category,
               bool completed,
               quality videoQuality,
               std::string director,
               unsigned int duration,
               std::vector<std::string> actors
               ):
        AbstractMedia(id, title, releaseYear, image_path, category, completed),
        videoQuality(videoQuality),
        director(director),
        duration(duration),
        actors(actors)
    {}

    unsigned int Film::getQuality() const {
        return videoQuality;
    }

    Film& Film::setQuality(const quality q) {
        this->videoQuality = q;
        return *this;
    }

    const std::string& Film::getDirector() const {
        return director;
    }

    Film& Film::setDirector(std::string director) {
        this->director = director;
        return *this;
    }

    unsigned int Film::getDuration() const {
        return duration;
    }

    Film& Film::setDuration(const unsigned int duration) {
        this->duration = duration;
        return *this;
    }

    const std::vector<std::string>& Film::getActors() const {
        return actors;
    }

    void Film::accept(Visitor& visitor) {
        visitor.visit(*this);
    }

    void Film::accept(ConstVisitor& visitor) const {
        visitor.visit(*this);
    }

} // Media
