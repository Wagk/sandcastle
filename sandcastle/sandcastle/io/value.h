#ifndef io_value_h__
#define io_value_h__

#include <string>
#include <vector>
#include <memory>

/*
 * Previously we attempted to unify the interfaces by using a single monolithic
 * object. This time we try to unify the interfaces by using iterators
 *
 * `iterator_base` can probably be a base class, but the core
 * workhorse of the iterator would probably be a templated object
 * much like the std iterators
 *
 */

namespace sandcastle::io::serial
{
    class value;

    class iterator_base
    {
    public:

        virtual value& operator*() = 0;
        virtual const value& operator*() const = 0;
        virtual bool operator==(const iterator_base& rhs) const;

        virtual iterator_base& operator++() = 0;

    private:
    };

    //values can store either actual PODs or other values
    class value
    {
    public:

        using iterator = iterator_base;
        
        value(const std::string& type);

        virtual iterator_base begin() = 0;
        virtual iterator_base end() = 0;

    private:

        std::string _type;
        
    };

	class struct_value : public value
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

    class array_value : public value
    {
        public:

            array_value(const std::string& type);

            value& operator[](size_t index);
            const value& operator[](size_t index) const;

        private:

            std::vector<std::unique_ptr<value>> _values;

    };

    template<typename T>
    class data_value : public value
    {
        public:



            T value() const;

        private:
    }

}

#endif
