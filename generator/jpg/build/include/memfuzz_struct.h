#ifndef _MEMFUZZ_STRUCT_H_
#define _MEMFUZZ_STRUCT_H_
/*Struct Declaration Begin*/
struct jpeg_error_mgr;
struct jpeg_forward_dct;
struct jpeg_marker_reader;
struct jpeg_memory_mgr;
struct jpeg_entropy_encoder;
struct jpeg_input_controller;
struct jpeg_d_main_controller;
struct jpeg_destination_mgr;
struct jpeg_comp_master;
struct jpeg_decompress_struct;
struct jpeg_color_converter;
struct jpeg_color_deconverter;
struct jpeg_entropy_decoder;
struct _IO_marker;
struct jpeg_common_struct;
struct jpeg_source_mgr;
struct jpeg_c_main_controller;
struct jpeg_marker_struct;
struct jpeg_inverse_dct;
struct jpeg_d_coef_controller;
struct jpeg_compress_struct;
struct jpeg_progress_mgr;
struct cdjpeg_progress_mgr;
struct jpeg_d_post_controller;
struct jpeg_upsampler;
struct jpeg_color_quantizer;
struct jpeg_c_prep_controller;
struct jpeg_c_coef_controller;
struct djpeg_dest_struct;
struct _IO_FILE;
struct jvirt_barray_control;
struct jpeg_decomp_master;
struct jpeg_downsampler;
struct jpeg_marker_writer;
/*Enumeration Definition Begin*/
enum memfuzz_anonymous_enum_0 {
		JDCT_ISLOW = 0,
		JDCT_IFAST = 1,
		JDCT_FLOAT = 2,
	};
enum memfuzz_anonymous_enum_1 {
		JDITHER_NONE    = 0,
		JDITHER_ORDERED = 1,
		JDITHER_FS      = 2,
	};
enum memfuzz_anonymous_enum_2 {
		JCS_UNKNOWN   = 0,
		JCS_GRAYSCALE = 1,
		JCS_RGB       = 2,
		JCS_YCbCr     = 3,
		JCS_CMYK      = 4,
		JCS_YCCK      = 5,
		JCS_EXT_RGB   = 6,
		JCS_EXT_RGBX  = 7,
		JCS_EXT_BGR   = 8,
		JCS_EXT_BGRX  = 9,
		JCS_EXT_XBGR  = 10,
		JCS_EXT_XRGB  = 11,
		JCS_EXT_RGBA  = 12,
		JCS_EXT_BGRA  = 13,
		JCS_EXT_ABGR  = 14,
		JCS_EXT_ARGB  = 15,
		JCS_RGB565    = 16,
	};
/*Struct Definition Begin*/
/* Used at: /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/djpeg.c */
/* <933> /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/jpeglib.h:720 */
struct jpeg_error_mgr {
	void **error_exit;                                                /*     0     8 */
	void **emit_message;                                                /*     8     8 */
	void **output_message;                                                /*    16     8 */
	void **format_message;                                                /*    24     8 */
	void **reset_error_mgr;                                                /*    32     8 */
	int                        msg_code;             /*    40     4 */
	union {
		int                i[8];                 /*    44    32 */
		char               s[80];                /*    44    80 */
	} msg_parm;                                      /*    44    80 */
	/* --- cacheline 1 boundary (64 bytes) was 60 bytes ago --- */
	int                        trace_level;          /*   124     4 */
	/* --- cacheline 2 boundary (128 bytes) --- */
	long int                   num_warnings;         /*   128     8 */
	const const char  *        *jpeg_message_table;  /*   136     8 */
	int                        last_jpeg_message;    /*   144     4 */

	/* XXX 4 bytes hole, try to pack */

	const const char  *        *addon_message_table; /*   152     8 */
	int                        first_addon_message;  /*   160     4 */
	int                        last_addon_message;   /*   164     4 */

