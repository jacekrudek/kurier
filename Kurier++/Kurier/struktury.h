/** @file */

#ifndef STRUKTURY_H  
#define STRUKTURY_H

#include <vector> 
#include <string>

/**
 * Struktura przechowujaca informacje o podrozy.
 * @param dystans - przebyta odleglosc
 * @param sciezka - kolejnosc odwiedzanych miast
 */
struct podroz
{
	double dystans;				
	std::vector<std::string> sciezka;  
};
/**
 * Struktura przechowujaca dane plikow: wejsciowego i wyjsciowego.
 * @param wejsciowy - nazwa pliku z danymi wejsciowymi
 * @param wyjsciowy - nazwa pliku z danymi wyjsciowymi
 */
struct plik
{
	std::string wejsciowy, wyjsciowy;
};

#endif
