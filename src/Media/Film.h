#ifndef FILM_H
#define FILM_H

#include "AbstractMedia.h"
#include <vector>

namespace Media {

class Film : public AbstractMedia {
public:
    enum quality {HD, FullHD, UltraHD};
private:
    quality videoQuality;
    std::string director;
    unsigned int duration;
    std::vector<std::string> actors;
public:
    Film(unsigned int id,
        std::string title,
        unsigned int releaseYear,
        std::string image_path,
        std::string category,
        bool completed,
        quality videoQuality,
        std::string director,
        unsigned int duration,
        std::vector<std::string> actors
        );

    unsigned int getQuality() const;
    Film& setQuality(const quality q);
    const std::string& getDirector() const;
    Film& setDirector(std::string director);
    unsigned int getDuration() const;
    Film& setDuration(const unsigned int duration);
    const std::vector<std::string>& getActors() const;
    void accept(Visitor &visitor) override;
    void accept(ConstVisitor &visitor) const override;
};

} // Media
#endif // FILM_H
