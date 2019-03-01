#include "stdafx.h"
#include "interfaceGeneration.h"
#include "objectsConfiguration.h"

namespace interfaceDrawingLibrary {

	HANDLE consoleControler = GetStdHandle(STD_OUTPUT_HANDLE);	// grafinei bibliotekai palaikyti
	COORD drawingPositionCoordinates;	// piesimo pozija

	vector <string> itemOutputString;
	vector <string> existingFilesList{ "FOOD_PRODUCTS_DATABASE",	// failu vardai
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

	char reactToKeyboardButton;		// ivesties mygtukas

	bool ObjectCoordinates::setScreenCoordinatesXY(short screenCoordinateX, short screenCoordinateY) {	// ekrano koordinaciu X ir Y isgavimas
		this->screenCoordinateX = screenCoordinateX;
		this->screenCoordinateY = screenCoordinateY;
		return true;
	};

	short ObjectCoordinates::getScreenCoordinateX() {	// ekrano koordinates X gavimas
		return screenCoordinateX;
	};

	short ObjectCoordinates::getScreenCoordinateY() {	// ekrano koordinates Y gavimas
		return screenCoordinateY;
	};

	bool ObjectCoordinates::setScreenCoordinateX(short screenCoordinateX) {		// nustatyti ekrano koordinate X
		this->screenCoordinateX = screenCoordinateX;
		return true;
	};

	bool ObjectCoordinates::setScreenCoordinateY(short screenCoordinateY) {		// nustatyti ekrano koordinate Y
		this->screenCoordinateX = screenCoordinateY;
		return true;
	};

	ObjectCoordinates::ObjectCoordinates() {			// default reiksmes
		screenCoordinateX = DEFAULT_COORDINATE_RANGE;
		screenCoordinateY = DEFAULT_COORDINATE_RANGE;
	};

	ObjectCoordinates::~ObjectCoordinates() {};			// destruktorius

	/* ---------------------------------------------------------------------------------------- */

	bool MenuBordersStyle::setMenuSize(short screenCoordinateX, short screenCoordinateY) {		// nustatyti meniu dydi
		this->menuSize.setScreenCoordinatesXY(screenCoordinateX, screenCoordinateY);
		return true;
	};

	bool MenuBordersStyle::setMenuPosition(short screenCoordinateX, short screenCoordinateY) {	// nustatyti meniu pozicija
		this->menuPosition.setScreenCoordinatesXY(screenCoordinateX, screenCoordinateY);
		return true;
	};

	bool MenuBordersStyle::setBorderColor(short currentColor) {		// remelio spalva
		this->borderColor = currentColor;
		return true;
	};

	short MenuBordersStyle::getBorderColor() {		// gauti remelio spalvos koda
		return borderColor;
	};

	bool MenuBordersStyle::setWindowColor(short currentColor) {		// nustatyti lango spalva
		this->windowColor = currentColor;
		return true;
	};

	short MenuBordersStyle::getWindowColor() {			// gauti lango spalvos koda
		return windowColor;
	};

	void MenuBordersStyle::setupMenuSizeAndPosition() {			// nustatyti meniu dydi ir piesimo pozicija konsoleje
		setMenuPosition(this->menuPosition.getScreenCoordinateX(), this->menuPosition.getScreenCoordinateY());
		setMenuSize(this->menuSize.getScreenCoordinateX(), this->menuSize.getScreenCoordinateY());
		drawingPositionCoordinates.X = this->menuPosition.getScreenCoordinateX();
		drawingPositionCoordinates.Y = this->menuPosition.getScreenCoordinateY();
	};

	void MenuBordersStyle::setupMenuColorAndConsoleDisplayPosition() {		// lango kairiojo kampo koordinates bei jo spalva
		SetConsoleCursorPosition(consoleControler, drawingPositionCoordinates);
		SetConsoleTextAttribute(consoleControler, this->getWindowColor());
	};

	void MenuBordersStyle::setupMenuBackgroundField() {			// nustatyti fona
		setupMenuSizeAndPosition();
		for (short iteratorForX = 0; iteratorForX <= this->menuSize.getScreenCoordinateY(); iteratorForX++) {
			drawingPositionCoordinates.Y = this->menuPosition.getScreenCoordinateY() + iteratorForX;
			setupMenuColorAndConsoleDisplayPosition();
			cout << setw(this->menuSize.getScreenCoordinateX()) << SPACE_CHAR;
		}
	};
																	// nustatyti meniu krastu ir krastiniu styliu bei jas isspausdinti
	void MenuBordersStyle::setupMenuBorderCornersStyleAndDisplayBorderCorners(short iteratorForX, short iteratorForY) {	
		if (iteratorForX == 0 && iteratorForY == 0) displayTopLeftCornerLine(iteratorForX, iteratorForY);
		if (iteratorForX == 0 && iteratorForY == this->menuSize.getScreenCoordinateY()) displayBottomLeftCornerLine(iteratorForX, iteratorForY);
		if (iteratorForX == this->menuSize.getScreenCoordinateX() && iteratorForY == 0) displayTopRightCornerLine(iteratorForX, iteratorForY);
		if (iteratorForX == this->menuSize.getScreenCoordinateX() && iteratorForY == this->menuSize.getScreenCoordinateY()) displayBottomRightCornerLine(iteratorForX, iteratorForY);
	};
				// virsutine funckija skyla i daug sub-funkciju, kurios braizo tam tikrus simbolius atskirai, atsizvelgiant i koordinates, pozicija ir lango dydi
	void MenuBordersStyle::setupAndDisplayMenuVerticalAndHorizontalLinesStyle(short iteratorForX, short iteratorForY) {
		if ((iteratorForX == 0 || iteratorForX == this->menuSize.getScreenCoordinateX()) && (iteratorForY != 0 || iteratorForY != this->menuSize.getScreenCoordinateY()))
			displayVerticalLine(iteratorForX, iteratorForY);
		if ((iteratorForX != 0 || iteratorForX != this->menuSize.getScreenCoordinateX()) && (iteratorForY == 0 || iteratorForY == this->menuSize.getScreenCoordinateY()) || (iteratorForY == 2))
			displayHorizontalLine(iteratorForX, iteratorForY);			// vertikales ir horizontales linijos
	};

	void MenuBordersStyle::setupAndDisplayButtonVerticalAndHorizontalLinesStyle(short iteratorForX, short iteratorForY) {
		if ((iteratorForX == 0 || iteratorForX == this->menuSize.getScreenCoordinateX()) && (iteratorForY != 0 || iteratorForY != this->menuSize.getScreenCoordinateY()))
			displayVerticalLine(iteratorForX, iteratorForY);
		if ((iteratorForX != 0 || iteratorForX != this->menuSize.getScreenCoordinateX()) && (iteratorForY == 0 || iteratorForY == this->menuSize.getScreenCoordinateY()))
			displayHorizontalLine(iteratorForX, iteratorForY);
	};

	void MenuBordersStyle::setupAndDisplayMenuTitleSeparationCornerStyle(short iteratorForX, short iteratorForY) {
		if (iteratorForY == 2 && iteratorForX == 0)
			displayGeometricTShapeFrameFacingRight(iteratorForX, iteratorForY);
		if (iteratorForY == 2 && iteratorForX == this->menuSize.getScreenCoordinateX())
			displayGeometricTShapeFrameFacingLeft(iteratorForX, iteratorForY);
	};
						// lenteles braizymo logika
	void MenuBordersStyle::setupAndDisplayTable(short iteratorForX, short iteratorForY) {
		if (iteratorForY % 2 != 0)
			displayHorizontalLineForTable(iteratorForX, iteratorForY);
		if ((iteratorForX == 30 || iteratorForX == 39 || iteratorForX == 48 || iteratorForX == 55 || iteratorForX == 73 || iteratorForY == 80) && iteratorForY % 2 == 0)
			displayVerticalLineForTable(iteratorForX, iteratorForY);
	};

	void MenuBordersStyle::setupMenuBorderStyleAndDisplayBorders(short iteratorForX, short iteratorForY) {
		setupAndDisplayMenuVerticalAndHorizontalLinesStyle(iteratorForX, iteratorForY);
		setupMenuBorderCornersStyleAndDisplayBorderCorners(iteratorForX, iteratorForY);
		setupAndDisplayMenuTitleSeparationCornerStyle(iteratorForX, iteratorForY);
	};

	void MenuBordersStyle::setupMenuButtonsStyleAndDisplayBox(short iteratorForX, short iteratorForY) {
		setupAndDisplayButtonVerticalAndHorizontalLinesStyle(iteratorForX, iteratorForY);
		setupMenuBorderCornersStyleAndDisplayBorderCorners(iteratorForX, iteratorForY);
	};

	void MenuBordersStyle::drawItemsMenuBorder() {
		setupMenuBackgroundField();
		for (short iteratorForX = 0; iteratorForX <= this->menuSize.getScreenCoordinateX(); iteratorForX++) {
			for (short iteratorForY = 0; iteratorForY <= this->menuSize.getScreenCoordinateY(); iteratorForY++) {
				SetConsoleTextAttribute(consoleControler, this->getBorderColor());
				setupMenuBorderStyleAndDisplayBorders(iteratorForX, iteratorForY);
			}
		}
	};

	void MenuBordersStyle::drawItemsMenuButtonBox() {
		setupMenuBackgroundField();
		for (short iteratorForX = 0; iteratorForX <= this->menuSize.getScreenCoordinateX(); iteratorForX++) {
			for (short iteratorForY = 0; iteratorForY <= this->menuSize.getScreenCoordinateY(); iteratorForY++) {
				SetConsoleTextAttribute(consoleControler, this->getBorderColor());
				setupMenuButtonsStyleAndDisplayBox(iteratorForX, iteratorForY);
			}
		}
	};

	void MenuBordersStyle::setupCoordinatesForDatabaseTable() {
		drawingPositionCoordinates.X = this->menuPosition.getScreenCoordinateX();
		drawingPositionCoordinates.Y = this->menuPosition.getScreenCoordinateY() + TEXT_OFFSET * 3;
	};

	void MenuBordersStyle::setFirstButton(MenuBordersStyle button) {
		button.setMenuPosition(this->menuPosition.getScreenCoordinateX() + 1 + BUTTON_OFFSET_X, this->menuSize.getScreenCoordinateY() + this->menuPosition.getScreenCoordinateY() - BUTTON_OFFSET_Y);
		button.drawItemsMenuButtonBox();
	};

	void MenuBordersStyle::setFirstButtonForSignalTable(MenuBordersStyle button) {
		button.setMenuPosition(this->menuPosition.getScreenCoordinateX() + 4 * BUTTON_OFFSET_X + 1, this->menuSize.getScreenCoordinateY() + this->menuPosition.getScreenCoordinateY() - BUTTON_OFFSET_Y);
		button.drawItemsMenuButtonBox();
	};

	void MenuBordersStyle::setFirstRenameButton(MenuBordersStyle button) {
		button.setMenuPosition(this->menuPosition.getScreenCoordinateX() + BUTTON_OFFSET_X * 6, this->menuSize.getScreenCoordinateY() + this->menuPosition.getScreenCoordinateY() - BUTTON_OFFSET_Y);
		button.drawItemsMenuButtonBox();
	};

	void MenuBordersStyle::setSecondRenameButton(MenuBordersStyle button) {
		button.setMenuPosition(this->menuPosition.getScreenCoordinateX() + 3 * BUTTON_OFFSET_X + BUTTON_SIZE_X * 2, this->menuSize.getScreenCoordinateY() + this->menuPosition.getScreenCoordinateY() - BUTTON_OFFSET_Y);
		button.drawItemsMenuButtonBox();
	};

	void MenuBordersStyle::setSecondButton(MenuBordersStyle button) {
		button.setMenuPosition(this->menuPosition.getScreenCoordinateX() + 3 * BUTTON_OFFSET_X + BUTTON_SIZE_X, this->menuSize.getScreenCoordinateY() + this->menuPosition.getScreenCoordinateY() - BUTTON_OFFSET_Y);
		button.drawItemsMenuButtonBox();
	};

	void MenuBordersStyle::setSecondButtonForSignalTable(MenuBordersStyle button) {
		button.setMenuPosition(this->menuPosition.getScreenCoordinateX() + 6 * BUTTON_OFFSET_X + BUTTON_SIZE_X, this->menuSize.getScreenCoordinateY() + this->menuPosition.getScreenCoordinateY() - BUTTON_OFFSET_Y);
		button.drawItemsMenuButtonBox();
	};

	void MenuBordersStyle::setThirdButton(MenuBordersStyle button) {
		button.setMenuPosition(this->menuPosition.getScreenCoordinateX() + 9 * BUTTON_OFFSET_X + BUTTON_SIZE_X, this->menuSize.getScreenCoordinateY() + this->menuPosition.getScreenCoordinateY() - BUTTON_OFFSET_Y);
		button.drawItemsMenuButtonBox();
	};

	void MenuBordersStyle::setRenameField(MenuBordersStyle button) {
		button.setMenuPosition(this->menuPosition.getScreenCoordinateX() - TEXT_OFFSET * 7 + BUTTON_SIZE_X, this->menuSize.getScreenCoordinateY() + this->menuPosition.getScreenCoordinateY() - BUTTON_OFFSET_Y * 2);
		button.drawItemsMenuButtonBox();
	};

	void MenuBordersStyle::createThreeButtonsObject() {
		MenuBordersStyle button;
		button.setMenuSize(BUTTON_SIZE_X, BUTTON_SIZE_Y);
		setFirstButton(button);
		setSecondButton(button);
		setThirdButton(button);
	};

	void MenuBordersStyle::createTwoButtonsObject() {
		MenuBordersStyle button;
		button.setMenuSize(BUTTON_SIZE_X, BUTTON_SIZE_Y);
		setFirstButtonForSignalTable(button);
		setSecondButtonForSignalTable(button);
	};

	void MenuBordersStyle::drawInstructionalMenuBorder() {
		MenuBordersStyle button;
		button.setMenuSize(BUTTON_SIZE_X, BUTTON_SIZE_Y);
		drawItemsMenuBorder();
		setSecondButton(button);
	};

	void MenuBordersStyle::drawRenameField() {
		MenuBordersStyle button;
		button.setMenuSize(40, BUTTON_SIZE_Y);
		setRenameField(button);
		button.setMenuSize(BUTTON_SIZE_X, BUTTON_SIZE_Y);
		setFirstRenameButton(button);
		setSecondRenameButton(button);
	};

	void MenuBordersStyle::drawDatabaseTableBorders() {
		for (short iteratorForX = 1; iteratorForX <= this->menuSize.getScreenCoordinateX() - TEXT_OFFSET; iteratorForX++) {
			for (short iteratorForY = 1; iteratorForY <= this->menuSize.getScreenCoordinateY() - TEXT_OFFSET * 7; iteratorForY++) {
				SetConsoleTextAttribute(consoleControler, this->getBorderColor());
				setupAndDisplayTable(iteratorForX, iteratorForY);
			}
		}
	};

	void MenuBordersStyle::setFirstButtonForDatabaseTable(MenuBordersStyle button) {
		button.setMenuPosition(this->menuPosition.getScreenCoordinateX() + BUTTON_OFFSET_X, this->menuPosition.getScreenCoordinateY() + BUTTON_OFFSET_Y - TEXT_OFFSET);
		button.drawItemsMenuButtonBox();
	};

	void MenuBordersStyle::setSecondButtonForDatabaseTable(MenuBordersStyle button) {
		button.setMenuPosition(this->menuPosition.getScreenCoordinateX() + BUTTON_OFFSET_X * 11, this->menuPosition.getScreenCoordinateY() + BUTTON_OFFSET_Y - TEXT_OFFSET);
		button.drawItemsMenuButtonBox();
	};

	void MenuBordersStyle::createTwoButtonsObjectForDatabaseTable() {
		MenuBordersStyle button;
		button.setMenuSize(BUTTON_SIZE_X * 2, BUTTON_SIZE_Y);
		setFirstButtonForDatabaseTable(button);
		setSecondButtonForDatabaseTable(button);
	};

	void MenuBordersStyle::drawDatabaseMenuTableBorder() {
		setupMenuBackgroundField();
		drawItemsMenuBorder();
		setupCoordinatesForDatabaseTable();
		drawDatabaseTableBorders();
		createTwoButtonsObjectForDatabaseTable();
	};

	void MenuBordersStyle::drawSignalTableBorder() {
		setupMenuBackgroundField();
		drawItemsMenuBorder();
		createTwoButtonsObject();
	};

	void MenuBordersStyle::drawRenameTableBorder() {
		setupMenuBackgroundField();
		drawItemsMenuBorder();
		drawRenameField();
	};

	bool MenuBordersStyle::setBorderStyleToDouble(bool isBorderDouble) {
		this->isBorderDouble = isBorderDouble;
		return true;
	};

	bool MenuBordersStyle::isBorderStyleDoubleLine() {
		return isBorderDouble;
	};

	void MenuBordersStyle::setSymbolPositionCoordinates(short iteratorForX, short iteratorForY) {
		drawingPositionCoordinates.X = this->menuPosition.getScreenCoordinateX() + iteratorForX;
		drawingPositionCoordinates.Y = this->menuPosition.getScreenCoordinateY() + iteratorForY;
		SetConsoleCursorPosition(consoleControler, drawingPositionCoordinates);
	};

	void MenuBordersStyle::setTableSymbolPositionCoordinates(short iteratorForX, short iteratorForY) {
		drawingPositionCoordinates.X = this->menuPosition.getScreenCoordinateX() + iteratorForX;
		drawingPositionCoordinates.Y = this->menuPosition.getScreenCoordinateY() + iteratorForY + TEXT_OFFSET * 5;
		SetConsoleCursorPosition(consoleControler, drawingPositionCoordinates);
	};

	void MenuBordersStyle::displayHorizontalLine(short iteratorForX, short iteratorForY) {
		setSymbolPositionCoordinates(iteratorForX, iteratorForY);
		if (!isBorderStyleDoubleLine()) cout << HORIZONTAL_LINE;
		else cout << HORIZONTAL_LINE_DOUBLE;
	};

	void MenuBordersStyle::displayHorizontalLineForTable(short iteratorForX, short iteratorForY) {
		setTableSymbolPositionCoordinates(iteratorForX, iteratorForY);
		cout << HORIZONTAL_LINE;
	};

	void MenuBordersStyle::displayVerticalLine(short iteratorForX, short iteratorForY) {
		setSymbolPositionCoordinates(iteratorForX, iteratorForY);
		if (!isBorderStyleDoubleLine()) cout << VERTICAL_LINE;
		else cout << VERTICAL_LINE_DOUBLE;
	};

	void MenuBordersStyle::displayVerticalLineForTable(short iteratorForX, short iteratorForY) {
		setTableSymbolPositionCoordinates(iteratorForX, iteratorForY);
		cout << VERTICAL_LINE;
	};

	void MenuBordersStyle::displayTopLeftCornerLine(short iteratorForX, short iteratorForY) {
		setSymbolPositionCoordinates(iteratorForX, iteratorForY);
		if (!isBorderStyleDoubleLine()) cout << TOP_LEFT_CORNER;
		else cout << TOP_LEFT_CORNER_DOUBLE;
	};

	void MenuBordersStyle::displayBottomLeftCornerLine(short iteratorForX, short iteratorForY) {
		setSymbolPositionCoordinates(iteratorForX, iteratorForY);
		if (!isBorderStyleDoubleLine()) cout << BOTTOM_LEFT_CORNER;
		else cout << BOTTOM_LEFT_CORNER_DOUBLE;
	};

	void MenuBordersStyle::displayTopRightCornerLine(short iteratorForX, short iteratorForY) {
		setSymbolPositionCoordinates(iteratorForX, iteratorForY);
		if (!isBorderStyleDoubleLine()) cout << TOP_RIGHT_CORNER;
		else cout << TOP_RIGHT_CORNER_DOUBLE;
	};

	void MenuBordersStyle::displayBottomRightCornerLine(short iteratorForX, short iteratorForY) {
		setSymbolPositionCoordinates(iteratorForX, iteratorForY);
		if (!isBorderStyleDoubleLine()) cout << BOTTOM_RIGHT_CORNER;
		else cout << BOTTOM_RIGHT_CORNER_DOUBLE;
	};

	void MenuBordersStyle::displayGeometricTShapeFrameFacingLeft(short iteratorForX, short iteratorForY) {
		setSymbolPositionCoordinates(iteratorForX, iteratorForY);
		if (!isBorderStyleDoubleLine()) cout << GEOMETRIC_T_SHAPED_FRAME_FACING_LEFT;
		else cout << GEOMETRIC_T_SHAPED_FRAME_FACING_LEFT_DOUBLE;
	};

	void MenuBordersStyle::displayGeometricTShapeFrameFacingRight(short iteratorForX, short iteratorForY) {
		setSymbolPositionCoordinates(iteratorForX, iteratorForY);
		if (!isBorderStyleDoubleLine()) cout << GEOMETRIC_T_SHAPED_FRAME_FACING_RIGHT;
		else cout << GEOMETRIC_T_SHAPED_FRAME_FACING_RIGHT_DOUBLE;
	};

	short MenuBordersStyle::getMenuSizeX() {
		return menuSize.getScreenCoordinateX();
	};

	short MenuBordersStyle::getMenuSizeY() {
		return menuSize.getScreenCoordinateY();
	};

	short MenuBordersStyle::getMenuPositionX() {
		return menuPosition.getScreenCoordinateX();
	};

	short MenuBordersStyle::getMenuPositionY() {
		return menuPosition.getScreenCoordinateY();
	};

	MenuBordersStyle::MenuBordersStyle() {
		isBorderDouble = 1;
		borderColor = 0b10011111;
		windowColor = 0b10011111;
	};

	MenuBordersStyle::~MenuBordersStyle() {};

	/* ---------------------------------------------------------------------------------------- */

	bool TextOutputControler::setText(string text) {
		this->text = text;
		return true;
	};

	string TextOutputControler::getText() {
		return text;
	};

	void TextOutputControler::displayMenuItemsTable() {
		drawItemsMenuBorder();
		setupMenuSizeAndPosition();
		adjustTextPositionOffset();
		if (this->getAllignmentStyle() == 0)
			allignTextToLeft();
		else allignTextToRightOrCenter();
	};

	void TextOutputControler::displayTextInstructions() {
		drawInstructionalMenuBorder();
		setupMenuSizeAndPosition();
		adjustTextPositionOffset();
		if (this->getAllignmentStyle() == 0)
			allignTextToLeft();
		else allignTextToRightOrCenter();
	};

	void TextOutputControler::displayTextSignalTables() {
		drawSignalTableBorder();
		setupMenuSizeAndPosition();
		adjustSignalTextPositionOffset();
		if (this->getAllignmentStyle() == 0)
			allignTextToLeft();
		else allignTextToRightOrCenter();
	};

	void TextOutputControler::displayRenameTableWithButtons() {
		drawRenameTableBorder();
		setupMenuSizeAndPosition();
		adjustSignalTextPositionOffset();
		if (this->getAllignmentStyle() == 0)
			allignTextToLeft();
		else allignTextToRightOrCenter();
	};

	void TextOutputControler::displayTextLineWithoutBorder(string outputText) {
		SetConsoleCursorPosition(consoleControler, drawingPositionCoordinates);
		if (this->isMenuTitleActive())
			SetConsoleTextAttribute(consoleControler, this->getActiveTitleColor());
		else SetConsoleTextAttribute(consoleControler, this->getUnactiveTitleColor());
		for (short iteratorForX = 0; iteratorForX < this->getMenuTitle().length(); iteratorForX++)
			cout << this->getMenuTitle()[iteratorForX];
	};

	void TextOutputControler::displayPathLineWithoutBorder(string outputText) {
		SetConsoleCursorPosition(consoleControler, drawingPositionCoordinates);
		SetConsoleTextAttribute(consoleControler, this->getPathColor());
		for (short iteratorForX = 0; iteratorForX < this->getPath().length(); iteratorForX++)
			cout << this->getPath()[iteratorForX];
	};

	string TextOutputControler::wrapText(short screenSizeX, short screenSizeY) {
		int spaceLocation, position, subCounter = 0;
		string temporaryText = this->getText(), wrappedText;
		for (short iteratorForY = 0; iteratorForY < screenSizeY; iteratorForY++) {
			spaceLocation = temporaryText.rfind(SPACE_CHAR, screenSizeX);
			if (spaceLocation != string::npos)
				temporaryText.at(spaceLocation) = NEW_LINE_CHAR;
			position = temporaryText.find(NEW_LINE_CHAR);
			if (position != string::npos)
				wrappedText += NEW_LINE_CHAR + temporaryText.substr(0, position);
			else if (position == string::npos && subCounter == 0) {
				wrappedText += NEW_LINE_CHAR + temporaryText;
				subCounter++;
			}
			temporaryText = temporaryText.substr(temporaryText.find(NEW_LINE_CHAR) + TEXT_OFFSET);
		}
		this->setText(wrappedText);
		return this->getText();
	};

	bool TextOutputControler::setTextColor(short textColor) {
		this->textColor = textColor;
		return true;
	};

	short TextOutputControler::getTextColor() {
		return textColor;
	};

	bool TextOutputControler::setAllignmentStyle(short allignmentStyle) {
		this->allignmentStyle = allignmentStyle;
		return true;
	};

	short TextOutputControler::getAllignmentStyle() {
		return allignmentStyle;
	};

	void TextOutputControler::setupTextColorAndPosition() {
		SetConsoleTextAttribute(consoleControler, this->getTextColor());
		SetConsoleCursorPosition(consoleControler, drawingPositionCoordinates);
	};

	short TextOutputControler::allignmentToRightTextFormula(short position, string textLine) {
		position = this->menuSize.getScreenCoordinateX() - TEXT_OFFSET - textLine.length();
		return position;
	};

	short TextOutputControler::allignmentToCenterTextFormula(short position, string textLine) {
		position = ((this->menuSize.getScreenCoordinateX() - 2) / 2) - textLine.length() / 2;
		return position;
	};

	void TextOutputControler::adjustPositionBeforeCout(short position) {
		drawingPositionCoordinates.X += position;
		SetConsoleCursorPosition(consoleControler, drawingPositionCoordinates);
	};

	void TextOutputControler::adjustPositionAfterCout() {
		drawingPositionCoordinates.Y++;
		drawingPositionCoordinates.X = this->menuPosition.getScreenCoordinateX() + TEXT_OFFSET;
	};

	void TextOutputControler::adjustTextPositionOffset() {
		drawingPositionCoordinates = { this->menuPosition.getScreenCoordinateX() + TEXT_OFFSET * 2,
									   this->menuPosition.getScreenCoordinateY() + TEXT_OFFSET * 3 };
	};

	void TextOutputControler::adjustSignalTextPositionOffset() {
		drawingPositionCoordinates = { this->menuPosition.getScreenCoordinateX() + TEXT_OFFSET * 2,
									   this->menuPosition.getScreenCoordinateY() + TEXT_OFFSET * 4 };
	};

	void TextOutputControler::adjustTitlePositionOffset() {
		drawingPositionCoordinates = { this->menuPosition.getScreenCoordinateX() + TEXT_OFFSET,
									   this->menuPosition.getScreenCoordinateY() + TEXT_OFFSET };
	};

	void TextOutputControler::adjustPathPositionOffset() {
		drawingPositionCoordinates = { this->menuPosition.getScreenCoordinateX() + TEXT_OFFSET,
									   this->menuPosition.getScreenCoordinateY() + this->menuSize.getScreenCoordinateY() - TEXT_OFFSET };
	}

	void TextOutputControler::pushWrappedText() {
		if (getTextWrapping())
			this->setText(wrapText(this->menuSize.getScreenCoordinateX() - 2, this->menuSize.getScreenCoordinateY()));
	};

	void TextOutputControler::displayTextLine(string textLine) {
		cout << textLine << endl;
	};

	void TextOutputControler::callPositionAdjustersAndTextLineDisplayer(short position, string textLine) {
		adjustPositionBeforeCout(position);
		displayTextLine(textLine);
		adjustPositionAfterCout();
	}

	void TextOutputControler::setupNonDefaultAlignmentStyle(short position, string textLine) {
		if (this->getAllignmentStyle() == 1)
			allignmentToRightTextFormula(position, textLine);
		if (this->getAllignmentStyle() == 2)
			allignmentToCenterTextFormula(position, textLine);
	};

	void TextOutputControler::allignTextToLeft() {
		istringstream IOStringStream(this->getText());
		short position{ 0 };
		pushWrappedText();
		for (string textLine; getline(IOStringStream, textLine); ) {
			setupTextColorAndPosition();
			callPositionAdjustersAndTextLineDisplayer(position, textLine);
		}
	};

	void TextOutputControler::allignTextToRightOrCenter() {
		istringstream IOStringStream(this->getText()); short position{ 0 };
		pushWrappedText();
		for (string textLine; getline(IOStringStream, textLine); ) {
			setupTextColorAndPosition();
			setupNonDefaultAlignmentStyle(position, textLine);
			callPositionAdjustersAndTextLineDisplayer(position, textLine);
		}
	};

	bool TextOutputControler::setTextWrapping(bool textWrapping) {
		this->textWrapping = textWrapping;
		return true;
	};

	bool TextOutputControler::getTextWrapping() {
		return textWrapping;
	};

	bool TextOutputControler::setMenuTitle(string menuTitle) {
		this->menuTitle = menuTitle;
		return true;
	};

	string TextOutputControler::getMenuTitle() {
		return menuTitle;
	};

	bool TextOutputControler::setUnactiveTitleColor(short currentColor) {
		this->unactiveTitleColor = currentColor;
		return true;
	};

	short TextOutputControler::getUnactiveTitleColor() {
		return unactiveTitleColor;
	};

	bool TextOutputControler::setActiveTitleColor(short currentColor) {
		this->activeTitleColor = currentColor;
		return true;
	};

	short TextOutputControler::getActiveTitleColor() {
		return activeTitleColor;
	};

	bool TextOutputControler::setTitleActive(bool isTitleActive) {
		this->isTitleActive = isTitleActive;
		return true;
	};

	bool TextOutputControler::isMenuTitleActive() {
		return isTitleActive;
	};

	bool TextOutputControler::setPath(string path) {
		this->path = path;
		return true;
	};

	string TextOutputControler::getPath() {
		return path;
	};

	bool TextOutputControler::setPathColor(short currentColor) {
		this->pathColor = currentColor;
		return true;
	};

	short TextOutputControler::getPathColor() {
		return pathColor;
	};

	void TextOutputControler::displayMenuTitle(string menuTitle) {
		this->setMenuTitle(menuTitle);
		adjustTitlePositionOffset();
		displayTextLineWithoutBorder(this->getMenuTitle());
	};

	void TextOutputControler::displayMenuPath(string menuTitle) {
		this->setPath(menuTitle);
		adjustPathPositionOffset();
		displayPathLineWithoutBorder(this->getPath());
	};

	void TextOutputControler::adjustAttributesNamesPositionOffset() {
		drawingPositionCoordinates = { this->menuPosition.getScreenCoordinateX() + TEXT_OFFSET,
									   this->menuPosition.getScreenCoordinateY() + TEXT_OFFSET * 7 };
		SetConsoleCursorPosition(consoleControler, drawingPositionCoordinates);
	};

	void TextOutputControler::adjustNextAttributeOffset(short offsetValue) {	// nustatyti pozicija duombazes atributu tekstui
		drawingPositionCoordinates.X += offsetValue;
		SetConsoleCursorPosition(consoleControler, drawingPositionCoordinates);
	};

	void TextOutputControler::adjustCreatingDataAttributeOffset() {	// nustatyti pozicija naujo kuriamo objekto lentelei
		drawingPositionCoordinates = { this->menuPosition.getScreenCoordinateX() + TEXT_OFFSET * 2,
									   this->menuPosition.getScreenCoordinateY() + TEXT_OFFSET * 7 };
		SetConsoleCursorPosition(consoleControler, drawingPositionCoordinates);
	};

	void TextOutputControler::displayAtrributesTextWithoutBorder() { 	// i duombazes lentele suvesti atributu pavadinimus
		SetConsoleTextAttribute(consoleControler, DEFAULT_ITEM_ATTRIBUTE_COLOR);
		cout << "ITEM NAME";
		adjustNextAttributeOffset(30);
		cout << "PRICE";
		adjustNextAttributeOffset(9);
		cout << "TYPE";
		adjustNextAttributeOffset(9);
		cout << "STATE";
		adjustNextAttributeOffset(7);
		cout << "ITEM CODE";
		adjustNextAttributeOffset(18);
		cout << "EXIST";
	};

	void TextOutputControler::displayPossibleAttributesForNewItem() {	// i naujo objekto kurimo lentele suvesti atributu pavadinimus
		adjustCreatingDataAttributeOffset();
		SetConsoleTextAttribute(consoleControler, DEFAULT_ITEM_ATTRIBUTE_COLOR);
		for (auto iterator = 0; iterator < 11; iterator++) {
			SetConsoleCursorPosition(consoleControler, drawingPositionCoordinates);
			if (iterator == 0)		 { cout << "ITEM NAME:" << endl;  drawingPositionCoordinates.Y += 1; drawingPositionCoordinates.X = 33; }
			else if (iterator == 2)  { cout << "PRICE:" << endl; drawingPositionCoordinates.Y += 1; drawingPositionCoordinates.X = 33; }
			else if (iterator == 4)  { cout << "TYPE:" << endl; drawingPositionCoordinates.Y += 1; drawingPositionCoordinates.X = 33; }
			else if (iterator == 6)  { cout << "STATE:" << endl; drawingPositionCoordinates.Y += 1; drawingPositionCoordinates.X = 33; }
			else if (iterator == 8)  { cout << "ITEM CODE:" << endl; drawingPositionCoordinates.Y += 1; drawingPositionCoordinates.X = 33; }
			else if (iterator == 10) { cout << "EXIST:" << endl; }
			else {
				for (auto iteratorForTable = 0; iteratorForTable < 37; iteratorForTable++) {
					cout << HORIZONTAL_LINE;
				}
				drawingPositionCoordinates.Y += 1; drawingPositionCoordinates.X = 33;
				cout << endl;
			}
		}
	};

	void TextOutputControler::displayAttributesNames() {
		adjustAttributesNamesPositionOffset();
		displayAtrributesTextWithoutBorder();
	};

	TextOutputControler::TextOutputControler() {
		text = DEFAULT_TEXT_MESSAGE;
		textColor = 0b10011111;
		allignmentStyle = DEFAULT_ALLIGNMENT_STYLE;
		textWrapping = DEFAULT_CHOICE;
		unactiveTitleColor = 0b10001111;
		activeTitleColor = 0b00111111;
		isTitleActive = 1;
		pathColor = 0b00001111;
	};

	TextOutputControler::~TextOutputControler() {};

	/*--------------------------------------------------------------------------------------------*/

	void DatabaseControler::getFileSelectionFromInterface(short controlerIndex) {		// gauname failo pavadinima
		itemOutputString.erase(itemOutputString.begin(), itemOutputString.end());
		itemDataList.erase(itemDataList.begin(), itemDataList.end());
		this->setItemDataList(itemDataList);
		for (auto iteratorForFiles = 0; iteratorForFiles < 11; iteratorForFiles++) {
			if (iteratorForFiles == controlerIndex) {
				readSelectedFile(existingFilesList[iteratorForFiles]);
			}
		}
	};

	void DatabaseControler::readSelectedFile(string existingFileName) {		// nuskaitymas is failo
		ifstream selectedFile(existingFileName.append(".txt"));
		unsigned int length;
		if (selectedFile.good()) {             // ar faila pavyko atidaryti ir ar jis egzistuoja?
			selectedFile.seekg(0, ios::end);  // ar failas tuscias?
			length = selectedFile.tellg();	 // per kiek poziciju zymeklis pasislinko einant epr failo turini
			if (length != 0) {				// jei zymeklis pasislinko per 0 poziciju, jis yra tuscias <-> kitu atveju jame kazkas yra
				selectedFile.seekg(0);	   //atstatome zymekli i failo pradzia, kadangi jis buvo is ten perkeltas
				while (!selectedFile.eof()) {
					ItemData temporaryObject;
					selectedFile >> temporaryObject.itemName;
					selectedFile >> temporaryObject.itemPriceEuros;
					selectedFile >> temporaryObject.itemType;
					selectedFile >> temporaryObject.itemState;
					selectedFile >> temporaryObject.itemCode;
					selectedFile >> temporaryObject.isItemExist;
					addObjectFromFile(temporaryObject);
				}
			}
		}
		createItemOutputString(this->getItemDataList());
	};

	void DatabaseControler::overwriteSelectedFile(string existingFileName, vector <ItemData> itemDataList) {	// funkcija duomenu irsaymui ir atnaujinimui i faila
		ofstream selectedFile(existingFileName.append(".txt"));
		for (auto objectsCounter = 0; objectsCounter < this->getItemDataList().size(); objectsCounter++) {
			selectedFile << itemDataList[objectsCounter].itemName << SPACE_CHAR;
			selectedFile << itemDataList[objectsCounter].itemPriceEuros << SPACE_CHAR;
			selectedFile << itemDataList[objectsCounter].itemType << SPACE_CHAR;
			selectedFile << itemDataList[objectsCounter].itemState << SPACE_CHAR;
			selectedFile << itemDataList[objectsCounter].itemCode << SPACE_CHAR;
			if (this->getItemDataList().size() - VECTOR_ARRAY_OFFSET == objectsCounter) {	// apsauga, kad nepasigautume nezinomo objekto nuskaite naujos eilutes simboli
				selectedFile << itemDataList[objectsCounter].isItemExist;
			}
			else selectedFile << itemDataList[objectsCounter].isItemExist << endl;
		}
	};

	vector <string> DatabaseControler::createItemOutputString(vector <ItemData> itemDataList) {		// suspaudzia visus atributus i viena stringa kad butu patogesnis isvedimas
		int iteratorForItems = 0; string temporaryString = "", temporaryCutoff = "";
		itemOutputString.erase(itemOutputString.begin(), itemOutputString.end());
		for (auto objectsCounter = 0; objectsCounter < itemDataList.size(); objectsCounter++) {
			temporaryString = "";
			temporaryString += itemDataList[objectsCounter].itemName;
			if (temporaryString.length() > 28) {
				temporaryString = "";
				temporaryString += itemDataList[objectsCounter].itemName.substr(0, 27) + "..";
			}
			if (temporaryString.length() <= 28) {
				for (auto iterator = temporaryString.length(); iterator <= 28; iterator++)
					temporaryString.append(" ");
			}
			temporaryString += VERTICAL_LINE;
			temporaryString += itemDataList[objectsCounter].itemPriceEuros;
			temporaryString += "eur";
			if (temporaryString.length() < 38) {
				for (auto iterator = temporaryString.length(); iterator < 38; iterator++)
					temporaryString.append(" ");
			}
			temporaryString += VERTICAL_LINE;
			temporaryCutoff = itemDataList[objectsCounter].itemType;
			if (temporaryCutoff.length() >= 8) {
				temporaryString += temporaryCutoff.substr(0, 6) + "..";
			}
			else if (temporaryCutoff.length() <= 7) {
				temporaryString += itemDataList[objectsCounter].itemType;
				for (auto iterator = temporaryCutoff.length(); iterator <= 7; iterator++)
					temporaryString.append(" ");
			}
			else temporaryString += itemDataList[objectsCounter].itemType;
			temporaryString += VERTICAL_LINE;
			temporaryString += itemDataList[objectsCounter].itemState;
			if (temporaryString.length() <= 53) {
				for (auto iterator = temporaryString.length(); iterator <= 53; iterator++)
					temporaryString.append(" ");
			}
			temporaryString += VERTICAL_LINE;
			temporaryString += itemDataList[objectsCounter].itemCode;
			if (temporaryString.length() <= 71) {
				for (auto iterator = temporaryString.length(); iterator <= 71; iterator++)
					temporaryString.append(" ");
			}
			temporaryString += VERTICAL_LINE;
			temporaryString += itemDataList[objectsCounter].isItemExist;
			if (temporaryString.length() < 78) {
				for (auto iterator = temporaryString.length(); iterator <= 78; iterator++)
					temporaryString.append(" ");
			}
			itemOutputString.push_back(temporaryString);
		}
		return itemOutputString;
	};

	bool DatabaseControler::setItemDataList(vector <ItemData> itemDataList) {
		this->itemDataList = itemDataList;
		return true;
	};

	vector <ItemData> DatabaseControler::getItemDataList() {
		return itemDataList;
	};

	void DatabaseControler::addObjectFromFile(ItemData itemDataObject) {	// funkcija skirta ideti objektui is failo i duomenu struktura, bet siuuo atveju ji puikiai tinka ir kuriant pirmaja funkcija
		this->itemDataList.push_back(itemDataObject);		// metodas objektui ikelti i vektoriu
	};

	void DatabaseControler::createFirstObject(vector <string> defAttributes, vector <ItemData> itemDataList) {	// pirmojo objekto sukurimas su pirmosiomis atributu reiksmemis
		ItemData defObject; // pats pirmasis kiekviename sarase esantis objektas
		defObject.itemName = defAttributes[0];  defObject.itemPriceEuros = defAttributes[0];
		defObject.itemType = defAttributes[0];  defObject.itemState = defAttributes[0];
		defObject.isItemExist = defAttributes[0]; defObject.itemCode = defAttributes[0];
		itemDataList.push_back(defObject);
		itemOutputString.erase(itemOutputString.begin(), itemOutputString.end());
		this->setItemDataList(itemDataList);
		createItemOutputString(this->getItemDataList());
	};

	void DatabaseControler::changeAttributeName(vector <ItemData> itemsDataList, short choosedDataIndex, short attributeSelection, string newAttributeName) {	// pagrindine funkcija, reikalinga atributu pervadinimui
		itemOutputString.erase(itemOutputString.begin(), itemOutputString.end());
		if (attributeSelection == 0) itemsDataList[choosedDataIndex].itemName = newAttributeName;
		if (attributeSelection == 1) itemsDataList[choosedDataIndex].itemPriceEuros = newAttributeName;
		if (attributeSelection == 2) itemsDataList[choosedDataIndex].itemType = newAttributeName;
		if (attributeSelection == 3) itemsDataList[choosedDataIndex].itemState = newAttributeName;
		if (attributeSelection == 4) itemsDataList[choosedDataIndex].itemCode = newAttributeName;
		if (attributeSelection == 5) itemsDataList[choosedDataIndex].isItemExist = newAttributeName;
		this->setItemDataList(itemsDataList);
		createItemOutputString(this->getItemDataList());
	};

	void DatabaseControler::deleteItemFromList(vector <ItemData> itemsDataList, short choosedDataIndex) { // pagrindine funkcija, reikalinga objektu trynimui
		itemOutputString.erase(itemOutputString.begin(), itemOutputString.end());
		itemsDataList.erase(itemsDataList.begin() + choosedDataIndex);
		this->setItemDataList(itemsDataList);
		createItemOutputString(this->getItemDataList());
	};

	void DatabaseControler::addNewItemAbove(vector <ItemData> itemsDataList, vector <string> itemsAttributes, short choosedDataIndex) { // ideda nauja objekta i vektoriaus nurodyta pozicija bei pakeitimus iraso i faila[pozicija = po indeksuotu objektu]
		ItemData createdObject;
		itemOutputString.erase(itemOutputString.begin(), itemOutputString.end());
		createdObject.itemName = itemsAttributes[0];
		createdObject.itemPriceEuros = itemsAttributes[1];
		createdObject.itemType = itemsAttributes[2];
		createdObject.itemState = itemsAttributes[3];
		createdObject.itemCode = itemsAttributes[4];
		createdObject.isItemExist = itemsAttributes[5];
		itemsDataList.insert(itemsDataList.begin() + choosedDataIndex, createdObject);
		this->setItemDataList(itemsDataList);
		createItemOutputString(this->getItemDataList());
	};

	void DatabaseControler::deleteWholeTable(vector <ItemData> itemsDataList) {
		itemOutputString.erase(itemOutputString.begin(), itemOutputString.end());
		itemsDataList.erase(itemsDataList.begin(), itemsDataList.end());
		this->setItemDataList(itemsDataList);
	};

	void DatabaseControler::addNewItemBellow(vector <ItemData> itemsDataList, vector <string> itemsAttributes, short choosedDataIndex) { // ideda nauja objekta i vektoriaus nurodyta pozicija bei pakeitimus iraso i faila [pozicija = pries indeksuota objekta]
		ItemData createdObject;
		itemOutputString.erase(itemOutputString.begin(), itemOutputString.end());
		createdObject.itemName = itemsAttributes[0];
		createdObject.itemPriceEuros = itemsAttributes[1];
		createdObject.itemType = itemsAttributes[2];
		createdObject.itemState = itemsAttributes[3];
		createdObject.itemCode = itemsAttributes[4];
		createdObject.isItemExist = itemsAttributes[5];
		itemsDataList.insert(itemsDataList.begin() + choosedDataIndex + VECTOR_ARRAY_OFFSET, createdObject);	// iterpimas po objektu
		this->setItemDataList(itemsDataList);
		createItemOutputString(this->getItemDataList());
	};

	vector <string> DatabaseControler::searchForExistingItems(vector <ItemData> itemsDataList, string keyword) {
		vector <ItemData> temporarySearchResults;
		itemOutputString.erase(itemOutputString.begin(), itemOutputString.end());
		for (auto iterator = 0; iterator < itemsDataList.size(); iterator++) {
			if (string::npos != itemsDataList[iterator].itemName.find(keyword)
				|| string::npos != itemsDataList[iterator].itemPriceEuros.find(keyword)
				|| string::npos != itemsDataList[iterator].itemType.find(keyword)
				|| string::npos != itemsDataList[iterator].itemState.find(keyword)
				|| string::npos != itemsDataList[iterator].itemCode.find(keyword)
				|| string::npos != itemsDataList[iterator].isItemExist.find(keyword)) {
				temporarySearchResults.push_back(itemsDataList[iterator]);
			}
		}
		return createItemOutputString(temporarySearchResults);
	};

	void DatabaseControler::swapStrings(string *jteratorValue, string *iteratorValue) {	// sortinimui reikalinga funkcija,kad apkeisti string kintamuju reiksmes
		string tempValue = *jteratorValue;
		*jteratorValue = *iteratorValue;
		*iteratorValue = tempValue;
	}

	void DatabaseControler::sortExistingVector(vector <ItemData> itemsDataList) {	// rikiavimo funkcija
		for (auto iterator = 0; iterator < this->getItemDataList().size() - VECTOR_ARRAY_OFFSET; iterator++) {
			for (auto jterator = 0; jterator < this->getItemDataList().size() - VECTOR_ARRAY_OFFSET; jterator++) {
				if (itemsDataList[jterator].itemName[0] - '0' > itemsDataList[jterator + VECTOR_ARRAY_OFFSET].itemName[0] - '0') {  // char -> int ir lyginu
					swapStrings(&itemsDataList[jterator].itemName, &itemsDataList[jterator + VECTOR_ARRAY_OFFSET].itemName);
					swapStrings(&itemsDataList[jterator].isItemExist, &itemsDataList[jterator + VECTOR_ARRAY_OFFSET].isItemExist);
					swapStrings(&itemsDataList[jterator].itemCode, &itemsDataList[jterator + VECTOR_ARRAY_OFFSET].itemCode);
					swapStrings(&itemsDataList[jterator].itemPriceEuros, &itemsDataList[jterator + VECTOR_ARRAY_OFFSET].itemPriceEuros);
					swapStrings(&itemsDataList[jterator].itemState, &itemsDataList[jterator + VECTOR_ARRAY_OFFSET].itemState);
					swapStrings(&itemsDataList[jterator].itemType, &itemsDataList[jterator + VECTOR_ARRAY_OFFSET].itemType);
				}
			}
		}
		this->setItemDataList(itemsDataList);
		createItemOutputString(this->getItemDataList());
	};

	DatabaseControler::DatabaseControler() {};

	DatabaseControler::~DatabaseControler() {};

	/*---------------------------------------------------------------------------------------*/

	void ActiveMenuControler::displayMenuWithItems() {
		setupActiveItemsPosition();
		activeItemsMenuList(this->getMenuItemList());
	};

	void ActiveMenuControler::displayMenuWithOneButton() {
		setupOneActiveButtonPosition();
		activeOneButtonMenu(this->getMenuItemList());
	};

	void ActiveMenuControler::displayMenuWithTwoButtons() {
		setupTwoActiveButtonsPosition();
		activeTwoButtonMenu(this->getMenuItemList());
	};

	void ActiveMenuControler::displayDatabaseMenu() {
		displayAttributesNames();
		setupDatabaseActiveButtonsPosition();
		activeDatabaseTableMenu(this->getMenuItemList());
	};

	void ActiveMenuControler::displayRenameMenu() {
		rename = true;	// jeigu pervadiname faila, mygtuku pozicija pasikeicia, negu naudojant kita meniu
		setupTwoActiveButtonsForRenameTablePosition();
		activeTwoButtonMenu(this->getMenuItemList());
	};

	void ActiveMenuControler::displayAdditionMenu() {
		create = true;  // jeigu kuriame objekta, mygtuku pozicija pasikeicia, negu naudojant kita meniu
		displayPossibleAttributesForNewItem();
		setupTwoActiveButtonsForCreationTablePosition();
		activeTwoButtonMenu(this->getMenuItemList());
	};

	void ActiveMenuControler::activeItemsMenuList(vector <string> itemIDList) {
		short temporaryIndex, tableIndex = 0;
		reactToKeyboardButton = ' ';
		if (getMenuActivity()) {
			controlerIndex = 0;
		}
		while (reactToKeyboardButton != 'X' && reactToKeyboardButton != 'x') {
			for (auto iteratorForY = 0; iteratorForY < this->getMenuItemList().size(); iteratorForY++) {
				SetConsoleCursorPosition(consoleControler, drawingPositionCoordinates);
				if (iteratorForY == controlerIndex) {
					SetConsoleTextAttribute(consoleControler, this->getActiveMenuItemColor());
					cout << this->getMenuItemList()[iteratorForY];
					drawingPositionCoordinates.Y += TEXT_OFFSET;
					drawingPositionCoordinates.X = getMenuPositionX() + TEXT_OFFSET;
				}
				else {
					SetConsoleTextAttribute(consoleControler, this->getNonActiveMenuItemColor());
					cout << this->getMenuItemList()[iteratorForY];
					drawingPositionCoordinates.Y += TEXT_OFFSET;
					drawingPositionCoordinates.X = getMenuPositionX() + TEXT_OFFSET;
				}
			}
			if (getMenuActivity()) {
				testIfAnyEnteredArrowAreValid(false);
			}
			else break;
			setupActiveItemsPosition();
		}
		temporaryIndex = controlerIndex;
		this->setControlerIndex(temporaryIndex);
	};

	void ActiveMenuControler::activeOneButtonMenu(vector <string> itemIDList) {
		short temporaryIndex;
		reactToKeyboardButton = ' ';
		if (getMenuActivity()) {
			controlerIndex = 0;
		}
		while (reactToKeyboardButton != 'X' && reactToKeyboardButton != 'x') {
			SetConsoleCursorPosition(consoleControler, drawingPositionCoordinates);
			SetConsoleTextAttribute(consoleControler, this->getActiveMenuItemColor());
			cout << this->getMenuItemList()[0];
			if (getMenuActivity()) {
				testIfAnyEnteredArrowAreValid(false);
			}
			else break;
			setupOneActiveButtonPosition();
		}
		temporaryIndex = controlerIndex;
		this->setControlerIndex(temporaryIndex);
	};

	void ActiveMenuControler::activeTwoButtonMenu(vector <string> itemIDList) {
		short temporaryIndex;
		reactToKeyboardButton = ' ';
		if (getMenuActivity()) {
			controlerIndex = 0;
		}
		while (reactToKeyboardButton != 'X' && reactToKeyboardButton != 'x') {		// kol neivedame X arba x, vyks aktyviu ir ne-aktyviu mygtuku spausdinimas 
			for (auto iteratorForY = 0; iteratorForY < this->getMenuItemList().size(); iteratorForY++) {
				SetConsoleCursorPosition(consoleControler, drawingPositionCoordinates);
				if (iteratorForY == controlerIndex) {
					SetConsoleTextAttribute(consoleControler, this->getActiveMenuItemColor());
					cout << this->getMenuItemList()[iteratorForY];
					drawingPositionCoordinates.X += TEXT_OFFSET * 12;
				}
				else {
					SetConsoleTextAttribute(consoleControler, this->getNonActiveMenuItemColor());
					cout << this->getMenuItemList()[iteratorForY];
					drawingPositionCoordinates.X += TEXT_OFFSET * 12;
				}
			}
			if (getMenuActivity()) {
				testIfAnyEnteredArrowAreValid(false);
			}
			else break;
			if (rename) setupTwoActiveButtonsForRenameTablePosition();	// jeigu funkcija kvieciame is kitos funkcijos, kuri yra skirta pervadinti atributus
			else if (create) setupTwoActiveButtonsForCreationTablePosition(); // jeigu funkcija kvieciame is funkcijos, kurios prasme - sukurti objekta
			else setupTwoActiveButtonsPosition();	// kitu atveju musu lentele yra standartines paskirties -> dazniausiai perspeti apie tam tikra event'a (sukurima/isejima/ect.)
		}
		rename = false; create = false;  // vel atstatome tikrinamuju kintamuju bazines reiksmes
		temporaryIndex = controlerIndex;
		this->setControlerIndex(temporaryIndex);
	};

	void ActiveMenuControler::activeDatabaseTableMenu(vector <string> itemIDList) {
		short temporaryIndex, iterator = 0; // laikinieji indeksai ir iteratoriai padeda valdyti "plaukiojima meniu"
		bool moreThan7 = false; // reikalingas nustatyti, kokiais atvejais iteratorius buna aukstesnis uz 7
		reactToKeyboardButton = ' ';
		if (getMenuActivity()) {
			controlerIndex = 0;
		}
		short temporayIndexValue = 0;
		while (reactToKeyboardButton != 'X' && reactToKeyboardButton != 'x') {
			for (auto iteratorForY = 0; iteratorForY < this->getMenuItemList().size(); iteratorForY++) {
				SetConsoleCursorPosition(consoleControler, drawingPositionCoordinates);
				if (iteratorForY == 0 || iteratorForY == 1) {
					if (iteratorForY == controlerIndex) {
						SetConsoleTextAttribute(consoleControler, this->getActiveMenuItemColor());
						cout << this->getMenuItemList()[iteratorForY];
						drawingPositionCoordinates.X += TEXT_OFFSET * 20;
					}
					else {
						SetConsoleTextAttribute(consoleControler, this->getNonActiveMenuItemColor());
						cout << this->getMenuItemList()[iteratorForY];
						drawingPositionCoordinates.X += TEXT_OFFSET * 20;
					}
				}
			} 
			temporayIndexValue = controlerIndex;
			if (controlerIndex > 1) {
				setupDatabaseActiveButtonsPosition();
				drawingPositionCoordinates.X += TEXT_OFFSET * 20;
				SetConsoleCursorPosition(consoleControler, drawingPositionCoordinates);
				SetConsoleTextAttribute(consoleControler, this->getUnactiveTitleColor());
				cout << this->getMenuItemList()[1];
			}
			setupDatabaseListPosition();
			for (auto iteratorForList = 0; iteratorForList < itemOutputString.size(); iteratorForList++) {
				SetConsoleCursorPosition(consoleControler, drawingPositionCoordinates);
				if (iteratorForList == controlerIndex - TABLE_OFFSET) {
					SetConsoleTextAttribute(consoleControler, this->getActiveMenuItemColor());
					if (itemOutputString.size() - VECTOR_ARRAY_OFFSET >= iteratorForList + iterator) {
						cout << itemOutputString[iteratorForList + iterator];
					}
					else if (itemOutputString.size() - VECTOR_ARRAY_OFFSET == iteratorForList + iterator) resetLine(); // jeigu nera objekto, laukeli atnaujiname
					drawingPositionCoordinates.Y += TABLE_OFFSET;
				}
				else if (iteratorForList != controlerIndex - TABLE_OFFSET) {
					SetConsoleTextAttribute(consoleControler, this->getNonActiveMenuItemColor());
					if (itemOutputString.size() - VECTOR_ARRAY_OFFSET >= iteratorForList + iterator)
						cout << itemOutputString[iteratorForList + iterator];
					else if (itemOutputString.size() - VECTOR_ARRAY_OFFSET == iteratorForList + iterator) resetLine(); // jeigu nera objekto, laukeli atnaujiname
					drawingPositionCoordinates.Y += TABLE_OFFSET;
				}
			}	
			setupDatabaseActiveButtonsPosition();
			if (getMenuActivity()) {
				testIfAnyEnteredArrowAreValid(true);
			}
			else break;
			setupDatabaseActiveButtonsPosition();
		}
		temporaryIndex = controlerIndex;
		if (temporaryIndex < 2) {
			this->setControlerIndex(temporayIndexValue);
		}
		else this->setControlerIndex(temporaryIndex);
	};

	void ActiveMenuControler::resetLine() {
		cout << "                             " << VERTICAL_LINE << "        " << VERTICAL_LINE << "        " << VERTICAL_LINE << "      " << VERTICAL_LINE << "                 " << VERTICAL_LINE << "      ";
	};

	void ActiveMenuControler::setupDatabaseListPosition() {
		drawingPositionCoordinates.Y = this->getMenuPositionY() + TEXT_OFFSET * 9;
		drawingPositionCoordinates.X = this->getMenuPositionX() + TEXT_OFFSET;
		SetConsoleCursorPosition(consoleControler, drawingPositionCoordinates);
	};

	void ActiveMenuControler::testIfAnyEnteredArrowAreValid(bool isDatabaseInterfaceActive) {
		reactToKeyboardButton = _getch();
		if (this->getMenuItemList().size() != 1) {
			switch (reactToKeyboardButton) {
			case 72: { // rodykle i virsu
				controlerIndex--;
				if (controlerIndex <= 0) {
					controlerIndex = 0;
				} break;
			}
			case 80: { // rodykle i apacia
				controlerIndex++;
				if (isDatabaseInterfaceActive) {
					if (itemOutputString.size() > itemOutputString.size()) {
						if (controlerIndex >= this->getMenuItemList().size() + itemOutputString.size() - TABLE_OFFSET) {
							controlerIndex = this->getMenuItemList().size() + itemOutputString.size() - TABLE_OFFSET;
						}
					}
					else {
						if (controlerIndex >= this->getMenuItemList().size() + itemOutputString.size() - VECTOR_ARRAY_OFFSET) {
							controlerIndex = this->getMenuItemList().size() + itemOutputString.size() - VECTOR_ARRAY_OFFSET;
						}
					}
				}
				else {
					if (controlerIndex >= this->getMenuItemList().size() - VECTOR_ARRAY_OFFSET) {
						controlerIndex = this->getMenuItemList().size() - VECTOR_ARRAY_OFFSET;
					}
				}
			} break;
			default: { break; }
			}
		}
	};

	void ActiveMenuControler::addMenuItem(string itemID) {
		this->menuItemList.push_back(itemID);
	};

	bool ActiveMenuControler::setMenuItemList(vector <string> itemIDList) {
		this->menuItemList = itemIDList;
		return true;
	};

	bool ActiveMenuControler::setActiveMenuItemColor(short activeColor) {
		this->activeMenuItemColor = activeColor;
		return true;
	};

	short ActiveMenuControler::getActiveMenuItemColor() {
		return activeMenuItemColor;
	};

	vector <string> ActiveMenuControler::getMenuItemList() {
		return menuItemList;
	};

	bool ActiveMenuControler::setNonActiveMenuItemColor(short currentColor) {
		this->nonActiveMenuItemColor = currentColor;
		return true;
	};

	short ActiveMenuControler::getNonActiveMenuItemColor() {
		return nonActiveMenuItemColor;
	};

	void ActiveMenuControler::setupActiveItemsPosition() {
		drawingPositionCoordinates.Y = this->getMenuPositionY() + TEXT_OFFSET * 4;
		drawingPositionCoordinates.X = this->getMenuPositionX() + TEXT_OFFSET;
	};

	void ActiveMenuControler::setupOneActiveButtonPosition() {
		drawingPositionCoordinates.Y = this->getMenuPositionY() + TEXT_OFFSET * this->getMenuSizeY() - TEXT_OFFSET * 3;
		drawingPositionCoordinates.X = this->getMenuPositionX() + TEXT_OFFSET * 16;
	};

	void ActiveMenuControler::setupTwoActiveButtonsPosition() {
		drawingPositionCoordinates.Y = this->getMenuPositionY() + TEXT_OFFSET * 7;
		drawingPositionCoordinates.X = this->getMenuPositionX() + TEXT_OFFSET * 10;
	};

	void ActiveMenuControler::setupTwoActiveButtonsForRenameTablePosition() {
		drawingPositionCoordinates.Y = this->getMenuPositionY() + TEXT_OFFSET * 10;
		drawingPositionCoordinates.X = this->getMenuPositionX() + TEXT_OFFSET * 13;
		SetConsoleCursorPosition(consoleControler, drawingPositionCoordinates);
	};

	void ActiveMenuControler::setupTwoActiveButtonsForCreationTablePosition() {
		drawingPositionCoordinates.Y = this->getMenuPositionY() + TEXT_OFFSET * 20;
		drawingPositionCoordinates.X = this->getMenuPositionX() + TEXT_OFFSET * 10;
		SetConsoleCursorPosition(consoleControler, drawingPositionCoordinates);
	};

	void ActiveMenuControler::setupDatabaseActiveButtonsPosition() {
		drawingPositionCoordinates.Y = this->getMenuPositionY() + TEXT_OFFSET * 4;
		drawingPositionCoordinates.X = this->getMenuPositionX() + TEXT_OFFSET * 3;
		SetConsoleCursorPosition(consoleControler, drawingPositionCoordinates);
	};

	bool ActiveMenuControler::setMenuActivity(bool isMenuActive) {
		this->isMenuActive = isMenuActive;
		return true;
	};

	bool ActiveMenuControler::getMenuActivity() {
		return isMenuActive;
	};

	bool ActiveMenuControler::setControlerIndex(short controlerIndex) {
		this->controlerIndex = controlerIndex;
		return true;
	};

	short ActiveMenuControler::getControlerIndex() {
		return controlerIndex;
	};

	ActiveMenuControler::ActiveMenuControler() {
		menuItemList = { "DefaultChoice0", "DefaultChoice1", "DefaultChoice2" };
		activeMenuItemColor = 0b00111111;
		nonActiveMenuItemColor = 0b10011111;
		controlerIndex = DEFAULT_CHOICE;
	};

	ActiveMenuControler::~ActiveMenuControler() {};

}