#ifndef serial_json_h__
#define serial_json_h__

#include <json/json.h>

#include <io/statedata.h>
#include <io/modifydata.h>

namespace sandcastle::io::serial
{

	Json::Value to_json(const state_data&);
	modify_data from_json(const Json::Value&);

}

#endif