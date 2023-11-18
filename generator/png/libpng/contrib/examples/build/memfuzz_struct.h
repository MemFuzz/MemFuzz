#ifndef _MEMFUZZ_STRUCT_H_
#define _MEMFUZZ_STRUCT_H_
#include <zlib.h>
#include <setjmp.h>
/*Add necessary header here to avoid compile problems*/
/*Struct Declaration Begin*/
struct png_XYZ;
struct png_xy;
struct memfuzz_anonymous_struct_0;
struct png_row_info_struct;
struct png_compression_buffer;
struct png_color_struct;
struct png_color_16_struct;
struct png_color_8_struct;
struct png_colorspace;
struct png_text_struct;
struct png_time_struct;
struct png_info_def;
struct png_unknown_chunk_t;
struct png_struct_def;
struct png_sPLT_struct;
struct png_sPLT_entry_struct;
struct memfuzz_anonymous_struct_2;
struct png_control;
struct memfuzz_anonymous_struct_4;
struct memfuzz_anonymous_struct_9;
struct memfuzz_anonymous_struct_10;
struct png_dsort_struct;
struct memfuzz_anonymous_struct_18;
struct memfuzz_anonymous_struct_19;
struct memfuzz_anonymous_struct_22;
/*Enumeration Definition Begin*/
/*Struct Definition Begin*/
/* Used at: png.c */
/* <138> ./pngstruct.h:94 */
struct png_XYZ {
	int                        red_X;                /*     0     4 */
	int                        red_Y;                /*     4     4 */
	int                        red_Z;                /*     8     4 */
	int                        green_X;              /*    12     4 */
	int                        green_Y;              /*    16     4 */
	int                        green_Z;              /*    20     4 */
	int                        blue_X;               /*    24     4 */
	int                        blue_Y;               /*    28     4 */
	int                        blue_Z;               /*    32     4 */

	/* size: 36, cachelines: 1, members: 9 */
	/* last cacheline: 36 bytes */
};
/* Used at: png.c */
/* <28b> ./pngstruct.h:83 */
struct png_xy {
	int                        redx;                 /*     0     4 */
	int                        redy;                 /*     4     4 */
	int                        greenx;               /*     8     4 */
	int                        greeny;               /*    12     4 */
	int                        bluex;                /*    16     4 */
	int                        bluey;                /*    20     4 */
	int                        whitex;               /*    24     4 */
	int                        whitey;               /*    28     4 */

	/* size: 32, cachelines: 1, members: 8 */
	/* last cacheline: 32 bytes */
};
/* Used at: png.c */
/* <33d> /home/liu2598/Product/libpng/master/src_raw/png.c:2245 */
struct memfuzz_anonymous_struct_0 {
	unsigned int               adler;                /*     0     4 */
	unsigned int               crc;                  /*     4     4 */
	unsigned int               length;               /*     8     4 */
	unsigned int               md5[4];               /*    12    16 */
	unsigned char              have_md5;             /*    28     1 */
	unsigned char              is_broken;            /*    29     1 */
	unsigned short             intent;               /*    30     2 */

	/* size: 32, cachelines: 1, members: 7 */
	/* last cacheline: 32 bytes */
};
/* Used at: png.c */
/* <2b8e> ./png.h:754 */
struct png_row_info_struct {
	unsigned int               width;                /*     0     4 */

	/* XXX 4 bytes hole, try to pack */

	long unsigned int          rowbytes;             /*     8     8 */
	unsigned char              color_type;           /*    16     1 */
	unsigned char              bit_depth;            /*    17     1 */
	unsigned char              channels;             /*    18     1 */
	unsigned char              pixel_depth;          /*    19     1 */

	/* size: 24, cachelines: 1, members: 6 */
	/* sum members: 16, holes: 1, sum holes: 4 */
	/* padding: 4 */
	/* last cacheline: 24 bytes */
};
/* Used at: png.c */
/* <2d30> ./pngstruct.h:61 */
struct png_compression_buffer {
	struct png_compression_buffer *next;             /*     0     8 */
	unsigned char              output[1];            /*     8     1 */

