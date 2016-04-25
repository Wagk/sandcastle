/*!************************************************************
Created:	2016/02/22
Intent:
        Reads in a file and determines from that the layout
        of a pattern of modules that forms something (like a ship)
Note:
        Should eventually convert to json and back

**************************************************************/
#ifndef util_parser_h__
#define util_parser_h__

#include <string>
#include <fstream>

#include "modulegroup.h"

class ModuleLayoutParser
{
public:

  ModuleLayoutParser();
  ModuleLayoutParser(const std::string& filestring); //reads in a file and does things to it

  ModuleGroup GetModuleGroup() const;


private:


};

#endif // module_definer_h__
/*!************************************************************
Todo:

  Files should read like a report
  ----------------------------------------
  #Parser v0.1 //should parse comments

  <NAME>

  <FLUFF>

  <EQUIPMENT>
  SENSOR_MODULE
    1 SCIPIO_GROUND_SCANNER
  WEAPON_MODULE
    1 VULKAN_AUTOCANNON_58MM
    1 VULKAN_AUTOCANNON_58MM
    1 OPEN_SLOT
  ENGINE_MODULE
    1 MINSKY_FTL_DRIVE
    1 CHOAM_SUBLIGHT_DRIVE

  <OTHER STUFF>

  ----------------------------------------

**************************************************************/


