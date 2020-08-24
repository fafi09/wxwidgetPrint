/***************************************************************
 * Name:      wxtestApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2020-08-23
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "wxtestApp.h"
#include "wxtestMain.h"

IMPLEMENT_APP(wxtestApp);

bool wxtestApp::OnInit()
{
    
    wxtestDialog* dlg = new wxtestDialog(0L, _("wxWidgets Application Template"));
    dlg->SetIcon(wxICON(aaaa)); // To Set App Icon
    dlg->Show();
    return true;
}
