#ifndef CONTENTMODEL_H
#define CONTENTMODEL_H
#include <wx/string.h>
#include <wx/list.h>


class ContentModel
{
    public:
        ContentModel();
        virtual ~ContentModel();

        void SetTitle(wxString title);
        wxString GetTitle() const;
    protected:

    private:
        wxString m_title;
};

WX_DECLARE_LIST(ContentModel, ContentModelList);

#endif // CONTENTMODEL_H
