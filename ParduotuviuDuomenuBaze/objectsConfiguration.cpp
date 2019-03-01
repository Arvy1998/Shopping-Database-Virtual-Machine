#include "stdafx.h"
#include "interfaceGeneration.h"
#include "objectsConfiguration.h"

namespace interfaceDrawingLibrary { // vardu sritis visur bendra kad butu patogu susieti .h failus, vartotojas, rasydamas programa su siuo "duombazes paketu" gales
									// lengvai issikviesti objektus, juos tinkinti bei tures daugiau laisves renkantis kintamuju/funkciju/klasiu ir t.t. pavadinimus
	ActiveMenuControler mainMenu;	// sukuriame objektus skirtingiems meniu langams
	ActiveMenuControler mainInformationMenu;
	ActiveMenuControler exitConfirmationMenu;
	ActiveMenuControler mainFunctionsInformationMenu;
	ActiveMenuControler mainControlsInformationMenu;
	ActiveMenuControler mainAboutInformationMenu;
	ActiveMenuControler mainVersionInformationMenu;
	ActiveMenuControler databaseContentMenu;
	ActiveMenuControler databaseMenuTable;
	ActiveMenuControler dataSettingsMenu;
	ActiveMenuControler changingDataAttributesMenu;
	ActiveMenuControler changingNameTable;
	ActiveMenuControler attributeNameChangeConfirmationTable;
	ActiveMenuControler itemDeleteConfirmationMenu;
	ActiveMenuControler itemDeletedConfirmationTable;
	ActiveMenuControler addNewItemTable;
	ActiveMenuControler itemCreatedConfirmationTable;
	ActiveMenuControler searchForKeywordMenu;
	ActiveMenuControler searchResultTable;
	ActiveMenuControler searchResultsWarningMessage;
	ActiveMenuControler menuAskingForAllItemDeletion;
	ActiveMenuControler moreOptionsMenu;
	ActiveMenuControler firstElementIndicatorMenu;

	HANDLE consoleExitInterface = GetStdHandle(STD_OUTPUT_HANDLE);	// graziam isejimui reikalingi parametrai
	COORD exitCursorPosition = { 8, 15 };

	string temporaryAttributeName = " ";	// laikinas naujo atributo vardas

	short databaseItemValue{ 0 }, selectedFile{ 0 };	// duombazes objekto pasirinkimo indeksas ir pasirinkto failo numeris yra globalus

	vector <string> existingFilesListForManagement{ "FOOD_PRODUCTS_DATABASE",	// failu vardai
		"FURNITURE_PRODUCTS_DATABASE",
		"LEISURE_PRODUCTS_DATABASE",
		"PERFUME_PRODUCTS_DATABASE",
		"ELECTRONICS_PRODUCTS_DATABASE ",
		"COMPUTER_COMPONENTS_DATABASE",
		"SPORTS_PRODUCTS_DATABASE",
		"AUDIO_COMPONENTS_DATABASE",
		"SPECIAL_PRODUCTS_DATABASE",
		"CLOTHES_DATABASE",
		"HYGIENIC_PRODUCTS_DATABASE"
	};

	vector <string> temporaryNewAttributesValues{" ", " ", " ", " ", " ", " "};

	void MenuObjectPathControler::fancyExitConfiguration() {	// funkcija grazesniam isejimui
		exitCursorPosition = { 8, 15 };
		SetConsoleTextAttribute(consoleExitInterface, 0b00001111);	//default spalva
		SetConsoleCursorPosition(consoleExitInterface, exitCursorPosition);
	};

	void MenuObjectPathControler::menuConfiguration() {		// pagrindinio meniu valdymas
		displayMainMenu(true);
		if (mainMenu.getControlerIndex() == 0) {	// ejimas i duombaziu sarasa
			databasePath();
		}
		if (mainMenu.getControlerIndex() == 1) {	// ejimas i informacini meniu langa
			informationTablePath();
		}
		if (mainMenu.getControlerIndex() == 2) {	// isejimas
			displayMainMenu(false);
			displayExitConfirmationMenu(true);
			if (exitConfirmationMenu.getControlerIndex() == 0) {	// patvirtinus isejima, programa duoda exit code 0
				fancyExitConfiguration();
				exit(0);
			}
			if (exitConfirmationMenu.getControlerIndex() == 1) {	// galima atsaukti isejima is programos
				resetConsole();
				menuConfiguration();
			}
		}
	};

	void MenuObjectPathControler::informationTablePath() {	// informacine skiltis
		displayMainMenu(false);
		displayMainInformationMenu(true);
		if (mainInformationMenu.getControlerIndex() == 0) {		// toliau pasirinkus atitinkama meniu numeri, iskvieciamas atitinkamas objektas rodymui ir meniu "medzio" interpretacijai
			displayMainInformationMenu(false);			// funkciju informacija
			displayMainFunctionsInformationMenu(true);
			if (mainFunctionsInformationMenu.getControlerIndex() == 0) {
				resetConsole();
				informationTablePath();
			}
		}
		if (mainInformationMenu.getControlerIndex() == 1) {			// kontroliu informacija
			displayMainInformationMenu(false);
			displayMainControlsInformationMenu(true);
			if (mainControlsInformationMenu.getControlerIndex() == 0) {
				resetConsole();
				informationTablePath();
			}
		}
		if (mainInformationMenu.getControlerIndex() == 2) {			// informacija "APIE"
			displayMainInformationMenu(false);
			displayMainAboutInformationMenu(true);
			if (mainAboutInformationMenu.getControlerIndex() == 0) {
				resetConsole();
				informationTablePath();
			}
		}
		if (mainInformationMenu.getControlerIndex() == 3) {			// versijos informacija
			displayMainInformationMenu(false);
			displayMainVersionInformationMenu(true);
			if (mainAboutInformationMenu.getControlerIndex() == 0) {
				resetConsole();
				informationTablePath();
			}
		}
		if (mainInformationMenu.getControlerIndex() == 4) {	// ejimas atgal i pagrindini meniu
			resetConsole();
			menuConfiguration();
		}
	};

