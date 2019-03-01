#pragma once	// "visual studio"

#ifndef OBJECTSCONFIGURATION_H	// "code blocks"
#define OBJECTSCONFIGURATION_H

#include "interfaceGeneration.h"	// iterpiame grafines sasajos su duombazes risimo biblioteka

namespace interfaceDrawingLibrary {		// vel naudojame ta pati namespace sriti, kad klase su funkcijomis butu susieti kartu su bibliotekomis

	class MenuObjectPathControler : public DatabaseControler {		// klase, kurioje yra visi grafiniai objektai bei meniu valdikliai paveldi duombazes valdikli, kuriame saugoma informacija apie prekes
	public:
		void fancyExitConfiguration();	// grazesnis isejimas
		void menuConfiguration();	// pradinio meniu lango aktyvavimas

		void informationTablePath();	// pradiniame meniu pasirinke informacine skilti, atidarome meniu, skirta visai bendrai informacijai isvesti
		void databasePath();	//	kelias i duomenu bazes valdymo meniu valdyklius
		void databaseTablePath();	// duomenu bazes lenteles ijungimas
		void databaseChangingChoices();		// lenteles, kurioje yra saugomos pagrindines funkcijos su failuose esanciais duomenimis, aktyvavimas
		void pathFromAttributesSelectionToRename();	// pasinaudoje sia funkcija galime eiti is atributu pasirinkimo i ju pervadinimo sriti
		void changingNameTableTitleActive();	// funkcija reikalinga interpretuoti, jog kol vyksta vartotojo ivedimas, langas islieka aktyvus
		void changingNameTableTitleUnactive();		// funkcija reikalinga interpretuoti, jog kol vyksta vartotojo ivedimas, langas islieka ne-aktyvus

		void attributesChangingPath();	// kelias i atributu keitimo meniu langus

		void renameAnyAttribute(); // suglausta funkcija, reikalinga 5-is kartus is eiles atlikti pasikartojancius ~10veiksmu (nustato, kuri atributa pervadinsime pagal pasirinkta kontrolerio indekso numeri)
		void renameAttributeAndOverwriteFile(); // pervadinimo atributo bei failo atnaujinimo funkciju kombinacija
		void requestForInput(); // funkcija, reikalinga pristabdyti aktyvaus meniu vykdyma del input'o gavimo
		void requestForKeyword();
		void requestForMultiInput();	// keleto reiksmiu ivedimas

		void pathFromWarningMessageToSearchResults();
		void pathFromChangingAttributeToDatabase();	// sios funkcijos pagalba griztame atgal is atributu keitimo meniu i duombazes langa paspaude CANCEL

		void resetConsole();	// atnaujinam konsoles langa
		void databaseMenuTitleUnactive();	// duombazes meniuTitle padarome neaktyvu taip interpreduodami jo isjungima ir sumazindami konsoles lango mirgejima
		void itemDeletionHandle(); // funkcija, turinti objekto trynimo kontroleri

		void activeCreationTitle();	// funkcijos reikalingos interpretuoti meniu aktyvuma, kol laukiama vartoto ivesties
		void unactiveCreationTitle();
		void activeKeywordSearcher();

		void displayMainMenu(bool);		// atvaizduoja pagrindinio meniu langa
		void displayMainInformationMenu(bool);	// atvaizduoja pagrindines informacijos langa
		void displayExitConfirmationMenu(bool);		// isejimo is programos sutikimo langas
		void displayMainFunctionsInformationMenu(bool);		// meniu, kuriame aprasytos funkcijos
		void displayMainControlsInformationMenu(bool);		// meniu, kuriame nurodytos kontroles
		void displayMainAboutInformationMenu(bool);		// valdyklio "apie" aktyvavimas
		void displayMainVersionInformationMenu(bool);	// informacija apie programos versija
		void displayDatabaseTableMenu(bool);	// duomenu bazes reliacine lentele
		void displayDatabaseContentMenu(bool);	// duombazes failu saraso meniu
		void displayDataSettingsMenu(bool);		// manipuliacijos su duomenimis pasirinkimo meniu
		void displayAttributeChangingSelectionMenu(bool);	// pasirinkimo, kuri atributa pervadinsime, meniu
		void displayAttributeChangingWindow(bool, string); // sioje funkcijoje turime ir objekta, kuris priklauso nuo katik musu ivesto string kintamojo
		void displayAttributesChangingConfirmation(bool);	// atributo pervadinimo sutikimo ir patvirtinimo meniu
		void displayMenuAskingForItemDeletion(bool);	// meniu, kuris klausia, ar tikrai norime panaikinti objekta
		void displayItemDeletionConfirmationMenu(bool); // patvirtinimo pranesimas, kad pavyko sunaikinti elementa
		void displayItemCreationMenu(bool); // meniu, kuriame leidziama ivesti naujo kuriamo objekto atributu reiksmems
		void displayItemCreationConfirmationMenu(bool);  // naujo sukurto objekto notifikacija
		void displayEnterSearchKeywordWindow(bool, string);   // langas, i kuri galima irasyt, pagal kuri zodi ieskoti objektu duomenu bazeje
		void displayDatabaseSearchResult(bool);		// reliacines aibes atvaizdavimo objektas paieskos rezultatams atvaizduoti
		void displaySearchResultsWarningMessage(bool);   // pranesimas, kad negalima atlikineti jokiu veiksmu su duomenimis, kurie yra isvesti i paieskos rezultato vektoriu
		void displayMenuAskingForAllItemDeletion(bool);	// isspausdinti langa, kuriame ispejama apie busima visu failu istrynima
		void displayMoreOptionsMenu(bool);		// leidzia vartotojui duomenu bazeje pasirinkti siek tiek daugiau veiksmu
		void displayConfirmationAboutCreatingFirstListElement(bool);	// indikatorius apie pirmojo elemento tusciajame sarase (pranesimas)
		MenuObjectPathControler();	// konstruktorius
		~MenuObjectPathControler();	// destruktorius

	};	// klases pabaiga

}	// namespace pabaiga

#endif