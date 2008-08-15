#ifndef __PIXEL_H__MIL
#define __PIXEL_H__MIL
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

#include "pipeline.h"
#include <limits>

namespace Mil
{
	template <class T>
	struct BoundedArithmetic
	{
		inline T sum (T a, T b) const
		{
			T sum = a + b;
			if ((b > 0) && (a > sum))
				return std::numeric_limits<T>::max();
			else if ((b < 0) && (a < sum))
				return std::numeric_limits<T>::min();
			else
				return sum;
		}

		inline T sub (T a, T b) const
		{
			T sub = a - b;
			if ((b > 0) && (a < sub))
				return std::numeric_limits<T>::min(); 
			else if ((b < 0) && (a > sub))
				return std::numeric_limits<T>::max();
			else
				return sub;
		}

		inline T prod(T a, float b) const
		{
			float prod = a * b;
			if (prod > std::numeric_limits<T>::max())
				return std::numeric_limits<T>::max();
			else if (prod < std::numeric_limits<T>::min())
				return std::numeric_limits<T>::min();
			else
				return (T) prod;
		}
		
		inline T div(T a, float b) const
		{
			float div = a / b;
			if (div > std::numeric_limits<T>::max())
				return std::numeric_limits<T>::max();
			else if (div < std::numeric_limits<T>::min())
				return std::numeric_limits<T>::min();
			else
				return (T) div;
		}
	};

	template <class T>
	struct UnBoundedArithmetic
	{
		inline T sum (T a, T b) const
		{
			return a + b;
		}

		inline T sub (T a, T b) const
		{
			return a - b;
		}

		inline T prod(T a, float b) const
		{
			return a * b;
		}
		
		inline T div(T a, float b) const
		{
			return a / b;
		}
	};

	template <class T, class A = UnBoundedArithmetic<T> >
	struct Pixel : private A
	{
		typedef T ChannelType;
		static T max() { return std::numeric_limits<T>::max();} //TODO consider the use of PixelTraits
		static T min() { return std::numeric_limits<T>::min();}


		//typedef typename Generic::Unsigned<T>::Type AdditionType;
		typedef typename  PipelineTraits<T>::Type PipelineType;
		T red;
		T green;
		T blue;

		template<class T2>
		Pixel(const Pixel<T2> pix)
		{
			red = assign(pix.red);
			green = assign(pix.green);
			blue = assign(pix.blue);
		}

		Pixel():red(0), green(0), blue(0) {}

		template <class T2>
		Pixel &operator=(const Pixel<T2> pix)
		{
			red = assign(pix.red);
			green = assign(pix.green);
			blue = assign(pix.blue);
			return *this;
		}

		//Here are the (x)= operators
		Pixel &operator+=(Pixel &a)
		{
			red = sum(red , a.red);
			green = sum(green, a.green);
			blue = sum(blue, a.blue);
			return *this;
		}
		
		Pixel& operator+=(const T &c)
		{
			red = sum(red, c); 
			green = sum(green, c);
			blue = sum(blue, c);
			return *this;
		}

		Pixel& operator-=(const T &c)
		{
			red = sub(red, c); 
			green = sub(green, c);
			blue = sub(blue, c);
			return *this;
		}

		Pixel& operator*=(float c)
		{
			red   = prod(red, c); 
			green = prod(green, c);
			blue  = prod(blue, c);
			return *this;
		}

		Pixel& operator/=(float c)
		{
			red   = div(red, c); 
			green = div(green, c);
			blue  = div(blue, c);
			return *this;
		}

	private:
		template <class T2>
		T assign(T2 a)
		{
			if (a > std::numeric_limits<T>::max())
				return std::numeric_limits<T>::max();
			else if (a < std::numeric_limits<T>::min())
				return std::numeric_limits<T>::min();
			else
				return (T)a;
		}
	};

	template<class T>
	Pixel<T> operator+(Pixel<T> a, Pixel<T> b)
	{
		Pixel<T> temp(a);
		temp+= b;
		return temp;
	}

	template<class T, typename N>
	Pixel<T> operator+(Pixel<T> a, N b)
	{
		Pixel<T> temp(a);
		temp += (T)b;
		return temp;
	}

	template<class T, typename N>
	Pixel<T> operator+(N b, Pixel<T> a)
	{
		return (a + b);
	}

	template<class T>
	Pixel<T> operator-(Pixel<T> a, Pixel<T> b)
	{
		Pixel<T> temp(a);
		temp-= b;
		return temp;
	}

	template<class T, typename N>
	Pixel<T> operator-(Pixel<T> a, N b)
	{
		Pixel<T> temp(a);
		temp -= b;
		return temp;
	}

	template<class T, typename N>
	Pixel<T> operator-(N b, Pixel<T> a)
	{
		return (a - b);
	}

	template<class T>
	Pixel<T> operator*(Pixel<T> a, float b)
	{
		Pixel<T> temp(a);
		temp *= b;
		return temp;
	}

	template<class T>
	Pixel<T> operator*(float b, Pixel<T> a)
	{
		return (a * b);
	}

	/*template<class P1, class P2>
	Pixel<P1>& operator=(Pixel<P1> &p1, const Pixel<P2> &p2)
	{
		return p1;
	}*/
}
#endif //__PIXEL_H__MIL