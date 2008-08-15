#ifndef __MANIPULATION_H__MIL
#define __MANIPULATION_H__MIL
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
#include <algorithm>

namespace Mil
{
	template <class I>
	class PixelTransform
	{
	protected:
		I &image;
		typedef typename I::PixelType PixelType;
		typedef typename I::PixelType::PipelineType PipelineType;

	private:
		virtual PixelType transform (Pixel<PipelineType> p, int x, int y) =0;
		virtual void before_apply() {}
		virtual void after_apply() {}

	public:
		PixelTransform(I &img):image(img) {}
		
		void set_image(I &image)
		{
			this->image = image;
		}

		void apply()
		{
			before_apply();
			for(int x=0; x < image.get_size().x; x++)
			{
				for(int y=0; y < image.get_size().y; y++)
				{
					image.set(x, y, transform(image.get(x,y), x, y));
				}
			}
			after_apply();
		}

	};

	template <class I>
	class BrightnessAndContrast : public PixelTransform<I>
	{
		PipelineType bright;
		float contrast;
	public:
		BrightnessAndContrast<I>(I &img, PipelineType bright, float contrast) : PixelTransform<I>(img), bright(bright), contrast(contrast)
		{
		}
	private:

		virtual PixelType transform (Pixel<PipelineType> p, int x, int y)
		{
			return  p * contrast + bright;;
		}
	};

	template <class I>
	class MinMax : public PixelTransform<I>
	{
		typedef typename PixelType::ChannelType ChannelType;
		ChannelType min_val, max_val;

		ChannelType min(ChannelType x, ChannelType y, ChannelType z)
		{
			return std::min(std::min(x, y), z);
		}

		ChannelType max(ChannelType x, ChannelType y, ChannelType z)
		{
			return std::max(std::max(x, y), z);
		}

	public:
		MinMax<I>(I &img) : PixelTransform<I>(img), max_val(PixelType::min()), min_val(PixelType::max()) {}
		ChannelType get_min() { return min_val; }
		ChannelType get_max() { return max_val; }

	private:
		virtual PixelType transform (Pixel<PipelineType> p, int x, int y)
		{
			if (max_val < max(p.red, p.green, p.blue))
				max_val = max(p.red, p.green, p.blue);
			if (min_val > min(p.red, p.green, p.blue))
				min_val = min(p.red, p.green, p.blue);
			return p;
		}
	};
}

#endif //__MANIPULATION_H__MIL