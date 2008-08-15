/*    
    This file is part of Mil Image Library.
	Copyright 2008, Francisco Ferreira
	http://www.fferreira.com.ar/contact

    Mil Image Library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Mil Image Library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

// main.cpp : Defines the entry point for the console application.
//
#include <iostream>

#include "mil.h"
#include "manipulation.h"
#include "io.h"
#include "display.h"

typedef Mil::Image<Mil::Pixel<float> > CurrentImage;
typedef Mil::Image<Mil::Pixel<unsigned char> > CurrentImageSave;


int main(int argc, char* argv[])
{
	try
	{
		CurrentImage img;
		Mil::IO::Load<CurrentImage> loader(img, "small.png");

		loader.apply();

		std::cout << "Image Loaded!" << std::endl;

		Mil::MinMax<CurrentImage> filterMM(img);
		filterMM.apply();

		std::cout << "Min: " << (int)filterMM.get_min() << std::endl;
		std::cout << "Max: " << (int)filterMM.get_max() << std::endl;

		Mil::BrightnessAndContrast<CurrentImage> filterBC(img, -50, 1.5f);
		filterBC.apply();

		filterMM.apply();

		std::cout << "Min: " << (int)filterMM.get_min() << std::endl;
		std::cout << "Max: " << (int)filterMM.get_max() << std::endl;

		std::cout << "Processing done!" << std::endl;

		Mil::IO::Save<CurrentImage> save(img, "bright.png");
		save.apply();		

		std::cout << "Image Saved!" << std::endl;
	} catch (std::exception e)
	{
		std::cerr << "An error ocured" << std::endl;
		std::cerr << e.what();
		char ch;
		std::cin >> ch;
	} catch (...)
	{
		std::cerr << "An unidentified error ocured" << std::endl;
		char ch;
		std::cin >> ch;
	}

	
	return 0;
}


