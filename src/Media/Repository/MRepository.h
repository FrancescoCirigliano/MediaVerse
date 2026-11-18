#ifndef MREPOSITORY_H
#define MREPOSITORY_H

#include <vector>
#include "../AbstractMedia.h"

namespace Media::Repository {

class MRepository {
public:
    virtual ~MRepository() = default;
    virtual MRepository& create(AbstractMedia* item) = 0;
    virtual AbstractMedia* read(unsigned int id) const = 0;
    virtual MRepository& update(AbstractMedia* item) = 0;
    virtual MRepository& remove(unsigned int id) = 0;
    virtual std::vector<AbstractMedia*> readAll() const = 0;
};

} // Media::Repository

#endif // MREPOSITORY_H
