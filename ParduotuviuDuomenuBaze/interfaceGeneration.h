#pragma once
#ifndef INTERFACEGENERATION_H
#define INTERFACEGENERATION_H

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <windows.h>
#include <stdlib.h>
#include <sstream>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <xutility>

using namespace std;

namespace interfaceDrawingLibrary {

	#define VERTICAL_LINE char(179)				// konstantos, kad butu suprantama, ka reiskia tam tikri skaiciai, nes jie jau turi pavadinima ir kad kodas butu grazesnis
	#define HORIZONTAL_LINE char(196)
	#define TOP_LEFT_CORNER char(218)
	#define TOP_RIGHT_CORNER char(191)
	#define BOTTOM_LEFT_CORNER char(192)
	#define BOTTOM_RIGHT_CORNER char(217)					// geometrines figuros interfeiso vaizdavimui

	#define VERTICAL_LINE_DOUBLE char(186)
	#define HORIZONTAL_LINE_DOUBLE char(205)
	#define TOP_LEFT_CORNER_DOUBLE char(201)
	#define TOP_RIGHT_CORNER_DOUBLE char(187)
	#define BOTTOM_LEFT_CORNER_DOUBLE char(200)
	#define BOTTOM_RIGHT_CORNER_DOUBLE char(188)

	#define GEOMETRIC_T_SHAPED_FRAME_FACING_LEFT char(180)				// lenteles braizymas bei meniu pavadinimo dekoraciniai simboliai
	#define GEOMETRIC_T_SHAPED_FRAME_FACING_RIGHT char(195)
	#define GEOMETRIC_T_SHAPED_FRAME_FACING_LEFT_DOUBLE char(185)
	#define GEOMETRIC_T_SHAPED_FRAME_FACING_RIGHT_DOUBLE char(204)

	#define TEXT_OFFSET 1
	#define TABLE_OFFSET 2
	#define DEFAULT_STYLE 0
	#define BUTTON_SIZE_X 9
	#define BUTTON_SIZE_Y 2
	#define BUTTON_OFFSET_X 2
	#define BUTTON_OFFSET_Y 4
	#define DEFAULT_CHOICE 0
	#define VECTOR_ARRAY_OFFSET 1
	#define DEFAULT_COLOR 0b00001111
	#define DEFAULT_ALLIGNMENT_STYLE 0
	#define DEFAULT_COORDINATE_RANGE 10
	#define DEFAULT_TEXT_MESSAGE_LENGTH 12
	#define DEFAULT_ITEM_ATTRIBUTE_COLOR 0b10011000

	#define SPACE_CHAR ' '
	#define NEW_LINE_CHAR '\n'
	#define DEFAULT_MENU_TITLE "No_Title"
	#define DEFAULT_TEXT_MESSAGE " "

	class ObjectCoordinates {	// bazine klase
	private:
		short screenCoordinateX, screenCoordinateY;   // X ir Y koordinates
	public:
		bool setScreenCoordinatesXY(short, short); // nustatyti abi X ir Y koordinates
		bool setScreenCoordinateX(short); // nustatyti X koordinates
		bool setScreenCoordinateY(short); // nustatyti Y koordinates
		short getScreenCoordinateX(); // gauti X koordinates
		short getScreenCoordinateY(); // gauti Y koordinates

		ObjectCoordinates(); // konstruktorius
		~ObjectCoordinates(); // destruktorius
	};

	class MenuBordersStyle : public ObjectCoordinates {		// meniu remeliu braizymo klase
	private:
		ObjectCoordinates menuSize, menuPosition;     // meniu dydzio ir pozicijos objektai
		short borderColor, windowColor, isBorderDouble;	// nusako remelio, fonp spalvas bei pazymi atvejus, kuriais meniu remelis bus dvigubas ar viengubas
		friend class TextOutputControler;	// draugiskai klasei leidziama pasiekti sios klases private narius
	public:
		bool setMenuSize(short, short);
		bool setMenuPosition(short, short);
		bool setBorderColor(short);
		short getBorderColor();
		bool setWindowColor(short);
		short getWindowColor();
		void setupMenuSizeAndPosition();
		void setupMenuColorAndConsoleDisplayPosition();

		void setupMenuBackgroundField();
		void setupMenuBorderStyleAndDisplayBorders(short, short);
		void setupMenuButtonsStyleAndDisplayBox(short, short);
		void setupMenuBorderCornersStyleAndDisplayBorderCorners(short, short);
		void setupAndDisplayMenuVerticalAndHorizontalLinesStyle(short, short);
		void setupAndDisplayButtonVerticalAndHorizontalLinesStyle(short, short);
		void setupAndDisplayMenuTitleSeparationCornerStyle(short, short);
		void setupAndDisplayTable(short, short);

