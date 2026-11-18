#include "Card.h"
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTime>

#include "../../Media/Book.h"
#include "../../Media/Film.h"
#include "../../Media/Song.h"

namespace View::ItemRender {

Card::Card() : widget(nullptr) {}

void Card::visit(const Media::Book& book) {
    QFrame* cardFrame = new QFrame(0);
    cardFrame->setObjectName("CardWidget");

    QLabel* coverLabel = new QLabel();
    coverLabel->setObjectName("CardCover");
    coverLabel->setFixedSize(80, 120);
    coverLabel->setAlignment(Qt::AlignCenter);
    coverLabel->setWordWrap(true);

    QPixmap pixmap(QString::fromStdString(book.getImagePath()));
    bool imageIsMissing = pixmap.isNull();

    coverLabel->setProperty("imageMissing", imageIsMissing);
    coverLabel->setProperty("mediaType", "book");

    coverLabel->setPixmap(pixmap.scaled(coverLabel->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

    QLabel* titleLabel = new QLabel(QString::fromStdString(book.getTitle()));
    titleLabel->setObjectName("CardTitle");
    titleLabel->setWordWrap(true);

    QLabel* authorLabel = new QLabel(QString::fromStdString(book.getAuthor()));
    authorLabel->setObjectName("CardAuthor");

    QString metaInfoText = QString("%1 | %2 | %3 pag.").arg(book.get_release_year()).arg(QString::fromStdString(book.getCategory())).arg(book.getPages());
    QLabel* metaInfoLabel = new QLabel(metaInfoText);
    metaInfoLabel->setWordWrap(true);
    metaInfoLabel->setObjectName("CardMetaInfo");

    QLabel* statusDotLabel = new QLabel();
    statusDotLabel->setObjectName("CardStatusDot");
    statusDotLabel->setProperty("read", book.getCompleted());


    QLabel* statusTextLabel = new QLabel(book.getCompleted() ? "Letto" : "Non Letto");
    statusTextLabel->setObjectName("CardStatusText");

    QVBoxLayout* infoTextLayout = new QVBoxLayout();
    infoTextLayout->setSpacing(4);
    infoTextLayout->setContentsMargins(0, 0, 0, 0);
    infoTextLayout->addWidget(titleLabel);
    infoTextLayout->addWidget(authorLabel);
    infoTextLayout->addWidget(metaInfoLabel);
    infoTextLayout->addStretch();

    QHBoxLayout* headerLayout = new QHBoxLayout();
    headerLayout->setSpacing(15);
    headerLayout->addWidget(coverLabel);
    headerLayout->addLayout(infoTextLayout, 1);

    QHBoxLayout* statusLayout = new QHBoxLayout();
    statusLayout->setObjectName("CardStatusLayout");
    statusLayout->setSpacing(8);
    statusLayout->setContentsMargins(0, 0, 0, 0);
    statusLayout->setAlignment(Qt::AlignLeft);
    statusLayout->addWidget(statusDotLabel);
    statusLayout->addWidget(statusTextLabel);
    statusLayout->addStretch();

    QVBoxLayout* mainLayout = new QVBoxLayout(cardFrame);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);
    mainLayout->addLayout(headerLayout);
    mainLayout->addLayout(statusLayout);

    cardFrame->setMinimumSize(280, 195);
    this->widget = cardFrame;
}


void Card::visit(const Media::Film& film) {
    QFrame* cardFrame = new QFrame();
    cardFrame->setObjectName("CardWidget");

    QLabel* coverLabel = new QLabel();
    coverLabel->setObjectName("CardCover");
    coverLabel->setFixedSize(80, 120);
    coverLabel->setAlignment(Qt::AlignCenter);
    coverLabel->setWordWrap(true);

    QPixmap pixmap(QString::fromStdString(film.getImagePath()));
    bool imageIsMissing = pixmap.isNull();

    coverLabel->setProperty("imageMissing", imageIsMissing);
    coverLabel->setProperty("mediaType", "film");

    coverLabel->setPixmap(pixmap.scaled(coverLabel->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

    QLabel* titleLabel = new QLabel(QString::fromStdString(film.getTitle()));
    titleLabel->setObjectName("CardTitle");
    titleLabel->setWordWrap(true);

    QLabel* authorLabel = new QLabel(QString::fromStdString(film.getDirector()));
    authorLabel->setObjectName("CardAuthor");

    QString metaInfoText = QString("%1 | %2 | %3 min").arg(QString::number(film.get_release_year())).arg(QString::fromStdString(film.getCategory())).arg(QString::number(film.getDuration()));
    QLabel* metaInfoLabel = new QLabel(metaInfoText);
    metaInfoLabel->setWordWrap(true);
    metaInfoLabel->setObjectName("CardMetaInfo");

    QLabel* statusDotLabel = new QLabel();
    statusDotLabel->setObjectName("CardStatusDot");
    statusDotLabel->setProperty("read", film.getCompleted());
    QLabel* statusTextLabel = new QLabel(film.getCompleted() ? "Visto" : "Non Visto");
    statusTextLabel->setObjectName("CardStatusText");


    QVBoxLayout* infoTextLayout = new QVBoxLayout();
    infoTextLayout->setSpacing(4);
    infoTextLayout->setContentsMargins(0, 0, 0, 0);
    infoTextLayout->addWidget(titleLabel);
    infoTextLayout->addWidget(authorLabel);
    infoTextLayout->addWidget(metaInfoLabel);
    infoTextLayout->addStretch();

    QHBoxLayout* headerLayout = new QHBoxLayout();
    headerLayout->setSpacing(15);
    headerLayout->addWidget(coverLabel);
    headerLayout->addLayout(infoTextLayout, 1);

    QHBoxLayout* statusLayout = new QHBoxLayout();
    statusLayout->setObjectName("CardStatusLayout");
    statusLayout->setSpacing(8);
    statusLayout->setContentsMargins(0, 0, 0, 0);
    statusLayout->setAlignment(Qt::AlignLeft);
    statusLayout->addWidget(statusDotLabel);
    statusLayout->addWidget(statusTextLabel);
    statusLayout->addStretch();

    QVBoxLayout* mainLayout = new QVBoxLayout(cardFrame);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(0);

    mainLayout->addLayout(headerLayout);

    mainLayout->addSpacing(15);

    mainLayout->addLayout(statusLayout);

    cardFrame->setMinimumSize(280, 195);
    this->widget = cardFrame;
}

void Card::visit(const Media::Song& song) {
    QFrame* cardFrame = new QFrame(0);
    cardFrame->setObjectName("CardWidget");

    QLabel* coverLabel = new QLabel();
    coverLabel->setObjectName("CardCover");
    coverLabel->setFixedSize(90, 90);
    coverLabel->setAlignment(Qt::AlignCenter);
    coverLabel->setWordWrap(true);

    QPixmap pixmap(QString::fromStdString(song.getImagePath()));
    bool imageIsMissing = pixmap.isNull();

    coverLabel->setProperty("imageMissing", imageIsMissing);
    coverLabel->setProperty("mediaType", "song");

    coverLabel->setPixmap(pixmap.scaled(coverLabel->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

    QLabel* titleLabel = new QLabel(QString::fromStdString(song.getTitle()));
    titleLabel->setObjectName("CardTitle");
    titleLabel->setWordWrap(true);

    QLabel* authorLabel = new QLabel(QString::fromStdString(song.getAuthor()));
    authorLabel->setObjectName("CardAuthor");

    QTime durationTime = QTime::fromMSecsSinceStartOfDay(static_cast<int>(song.getDuration())*1000);
    QString duration = durationTime.toString("mm:ss");
    QString metaInfoText = QString("%1 | %2 | %3 min").arg(song.get_release_year()).arg(QString::fromStdString(song.getCategory())).arg(duration);
    QLabel* metaInfoLabel = new QLabel(metaInfoText);
    metaInfoLabel->setWordWrap(true);
    metaInfoLabel->setObjectName("CardMetaInfo");

    QLabel* statusDotLabel = new QLabel();
    statusDotLabel->setObjectName("CardStatusDot");
    statusDotLabel->setProperty("read", song.getCompleted());

    QLabel* statusTextLabel = new QLabel(song.getCompleted() ? "Ascoltato" : "Non ascoltato");
    statusTextLabel->setObjectName("CardStatusText");

    QVBoxLayout* infoTextLayout = new QVBoxLayout();
    infoTextLayout->setSpacing(4);
    infoTextLayout->setContentsMargins(0, 0, 0, 0);
    infoTextLayout->addWidget(titleLabel);
    infoTextLayout->addWidget(authorLabel);
    infoTextLayout->addWidget(metaInfoLabel);
    infoTextLayout->addStretch();

    QHBoxLayout* headerLayout = new QHBoxLayout();
    headerLayout->setSpacing(15);
    headerLayout->addWidget(coverLabel);
    headerLayout->addLayout(infoTextLayout, 1);

    QHBoxLayout* statusLayout = new QHBoxLayout();
    statusLayout->setObjectName("CardStatusLayout");
    statusLayout->setSpacing(8);
    statusLayout->setContentsMargins(0, 0, 0, 0);
    statusLayout->setAlignment(Qt::AlignLeft);
    statusLayout->addWidget(statusDotLabel);
    statusLayout->addWidget(statusTextLabel);
    statusLayout->addStretch();

    QVBoxLayout* mainLayout = new QVBoxLayout(cardFrame);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);
    mainLayout->addLayout(headerLayout);
    mainLayout->addLayout(statusLayout);

    cardFrame->setMinimumSize(280, 180);
    this->widget = cardFrame;

}

QWidget *Card::getWidget() const {
    return widget;
}
}