	void MenuObjectPathControler::databasePath() {	// duombazes valdymo funkcija
		displayMainMenu(false);
		displayDatabaseContentMenu(true);	// ijungiame duombazes turinio pasirinkima
		getFileSelectionFromInterface(databaseContentMenu.getControlerIndex());	// nuskaitome failus ir juose esancius duomenis isimetame i objektu vektoriu
		if (databaseContentMenu.getControlerIndex() < 11) {	// jeigu kontroles indeksas mazesnis uz 10, vadinasi pasirinkome faila
			selectedFile = databaseContentMenu.getControlerIndex();
			displayDatabaseContentMenu(false);
			databaseTablePath();
		}
		if (databaseContentMenu.getControlerIndex() == 11) {	// kitu atveju isejome i pagrindini meniu
			resetConsole();
			menuConfiguration();
		}
	};

	void MenuObjectPathControler::databaseTablePath() {	// duombazes reliacines aibes interfeisas
		displayDatabaseTableMenu(true);
		if (databaseMenuTable.getControlerIndex() == 0) {	// ejimas atgal i pagrindini meniu
			resetConsole();
			menuConfiguration();
		}
		if (databaseMenuTable.getControlerIndex() == 1) {		// meniu punktas, issiskleidziantis i daugiau pasirinkimu
			databaseMenuTitleUnactive();
			displayMoreOptionsMenu(true);		
			if (moreOptionsMenu.getControlerIndex() == 0) {		// sukurimas bazinis objektas, kad nuo jo pradeti tvarkyti duomenis (sis nustatymas budingas tik failams, turintiems 0 objektu)
				temporaryNewAttributesValues = { "-", "-", "-", "-", "-", "-" };
				createFirstObject(temporaryNewAttributesValues, this->getItemDataList());
				overwriteSelectedFile(existingFilesListForManagement[selectedFile], this->getItemDataList());
				temporaryNewAttributesValues = { " ", " ", " ", " ", " ", " " };	// nustate tuscius vardus pirmiesiems atributams juos vel perstatome i tuscius
				displayMoreOptionsMenu(false);
				displayConfirmationAboutCreatingFirstListElement(true);
				if (firstElementIndicatorMenu.getControlerIndex() == 0) {	// numygus OK, gryztame i duombaze su jau pirmuoju baziniu elementu, taciau jis neturi atributu pavadinimu, todel ji privalu pervadinti
					pathFromChangingAttributeToDatabase();
				}
			}
			if (moreOptionsMenu.getControlerIndex() == 1) {		// ejimas atgal i duombazeje esanciu failu sarasa
				resetConsole();
				databasePath();
			}
		}
		if (databaseMenuTable.getControlerIndex() >= 2) {	// toliau prasideda paciu objektu pasirinkimas is duombazes
			databaseMenuTitleUnactive();
			databaseChangingChoices();
		}
	};

	void MenuObjectPathControler::databaseChangingChoices() {	// ka rodome, kai pasirenkame bet kuri objekta, jau irasyta i reliacine aibe
		displayDataSettingsMenu(true);
		databaseItemValue = databaseMenuTable.getControlerIndex() - 2; // gaunu saraso elemento, su kuriuo dirbsime, indekso numeri
		if (dataSettingsMenu.getControlerIndex() == 0) {	// 0 ir 1 prideda nauju objektu i vektoriu bei juos iraso i duombaze kaip naujus duomenis
			displayDataSettingsMenu(false);
			displayItemCreationMenu(false);
			activeCreationTitle();
			requestForMultiInput();
			displayItemCreationMenu(true);
			displayItemCreationMenu(false);
			if (addNewItemTable.getControlerIndex() == 0) {		// ar objektas sukurtas sekmingai -> meniu langas
				displayItemCreationConfirmationMenu(true);
				if (itemCreatedConfirmationTable.getControlerIndex() == 0) {
					addNewItemAbove(this->getItemDataList(), temporaryNewAttributesValues, databaseItemValue);
					overwriteSelectedFile(existingFilesListForManagement[selectedFile], this->getItemDataList());
					pathFromChangingAttributeToDatabase();
				}
				else pathFromChangingAttributeToDatabase();
			}
			else pathFromChangingAttributeToDatabase();
		}
		if (dataSettingsMenu.getControlerIndex() == 1) {
			displayDataSettingsMenu(false);
			displayItemCreationMenu(false);
			activeCreationTitle();
			requestForMultiInput();
			displayItemCreationMenu(true);
			displayItemCreationMenu(false);
			if (addNewItemTable.getControlerIndex() == 0) {		// ar objektas sukurtas sekmingai -> meniu langas
				displayItemCreationConfirmationMenu(true);
				if (itemCreatedConfirmationTable.getControlerIndex() == 0) {
					addNewItemBellow(this->getItemDataList(), temporaryNewAttributesValues, databaseItemValue);
					overwriteSelectedFile(existingFilesListForManagement[selectedFile], this->getItemDataList());
					pathFromChangingAttributeToDatabase();
				}
				else pathFromChangingAttributeToDatabase();
			}
			else pathFromChangingAttributeToDatabase();
		}
		if (dataSettingsMenu.getControlerIndex() == 2) {	// pasirenkamas atributu pervadinimo valdiklis
			displayDataSettingsMenu(false);
			attributesChangingPath();
		}
		if (dataSettingsMenu.getControlerIndex() == 3) {	// objektu naikinimas
			displayDataSettingsMenu(false);
			displayMenuAskingForItemDeletion(true);
			itemDeletionHandle();
		}
		if (dataSettingsMenu.getControlerIndex() == 4) {
			displayDataSettingsMenu(false);
			displayMenuAskingForAllItemDeletion(true);
			if (menuAskingForAllItemDeletion.getControlerIndex() == 0) {
				deleteWholeTable(this->getItemDataList());
				overwriteSelectedFile(existingFilesListForManagement[selectedFile], this->getItemDataList());
				pathFromChangingAttributeToDatabase();
			}
			else pathFromChangingAttributeToDatabase();
		}
		if (dataSettingsMenu.getControlerIndex() == 5) {	// objektu paieska
			displayDataSettingsMenu(false);
			displayEnterSearchKeywordWindow(false, " ");
			activeKeywordSearcher();	// aktyvus meniu su paieskos laukeliu pavadinimas
			requestForKeyword();
			displayEnterSearchKeywordWindow(true, temporaryAttributeName);
			if (searchForKeywordMenu.getControlerIndex() == 0) {
				displayEnterSearchKeywordWindow(false, temporaryAttributeName);
				pathFromWarningMessageToSearchResults();
			}
			else pathFromChangingAttributeToDatabase();
		}
		if (dataSettingsMenu.getControlerIndex() == 6) {	// vektoriaus rikiavimas abeceles tvarka
			displayDataSettingsMenu(false);
			sortExistingVector(this->getItemDataList());
			overwriteSelectedFile(existingFilesListForManagement[selectedFile], this->getItemDataList());
			pathFromChangingAttributeToDatabase();
		}
		if (dataSettingsMenu.getControlerIndex() == 7) {	// atgal i duombazes lango rodini
			pathFromChangingAttributeToDatabase();
		}
	};

