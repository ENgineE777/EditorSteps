
#include "MetaData.h"

MetaData::MetaData()
{
	inited = false;
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
			memcpy(prop.value, &prop.defvalue.boolean, 1);
		}
	}
}