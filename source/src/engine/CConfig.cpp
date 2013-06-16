#include "engine/CConfig.hpp"
#include <iostream>
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

CConfig::CConfig(const stringw &xmlFile):
    mNullDevice(0),
    mXMLFileName(xmlFile)
{
    // Создаем пустое устройство для взятие параметров системы.
    mNullDevice = irr::createDevice(video::EDT_NULL);

    // Устанавливаем значения для карты драйверов.
    mDriverMap.insert(L"Software"   , video::EDT_SOFTWARE);
    mDriverMap.insert(L"OpenGL"     , video::EDT_OPENGL);
    mDriverMap.insert(L"Direct3D9"  , video::EDT_DIRECT3D9);
    mDriverMap.insert(L"Direct3D8"  , video::EDT_DIRECT3D8);

    //Устанавливаем список разрешений.
    IVideoModeList* modes = mNullDevice->getVideoModeList();
    for(s32 i = 0; i < modes->getVideoModeCount(); i++)
    {
        dimension2d<u32> res = modes->getVideoModeResolution(i);
        wchar_t * tmp = new wchar_t[10]; // nnnnXnnnn
        swprintf(tmp, 10, L"%dx%d", res.Width, res.Height);
        mResolutionMap.insert(tmp, res);
        delete [] tmp;
    }
    mResolutionMap.insert(L"desktop", mNullDevice->getVideoModeList()
                          ->getDesktopResolution());
}
CConfig::~CConfig()
{
    if(mNullDevice)
    {
        mNullDevice->closeDevice();
        mNullDevice->drop();
    }
}


bool CConfig::load()
{
    if(!mNullDevice)
    {
        return false;
    }
    IXMLReader* xml = mNullDevice->getFileSystem()->createXMLReader(mXMLFileName);

    if(!xml)
    {
        return false;
    }
    const stringw configTag(L"config");
    const stringw videoTag(L"video");

    stringw currentSection;

    while(xml->read())
    {
        //Проверяем тип корня
        switch(xml->getNodeType())
        {
            //Новый элемент найден
        case irr::io::EXN_ELEMENT:
        {
            if(currentSection.empty() &&
               videoTag.equals_ignore_case(xml->getNodeName()))
            {
                currentSection = videoTag;
            } else if (currentSection.equals_ignore_case(videoTag) &&
                       configTag.equals_ignore_case(xml->getNodeName()))
            {
                stringw key = xml->getAttributeValueSafe(L"name");
                if(!key.empty())
                {
                    mConfigMap[key] = xml->getAttributeValueSafe(L"value");
                }
            }
        } break;
        case irr::io::EXN_ELEMENT_END:
        {
            currentSection = L"";
        } break;
        }
    }
    xml->drop();
    doParam();
    return true;
}
stringw CConfig::getConfig(const stringw& key)
{
    map<stringw,stringw>::Node *it = mConfigMap.find(key);
    if(it)
        return it->getValue();
    else
        return L"";
}
s32 CConfig::getInteger(const stringw& key) {
    const stringc s = getConfig(key);
    if(s.empty())
        return 0;
    else
        return strtol10(s.c_str());
}
bool CConfig::getBool(const stringw& key)
{
    stringw s = getConfig(key);
    if(s.empty())
        return false;
    else
        return s.equals_ignore_case(L"1");
}
void CConfig::doParam()
{
    mParam.Fullscreen = getBool(L"fullscreen");
    if(mParam.Fullscreen)
    {
        if(getBool(L"DesktopFull"))
        {
            mParam.WindowSize = mResolutionMap[L"desktop"];
        }
        else
        {
            mParam.WindowSize = mResolutionMap[ getConfig( L"resolution") ];
        }
    }

    mParam.DriverType = (E_DRIVER_TYPE)mDriverMap[ getConfig(L"driver") ];
    mParam.Doublebuffer = getBool(L"doublebuffer");
    mParam.Vsync = getBool(L"vsync");
}

SIrrlichtCreationParameters CConfig::getParam()
{
    return mParam;
}
