#ifndef CCONFIG_HPP
#define CCONFIG_HPP
#include <irrlicht/irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class CConfig
{
public:
    CConfig(const stringw &xmlFile);
    ~CConfig();
    bool load();
    SIrrlichtCreationParameters getParam();
    bool isError();
    stringw     getConfig(const stringw& key);
    s32         getInteger(const stringw& key);
    bool        getBool(const stringw& key);

private:
    void doParam();
    SIrrlichtCreationParameters mParam;
    stringw                     mXMLFileName;
    map<stringw,stringw>        mConfigMap;
    map<stringw,E_DRIVER_TYPE>  mDriverMap;
    map<stringw,dimension2du>   mResolutionMap;
    IrrlichtDevice              *mNullDevice;
    stringw                     mTitle;
    bool                        mError;
};
#endif // CCONFIG_HPP