	/* size: 168, cachelines: 3, members: 14 */
	/* sum members: 164, holes: 1, sum holes: 4 */
	/* last cacheline: 40 bytes */
};
/* Used at: /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/wrppm.c */
/* <8ede> /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/jpegint.h:219 */
struct jpeg_marker_reader {
	void **reset_marker_reader;                                                /*     0     8 */
	void **read_markers;                                                /*     8     8 */
	void **read_restart_marker;                                                /*    16     8 */
	int                        saw_SOI;              /*    24     4 */
	int                        saw_SOF;              /*    28     4 */
	int                        next_restart_num;     /*    32     4 */
	unsigned int               discarded_bytes;      /*    36     4 */

	/* size: 40, cachelines: 1, members: 7 */
	/* last cacheline: 40 bytes */
};
/* Used at: /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/djpeg.c */
/* <a6a> /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/jpeglib.h:833 */
struct jpeg_memory_mgr {
	void **alloc_small;                                                /*     0     8 */
	void **alloc_large;                                                /*     8     8 */
	void **alloc_sarray;                                                /*    16     8 */
	void **alloc_barray;                                                /*    24     8 */
	void **request_virt_sarray;                                                /*    32     8 */
	void **request_virt_barray;                                                /*    40     8 */
	void **realize_virt_arrays;                                                /*    48     8 */
	void **access_virt_sarray;                                                /*    56     8 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	void **access_virt_barray;                                                /*    64     8 */
	void **free_pool;                                                /*    72     8 */
	void **self_destruct;                                                /*    80     8 */
	long int                   max_memory_to_use;    /*    88     8 */
	long int                   max_alloc_chunk;      /*    96     8 */

	/* size: 104, cachelines: 2, members: 13 */
	/* last cacheline: 40 bytes */
};
/* Used at: /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/wrppm.c */
/* <8e88> /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/jpegint.h:180 */
struct jpeg_input_controller {
	void **consume_input;                                                /*     0     8 */
	void **reset_input_controller;                                                /*     8     8 */
	void **start_input_pass;                                                /*    16     8 */
	void **finish_input_pass;                                                /*    24     8 */
	int                        has_multiple_scans;   /*    32     4 */
	int                        eoi_reached;          /*    36     4 */

	/* size: 40, cachelines: 1, members: 6 */
	/* last cacheline: 40 bytes */
};
/* Used at: /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/wrppm.c */
/* <8d52> /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/jpegint.h:192 */
struct jpeg_d_main_controller {
	void **start_pass;                                                /*     0     8 */
	void **process_data;                                                /*     8     8 */

	/* size: 16, cachelines: 1, members: 2 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/rdswitch.c */
/* <56e5> /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/jpeglib.h:790 */
struct jpeg_destination_mgr {
	unsigned char              *next_output_byte;    /*     0     8 */
	long unsigned int          free_in_buffer;       /*     8     8 */
	void **init_destination;                                                /*    16     8 */
	void **empty_output_buffer;                                                /*    24     8 */
	void **term_destination;                                                /*    32     8 */

	/* size: 40, cachelines: 1, members: 5 */
	/* last cacheline: 40 bytes */
};
/* Used at: /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/djpeg.c */
/* <e9c> /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/jpeglib.h:472 */
struct jpeg_decompress_struct {
	struct jpeg_error_mgr      *err;                 /*     0     8 */
	struct jpeg_memory_mgr     *mem;                 /*     8     8 */
	struct jpeg_progress_mgr   *progress;            /*    16     8 */
	void *                     client_data;          /*    24     8 */
	int                        is_decompressor;      /*    32     4 */
	int                        global_state;         /*    36     4 */
	struct jpeg_source_mgr     *src;                 /*    40     8 */
	unsigned int               image_width;          /*    48     4 */
	unsigned int               image_height;         /*    52     4 */
	int                        num_components;       /*    56     4 */
	enum memfuzz_anonymous_enum_2 jpeg_color_space;
	/* --- cacheline 1 boundary (64 bytes) --- */
	enum memfuzz_anonymous_enum_2 out_color_space;
	unsigned int               scale_num;            /*    68     4 */
	unsigned int               scale_denom;          /*    72     4 */

	/* XXX 4 bytes hole, try to pack */

