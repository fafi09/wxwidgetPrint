#ifndef CONFIGINI_H
#define CONFIGINI_H

#include "wx/stdpaths.h"
#include "wx/filename.h"
#include "wx/file.h"
#include "wx/fileconf.h" //file config.ini
#include "wx/wfstream.h"


class ConfigINI
{
    public:
        ConfigINI();
        virtual ~ConfigINI();
        wxString GetWorkPath();
        void LoadConfig(wxString fileName);
        wxString GetConfigProp(wxString key);
        char* GetConfigPropWithUTF8(wxString key);
    protected:

    private:
        //char valueArray[64];
};

#endif // CONFIGINI_H
