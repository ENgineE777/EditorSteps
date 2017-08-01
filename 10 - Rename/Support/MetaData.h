
#pragma once

#include "Support/Support.h"

class MetaData
{
public:
	enum Type
	{
		Boolean
	};

	struct Str
	{
		std::string str;
	};

	union DefValue
	{
		bool boolean;
	};

	struct Property
	{
		int      offset;
		Type     type;
		DefValue defvalue;
		byte*    value;
	};

	bool inited;
	std::vector<Property> properties;

	MetaData();
	virtual void Init() = 0;
	void Prepare(void* owner);
	void SetDefValuesPrepare();
};

#define META_DATA_DECL(className)\
class MetaData##className : public MetaData\
{\
public:\
	virtual void Init();\
};\
static MetaData##className meta_data;\
virtual MetaData* GetMetaData();

#define META_DATA_DESC(className)\
className##::MetaData##className className##::meta_data;\
MetaData* className##::GetMetaData() { return &className##::meta_data; };\
void className##::MetaData##className##::Init()\
{

#define META_DATA_DESC_END()\
}


#define memberOFFSET(s,m) ((size_t)(&reinterpret_cast<s*>(100000)->m)-100000)

#define BOOL_PROP(className, classMember, defValue)\
{\
	Property prop;\
	prop.offset = memberOFFSET(className, classMember);\
	prop.type = Boolean;\
	prop.defvalue.boolean = defValue;\
	properties.push_back(prop);\
}