#include "../Converter/JsonReader.h"
#include "../Converter/Json.h"
#include "JsonRepository.h"

namespace Media::Repository {

    JsonRepository::JsonRepository(DataMapper::JsonFile data_mapper) : data_mapper(data_mapper)
    {
        std::vector<AbstractMedia*> items(data_mapper.load());
        for(std::vector<AbstractMedia*>::const_iterator it = items.begin();
             it != items.end();
             it++
             )
        {
            repository[(*it)->getID()] = *it;
        }
        id = 0;
    }

    JsonRepository::~JsonRepository() {
        for(std::map<unsigned int, AbstractMedia*>::const_iterator it = repository.begin();
             it != repository.end();
             it++
            )
        {
            delete it->second;
        }
    }

    const unsigned int &JsonRepository::getNextID() const  {
        return id;
    }

    void JsonRepository::NextID() {
        this->id++;
    }

    JsonRepository &JsonRepository::setID(unsigned int id) {
        this->id = id;
        return *this;
    }

    JsonRepository JsonRepository::fromPath(const std::string path) {
        Converter::Json::JsonReader reader;
        Converter::Json::Json converter(reader);
        DataMapper::JsonFile data_mapper(path, converter);
        JsonRepository repository(data_mapper);
        return repository;
    }

    const DataMapper::JsonFile& JsonRepository::getDataMapper() const {
        return data_mapper;
    }

    const std::map<unsigned int, AbstractMedia*>& JsonRepository::getRepository() const {
        return repository;
    }

    const std::string& JsonRepository::getPath() const {
        return data_mapper.getPath();
    }

    JsonRepository& JsonRepository::setPath(std::string path) {
        data_mapper.setPath(path);
        return *this;
    }

    JsonRepository& JsonRepository::create(AbstractMedia* item) {
        repository[item->getID()] = item;
        NextID();
        return *this;
    }

    AbstractMedia* JsonRepository::read(unsigned int id) const {
        std::map<unsigned int, AbstractMedia*>::const_iterator it = repository.find(id);
        if(it == repository.end()) {
            throw std::string("Item not found");
        }
        return it->second;
    }

    JsonRepository& JsonRepository::update(AbstractMedia* item) {
        return create(item);
    }

    JsonRepository& JsonRepository::remove(unsigned int id) {
        std::map<unsigned int, AbstractMedia*>::const_iterator it = repository.find(id);
        if(it != repository.end()) {
            repository.erase(it);
        }
        return *this;
    }

    std::vector<AbstractMedia*> JsonRepository::readAll() const {
        std::vector<AbstractMedia*> items;
        for(std::map<unsigned int, AbstractMedia*>::const_iterator it = repository.begin();
             it != repository.end();
             it++
            )
        {
            items.push_back(it->second);
        }
        return items;
    }

    unsigned int JsonRepository::getSize() const {
        return repository.size();
    }

    JsonRepository& JsonRepository::store() {
        data_mapper.store(readAll());
        return *this;
    }

}