	double                     output_gamma;         /*    80     8 */
	int                        buffered_image;       /*    88     4 */
	int                        raw_data_out;         /*    92     4 */
	enum memfuzz_anonymous_enum_0 dct_method;
	int                        do_fancy_upsampling;  /*   100     4 */
	int                        do_block_smoothing;   /*   104     4 */
	int                        quantize_colors;      /*   108     4 */
	enum memfuzz_anonymous_enum_1 dither_mode;
	int                        two_pass_quantize;    /*   116     4 */
	int                        desired_number_of_colors; /*   120     4 */
	int                        enable_1pass_quant;   /*   124     4 */
	/* --- cacheline 2 boundary (128 bytes) --- */
	int                        enable_external_quant; /*   128     4 */
	int                        enable_2pass_quant;   /*   132     4 */
	unsigned int               output_width;         /*   136     4 */
	unsigned int               output_height;        /*   140     4 */
	int                        out_color_components; /*   144     4 */
	int                        output_components;    /*   148     4 */
	int                        rec_outbuf_height;    /*   152     4 */
	int                        actual_number_of_colors; /*   156     4 */
	unsigned char              **colormap;           /*   160     8 */
	unsigned int               output_scanline;      /*   168     4 */
	int                        input_scan_number;    /*   172     4 */
	unsigned int               input_iMCU_row;       /*   176     4 */
	int                        output_scan_number;   /*   180     4 */
	unsigned int               output_iMCU_row;      /*   184     4 */

	/* XXX 4 bytes hole, try to pack */

	/* --- cacheline 3 boundary (192 bytes) --- */
	int                        *coef_bits[64];       /*   192     8 */
	struct {
		unsigned short     quantval[64];         /*   200   128 */
		/* --- cacheline 5 boundary (320 bytes) was 8 bytes ago --- */
		int                sent_table;           /*   328     4 */
	} *quant_tbl_ptrs[4]; /*   200    32 */
	struct {
		unsigned char      bits[17];             /*   232    17 */
		unsigned char      huffval[256];         /*   249   256 */

		/* XXX 3 bytes hole, try to pack */

		/* --- cacheline 7 boundary (448 bytes) was 60 bytes ago --- */
		int                sent_table;           /*   508     4 */
	} *dc_huff_tbl_ptrs[4]; /*   232    32 */
	struct {
		unsigned char      bits[17];             /*   264    17 */
		unsigned char      huffval[256];         /*   281   256 */

		/* XXX 3 bytes hole, try to pack */

		/* --- cacheline 8 boundary (512 bytes) was 28 bytes ago --- */
		int                sent_table;           /*   540     4 */
	} *ac_huff_tbl_ptrs[4]; /*   264    32 */
	int                        data_precision;       /*   296     4 */

	/* XXX 4 bytes hole, try to pack */

	struct {
		int                component_id;         /*   304     4 */
		int                component_index;      /*   308     4 */
		int                h_samp_factor;        /*   312     4 */
		int                v_samp_factor;        /*   316     4 */
		int                quant_tbl_no;         /*   320     4 */
		int                dc_tbl_no;            /*   324     4 */
		int                ac_tbl_no;            /*   328     4 */
		unsigned int       width_in_blocks;      /*   332     4 */
		unsigned int       height_in_blocks;     /*   336     4 */
		int                DCT_scaled_size;      /*   340     4 */
		unsigned int       downsampled_width;    /*   344     4 */
		unsigned int       downsampled_height;   /*   348     4 */
		int                component_needed;     /*   352     4 */
		int                MCU_width;            /*   356     4 */
		int                MCU_height;           /*   360     4 */
		int                MCU_blocks;           /*   364     4 */
		int                MCU_sample_width;     /*   368     4 */
		int                last_col_width;       /*   372     4 */
		int                last_row_height;      /*   376     4 */

		/* XXX 4 bytes hole, try to pack */