		void drawItemsMenuBorder();
		void setFirstButton(MenuBordersStyle);
		void setFirstRenameButton(MenuBordersStyle);
		void setFirstButtonForSignalTable(MenuBordersStyle);
		void setSecondButton(MenuBordersStyle);
		void setSecondRenameButton(MenuBordersStyle);
		void setSecondButtonForSignalTable(MenuBordersStyle);
		void setThirdButton(MenuBordersStyle);
		void setRenameField(MenuBordersStyle);
		void drawItemsMenuButtonBox();
		void setupCoordinatesForDatabaseTable();
		void createThreeButtonsObject();
		void createTwoButtonsObject();

		void drawInstructionalMenuBorder();
		void drawRenameField();
		void drawDatabaseTableBorders();
		void setFirstButtonForDatabaseTable(MenuBordersStyle);
		void setSecondButtonForDatabaseTable(MenuBordersStyle);

		void createTwoButtonsObjectForDatabaseTable();
		void drawDatabaseMenuTableBorder();
		void drawSignalTableBorder();
		void drawRenameTableBorder();

		bool setBorderStyleToDouble(bool);
		bool isBorderStyleDoubleLine();
		void setSymbolPositionCoordinates(short, short);
		void setTableSymbolPositionCoordinates(short, short);
		void displayHorizontalLine(short, short);
		void displayHorizontalLineForTable(short, short);

		void displayVerticalLine(short, short);
		void displayVerticalLineForTable(short, short);

		void displayTopLeftCornerLine(short, short);
		void displayBottomLeftCornerLine(short, short);
		void displayTopRightCornerLine(short, short);
		void displayBottomRightCornerLine(short, short);
		void displayGeometricTShapeFrameFacingLeft(short, short);
		void displayGeometricTShapeFrameFacingRight(short, short);

		short getMenuSizeX();
		short getMenuSizeY();
		short getMenuPositionX();
		short getMenuPositionY();

		MenuBordersStyle(); // konstruktorius
		~MenuBordersStyle(); // destruktorius
	};

	class TextOutputControler : public MenuBordersStyle {
	private:
		string text, menuTitle, path;
		short textColor, allignmentStyle, unactiveTitleColor, activeTitleColor, pathColor;
		bool textWrapping, isTitleActive;
	public:
		bool setText(string);
		string getText();

		void displayMenuItemsTable();
		void displayTextInstructions();
		void displayTextSignalTables();
		void displayRenameTableWithButtons();

		void displayTextLineWithoutBorder(string);
		void displayPathLineWithoutBorder(string);
		string wrapText(short, short);
		bool setTextColor(short);
		short getTextColor();
		bool setAllignmentStyle(short);
		short getAllignmentStyle();
		void setupTextColorAndPosition();
		short allignmentToRightTextFormula(short, string);
		short allignmentToCenterTextFormula(short, string);
		void adjustPositionBeforeCout(short);
		void adjustPositionAfterCout();
		void adjustTextPositionOffset();
		void adjustSignalTextPositionOffset();
		void adjustTitlePositionOffset();
		void adjustPathPositionOffset();
		void pushWrappedText();
		void displayTextLine(string);
		void callPositionAdjustersAndTextLineDisplayer(short, string);	// teksto eilutes pozicijos nustatymas ir textline isvedimas
		void setupNonDefaultAlignmentStyle(short, string);

		void allignTextToLeft();
		void allignTextToRightOrCenter();
		bool setTextWrapping(bool);
		bool getTextWrapping();
		bool setMenuTitle(string);
		string getMenuTitle();
		bool setUnactiveTitleColor(short);
		short getUnactiveTitleColor();
		bool setActiveTitleColor(short);
		short getActiveTitleColor();
		bool setTitleActive(bool);
		bool isMenuTitleActive();
		bool setPath(string);
		string getPath();
		bool setPathColor(short);
		short getPathColor();

		void displayMenuTitle(string);
		void displayMenuPath(string);
		void displayAttributesNames();
		void adjustAttributesNamesPositionOffset();
		void adjustNextAttributeOffset(short);		// nustatyti pozicija duombazes atributu tekstui
		void adjustCreatingDataAttributeOffset();	// nustatyti pozicija naujo kuriamo objekto lentelei// nustatyti pozicija duombazes atributu tekstui
		void displayAtrributesTextWithoutBorder(); 	// i duombazes lentele suvesti atributu pavadinimus
		void displayPossibleAttributesForNewItem();	// i naujo objekto kurimo lentele suvesti atributu pavadinimus

		TextOutputControler(); // konstruktorius
		~TextOutputControler(); // destruktorius
	};

	struct ItemData {	// struktura su duomenimis, einanciais i klase
		string itemName, itemType, itemState, itemCode, isItemExist, itemPriceEuros;
	};

	class DatabaseControler {
	public:
		vector <ItemData> itemDataList;		// informacijos vektorius
		vector <ItemData> searchResultDataList;		// paieskos rezultato vektorius
		void getFileSelectionFromInterface(short);		// is failo duomenis perkelti i dinamine duomenu struktura
		void readSelectedFile(string);
		void overwriteSelectedFile(string, vector <ItemData>);	// funkcija duomenu irsaymui ir atnaujinimui i faila
		vector <string> createItemOutputString(vector <ItemData>);

