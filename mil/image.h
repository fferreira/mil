#ifndef __IMAGE_H__MIL
#define __IMAGE_H__MIL
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

#include <istream>
#include <string>

namespace Mil {

	struct Size
	{
		int x, y;
		
		Size():x(0), y(0) {}
		Size(unsigned int x, unsigned int y):x(x), y(y) {}
		void set(unsigned int x, unsigned int y) { this->x = x; this->y = y; }
	};
	
	template<class P>
	class Image
	{
	private:
		Size size;
		P* buffer;

		void allocate_buffer(Size size)
		{
			buffer = new P[size.x*size.y];
			this->size = size;
		}
		void copy(const Image& img)
		{
			clear();
			allocate_buffer(img.size);
			this->size = img.size;
			
			memcpy(this->buffer, img.buffer, (size.x * size.y) * sizeof(P));
		}
	protected:
	public:
		typedef P PixelType;
		explicit Image(Size size) { allocate_buffer(size); this->size = size;}
		Image() {}

		Image(const Image& img)
		{
			copy(img);
		}

		template<class P2>
		Image(const Image<P2> &img)
		{
			allocate_buffer(img.get_size());
			for(int x = 0; x < img.get_size().x; x++)
			{
				for(int y = 0; y < img.get_size().y; y++)
				{
					this->set(x, y, img.get(x, y));
				}
			}

		}
		const Image& operator= (const Image& img)
		{
			copy(img);
			return img;
		}

		~Image() { clear();}

		Size get_size() const { return size; }
		void set_size(Size size)
		{
			if ((this->size.x == 0) && (this->size.y == 0))
			{
				this->size = size;
				allocate_buffer(size);
			} else {
				throw std::exception("Unable to set the size of an image with contents");
			}
		}

		void clear()
		{
			if (size.x != 0 && size.y != 0)
			{
				size.x = size.y = 0;
				delete[] buffer;
			}
		}

		inline const P& get(unsigned int x, unsigned int y) const
		{
			return buffer[x +(y * size.x)];
		}

		inline void set(unsigned int x, unsigned int y, const P& p)
		{
			buffer[x +(y * size.x)] = p;
		}
	};
}

#endif //__IMAGE_H__MIL