		struct {
			unsigned short quantval[64];     /*   384   128 */
			int        sent_table;           /*   512     4 */
		} *quant_table; /*   384     8 */
		void *             dct_table;            /*   392     8 */
	} *comp_info; /*   304     8 */
	int                        progressive_mode;     /*   312     4 */
	int                        arith_code;           /*   316     4 */
	unsigned char              arith_dc_L[16];       /*   320    16 */
	unsigned char              arith_dc_U[16];       /*   336    16 */
	unsigned char              arith_ac_K[16];       /*   352    16 */
	unsigned int               restart_interval;     /*   368     4 */
	int                        saw_JFIF_marker;      /*   372     4 */
	unsigned char              JFIF_major_version;   /*   376     1 */
	unsigned char              JFIF_minor_version;   /*   377     1 */
	unsigned char              density_unit;         /*   378     1 */

	/* XXX 1 byte hole, try to pack */

	unsigned short             X_density;            /*   380     2 */
	unsigned short             Y_density;            /*   382     2 */
	int                        saw_Adobe_marker;     /*   384     4 */
	unsigned char              Adobe_transform;      /*   388     1 */

	/* XXX 3 bytes hole, try to pack */

	int                        CCIR601_sampling;     /*   392     4 */

	/* XXX 4 bytes hole, try to pack */

	struct jpeg_marker_struct  *marker_list;         /*   400     8 */
	int                        max_h_samp_factor;    /*   408     4 */
	int                        max_v_samp_factor;    /*   412     4 */
	int                        min_DCT_scaled_size;  /*   416     4 */
	unsigned int               total_iMCU_rows;      /*   420     4 */
	unsigned char              *sample_range_limit;  /*   424     8 */
	int                        comps_in_scan;        /*   432     4 */

	/* XXX 4 bytes hole, try to pack */

	struct {
		int                component_id;         /*   440     4 */
		int                component_index;      /*   444     4 */
		int                h_samp_factor;        /*   448     4 */
		int                v_samp_factor;        /*   452     4 */
		int                quant_tbl_no;         /*   456     4 */
		int                dc_tbl_no;            /*   460     4 */
		int                ac_tbl_no;            /*   464     4 */
		unsigned int       width_in_blocks;      /*   468     4 */
		unsigned int       height_in_blocks;     /*   472     4 */
		int                DCT_scaled_size;      /*   476     4 */
		unsigned int       downsampled_width;    /*   480     4 */
		unsigned int       downsampled_height;   /*   484     4 */
		int                component_needed;     /*   488     4 */
		int                MCU_width;            /*   492     4 */
		int                MCU_height;           /*   496     4 */
		int                MCU_blocks;           /*   500     4 */
		int                MCU_sample_width;     /*   504     4 */
		int                last_col_width;       /*   508     4 */
		int                last_row_height;      /*   512     4 */

		/* XXX 4 bytes hole, try to pack */

		struct {
			unsigned short quantval[64];     /*   520   128 */
			/* --- cacheline 10 boundary (640 bytes) was 8 bytes ago --- */
			int        sent_table;           /*   648     4 */
		} *quant_table; /*   520     8 */
		void *             dct_table;            /*   528     8 */
	} *cur_comp_info[4]; /*   440    32 */
	unsigned int               MCUs_per_row;         /*   472     4 */
	unsigned int               MCU_rows_in_scan;     /*   476     4 */
	int                        blocks_in_MCU;        /*   480     4 */
	int                        MCU_membership[10];   /*   484    40 */
	int                        Ss1;                   /*   524     4 */
	int                        Se1;                   /*   528     4 */
	int                        Ah1;                   /*   532     4 */
	int                        Al1;                   /*   536     4 */
	int                        unread_marker;        /*   540     4 */
	struct jpeg_decomp_master  *master;              /*   544     8 */
	struct jpeg_d_main_controller *main;             /*   552     8 */
	struct jpeg_d_coef_controller *coef;             /*   560     8 */
	struct jpeg_d_post_controller *post;             /*   568     8 */
	struct jpeg_input_controller *inputctl;          /*   576     8 */
	struct jpeg_marker_reader  *marker;              /*   584     8 */
	struct jpeg_entropy_decoder *entropy;            /*   592     8 */
	struct jpeg_inverse_dct    *idct;                /*   600     8 */
	struct jpeg_upsampler      *upsample;            /*   608     8 */
	struct jpeg_color_deconverter *cconvert;         /*   616     8 */
	struct jpeg_color_quantizer *cquantize;          /*   624     8 */

