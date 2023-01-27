/** @file */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#include "tsp_algorithm.h"
#include "struktury.h"


podroz szukaj_trasy(const std::string miasto_startowe, std::map<std::string, bool>& czy_odwiedzone, double cost, std::vector<std::string>&kolejnosc,	podroz&wynik, const std::map<std::string, std::map<std::string, double>>& miasta_i_odleglosci, const std::string& miasto_startowe_const, bool& znaleziono_powrot)
{
	podroz info;
	info.dystans = cost;
	info.sciezka = kolejnosc;
	info.sciezka.push_back(miasto_startowe);

	if (info.sciezka.size() == czy_odwiedzone.size())
	{
		for (const auto& zewnetrzna : miasta_i_odleglosci)
		{
			for (const auto& wewnetrzna : zewnetrzna.second)
			{
				if (zewnetrzna.first == miasto_startowe && wewnetrzna.first==miasto_startowe_const)
				{
					info.dystans += wewnetrzna.second;
					info.sciezka.push_back(miasto_startowe_const);
					znaleziono_powrot = true;
				}
			}		
		}
		return info;
	}
	else if (cost < wynik.dystans)
	{
		for (const auto& zewnetrzna : miasta_i_odleglosci) {
			if (zewnetrzna.first == miasto_startowe)
			{
				for (const auto& wewnetrzna : zewnetrzna.second)
				{
					if (czy_odwiedzone[wewnetrzna.first] == false)
					{
						czy_odwiedzone[wewnetrzna.first] = true;
						podroz temp = szukaj_trasy(wewnetrzna.first, czy_odwiedzone, cost + wewnetrzna.second, info.sciezka, wynik, miasta_i_odleglosci, miasto_startowe_const, znaleziono_powrot);
						if (temp.dystans < wynik.dystans && temp.sciezka.size() == czy_odwiedzone.size()+1 && znaleziono_powrot == true)
						{
							info = temp;
							wynik.sciezka = temp.sciezka;
							wynik.dystans = temp.dystans;
							znaleziono_powrot = false;
						}
						czy_odwiedzone[wewnetrzna.first] = false;
					}
				}
				break;
			}
		}
	}
	return info;	
}






