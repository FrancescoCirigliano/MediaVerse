#ifndef SONG_H
#define SONG_H

#include "AbstractMedia.h"

namespace Media {

class Song : public AbstractMedia {
public:
    enum format {MP3, WAW, FLAC};
private:
    format audioFormat;
    std::string author;
    std::string album;
    unsigned int duration;
    double bitrate;
    bool lossless;
public:
    Song(unsigned int id,
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
            bool lossless = false
            );

    unsigned int getFormat() const;
    Song& setFormat(const format f);
    const std::string& getAuthor() const;
    Song& setAuthor(const std::string author);
    const std::string& getAlbum() const;
    Song& setAlbum(const std::string album);
    unsigned int getDuration() const;
    Song& setDuration(unsigned int duration);
    double getBitrate() const;
    Song& setBitrate(double bitrate);
    Song& setLossLess();
    bool isLossLess() const;
    void accept(Visitor& visitor) override;
    void accept(ConstVisitor& visitor) const override;
};

} // Media

#endif // SONG_H
