#pragma once
#ifndef file_read_h
#define file_read_h
#include <string>
#include <vector>

#include "struktury.h"

/** Funkcja odczytuje dane z pliku usuwajac: znaki nawiasu, spacje, znaki nowej linii.
 * @param nazwa_pliku - nazwa pliku z którego odczytujemy dane
 * @return Funkcja zwraca sformatowane dane w postaci vectora stringów, w którym ka¿dy string moze byc liczba lub symbolem (myslnik, strzalka, dwukropek lub przecinek)
 */
std::vector<std::string>optymalizacja_pliku(const std::string& nazwa_pliku);
/**
 * Funkcja sprawdzajaca czy dany string to liczba.
 * @param string - sprawdzany string
 * @return Funkcja zwraca informacje true- jesli dany string to liczba, lub false- jesli dany string nie jest liczba.
 */
bool czy_liczba(const std::string& string);
/**
 * Funkcja wypisuj¹ca instrukcje o tym, jak powinien byc sformatowany plik z danymi wejsciowymi w przypadku, gdy program napotka blad podczas zczytywania danych.
 * @return Funkcja nic nie zwraca.
 */
void wypisz_intrukcje();
/**
 * Funkcja wprowadza informacje o mozliwych polaczeniach do mapy w formacie std::map<miasto1,<miasto2, odleglosc>>.
 * @param wejscie - vector ze znakami zwrocony z funkcji "optymalizacja_pliku"
 * @param miasta_i_odleglosci - mapa w ktorej beda zapisywane dane
 * @param visited - mapa w formacie std::map<miasto, informacja_czy_zostalo_odwiedzone> przechowujaca informacje o odwiedzonych miastach (potrzebna do funkcji rekurencyjnej "szukaj_trasy")
 * @return Funkcja zwraca sformatowana mape.
 */
void wprowadz_do_mapy(const std::vector<std::string>wejscie, std::map<std::string, std::map<std::string, double>>& miasta_i_odleglosci, std::map<std::string, bool>& visited, bool& powodzenie_wczytywania);
/**
 * Funkcja, która zapisuje znaleziona odpowiedz (najkrotsza mozliwa trase i kolejnosc odwiedzanych miast) do pliku tekstowego.
 * @param nazwa_pliku - nazwa pliku do ktorego chcemy zapisac odpowiedz
 * @param wynik - struktura przechowujaca odpowiedzi do zadania, ktore zostana wypisane do pliku
 * @return Funkcja nic nie zwraca.
 */
void zapisz_do_pliku(const std::string& nazwa_pliku, const podroz& wynik);

#endif