	void MenuObjectPathControler::pathFromWarningMessageToSearchResults() {
		displayDatabaseSearchResult(true);
		if (searchResultTable.getControlerIndex() == 0) {
			resetConsole();
			temporaryAttributeName = " ";
			menuConfiguration();
		}
		if (searchResultTable.getControlerIndex() == 1) {
			temporaryAttributeName = " ";
			createItemOutputString(this->getItemDataList());
			pathFromChangingAttributeToDatabase();
		}
		if (searchResultTable.getControlerIndex() > 1) {
			displayDatabaseSearchResult(false);
			displaySearchResultsWarningMessage(true);
			if (searchResultsWarningMessage.getControlerIndex() == 0) {
				pathFromWarningMessageToSearchResults();
			}
		}
	};

	void MenuObjectPathControler::pathFromAttributesSelectionToRename() {	//	leidzia pasirinkus norima pervadinti atributa eiti i pervadinimo procesa
		displayAttributeChangingSelectionMenu(false);
		displayAttributeChangingWindow(false, " "); // is pradziu neturime isivede jokios string reiksmes, todel i funkcija paduodame ' "" '
		changingNameTableTitleActive();
	};

	void MenuObjectPathControler::changingNameTableTitleActive() { // funkcija reikalinga interpretuoti, jog kol vyksta vartotojo ivedimas, langas islieka aktyvus
		changingNameTable.setTitleActive(true);
		changingNameTable.displayMenuTitle("            RENAME CONFIRMATION            ");
	};

	void MenuObjectPathControler::changingNameTableTitleUnactive() {	// funkcija reikalinga interpretuoti, jog kol vyksta vartotojo ivedimas, langas islieka ne-aktyvus
		changingNameTable.setTitleActive(false);
		changingNameTable.displayMenuTitle("            RENAME CONFIRMATION            ");
	};

	void MenuObjectPathControler::attributesChangingPath() {	// 0-5 pasirenkame, koki atributa norime keisti ir kiekvienu zingsniu atliekame analogija
		displayAttributeChangingSelectionMenu(true);	// atveriame atributu pasirinkima ir visais atvejais darome analogiskus zingsnius priklausomai nuo kontroles indekso
		if (changingDataAttributesMenu.getControlerIndex() == 0) {	// itemName atributas
			renameAnyAttribute();
		}
		if (changingDataAttributesMenu.getControlerIndex() == 1) {	// itemPriceEuros atributas
			renameAnyAttribute();
		}
		if (changingDataAttributesMenu.getControlerIndex() == 2) {	// itemType atributas
			renameAnyAttribute();
		}
		if (changingDataAttributesMenu.getControlerIndex() == 3) {	// itemState atributas
			renameAnyAttribute();
		}
		if (changingDataAttributesMenu.getControlerIndex() == 4) {	// itemCode atributas
			renameAnyAttribute();
		}
		if (changingDataAttributesMenu.getControlerIndex() == 5) {	// isExist atributas
			renameAnyAttribute();
		}
		if (changingDataAttributesMenu.getControlerIndex() == 6) {	// isejimas atgal i reliacine lentele
			pathFromChangingAttributeToDatabase();
		}
	};

	void MenuObjectPathControler::renameAnyAttribute() {	// si funkcija nustato, kuri atributa pervadinsime pagal pasirinkta kontrolerio indekso numeri
		pathFromAttributesSelectionToRename();
		requestForInput(); // supakuota funkcija
		displayAttributeChangingWindow(true, temporaryAttributeName);
		changingNameTableTitleUnactive();
		if (changingNameTable.getControlerIndex() == 0) {	// jeigu sutinkame pervadinti atributa
			renameAttributeAndOverwriteFile();
			if (attributeNameChangeConfirmationTable.getControlerIndex() == 0) {	// patvirtinimas, jog atributas buvo pervadintas
				pathFromChangingAttributeToDatabase();
			}
		}
		else pathFromChangingAttributeToDatabase();		// jeigu atmetame atributo pervadinima, griztame atgal i duombaze
	};

	void MenuObjectPathControler::renameAttributeAndOverwriteFile() {	// pervadintas atributas yra irasomas i faila
		changeAttributeName(this->getItemDataList(), databaseItemValue, changingDataAttributesMenu.getControlerIndex(), temporaryAttributeName); // kvieciame atributo verdo keitimo funkcija
		overwriteSelectedFile(existingFilesListForManagement[selectedFile], this->getItemDataList());	// pakeitimai issaugojami faile
		displayAttributesChangingConfirmation(true);	// sutikimo apie tai, kad atributo varda pavyko pakeisti, meniu "pop-outas"
	};

	void MenuObjectPathControler::requestForInput() {	// laukimas. kol vartotojas ives input'a
		exitCursorPosition.X = 35; exitCursorPosition.Y = 28;
		SetConsoleCursorPosition(consoleExitInterface, exitCursorPosition); SetConsoleTextAttribute(consoleExitInterface, 0b10010000);
		cin >> temporaryAttributeName;
	};

