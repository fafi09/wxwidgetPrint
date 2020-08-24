#ifndef QUICKPRINT_H
#define QUICKPRINT_H

#include <iostream>
#include "wx/wx.h"
#include "wx/print.h"
#include "wx/printdlg.h"
#include <cmath>


class QuickPrint : public wxPrintout
{
    public:
        QuickPrint(int page_amount);
        virtual ~QuickPrint();
        wxPrintData getPrintData();
        bool OnPrintPage(int pageNum);
        bool HasPage(int pageNum);
        bool OnBeginDocument(int startPage, int endPage);

    protected:

    private:
        wxPageSetupDialogData m_page_setup;
        int m_page_amount;
};

#endif // QUICKPRINT_H
