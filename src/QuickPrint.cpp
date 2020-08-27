#include "QuickPrint.h"
#include "Barcode128.h"

QuickPrint::QuickPrint(int page_amount)
{
    wxPrintData printdata;
    printdata.SetPrintMode( wxPRINT_MODE_PRINTER );
    printdata.SetOrientation( wxLANDSCAPE );
    printdata.SetNoCopies(1);
    printdata.SetPaperId( wxPAPER_LETTER );

    this->m_page_amount = page_amount;

    this->m_page_setup = wxPageSetupDialogData(printdata);
}

QuickPrint::~QuickPrint()
{
    //dtor
}

wxPrintData QuickPrint::getPrintData()
{

    return this->m_page_setup.GetPrintData();

}

bool QuickPrint::OnPrintPage(int pageNum)
{
    std::cout << "printing page " << pageNum << std::endl;
    int brush_size = 3;
    const int x0 = 0;
    const int y0 = 0;
    const int width = 1024;
    const int height = 768;
    const int x1 = x0 + width;
    const int y1 = y0 + height;

    const int center_x = x0 + width/2;
    const int center_y = y0 + height/2;
    //const int pageNum = 1;

    wxDC* ptr = GetDC();
    wxDC& pDC = *ptr;

    //wxPrinterDC pDC(printdata);


    pDC.Clear();
   /* pDC.SetPen(  wxPen( wxColour(0,0,0), brush_size ) );
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
    //wxString fileName("D4yq5P1A3n.png");

    pDC.SetFont(wxFont(25, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "宋体"));
    pDC.SetUserScale(4.0,4.0);

    //pDC.SetMapMode(wxMM_TEXT);
	//pDC.SetUserScale(1.0,1.0);
    wxImage image(_T("D:\\workspace\\wxwidgets\\wxtest\\Build.bmp"));
    wxBitmap bp(image);
    pDC.DrawBitmap(bp, 30,10);
    pDC.DrawText( "天气名称：", 50, 40);
    pDC.SetFont(wxFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "宋体"));
    pDC.DrawText( "人气名称：", 50, 80);

    char barcode[20] = {'2','2','2','2','0','8','0','9','5','1','0','0','0','0','0','1','\0','\0','\0','\0'};
    //char barcode[3] = {'A','B','\0'};
    Barcode128 gen;
    gen.Encode128C(barcode);
    //gen.Encode128A(barcode);
    std::cout << gen.ia_Buf[1] << gen.i_LenBuf << std::endl;
    gen.Draw128(pDC,120,192,280,*wxBLACK, *wxWHITE, 3);
}

bool QuickPrint::HasPage(int pageNum)
{
    return pageNum >= 1 && pageNum <= m_page_amount;
}

bool QuickPrint::OnBeginDocument(int startPage, int endPage)
{
    std::cout << "beginning to print document, from page " << startPage
                  << " to " << endPage << std::endl;
    return wxPrintout::OnBeginDocument(startPage, endPage);

}
