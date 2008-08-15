#ifndef __PIPELINE_H__MIL
#define __PIPELINE_H__MIL
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
	/*
	There is an specific type to do the pixel calculations
	The type of the calculations depends on the type of the channel of the image
	*/

namespace Mil
{
	template <class P>
	struct PipelineTraits
	{
		typedef typename P Type;
	};
	
	template <>
	struct PipelineTraits<unsigned char>
	{
		typedef int Type;
	};

	template <>
	struct PipelineTraits<char>
	{
		typedef int Type;
	};

	template <>
	struct PipelineTraits<unsigned int>
	{
		typedef int Type;
	};
}
#endif //__PIPELINE_H__MIL