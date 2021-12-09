#pragma once
#include <wx/wx.h>


enum
{
    ID_FILE,
    wxID_MEDIACTRL,
    TIMER_ID,
    ID_MEDIACTRL_SLIDER,
    ID_MEDIACTRL_CHANGE_SPEED,
    ID_MEDIACTRL_VOLUME,
    ID_INFO,
    ID_PLAY,
    ID_PAUSE,
    ID_STOP,
    ID_FRAME,
    ID_EXIT,
    ID_ISLOOPING
};

class VideoPlayer : public wxApp
{
public:
    virtual bool OnInit();
};