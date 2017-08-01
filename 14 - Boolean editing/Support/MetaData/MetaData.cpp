
#include "MetaData.h"

MetaData::MetaData()
{
	inited = false;
	widgets_inited = false;
}

void MetaData::Prepare(void* owner)
{
	if (!inited)
	{
		Init();
		inited = true;
	}

	for (int i = 0; i < properties.size(); i++)
	{
		Property& prop = properties[i];
		prop.value = (byte*)owner + prop.offset;
	}
}

void MetaData::SetDefValuesPrepare()
{
	for (int i = 0; i < properties.size(); i++)
	{
		Property& prop = properties[i];

		if (prop.type == Boolean)
		{
			memcpy(prop.value, &prop.defvalue.boolean, sizeof(bool));
		}
	}
}

void MetaData::PrepareWidgets(EUICategories* parent)
{
	for (int i = 0; i < properties.size(); i++)
	{
		Property& prop = properties[i];

		if (!widgets_inited)
		{
			prop.widget = new BoolWidget();
			prop.widget->Init(parent, prop.catName.c_str(), prop.propName.c_str());
		}

		prop.widget->SetData(prop.value);
		prop.widget->Show(true);
	}

	if (!widgets_inited)
	{
		widgets_inited = true;
	}
}

void MetaData::HideWidgets()
{
	if (!widgets_inited)
	{
		return;
	}

	for (int i = 0; i < properties.size(); i++)
	{
		properties[i].widget->Show(false);
	}
}