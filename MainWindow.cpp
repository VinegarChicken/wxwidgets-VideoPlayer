#include <iomanip>
#include "MainWindow.h"

std::ifstream::pos_type getFilesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}


VideoPlayerWindow::VideoPlayerWindow(int argc, char** argv)
        : wxFrame(nullptr, wxID_ANY, "Video Player", wxDefaultPosition, wxSize(1600, 800))
{
    player = new VideoPlayerFrame(wxEmptyString, this);
    menuFile = new wxMenu;
    menuSettings = new wxMenu;
    menuFile->Append(ID_FILE, "&Open File...\tCtrl-H",
                     "Open File");
    menuFile->AppendSeparator();
    //menuFile->Append(ID_EXIT);
    menuSettings->Append(ID_INFO, "View Video Information");
    menuSettings->Enable(ID_INFO, false);
    menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuSettings, "&Info");
    SetMenuBar( menuBar );
    Bind(wxEVT_MENU, &VideoPlayerWindow::onOpen, this, ID_FILE);
    Bind(wxEVT_MENU, &VideoPlayerWindow::onInfo, this, ID_INFO);
    Bind(wxEVT_SLIDER, &VideoPlayerWindow::onSliderMove, this, ID_MEDIACTRL_SLIDER);
    Bind(wxEVT_SLIDER, &VideoPlayerWindow::onSetSpeed, this, ID_MEDIACTRL_CHANGE_SPEED);
    Bind(wxEVT_SLIDER, &VideoPlayerWindow::onSetVol, this, ID_MEDIACTRL_VOLUME);
    Bind(wxEVT_LEFT_DOWN, &VideoPlayerWindow::onClick, this, wxID_MEDIACTRL);
    Bind(wxEVT_TIMER, &VideoPlayerWindow::onTimer, this, TIMER_ID);
    Bind(wxEVT_MEDIA_LOADED, &VideoPlayerWindow::onMediaLoaded, this, wxID_MEDIACTRL);
    Bind(wxEVT_MEDIA_PLAY, &VideoPlayerWindow::startVideoTimer, this, wxID_MEDIACTRL);
    Bind(wxEVT_MEDIA_FINISHED, &VideoPlayerWindow::onFinished, this, wxID_MEDIACTRL);
    Bind(wxEVT_BUTTON, &VideoPlayerWindow::onPlay, this, ID_PLAY);
    Bind(wxEVT_BUTTON, &VideoPlayerWindow::onPause, this, ID_PAUSE);
    Bind(wxEVT_BUTTON, &VideoPlayerWindow::onStop, this, ID_STOP);

    /*
     * TODO: Use Bind for this
     */
    player->getMediaCtrl()->Connect(wxID_MEDIACTRL, wxEVT_LEFT_DOWN, wxMouseEventHandler(VideoPlayerWindow::onClick), nullptr, this);

    CreateStatusBar();

    wxPanel* panel = new wxPanel(this);
    vidPosSlider = new wxSlider(panel, ID_MEDIACTRL_SLIDER, 0.0, 0.0, 1.0, wxPoint(300, 900), wxSize(700, 100));
    pbrateslider = new wxSlider(panel, ID_MEDIACTRL_CHANGE_SPEED, 100.0, 20.0, 300.0, wxPoint(300, 900), wxSize(700, 100));
    volslider = new wxSlider(panel, ID_MEDIACTRL_VOLUME, 100.0, 0.0, 100.0, wxPoint(300, 900), wxSize(700, 100));
    isLooping = new wxCheckBox(panel, ID_ISLOOPING, "Loop Video");
    posdesc = new wxStaticText(panel, wxID_ANY, "Current Position");
    speeddesc = new wxStaticText(panel, wxID_ANY, "Video Speed");
    voldesc = new wxStaticText(panel, wxID_ANY, "Video Volume");

    wxButton* playbtn = new wxButton(panel, ID_PLAY, "Play");
    playbtn->SetToolTip("Play Video");
    wxButton* pausebtn = new wxButton(panel, ID_PAUSE, "Pause");
    pausebtn->SetToolTip("Pause Video");
    wxButton* stopbtn = new wxButton(panel, ID_PAUSE, "Stop");
    pausebtn->SetToolTip("Stop Video");

    wxFlexGridSizer* ctrlSizer = new wxFlexGridSizer(2);
    ctrlSizer->AddGrowableCol(0);
    panel->SetSizer(ctrlSizer);


    wxBoxSizer* vertsizer = new wxBoxSizer(wxHORIZONTAL);
     ppsdesc  = new wxStaticText(panel, wxID_ANY, "Play/Pause/Stop buttons");
    ctrlSizer->Add(ppsdesc, 0, wxALIGN_CENTER, 5);
    ctrlSizer->AddStretchSpacer();
    vertsizer->Add(playbtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    vertsizer->Add(pausebtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    vertsizer->Add(stopbtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    ctrlSizer->Add(vertsizer, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    ctrlSizer->AddStretchSpacer();


    ctrlSizer->Add(isLooping, 0, wxALIGN_CENTER, 5);
    ctrlSizer->AddStretchSpacer();
    ctrlSizer->Add(posdesc, 0, wxALIGN_CENTER, 5);
    ctrlSizer->AddStretchSpacer();
    ctrlSizer->Add(vidPosSlider, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    ctrlSizer->AddStretchSpacer();

    ctrlSizer->Add(speeddesc, 0, wxALIGN_CENTER, 5);
    ctrlSizer->AddStretchSpacer();
    ctrlSizer->Add(pbrateslider, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    ctrlSizer->AddStretchSpacer();

    ctrlSizer->Add(voldesc, 0, wxALIGN_CENTER, 5);
    ctrlSizer->AddStretchSpacer();
    ctrlSizer->Add(volslider, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    //Mediactrl sizer
    sizer = new wxFlexGridSizer(2);
    sizer->AddGrowableCol(0);
    this->SetSizer(sizer);
    sizer->Add(player->getMediaCtrl(), wxSizerFlags().Expand().Border());
    sizer->Add(panel);
    sizer->AddGrowableRow(0);

    if(argc > 1){
        filePath = argv[1];
        player->loadFile(filePath);
         menuSettings->Enable(ID_INFO, true);
    }

}

void VideoPlayerWindow::onOpen(wxCommandEvent& event)
{
    wxFileDialog* openFileDialog = new wxFileDialog(this, "Open Media Files", "", "",
                                                     "", wxFD_OPEN);
    if (openFileDialog->ShowModal() == wxID_OK){
        filePath = openFileDialog->GetPath();
        player->loadFile(filePath);
         menuSettings->Enable(ID_INFO, true);
    }
}

void VideoPlayerWindow::startVideoTimer(wxCommandEvent &ev) {
    timer->Start(1);
}

void VideoPlayerWindow::onMediaLoaded(wxCommandEvent &ev) {
    player->Play();
}

void VideoPlayerWindow::onTimer(wxTimerEvent& tev) {
    currentPos = player->getVideoPosition() / 1000;
    mediaLength = player->getVideoLength() / 1000;
    std::string seconds;
    currentPos % 60 < 10 ? seconds = "0" + std::to_string(currentPos % 60) : seconds = std::to_string(currentPos % 60);
    vidPosSlider->SetValue(currentPos);
    vidPosSlider->SetMax(mediaLength);
    posdesc->SetLabel(wxString("Video Position: " + std::to_string(currentPos / 60) + ":" + seconds));
    SetStatusText( filePath + ": " + std::to_string(currentPos / 60) + ":" + seconds);
}

void VideoPlayerWindow::onSliderMove(wxCommandEvent &ev) {
    player->setVideoPosition(vidPosSlider->GetValue() * 1000);
}

void VideoPlayerWindow::onInfo(wxCommandEvent &ev) {
    long double fileSize = std::round((double) getFilesize(filePath.c_str()));
    std::string fSizeType;
    std::string fsizeString;
    if(fileSize > 1000000000){
        fSizeType = "Gb";
        fsizeString = (std::to_string(fileSize / 1000000000) + " ") ;
    }
    else if(fileSize > 1000000){
        fSizeType = "Mb";
        fsizeString = (std::to_string(fileSize / 1000000) + " ");
    }
    else{
        fSizeType = "Kb";
        fsizeString = (std::to_string(fileSize / 1000) + " ");
    }
    fsizeString.resize(5);
    fsizeString.append(" " + fSizeType);
    std::string seconds;
    mediaLength < 10 ? seconds = "0" + std::to_string(mediaLength % 60) : seconds = std::to_string(mediaLength % 60);

 wxMessageBox(wxString("File: " + filePath + "\n" +
                                "Video Length: " + std::to_string(mediaLength / 60) + ":" + seconds + "\n"
                                //"Dimensions: " + std::to_string(playerBestSize.x) + "x" + std::to_string(playerBestSize.y) + "\n"
                                "File Size: " + fsizeString), "General Video Information", wxOK | wxICON_INFORMATION );
}

void VideoPlayerWindow::onClick(wxMouseEvent &ev) {
    player->isPaused() ? player->Play() : player->Pause();
}

void VideoPlayerWindow::onPlay(wxCommandEvent &ev) {
    player->Play();
}

void VideoPlayerWindow::onStop(wxCommandEvent &ev) {
    player->Stop();
}

void VideoPlayerWindow::onPause(wxCommandEvent &ev) {
    player->Pause();
}

void VideoPlayerWindow::onFinished(wxCommandEvent &ev) {
    if(isLooping->GetValue()){
        player->setVideoPosition(0);
        player->Play();
    }
}

void VideoPlayerWindow::onSetSpeed(wxCommandEvent &ev) {
    float speed = (float) pbrateslider->GetValue() / 100;
    std::string speedstr = std::to_string(speed);
    speedstr.resize(4);
    player->setVideospeed((speed));
    speeddesc->SetLabel(wxString("Current Video Speed: " + speedstr));
}

void VideoPlayerWindow::onSetVol(wxCommandEvent &ev) {
    float vol = (float) volslider->GetValue() / 100;
    std::string volString = std::to_string(vol);
    volString.resize(4);
    player->SetVolume(vol);
    voldesc->SetLabel(wxString("Current Volume: " + volString));
}
