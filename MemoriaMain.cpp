/***************************************************************
 * Name:      MemoriaMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2014-07-29
 * Copyright:  ()
 * License:
 **************************************************************/

#include "MemoriaMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(MemoriaDialog)
#include <wx/string.h>
#include <wx/intl.h>
//*)
#include <wx/stdpaths.h>
#include <wx/mstream.h>
#include <wx/image.h>
#include "corinthians.h"
#include "palmeiras.h"
#include "santos.h"
#include "sp.h"
#include "flamengo.h"
#include "fluminense.h"
#include "botafogo.h"
#include "vasco.h"
#include "atletico.h"
#include "cruzeiro.h"
#include "gremio.h"
#include "internacional.h"
#include "nautico.h"
#include "sport.h"
#include "bayern.h"
#include "argentina.h"
#include "brasil.h"
#include "barcelona.h"
#include "empty.h"

inline wxBitmap wxGetBitmapFromMemory(const unsigned char *data, unsigned int size) {
   wxMemoryInputStream is(data, size);
   return wxBitmap(wxImage(is, wxBITMAP_TYPE_ANY, -1), -1);
 }

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}



//(*IdInit(MemoriaDialog)
const long MemoriaDialog::ID_TIMER1 = wxNewId();
const long MemoriaDialog::ID_TIMER2 = wxNewId();
//*)

const long MemoriaDialog::ID_MEMITEM[] = {wxNewId(),wxNewId(),wxNewId(),wxNewId(),wxNewId(),wxNewId(),
                                        wxNewId(),wxNewId(),wxNewId(),wxNewId(),wxNewId(),wxNewId(),
                                        wxNewId(),wxNewId(),wxNewId(),wxNewId(),wxNewId(),wxNewId(),
                                        wxNewId(),wxNewId(),wxNewId(),wxNewId(),wxNewId(),wxNewId(),
                                        wxNewId(),wxNewId(),wxNewId(),wxNewId(),wxNewId(),wxNewId(),
                                        wxNewId(),wxNewId(),wxNewId(),wxNewId(),wxNewId(),wxNewId()};

BEGIN_EVENT_TABLE(MemoriaDialog,wxDialog)
    //(*EventTable(MemoriaDialog)
    //*)
END_EVENT_TABLE()

