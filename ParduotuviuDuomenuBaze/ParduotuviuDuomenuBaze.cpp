// ParduotuviuDuomenuBaze.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"	// iterpiame reikiamas bibliotekas (#include "stdafx.h" reikalingas tik visual studio)
#include "interfaceGeneration.h"
#include "objectsConfiguration.h"

int main(int argc, char *argv[]) {
	system("color f7");							// koks is pradziu bus konsoles langas
	system("title DATABASE MANAGEMENT TOOL");	// nustatome grazesni konsoles pavadinima
	
	interfaceDrawingLibrary::MenuObjectPathControler runDatabase;	// pagrindinis objektas - runDatabase
	runDatabase.menuConfiguration();	// paleidziame sistema po objekto sukurimo

	return 0;	// programa baigia darba su kodu 0
}