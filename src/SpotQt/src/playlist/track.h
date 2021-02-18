#pragma once

#include <QObject>

class Track : public QObject
{
    Q_PROPERTY(int id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString playlistName READ getPlaylistName WRITE setPlaylistName NOTIFY playlistNameChanged)
    Q_PROPERTY(QString track READ getTrack WRITE setTrack NOTIFY trackChanged)
    Q_PROPERTY(QString artist READ getArtist WRITE setArtist NOTIFY artistChanged)
    Q_PROPERTY(QString previewUrl READ getPreviewUrl WRITE setPreviewUrl NOTIFY previewUrlChanged)
    Q_PROPERTY(QString image READ getImage WRITE setImage NOTIFY imageChanged)
    Q_OBJECT

public:
    explicit Track(QObject *parent = nullptr);
    ~Track() = default;

    int getId() const;
    QString getPlaylistName() const;
    QString getTrack() const;
    QString getPreviewUrl() const;
    QString getImage() const;
    QString getArtist() const;

public slots:
    void setId(int id);
    void setPlaylistName(const QString& name);
    void setTrack(const QString& track);
    void setPreviewUrl(const QString& previewUrl);
    void setImage(const QString &image);
    void setArtist(const QString &artist);

signals:
    void idChanged();
    void playlistNameChanged();
    void trackChanged();
    void previewUrlChanged();
    void imageChanged();
    void artistChanged();

private:
    int m_id;
    QString m_playlistName;
    QString m_track;
    QString m_artist;
    QString m_previewUrl;
    QString m_image;
};

