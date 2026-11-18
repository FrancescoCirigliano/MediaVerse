#include "SongEditor.h"
#include <QFormLayout>
#include <QLabel>
#include <QTimeEdit>
#include "../../Media/Song.h"

namespace View::ItemEditor {

SongEditor::SongEditor(QWidget *parent): View::ItemEditor::AbstractItemEditor(parent) {
        QFormLayout* form = new QFormLayout(this);
        QHBoxLayout* hbox = new QHBoxLayout();

        format = new QComboBox();
        QLabel* formatLabel = new QLabel("FORMAT");
        format->addItem("MP3"); format->addItem("WAW"); format->addItem("FLAC");
        lossless = new QCheckBox();
        lossless->setEnabled(false);

        hbox->addWidget(format);
        hbox->addWidget(lossless);

        form->addRow(formatLabel, hbox);

        author = new QLineEdit();
        QLabel* authorLabel = new QLabel("AUTHOR");
        form->addRow(authorLabel, author);

        album = new QLineEdit();;
        QLabel* albumLabel = new QLabel("ALBUM");
        form->addRow(albumLabel, album);

        duration = new QTimeEdit();
        duration->setDisplayFormat("mm:ss");

        QLabel* durationLabel = new QLabel("DURATION (mm:ss):");
        form->addRow(durationLabel, duration);

        bitrate = new QSpinBox();
        QLabel* bitrateLabel = new QLabel("BITRATE");
        bitrate->setMaximum(320);
        bitrate->setMinimum(32);
        form->addRow(bitrateLabel, bitrate);

        connect(format, &QComboBox::currentIndexChanged, [=](int index) {
            if(index == 0) {
                bitrate->setMaximum(320);
                bitrate->setMinimum(32);
                lossless->setChecked(false);
            }
            else if(index == 1) {
                bitrate->setMaximum(1411);
                bitrate->setMinimum(1000);
                lossless->setChecked(true);
            }
            else if(index == 2) {
                bitrate->setMaximum(5000);
                bitrate->setMinimum(500);
                lossless->setChecked(true);
            }
        });
}

SongEditor::~SongEditor() = default;

Media::AbstractMedia *SongEditor::create(unsigned int id, const QString &title, const unsigned int releaseYear, const QString &image_path, const QString &category, const bool completed) const {
    QTime durationTime = duration->time();
    float durationSeconds = QTime(0,0,0).secsTo(durationTime);
    return new Media::Song(
                id,
                title.toStdString(),
                releaseYear,
                image_path.toStdString(),
                category.toStdString(),
                completed,
                static_cast<Media::Song::format>(format->currentIndex()),
                author->text().toStdString(),
                album->text().toStdString(),
                durationSeconds,
                bitrate->value(),
                lossless->QAbstractButton::isChecked()
                );
}

void SongEditor::setValues(const Media::Song &song){
    format->setCurrentIndex(song.getFormat());
    lossless->setEnabled(song.isLossLess());
    author->setText(QString::fromStdString(song.getAuthor()));
    album->setText(QString::fromStdString(song.getAlbum()));
    float durationSeconds = song.getDuration();
    QTime durationTime = QTime::fromMSecsSinceStartOfDay(static_cast<int>(durationSeconds)*1000);
    duration->setTime(durationTime);
    bitrate->setValue(song.getBitrate());
}

} // View::ItemEditor