	/* size: 16, cachelines: 1, members: 2 */
	/* padding: 7 */
	/* last cacheline: 16 bytes */
};
/* Used at: png.c */
/* <2d7a> ./png.h:478 */
struct png_color_struct {
	unsigned char              red;                  /*     0     1 */
	unsigned char              green;                /*     1     1 */
	unsigned char              blue;                 /*     2     1 */

	/* size: 3, cachelines: 1, members: 3 */
	/* last cacheline: 3 bytes */
};
/* Used at: png.c */
/* <2db7> ./png.h:488 */
struct png_color_16_struct {
	unsigned char              index;                /*     0     1 */

	/* XXX 1 byte hole, try to pack */

	unsigned short             red;                  /*     2     2 */
	unsigned short             green;                /*     4     2 */
	unsigned short             blue;                 /*     6     2 */
	unsigned short             gray;                 /*     8     2 */

	/* size: 10, cachelines: 1, members: 5 */
	/* sum members: 9, holes: 1, sum holes: 1 */
	/* last cacheline: 10 bytes */
};
/* Used at: png.c */
/* <2e26> ./png.h:500 */
struct png_color_8_struct {
	unsigned char              red;                  /*     0     1 */
	unsigned char              green;                /*     1     1 */
	unsigned char              blue;                 /*     2     1 */
	unsigned char              gray;                 /*     3     1 */
	unsigned char              alpha;                /*     4     1 */

	/* size: 5, cachelines: 1, members: 5 */
	/* last cacheline: 5 bytes */
};
/* Used at: png.c */
/* <3195> ./pngstruct.h:112 */
struct png_colorspace {
	int                        gamma;                /*     0     4 */
	struct png_xy              end_points_xy;        /*     4    32 */
	struct png_XYZ             end_points_XYZ;       /*    36    36 */
	/* --- cacheline 1 boundary (64 bytes) was 8 bytes ago --- */
	unsigned short             rendering_intent;     /*    72     2 */
	unsigned short             flags;                /*    74     2 */

	/* size: 76, cachelines: 2, members: 5 */
	/* last cacheline: 12 bytes */
};
/* Used at: png.c */
/* <3203> ./png.h:562 */
struct png_text_struct {
	int                        compression;          /*     0     4 */

	/* XXX 4 bytes hole, try to pack */

	char                       *key;                 /*     8     8 */
	char                       *text;                /*    16     8 */
	long unsigned int          text_length;          /*    24     8 */
	long unsigned int          itxt_length;          /*    32     8 */
	char                       *lang;                /*    40     8 */
	char                       *lang_key;            /*    48     8 */

	/* size: 56, cachelines: 1, members: 7 */
	/* sum members: 52, holes: 1, sum holes: 4 */
	/* last cacheline: 56 bytes */
};
/* Used at: png.c */
/* <3274> ./png.h:600 */
struct png_time_struct {
	unsigned short             year;                 /*     0     2 */
	unsigned char              month;                /*     2     1 */
	unsigned char              day;                  /*     3     1 */
	unsigned char              hour;                 /*     4     1 */
	unsigned char              minute;               /*     5     1 */
	unsigned char              second;               /*     6     1 */

	/* size: 8, cachelines: 1, members: 6 */
	/* padding: 1 */
	/* last cacheline: 8 bytes */
};
/* Used at: png.c */
/* <2ed9> ./pnginfo.h:55 */
struct png_info_def {
	unsigned int               width;                /*     0     4 */
	unsigned int               height;               /*     4     4 */
	unsigned int               valid;                /*     8     4 */

	/* XXX 4 bytes hole, try to pack */

