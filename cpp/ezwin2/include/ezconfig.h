
/***********************************************************
 * EZWIN2
 *
 * Name:      ezconfig.h
 * version:   0.1
 * date:      28 April 2002
 * author:	  John Donoghue <john.donoghue@ieee.org>
 * copyright: (c) John Donoghue, 2001-2002
 *
 ***********************************************************/

/***********************************************************
 * This software is free, and may be distributed or modified
 * as specified under the terms of the Lesser General Public 
 * License as published by the Free Software Foundation.
 ***********************************************************/

#ifndef ezconfig_h
#define ezconfig_h

#include <ezwin.h>

#include <string>

// registry/system config settings

class DLL_EXP EZConfig
{
private:
  // internal constructor
  EZConfig(HKEY parent,const char *str,bool create);

  HKEY _handle;

public:
  typedef enum
  {
    EZCONFIG_CLASSES_ROOT,
    EZCONFIG_CURRENT_CONFIG,
    EZCONFIG_CURRENT_USER,
    EZCONFIG_LOCAL_MACHINE,
    EZCONFIG_USERS
  } BaseConfig;

  EZConfig(BaseConfig base=EZCONFIG_CURRENT_USER,const char *key=0);
  EZConfig(const EZConfig &conf);

  ~EZConfig();


  EZConfig & operator=(const EZConfig &conf);

  bool operator()();
  bool operator!();

  HKEY getHandle() { return _handle; }
  bool isValid() { return _handle!=0; }

  EZConfig createKey(const char *str);
  EZConfig openKey(const char *str);

  bool getStringValue(int index, std::string &name,std::string &value);
  bool getStringValue(const std::string &name,std::string &value);

  bool setStringValue(const std::string &name,const std::string &value);

  bool getIntValue(const std::string &name,int &value);
  bool setIntValue(const std::string &name,const int &value);

  bool flush();
};


#endif // ezconfig_h
