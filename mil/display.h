#ifndef __DISPLAY_H__MIL
#define __DISPLAY_H__MIL
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

#include "mil.h"

namespace Mil
{
	namespace UI
	{
		template <class I>
		class Display
		{
		protected:
			Display(I image) {}
		public:
			static Display<I> get_display();
		};
	}
}

#endif //__DISPLAY_H__MIL