	void MenuObjectPathControler::requestForKeyword() {
		exitCursorPosition.X = 34; exitCursorPosition.Y = 25;
		SetConsoleCursorPosition(consoleExitInterface, exitCursorPosition); SetConsoleTextAttribute(consoleExitInterface, 0b10010000);
		cin >> temporaryAttributeName;
	};

	void MenuObjectPathControler::requestForMultiInput() {	// keleto reiksmiu ivedimas
		string userInputString;
		exitCursorPosition.X = 43; exitCursorPosition.Y = 26;
		SetConsoleCursorPosition(consoleExitInterface, exitCursorPosition); SetConsoleTextAttribute(consoleExitInterface, 0b10010000);
		cin >> userInputString; temporaryNewAttributesValues[0] = userInputString; // ITEM NAME
		exitCursorPosition.X = 39; exitCursorPosition.Y = 28; SetConsoleCursorPosition(consoleExitInterface, exitCursorPosition);
		cin >> userInputString; temporaryNewAttributesValues[1] = userInputString; // ITEM PRICE
		exitCursorPosition.X = 38; exitCursorPosition.Y = 30; SetConsoleCursorPosition(consoleExitInterface, exitCursorPosition);
		cin >> userInputString; temporaryNewAttributesValues[2] = userInputString; // ITEM TYPE
		exitCursorPosition.X = 39; exitCursorPosition.Y = 32; SetConsoleCursorPosition(consoleExitInterface, exitCursorPosition);
		cin >> userInputString; temporaryNewAttributesValues[3] = userInputString; // ITEM STATE
		exitCursorPosition.X = 43; exitCursorPosition.Y = 34; SetConsoleCursorPosition(consoleExitInterface, exitCursorPosition);
		cin >> userInputString; temporaryNewAttributesValues[4] = userInputString; // ITEM CODE
		exitCursorPosition.X = 39; exitCursorPosition.Y = 36; SetConsoleCursorPosition(consoleExitInterface, exitCursorPosition);
		cin >> userInputString; temporaryNewAttributesValues[5] = userInputString; // DO ITEM EXIST
	};

	void MenuObjectPathControler::pathFromChangingAttributeToDatabase() {	// ejimas atgal is atributo keitimo i duombazes langa
		temporaryAttributeName = " "; // po galimo pervadinimo liko kintamojo reiksme, todel ja atnaujiname
		temporaryNewAttributesValues = { "", "", "", "", "", "" }; // ta pati padarome ir su vektoriumi, skirtam laikinajai vartotojo isvesciai laikyti
		resetConsole();
		displayMainMenu(false);
		displayDatabaseContentMenu(false);
		databaseTablePath();
	};

	void MenuObjectPathControler::resetConsole() { // funkcija reset'ina (atnaujina) konsoles langa, kad panaikintu viena ant kito uzlipusius meniu langus
		system("cls"); 
		system("color f7");
	};

	void MenuObjectPathControler::databaseMenuTitleUnactive() {		// nustato duombazes langa ne-aktyvu
		databaseMenuTable.setTitleActive(false);
		databaseMenuTable.displayMenuTitle("                                DATA MANAGEMENT                                ");
	};

	void MenuObjectPathControler::itemDeletionHandle() {	// funkcija, turinti objekto trynimo kontroleri
		displayMenuAskingForItemDeletion(false);
		if (itemDeleteConfirmationMenu.getControlerIndex() == 0) {
			displayItemDeletionConfirmationMenu(true);
			deleteItemFromList(this->getItemDataList(), databaseItemValue);
			overwriteSelectedFile(existingFilesListForManagement[selectedFile], this->getItemDataList()); // pakeitimai issaugojami faile
			pathFromChangingAttributeToDatabase();
		}
		else pathFromChangingAttributeToDatabase();		// ta pati funkcija tinka ir siai situacijai, nes joje nera nurodymo, is kur isejome
	};

	void MenuObjectPathControler::activeCreationTitle() {
		addNewItemTable.setTitleActive(true);
		addNewItemTable.displayMenuTitle("             ADD NEW ITEM              ");
	};

	void MenuObjectPathControler::unactiveCreationTitle() {
		addNewItemTable.setTitleActive(false);
		addNewItemTable.displayMenuTitle("             ADD NEW ITEM              ");
	};

	void MenuObjectPathControler::activeKeywordSearcher() {
		searchForKeywordMenu.setTitleActive(true);
		searchForKeywordMenu.displayMenuTitle("            ENTER SEARCH KEYWORD           ");
	};

	void MenuObjectPathControler::displayMainMenu(bool isActive) {	// pagrindinis meniu langas
		mainMenu.setTitleActive(isActive);
		mainMenu.setMenuActivity(isActive);
		mainMenu.setMenuSize(40, 9);
		mainMenu.setMenuPosition(6, 3);
		mainMenu.displayMenuItemsTable();
		mainMenu.setMenuItemList({ "         VIEW DATABASE CONTENT         ", "           MAIN INSTRUCTIONS           ", "                 EXIT                  " });
		mainMenu.displayMenuTitle("               MAIN MENU               ");
		mainMenu.displayMenuPath(".../main_menu");
		mainMenu.displayMenuWithItems();
	};

	void MenuObjectPathControler::displayMainInformationMenu(bool isActive) {	// pagrindines informacijos skilties valdiklis
		mainInformationMenu.setTitleActive(isActive);
		mainInformationMenu.setMenuActivity(isActive);
		mainInformationMenu.setMenuSize(40, 11);
		mainInformationMenu.setMenuPosition(7, 6);
		mainInformationMenu.displayMenuItemsTable();
		mainInformationMenu.setMenuItemList({ "               FUNCTIONS               ", "               CONTROLS                ", "                ABOUT                  ", "               VERSION                 ", "           BACK TO MAIN MENU           " });
		mainInformationMenu.displayMenuTitle("           MAIN INFORMATION            ");
		mainInformationMenu.displayMenuPath(".../main_menu/main_instructions");
		mainInformationMenu.displayMenuWithItems();
	};