	/* size: 632, cachelines: 10, members: 88 */
	/* sum members: 608, holes: 7, sum holes: 24 */
	/* last cacheline: 56 bytes */
};
/* Used at: /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/wrppm.c */
/* <9038> /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/jpegint.h:273 */
struct jpeg_color_deconverter {
	void **start_pass;                                                /*     0     8 */
	void **color_convert;                                                /*     8     8 */

	/* size: 16, cachelines: 1, members: 2 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/wrppm.c */
/* <8f4c> /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/jpegint.h:239 */
struct jpeg_entropy_decoder {
	void **start_pass;                                                /*     0     8 */
	void **decode_mcu;                                                /*     8     8 */
	int                        insufficient_data;    /*    16     4 */

	/* size: 24, cachelines: 1, members: 3 */
	/* padding: 4 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/djpeg.c */
/* <8d6> /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/jpeglib.h:282 */
struct jpeg_common_struct {
	struct jpeg_error_mgr      *err;                 /*     0     8 */
	struct jpeg_memory_mgr     *mem;                 /*     8     8 */
	struct jpeg_progress_mgr   *progress;            /*    16     8 */
	void *                     client_data;          /*    24     8 */
	int                        is_decompressor;      /*    32     4 */
	int                        global_state;         /*    36     4 */

	/* size: 40, cachelines: 1, members: 6 */
	/* last cacheline: 40 bytes */
};
/* Used at: /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/djpeg.c */
/* <1352> /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/jpeglib.h:802 */
struct jpeg_source_mgr {
	const unsigned char        *next_input_byte;     /*     0     8 */
	long unsigned int          bytes_in_buffer;      /*     8     8 */
	void **init_source;                                                /*    16     8 */
	void **fill_input_buffer;                                                /*    24     8 */
	void **skip_input_data;                                                /*    32     8 */
	void **resync_to_restart;                                                /*    40     8 */
	void **term_source;                                                /*    48     8 */

	/* size: 56, cachelines: 1, members: 7 */
	/* last cacheline: 56 bytes */
};
/* Used at: /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/djpeg.c */
/* <1630> /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/jpeglib.h:203 */
struct jpeg_marker_struct {
	struct jpeg_marker_struct  *next;                /*     0     8 */
	unsigned char              marker;               /*     8     1 */

	/* XXX 3 bytes hole, try to pack */

	unsigned int               original_length;      /*    12     4 */
	unsigned int               data_length;          /*    16     4 */

	/* XXX 4 bytes hole, try to pack */

	unsigned char              *data;                /*    24     8 */

	/* size: 32, cachelines: 1, members: 5 */
	/* sum members: 25, holes: 2, sum holes: 7 */
	/* last cacheline: 32 bytes */
};
/* Used at: /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/wrppm.c */
/* <8f93> /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/jpegint.h:255 */
struct jpeg_inverse_dct {
	void **start_pass;                                                /*     0     8 */
	void **inverse_DCT[10];                                            /*     8    80 */

	/* size: 88, cachelines: 2, members: 2 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/wrppm.c */
/* <8db4> /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/jpegint.h:199 */
struct jpeg_d_coef_controller {
	void **start_input_pass;                                                /*     0     8 */
	void **consume_data;                                                /*     8     8 */
	void **start_output_pass;                                                /*    16     8 */
	void **decompress_data;                                                /*    24     8 */
	struct jvirt_barray_control **coef_arrays;       /*    32     8 */

