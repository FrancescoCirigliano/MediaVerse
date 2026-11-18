#ifndef JSONREPOSITORY_H
#define JSONREPOSITORY_H

#include <string>
#include <map>

#include "MRepository.h"
#include "../DataMapper/JsonFile.h"

namespace Media::Repository {

class JsonRepository : public MRepository {
private:
    unsigned int id;
    DataMapper::JsonFile data_mapper;
    std::map<unsigned int, AbstractMedia*> repository;
public:
    JsonRepository(DataMapper::JsonFile data_mapper);
    virtual ~JsonRepository();
    const unsigned int& getNextID() const;
    void NextID();
    JsonRepository& setID(unsigned int id);
    static JsonRepository fromPath(const std::string path);
    const DataMapper::JsonFile& getDataMapper() const;
    const std::map<unsigned int, AbstractMedia*>& getRepository() const;
    const std::string& getPath() const;
    JsonRepository& setPath(std::string path);
    virtual JsonRepository& create(AbstractMedia* item);
    virtual AbstractMedia* read(unsigned int id) const;
    virtual JsonRepository& update(AbstractMedia* item);
    virtual JsonRepository& remove(unsigned int id);
    virtual std::vector<AbstractMedia*> readAll() const;
    unsigned int getSize() const;
    JsonRepository& store();
};

}

#endif // JSONREPOSITORY_H
