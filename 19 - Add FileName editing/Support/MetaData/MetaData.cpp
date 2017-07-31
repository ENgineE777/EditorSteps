
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
		else
		if (prop.type == Float)
		{
			memcpy(prop.value, &prop.defvalue.flt, sizeof(float));
		}
		if (prop.type == String || prop.type == FileName)
		{
			*((std::string*)prop.value) = defStrings[prop.defvalue.string];
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
		else
		if (prop.type == Float)
		{
			float val;
			if (reader->Read(prop.propName.c_str(), val))
			{
				memcpy(prop.value, &val, sizeof(float));
			}
		}
		else
		if (prop.type == String || prop.type == FileName)
		{
			reader->Read(prop.propName.c_str(), *((std::string*)prop.value));
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
		else
		if (prop.type == Float)
		{
			writer->Write(prop.propName.c_str(), *((float*)prop.value));
		}
		else
		if (prop.type == String || prop.type == FileName)
		{
			writer->Write(prop.propName.c_str(), ((std::string*)prop.value)->c_str());
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
			else
			if (prop.type == Float)
			{
				prop.widget = new FloatWidget();
			}
			else
			if (prop.type == String)
			{
				prop.widget = new StringWidget();
			}
			else
			if (prop.type == FileName)
			{
				prop.widget = new FileNameWidget();
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