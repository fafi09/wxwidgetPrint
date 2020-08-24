/***************************************************************
 * Name:      wxtestMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2020-08-23
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef WXTESTMAIN_H
#define WXTESTMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "wxtestApp.h"


#include <wx/button.h>
#include <wx/statline.h>
class wxtestDialog: public wxDialog
{
    public:
        wxtestDialog(wxDialog *dlg, const wxString& title);
        ~wxtestDialog();

    protected:
        enum
        {
            idBtnQuit = 1000,
            idBtnAbout,
            idBtnPrint
        };
        wxStaticText* m_staticText1;
        wxButton* BtnAbout;
        wxStaticLine* m_staticline1;
        wxButton* BtnQuit;
        wxButton* BtnPrint;

    private:
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnPrint(wxCommandEvent& event);
        void OnInitDialog(wxInitDialogEvent& event);
        void OnPaint(wxPaintEvent& event);
        DECLARE_EVENT_TABLE()
};

#endif // WXTESTMAIN_H