	long unsigned int          rowbytes;             /*    16     8 */
	struct png_color_struct    *palette;             /*    24     8 */
	unsigned short             num_palette;          /*    32     2 */
	unsigned short             num_trans;            /*    34     2 */
	unsigned char              bit_depth;            /*    36     1 */
	unsigned char              color_type;           /*    37     1 */
	unsigned char              compression_type;     /*    38     1 */
	unsigned char              filter_type;          /*    39     1 */
	unsigned char              interlace_type;       /*    40     1 */
	unsigned char              channels;             /*    41     1 */
	unsigned char              pixel_depth;          /*    42     1 */
	unsigned char              spare_byte;           /*    43     1 */
	unsigned char              signature[8];         /*    44     8 */
	struct png_colorspace      colorspace;           /*    52    76 */
	/* --- cacheline 2 boundary (128 bytes) --- */
	char                       *iccp_name;           /*   128     8 */
	unsigned char              *iccp_profile;        /*   136     8 */
	unsigned int               iccp_proflen;         /*   144     4 */
	int                        num_text;             /*   148     4 */
	int                        max_text;             /*   152     4 */

	/* XXX 4 bytes hole, try to pack */

	struct png_text_struct     *text;                /*   160     8 */
	struct png_time_struct     mod_time;             /*   168     8 */
	struct png_color_8_struct  sig_bit;              /*   176     5 */

	/* XXX 3 bytes hole, try to pack */

	unsigned char              *trans_alpha;         /*   184     8 */
	/* --- cacheline 3 boundary (192 bytes) --- */
	struct png_color_16_struct trans_color;          /*   192    10 */
	struct png_color_16_struct background;           /*   202    10 */
	int                        x_offset;             /*   212     4 */
	int                        y_offset;             /*   216     4 */
	unsigned char              offset_unit_type;     /*   220     1 */

	/* XXX 3 bytes hole, try to pack */

	unsigned int               x_pixels_per_unit;    /*   224     4 */
	unsigned int               y_pixels_per_unit;    /*   228     4 */
	unsigned char              phys_unit_type;       /*   232     1 */

	/* XXX 3 bytes hole, try to pack */

	int                        num_exif;             /*   236     4 */
	unsigned char              *exif;                /*   240     8 */
	unsigned char              *eXIf_buf;            /*   248     8 */
	/* --- cacheline 4 boundary (256 bytes) --- */
	unsigned short             *hist;                /*   256     8 */
	char                       *pcal_purpose;        /*   264     8 */
	int                        pcal_X0;              /*   272     4 */
	int                        pcal_X1;              /*   276     4 */
	char                       *pcal_units;          /*   280     8 */
	char                       **pcal_params;        /*   288     8 */
	unsigned char              pcal_type;            /*   296     1 */
	unsigned char              pcal_nparams;         /*   297     1 */

	/* XXX 2 bytes hole, try to pack */

	unsigned int               free_me;              /*   300     4 */
	struct png_unknown_chunk_t *unknown_chunks;      /*   304     8 */
	int                        unknown_chunks_num;   /*   312     4 */

	/* XXX 4 bytes hole, try to pack */

	/* --- cacheline 5 boundary (320 bytes) --- */
	struct png_sPLT_struct     *splt_palettes;       /*   320     8 */
	int                        splt_palettes_num;    /*   328     4 */
	unsigned char              scal_unit;            /*   332     1 */

	/* XXX 3 bytes hole, try to pack */

	char                       *scal_s_width;        /*   336     8 */
	char                       *scal_s_height;       /*   344     8 */
	unsigned char              **row_pointers;       /*   352     8 */

	/* size: 360, cachelines: 6, members: 54 */
	/* sum members: 334, holes: 8, sum holes: 26 */
	/* last cacheline: 40 bytes */
};
/* Used at: png.c */
/* <32fa> ./png.h:622 */
struct png_unknown_chunk_t {
	unsigned char              name[5];              /*     0     5 */

	/* XXX 3 bytes hole, try to pack */

	unsigned char              *data;                /*     8     8 */
	long unsigned int          size;                 /*    16     8 */
	unsigned char              location;             /*    24     1 */

