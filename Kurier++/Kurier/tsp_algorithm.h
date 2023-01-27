/** @file */

#ifndef tsp_algorithm_h
#define tsp_algorithm_h
#include <string>
#include <vector>

#include "struktury.h"

/**
 * Funkcja rekurencyjna, która znajduje najkrótsze po³¹czenie pomiêdzy miastem startowym a wszystkimi pozostalymi.
 * @param miasto_startowe - punkt od ktorego zaczynamy
 * @param czy_odwiedzone - mapa ktora odznacza czy konkretne miasto zostalo juz odwiedzone
 * @param cost - zmienna przechowujaca aktualny dystans
 * @param kolejnosc - zmienna przechowujaca kolejnosc odwiedzanych miast
 * @param wynik - struktura przechowujaca odleglosc i kolejnosc odwiedzanych miast dla najkrotszej z kombinacji
 * @param miasta_i_odleglosci - mapa przechowujaca miasta i ich mozliwe polaczenia wraz z odleglosciami
 * @param miasto_startowe_const - miasto od którego kurier zaczyna CALA podroz
 * @param znaleziono_powrot - zmienna przechowujaca informacje czy znaleziona podroz jest kompletna czy nie (czy jest mozliwosc powrotu do miasta poczatkowego)
 * @return Funkcja zwraca najkrotsza mozliwa trase wraz z kolejnoscia odwiedzanych miast w strukturze "wynik".
 */
podroz szukaj_trasy(const std::string miasto_startowe, std::map<std::string, bool>& czy_odwiedzone, double cost, std::vector<std::string>& kolejnosc, podroz& wynik, const std::map<std::string, std::map<std::string, double>>& miasta_i_odleglosci, const std::string& miasto_startowe_const, bool& znaleziono_powrot);

#endif



