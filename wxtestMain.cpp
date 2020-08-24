/***************************************************************
 * Name:      wxtestMain.cpp
 * Purpose:   Code for Application Frame
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

#include "wxtestMain.h"
#include <wx/cmndata.h>
#include "QuickPrint.h"
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
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
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


BEGIN_EVENT_TABLE(wxtestDialog, wxDialog)
    EVT_CLOSE(wxtestDialog::OnClose)
    EVT_BUTTON(idBtnQuit, wxtestDialog::OnQuit)
    EVT_BUTTON(idBtnAbout, wxtestDialog::OnAbout)
    EVT_BUTTON(idBtnPrint, wxtestDialog::OnPrint)
    EVT_INIT_DIALOG(wxtestDialog::OnInitDialog)
    EVT_PAINT(wxtestDialog::OnPaint)
END_EVENT_TABLE()

wxtestDialog::wxtestDialog(wxDialog *dlg, const wxString &title)
    : wxDialog(dlg, -1, title,wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE | wxMAXIMIZE_BOX)
{
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);
    wxSize* pSize = new wxSize(300,800);
    //this->setInitialSize(pSize);
    //this->SetSizeHints(pSize,pSize);
    wxBoxSizer* bSizer1;
    bSizer1 = new wxBoxSizer(wxHORIZONTAL);
    m_staticText1 = new wxStaticText(this, wxID_ANY, wxT("Welcome To\nwxWidgets"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText1->SetFont(wxFont(20, 74, 90, 90, false, wxT("Arial")));
    bSizer1->Add(m_staticText1, 0, wxALL|wxEXPAND, 5);
    wxBoxSizer* bSizer2;
    bSizer2 = new wxBoxSizer(wxVERTICAL);
    BtnAbout = new wxButton(this, idBtnAbout, wxT("&About"), wxDefaultPosition, wxDefaultSize, 0);
    bSizer2->Add(BtnAbout, 0, wxALL, 5);
    m_staticline1 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    bSizer2->Add(m_staticline1, 0, wxALL|wxEXPAND, 5);
    BtnQuit = new wxButton(this, idBtnQuit, wxT("&Quit"), wxDefaultPosition, wxDefaultSize, 0);
    bSizer2->Add(BtnQuit, 0, wxALL, 5);

    BtnPrint =  new wxButton(this, idBtnPrint, wxT("&Printe"), wxDefaultPosition, wxDefaultSize, 0);
    bSizer2->Add(BtnPrint, 0, wxALL, 5);

    bSizer1->Add(bSizer2, 1, wxEXPAND, 5);

    this->SetSizer(bSizer1);
    this->Layout();
    bSizer1->Fit(this);

    std::cout << "wxtestDialog" << std::endl;
}


wxtestDialog::~wxtestDialog()
{
}

void wxtestDialog::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void wxtestDialog::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void wxtestDialog::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void wxtestDialog::OnInitDialog(wxInitDialogEvent& event)
{

    //wxString msg = wxbuildinfo(long_f);
    //wxMessageBox(msg, _("Welcome to..."));


    //pDC.ReleaseHDC();

    std::cout << "initidialog" << std::endl;


}


void wxtestDialog::OnPaint(wxPaintEvent& event)
{
    wxPaintDC pDC(this);
    wxPen pen = pDC.GetPen();

    pDC.SetPen(*wxBLUE_PEN);
    //wxColour c = pen.GetColour();
    //pen.SetColour(20,20,20);
    //pen.SetStyle(wxBLUE_PEN);
    pDC.DrawLine(10,200,500,200);

    wxString ws = "stasrt";
    pDC.DrawText(ws,600,300);

    //pen.SetColour(c);
    pDC.SetPen(pen);

    //wxBitmap bp = new wxBitmap()
}


void wxtestDialog::OnPrint(wxCommandEvent& event)
{
    /*
    int brush_size = 3;
    const int x0 = 0;
    const int y0 = 0;
    const int width = 800;
    const int height = 300;
    const int x1 = x0 + width;
    const int y1 = y0 + height;

    const int center_x = x0 + width/2;
    const int center_y = y0 + height/2;
    const int pageNum = 1;

    wxString msg = "printer";
    wxMessageBox(msg, _("Welcome to..."));
    wxPrintData printdata;
    printdata.SetPrintMode( wxPRINT_MODE_PRINTER );
    printdata.SetOrientation( wxLANDSCAPE );
    printdata.SetNoCopies(1);
    printdata.SetPaperId( wxPAPER_LETTER );


    //wxPageSetupDialogData m_page_setup = wxPageSetupDialogData(printdata);
    wxPrinterDC pDC(printdata);


    pDC.Clear();
    pDC.SetPen(  wxPen( wxColour(0,0,0), brush_size ) );
    pDC.SetBrush( *wxTRANSPARENT_BRUSH );

    // draw a rectangle to show its bounds.
    pDC.DrawRectangle(x0, y0, width, height);

    // draw wxWidgets logo
    pDC.SetBrush( *wxRED_BRUSH );
    pDC.DrawRectangle(center_x-45-38, center_y, 76, 76);
    pDC.SetBrush( *wxBLUE_BRUSH );
    pDC.DrawRectangle(center_x-38, center_y-45, 76, 76);
    pDC.SetBrush( wxBrush( wxColor(255,244,0) ) );
    pDC.DrawRectangle(center_x+45-38, center_y-10, 76, 76);

    // draw page number label
    wxString label( wxT("This is page #") );
    label << pageNum;
    pDC.SetTextBackground( wxColour(255,255,0) );
    pDC.SetTextForeground( wxColour(0,0,0) );
    pDC.DrawText( label, x0 + width/5, y0 + height - 50 );
    */

    QuickPrint*  myprint = new QuickPrint(1);
    wxPrintDialogData data(myprint->getPrintData());

    wxPrinter printer(&data);
    const bool success = printer.Print(NULL, myprint, false /* show dialog */);


    delete myprint;

}
