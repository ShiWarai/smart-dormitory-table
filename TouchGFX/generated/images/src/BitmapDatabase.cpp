// 4.19.1 0xf40d7ac0
// Generated by imageconverter. Please, do not edit!

#include <BitmapDatabase.hpp>
#include <touchgfx/Bitmap.hpp>

extern const unsigned char image_blue_backgrounds_main_bg_480x272px[]; // BITMAP_BLUE_BACKGROUNDS_MAIN_BG_480X272PX_ID = 0, Size: 480x272 pixels
extern const unsigned char image_blue_backgrounds_main_bg_texture_480x272px[]; // BITMAP_BLUE_BACKGROUNDS_MAIN_BG_TEXTURE_480X272PX_ID = 1, Size: 480x272 pixels
extern const unsigned char image_blue_progressindicators_bg_medium_progress_indicator_bg_square_0_degrees[]; // BITMAP_BLUE_PROGRESSINDICATORS_BG_MEDIUM_PROGRESS_INDICATOR_BG_SQUARE_0_DEGREES_ID = 2, Size: 184x20 pixels
extern const unsigned char image_images[]; // BITMAP_IMAGES_ID = 3, Size: 559x255 pixels

const touchgfx::Bitmap::BitmapData bitmap_database[] = {
    { image_blue_backgrounds_main_bg_480x272px, 0, 480, 272, 0, 0, 480, ((uint8_t)touchgfx::Bitmap::RGB565) >> 3, 272, ((uint8_t)touchgfx::Bitmap::RGB565) & 0x7 },
    { image_blue_backgrounds_main_bg_texture_480x272px, 0, 480, 272, 0, 0, 480, ((uint8_t)touchgfx::Bitmap::RGB565) >> 3, 272, ((uint8_t)touchgfx::Bitmap::RGB565) & 0x7 },
    { image_blue_progressindicators_bg_medium_progress_indicator_bg_square_0_degrees, 0, 184, 20, 0, 0, 184, ((uint8_t)touchgfx::Bitmap::RGB565) >> 3, 20, ((uint8_t)touchgfx::Bitmap::RGB565) & 0x7 },
    { image_images, 0, 559, 255, 446, 105, 22, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 45, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 }
};

namespace BitmapDatabase
{
const touchgfx::Bitmap::BitmapData* getInstance()
{
    return bitmap_database;
}

uint16_t getInstanceSize()
{
    return (uint16_t)(sizeof(bitmap_database) / sizeof(touchgfx::Bitmap::BitmapData));
}
} // namespace BitmapDatabase
