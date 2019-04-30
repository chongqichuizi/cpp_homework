#include <ezconfig.h>

EZConfig::EZConfig(BaseConfig base,const char *key)
{
  HKEY parentkey;

  switch(base)
  {
    case EZCONFIG_CLASSES_ROOT:
      parentkey = HKEY_CLASSES_ROOT;
      break;
    case EZCONFIG_CURRENT_CONFIG:
      parentkey = HKEY_CURRENT_CONFIG;
      break;
    case EZCONFIG_CURRENT_USER:
      parentkey = HKEY_CURRENT_USER;
      break;
    case EZCONFIG_LOCAL_MACHINE:
      parentkey = HKEY_LOCAL_MACHINE;
      break;
    case EZCONFIG_USERS:
      parentkey = HKEY_USERS;
      break;
    default:
      parentkey = 0;
  }

  _handle = 0;

   if(RegOpenKeyEx(parentkey,key,0,KEY_ALL_ACCESS,&_handle)!=ERROR_SUCCESS)
   {
       _handle = 0;
   }
}

EZConfig::EZConfig(const EZConfig &conf)
{
   if(this != &conf)
   {
     if(conf._handle)
       RegOpenKey(conf._handle,0,&_handle);
     else
       _handle = 0;
   }
}
EZConfig & EZConfig::operator=(const EZConfig &conf)
{
   if(this != &conf)
   {
     if(this->_handle)
       RegCloseKey(this->_handle);

	 this->_handle = 0;

     if(conf._handle)
       //RegOpenKey(conf._handle,0,&this->_handle); //cant write under 2000 unless key all access
       RegOpenKeyEx(conf._handle,0,0, KEY_ALL_ACCESS, &this->_handle);
     else
       this->_handle = 0;
   }
   return *this;
}
EZConfig EZConfig::openKey(const char *key)
{
  return EZConfig(_handle,key,false);
}
EZConfig EZConfig::createKey(const char *key)
{
  return EZConfig(_handle,key,true);
}
bool EZConfig::operator()()
{
   return _handle!=0;
}
bool EZConfig::operator!()
{
   return _handle==0;
}

EZConfig::EZConfig(HKEY parent,const char *str,bool create)
{
   DWORD ret_flags;

   if(parent==0)
     _handle = 0;
   else if(!create)
   {
     if(RegOpenKeyEx(parent,str,0,KEY_ALL_ACCESS,&_handle)!=ERROR_SUCCESS)
     {
       _handle = 0;
     }
   }
   else
   {
     if(RegCreateKeyEx(parent,str,0,0,REG_OPTION_NON_VOLATILE,
     KEY_ALL_ACCESS,0,&_handle,&ret_flags)!=ERROR_SUCCESS)
     {
       _handle = 0;
     }
   }
}

EZConfig::~EZConfig()
{
  if(_handle) RegCloseKey(_handle);
}

bool EZConfig::getStringValue(int index,std::string &name,std::string &value)
{
   char namebuffer[1024];
   char valuebuffer[1024];

   DWORD namesize=1024;
   DWORD valuesize=1024;

   DWORD type;

   if(RegEnumValue(_handle,index,namebuffer,&namesize,0,&type,(unsigned char *)valuebuffer,&valuesize)==ERROR_SUCCESS)
   {
     value = valuebuffer;
     name = namebuffer;
     return true;
   }
   return false;
}
bool EZConfig::getStringValue(const std::string &name,std::string &value)
{
   char valuebuffer[1024];
   DWORD valuesize=1024;

   DWORD type;

   if(RegQueryValueEx(_handle,name.c_str(),0,&type,(unsigned char *)valuebuffer,&valuesize)==ERROR_SUCCESS)
   {
     value = valuebuffer;
     return true;
   }
   return false;
}

bool EZConfig::setStringValue(const std::string &name,const std::string &value)
{
   if(RegSetValueEx(_handle,name.c_str(),0,REG_SZ,(unsigned char *)value.c_str(),value.length()+1)==ERROR_SUCCESS)
     return true;
   else
     return false;
}
bool EZConfig::flush()
{
   if(RegFlushKey(_handle)==ERROR_SUCCESS)
     return true;
   else
     return false;
}

bool EZConfig::getIntValue(const std::string &name,int &value)
{
   //char valuebuffer[1024];
   DWORD valuesize=sizeof(int);

   DWORD type;

   if(RegQueryValueEx(_handle,name.c_str(),0,&type,(unsigned char *)&value,&valuesize)==ERROR_SUCCESS)
   {
     //value = atoi( (const char *)valuebuffer );
     return true;
   }
   return false;
}

bool EZConfig::setIntValue(const std::string &name,const int &value)
{

   if(RegSetValueEx(_handle,name.c_str(),0,REG_DWORD,(unsigned char *)&value,sizeof(int))==ERROR_SUCCESS)
     return true;
   else
     return false;
}