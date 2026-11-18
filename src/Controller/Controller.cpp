#include "Controller.h"
#include "../View/EditWidget.h"
#include "../View/MainWindow.h"
#include "../View/Grid.h"
#include "../View/MediaRender/FilterRender.h"


#include <string>
#include <algorithm>

namespace Controller {

Controller::Controller(View::MainWindow* mainWindow, QObject *parent)
    : QObject{parent}, mainWindow(mainWindow) {

    reader = new Media::Converter::Json::JsonReader;
    converter = new Media::Converter::Json::Json(*reader);
    data_mapper= new Media::DataMapper::JsonFile("", *converter);
    repository = new Media::Repository::JsonRepository(*data_mapper);
}

Controller::~Controller()
{
    delete reader;
    delete converter;
    delete data_mapper;
    delete repository;

}

void Controller::refreshCache() {
    cache.clear();
    std::vector<Media::AbstractMedia*> repo_items = repository->readAll();
    for(std::vector<Media::AbstractMedia*>::const_iterator it = repo_items.begin();
        it!=repo_items.end();
        it++)
    {
        cache.push_back(*it);
    }
}


void Controller::requestCreateNewItem() {
    editWidget = new View::EditWidget(this);
    editWidget->show();
    mainWindow->setSaved(false);
}

void Controller::editCompleted(Media::AbstractMedia* item) {
    editWidget->close();
    repository->update(item);
    refreshCache();
    mainWindow->setButton();
    requestFilter();
    mainWindow->setSaved(false);
}

const std::vector<const Media::AbstractMedia*> Controller::requestData() const {
    return cache;
}

void Controller::requestEditItem(const Media::AbstractMedia* media) {
    editWidget = new View::EditWidget(this,media);
    editWidget->show();
}

unsigned int Controller::requestNextID() {
    return repository->getNextID();
}

void Controller::requestSaveAs(const std::string path) {
    if(path.empty() || repository == nullptr)
        return;
    repository->setPath(path);
    repository->store();
    mainWindow->setSaved(true);
}

void Controller::requestLoad(const std::string path) {
    if(path.empty())
        return;
    if(repository != nullptr) {
        delete repository;
        delete reader;
        delete converter;
        delete data_mapper;
    }

    reader = new Media::Converter::Json::JsonReader;
    converter = new Media::Converter::Json::Json(*reader);
    data_mapper= new Media::DataMapper::JsonFile(path, *converter);
    repository = new Media::Repository::JsonRepository(*data_mapper);
    refreshCache();
    repository->setID(repository->getSize()-1);
    requestFilter();
}

void Controller::requestEmptyDataset() {
    delete repository;
    delete reader;
    delete converter;
    delete data_mapper;

    reader = new Media::Converter::Json::JsonReader;
    converter = new Media::Converter::Json::Json(*reader);
    data_mapper= new Media::DataMapper::JsonFile("", *converter);
    repository = new Media::Repository::JsonRepository(*data_mapper);
    cache.clear();
    refreshCache();
    requestFilter();
    mainWindow->setSaved(true);
}

void Controller::requestRemoveItem(const Media::AbstractMedia *item) {
    repository->remove(item->getID());
    refreshCache();
    mainWindow->setButton();
    requestFilter();
    mainWindow->setSaved(false);
}

void Controller::requestFilter() {
    filteredBookView = new View::ItemRender::Grid();
    filteredFilmView = new View::ItemRender::Grid();
    filteredSongView = new View::ItemRender::Grid();

    View::ItemRender::FilterRender filter;
    for(std::vector<const Media::AbstractMedia*>::const_iterator it = cache.begin();
        it != cache.end();
        it++)
    {
        (*it)->accept(filter);
    }

    booklist = filter.getBooks();
    filmlist = filter.getFilms();
    songlist = filter.getSongs();

    mainWindow->setBookView(filteredBookView);
    mainWindow->setFilmView(filteredFilmView);
    mainWindow->setSongView(filteredSongView);

    for(auto item : filmlist) {
        qDebug() << QString::fromStdString(item->getTitle()) + QString::number(item->getID());
    }

    filteredBookView->displayData(booklist);
    filteredFilmView->displayData(filmlist);
    filteredSongView->displayData(songlist);

    mainWindow->displayMedia(booklist, filmlist, songlist);
}

void Controller::requestSearch(std::string &query) {
    std::vector<const Media::AbstractMedia*> results;
    search(results, query);
}

void Controller::search(std::vector<const Media::AbstractMedia*>& results, const std::string &query) {
    std::string lowercaseQuery = query;
    std::transform (lowercaseQuery.begin(), lowercaseQuery.end(), lowercaseQuery.begin(), [](unsigned char c) {return std::tolower(c);});
    for(std::vector<const Media::AbstractMedia*>::const_iterator it = cache.begin();
        it != cache.end();
        it++
        )
    {
        std::string lowercaseTitle = (*it)->getTitle();
        std::transform (lowercaseTitle.begin(), lowercaseTitle.end(), lowercaseTitle.begin(), [](unsigned char c) {return std::tolower(c);});
        if(lowercaseTitle.find(lowercaseQuery) != std::string::npos) {
            results.push_back(*it);
        }
    }
}

unsigned int Controller::getSize() {
    return cache.size();
}

void Controller::requestSave() {
    if((repository->getPath()).empty() || repository == nullptr) {
        return;
    }
    repository->store();
    mainWindow->setSaved(true);
}
}