	/* size: 40, cachelines: 1, members: 5 */
	/* last cacheline: 40 bytes */
};
/* Used at: /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/rdswitch.c */
/* <535f> /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/jpeglib.h:297 */
struct jpeg_compress_struct {
	struct jpeg_error_mgr      *err;                 /*     0     8 */
	struct jpeg_memory_mgr     *mem;                 /*     8     8 */
	struct jpeg_progress_mgr   *progress;            /*    16     8 */
	void *                     client_data;          /*    24     8 */
	int                        is_decompressor;      /*    32     4 */
	int                        global_state;         /*    36     4 */
	struct jpeg_destination_mgr *dest;               /*    40     8 */
	unsigned int               image_width;          /*    48     4 */
	unsigned int               image_height;         /*    52     4 */
	int                        input_components;     /*    56     4 */
	enum memfuzz_anonymous_enum_2 in_color_space;
	/* --- cacheline 1 boundary (64 bytes) --- */
	double                     input_gamma;          /*    64     8 */
	int                        data_precision;       /*    72     4 */
	int                        num_components;       /*    76     4 */
	enum memfuzz_anonymous_enum_2 jpeg_color_space;

	/* XXX 4 bytes hole, try to pack */

	struct {
		int                component_id;         /*    88     4 */
		int                component_index;      /*    92     4 */
		int                h_samp_factor;        /*    96     4 */
		int                v_samp_factor;        /*   100     4 */
		int                quant_tbl_no;         /*   104     4 */
		int                dc_tbl_no;            /*   108     4 */
		int                ac_tbl_no;            /*   112     4 */
		unsigned int       width_in_blocks;      /*   116     4 */
		unsigned int       height_in_blocks;     /*   120     4 */
		int                DCT_scaled_size;      /*   124     4 */
		/* --- cacheline 2 boundary (128 bytes) --- */
		unsigned int       downsampled_width;    /*   128     4 */
		unsigned int       downsampled_height;   /*   132     4 */
		int                component_needed;     /*   136     4 */
		int                MCU_width;            /*   140     4 */
		int                MCU_height;           /*   144     4 */
		int                MCU_blocks;           /*   148     4 */
		int                MCU_sample_width;     /*   152     4 */
		int                last_col_width;       /*   156     4 */
		int                last_row_height;      /*   160     4 */

		/* XXX 4 bytes hole, try to pack */

		struct {
			unsigned short quantval[64];     /*   168   128 */
			/* --- cacheline 4 boundary (256 bytes) was 40 bytes ago --- */
			int        sent_table;           /*   296     4 */
		} *quant_table; /*   168     8 */
		void *             dct_table;            /*   176     8 */
	} *comp_info; /*    88     8 */
	struct {
		unsigned short     quantval[64];         /*    96   128 */
		int                sent_table;           /*   224     4 */
	} *quant_tbl_ptrs[4]; /*    96    32 */
	struct {
		unsigned char      bits[17];             /*   128    17 */
		unsigned char      huffval[256];         /*   145   256 */

		/* XXX 3 bytes hole, try to pack */

		/* --- cacheline 6 boundary (384 bytes) was 20 bytes ago --- */
		int                sent_table;           /*   404     4 */
	} *dc_huff_tbl_ptrs[4]; /*   128    32 */
	struct {
		unsigned char      bits[17];             /*   160    17 */
		unsigned char      huffval[256];         /*   177   256 */

		/* XXX 3 bytes hole, try to pack */

		int                sent_table;           /*   436     4 */
	} *ac_huff_tbl_ptrs[4]; /*   160    32 */
	unsigned char              arith_dc_L[16];       /*   192    16 */
	unsigned char              arith_dc_U[16];       /*   208    16 */
	unsigned char              arith_ac_K[16];       /*   224    16 */
	int                        num_scans;            /*   240     4 */

	/* XXX 4 bytes hole, try to pack */

	const struct {
		int          comps_in_scan;        /*   248     4 */
		int          component_index[4];   /*   252    16 */
		int          Ss;                   /*   268     4 */
		int          Se;                   /*   272     4 */
		int          Ah;                   /*   276     4 */
		int          Al;                   /*   280     4 */

		/* size: 36, cachelines: 1, members: 6 */
		/* last cacheline: 28 bytes */
	}; /*   248     8 */
	int                        raw_data_in;          /*   256     4 */
	int                        arith_code;           /*   260     4 */
	int                        optimize_coding;      /*   264     4 */
	int                        CCIR601_sampling;     /*   268     4 */
	int                        smoothing_factor;     /*   272     4 */
	enum memfuzz_anonymous_enum_0 dct_method;
	unsigned int               restart_interval;     /*   280     4 */
	int                        restart_in_rows;      /*   284     4 */
	int                        write_JFIF_header;    /*   288     4 */
	unsigned char              JFIF_major_version;   /*   292     1 */
	unsigned char              JFIF_minor_version;   /*   293     1 */
	unsigned char              density_unit;         /*   294     1 */

