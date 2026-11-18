#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Media/AbstractMedia.h"
#include "../Media/Repository/JsonRepository.h"
#include "../Media/Converter/Json.h"
#include "../Media/Converter/JsonReader.h"

#include <QObject>
#include <vector>

namespace View {
class MainWindow;
class EditWidget;
}

namespace View::ItemRender {
class Grid;
}

namespace Media::Repository {
class JsonRepository;
}

namespace Controller {

class Controller : public QObject {
    Q_OBJECT
private:
    View::MainWindow* mainWindow;
    View::EditWidget* editWidget;
    View::ItemRender::Grid* filteredBookView;
    View::ItemRender::Grid* filteredFilmView;
    View::ItemRender::Grid* filteredSongView;

    Media::Repository::JsonRepository* repository;

    std::vector<const Media::AbstractMedia*> cache;
    std::vector<const Media::AbstractMedia*> booklist;
    std::vector<const Media::AbstractMedia*> filmlist;
    std::vector<const Media::AbstractMedia*> songlist;

    Media::Converter::Json::JsonReader* reader;
    Media::Converter::Json::Json* converter;
    Media::DataMapper::JsonFile* data_mapper;
public:
    explicit Controller(View::MainWindow* mainWindow, QObject *parent = nullptr);
    ~Controller();
    void requestCreateNewItem();
    void editCompleted(Media::AbstractMedia* item);
    const std::vector<const Media::AbstractMedia*> requestData() const;
    void cleanCache();
    void requestEditItem(const Media::AbstractMedia* media);
    unsigned int requestNextID();
    void requestSaveAs(const std::string path);
    void requestLoad(const std::string path);
    void refreshCache();
    void requestRemoveItem(const Media::AbstractMedia* item);
    void requestFilter();
    void requestSearch(std::string& query);
    void search(std::vector<const Media::AbstractMedia*>& results, const std::string &query);
    unsigned int getSize();
    void requestSave();
    void requestEmptyDataset();
};

}

#endif // CONTROLLER_H
