// ChatOnFriday.cpp : main project file.

//#include "stdafx.h"
#include "../include/form.h"

using namespace ChatOnFriday;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 
	Application::Run(gcnew Form1());
	return 0;
}