	/* XXX 1 byte hole, try to pack */

	unsigned short             X_density;            /*   296     2 */
	unsigned short             Y_density;            /*   298     2 */
	int                        write_Adobe_marker;   /*   300     4 */
	unsigned int               next_scanline;        /*   304     4 */
	int                        progressive_mode;     /*   308     4 */
	int                        max_h_samp_factor;    /*   312     4 */
	int                        max_v_samp_factor;    /*   316     4 */
	unsigned int               total_iMCU_rows;      /*   320     4 */
	int                        comps_in_scan1;        /*   324     4 */
	struct {
		int                component_id;         /*   328     4 */
		int                component_index;      /*   332     4 */
		int                h_samp_factor;        /*   336     4 */
		int                v_samp_factor;        /*   340     4 */
		int                quant_tbl_no;         /*   344     4 */
		int                dc_tbl_no;            /*   348     4 */
		int                ac_tbl_no;            /*   352     4 */
		unsigned int       width_in_blocks;      /*   356     4 */
		unsigned int       height_in_blocks;     /*   360     4 */
		int                DCT_scaled_size;      /*   364     4 */
		unsigned int       downsampled_width;    /*   368     4 */
		unsigned int       downsampled_height;   /*   372     4 */
		int                component_needed;     /*   376     4 */
		int                MCU_width;            /*   380     4 */
		int                MCU_height;           /*   384     4 */
		int                MCU_blocks;           /*   388     4 */
		int                MCU_sample_width;     /*   392     4 */
		int                last_col_width;       /*   396     4 */
		int                last_row_height;      /*   400     4 */

		/* XXX 4 bytes hole, try to pack */

		struct {
			unsigned short quantval[64];     /*   408   128 */
			/* --- cacheline 8 boundary (512 bytes) was 24 bytes ago --- */
			int        sent_table;           /*   536     4 */
		} *quant_table; /*   408     8 */
		void *             dct_table;            /*   416     8 */
	} *cur_comp_info[4]; /*   328    32 */
	unsigned int               MCUs_per_row;         /*   360     4 */
	unsigned int               MCU_rows_in_scan;     /*   364     4 */
	int                        blocks_in_MCU;        /*   368     4 */
	int                        MCU_membership[10];   /*   372    40 */
	int                        Ss1;                   /*   412     4 */
	int                        Se1;                   /*   416     4 */
	int                        Ah1;                   /*   420     4 */
	int                        Al1;                   /*   424     4 */

	/* XXX 4 bytes hole, try to pack */

	struct jpeg_comp_master    *master;              /*   432     8 */
	struct jpeg_c_main_controller *main;             /*   440     8 */
	struct jpeg_c_prep_controller *prep;             /*   448     8 */
	struct jpeg_c_coef_controller *coef;             /*   456     8 */
	struct jpeg_marker_writer  *marker;              /*   464     8 */
	struct jpeg_color_converter *cconvert;           /*   472     8 */
	struct jpeg_downsampler    *downsample;          /*   480     8 */
	struct jpeg_forward_dct    *fdct;                /*   488     8 */
	struct jpeg_entropy_encoder *entropy;            /*   496     8 */
	struct {
		int                comps_in_scan;        /*   504     4 */
		int                component_index[4];   /*   508    16 */
		int                Ss;                   /*   524     4 */
		int                Se;                   /*   528     4 */
		int                Ah;                   /*   532     4 */
		int                Al;                   /*   536     4 */
	} *script_space; /*   504     8 */
	int                        script_space_size;    /*   512     4 */

