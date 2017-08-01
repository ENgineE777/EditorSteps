
#pragma once

#include "Support/Support.h"
#include "Support/json/JSONReader.h"
#include "Support/json/JSONWriter.h"
#include "BoolWidget.h"
#include "IntWidget.h"
#include "FloatWidget.h"
#include "StringWidget.h"

class MetaData
{
public:
	enum Type
	{
		Boolean,
		Integer,
		Float,
		String
	};

	union DefValue
	{
		bool  boolean;
		int   integer;
		float flt;
		int   string;
	};

	std::vector<std::string> defStrings;

	struct Property
	{
		int            offset;
		Type           type;
		DefValue       defvalue;
		byte*          value;
		std::string    catName;
		std::string    propName;
		ProperyWidget* widget;
	};

	bool inited;
	bool widgets_inited;
	std::vector<Property> properties;

	MetaData();
	virtual void Init() = 0;
	void Prepare(void* owner);
	void SetDefValuesPrepare();
	void Load(JSONReader* reader);
	void Save(JSONWriter* writer);
	void PrepareWidgets(EUICategories* parent);
	void HideWidgets();
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

#define BOOL_PROP(className, classMember, defValue, strCatName, strPropName)\
{\
	Property prop;\
	prop.offset = memberOFFSET(className, classMember);\
	prop.type = Boolean;\
	prop.defvalue.boolean = defValue;\
	prop.catName = strCatName;\
	prop.propName = strPropName;\
	properties.push_back(prop);\
}

#define INT_PROP(className, classMember, defValue, strCatName, strPropName)\
{\
	Property prop;\
	prop.offset = memberOFFSET(className, classMember);\
	prop.type = Integer;\
	prop.defvalue.integer = defValue;\
	prop.catName = strCatName;\
	prop.propName = strPropName;\
	properties.push_back(prop);\
}

#define FLOAT_PROP(className, classMember, defValue, strCatName, strPropName)\
{\
	Property prop;\
	prop.offset = memberOFFSET(className, classMember);\
	prop.type = Float;\
	prop.defvalue.flt = defValue;\
	prop.catName = strCatName;\
	prop.propName = strPropName;\
	properties.push_back(prop);\
}

#define STRING_PROP(className, classMember, defValue, strCatName, strPropName)\
{\
	Property prop;\
	prop.offset = memberOFFSET(className, classMember);\
	prop.type = String;\
	defStrings.push_back(defValue);\
	prop.defvalue.string = defStrings.size() - 1;\
	prop.catName = strCatName;\
	prop.propName = strPropName;\
	properties.push_back(prop);\
}