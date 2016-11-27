#ifndef io_value_h__
#define io_value_h__

#include <string>
#include <vector>
#include <map>
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

 //   //values can store either actual PODs or other values
 //   class value
 //   {
 //   public:

 //       value(const std::string& type);

	//	virtual void		string(const std::string&) = 0;
	//	virtual std::string string() const = 0;

 //   private:

 //       std::string _type;
 //       
 //   };

	//class struct_value : public value
	//{
	//public:

 //       struct_value(const std::string& type);

 //       value& operator[](const std::string& key);
 //       const value& operator[](const std::string& key) const;

	//	virtual void		string(const std::string&) override;
	//	virtual std::string string() const override;

	//private:

 //       std::map<std::string, std::unique_ptr<value>> _keypairs;

	//};

 //   class array_value : public value
 //   {
	//public:

	//	array_value(const std::string& type);

	//	value& operator[](size_t index);
	//	const value& operator[](size_t index) const;

	//	virtual void		string(const std::string&) override;
	//	virtual std::string string() const override;

	//private:

	//	std::vector<std::unique_ptr<value>> _values;

 //   };

 //   template<typename T>
 //   class data_value : public value
 //   {
	//public:

	//	virtual void		string(const std::string&) override;
	//	virtual std::string string() const override;

	//private:
	//};

}

#endif