	/* size: 520, cachelines: 9, members: 65 */
	/* sum members: 503, holes: 4, sum holes: 13 */
	/* padding: 4 */
	/* last cacheline: 8 bytes */
};
/* Used at: /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/djpeg.c */
/* <cbb> /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/jpeglib.h:778 */
struct jpeg_progress_mgr {
	void **progress_monitor;                                                /*     0     8 */
	long int                   pass_counter;         /*     8     8 */
	long int                   pass_limit;           /*    16     8 */
	int                        completed_passes;     /*    24     4 */
	int                        total_passes;         /*    28     4 */

	/* size: 32, cachelines: 1, members: 5 */
	/* last cacheline: 32 bytes */
};
/* Used at: /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/djpeg.c */
/* <1a1d> /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/cdjpeg.h:90 */
struct cdjpeg_progress_mgr {
	struct jpeg_progress_mgr   pub;                  /*     0    32 */
	int                        completed_extra_passes; /*    32     4 */
	int                        total_extra_passes;   /*    36     4 */
	unsigned int               max_scans;            /*    40     4 */
	int                        report;               /*    44     4 */
	int                        percent_done;         /*    48     4 */

	/* size: 56, cachelines: 1, members: 6 */
	/* padding: 4 */
	/* last cacheline: 56 bytes */
};
/* Used at: /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/wrppm.c */
/* <8e38> /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/jpegint.h:209 */
struct jpeg_d_post_controller {
	void **start_pass;                                                /*     0     8 */
	void **post_process_data;                                                /*     8     8 */

	/* size: 16, cachelines: 1, members: 2 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/wrppm.c */
/* <9002> /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/jpegint.h:262 */
struct jpeg_upsampler {
	void **start_pass;                                                /*     0     8 */
	void **upsample;                                                /*     8     8 */
	int                        need_context_rows;    /*    16     4 */

	/* size: 24, cachelines: 1, members: 3 */
	/* padding: 4 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/wrppm.c */
/* <9081> /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/jpegint.h:281 */
struct jpeg_color_quantizer {
	void **start_pass;                                                /*     0     8 */
	void **color_quantize;                                                /*     8     8 */
	void **finish_pass;                                                /*    16     8 */
	void **new_color_map;                                                /*    24     8 */

	/* size: 32, cachelines: 1, members: 4 */
	/* last cacheline: 32 bytes */
};
/* Used at: /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/djpeg.c */
/* <1a7e> /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/cdjpeg.h:51 */
struct djpeg_dest_struct {
	void **start_output;                                                /*     0     8 */
	void **put_pixel_rows;                                                /*     8     8 */
	void **finish_output;                                                /*    16     8 */
	void **calc_buffer_dimensions;                                                /*    24     8 */
	struct _IO_FILE            *output_file;         /*    32     8 */
	unsigned char              **buffer;             /*    40     8 */
	unsigned int               buffer_height;        /*    48     4 */

	/* size: 56, cachelines: 1, members: 7 */
	/* padding: 4 */
	/* last cacheline: 56 bytes */
};
/* Used at: /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/wrppm.c */
/* <8ccc> /home/youwei/MemFuzz/Product/libjpeg/master/src_raw/jpegint.h:161 */
struct jpeg_decomp_master {
	void **prepare_for_output_pass;                                                /*     0     8 */
	void **finish_output_pass;                                                /*     8     8 */
	int                        is_dummy_pass;        /*    16     4 */
	unsigned int               first_iMCU_col;       /*    20     4 */
	unsigned int               last_iMCU_col;        /*    24     4 */
	unsigned int               first_MCU_col[10];    /*    28    40 */
	/* --- cacheline 1 boundary (64 bytes) was 4 bytes ago --- */
	unsigned int               last_MCU_col[10];     /*    68    40 */
	int                        jinit_upsampler_no_alloc; /*   108     4 */
	unsigned int               last_good_iMCU_row;   /*   112     4 */

	/* size: 120, cachelines: 2, members: 9 */
	/* padding: 4 */
	/* last cacheline: 56 bytes */
};
#endif
