#include <windows.h>

#include "Support\classFactory.h"

HWND hwnd;

const char g_szClassName[] = "LectureClass";

class BaseClass
{
public:
	virtual const char* GetName() = 0;
};

CLASSFACTORYDEF(BaseClass)

CLASSFACTORYDECL(BaseClass)

class ClassA : public BaseClass
{
public:
	CLASSDECLDIF(BaseClass, ClassA)
		virtual const char* GetName() { return "A"; };
};
CLASSDECLDECL(BaseClass, ClassA)

class ClassB : public BaseClass
{
public:
	CLASSDECLDIF(BaseClass, ClassB)
		virtual const char* GetName() { return "B"; };
};
CLASSDECLDECL(BaseClass, ClassB)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	BaseClass* b = ClassFactoryBaseClass::Create("ClassB");

	const char* name = b->GetName();


	return 0;
}