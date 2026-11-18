#include "Json.h"
#include "JsonVisitor.h"

namespace Media::Converter::Json {

Json::Json(MReader& reader) : reader(reader) {}

const MReader& Json::getReader() const {
    return reader;
}

QJsonObject Json::fromObj(const AbstractMedia& item) const {
    JsonVisitor json_visitor;
    item.accept(json_visitor);
    return json_visitor.getObj();
}

AbstractMedia* Json::toObj(const QJsonObject& json) const {
    return reader.read(json);
}

} // Media::Converter::Json