	/* size: 32, cachelines: 1, members: 4 */
	/* sum members: 22, holes: 1, sum holes: 3 */
	/* padding: 7 */
	/* last cacheline: 32 bytes */
};
/* Used at: png.c */
/* <2290> ./pngstruct.h:143 */
struct png_struct_def {
	struct __jmp_buf_tag       jmp_buf_local[1];     /*     0   200 */
	/* --- cacheline 3 boundary (192 bytes) was 8 bytes ago --- */
	void **longjmp_fn;                                                /*   200     8 */
	struct __jmp_buf_tag       *jmp_buf_ptr[1];      /*   208     8 */
	long unsigned int          jmp_buf_size;         /*   216     8 */
	void **error_fn;                                                /*   224     8 */
	void **warning_fn;                                                /*   232     8 */
	void *                     error_ptr;            /*   240     8 */
	void **write_data_fn;                                                /*   248     8 */
	/* --- cacheline 4 boundary (256 bytes) --- */
	void **read_data_fn;                                                /*   256     8 */
	void *                     io_ptr;               /*   264     8 */
	void **read_user_transform_fn;                                                /*   272     8 */
	void **write_user_transform_fn;                                                /*   280     8 */
	void *                     user_transform_ptr;   /*   288     8 */
	unsigned char              user_transform_depth; /*   296     1 */
	unsigned char              user_transform_channels; /*   297     1 */

	/* XXX 2 bytes hole, try to pack */

	unsigned int               mode;                 /*   300     4 */
	unsigned int               flags;                /*   304     4 */
	unsigned int               transformations;      /*   308     4 */
	unsigned int               zowner;               /*   312     4 */

	/* XXX 4 bytes hole, try to pack */

	/* --- cacheline 5 boundary (320 bytes) --- */
	struct z_stream_s          zstream;              /*   320   112 */
	/* --- cacheline 6 boundary (384 bytes) was 48 bytes ago --- */
	struct png_compression_buffer *zbuffer_list;     /*   432     8 */
	unsigned int               zbuffer_size;         /*   440     4 */
	int                        zlib_level;           /*   444     4 */
	/* --- cacheline 7 boundary (448 bytes) --- */
	int                        zlib_method;          /*   448     4 */
	int                        zlib_window_bits;     /*   452     4 */
	int                        zlib_mem_level;       /*   456     4 */
	int                        zlib_strategy;        /*   460     4 */
	int                        zlib_text_level;      /*   464     4 */
	int                        zlib_text_method;     /*   468     4 */
	int                        zlib_text_window_bits; /*   472     4 */
	int                        zlib_text_mem_level;  /*   476     4 */
	int                        zlib_text_strategy;   /*   480     4 */
	int                        zlib_set_level;       /*   484     4 */
	int                        zlib_set_method;      /*   488     4 */
	int                        zlib_set_window_bits; /*   492     4 */
	int                        zlib_set_mem_level;   /*   496     4 */
	int                        zlib_set_strategy;    /*   500     4 */
	unsigned int               width;                /*   504     4 */
	unsigned int               height;               /*   508     4 */
	/* --- cacheline 8 boundary (512 bytes) --- */
	unsigned int               num_rows;             /*   512     4 */
	unsigned int               usr_width;            /*   516     4 */
	long unsigned int          rowbytes;             /*   520     8 */
	unsigned int               iwidth;               /*   528     4 */
	unsigned int               row_number;           /*   532     4 */
	unsigned int               chunk_name;           /*   536     4 */

	/* XXX 4 bytes hole, try to pack */

	unsigned char              *prev_row;            /*   544     8 */
	unsigned char              *row_buf;             /*   552     8 */
	unsigned char              *try_row;             /*   560     8 */
	unsigned char              *tst_row;             /*   568     8 */
	/* --- cacheline 9 boundary (576 bytes) --- */
	long unsigned int          info_rowbytes;        /*   576     8 */
	unsigned int               idat_size;            /*   584     4 */
	unsigned int               crc;                  /*   588     4 */
	struct png_color_struct    *palette;             /*   592     8 */
	unsigned short             num_palette;          /*   600     2 */

