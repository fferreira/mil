#ifndef __IO_H__MIL
#define __IO_H__MIL

#include "mil.h"
#include "manipulation.h"
#include <string>

#include "FreeImage.h"
FIBITMAP* GenericLoader(const char* lpszPathName, int flag=0);

namespace Mil
{
	namespace IO
	{
		template <class I>
		class Load : public PixelTransform<I>
		{
			std::string file_name;
			FIBITMAP *fib;

			virtual void before_apply()
			{
				fib = GenericLoader(file_name.c_str());
				if (fib==0)
					throw std::exception("Unable to open file");

				Size img_size;
				img_size.set(FreeImage_GetWidth(fib), FreeImage_GetHeight(fib));

				image.clear();
				image.set_size(img_size);
			}

			virtual void after_apply()
			{
				FreeImage_Unload(fib);
				fib = 0;
			}

			virtual PixelType transform (Pixel<PipelineType> p, int x, int y)
			{
				Pixel<unsigned char> pix;
				RGBQUAD rgb;

				FreeImage_GetPixelColor(fib, x, y, &rgb);
				pix.red = rgb.rgbRed;
				pix.green = rgb.rgbGreen;
				pix.blue = rgb.rgbBlue;

				return pix;
			}

		public:
			explicit Load(I &img, std::string file_name) : PixelTransform<I>(img), file_name(file_name) {}
		};

		template <class I>
		class Save : public PixelTransform<I>
		{
			std::string file_name;
			FIBITMAP *fib;

			virtual void before_apply()
			{
				const int bpp_png=24;
				Size size = image.get_size();
				fib = FreeImage_Allocate(size.x, size.y, bpp_png);

				if (fib == NULL)
					throw std::exception("Unable to allocate save buffer");
			}

			virtual PixelType transform (Pixel<PipelineType> p, int x, int y)
			{
				RGBQUAD fibpix;
				Pixel<unsigned char> pix(p);

				fibpix.rgbRed = pix.red;
				fibpix.rgbGreen = pix.green;
				fibpix.rgbBlue = pix.blue;

				FreeImage_SetPixelColor(fib, x, y, &fibpix);
				return p;
			}

			virtual void after_apply()
			{
				FreeImage_Save(FIF_PNG, fib, file_name.c_str());
				FreeImage_Unload(fib);
				fib = 0;
			}
		public:
			explicit Save(I &img, std::string file_name) : PixelTransform<I>(img), file_name(file_name) {}
		};
	}
}

#endif