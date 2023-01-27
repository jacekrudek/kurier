/** @file */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#include "struktury.h"
#include "file_management.h"

void wypisz_intrukcje()
{
	std::cout << "Blad w pliku wejsciowym." << std::endl << std::endl;
	std::cout << "Poprawny format pliku to: (<miasto A> - <miasto B>: <odleglosc>)" << std::endl;
	std::cout << "Pamietaj ze:" << std::endl;
	std::cout << "- czesc dziesietna liczby nalezy oddzielic od czesci calkowitej KROPKA, a nie przecinkiem," << std::endl;
	std::cout << "- kazda inicjowana trasa musi posiadac miasto A, miasto B oraz dystans miedzy nimi," << std::endl;
	std::cout << "- symbol '-' oznacza droge dwukierunkowa, natomiast '->' droge jednokierunkowa w strone miasta B," << std::endl;
	std::cout << "- trasy nalezy oddzielac przecinkami." << std::endl;
	return;
}
std::vector<std::string>optymalizacja_pliku(const std::string& nazwa_pliku)
{
	std::vector<std::string> finisz;
	std::vector<char> zoptymalizowany;
	std::ifstream plik(nazwa_pliku);
	char c;
	if (plik.fail())
	{
		std::cout << "Zle zainicjowane pliki wejscia/wyjscia." << std::endl;
		std::cout << "Odpowiedni format komendy to: " << std::endl;
		std::cout << R"(.\Kurier -i <plik z danymi wejsciowymi> -d <plik z rozwiazaniem>)" << std::endl;

	}
	while (plik.get(c))
	{
		if (c == ' ' || c == '\n' || c == '(' || c == ')' || c == '\r')
		{
			continue;
		}
		zoptymalizowany.push_back(c);
	}
	for (int i = 0; i < zoptymalizowany.size(); i++)
	{
		if (zoptymalizowany[i] == '-' && zoptymalizowany[i + 1] == '>')
		{
			finisz.push_back("->");
		}
		else if (zoptymalizowany[i] == '>')
		{
			continue;
		}
		else if (zoptymalizowany[i] == ':')
		{
			finisz.push_back(":");
		}
		else if (zoptymalizowany[i] == ',')
		{
			finisz.push_back(",");
		}
		else if (zoptymalizowany[i] == '-')
		{
			finisz.push_back("-");
		}
		else
		{
			std::string temp;
			int counter = 0;
			for (int y = i; y < zoptymalizowany.size(); y++)
			{
				if (zoptymalizowany[y] == '-' || zoptymalizowany[y] == ':' || zoptymalizowany[y] == ',')
				{
					break;
				}
				temp.push_back(zoptymalizowany[y]);
				counter++;
			}
			finisz.push_back(temp);
			i += counter - 1;
		}
	}
	return finisz;
}
bool czy_liczba(const std::string& string)
{
	for (const char& c : string) {
		if (std::isdigit(c) == false && c != '.')
			return false;
	}
	return true;
}
void wprowadz_do_mapy(const std::vector<std::string>wejscie, std::map<std::string, std::map<std::string, double>>& miasta_i_odleglosci, std::map<std::string, bool>& visited, bool& powodzenie_wczytywania)
{
	if (wejscie.size() < 5)
	{
		wypisz_intrukcje();
		powodzenie_wczytywania = false;
		return;
	}
	for (int i = 0; i < wejscie.size(); i = i + 6)
	{
		//Sprawdzenie czy plik wejsciowy jest odpowiednio sformatowany
		if ((wejscie[i + 1] != "-" && wejscie[i + 1] != "->") || czy_liczba(wejscie[i + 4]) == false)
		{
			powodzenie_wczytywania = false;
			wypisz_intrukcje();
			return;
		}
		//dla znaku '-' wprowadzenie polaczenia zarowno dla miasta a->b jak i b->a
		else if (wejscie[i + 1] == "-")
		{
			miasta_i_odleglosci[wejscie[i]][wejscie[i + 2]] = std::stod(wejscie[i + 4]);
			miasta_i_odleglosci[wejscie[i + 2]][wejscie[i]] = std::stod(wejscie[i + 4]);
		}
		//dla znaaku "->" wprowadzenie polaczenia jednokierunkowego a->b
		else if (wejscie[i + 1] == "->")
		{
			miasta_i_odleglosci[wejscie[i]][wejscie[i + 2]] = std::stod(wejscie[i + 4]);
		}
		//wprowadzenie miast do mapy odwiedzonych
		visited[wejscie[i]] = false;
		visited[wejscie[i + 2]] = false;
	}
	
}
void zapisz_do_pliku(const std::string& nazwa_pliku, const podroz& wynik)
{
	std::ofstream plik(nazwa_pliku);
	if (plik.is_open())
	{
		plik << "Najkrotsza mozliwa odleglosc: " << wynik.dystans << std::endl;
		plik << "Kolejnosc odwiedzanych miast: ";
		for (int i = 0; i < wynik.sciezka.size(); i++)
		{
			plik << wynik.sciezka[i] << ", ";
		}
		plik << std::endl << std::endl << "Przyjemnej podrozy!";
	}
	plik.close();
}