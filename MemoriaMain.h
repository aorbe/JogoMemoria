/***************************************************************
 * Name:      MemoriaMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2014-07-29
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef MEMORIAMAIN_H
#define MEMORIAMAIN_H

//(*Headers(MemoriaDialog)
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/timer.h>
//*)
#include <wx/bmpbuttn.h>

class MemoriaDialog: public wxDialog
{
    public:

        MemoriaDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~MemoriaDialog();

    private:

        //(*Handlers(MemoriaDialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButtonClick(wxCommandEvent& event);
        void OnTimer1Trigger(wxTimerEvent& event);
        void OnSecond(wxTimerEvent& event);
        //*)

        //(*Identifiers(MemoriaDialog)
        static const long ID_TIMER1;
        static const long ID_TIMER2;
        //*)
        static const long ID_MEMITEM[];

        //(*Declarations(MemoriaDialog)
        wxTimer Timer1;
        wxTimer Timer2;
        //*)
        wxBitmapButton* Item[36];
        wxBitmap dog;
        unsigned char* ImgTime[18];
        long ImgSize[18];
        int ItemTime[36];
        int opened, elemento, found;
        long TotalTime;

        DECLARE_EVENT_TABLE()
};

#endif // MEMORIAMAIN_H
