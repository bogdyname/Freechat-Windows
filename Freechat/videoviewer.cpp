/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "videoviewer.h"
#include "multimedia.h"

Videoviewer::Videoviewer()
{


    playlist = new QMediaPlaylist(player);
    playlist->addMedia(QUrl("http://example.com/Video.mp4"));

    videoWidget = new QVideoWidget;
    player->setVideoOutput(videoWidget);

    Video->show();
    playlist->setCurrentIndex(1);
    player->play();
}