	/* XXX 2 bytes hole, try to pack */

	int                        num_palette_max;      /*   604     4 */
	unsigned short             num_trans;            /*   608     2 */
	unsigned char              compression;          /*   610     1 */
	unsigned char              filter;               /*   611     1 */
	unsigned char              interlaced;           /*   612     1 */
	unsigned char              pass;                 /*   613     1 */
	unsigned char              do_filter;            /*   614     1 */
	unsigned char              color_type;           /*   615     1 */
	unsigned char              bit_depth;            /*   616     1 */
	unsigned char              usr_bit_depth;        /*   617     1 */
	unsigned char              pixel_depth;          /*   618     1 */
	unsigned char              channels;             /*   619     1 */
	unsigned char              usr_channels;         /*   620     1 */
	unsigned char              sig_bytes;            /*   621     1 */
	unsigned char              maximum_pixel_depth;  /*   622     1 */
	unsigned char              transformed_pixel_depth; /*   623     1 */
	unsigned char              zstream_start;        /*   624     1 */

	/* XXX 1 byte hole, try to pack */

	unsigned short             filler;               /*   626     2 */
	unsigned char              background_gamma_type; /*   628     1 */

	/* XXX 3 bytes hole, try to pack */

	int                        background_gamma;     /*   632     4 */
	struct png_color_16_struct background;           /*   636    10 */
	/* --- cacheline 10 boundary (640 bytes) was 6 bytes ago --- */
	struct png_color_16_struct background_1;         /*   646    10 */
	void **output_flush_fn;                                                /*   656     8 */
	unsigned int               flush_dist;           /*   664     4 */
	unsigned int               flush_rows;           /*   668     4 */
	int                        gamma_shift;          /*   672     4 */
	int                        screen_gamma;         /*   676     4 */
	unsigned char              *gamma_table;         /*   680     8 */
	unsigned short             **gamma_16_table;     /*   688     8 */
	unsigned char              *gamma_from_1;        /*   696     8 */
	/* --- cacheline 11 boundary (704 bytes) --- */
	unsigned char              *gamma_to_1;          /*   704     8 */
	unsigned short             **gamma_16_from_1;    /*   712     8 */
	unsigned short             **gamma_16_to_1;      /*   720     8 */
	struct png_color_8_struct  sig_bit;              /*   728     5 */
	struct png_color_8_struct  shift;                /*   733     5 */

	/* XXX 6 bytes hole, try to pack */

	unsigned char              *trans_alpha;         /*   744     8 */
	struct png_color_16_struct trans_color;          /*   752    10 */

	/* XXX 6 bytes hole, try to pack */

	/* --- cacheline 12 boundary (768 bytes) --- */
	void **read_row_fn;                                                /*   768     8 */
	void **write_row_fn;                                                /*   776     8 */
	void **info_fn;                                                /*   784     8 */
	void **row_fn;                                                /*   792     8 */
	void **end_fn;                                                /*   800     8 */
	unsigned char              *save_buffer_ptr;     /*   808     8 */
	unsigned char              *save_buffer;         /*   816     8 */
	unsigned char              *current_buffer_ptr;  /*   824     8 */
	/* --- cacheline 13 boundary (832 bytes) --- */
	unsigned char              *current_buffer;      /*   832     8 */
	unsigned int               push_length;          /*   840     4 */
	unsigned int               skip_length;          /*   844     4 */
	long unsigned int          save_buffer_size;     /*   848     8 */
	long unsigned int          save_buffer_max;      /*   856     8 */
	long unsigned int          buffer_size;          /*   864     8 */
	long unsigned int          current_buffer_size;  /*   872     8 */
	int                        process_mode;         /*   880     4 */
	int                        cur_palette;          /*   884     4 */
	unsigned char              *palette_lookup;      /*   888     8 */
	/* --- cacheline 14 boundary (896 bytes) --- */
	unsigned char              *quantize_index;      /*   896     8 */
	unsigned int               options;              /*   904     4 */
	char                       time_buffer[29];      /*   908    29 */

