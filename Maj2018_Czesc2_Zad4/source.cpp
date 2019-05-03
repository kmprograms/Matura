#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <tuple>
#include <cmath>

auto pobierz_dane(const std::string& nazwa_pliku) -> std::vector<std::string> {
	std::ifstream odczyt;
	odczyt.open(nazwa_pliku);

	std::vector<std::string> dane;
	std::string wiersz;

	if (odczyt.is_open()) {
		while (!odczyt.eof()) {
			std::getline(odczyt, wiersz);
			
			if (!wiersz.empty()) {
				dane.emplace_back(wiersz);
			}
		}
		odczyt.close();
	} 
	else {
		std::cout << "Blad komunikacji z plikiem " << nazwa_pliku << std::endl;
	}

	return dane;
}

auto pokaz_dane(const std::vector<std::string>& dane) -> void {
	for (const auto& d : dane) {
		std::cout << d << std::endl;
	}
}

// ------------------------------------------------------------------------------
// ZAD 4.1
// ------------------------------------------------------------------------------
auto odczyt_komunikat(const std::vector<std::string>& dane) -> std::string {
	std::string komunikat;	
	for (unsigned int i = 39; i < dane.size(); i += 40) {		
		komunikat += dane[i][9];
	}
	
	return komunikat;
}

// ------------------------------------------------------------------------------
// ZAD 4.2
// ------------------------------------------------------------------------------
auto ilosc_roznych_znakow(const std::string& napis) -> int {
	std::set<char> znaki{napis.begin(), napis.end()};
	return znaki.size();
}

auto napis_max_ilosc_roznych_znakow(const std::vector<std::string>& dane) -> std::tuple<std::string, int> {
	
	std::string napis = dane[0];
	int ilosc_max = ilosc_roznych_znakow(dane[0]), ilosc;

	for (unsigned int i = 1; i < dane.size(); ++i) {
		ilosc = ilosc_roznych_znakow(dane[i]);
		if (ilosc > ilosc_max) {
			ilosc_max = ilosc;
			napis = dane[i];
		}
	}
	return std::make_tuple(napis, ilosc_max);
}

// ------------------------------------------------------------------------------
// ZAD 4.3
// ------------------------------------------------------------------------------
auto odleglosc_znaki(const std::string& napis) -> bool {
	for (int i = 0; i < napis.length(); ++i) {
		for (int j = i + 1; j < napis.length(); ++j) {
			if (abs(napis[i] - napis[j]) > 10) {
				return false;
			}
		}
	}
	return true;
}

auto ile_napisow(const std::vector<std::string>& dane) -> std::vector<std::string> {
	std::vector<std::string> napisy;
	for (const auto& d : dane) {
		if (odleglosc_znaki(d)) {
			napisy.emplace_back(d);
		}
	}
	return napisy;
}

// ------------------------------------------------------------------------------
// ZAPIS
// ------------------------------------------------------------------------------
auto zapisz_dane(const std::string& nazwa_pliku, const std::vector<std::string>& dane) -> void {
	std::ofstream zapis;
	zapis.open(nazwa_pliku);

	if (zapis.is_open()) {
		zapis << "4.1: ";
		zapis << odczyt_komunikat(dane) << std::endl;

		zapis << "4.2: ";
		std::string s_max;
		int i_max;
		std::tie(s_max, i_max) = napis_max_ilosc_roznych_znakow(dane);
		zapis << s_max << " " << i_max << std::endl;

		zapis << "4.3:" << std::endl;
		const auto napisy = ile_napisow(dane);
		for (const auto& n : napisy) {
			zapis << n << std::endl;
		}

		zapis.close();
	}
	else {
		std::cout << "Blad polaczenia z plikiem " << nazwa_pliku << std::endl;
	}
}

int main() {

	const std::string NAZWA_PLIKU_ODCZYT = "sygnaly.txt";
	const std::string NAZWA_PLIKU_ODCZYT_PRZYKLAD = "przyklad.txt";
	const std::string NAZWA_PLIKU_ZAPIS = "wyniki4.txt";

	std::vector<std::string> dane = pobierz_dane(NAZWA_PLIKU_ODCZYT);
	// std::vector<std::string> dane = pobierz_dane(NAZWA_PLIKU_ODCZYT_PRZYKLAD);
	// pokaz_dane(dane);

	zapisz_dane(NAZWA_PLIKU_ZAPIS, dane);
 
	std::cin.get();
	return 0;
}