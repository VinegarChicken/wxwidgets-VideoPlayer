#pragma once
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/filedlg.h>
#include <wx/mediactrl.h>
#include <wx/slider.h>
#include <wx/msgout.h>
#include <cmath>


class VideoPlayerFrame
{
public:
    VideoPlayerFrame(const wxString& filename, wxFrame* parent);
    ~VideoPlayerFrame();
    bool Play();
    bool Pause();
    bool Stop();
    unsigned long long getVideoPosition();
    bool setVideoPosition(unsigned long long pos);
    bool loadFile(wxString filePath);
    wxMediaCtrl* getMediaCtrl(){return media;};
    unsigned long long getVideoLength();
    bool setVideospeed(double speed);
    double getVideospeed(); [[maybe_unused]]
    bool SetVolume(double vol);
    double GetVolume();
    bool isPaused();
    wxSize getBestSize();


private:
    wxMediaCtrl* media;
    wxSlider* slider;
    int mediaLength, currentPos;
    std::string filePath;
    wxTimer* timer = new wxTimer();
    wxMenuBar *menuBar;



};