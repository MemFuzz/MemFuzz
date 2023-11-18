#ifndef _MEMFUZZ_STRUCT_H_
#define _MEMFUZZ_STRUCT_H_
/*Add necessary header here to avoid compile problems*/
/*Struct Declaration Begin*/
struct ColorMapObject;
struct GifColorType;
struct GifImageDesc;
struct GifFileType;
struct SavedImage;
struct ExtensionBlock;
/*Enumeration Definition Begin*/
/*Struct Definition Begin*/
/* Used at: gif2rgb.c */
/* <5fc> ./gif_lib.h:42 */
struct ColorMapObject {
	int                        ColorCount;           /*     0     4 */
	int                        BitsPerPixel;         /*     4     4 */
	_Bool                      SortFlag;             /*     8     1 */

	/* XXX 7 bytes hole, try to pack */

	struct GifColorType        *Colors;              /*    16     8 */

	/* size: 24, cachelines: 1, members: 4 */
	/* sum members: 17, holes: 1, sum holes: 7 */
	/* last cacheline: 24 bytes */
};
/* Used at: gif2rgb.c */
/* <645> ./gif_lib.h:38 */
struct GifColorType {
	unsigned char              Red;                  /*     0     1 */
	unsigned char              Green;                /*     1     1 */
	unsigned char              Blue;                 /*     2     1 */

	/* size: 3, cachelines: 1, members: 3 */
	/* last cacheline: 3 bytes */
};
/* Used at: gif2rgb.c */
/* <877> ./gif_lib.h:49 */
struct GifImageDesc {
	int                        Left;                 /*     0     4 */
	int                        Top;                  /*     4     4 */
	int                        Width;                /*     8     4 */
	int                        Height;               /*    12     4 */
	_Bool                      Interlace;            /*    16     1 */

	/* XXX 7 bytes hole, try to pack */

	struct ColorMapObject      *ColorMap;            /*    24     8 */

	/* size: 32, cachelines: 1, members: 6 */
	/* sum members: 25, holes: 1, sum holes: 7 */
	/* last cacheline: 32 bytes */
};
/* Used at: gif2rgb.c */
/* <7b0> ./gif_lib.h:73 */
struct GifFileType {
	int                        SWidth;               /*     0     4 */
	int                        SHeight;              /*     4     4 */
	int                        SColorResolution;     /*     8     4 */
	int                        SBackGroundColor;     /*    12     4 */
	unsigned char              AspectByte;           /*    16     1 */

	/* XXX 7 bytes hole, try to pack */

	struct ColorMapObject      *SColorMap;           /*    24     8 */
	int                        ImageCount;           /*    32     4 */

	/* XXX 4 bytes hole, try to pack */

	struct GifImageDesc        Image;                /*    40    32 */
	/* --- cacheline 1 boundary (64 bytes) was 8 bytes ago --- */
	struct SavedImage          *SavedImages;         /*    72     8 */
	int                        ExtensionBlockCount;  /*    80     4 */

	/* XXX 4 bytes hole, try to pack */

	struct ExtensionBlock      *ExtensionBlocks;     /*    88     8 */
	int                        Error;                /*    96     4 */

	/* XXX 4 bytes hole, try to pack */

	void *                     UserData;             /*   104     8 */
	void *                     Private;              /*   112     8 */

	/* size: 120, cachelines: 2, members: 14 */
	/* sum members: 101, holes: 4, sum holes: 19 */
	/* last cacheline: 56 bytes */
};
/* Used at: gif2rgb.c */
/* <8d8> ./gif_lib.h:66 */
struct SavedImage {
	struct GifImageDesc        ImageDesc;            /*     0    32 */
	unsigned char              *RasterBits;          /*    32     8 */
	int                        ExtensionBlockCount;  /*    40     4 */

	/* XXX 4 bytes hole, try to pack */

	struct ExtensionBlock      *ExtensionBlocks;     /*    48     8 */

	/* size: 56, cachelines: 1, members: 4 */
	/* sum members: 52, holes: 1, sum holes: 4 */
	/* last cacheline: 56 bytes */
};
/* Used at: gif2rgb.c */
/* <921> ./gif_lib.h:55 */
struct ExtensionBlock {
	int                        ByteCount;            /*     0     4 */

	/* XXX 4 bytes hole, try to pack */

	unsigned char              *Bytes;               /*     8     8 */
	int                        Function;             /*    16     4 */

	/* size: 24, cachelines: 1, members: 3 */
	/* sum members: 16, holes: 1, sum holes: 4 */
	/* padding: 4 */
	/* last cacheline: 24 bytes */
};
#endif