	/* XXX 3 bytes hole, try to pack */

	unsigned int               free_me;              /*   940     4 */
	void *                     user_chunk_ptr;       /*   944     8 */
	void **read_user_chunk_fn;                                                /*   952     8 */
	/* --- cacheline 15 boundary (960 bytes) --- */
	int                        unknown_default;      /*   960     4 */
	unsigned int               num_chunk_list;       /*   964     4 */
	unsigned char              *chunk_list;          /*   968     8 */
	unsigned char              rgb_to_gray_status;   /*   976     1 */
	unsigned char              rgb_to_gray_coefficients_set; /*   977     1 */
	unsigned short             rgb_to_gray_red_coeff; /*   978     2 */
	unsigned short             rgb_to_gray_green_coeff; /*   980     2 */

	/* XXX 2 bytes hole, try to pack */

	unsigned char              *riffled_palette;     /*   984     8 */
	unsigned int               mng_features_permitted; /*   992     4 */
	unsigned char              filter_type;          /*   996     1 */

	/* XXX 3 bytes hole, try to pack */

	void *                     mem_ptr;              /*  1000     8 */
	void **malloc_fn;                                                /*  1008     8 */
	void **free_fn;                                                /*  1016     8 */
	/* --- cacheline 16 boundary (1024 bytes) --- */
	unsigned char              *big_row_buf;         /*  1024     8 */
	unsigned char              *quantize_sort;       /*  1032     8 */
	unsigned char              *index_to_palette;    /*  1040     8 */
	unsigned char              *palette_to_index;    /*  1048     8 */
	unsigned char              compression_type;     /*  1056     1 */

	/* XXX 3 bytes hole, try to pack */

	unsigned int               user_width_max;       /*  1060     4 */
	unsigned int               user_height_max;      /*  1064     4 */
	unsigned int               user_chunk_cache_max; /*  1068     4 */
	long unsigned int          user_chunk_malloc_max; /*  1072     8 */
	struct png_unknown_chunk_t unknown_chunk;        /*  1080    32 */
	/* --- cacheline 17 boundary (1088 bytes) was 24 bytes ago --- */
	long unsigned int          old_big_row_buf_size; /*  1112     8 */
	unsigned char              *read_buffer;         /*  1120     8 */
	long unsigned int          read_buffer_size;     /*  1128     8 */
	unsigned int               IDAT_read_size;       /*  1136     4 */
	unsigned int               io_state;             /*  1140     4 */
	unsigned char              *big_prev_row;        /*  1144     8 */
	/* --- cacheline 18 boundary (1152 bytes) --- */
	void **read_filter[4];                                             /*  1152    32 */
	struct png_colorspace      colorspace;           /*  1184    76 */

	/* size: 1264, cachelines: 20, members: 146 */
	/* sum members: 1221, holes: 12, sum holes: 39 */
	/* padding: 4 */
	/* last cacheline: 48 bytes */
};
/* Used at: png.c */
/* <3361> ./png.h:533 */
struct png_sPLT_struct {
	char                       *name;                /*     0     8 */
	unsigned char              depth;                /*     8     1 */

	/* XXX 7 bytes hole, try to pack */

	struct png_sPLT_entry_struct *entries;           /*    16     8 */
	int                        nentries;             /*    24     4 */

	/* size: 32, cachelines: 1, members: 4 */
	/* sum members: 21, holes: 1, sum holes: 7 */
	/* padding: 4 */
	/* last cacheline: 32 bytes */
};
/* Used at: png.c */
/* <33bc> ./png.h:516 */
struct png_sPLT_entry_struct {
	unsigned short             red;                  /*     0     2 */
	unsigned short             green;                /*     2     2 */
	unsigned short             blue;                 /*     4     2 */
	unsigned short             alpha;                /*     6     2 */
	unsigned short             frequency;            /*     8     2 */

