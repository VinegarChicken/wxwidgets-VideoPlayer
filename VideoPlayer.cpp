#include "VideoPlayer.h"
#include "main.h"

VideoPlayerFrame::VideoPlayerFrame(const wxString& filename, wxFrame* parent)
{
    media = new wxMediaCtrl(parent, wxID_MEDIACTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxMC_NO_AUTORESIZE);
    this->loadFile(filename);
}

bool VideoPlayerFrame::loadFile(wxString filePath) {
    return media->Load(filePath);
}

bool VideoPlayerFrame::Pause() {
    return media->Pause();
}

bool VideoPlayerFrame::Stop() {
    return media->Stop();
}
bool VideoPlayerFrame::SetVolume(double vol) {
    return media->SetVolume(vol);
}

double VideoPlayerFrame::GetVolume() {
    return media->GetVolume();
}


unsigned long long VideoPlayerFrame::getVideoPosition() {
    return media->Tell();
}

bool VideoPlayerFrame::setVideoPosition(unsigned long long pos) {
    return media->Seek(pos);
}

bool VideoPlayerFrame::Play() {
    return media->Play();
}

unsigned long long VideoPlayerFrame::getVideoLength() {
    return media->Length();
}

VideoPlayerFrame::~VideoPlayerFrame() {
    delete media;
}

bool VideoPlayerFrame::setVideospeed(double speed) {
    return media->SetPlaybackRate(speed);
}

wxSize VideoPlayerFrame::getBestSize(){
    return media->GetBestSize();
}

double VideoPlayerFrame::getVideospeed() {
    return media->GetPlaybackRate();
}

bool VideoPlayerFrame::isPaused(){
    return media->GetState() == wxMEDIASTATE_PAUSED;
}


