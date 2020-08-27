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
    // ����Ĵ����������дֻ����Ϊ����֪��ͼƬ�Ĵ�С��200x200
    // ������ǲ�֪���Ļ�����Ҫ�ȼ���ͼƬ�Ĵ�С
    float maxX = 200;
    float maxY = 200;
    // ����������������50���豸��λ�ı߿�
    float marginX = 50;
    float marginY = 50;
    // ���߿�Ĵ�С���ӵ�ͼƬ����Χ
    maxX += (2*marginX);
    maxY += (2*marginY);
    // ��ȡ���ص�λ�ĵ�ǰ�豸�����ĵĴ�С
    int w, h;
    dc->GetSize(&w, &h);
    //����һ�����ʵ�����ֵ
    float scaleX=(float)(w/maxX);
    float scaleY=(float)(h/maxY);
    // ѡ��X����Y�����Ͻ�С���Ǹ�
    float actualScale = wxMin(scaleX,scaleY);
    // ����ͼƬ���豸�ϵĺ���λ���Ա����
    float posX = (float)((w - (200*actualScale))/2.0);
    float posY = (float)((h - (200*actualScale))/2.0);
    // �����豸ƽ�ƺ�����
    dc->SetUserScale(actualScale, actualScale);
    dc->SetDeviceOrigin( (long)posX, (long)posY );
    // ok,���ڿ�ʼ����
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
    // �����ʹ������Ĵ��������ô�ӡ���Ա�����Է�Ӧ���ı�����Ļ�ϵĴ�С
    // ��������Ĵ��뻹����ӡһ��5cm�����߶Ρ�
    // ���Ȼ����Ļ�ʹ�ӡ���ϸ��Ե�1Ӣ����߼����ظ���
    int ppiScreenX, ppiScreenY;
    GetPPIScreen(&ppiScreenX, &ppiScreenY);
    int ppiPrinterX, ppiPrinterY;
    GetPPIPrinter(&ppiPrinterX, &ppiPrinterY);
    // �����������������ŵķ�Ӧ��Ļ��ʵ�ʴ�ӡ�豸��һ������
    float scale = (float)((float)ppiPrinterX/(float)ppiScreenX);
    // ���ڣ����ǻ���Ҫ����ҳ������
    // (���磺������������ӡԤ�����û�ѡ����һ�����ż���)
    int pageWidth, pageHeight;
    int w, h;
    dc->GetSize(&w, &h);
    GetPageSizePixels(&pageWidth, &pageHeight);
    // �����ӡ�豸��ҳ���СpageWidth == ��ǰDC�Ĵ�С, �Ͳ���Ҫ�����ⷽ���������
    // ���������п����ǲ�һ����
    // ��ˣ����Ű�.
    float overallScale = scale * (float)(w/(float)pageWidth);
    dc->SetUserScale(overallScale, overallScale);
    // ��������������ÿ���߼���λ�ж��ٸ�����
    // ����֪��1Ӣ������25.4����.��ppi
    // ���������Ӣ��Ϊ��λ��. ���1���׾͵���ppi/25.4���豸��λ
    // �������ǻ���Ҫ�ٳ������ǵ���������scale
    // (����ע��Ϊʲô������scale������overallScale��)
    // (��ʵoverallScale��scale���ԣ�����һ��Ԥ��������)
    // ������Ԥ����ʱ��������ϣ���߶εĳ��Ȱ����û����õı����仯�ģ�
    // ��Ϊ���ǵ��豸�Ѿ�����������������
    // ��������������һ������Ϊ50mm��Lͼ��
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

    pDC.SetFont(wxFont(25, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "����"));
    pDC.SetUserScale(4.0,4.0);

    //pDC.SetMapMode(wxMM_TEXT);
	//pDC.SetUserScale(1.0,1.0);
    wxImage image(_T("D:\\workspace\\wxwidgets\\wxtest\\Build.bmp"));
    wxBitmap bp(image);
    pDC.DrawBitmap(bp, 30,10);
    pDC.DrawText( "�������ƣ�", 50, 40);
    pDC.SetFont(wxFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "����"));
    pDC.DrawText( "�������ƣ�", 50, 80);

    char barcode[20] = {'2','2','2','2','0','8','0','9','5','1','0','0','0','0','0','1','\0','\0','\0','\0'};
    //char barcode[3] = {'A','B','\0'};
    Barcode128 gen;
    gen.Encode128C(barcode);
    //gen.Encode128A(barcode);
    std::cout << gen.ia_Buf[1] << gen.i_LenBuf << std::endl;
    gen.Draw128(pDC,120,192,280,*wxBLACK, *wxWHITE, 3);
}