	void MenuObjectPathControler::displayExitConfirmationMenu(bool isActive) {	// sutikimo iseiti is programos funkcija
		exitConfirmationMenu.setTitleActive(isActive);
		exitConfirmationMenu.setMenuActivity(isActive);
		exitConfirmationMenu.setMenuPosition(7, 6);
		exitConfirmationMenu.setMenuSize(40, 10);
		exitConfirmationMenu.setAllignmentStyle(2);
		exitConfirmationMenu.setText("    Are you sure you want to exit?");
		exitConfirmationMenu.displayTextSignalTables();
		exitConfirmationMenu.setMenuItemList({ "  YES   ", "   NO   " });
		exitConfirmationMenu.displayMenuTitle("           EXIT CONFIRMATION           ");
		exitConfirmationMenu.displayMenuPath(".../main_menu/exit_confirm");
		exitConfirmationMenu.displayMenuWithTwoButtons();
	};

	void MenuObjectPathControler::displayMainFunctionsInformationMenu(bool isActive) {	// objektas su informacija apie pagrindines manipuliacijos su duomenimis funkcija
		mainFunctionsInformationMenu.setTitleActive(isActive);
		mainFunctionsInformationMenu.setMenuActivity(isActive);
		mainFunctionsInformationMenu.setMenuPosition(8, 9);
		mainFunctionsInformationMenu.setMenuSize(40, 23);
		mainFunctionsInformationMenu.setTextWrapping(false);
		mainFunctionsInformationMenu.setAllignmentStyle(2);
		mainFunctionsInformationMenu.setText("1] View existing list files: shows\n database content; 2] Edit list file:\n enables user to edit existing file\n and view its content; 3] Add item:\n function allows user to add more items\n into list file; 4] Remove item:\n function allows user to delete item\n from the file; 5] Edit item: lets user\n to change items attributes and item\n itself; 6] Search items: searches for\n similar or identic attributes and\n outputs them on another table. 7] Sort\n items: sorts out all list in\n alphabetical order.");
		mainFunctionsInformationMenu.displayTextInstructions();
		mainFunctionsInformationMenu.setMenuItemList({ "   OK   " });
		mainFunctionsInformationMenu.displayMenuTitle("               FUNCTIONS               ");
		mainFunctionsInformationMenu.displayMenuPath(".../main_menu/main_instructions/func...");
		mainFunctionsInformationMenu.displayMenuWithOneButton();
	};

	void MenuObjectPathControler::displayMainControlsInformationMenu(bool isActive) {	// objektas su informacija apie kontrole
		mainControlsInformationMenu.setTitleActive(isActive);
		mainControlsInformationMenu.setMenuActivity(isActive);
		mainControlsInformationMenu.setMenuPosition(8, 9);
		mainControlsInformationMenu.setMenuSize(40, 17);
		mainControlsInformationMenu.setTextWrapping(false);
		mainControlsInformationMenu.setAllignmentStyle(2);
		mainControlsInformationMenu.setText("User can use UP (^) and DOWN (v)\n arrows to move trough menus and\n buttons. To select any item from menu\n list press X. To input text, first\n type any word, then press ENTER. Menu\n is designed for average user so it\n doesn't require advanced knowledge to\n use this database. Good luck!");
		mainControlsInformationMenu.displayTextInstructions();
		mainControlsInformationMenu.setMenuItemList({ "   OK   " });
		mainControlsInformationMenu.displayMenuTitle("               CONTROLS                ");
		mainControlsInformationMenu.displayMenuPath(".../main_menu/main_instructions/cont...");
		mainControlsInformationMenu.displayMenuWithOneButton();
	};

	void MenuObjectPathControler::displayMainAboutInformationMenu(bool isActive) {		// siame meniu lange yra informacija apie tai, kas kure sia programa bei ka ji interpretuoja
		mainAboutInformationMenu.setTitleActive(isActive);
		mainAboutInformationMenu.setMenuActivity(isActive);
		mainAboutInformationMenu.setMenuPosition(8, 9);
		mainAboutInformationMenu.setMenuSize(40, 14);
		mainAboutInformationMenu.setTextWrapping(false);
		mainAboutInformationMenu.setAllignmentStyle(2);
		mainAboutInformationMenu.setText("* This virtual machine represents\n shopping database;\n * Creator: Arvydas Baranauskas;\n * Group: PRIF-17/2;\n * Creation years: 2018.");
		mainAboutInformationMenu.displayTextInstructions();
		mainAboutInformationMenu.setMenuItemList({ "   OK   " });
		mainAboutInformationMenu.displayMenuTitle("                 ABOUT                 ");
		mainAboutInformationMenu.displayMenuPath(".../main_menu/main_instructions/abou...");
		mainAboutInformationMenu.displayMenuWithOneButton();
	};

	void MenuObjectPathControler::displayMainVersionInformationMenu(bool isActive) {	// pagrindines versijos aktyvusis langas
		mainVersionInformationMenu.setTitleActive(isActive);
		mainVersionInformationMenu.setMenuActivity(isActive);
		mainVersionInformationMenu.setMenuPosition(8, 9);
		mainVersionInformationMenu.setMenuSize(40, 13);
		mainVersionInformationMenu.setTextWrapping(false);
		mainVersionInformationMenu.setAllignmentStyle(2);
		mainVersionInformationMenu.setText("This version is currently in beta\n stage 0.02.1ver and are still being\n tested. If you see any bug, please\n report it so creator could fix that.");
		mainVersionInformationMenu.displayTextInstructions();
		mainVersionInformationMenu.setMenuItemList({ "   OK   " });
		mainVersionInformationMenu.displayMenuTitle("                VERSION                ");
		mainVersionInformationMenu.displayMenuPath(".../main_menu/main_instructions/vers...");
		mainVersionInformationMenu.displayMenuWithOneButton();
	};

