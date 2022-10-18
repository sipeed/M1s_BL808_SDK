#ifndef __MM_COMMON_H__
#define __MM_COMMON_H__

typedef enum {
	PIX_FMT_YUV420P,   /**< planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples) */
	PIX_FMT_YUYV422,   /**< packed YUV 4:2:2, 16bpp, Y0 Cb Y1 Cr */
	PIX_FMT_UYVY422,   /**< packed YUV 4:2:2, 16bpp, Cb Y0 Cr Y1 */
	PIX_FMT_YUV422P,   /**< planar YUV 4:2:2, 16bpp, (1 Cr & Cb sample per 2x1 Y samples) */
	PIX_FMT_YUV444P,   /**< planar YUV 4:4:4, 24bpp, (1 Cr & Cb sample per 1x1 Y samples) */
	PIX_FMT_GRAY8,     /**<	   Y	    ,  8bpp */
	PIX_FMT_MONOWHITE, /**<	   Y	    ,  1bpp, 0 is white, 1 is black, in each byte pixels are ordered from the msb to the lsb */
	PIX_FMT_MONOBLACK, /**<	   Y	    ,  1bpp, 0 is black, 1 is white, in each byte pixels are ordered from the msb to the lsb */

	PIX_FMT_NV12,      /**< planar YUV 4:2:0, 12bpp, 1 plane for Y and 1 plane for the UV components, which are interleaved (first byte U and the following byte V) */
	PIX_FMT_NV21,      /**< as above, but U and V bytes are swapped */

	PIX_FMT_RGB24,     /**< packed RGB 8:8:8, 24bpp, RGBRGB... */
	PIX_FMT_BGR24,     /**< packed RGB 8:8:8, 24bpp, BGRBGR... */

	PIX_FMT_ARGB,      /**< packed ARGB 8:8:8:8, 32bpp, ARGBARGB... */
	PIX_FMT_RGBA,	   /**< packed RGBA 8:8:8:8, 32bpp, RGBARGBA... */
	PIX_FMT_ABGR,	   /**< packed ABGR 8:8:8:8, 32bpp, ABGRABGR... */
	PIX_FMT_BGRA,	   /**< packed BGRA 8:8:8:8, 32bpp, BGRABGRA... */

	PIX_FMT_RGB565BE,  /**< packed RGB 5:6:5, 16bpp, (msb)	  5R 6G 5B(lsb), big-endian */
	PIX_FMT_RGB565LE,  /**< packed RGB 5:6:5, 16bpp, (msb)	  5R 6G 5B(lsb), little-endian */
	PIX_FMT_RGB555BE,  /**< packed RGB 5:5:5, 16bpp, (msb)1A 5R 5G 5B(lsb), big-endian, most significant bit to 0 */
	PIX_FMT_RGB555LE,  /**< packed RGB 5:5:5, 16bpp, (msb)1A 5R 5G 5B(lsb), little-endian, most significant bit to 0 */

	PIX_FMT_BGR565BE,  /**< packed BGR 5:6:5, 16bpp, (msb)	 5B 6G 5R(lsb), big-endian */
	PIX_FMT_BGR565LE,  /**< packed BGR 5:6:5, 16bpp, (msb)	 5B 6G 5R(lsb), little-endian */
	PIX_FMT_BGR555BE,  /**< packed BGR 5:5:5, 16bpp, (msb)1A 5B 5G 5R(lsb), big-endian, most significant bit to 1 */
	PIX_FMT_BGR555LE,  /**< packed BGR 5:5:5, 16bpp, (msb)1A 5B 5G 5R(lsb), little-endian, most significant bit to 1 */

	PIX_FMT_0RGB,      /**< packed RGB 8:8:8, 32bpp, 0RGB0RGB... */
	PIX_FMT_RGB0,	   /**< packed RGB 8:8:8, 32bpp, RGB0RGB0... */
	PIX_FMT_0BGR,	   /**< packed BGR 8:8:8, 32bpp, 0BGR0BGR... */
	PIX_FMT_BGR0,	   /**< packed BGR 8:8:8, 32bpp, BGR0BGR0... */

	PIX_FMT_BAYER_BGGR8,    /**< bayer, BGBG..(odd line), GRGR..(even line), 8-bit samples */
	PIX_FMT_BAYER_RGGB8,    /**< bayer, RGRG..(odd line), GBGB..(even line), 8-bit samples */
	PIX_FMT_BAYER_GBRG8,    /**< bayer, GBGB..(odd line), RGRG..(even line), 8-bit samples */
	PIX_FMT_BAYER_GRBG8,    /**< bayer, GRGR..(odd line), BGBG..(even line), 8-bit samples */

	PIX_FMT_RAW,
	PIX_FMT_DATA8,      /**<     8bpp */
	PIX_FMT_DATA16,     /**<     16bpp */

	PIX_FMT_NB,        /**< number of pixel formats. */
} MMPixelFormat;


#endif /* __MM_COMMON_H__ */
