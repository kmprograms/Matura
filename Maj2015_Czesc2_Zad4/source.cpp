#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <tuple>


auto pobierz_dane(const std::string& nazwa_pliku) -> std::vector<std::string> {
	std::ifstream odczyt;
	odczyt.open(nazwa_pliku);

	std::vector<std::string> dane;

	if (odczyt.is_open()) {
		std::string wiersz;

		while (!odczyt.eof()) {
			std::getline(odczyt, wiersz);
			if (!wiersz.empty()) {
				dane.emplace_back(wiersz);
			}
		}

		odczyt.close();
	}
	else {
		std::cout << "Blad polaczenia z plikiem " << nazwa_pliku << std::endl;
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
auto ile_zer(const std::string& liczba) -> int {
	int ile = 0;
	for (char x : liczba) {
		if (x == '0') {
			++ile;
		}
	}
	return ile;
}

auto ile_liczb(const std::vector<std::string>& dane) -> int {
	int ile = 0;

	for (const auto& d : dane) {
		if (ile_zer(d) * 2 > d.length()) {
			++ile;
		}
	}
	return ile;
}

// ------------------------------------------------------------------------------
// ZAD 4.2
// ------------------------------------------------------------------------------
auto podzielna_dwa(const std::string& liczba) -> bool {
	return liczba.back() == '0';
}

auto podzielna_osiem(const std::string& liczba) -> bool {
	return liczba.substr(liczba.length() - 3) == "000";
}

auto ile_podzielnych(const std::vector<std::string>& dane) -> std::tuple<int, int> {
	int ile2 = 0, ile8 = 0;

	for (const auto& d : dane) {
		if (podzielna_dwa(d)) {
			++ile2;
		}

		if (podzielna_osiem(d)) {
			++ile8;
		}
	}

	return std::make_tuple(ile2, ile8);
}


// ------------------------------------------------------------------------------
// ZAD 4.3
// ------------------------------------------------------------------------------
auto min_max(const std::vector<std::string>& dane) -> std::tuple<int, int> {
	std::string min_liczba = dane[0], max_liczba = dane[0];
	int min_idx = 0, max_idx = 0;

	for (int i = 1; i < dane.size(); ++i) {
		if (dane[i].length() > max_liczba.length() || (dane[i].length() == max_liczba.length() && dane[i] > max_liczba)) {
			max_liczba = dane[i];
			max_idx = i;
		}

		if (dane[i].length() < min_liczba.length() || (dane[i].length() == min_liczba.length() && dane[i] < min_liczba)) {
			min_liczba = dane[i];
			min_idx = i;
		}
	}

	return std::make_tuple(min_idx + 1, max_idx + 1);
}

auto zapisz_dane(const std::string& nazwa_pliku, const std::vector<std::string>& dane) -> void {
	std::ofstream zapis;
	zapis.open(nazwa_pliku);

	if (zapis.is_open()) {
		zapis << "4.1: ";
		zapis << ile_liczb(dane) << std::endl;

		zapis << "4.2: ";
		int ile2 = 0, ile8 = 0;
		std::tie(ile2, ile8) = ile_podzielnych(dane);
		zapis << "PODZIELNE 2: " << ile2 << ", PODZIELNE 8: " << ile8 << std::endl;

		zapis << "4.3: ";
		int min_idx = 0, max_idx = 0;
		std::tie(min_idx, max_idx) = min_max(dane);
		zapis << "MIN = " << min_idx << ", MAX = " << max_idx << std::endl;
		
		zapis.close();
	}
	else {
		std::cout << "Blad polaczenia z plikiem " << nazwa_pliku << std::endl;
	}
}

auto main() -> int {

	const std::string NAZWA_PLIKU_ODCZYT = "liczby.txt";
	const std::string NAZWA_PLIKU_ZAPIS = "wynik4.txt";

	std::vector<std::string> dane = pobierz_dane(NAZWA_PLIKU_ODCZYT);
	// pokaz_dane(dane);
	zapisz_dane(NAZWA_PLIKU_ZAPIS, dane);

	std::cin.get();
	return 0;
}