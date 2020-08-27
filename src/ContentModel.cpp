#include "ContentModel.h"
#include <wx/listimpl.cpp>

WX_DEFINE_LIST(ContentModelList);
ContentModel::ContentModel()
{
    //ctor
}

ContentModel::~ContentModel()
{
    //dtor
}

void ContentModel::SetTitle(wxString title)
{
    m_title = title;
}

wxString ContentModel::GetTitle() const
{
    return m_title;
}
