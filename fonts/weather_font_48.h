/*******************************************************************************
 * Size: 48 px
 * Bpp: 1
 * Opts: --bpp 1 --size 48 --no-compress --font artillweathericons.ttf --symbols 90EM --format lvgl -o weather_font_48.c
 ******************************************************************************/

#ifndef WEATHER_FONT_48
#define WEATHER_FONT_48 1
#endif

#if WEATHER_FONT_48

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap_wf_48[] = {
    /* U+0030 "0" */
    0x0, 0xc, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0,
    0xc0, 0x0, 0x0, 0x30, 0x0, 0x18, 0xc, 0x3,
    0x7, 0x0, 0x1, 0xc0, 0xe0, 0x0, 0xe0, 0x38,
    0x30, 0x30, 0x0, 0x7f, 0x80, 0x0, 0x3f, 0xf0,
    0x0, 0x1e, 0x1e, 0x0, 0x7, 0x3, 0x80, 0x3,
    0x80, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0,

    /* U+0039 "9" */
    0x0, 0x6, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0,
    0x1, 0x80, 0x0, 0x0, 0xc, 0x0, 0x0, 0xc0,
    0x60, 0x18, 0x7, 0x0, 0x1, 0xc0, 0x1c, 0x0,
    0x1c, 0x0, 0x60, 0x0, 0xc0, 0x0, 0x1f, 0xc0,
    0x0, 0x3, 0xff, 0x0, 0x0, 0x3c, 0x3c, 0x0,
    0x1, 0x80, 0x70, 0x0, 0x1c, 0x3, 0x80, 0x0,
    0xc0, 0xc, 0x3, 0xe6, 0x0, 0x63, 0xff, 0x30,
    0x3, 0x1f, 0x1, 0x80, 0x18, 0x0, 0x6, 0x1,
    0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x7, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xf8,

    /* U+0045 "E" */
    0x0, 0x0, 0x7c, 0x0, 0x0, 0x0, 0x7f, 0xc0,
    0x0, 0x0, 0x38, 0x38, 0x0, 0x0, 0x1c, 0x7,
    0x0, 0x0, 0xe, 0x0, 0xe0, 0x0, 0x3, 0x0,
    0x18, 0x0, 0x0, 0xc0, 0x7, 0xc0, 0x0, 0xf0,
    0x1, 0xfc, 0x0, 0xf8, 0x78, 0x3, 0x80, 0x38,
    0x3f, 0x0, 0x60, 0x1c, 0xf, 0xe0, 0xc, 0x6,
    0x1, 0x38, 0x3, 0x0, 0x0, 0xe, 0x0, 0xdf,
    0xff, 0xff, 0x0, 0x37, 0xff, 0xff, 0x80, 0xc,
    0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x3,
    0x9f, 0xff, 0xf, 0xff, 0xc7, 0xff, 0xe3, 0xff,
    0xc1, 0xff, 0xfc, 0x0, 0x0, 0x0, 0x7, 0x0,
    0x0, 0x0, 0x9, 0xc0, 0x0, 0x0, 0x7, 0xf0,
    0x0, 0x0, 0x0, 0xf8, 0x0, 0x0, 0x0, 0x8,
    0x0, 0x0, 0x0,

    /* U+004D "M" */
    0x0, 0x3f, 0x0, 0x0, 0xf, 0xfc, 0x0, 0x1,
    0xe1, 0xe0, 0x0, 0x38, 0x7, 0x0, 0x3, 0x0,
    0x38, 0x0, 0x70, 0x3, 0x80, 0xe, 0x0, 0x1f,
    0x3, 0xe0, 0x1, 0xfc, 0x78, 0x0, 0x0, 0xe6,
    0x0, 0x0, 0x6, 0xe0, 0x0, 0x0, 0x7c, 0x0,
    0x0, 0x3, 0xc0, 0x0, 0x0, 0x3c, 0x2, 0x1,
    0x3, 0xc0, 0x30, 0x18, 0x36, 0x7, 0x3, 0x86,
    0x70, 0x30, 0x38, 0xe3, 0xc0, 0x0, 0x3c, 0xc,
    0x6, 0x3, 0x0, 0x0, 0x60, 0x0, 0x0, 0xc6,
    0x60, 0x0, 0xc, 0x6, 0x0, 0x0, 0xc0, 0x60,
    0x0, 0x8, 0x4, 0x0, 0x0, 0x8, 0x0, 0x0,
    0x1, 0xc0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x1,
    0x80, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc_wf_48[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 491, .box_w = 26, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 56, .adv_w = 535, .box_w = 29, .box_h = 22, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 136, .adv_w = 690, .box_w = 34, .box_h = 25, .ofs_x = 5, .ofs_y = -5},
    {.bitmap_index = 243, .adv_w = 520, .box_w = 28, .box_h = 28, .ofs_x = 2, .ofs_y = -8}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0_wf_48[] = {
    0x0, 0x9, 0x15, 0x1d
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps_wf_48[] =
{
    {
        .range_start = 48, .range_length = 30, .glyph_id_start = 1,
        .unicode_list = unicode_list_0_wf_48, .glyph_id_ofs_list = NULL, .list_length = 4, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache_wf_48;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc_wf_48 = {
#else
static lv_font_fmt_txt_dsc_t font_dsc_wf_48 = {
#endif
    .glyph_bitmap = glyph_bitmap_wf_48,
    .glyph_dsc = glyph_dsc_wf_48,
    .cmaps = cmaps_wf_48,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache_wf_48
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t weather_font_48 = {
#else
lv_font_t weather_font_48 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 31,          /*The maximum line height required by the font*/
    .base_line = 8,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -6,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc_wf_48,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if WEATHER_FONT_48*/