	/* size: 10, cachelines: 1, members: 5 */
	/* last cacheline: 10 bytes */
};
/* Used at: png.c */
/* <37fa> ./png.h:2672 */
struct memfuzz_anonymous_struct_2 {
	struct png_control         *opaque;              /*     0     8 */
	unsigned int               version;              /*     8     4 */
	unsigned int               width;                /*    12     4 */
	unsigned int               height;               /*    16     4 */
	unsigned int               format;               /*    20     4 */
	unsigned int               flags;                /*    24     4 */
	unsigned int               colormap_entries;     /*    28     4 */
	unsigned int               warning_or_error;     /*    32     4 */
	char                       message[64];          /*    36    64 */

	/* size: 104, cachelines: 2, members: 9 */
	/* padding: 4 */
	/* last cacheline: 40 bytes */
};
/* Used at: png.c */
/* <3886> ./pngpriv.h:2026 */
struct png_control {
	struct png_struct_def      *png_ptr;             /*     0     8 */
	struct png_info_def        *info_ptr;            /*     8     8 */
	void *                     error_buf;            /*    16     8 */
	unsigned char              *memory;              /*    24     8 */
	long unsigned int          size;                 /*    32     8 */
	unsigned int               for_write:1;          /*    40: 0  4 */
	unsigned int               owned_file:1;         /*    40: 1  4 */

	/* size: 48, cachelines: 1, members: 7 */
	/* padding: 4 */
	/* bit_padding: 30 bits */
	/* last cacheline: 48 bytes */
};
/* Used at: pngerror.c */
/* <1e50> ./png.h:2672 */
struct memfuzz_anonymous_struct_4 {
	struct png_control         *opaque;              /*     0     8 */
	unsigned int               version;              /*     8     4 */
	unsigned int               width;                /*    12     4 */
	unsigned int               height;               /*    16     4 */
	unsigned int               format;               /*    20     4 */
	unsigned int               flags;                /*    24     4 */
	unsigned int               colormap_entries;     /*    28     4 */
	unsigned int               warning_or_error;     /*    32     4 */
	char                       message[64];          /*    36    64 */

	/* size: 104, cachelines: 2, members: 9 */
	/* padding: 4 */
	/* last cacheline: 40 bytes */
};
/* Used at: pngread.c */
/* <31a7> ./png.h:2672 */
struct memfuzz_anonymous_struct_9 {
	struct png_control         *opaque;              /*     0     8 */
	unsigned int               version;              /*     8     4 */
	unsigned int               width;                /*    12     4 */
	unsigned int               height;               /*    16     4 */
	unsigned int               format;               /*    20     4 */
	unsigned int               flags;                /*    24     4 */
	unsigned int               colormap_entries;     /*    28     4 */
	unsigned int               warning_or_error;     /*    32     4 */
	char                       message[64];          /*    36    64 */

