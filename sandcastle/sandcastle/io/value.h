#ifndef io_value_h__
#define io_value_h__

#include <string>
#include <vector>
#include <memory>

namespace sandcastle::io::serial
{

    //values can store either actual PODs or other values
    class value_base
    {
        public:

        private:
    };

	class struct_value : public value_base
	{
	public:

        nested_value(const std::string& type);

        value& operator[](const std::string& key);
        const value& operator[](const std::string& key) const;

	private:

        size_t find_key_index(const std::string& key);

        struct value_pair
        {
            size_t                  _hash;
            std::string             _key;
            std::unique_ptr<value>  _value;
        };

        std::string             _type;
        std::vector<value_pair> _keypairs;

	};

    class array_value : public value_base
    {

    };

    class stored_value : public value_base
    {

    }

    //example
    void operator>>(value val, json son)
    {
        
    }

}

#endif
