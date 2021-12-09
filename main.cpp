#include "main.h"
#include "VideoPlayer.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(VideoPlayer);
bool VideoPlayer::OnInit()
{
    VideoPlayerWindow *frame = new VideoPlayerWindow(this->argc, this->argv);
    frame->Show(true);
    return true;
}