	/* size: 104, cachelines: 2, members: 9 */
	/* padding: 4 */
	/* last cacheline: 40 bytes */
};
/* Used at: pngread.c */
/* <34e2> /home/liu2598/Product/libpng/master/src_raw/pngread.c:1283 */
typedef struct memfuzz_anonymous_struct_10 {
	struct {
		struct png_control *opaque;              /*     0     8 */
		unsigned int       version;              /*     8     4 */
		unsigned int       width;                /*    12     4 */
		unsigned int       height;               /*    16     4 */
		unsigned int       format;               /*    20     4 */
		unsigned int       flags;                /*    24     4 */
		unsigned int       colormap_entries;     /*    28     4 */
		unsigned int       warning_or_error;     /*    32     4 */
		char               message[64];          /*    36    64 */
	} *image; /*     0     8 */
	void *                     buffer;               /*     8     8 */
	int                        row_stride;           /*    16     4 */

	/* XXX 4 bytes hole, try to pack */

	void *                     colormap;             /*    24     8 */
	struct png_color_struct    *background;          /*    32     8 */
	void *                     local_row;            /*    40     8 */
	void *                     first_row;            /*    48     8 */
	long int                   row_bytes;            /*    56     8 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	int                        file_encoding;        /*    64     4 */
	int                        gamma_to_linear;      /*    68     4 */
	int                        colormap_processing;  /*    72     4 */

	/* size: 80, cachelines: 2, members: 11 */
	/* sum members: 72, holes: 1, sum holes: 4 */
	/* padding: 4 */
	/* last cacheline: 16 bytes */
} png_image_read_control;
/* Used at: pngrtran.c */
/* <a9> /home/liu2598/Product/libpng/master/src_raw/pngrtran.c:418 */
struct png_dsort_struct {
	struct png_dsort_struct    *next;                /*     0     8 */
	unsigned char              left;                 /*     8     1 */
	unsigned char              right;                /*     9     1 */

	/* size: 16, cachelines: 1, members: 3 */
	/* padding: 6 */
	/* last cacheline: 16 bytes */
};
/* Used at: pngwrite.c */
/* <2965> ./png.h:2672 */
struct memfuzz_anonymous_struct_18 {
	struct png_control         *opaque;              /*     0     8 */
	unsigned int               version;              /*     8     4 */
	unsigned int               width;                /*    12     4 */
	unsigned int               height;               /*    16     4 */
	unsigned int               format;               /*    20     4 */
	unsigned int               flags;                /*    24     4 */
	unsigned int               colormap_entries;     /*    28     4 */
	unsigned int               warning_or_error;     /*    32     4 */
	char                       message[64];          /*    36    64 */

	/* size: 104, cachelines: 2, members: 9 */
	/* padding: 4 */
	/* last cacheline: 40 bytes */
};
/* Used at: pngwrite.c */
/* <2a84> /home/liu2598/Product/libpng/master/src_raw/pngwrite.c:1519 */
typedef struct memfuzz_anonymous_struct_19 {
	struct {
		struct png_control *opaque;              /*     0     8 */
		unsigned int       version;              /*     8     4 */
		unsigned int       width;                /*    12     4 */
		unsigned int       height;               /*    16     4 */
		unsigned int       format;               /*    20     4 */
		unsigned int       flags;                /*    24     4 */
		unsigned int       colormap_entries;     /*    28     4 */
		unsigned int       warning_or_error;     /*    32     4 */
		char               message[64];          /*    36    64 */
	} *image; /*     0     8 */
	void*                      *buffer;              /*     8     8 */
	int                        row_stride;           /*    16     4 */

	/* XXX 4 bytes hole, try to pack */

	void*                      *colormap;            /*    24     8 */
	int                        convert_to_8bit;      /*    32     4 */

	/* XXX 4 bytes hole, try to pack */

	void*                      *first_row;           /*    40     8 */
	long int                   row_bytes;            /*    48     8 */
	void *                     local_row;            /*    56     8 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	unsigned char              *memory;              /*    64     8 */
	long unsigned int          memory_bytes;         /*    72     8 */
	long unsigned int          output_bytes;         /*    80     8 */

	/* size: 88, cachelines: 2, members: 11 */
	/* sum members: 80, holes: 2, sum holes: 8 */
	/* last cacheline: 24 bytes */
} png_image_write_control;
/* Used at: pngwutil.c */
/* <3158> /home/liu2598/Product/libpng/master/src_raw/pngwutil.c:469 */
typedef struct memfuzz_anonymous_struct_22 {
	unsigned char              *input;               /*     0     8 */
	long unsigned int          input_len;            /*     8     8 */
	unsigned int               output_len;           /*    16     4 */
	unsigned char              output[1024];         /*    20  1024 */

	/* size: 1048, cachelines: 17, members: 4 */
	/* padding: 4 */
	/* last cacheline: 24 bytes */
} compression_state;
#endif
