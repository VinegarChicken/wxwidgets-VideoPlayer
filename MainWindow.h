#pragma once
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/filedlg.h>
#include <wx/mediactrl.h>
#include <wx/slider.h>
#include <wx/msgout.h>
#include <cmath>
#include <fstream>
#include "VideoPlayer.h"
#include "main.h"


class VideoPlayerWindow : public wxFrame
{
public:
    VideoPlayerWindow(int args, char** argv);
    void onOpen(wxCommandEvent& ev);
    void onMediaLoaded(wxCommandEvent& ev);
    void startVideoTimer(wxCommandEvent &ev);
    void onSliderMove(wxCommandEvent &ev);
    void onTimer(wxTimerEvent& tev);
    void onInfo(wxCommandEvent& ev);
    void onClick(wxMouseEvent& ev);
    void onPlay(wxCommandEvent& ev);
    void onPause(wxCommandEvent& ev);
    void onStop(wxCommandEvent& ev);
    void onSetSpeed(wxCommandEvent& ev);
    void onSetVol(wxCommandEvent& ev);
    void onFinished(wxCommandEvent &ev);

private:
    wxSlider* vidPosSlider;
    wxSlider* pbrateslider;
    wxSlider* volslider;
    int mediaLength, currentPos;
    std::string filePath;
    wxTimer* timer = new wxTimer(this, TIMER_ID);
    wxMenuBar *menuBar;
    VideoPlayerFrame* player;
    wxFlexGridSizer* sizer;
    //Play button Pause button and stop button description
    wxStaticText* ppsdesc;
    //Video speed description
    wxStaticText* speeddesc;
    //volume slider description
    wxStaticText* voldesc;
    //Current pos description
    wxStaticText* posdesc;
    wxMenu *menuSettings;
    wxMenu *menuFile;
    wxCheckBox* isLooping;

};