	void MenuObjectPathControler::displayDatabaseTableMenu(bool isActive) {	// reliacines aibes atvaizdavimo objektas [dinaminis]
		databaseMenuTable.setMenuPosition(8, 9);
		databaseMenuTable.setMenuSize(80, (this->itemDataList.size() * 2) + 10); // reliacines lenteles meniu tampa dinaminis (priklauso nuo turimu duomenu)
		databaseMenuTable.drawDatabaseMenuTableBorder();
		databaseMenuTable.setTitleActive(isActive);
		databaseMenuTable.setMenuActivity(isActive);
		databaseMenuTable.displayMenuTitle("                                DATA MANAGEMENT                                ");
		if (this->itemDataList.size() == 0) databaseMenuTable.displayMenuPath(".../main_menu/database_content/manage_selected_file/warning_empty");
		else databaseMenuTable.displayMenuPath(".../main_menu/database_content/manage_selected_file");
		databaseMenuTable.setMenuItemList({ "  BACK TO MENU   ", "  MORE OPTIONS   " });
		databaseMenuTable.displayDatabaseMenu();
	};

	void MenuObjectPathControler::displayDatabaseContentMenu(bool isActive) {		// meniu, kuriame pavaziduoti visi imanomi pasirinkimui failai, su kuriais atliekami tolimesni veiksmai duombazeje
		databaseContentMenu.setTitleActive(isActive);
		databaseContentMenu.setMenuActivity(isActive);
		databaseContentMenu.setMenuSize(40, 18);
		databaseContentMenu.setMenuPosition(7, 6);
		databaseContentMenu.displayMenuItemsTable();
		databaseContentMenu.setMenuItemList({ "        FOOD PRODUCTS DATABASE         ", "      FURNITURE PRODUCTS DATABASE      ", "       LEISURE PRODUCTS DATABASE       ", "       PERFUME PRODUCTS DATABASE       ", "     ELECTRONICS PRODUCTS DATABASE     ", "      COMPUTER COMPONENTS DATABASE     ", "        SPORTS PRODUCTS DATABASE       ", "        AUDIO COMPONENTS DATABASE      " , "        SPECIAL PRODUCTS DATABASE      ", "            CLOTHES DATABASE           ", "       HYGIENIC PRODUCTS DATABASE      ","           BACK TO MAIN MENU           " });
		databaseContentMenu.displayMenuTitle("           DATABASE CONTENT            ");
		databaseContentMenu.displayMenuPath(".../main_menu/database_content");
		databaseContentMenu.displayMenuWithItems();
	};

	void MenuObjectPathControler::displayDataSettingsMenu(bool isActive) {		// manipuliacijos su duomenimis pasirinkimo meniu valdiklis
		dataSettingsMenu.setTitleActive(isActive);
		dataSettingsMenu.setMenuActivity(isActive);
		dataSettingsMenu.setMenuSize(40, 14);
		dataSettingsMenu.setMenuPosition(30, 16);
		dataSettingsMenu.displayMenuItemsTable();
		dataSettingsMenu.setMenuItemList({ "          ADD NEW ITEM ABOVE           ", "          ADD NEW ITEM BELOW           ", "         CHANGE SELECTED ITEM          ", "         DELETE SELECTED ITEM          ", "           DELETE ALL ITEMS            ", "            SEARCH FOR ITEM            ", "           SORT CURRENT LIST          ", "           BACK TO DATABASE            " });
		dataSettingsMenu.displayMenuTitle("             DATA SETTINGS             ");
		dataSettingsMenu.displayMenuPath(".../manage_selected_file/data_settings");
		dataSettingsMenu.displayMenuWithItems();
	};

	void MenuObjectPathControler::displayAttributeChangingSelectionMenu(bool isActive) {	// pasirinkimo, koki atributa norite pakeisti, meniu valdiklis
		changingDataAttributesMenu.setTitleActive(isActive);
		changingDataAttributesMenu.setMenuActivity(isActive);
		changingDataAttributesMenu.setMenuSize(40, 13);
		changingDataAttributesMenu.setMenuPosition(31, 19);
		changingDataAttributesMenu.displayMenuItemsTable();
		changingDataAttributesMenu.setMenuItemList({ "              CHANGE NAME              ", "              CHANGE PRICE             ", "              CHANGE TYPE              ", "              CHANGE STATE             ", "            CHANGE ITEM CODE           ","           CHANGE EXIST STATE          ", "            BACK TO DATABASE           " });
		changingDataAttributesMenu.displayMenuTitle("           CHANGE ATTRIBUTES           ");
		changingDataAttributesMenu.displayMenuPath(".../data_settings/rename_attributes");
		changingDataAttributesMenu.displayMenuWithItems();
	};

	void MenuObjectPathControler::displayAttributeChangingWindow(bool isActive, string input) {		// atributu keitimo langas, kuriame yra ivesties srautas naujo atributo vardui isgauti
		changingNameTable.setTitleActive(isActive);
		changingNameTable.setMenuActivity(isActive);
		changingNameTable.setMenuPosition(32, 22);
		changingNameTable.setMenuSize(44, 13);
		changingNameTable.setText("Press ENTER after input:");
		changingNameTable.displayRenameTableWithButtons();
		changingNameTable.setMenuItemList({ "CONFIRM ", " CANCEL " });
		changingNameTable.displayMenuTitle("            RENAME CONFIRMATION            ");
		changingNameTable.displayMenuPath(".../rename_attributes/rename_confirm");
		exitCursorPosition.X = 35; exitCursorPosition.Y = 28;
		SetConsoleCursorPosition(consoleExitInterface, exitCursorPosition);
		SetConsoleTextAttribute(consoleExitInterface, 0b10011000);
		cout << temporaryAttributeName;
		changingNameTable.displayRenameMenu();
	};

	void MenuObjectPathControler::displayAttributesChangingConfirmation(bool isActive) {	// sutikimas apie atributu vardo pasikeitima ir pakeitimu irasyma i faila
		attributeNameChangeConfirmationTable.setTitleActive(isActive);
		attributeNameChangeConfirmationTable.setMenuActivity(isActive);
		attributeNameChangeConfirmationTable.setMenuPosition(34, 26);
		attributeNameChangeConfirmationTable.setMenuSize(40, 10);
		attributeNameChangeConfirmationTable.setText("\n   Attribute succeesfully renamed!");
		attributeNameChangeConfirmationTable.displayTextInstructions();
		attributeNameChangeConfirmationTable.setMenuItemList({ "   OK   " });
		attributeNameChangeConfirmationTable.displayMenuTitle("     ATTRIBUTE CHANGE CONFIRMATION     ");
		attributeNameChangeConfirmationTable.displayMenuPath(".../main_menu/main_instructions/cont...");
		attributeNameChangeConfirmationTable.displayMenuWithOneButton();
	};

