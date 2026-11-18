#include "Full.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QFile>
#include <QScrollArea>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QTime>
#include <QtSvg/QSvgRenderer>

#include "../../Media/Book.h"
#include "../../Media/Film.h"
#include "../../Media/Song.h"

namespace View::ItemRender {

void Full::loadStyleSheet(){
    QFile file(":/assets/styles/detailed_style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        widget->setStyleSheet(styleSheet);
    }
}

Full::Full() {}

void Full::visit(const Media::Book &book) {
    widget = new QWidget();
    widget->setStyleSheet(" background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #667eea, stop:1 #764ba2);");

    QVBoxLayout* mainLayout = new QVBoxLayout(widget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    mainLayout->addStretch();

    QWidget* detailCard = new QWidget();
    detailCard->setObjectName("DetailCard");

    QVBoxLayout* cardLayout = new QVBoxLayout(detailCard);
    cardLayout->setContentsMargins(40, 40, 40, 40);
    cardLayout->setSpacing(30);

    QHBoxLayout* headerLayout = new QHBoxLayout();
    headerLayout->setSpacing(40);

    QLabel* CoverLabel = new QLabel();
    CoverLabel->setObjectName("CoverLabel");
    CoverLabel->setFixedSize(280, 400);

    CoverLabel->setAlignment(Qt::AlignCenter);

    QPixmap coverPixmap(QString::fromStdString(book.getImagePath()));

    if (coverPixmap.isNull()) {
        CoverLabel->setText(QString::fromStdString(book.getTitle()));
    } else {
        CoverLabel->setPixmap(coverPixmap.scaled(280, 400, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    }

    QGraphicsDropShadowEffect* coverShadow = new QGraphicsDropShadowEffect(detailCard);
    coverShadow->setBlurRadius(30);
    coverShadow->setColor(QColor(0, 0, 0, 80));
    coverShadow->setOffset(0, 10);
    CoverLabel->setGraphicsEffect(coverShadow);
    headerLayout->addWidget(CoverLabel);

    QWidget* infoContainer = new QWidget();
    QVBoxLayout* infoLayout = new QVBoxLayout(infoContainer);
    infoLayout->setContentsMargins(0, 0, 0, 0);

    infoContainer->setMinimumWidth(500);

    QLabel* bookTitleLabel = new QLabel(QString::fromStdString(book.getTitle()));
    bookTitleLabel->setObjectName("TitleLabel");
    bookTitleLabel->setWordWrap(true);

    QLabel* bookAuthorLabel = new QLabel("di " + QString::fromStdString(book.getTitle()));
    bookAuthorLabel->setObjectName("AuthorLabel");

    infoLayout->addWidget(bookTitleLabel);
    infoLayout->addWidget(bookAuthorLabel);

    QLabel* StatusIndicator = new QLabel();
    StatusIndicator->setObjectName("StatusIndicator");

    if (book.getCompleted()) {
        StatusIndicator->setText("Read");
        StatusIndicator->setProperty("isRead", true);
    } else {
        StatusIndicator->setText("Unread");
        StatusIndicator->setProperty("isRead", false);
    }

    infoLayout->addWidget(StatusIndicator, 0, Qt::AlignLeft);
    infoLayout->addStretch();

    QGridLayout* metaLayout = new QGridLayout();
    metaLayout->setSpacing(20);

    QWidget* yearItem = new QWidget();
    yearItem->setObjectName("MetaItem");
    QVBoxLayout* yearLayout = new QVBoxLayout(yearItem);
    QLabel* yearLabel = new QLabel("Year of Publication", yearItem);
    yearLabel->setProperty("class", "MetaLabel");
    QLabel* yearValue = new QLabel(QString::number(book.get_release_year()), yearItem);
    yearValue->setProperty("class", "MetaValue");
    yearLayout->addWidget(yearLabel);
    yearLayout->addWidget(yearValue);
    metaLayout->addWidget(yearItem, 0, 0);

    QWidget* categoryItem = new QWidget();
    categoryItem->setObjectName("MetaItem");
    QVBoxLayout* categoryLayout = new QVBoxLayout(categoryItem);
    QLabel* categoryLabel = new QLabel("Category", categoryItem);
    categoryLabel->setProperty("class", "MetaLabel");
    QLabel* genreValue = new QLabel(QString::fromStdString(book.getCategory()), categoryItem);
    genreValue->setProperty("class", "MetaValue");
    categoryLayout->addWidget(categoryLabel);
    categoryLayout->addWidget(genreValue);
    metaLayout->addWidget(categoryItem, 0, 1);

    QWidget* pagesItem = new QWidget();
    pagesItem->setObjectName("MetaItem");
    QVBoxLayout* pagesLayout = new QVBoxLayout(pagesItem);
    QLabel* pagesLabel = new QLabel("Pages", pagesItem);
    pagesLabel->setProperty("class", "MetaLabel");
    QLabel* pagesValue = new QLabel(QString::number(book.getPages()), pagesItem);
    pagesValue->setProperty("class", "MetaValue");
    pagesLayout->addWidget(pagesLabel);
    pagesLayout->addWidget(pagesValue);
    metaLayout->addWidget(pagesItem, 1, 0);

    QWidget* editorItem = new QWidget();
    editorItem->setObjectName("MetaItem");
    QVBoxLayout* editorLayout = new QVBoxLayout(editorItem);
    QLabel* editorLabel = new QLabel("Editor", editorItem);
    editorLabel->setProperty("class", "MetaLabel");
    QLabel* editorValue = new QLabel(QString::fromStdString(book.getEditor()), editorItem);
    editorValue->setProperty("class", "MetaValue");
    editorLayout->addWidget(editorLabel);
    editorLayout->addWidget(editorValue);
    metaLayout->addWidget(editorItem, 1, 1);

    QWidget* isbnItem = new QWidget();
    isbnItem->setObjectName("MetaItem");
    QVBoxLayout* isbnLayout = new QVBoxLayout(isbnItem);
    QLabel* isbnLabel = new QLabel("ISBN", isbnItem);
    isbnLabel->setProperty("class", "MetaLabel");
    QLabel* isbnValue = new QLabel(QString::fromStdString(book.getISBN()), isbnItem);
    isbnValue->setProperty("class", "MetaValue");
    isbnLayout->addWidget(isbnLabel);
    isbnLayout->addWidget(isbnValue);
    metaLayout->addWidget(isbnItem, 2, 0, 1, 2);

    infoLayout->addLayout(metaLayout);
    headerLayout->addWidget(infoContainer);

    QWidget* descriptionSection = new QWidget();
    QVBoxLayout* descriptionLayout = new QVBoxLayout(descriptionSection);

    QLabel* sectionTitle = new QLabel("Description");
    sectionTitle->setObjectName("SectionTitleLabel");

    QLabel* descriptionContentLabel = new QLabel(QString::fromStdString(book.getDescription()));
    descriptionContentLabel->setObjectName("DescriptionLabel");
    descriptionContentLabel->setWordWrap(true);

    descriptionLayout->addWidget(sectionTitle);
    descriptionLayout->addWidget(descriptionContentLabel);

    cardLayout->addLayout(headerLayout);
    cardLayout->addWidget(descriptionSection);

    QHBoxLayout* cardAreaLayout = new QHBoxLayout();
    cardAreaLayout->setContentsMargins(30, 20, 30, 20);

    cardAreaLayout->addStretch();
    cardAreaLayout->addWidget(detailCard);
    cardAreaLayout->addStretch();

    mainLayout->addLayout(cardAreaLayout);

    mainLayout->addStretch();

    loadStyleSheet();
}

void Full::visit(const Media::Film &film) {
    widget = new QWidget();

    QVBoxLayout* mainLayout = new QVBoxLayout(widget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    mainLayout->addStretch();

    QWidget* detailCard = new QWidget();
    detailCard->setObjectName("DetailCard");

    QVBoxLayout* cardLayout = new QVBoxLayout(detailCard);
    cardLayout->setContentsMargins(40, 40, 40, 40);
    cardLayout->setSpacing(30);

    QHBoxLayout* headerLayout = new QHBoxLayout();
    headerLayout->setSpacing(40);

    QLabel* CoverLabel = new QLabel(QString::fromStdString(film.getTitle()));
    CoverLabel->setObjectName("CoverLabel");
    CoverLabel->setFixedSize(280, 400);

    CoverLabel->setAlignment(Qt::AlignCenter);

    QPixmap coverPixmap(QString::fromStdString(film.getImagePath()));

    if (coverPixmap.isNull()) {
        CoverLabel->setText(QString::fromStdString(film.getTitle()));
    } else {
        CoverLabel->setPixmap(coverPixmap.scaled(280, 400, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    }

    QGraphicsDropShadowEffect* coverShadow = new QGraphicsDropShadowEffect(detailCard);
    coverShadow->setBlurRadius(30);
    coverShadow->setColor(QColor(0, 0, 0, 80));
    coverShadow->setOffset(0, 15);
    CoverLabel->setGraphicsEffect(coverShadow);
    headerLayout->addWidget(CoverLabel);

    QWidget* infoContainer = new QWidget();
    QVBoxLayout* infoLayout = new QVBoxLayout(infoContainer);
    infoLayout->setContentsMargins(0, 0, 0, 0);

    infoContainer->setMinimumWidth(500);

    QLabel* filmTitleLabel = new QLabel(QString::fromStdString(film.getTitle()));
    filmTitleLabel->setObjectName("TitleLabel");
    filmTitleLabel->setWordWrap(true);

    QLabel* filmDirectorLabel = new QLabel("di " + QString::fromStdString(film.getDirector()));
    filmDirectorLabel->setObjectName("AuthorLabel");

    infoLayout->addWidget(filmTitleLabel);
    infoLayout->addWidget(filmDirectorLabel);

    QLabel* StatusIndicator = new QLabel();
    StatusIndicator->setObjectName("StatusIndicator");

    if (film.getCompleted()) {
        StatusIndicator->setText("Watched");
        StatusIndicator->setProperty("isRead", true);
    } else {
        StatusIndicator->setText("Not Watched");
        StatusIndicator->setProperty("isRead", false);
    }

    infoLayout->addWidget(StatusIndicator, 0, Qt::AlignLeft);
    infoLayout->addStretch();

    QGridLayout* metaLayout = new QGridLayout();
    metaLayout->setSpacing(20);

    QWidget* yearItem = new QWidget();
    yearItem->setObjectName("MetaItem");
    QVBoxLayout* yearLayout = new QVBoxLayout(yearItem);
    QLabel* yearLabel = new QLabel("Year of realese", yearItem);
    yearLabel->setProperty("class", "MetaLabel");
    QLabel* yearValue = new QLabel(QString::number(film.get_release_year()), yearItem);
    yearValue->setProperty("class", "MetaValue");
    yearLayout->addWidget(yearLabel);
    yearLayout->addWidget(yearValue);
    metaLayout->addWidget(yearItem, 0, 0);

    QWidget* categoryItem = new QWidget();
    categoryItem->setObjectName("MetaItem");
    QVBoxLayout* categoryLayout = new QVBoxLayout(categoryItem);
    QLabel* categoryLabel = new QLabel("Category", categoryItem);
    categoryLabel->setProperty("class", "MetaLabel");
    QLabel* genreValue = new QLabel(QString::fromStdString(film.getCategory()), categoryItem);
    genreValue->setProperty("class", "MetaValue");
    categoryLayout->addWidget(categoryLabel);
    categoryLayout->addWidget(genreValue);
    metaLayout->addWidget(categoryItem, 0, 1);

    QWidget* durationItem = new QWidget();
    durationItem->setObjectName("MetaItem");
    QVBoxLayout* durationLayout = new QVBoxLayout(durationItem);
    QLabel* durationLabel = new QLabel("Duration", durationItem);
    durationLabel->setProperty("class", "MetaLabel");
    QLabel* durationValue = new QLabel(QString::number(film.getDuration()) + " min", durationItem);
    durationValue->setProperty("class", "MetaValue");
    durationLayout->addWidget(durationLabel);
    durationLayout->addWidget(durationValue);
    metaLayout->addWidget(durationItem, 1, 0);

    QWidget* directorItem = new QWidget();
    directorItem->setObjectName("MetaItem");
    QVBoxLayout* directorLayout = new QVBoxLayout(directorItem);
    QLabel* directorLabel = new QLabel("Directed by", directorItem);
    directorLabel->setProperty("class", "MetaLabel");
    QLabel* directorValue = new QLabel(QString::fromStdString(film.getDirector()), directorItem);
    directorValue->setProperty("class", "MetaValue");
    directorLayout->addWidget(directorLabel);
    directorLayout->addWidget(directorValue);
    metaLayout->addWidget(directorItem, 1, 1);

    QWidget* qualityItem = new QWidget();
    qualityItem->setObjectName("MetaItem");
    QVBoxLayout* qualityLayout = new QVBoxLayout(qualityItem);
    QLabel* qualityLabel = new QLabel("Video Quality", qualityItem);
    qualityLabel->setProperty("class", "MetaLabel");
    unsigned int quality = film.getQuality();
    QLabel* qualityValue = new QLabel();

    if(quality == Media::Film::HD){
        qualityValue->setText("HD");
    } else if (quality == Media::Film::FullHD) {
        qualityValue->setText("FullHD");
    } else if (quality == Media::Film::UltraHD) {
        qualityValue->setText("UltraHD");
    }

    qualityValue->setProperty("class", "MetaValue");
    qualityLayout->addWidget(qualityLabel);
    qualityLayout->addWidget(qualityValue);
    metaLayout->addWidget(qualityItem, 2, 0, 1, 2);

    infoLayout->addLayout(metaLayout);
    headerLayout->addWidget(infoContainer);

    QWidget* castSection = new QWidget();
    castSection->setObjectName("cast-section");
    QVBoxLayout* castSectionLayout = new QVBoxLayout(castSection);
    castSectionLayout->setContentsMargins(0, 0, 0, 0);
    castSectionLayout->setSpacing(20);

    QLabel* castTitleLabel = new QLabel("Cast");
    castTitleLabel->setObjectName("castTitle");
    castSectionLayout->addWidget(castTitleLabel);

    QWidget* castListContainer = new QWidget();
    QHBoxLayout* castListLayout = new QHBoxLayout(castListContainer);
    castListLayout->setContentsMargins(0, 0, 0, 0);
    castListLayout->setSpacing(25);

    const QString svgIconData = R"(<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="currentColor"><path d="M12 2C6.48 2 2 6.48 2 12s4.48 10 10 10 10-4.48 10-10S17.52 2 12 2zm0 4c1.93 0 3.5 1.57 3.5 3.5S13.93 13 12 13s-3.5-1.57-3.5-3.5S10.07 6 12 6zm0 14c-2.03 0-4.43-.82-6.14-2.88C7.55 15.8 9.68 15 12 15s4.45.8 6.14 2.12C16.43 19.18 14.03 20 12 20z"></path></svg>)";

    std::vector<std::string> actors = film.getActors();
    for (std::vector<std::string>::const_iterator it = actors.begin();
         it != actors.end();
         it++)
    {
        QWidget* actorWidget = new QWidget();
        actorWidget->setObjectName("actor");
        QVBoxLayout* actorLayout = new QVBoxLayout(actorWidget);
        actorLayout->setSpacing(10);
        actorLayout->setContentsMargins(0,0,0,0);

        QLabel* photoLabel = new QLabel();
        photoLabel->setObjectName("actor-photo");
        photoLabel->setFixedSize(80, 80);
        photoLabel->setAlignment(Qt::AlignCenter);

        QSvgRenderer renderer(QByteArray(svgIconData.toUtf8()));
        QPixmap pixmap(40, 40);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        renderer.render(&painter);
        photoLabel->setPixmap(pixmap);

        QLabel* nameLabel = new QLabel(QString::fromStdString(*it));
        nameLabel->setObjectName("actor-name");
        nameLabel->setAlignment(Qt::AlignCenter);
        nameLabel->setWordWrap(true);

        actorLayout->addWidget(photoLabel, 0, Qt::AlignCenter);
        actorLayout->addWidget(nameLabel);

        castListLayout->addWidget(actorWidget);
    }
    castListLayout->addStretch();
    castSectionLayout->addWidget(castListContainer);

    cardLayout->addLayout(headerLayout);
    cardLayout->addWidget(castSection);

    QHBoxLayout* cardAreaLayout = new QHBoxLayout();
    cardAreaLayout->setContentsMargins(30, 20, 30, 20);

    cardAreaLayout->addStretch();
    cardAreaLayout->addWidget(detailCard);
    cardAreaLayout->addStretch();

    mainLayout->addLayout(cardAreaLayout);
    mainLayout->addStretch();

    loadStyleSheet();
}

void Full::visit(const Media::Song &song) {
    widget = new QWidget();

    QVBoxLayout* mainLayout = new QVBoxLayout(widget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    mainLayout->addStretch();

    QWidget* detailCard = new QWidget();
    detailCard->setObjectName("DetailCard");

    QVBoxLayout* cardLayout = new QVBoxLayout(detailCard);
    cardLayout->setContentsMargins(40, 40, 40, 40);
    cardLayout->setSpacing(30);

    QHBoxLayout* headerLayout = new QHBoxLayout();
    headerLayout->setSpacing(40);

    QLabel* CoverLabel = new QLabel(QString::fromStdString(song.getTitle()));
    CoverLabel->setObjectName("CoverLabel");
    CoverLabel->setFixedSize(350, 350);

    CoverLabel->setAlignment(Qt::AlignCenter);

    QPixmap coverPixmap(QString::fromStdString(song.getImagePath()));

    if (coverPixmap.isNull()) {
        CoverLabel->setText(QString::fromStdString(song.getTitle()));
    } else {
        CoverLabel->setPixmap(coverPixmap.scaled(280, 400, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    }

    QGraphicsDropShadowEffect* coverShadow = new QGraphicsDropShadowEffect(detailCard);
    coverShadow->setBlurRadius(30);
    coverShadow->setColor(QColor(0, 0, 0, 80));
    coverShadow->setOffset(0, 15);
    CoverLabel->setGraphicsEffect(coverShadow);
    headerLayout->addWidget(CoverLabel);

    QWidget* infoContainer = new QWidget();
    QVBoxLayout* infoLayout = new QVBoxLayout(infoContainer);
    infoLayout->setContentsMargins(0, 0, 0, 0);

    infoContainer->setMinimumWidth(500);

    QLabel* TitleLabel = new QLabel(QString::fromStdString(song.getTitle()));
    TitleLabel->setObjectName("TitleLabel");
    TitleLabel->setWordWrap(true);

    QLabel* AuthorLabel = new QLabel("di " + QString::fromStdString(song.getAuthor()));
    AuthorLabel->setObjectName("AuthorLabel");

    infoLayout->addWidget(TitleLabel);
    infoLayout->addWidget(AuthorLabel);

    QLabel* StatusIndicator = new QLabel();
    StatusIndicator->setObjectName("StatusIndicator");

    if (song.getCompleted()) {
        StatusIndicator->setText("Listened");
        StatusIndicator->setProperty("isRead", true);
    } else {
        StatusIndicator->setText("Not listened to");
        StatusIndicator->setProperty("isRead", false);
    }

    infoLayout->addWidget(StatusIndicator, 0, Qt::AlignLeft);
    infoLayout->addStretch();

    QGridLayout* metaLayout = new QGridLayout();
    metaLayout->setSpacing(20);

    QWidget* yearItem = new QWidget();
    yearItem->setObjectName("MetaItem");
    QVBoxLayout* yearLayout = new QVBoxLayout(yearItem);
    QLabel* yearLabel = new QLabel("Year of release", yearItem);
    yearLabel->setProperty("class", "MetaLabel");
    QLabel* yearValue = new QLabel(QString::number(song.get_release_year()), yearItem);
    yearValue->setProperty("class", "MetaValue");
    yearLayout->addWidget(yearLabel);
    yearLayout->addWidget(yearValue);
    metaLayout->addWidget(yearItem, 0, 0);

    QWidget* categoryItem = new QWidget();
    categoryItem->setObjectName("MetaItem");
    QVBoxLayout* categoryLayout = new QVBoxLayout(categoryItem);
    QLabel* categoryLabel = new QLabel("Category", categoryItem);
    categoryLabel->setProperty("class", "MetaLabel");
    QLabel* genreValue = new QLabel(QString::fromStdString(song.getCategory()), categoryItem);
    genreValue->setProperty("class", "MetaValue");
    categoryLayout->addWidget(categoryLabel);
    categoryLayout->addWidget(genreValue);
    metaLayout->addWidget(categoryItem, 0, 1);

    QWidget* durationItem = new QWidget();
    durationItem->setObjectName("MetaItem");
    QVBoxLayout* durationLayout = new QVBoxLayout(durationItem);
    QLabel* durationLabel = new QLabel("Duration", durationItem);
    durationLabel->setProperty("class", "MetaLabel");
    QTime durationTime = QTime::fromMSecsSinceStartOfDay(static_cast<int>(song.getDuration())*1000);
    QString duration = durationTime.toString("mm:ss");
    QLabel* durationValue = new QLabel(duration + " min", durationItem);
    durationValue->setProperty("class", "MetaValue");
    durationLayout->addWidget(durationLabel);
    durationLayout->addWidget(durationValue);
    metaLayout->addWidget(durationItem, 1, 0);

    QWidget* albumItem = new QWidget();
    albumItem->setObjectName("MetaItem");
    QVBoxLayout* directorLayout = new QVBoxLayout(albumItem);
    QLabel* albumLabel = new QLabel("Album", albumItem);
    albumLabel->setProperty("class", "MetaLabel");
    QLabel* albumValue = new QLabel(QString::fromStdString(song.getAlbum()), albumItem);
    albumValue->setProperty("class", "MetaValue");
    directorLayout->addWidget(albumLabel);
    directorLayout->addWidget(albumValue);
    metaLayout->addWidget(albumItem, 1, 1);

    QWidget* formatItem = new QWidget();
    formatItem->setObjectName("MetaItem");
    QVBoxLayout* formatLayout = new QVBoxLayout(formatItem);
    QLabel* formaLabel = new QLabel("Audio Format", formatItem);
    formaLabel->setProperty("class", "MetaLabel");
    unsigned int quality = song.getFormat();
    QLabel* formatValue = new QLabel();

    if(quality == Media::Song::MP3){
        formatValue->setText("MP3");
    } else if (quality == Media::Song::WAW) {
        formatValue->setText("WAW");
    } else if (quality == Media::Song::FLAC) {
        formatValue->setText("FLAC");
    }

    formatValue->setProperty("class", "MetaValue");
    formatLayout->addWidget(formaLabel);
    formatLayout->addWidget(formatValue);
    metaLayout->addWidget(formatItem, 2, 0);

    QWidget* losslessItem = new QWidget();
    losslessItem->setObjectName("MetaItem");
    QVBoxLayout* losslessLayout = new QVBoxLayout(losslessItem);
    QLabel* losslessLabel = new QLabel("LossLess", losslessItem);
    formaLabel->setProperty("class", "MetaLabel");
    QCheckBox* losslessCheckBox = new QCheckBox();
    losslessCheckBox->setEnabled(false);
    losslessCheckBox->setObjectName("LosslessCheckbox");

    losslessCheckBox->setChecked(song.isLossLess());

    losslessLayout->addWidget(losslessLabel);
    losslessLayout->addWidget(losslessCheckBox, 0, Qt::AlignCenter);

    metaLayout->addWidget(losslessItem, 2, 1);

    infoLayout->addLayout(metaLayout);
    headerLayout->addWidget(infoContainer);

    cardLayout->addLayout(headerLayout);

    QHBoxLayout* cardAreaLayout = new QHBoxLayout();
    cardAreaLayout->setContentsMargins(30, 20, 30, 20);

    cardAreaLayout->addStretch();
    cardAreaLayout->addWidget(detailCard);
    cardAreaLayout->addStretch();

    mainLayout->addLayout(cardAreaLayout);
    mainLayout->addStretch();

    loadStyleSheet();
}

QWidget* Full::getWidget() const {
    return widget;
}
}
