/***************************************************************
 * Name:      MemoriaApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2014-07-29
 * Copyright:  ()
 * License:
 **************************************************************/

#include "MemoriaApp.h"

//(*AppHeaders
#include "MemoriaMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(MemoriaApp);

bool MemoriaApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;

    wxInitAllImageHandlers();

    if ( wxsOK )
    {
    	MemoriaDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}
