
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
		else
		if (prop.type == Integer)
		{
			memcpy(prop.value, &prop.defvalue.integer, sizeof(int));
		}
	}
}

void MetaData::Load(JSONReader* reader)
{
	for (int i = 0; i < properties.size(); i++)
	{
		Property& prop = properties[i];

		if (prop.type == Boolean)
		{
			bool val;
			if (reader->Read(prop.propName.c_str(), val))
			{
				memcpy(prop.value, &val, sizeof(bool));
			}
		}
		else
		if (prop.type == Integer)
		{
			int val;
			if (reader->Read(prop.propName.c_str(), val))
			{
				memcpy(prop.value, &val, sizeof(int));
			}
		}
	}
}

void MetaData::Save(JSONWriter* writer)
{
	for (int i = 0; i < properties.size(); i++)
	{
		Property& prop = properties[i];

		if (prop.type == Boolean)
		{
			writer->Write(prop.propName.c_str(), *((bool*)prop.value));
		}
		else
		if (prop.type == Integer)
		{
			writer->Write(prop.propName.c_str(), *((int*)prop.value));

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
			if (prop.type == Boolean)
			{
				prop.widget = new BoolWidget();
			}
			else
			if (prop.type == Integer)
			{
				prop.widget = new IntWidget();
			}

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