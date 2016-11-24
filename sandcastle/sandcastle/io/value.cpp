#include "value.h"

namespace sandcastle::io::serial
{

    value::value(const std::string& type)
        : _type(type)
    {

    }

    value& value::operator[](const std::string& key)
    {
    }

    const value& value::operator[](const std::string& key) const
    {

    }

    size_t value::find_key_index(const std::string& key)
    {
        size_t hash = std::hash<std::string>{}(key);

        for(size_t i = 0, s < _keypairs.size(); i < s; ++i)
        {
            value_pair& keypair = _keypairs[i];

            if(keypair._hash == hash && keypair._key == key)
            {
                return i;
            }
        }

        return _keypairs.size();
    }

}
