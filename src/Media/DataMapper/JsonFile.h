#ifndef JSONFILE_H
#define JSONFILE_H
#include <string>
#include <vector>

#include "../Converter/Json.h"
#include "../AbstractMedia.h"

namespace Media::DataMapper {

class JsonFile {
private:
    std::string path;
    Converter::Json::Json& converter;
public:
    JsonFile(const std::string& path, Converter::Json::Json& converter);
    static JsonFile fromPath(const std::string& path);
    const std::string& getPath() const;
    JsonFile& setPath(const std::string& path);
    const Converter::Json::Json& getConverter() const;
    JsonFile& store(const std::vector<AbstractMedia*> items);
    std::vector<AbstractMedia*> load();
};

} // Media::DataMapper
#endif // JSONFILE_H
