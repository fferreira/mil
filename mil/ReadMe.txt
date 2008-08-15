 Current Features
 
 - Small and Simple Generic Image library
 - Static polymorphism to avoid performance penalties
 - Simple pixel format support (Pixel support will need some rethinking)
 - Pixel arithmetic can be customized for particular formtas (with static polymorphism)
 - Simple (and yet very incomplete) and generic image manipulation support
 - IO functionality provided by FreeImage library (a lot of supported formats)
 - GPL v3 license
 
 Next To Dos
 
 - Add multiformat saving to Mil::IO:Save class 
 - Add scaling functionality 
 - Add croping functionality 
 - Add normalization for conversions and display 
 - Create a class to display images 
 - Create some sample programs
 
 Future
 
 - Add some paralelization
 
 Image manipulation support:
	- Add convolution based transforms
	- Add histogram manipulation
 
 - Add plugable image buffers with static polymorfism
 - Add to IO:Save and IO:Load support for FreeImage/other lib buffers
 
 Lower Priority 
 - Support Boost lambda library