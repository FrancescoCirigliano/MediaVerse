#include "Song.h"

namespace Media {

    Song::Song(unsigned int id,
            std::string title,
            unsigned int releaseYear,
            std::string image_path,
            std::string category,
            bool completed,
            format audioFormat,
            std::string author,
            std::string album,
            unsigned int duration,
            double bitrate,
            bool lossless
        ) :
        AbstractMedia(id, title, releaseYear, image_path, category, completed),
        audioFormat(audioFormat),
        author(author),
        album(album),
        duration(duration),
        bitrate(bitrate),
        lossless(lossless)
    {}

    unsigned int Song::getFormat() const {
        return audioFormat;
    }

    Song& Song::setFormat(const format f) {
        this->audioFormat = f;
        return *this;
    }

    const std::string& Song::getAuthor() const {
        return author;
    }

    Song& Song::setAuthor(const std::string author) {
        this->author = author;
        return *this;
    }

    const std::string& Song::getAlbum() const {
        return album;
    }

    Song& Song::setAlbum(const std::string album) {
        this->album = album;
        return *this;
    }

    unsigned int Song::getDuration() const {
        return duration;
    }

    Song& Song::setDuration(unsigned int duration) {
        this->duration = duration;
        return *this;
    }

    double Song::getBitrate() const {
        return bitrate;
    }

    Song &Song::setBitrate(double bitrate) {
        this->bitrate = bitrate;
        return *this;
    }

    Song& Song::setLossLess() {
        if(audioFormat == 0) {
            lossless = false;
        } else {
            lossless = true;
        }
        return *this;
    }

    bool Song::isLossLess() const {
        return lossless;
    }

    void Song::accept(Visitor& visitor) {
        visitor.visit(*this);
    }

    void Song::accept(ConstVisitor& visitor) const {
        visitor.visit(*this);
    }


}
