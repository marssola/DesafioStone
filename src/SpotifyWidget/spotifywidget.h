#pragma once

#include <QStackedWidget>
#include "spotifyui.h"
#include <memory>

class SpotifyWidget : public QStackedWidget
{
    Q_OBJECT

public:
    SpotifyWidget(QWidget *parent = nullptr);
    ~SpotifyWidget() = default;

private:
    std::unique_ptr<SpotifyUI> m_spotifyUI;
};
