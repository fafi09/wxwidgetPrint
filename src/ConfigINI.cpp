#include "ConfigINI.h"

ConfigINI::ConfigINI()
{
    //ctor
}

ConfigINI::~ConfigINI()
{
    //dtor
    wxFileConfig* config = (wxFileConfig*)wxConfigBase::Get();
    wxConfigBase::Set(NULL);
    if(config != NULL)
        delete config;
    //delete[] valueArray;
}

wxString ConfigINI::GetWorkPath()
{
    wxString apppath;
	wxStandardPathsBase& stpd = wxStandardPaths::Get();

	wxFileName exeFile(stpd.GetExecutablePath());
	apppath = exeFile.GetPath(wxPATH_GET_VOLUME|wxPATH_GET_SEPARATOR);

	return apppath;

}

void ConfigINI::LoadConfig(wxString fileName)
{
    wxFileInputStream is(this->GetWorkPath()+fileName);
    wxFileConfig* config = new wxFileConfig(is);
    wxConfigBase::Set(config);

}

wxString ConfigINI::GetConfigProp(wxString key)
{

    wxFileConfig* config = (wxFileConfig*)wxConfigBase::Get();
    wxString value = config->Read(key);
    return value;

}

char*  ConfigINI::GetConfigPropWithUTF8(wxString key)
{
    /*
    wxFileConfig* config = (wxFileConfig*)wxConfigBase::Get();

    memset(valueArray, '0', sizeof(valueArray));
    bool iskd = config->Read(key,valueArray);
    */
    return NULL;

}