	void MenuObjectPathControler::displayMenuAskingForItemDeletion(bool isActive) {		// meniu, kuris klausia, ar tikrai norime panaikinti objekta
		itemDeleteConfirmationMenu.setTitleActive(isActive);
		itemDeleteConfirmationMenu.setMenuActivity(isActive);
		itemDeleteConfirmationMenu.setMenuPosition(31, 19);
		itemDeleteConfirmationMenu.setMenuSize(40, 10);
		itemDeleteConfirmationMenu.setText("   Do you wish to delete this item?");
		itemDeleteConfirmationMenu.displayTextSignalTables();
		itemDeleteConfirmationMenu.setMenuItemList({ "  YES   ", "   NO   " });
		itemDeleteConfirmationMenu.displayMenuTitle("          DELETE CONFIRMATION          ");
		itemDeleteConfirmationMenu.displayMenuPath("...ected_file/data_settings/delete_item");
		itemDeleteConfirmationMenu.displayMenuWithTwoButtons();
	};

	void MenuObjectPathControler::displayItemDeletionConfirmationMenu(bool isActive) {		// patvirtinimo pranesimas, kad pavyko sunaikinti elementa
		itemDeletedConfirmationTable.setTitleActive(isActive);
		itemDeletedConfirmationTable.setMenuActivity(isActive);
		itemDeletedConfirmationTable.setMenuPosition(32, 22);
		itemDeletedConfirmationTable.setMenuSize(40, 10);
		itemDeletedConfirmationTable.setText("\n       Item successfuly removed!");
		itemDeletedConfirmationTable.displayTextInstructions();
		itemDeletedConfirmationTable.setMenuItemList({ "   OK   " });
		itemDeletedConfirmationTable.displayMenuTitle("       ITEM DELETION CONFIRMATION      ");
		itemDeletedConfirmationTable.displayMenuPath(".../data_settings/delete_item/confirm..");
		itemDeletedConfirmationTable.displayMenuWithOneButton();
	};

	void MenuObjectPathControler::displayItemCreationMenu(bool isActive) {	// meniu, kuriame leidziama ivesti naujo kuriamo objekto atributu reiksmems
		addNewItemTable.setTitleActive(isActive);
		addNewItemTable.setMenuActivity(isActive);
		addNewItemTable.setMenuPosition(31, 19);
		addNewItemTable.setMenuSize(40, 23);
		addNewItemTable.setText("After entering eatch value please\n press ENTER:");
		addNewItemTable.displayTextSignalTables();
		addNewItemTable.setMenuItemList({ " SUBMIT ", " CANCEL " });
		addNewItemTable.displayMenuTitle("             ADD NEW ITEM              ");
		addNewItemTable.displayMenuPath(".../data_settings/add_new_item");
		exitCursorPosition.X = 43; exitCursorPosition.Y = 26;
		SetConsoleCursorPosition(consoleExitInterface, exitCursorPosition); SetConsoleTextAttribute(consoleExitInterface, 0b10011000);
		cout << temporaryNewAttributesValues[0]; // ITEM NAME
		exitCursorPosition.X = 39; exitCursorPosition.Y = 28; SetConsoleCursorPosition(consoleExitInterface, exitCursorPosition);
		cout << temporaryNewAttributesValues[1]; // ITEM PRICE
		exitCursorPosition.X = 38; exitCursorPosition.Y = 30; SetConsoleCursorPosition(consoleExitInterface, exitCursorPosition);
		cout << temporaryNewAttributesValues[2]; // ITEM TYPE
		exitCursorPosition.X = 39; exitCursorPosition.Y = 32; SetConsoleCursorPosition(consoleExitInterface, exitCursorPosition);
		cout << temporaryNewAttributesValues[3]; // ITEM STATE
		exitCursorPosition.X = 43; exitCursorPosition.Y = 34; SetConsoleCursorPosition(consoleExitInterface, exitCursorPosition);
		cout << temporaryNewAttributesValues[4]; // ITEM CODE
		exitCursorPosition.X = 39; exitCursorPosition.Y = 36; SetConsoleCursorPosition(consoleExitInterface, exitCursorPosition);
		cout << temporaryNewAttributesValues[5]; // DO ITEM EXIST
		addNewItemTable.displayAdditionMenu();
	}

	void MenuObjectPathControler::displayItemCreationConfirmationMenu(bool isActive) {	// naujo sukurto objekto notifikacija
		itemCreatedConfirmationTable.setTitleActive(isActive);
		itemCreatedConfirmationTable.setMenuActivity(isActive);
		itemCreatedConfirmationTable.setMenuPosition(32, 30);
		itemCreatedConfirmationTable.setMenuSize(40, 10);
		itemCreatedConfirmationTable.setText("\n        Item successfuly created!");
		itemCreatedConfirmationTable.displayTextInstructions();
		itemCreatedConfirmationTable.setMenuItemList({ "   OK   " });
		itemCreatedConfirmationTable.displayMenuTitle("       ITEM CREATION CONFIRMATION      ");
		itemCreatedConfirmationTable.displayMenuPath(".../data_settings/add_new_item/confir..");
		itemCreatedConfirmationTable.displayMenuWithOneButton();
	};

