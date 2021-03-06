// Kostki.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
/// 
/// Liczba kostek w zadaniu
///
const uint32_t amountOfCubes = 600;
///
/// Przechowuje informację na temat tego ile kostek jest o danej wartości, i tak
/// Cubes...Array[0] - ilość kostek o wartości "1",
/// Cubes...Array[1] - ilość kostek o wartości "2",
/// ...
/// Cubes...Array[5] - ilość kostek o wartości "6",
///
uint16_t CubesValuesInArray[6];
///
/// klasa reprezentujaca pojdynczą kostkę
///
class Cube
{
public:
	Cube() { value = 6; }
	uint8_t value;
	/// 
	/// Oblicza ilośc kostek o danej wartości. Rezultat zapisany jest w CubesValuesInArray
	///
	static void GetValuesAmount(Cube* cubeArray, uint32_t size = amountOfCubes)
	{
		memset(CubesValuesInArray, 0, sizeof(CubesValuesInArray));
		for (uint32_t i = size; i > 0; i--)
		{
			CubesValuesInArray[cubeArray->value - 1]++;
			cubeArray++;
		}
	}
	static double CalcAnEntrophy(uint16_t *AmountOfCubesValues)
	{
		int sum = 0;
		for (int i = 0; i<6; i++)sum += AmountOfCubesValues[i];
		double ans = 0.5*log(2 * sum* 3.14) + sum*log(sum) - sum;
		for (int i = 0; i<6; i++)
		{
			if (0 == AmountOfCubesValues[i])continue;
			ans -= (0.5*log(2 * AmountOfCubesValues[i] * 3.14) + AmountOfCubesValues[i] * log(AmountOfCubesValues[i]) - AmountOfCubesValues[i]);
		}
		return ans;
	}
};
///
/// tablica kostek
///
Cube cubesArray[amountOfCubes];
///
/// Ilość kostek biorących udział w każdym z losowań
///
const uint32_t maxCubesInOneShot = 20;
///
/// Ilość losowań
///
const uint32_t RandomShots = 100;
///
/// Czas oczekiwania na kolejne losowanie w milisekundach.
///
const uint32_t delayTimeMS = 500;
int main()
{
	srand(NULL);
	// Ponizsze powatarzam RandomShots razy.
	for (uint32_t i = RandomShots; i > 0; i--)
	{
		// 1. Losuję maxCUbesInOneShot z tablicy cubesArray,
		for (uint32_t k = maxCubesInOneShot; k > 0; k--)
		{
			// Zakładam, że rand() zwróci mi wartość z zakresu większego niz 0...600
			cubesArray[rand() % amountOfCubes].value = ((rand() % 6)+1);
		}
		// 2. Obliczam ile jest kostek ma wartość 1, 2, 3, 4, 5 i 6.
		Cube::GetValuesAmount(cubesArray);
		// 3. Obliczam entropię układu
		printf("Losowanie %3d: %3d %3d %3d %3d %3d %3d. Entropia: %f\r\n", i, CubesValuesInArray[0], CubesValuesInArray[1], 
													   CubesValuesInArray[2], CubesValuesInArray[3], 
													CubesValuesInArray[4], CubesValuesInArray[5],
													Cube::CalcAnEntrophy(CubesValuesInArray));
		
		// 2. Odczekuje chwilę, jesli zadano
		std::this_thread::sleep_for(std::chrono::milliseconds(delayTimeMS));
	}
	getchar();
    return 0;
}

