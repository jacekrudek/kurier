#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#include "tsp_algorithm.h"
#include "struktury.h"
#include "file_management.h"


int main(int argc, char* argv[]) {
	//Zczytywanie danych z konsoli we/wy
	plik ww;
	for (int i = 1; i < argc-1; i++)
	{
		std::string temp = argv[i];
		if (temp == "-i")
		{
			ww.wejsciowy = argv[i + 1];
			i++;
		}
		else if (temp == "-d")
		{
			ww.wyjsciowy = argv[i + 1];
			i++;
		}
	}
	//Wypisanie krótkiej instrukcji w przypadku niezainicjowanych plików we/wy
	if (ww.wejsciowy.empty() || ww.wyjsciowy.empty())
	{
		std::cout << "Zle zainicjowane pliki wejscia/wyjscia." << std::endl;
		std::cout << "Odpowiedni format komendy to: " << std::endl;
		std::cout << R"(.\Kurier -i <plik z danymi wejsciowymi> -d <plik z rozwiazaniem>)" << std::endl;
		return 0;
	}
	//Inicjacja map i optymalizacja pliku wejsciowego
	std::map<std::string, std::map<std::string, double>> miasta_i_odleglosci;
	std::map<std::string, bool>visited;
	//Optymalizacja pliku do prostszej mozliwej postaci a nastepnie wprowadzenie danych do mapy 
	bool loading_success=true;//<-- specjalna zmienna dla sytuacji w ktorej plik jest pusty/dziwny
	std::vector<std::string> wejscie = optymalizacja_pliku(ww.wejsciowy);	
	wprowadz_do_mapy(wejscie, miasta_i_odleglosci, visited, loading_success);
	if (!loading_success)
	{
		return 0;
	}
	
	//for (int i = 0; i < wejscie.size(); i=i+6)
	//{
	//	//Sprawdzenie czy plik wejsciowy jest odpowiednio sformatowany
	//	if ((wejscie[i+1] !="-" && wejscie[i + 1] != "->")|| czy_liczba(wejscie[i + 4]) == false)
	//	{
	//		wypisz_intrukcje();
	//		return 0;
	//	}
	//	//dla znaku '-' wprowadzenie polaczenia zarowno dla miasta a->b jak i b->a
	//	else if (wejscie[i + 1] == "-")
	//	{
	//		miasta_i_odleglosci[wejscie[i]][wejscie[i + 2]]= std::stod(wejscie[i + 4]);
	//		miasta_i_odleglosci[wejscie[i+2]][wejscie[i]] = std::stod(wejscie[i + 4]);
	//	}
	//	//dla znaaku "->" wprowadzenie polaczenia jednokierunkowego a->b
	//	else if (wejscie[i + 1] == "->")
	//	{
	//		miasta_i_odleglosci[wejscie[i]][wejscie[i + 2]] = std::stod(wejscie[i + 4]);
	//	}
	//	//wprowadzenie miast do mapy odwiedzonych
	//	visited[wejscie[i]] = false;
	//	visited[wejscie[i+2]] = false;
	//}
	/*for (const auto& outerPair : miasta_i_odleglosci) {
		std::cout << outerPair.first << ": { ";
		for (const auto& innerPair : outerPair.second) {
			std::cout << innerPair.first << "=" << innerPair.second << ", ";
		}
		std::cout << " }" << std::endl;
	}
	std::cout << "miasta: ";
	for (auto const& c : visited)
	{
		std::cout << c.first << ", ";
	}*/
	//Inicjacja zmiennej wynikowej przechowujacej najkrotsza dotychczas znaleziona trase
	podroz final_result;
	final_result.dystans=INT_MAX;
	for (auto const & c: miasta_i_odleglosci)
	{
		//Zaznaczenie wszystkich miast jako nieodwiedzone
		for (auto const & d : visited)
		{
			visited[d.first] = false;
		}
		//Miasto startowe jako odwiedzone
		visited[c.first] = true;
		std::vector<std::string>kolejnosc;
		bool powrot = false;
		podroz info = szukaj_trasy(c.first, visited, 0, kolejnosc, final_result, miasta_i_odleglosci, c.first, powrot);
	}
	//Zapisanie wyniku do pliku wyjsciowego
	if (final_result.dystans != INT_MAX)
	{
		zapisz_do_pliku(ww.wyjsciowy, final_result);
	}
	//Dla sytuacji w ktorych NIE DA SIE rozwiazac zadania korzystajac z podanej tresci
	else
	{
		std::cout << "Nie mozna znalezc optymalnej trasy dla podanych polaczen, upewnij sie czy dane wejsciowe sa poprawne." << std::endl;
	}
	/*std::cout << std::endl << "Koszt podrozy: " << final_result.dystans << std::endl;
	std::cout << "Kolejnosc odwiedzanych miast: ";
	for (auto const & c : final_result.sciezka)
	{
		std::cout << c << ", ";
	}
	std::cout << std::endl;*/

	return 0;
}