MemoriaDialog::MemoriaDialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(MemoriaDialog)
    wxGridSizer* GridSizer1;

    Create(parent, id, _("Jogo da Memória"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxSize(600,600));
    GridSizer1 = new wxGridSizer(6, 6, 0, 0);
    SetSizer(GridSizer1);
    Timer1.SetOwner(this, ID_TIMER1);
    Timer2.SetOwner(this, ID_TIMER2);
    Timer2.Start(1000, false);
    GridSizer1->SetSizeHints(this);

    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&MemoriaDialog::OnTimer1Trigger);
    Connect(ID_TIMER2,wxEVT_TIMER,(wxObjectEventFunction)&MemoriaDialog::OnSecond);
    //*)
    wxString ItemName;
    for(int i=0; i<36; i++)
    {
        ItemName = _("ITEM");
        ItemName << i;
        Item[i] = new wxBitmapButton(this, ID_MEMITEM[i], wxNullBitmap, wxDefaultPosition, wxSize(100,100), wxBU_AUTODRAW, wxDefaultValidator, ItemName);
        Item[i]->SetDefault();
        GridSizer1->Add(Item[i], i, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
        Connect(ID_MEMITEM[i],wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MemoriaDialog::OnButtonClick);

    }
    ImgTime[ 0] = corinthians_png;      ImgSize[ 0] = sizeof(corinthians_png);
    ImgTime[ 1] = palmeiras_png;        ImgSize[ 1] = sizeof(palmeiras_png);
    ImgTime[ 2] = santos_png;           ImgSize[ 2] = sizeof(santos_png);
    ImgTime[ 3] = sp_png;               ImgSize[ 3] = sizeof(sp_png);
    ImgTime[ 4] = flamengo_png;         ImgSize[ 4] = sizeof(flamengo_png);
    ImgTime[ 5] = fluminense_png;       ImgSize[ 5] = sizeof(fluminense_png);
    ImgTime[ 6] = vasco_png;            ImgSize[ 6] = sizeof(vasco_png);
    ImgTime[ 7] = botafogo_png;         ImgSize[ 7] = sizeof(botafogo_png);
    ImgTime[ 8] = cruzeiro_png;         ImgSize[ 8] = sizeof(cruzeiro_png);
    ImgTime[ 9] = barcelona_png;        ImgSize[ 9] = sizeof(barcelona_png);
    ImgTime[10] = atletico_png;         ImgSize[10] = sizeof(atletico_png);
    ImgTime[11] = gremio_png;           ImgSize[11] = sizeof(gremio_png);
    ImgTime[12] = internacional_png;    ImgSize[12] = sizeof(internacional_png);
    ImgTime[13] = bayern_png;           ImgSize[13] = sizeof(bayern_png);
    ImgTime[14] = argentina_png;        ImgSize[14] = sizeof(argentina_png);
    ImgTime[15] = sport_png;            ImgSize[15] = sizeof(sport_png);
    ImgTime[16] = nautico_png;          ImgSize[16] = sizeof(nautico_png);
    ImgTime[17] = brasil_png;           ImgSize[17] = sizeof(brasil_png);

    opened = 36;
    elemento = 0;
    found = 0;
    Timer2.Stop();
    TotalTime = 0;

    for(int i=0; i<36; i++)
    {
        ItemTime[i] = 18;
    }
    int freeN = 0, freeQ = 0;
    srand(time(NULL));
    for(int i=0; i<36; i++)
    {
        ItemTime[i] = (rand()) % 18;
        int v = ItemTime[i];
        int q = 0;
        if(ItemTime[i] == freeN)
        {
            freeQ++;
            if (freeQ > 2)
            {
                while(freeQ > 1)
                {
                    freeN = (freeN+1)%18;
                    freeQ = 0;
                    for(int j=0; j<36; j++)
                    {
                        if(freeN==ItemTime[j])
                            freeQ++;
                    }
                }
                ItemTime[i] = freeN;
                freeQ++;
            }
            continue;
        }
        for(int j=0; j<i; j++)
        {
            if(ItemTime[j] == v)
            {
                q++;
            }
            if(q>1)
            {
                freeQ++;
                if (freeQ > 2)
                {
                    while(freeQ > 1)
                    {
                        freeN = (freeN+1)%18;
                        freeQ = 0;
                        for(int k=0; k<36; k++)
                        {
                            if(freeN==ItemTime[k])
                                freeQ++;
                        }
                    }
                    freeQ++;
                }
                ItemTime[i] = freeN;
                break;
            }
        }
    }

    for(int i=0; i<36; i++)
    {
        int v = ItemTime[i];
        int q = 0;
    }
}

MemoriaDialog::~MemoriaDialog()
{
    //(*Destroy(MemoriaDialog)
    //*)
}

void MemoriaDialog::OnQuit(wxCommandEvent& event)
{
    Close();
}

void MemoriaDialog::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void MemoriaDialog::OnButtonClick(wxCommandEvent& event)
{
    if(!Timer2.IsRunning())
        Timer2.Start(1000);
    if(Timer1.IsRunning())
        return;
    elemento = 0;
    while(ID_MEMITEM[elemento] != event.GetId())
    {
        elemento++;
    }
    if(elemento == opened)
        return;
    if (ItemTime[elemento] < 100)
    {
        Item[elemento]->SetBitmapLabel(wxGetBitmapFromMemory(ImgTime[ItemTime[elemento]], ImgSize[ItemTime[elemento]])); // Display new bitmap (segfault)
        if (opened != 36)
        {
            if (ItemTime[opened] == ItemTime[elemento])
            {
                ItemTime[opened] = 100 + ItemTime[opened];
                ItemTime[elemento] = 100 + ItemTime[elemento];
                found++;
                if(found==18)
                {
                    for(int i=0; i<36; i++)
                        Item[i]->Disable();
                    Timer2.Stop();
                    wxString msg;
                    msg << _("Você conseguiu encontrar todos os pares\n em ") << TotalTime << _(" segundos.");
                    wxMessageBox(msg, _("Parabéns"));

                }
                opened = 36;
            }
            else
            {
                Timer1.Start(1000, true);
            }
        }
        else
            opened = elemento;

    }
    event.Skip();
}

void MemoriaDialog::OnTimer1Trigger(wxTimerEvent& event)
{
    Item[elemento]->SetBitmapLabel(wxGetBitmapFromMemory(empty_png, sizeof(empty_png)));
    Item[opened]->SetBitmapLabel(wxGetBitmapFromMemory(empty_png, sizeof(empty_png)));
    opened = 36;

}

void MemoriaDialog::OnSecond(wxTimerEvent& event)
{
    TotalTime++;
    wxString title;
    title << _("Jogo da Memória (") << TotalTime << _(" s)");
    SetTitle(title);
}