		bool setItemDataList(vector <ItemData>);
		vector <ItemData> getItemDataList();
		void addObjectFromFile(ItemData);	// ideda objekta i vektoriu
		void createFirstObject(vector <string>, vector <ItemData>);	// sukuriamas pirmasis objektas kaip atskaitos taskas pradedant kurti duombazes turini

		void changeAttributeName(vector <ItemData>, short, short, string); // pagrindine funkcija, reikalinga atributu pervadinimui
		void deleteItemFromList(vector <ItemData>, short); // pagrindine funkcija, reikalinga objektu trynimui
		void addNewItemAbove(vector <ItemData>, vector <string>, short);	// ideda nauja objekta i vektoriaus nurodyta pozicija bei pakeitimus iraso i faila [pozicija = po indeksuotu objektu]
		void deleteWholeTable(vector <ItemData>);	// istryna absoliuciai viska is failo
		void addNewItemBellow(vector <ItemData>, vector <string>, short);	// ideda nauja objekta i vektoriaus nurodyta pozicija bei pakeitimus iraso i faila [pozicija = pries indeksuota objekta]
		vector <string> searchForExistingItems(vector <ItemData>, string);			// paieskos funkcija, rasti elementai dedami i atskira vektoriu ir yra spausdinami klonines reliacines aibes, tacia cia imanoma tik pasiziureti paieskos rezultatus

		void swapStrings(string*, string*);	// sortinimui reikalinga funkcija,kad apkeisti string kintamuju reiksmes
		void sortExistingVector(vector <ItemData>); // rikiavimo funkcija

		DatabaseControler();
		~DatabaseControler();
	};
	
	class ActiveMenuControler : public TextOutputControler , public DatabaseControler {
	private:
		short activeMenuItemColor, nonActiveMenuItemColor, controlerHandler, controlerIndex;	// aktyvaus ir neaktyvaus meniu objekto spalva
		vector <string> menuItemList;	// objektu sarasas [masyvas/vektorius]
		string menuTitle;	//	meniu pavadinimas, rodomas virsuje - centruotas
		bool isMenuActive, rename, create; // kintamieji, skirti meniu aktyvumui patikrinti bei nustatyti, kuomet kvieciame atributu pervadinimo valdymo skyda
		friend class DatabaseControler;
	public:
		void displayMenuWithItems(); //	 skirtingu tipu rodymui ir naudojimui
		void displayMenuWithOneButton();
		void displayMenuWithTwoButtons();
		void displayDatabaseMenu();
		void displayRenameMenu();
		void displayAdditionMenu();

		void activeItemsMenuList(vector <string>);	//skirtingu poziciju mygtuku issidestymai atsizvelgiant i kiekvieno meniu lango reikalavimus
		void activeOneButtonMenu(vector <string>);
		void activeTwoButtonMenu(vector <string>);
		void activeDatabaseTableMenu(vector <string>);
		
		void resetLine();	// tekstines eilutes panaikinimas
		void setupDatabaseListPosition();	// duomenu bazes lenteles pozicijos nustatymas
		void testIfAnyEnteredArrowAreValid(bool);	// kontroleris, kuris valdo ivedimo srautus, priklausancius nuo rodyklinio valdymo

		void  addMenuItem(string);	// vektoriu papildyti nauju meniu punktu
		bool  setMenuItemList(vector <string>);	// isgauti visa meniu punktu sarasa
		bool  setActiveMenuItemColor(short);	// nustatyti aktyvaus meniu objekto spalva
		short getActiveMenuItemColor();			// nustatyti aktyvaus meniu punkto spalva
		vector <string> getMenuItemList();		// isgauti meniu sarasa
		bool setNonActiveMenuItemColor(short);	// nustatyti ne-aktyvaus meniu punkto spalva
		short getNonActiveMenuItemColor();		// gauti ne-aktyvaus meniu punkto spalva
		void setupActiveItemsPosition();	// nustatyti aktyviu meniu punktu pozicijas
		void setupOneActiveButtonPosition();	// nustatyti vieno lange esancio mygtuko pozicija
		void setupTwoActiveButtonsPosition();	// nustatyti dvieju lange esancio mygtuko pozicija
		void setupTwoActiveButtonsForRenameTablePosition();	// nustatyti vieno lange esancio mygtuko pozicija su papildomu ivesties langu
		void setupTwoActiveButtonsForCreationTablePosition();
		void setupDatabaseActiveButtonsPosition();	// duomenu bazes lenteleje esantys aktyvus myktukai

		bool setMenuActivity(bool);
		bool getMenuActivity();
		bool setControlerIndex(short);
		short getControlerIndex();

		ActiveMenuControler(); // konstruktorius
		~ActiveMenuControler(); // destruktorius
	};

}

#endif