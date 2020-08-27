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
    wxDC* ptr = GetDC();
    //DrawBarcode(ptr);
    //DrawPageOne(ptr);
    DrawPageTwo(ptr);
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

void QuickPrint::DrawPageOne(wxDC *dc)
{
    // 下面的代码可以这样写只是因为我们知道图片的大小是200x200
    // 如果我们不知道的话，需要先计算图片的大小
    float maxX = 200;
    float maxY = 200;
    // 让我们先设置至少50个设备单位的边框
    float marginX = 50;
    float marginY = 50;
    // 将边框的大小增加到图片的周围
    maxX += (2*marginX);
    maxY += (2*marginY);
    // 获取象素单位的当前设备上下文的大小
    int w, h;
    dc->GetSize(&w, &h);
    //计算一个合适的缩放值
    float scaleX=(float)(w/maxX);
    float scaleY=(float)(h/maxY);
    // 选择X或者Y方向上较小的那个
    float actualScale = wxMin(scaleX,scaleY);
    // 计算图片在设备上的合适位置以便居中
    float posX = (float)((w - (200*actualScale))/2.0);
    float posY = (float)((h - (200*actualScale))/2.0);
    // 设置设备平移和缩放
    dc->SetUserScale(actualScale, actualScale);
    dc->SetDeviceOrigin( (long)posX, (long)posY );
    // ok,现在开始画画
    dc->SetBackground(*wxWHITE_BRUSH);
    dc->Clear();
    //dc->SetFont(wxGetApp().m_testFont);
    dc->SetBackgroundMode(wxTRANSPARENT);
    dc->SetBrush(*wxCYAN_BRUSH);
    dc->SetPen(*wxRED_PEN);
    dc->DrawRectangle(0, 30, 200, 100);
    dc->DrawText( wxT("Rectangle 200 by 100"), 40, 40);
    dc->SetPen( wxPen(*wxBLACK,0,wxDOT_DASH) );
    dc->DrawEllipse(50, 140, 100, 50);
    dc->SetPen(*wxRED_PEN);
    dc->DrawText( wxT("Test message: this is in 10 point text"),
                 10, 180);
}

void QuickPrint::DrawPageTwo(wxDC *dc)
{
    // 你可以使用下面的代码来设置打印机以便其可以反应出文本在屏幕上的大小
    // 另外下面的代码还将打印一个5cm长的线段。
    // 首先获得屏幕和打印机上各自的1英寸的逻辑象素个数
    int ppiScreenX, ppiScreenY;
    GetPPIScreen(&ppiScreenX, &ppiScreenY);
    int ppiPrinterX, ppiPrinterY;
    GetPPIPrinter(&ppiPrinterX, &ppiPrinterY);
    // 这个缩放因子用来大概的反应屏幕到实际打印设备的一个缩放
    float scale = (float)((float)ppiPrinterX/(float)ppiScreenX);
    // 现在，我们还需要考虑页面缩放
    // (比如：我们正在作打印预览，用户选择了一个缩放级别)
    int pageWidth, pageHeight;
    int w, h;
    dc->GetSize(&w, &h);
    GetPageSizePixels(&pageWidth, &pageHeight);
    // 如果打印设备的页面大小pageWidth == 当前DC的大小, 就不需要考虑这方面的缩放了
    // 但是它们有可能是不一样的
    // 因此，缩放吧.
    float overallScale = scale * (float)(w/(float)pageWidth);
    dc->SetUserScale(overallScale, overallScale);
    // 现在我们来计算每个逻辑单位有多少个毫米
    // 我们知道1英寸大概是25.4毫米.而ppi
    // 代表的是以英寸为单位的. 因此1毫米就等于ppi/25.4个设备单位
    // 另外我们还需要再除以我们的缩放因子scale
    // (译者注：为什么这里是scale而不是overallScale？)
    // (其实overallScale比scale而言，多了一个预览的缩放)
    // （而在预览的时候，我们是希望线段的长度按照用户设置的比例变化的）
    // 因为我们的设备已经被设置了缩放因子
    // 现在让我们来画一个长度为50mm的L图案
    float logUnitsFactor = (float)(ppiPrinterX/(scale*25.4));
    float logUnits = (float)(50*logUnitsFactor);
    dc->SetPen(* wxBLACK_PEN);
    dc->DrawLine(50, 250, (long)(50.0 + logUnits), 250);
    dc->DrawLine(50, 250, 50, (long)(250.0 + logUnits));
    dc->SetBackgroundMode(wxTRANSPARENT);
    dc->SetBrush(*wxTRANSPARENT_BRUSH);
    //dc->SetFont(wxGetApp().m_testFont);
    dc->DrawText(wxT("Some test text"), 200, 300 );
}

void QuickPrint::DrawBarcode(wxDC *ptr)
{
    std::cout << "printing page "  << std::endl;
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

    //wxDC* ptr = GetDC();
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
