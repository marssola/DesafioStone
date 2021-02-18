#include "spotifywidget.h"
#include <QStyle>
#include <QApplication>
#include <QDesktopWidget>

SpotifyWidget::SpotifyWidget(QWidget *parent) :
    QStackedWidget(parent),
    m_spotifyUI(std::make_unique<SpotifyUI>(this))
{
    constexpr auto width = 800;
    constexpr auto height = 600;

    resize(width, height);

    setObjectName(QStringLiteral("StackWidget"));
    setWindowTitle(QStringLiteral("Spotify Qt - Widget"));

    setGeometry(QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    size(),
                    QApplication::desktop()->availableGeometry(this)
                ));

    addWidget(m_spotifyUI.get());
    setCurrentWidget(m_spotifyUI.get());
}
