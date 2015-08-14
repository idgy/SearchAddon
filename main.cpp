#include <iostream>
#include<fstream>

const std::string homePage = "http://yandex.ru";

class SearchAddon
{
public:

	SearchAddon();

	void SetHPFlag();
	void SetDSFlag();
	void SetNTFlag();
	void SetSTFlag();

	void Process();

private:
	void SetHomePage();
	void SetDefaultSearch();

private:
	bool setHomePage;
	bool setDefaultSearch;
	bool setNewTab;
	bool setStartTab;
};

SearchAddon::SearchAddon()
: setHomePage(false)
, setDefaultSearch(false)
, setNewTab(false)
, setStartTab(false)
{

}

void SearchAddon::SetDSFlag()
{
	setDefaultSearch = true;
}

void SearchAddon::SetHPFlag()
{
	setHomePage = true;
}
void SearchAddon::SetNTFlag()
{
	setNewTab = true;
}
void SearchAddon::SetSTFlag()
{
	setStartTab = true;
}

void SearchAddon::Process()
{
	if (setHomePage)
		SetHomePage();

	if (setDefaultSearch)
		SetDefaultSearch();

}

void SearchAddon::SetDefaultSearch()
{
	std::cout << "set default search: need implement\n";

	std::ofstream reg, batch;
	reg.open("ds.reg", std::ios::out);

	reg << "Windows Registry Editor Version 5.00" << std::endl
		<< std::endl
		<< "[HKEY_LOCAL_MACHINE\\Software\\Policies\\Google]" << std::endl
		<< std::endl
		<< "[HKEY_LOCAL_MACHINE\\Software\\Policies\\Google\\Chrome]" << std::endl
		<< "\"DefaultSearchProviderSearchURL\"=\"" << homePage.c_str() << "/search?text={searchTerms}\"" << std::endl
		<< "\"DefaultSearchProviderSuggestURL\"=\"" << homePage.c_str() << "/suggest?text={searchTerms}\"" << std::endl
		<< std::endl;
	
	reg.close();
	batch.open("ds.bat", std::ios::out);
	batch << "regedit /s ds.reg";
	batch.close();

	system("ds.bat");

	remove("ds.reg");
	remove("ds.bat");

	std::cout << "THe end \n";
}

void SearchAddon::SetHomePage()
{
	std::cout << "set home page: need implement \n";

	std::ofstream reg, batch;
	reg.open("hp.reg", std::ios::out);

	reg << "Windows Registry Editor Version 5.00" << std::endl
		<< std::endl
		<< "[HKEY_LOCAL_MACHINE\\Software\\Policies\\Google]" << std::endl
		<< std::endl
		<< "[HKEY_LOCAL_MACHINE\\Software\\Policies\\Google\\Chrome]" << std::endl
		<< "\"HomepageLocation\"=\"" << homePage.c_str() << "\"" << std::endl
		<< "\"HomepageIsNewTabPage\"=" << "dword:00000000" << std::endl
		<< "\"ShowHomeButton\"=" << "dword:00000001" << std::endl
		<< std::endl;

	reg.close();
	batch.open("hp.bat", std::ios::out);
	batch << "regedit /s hp.reg";
	batch.close();

	system("hp.bat");

	remove("hp.reg");
	remove("hp.bat");

}

void main(int argc, char** argv)
{
	std::cout << "argc: " << argc << std::endl;
	if (argc == 1) {
		std::cout << "Too few params. Expected one of: /HP /DS /NT /ST \n";
	}

	SearchAddon addon;

	for (int i = 1; i < argc; ++i) {
		std::string str = argv[i];
		std::cout << "arg: " << str.c_str() << std::endl;
		if (strcmp(argv[i], "/HP") == 0) {
			addon.SetHPFlag();
		}
		else if (strcmp(argv[i], "/DS") == 0) {
			addon.SetDSFlag();
		}
	}

	addon.Process();
}