	void MenuObjectPathControler::displayEnterSearchKeywordWindow(bool isActive, string input) {   // langas, i kuri galima irasyt, pagal kuri zodi ieskoti objektu duomenu bazeje
		searchForKeywordMenu.setTitleActive(isActive);
		searchForKeywordMenu.setMenuActivity(isActive);
		searchForKeywordMenu.setMenuPosition(31, 19);
		searchForKeywordMenu.setMenuSize(44, 13);
		searchForKeywordMenu.setText("Press ENTER after input:");
		searchForKeywordMenu.displayRenameTableWithButtons();
		searchForKeywordMenu.setMenuItemList({ " SEARCH ", " CANCEL " });
		searchForKeywordMenu.displayMenuTitle("            ENTER SEARCH KEYWORD           ");
		searchForKeywordMenu.displayMenuPath(".../data_settings/search_for_keyword");
		exitCursorPosition.X = 34; exitCursorPosition.Y = 25;
		SetConsoleCursorPosition(consoleExitInterface, exitCursorPosition); SetConsoleTextAttribute(consoleExitInterface, 0b10011000);
		cout << temporaryAttributeName;
		searchForKeywordMenu.displayRenameMenu();
	};

	void MenuObjectPathControler::displayDatabaseSearchResult(bool isActive) {	// reliacines aibes atvaizdavimo objektas paieskos rezultatams atvaizduoti
		searchResultTable.setMenuPosition(20, 28);
		searchResultTable.setMenuSize(80, (searchForExistingItems(this->getItemDataList(), temporaryAttributeName).size() * 2) + 10); // reliacines lenteles meniu tampa dinaminis (priklauso nuo turimu duomenu)
		searchResultTable.drawDatabaseMenuTableBorder();
		searchResultTable.setTitleActive(isActive);
		searchResultTable.setMenuActivity(isActive);
		searchResultTable.displayMenuTitle("                             DATABASE SEARCH RESULTS                           ");
		if (searchForExistingItems(this->getItemDataList(), temporaryAttributeName).size() == 0) searchResultTable.displayMenuPath(".../manage_selected_file/data_settings/search_for_keyword/warning_no_results");
		else searchResultTable.displayMenuPath(".../manage_selected_file/data_settings/search_for_keyword/results_found");
		searchResultTable.setMenuItemList({ "  BACK TO MENU   ", "   END REVIEW    " });
		searchResultTable.displayDatabaseMenu();
	};

	void MenuObjectPathControler::displaySearchResultsWarningMessage(bool isActive) {  // pranesimas, kad negalima atlikineti jokiu veiksmu su duomenimis, kurie yra isvesti i paieskos rezultato vektoriu
		searchResultsWarningMessage.setTitleActive(isActive);
		searchResultsWarningMessage.setMenuActivity(isActive);
		searchResultsWarningMessage.setMenuPosition(36, 30);
		searchResultsWarningMessage.setMenuSize(40, 10);
		searchResultsWarningMessage.setText("\n    You can't change search results!");
		searchResultsWarningMessage.displayTextInstructions();
		searchResultsWarningMessage.setMenuItemList({ "   OK   " });
		searchResultsWarningMessage.displayMenuTitle("             WARNING MESSAGE           ");
		searchResultsWarningMessage.displayMenuPath("...ch_for_keyword/results_found/warning");
		searchResultsWarningMessage.displayMenuWithOneButton();
	};

	void MenuObjectPathControler::displayMenuAskingForAllItemDeletion(bool isActive) {	// isspausdinti langa, kuriame ispejama apie busima visu failu istrynima
		menuAskingForAllItemDeletion.setTitleActive(isActive);
		menuAskingForAllItemDeletion.setMenuActivity(isActive);
		menuAskingForAllItemDeletion.setMenuPosition(31, 19);
		menuAskingForAllItemDeletion.setMenuSize(42, 10);
		menuAskingForAllItemDeletion.setText("Do you really wish to delete all items?");
		menuAskingForAllItemDeletion.displayTextSignalTables();
		menuAskingForAllItemDeletion.setMenuItemList({ "  YES   ", "   NO   " });
		menuAskingForAllItemDeletion.displayMenuTitle("           DELETE CONFIRMATION           ");
		menuAskingForAllItemDeletion.displayMenuPath("...ected_file/data_settings/delete_al...");
		menuAskingForAllItemDeletion.displayMenuWithTwoButtons();
	};

	void MenuObjectPathControler::displayMoreOptionsMenu(bool isActive) {	// leidzia vartotojui duomenu bazeje pasirinkti siek tiek daugiau veiksmu - grizti ne i meniu, o i failu sarasa
		moreOptionsMenu.setTitleActive(isActive);								// bei leidzia vartotojui pradeti kurti duomenis sukuriant pirmaji atskaitos objekta
		moreOptionsMenu.setMenuActivity(isActive);
		moreOptionsMenu.setMenuSize(40, 8);
		moreOptionsMenu.setMenuPosition(9, 12);
		moreOptionsMenu.displayMenuItemsTable();
		moreOptionsMenu.setMenuItemList({ "           ADD EMPTY ELEMENT           ", "              BACK TO LIST             " });
		moreOptionsMenu.displayMenuTitle("              MORE OPTIONS             ");
		moreOptionsMenu.displayMenuPath(".../main_menu/database_content/more_...");
		moreOptionsMenu.displayMenuWithItems();
	};

	void MenuObjectPathControler::displayConfirmationAboutCreatingFirstListElement(bool isActive) {  // pranesimas, kad negalima atlikineti jokiu veiksmu su duomenimis, kurie yra isvesti i paieskos rezultato vektoriu
		firstElementIndicatorMenu.setTitleActive(isActive);
		firstElementIndicatorMenu.setMenuActivity(isActive);
		firstElementIndicatorMenu.setMenuPosition(10, 15);
		firstElementIndicatorMenu.setMenuSize(40, 10);
		firstElementIndicatorMenu.setText("\n         First item created!");
		firstElementIndicatorMenu.displayTextInstructions();
		firstElementIndicatorMenu.setMenuItemList({ "   OK   " });
		firstElementIndicatorMenu.displayMenuTitle("           WARNING MESSAGE             ");
		firstElementIndicatorMenu.displayMenuPath(".../database_content/first_item");
		firstElementIndicatorMenu.displayMenuWithOneButton();
	};

	MenuObjectPathControler::MenuObjectPathControler() {}; // konstruktorius

	MenuObjectPathControler::~MenuObjectPathControler() {}; // destruktorius
}
