#ifndef _MEMFUZZ_STRUCT_H_
#define _MEMFUZZ_STRUCT_H_
#include <pthread.h>
/*Add necessary header here to avoid compile problems*/
/*Struct Declaration Begin*/
struct dircnt;
struct opj_prec;
struct opj_image_comptparm;
struct opj_image;
struct opj_image_comp;
struct img_folder;
struct opj_dparameters;
struct opj_decompress_params;
struct opj_option;
struct opj_codestream_index;
struct opj_marker_info;
struct opj_tile_index;
struct opj_tp_index;
struct opj_packet_info;
union memfuzz_anonymous_struct_0;
union memfuzz_anonymous_struct_1;
struct opj_poc;
struct opj_cparameters;
struct pnm_header;
struct raw_cparameters;
struct raw_comp_cparameters;
struct memfuzz_anonymous_struct_2;
struct memfuzz_anonymous_struct_3;
struct opj_codestream_info;
struct opj_tile_info;
struct opj_tp_info;
struct opj_mutex_t;
struct opj_cond_t;
struct opj_thread_t;
struct memfuzz_anonymous_struct_11;
struct opj_thread_pool_t;
struct memfuzz_anonymous_struct_12;
struct opj_job_list_t;
struct memfuzz_anonymous_struct_13;
struct opj_tls_t;
struct opj_worker_thread_list_t;
struct opj_stream_private;
struct opj_event_mgr;
struct __va_list_tag;
struct opj_ppx_struct;
struct opj_tcp;
struct opj_stepsize;
struct opj_tccp;
struct opj_mct_data;
struct opj_simple_mcc_decorrelation_data;
struct opj_decoding_param;
struct opj_encoding_param;
union memfuzz_anonymous_struct_14;
struct opj_cp;
struct opj_decompression;
struct opj_compression;
union memfuzz_anonymous_struct_15;
struct opj_codec_private;
struct opj_tile_v2_info;
struct opj_codestream_info_v2;
struct opj_tccp_info;
struct j2k_prog_order;
struct opj_dec_memory_marker_handler;
struct opj_j2k_dec;
struct opj_j2k_enc;
union memfuzz_anonymous_struct_16;
struct opj_j2k;
union memfuzz_anonymous_struct_17;
struct opj_procedure_list;
struct opj_tcd;
struct opj_tcd_image;
struct opj_tcd_tile;
struct opj_tcd_tilecomp;
struct opj_tcd_band;
struct opj_tcd_resolution;
union memfuzz_anonymous_struct_18;
struct opj_tcd_precinct;
struct opj_tcd_cblk_enc;
struct opj_tcd_layer;
struct opj_tcd_pass;
struct opj_tcd_cblk_dec;
struct opj_tcd_seg;
struct opj_tcd_seg_data_chunk;
struct opj_tgt_tree;
struct opj_tgt_node;
struct opj_tcd_marker_info;
struct opj_jp2_header_handler;
union memfuzz_anonymous_struct_19;
union memfuzz_anonymous_struct_20;
union memfuzz_anonymous_struct_21;
struct opj_jp2_comps;
struct opj_jp2_color;
struct opj_jp2;
struct opj_jp2_cdef;
struct opj_jp2_cdef_info;
struct opj_jp2_pclr;
struct opj_jp2_cmap_comp;
struct opj_jp2_box;
struct opj_jp2_img_header_writer_handler;
struct opj_pi_iterator;
struct opj_pi_comp;
struct opj_pi_resolution;
union memfuzz_anonymous_struct_22;
union memfuzz_anonymous_struct_23;
union memfuzz_anonymous_struct_24;
struct opj_t2;
struct opj_bio;
struct dwt_local;
struct memfuzz_anonymous_struct_25;
struct memfuzz_anonymous_struct_26;
struct memfuzz_anonymous_struct_27;
struct memfuzz_anonymous_struct_28;
union memfuzz_anonymous_struct_29;
struct v8dwt_local;
struct memfuzz_anonymous_struct_30;
struct memfuzz_anonymous_struct_31;
union memfuzz_anonymous_struct_32;
union memfuzz_anonymous_struct_33;
struct opj_mqc;
struct opj_t1;
struct opj_mqc_state;
struct memfuzz_anonymous_struct_34;
union memfuzz_anonymous_struct_35;
struct memfuzz_anonymous_struct_36;
union memfuzz_anonymous_struct_37;
union memfuzz_anonymous_struct_38;
union memfuzz_anonymous_struct_39;
struct opj_sparse_array_int32;
/*Enumeration Definition Begin*/
enum opj_prec_mode {
		OPJ_PREC_MODE_CLIP  = 0,
		OPJ_PREC_MODE_SCALE = 1,
	};
enum COLOR_SPACE {
		OPJ_CLRSPC_UNKNOWN     = 4294967295,
		OPJ_CLRSPC_UNSPECIFIED = 0,
		OPJ_CLRSPC_SRGB        = 1,
		OPJ_CLRSPC_GRAY        = 2,
		OPJ_CLRSPC_SYCC        = 3,
		OPJ_CLRSPC_EYCC        = 4,
		OPJ_CLRSPC_CMYK        = 5,
	};
enum PROG_ORDER {
		OPJ_PROG_UNKNOWN = 4294967295,
		OPJ_LRCP         = 0,
		OPJ_RLCP         = 1,
		OPJ_RPCL         = 2,
		OPJ_PCRL         = 3,
		OPJ_CPRL         = 4,
	};
enum CINEMA_MODE {
		OPJ_OFF         = 0,
		OPJ_CINEMA2K_24 = 1,
		OPJ_CINEMA2K_48 = 2,
		OPJ_CINEMA4K_24 = 3,
	};
enum RSIZ_CAPABILITIES {
		OPJ_STD_RSIZ = 0,
		OPJ_CINEMA2K = 3,
		OPJ_CINEMA4K = 4,
		OPJ_MCT      = 33024,
	};
enum MCT_ELEMENT_TYPE {
		MCT_TYPE_INT16  = 0,
		MCT_TYPE_INT32  = 1,
		MCT_TYPE_FLOAT  = 2,
		MCT_TYPE_DOUBLE = 3,
	};
enum MCT_ARRAY_TYPE {
		MCT_TYPE_DEPENDENCY    = 0,
		MCT_TYPE_DECORRELATION = 1,
		MCT_TYPE_OFFSET        = 2,
	};
enum memfuzz_anonymous_enum_0 {
		OPJWTS_OK    = 0,
		OPJWTS_STOP  = 1,
		OPJWTS_ERROR = 2,
	};
/*Struct Definition Begin*/
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/opj_decompress.c */
/* <1da> /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/opj_decompress.c:81 */
struct dircnt {
	char                       *filename_buf;        /*     0     8 */
	char                       **filename;           /*     8     8 */

	/* size: 16, cachelines: 1, members: 2 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/opj_decompress.c */
/* <231> /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/opj_decompress.c:106 */
struct opj_prec {
	unsigned int               prec;                 /*     0     4 */
	enum opj_prec_mode         mode;                 /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/opj_decompress.c */
/* <26e> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.h:728 */
struct opj_image_comptparm {
	unsigned int               dx;                   /*     0     4 */
	unsigned int               dy;                   /*     4     4 */
	unsigned int               w;                    /*     8     4 */
	unsigned int               h;                    /*    12     4 */
	unsigned int               x0;                   /*    16     4 */
	unsigned int               y0;                   /*    20     4 */
	unsigned int               prec;                 /*    24     4 */
	unsigned int               bpp;                  /*    28     4 */
	unsigned int               sgnd;                 /*    32     4 */

	/* size: 36, cachelines: 1, members: 9 */
	/* last cacheline: 36 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/opj_decompress.c */
/* <d87> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.h:703 */
struct opj_image {
	unsigned int               x0;                   /*     0     4 */
	unsigned int               y0;                   /*     4     4 */
	unsigned int               x1;                   /*     8     4 */
	unsigned int               y1;                   /*    12     4 */
	unsigned int               numcomps;             /*    16     4 */
	enum COLOR_SPACE           color_space;          /*    20     4 */
	struct opj_image_comp      *comps;               /*    24     8 */
	unsigned char              *icc_profile_buf;     /*    32     8 */
	unsigned int               icc_profile_len;      /*    40     4 */

	/* size: 48, cachelines: 1, members: 9 */
	/* padding: 4 */
	/* last cacheline: 48 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/opj_decompress.c */
/* <e23> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.h:671 */
struct opj_image_comp {
	unsigned int               dx;                   /*     0     4 */
	unsigned int               dy;                   /*     4     4 */
	unsigned int               w;                    /*     8     4 */
	unsigned int               h;                    /*    12     4 */
	unsigned int               x0;                   /*    16     4 */
	unsigned int               y0;                   /*    20     4 */
	unsigned int               prec;                 /*    24     4 */
	unsigned int               bpp;                  /*    28     4 */
	unsigned int               sgnd;                 /*    32     4 */
	unsigned int               resno_decoded;        /*    36     4 */
	unsigned int               factor;               /*    40     4 */

	/* XXX 4 bytes hole, try to pack */

	int                        *data;                /*    48     8 */
	unsigned short             alpha;                /*    56     2 */

	/* size: 64, cachelines: 1, members: 13 */
	/* sum members: 54, holes: 1, sum holes: 4 */
	/* padding: 6 */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/opj_decompress.c */
/* <fb4> /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/opj_decompress.c:89 */
struct img_folder {
	char                       *imgdirpath;          /*     0     8 */
	char                       *out_format;          /*     8     8 */
	char                       set_imgdir;           /*    16     1 */
	char                       set_out_format;       /*    17     1 */

	/* size: 24, cachelines: 1, members: 4 */
	/* padding: 6 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/opj_decompress.c */
/* <1130> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.h:546 */
struct opj_dparameters {
	unsigned int               cp_reduce;            /*     0     4 */
	unsigned int               cp_layer;             /*     4     4 */
	char                       infile[4096];         /*     8  4096 */
	/* --- cacheline 64 boundary (4096 bytes) was 8 bytes ago --- */
	char                       outfile[4096];        /*  4104  4096 */
	/* --- cacheline 128 boundary (8192 bytes) was 8 bytes ago --- */
	int                        decod_format;         /*  8200     4 */
	int                        cod_format;           /*  8204     4 */
	unsigned int               DA_x0;                /*  8208     4 */
	unsigned int               DA_x1;                /*  8212     4 */
	unsigned int               DA_y0;                /*  8216     4 */
	unsigned int               DA_y1;                /*  8220     4 */
	int                        m_verbose;            /*  8224     4 */
	unsigned int               tile_index;           /*  8228     4 */
	unsigned int               nb_tile_to_decode;    /*  8232     4 */
	int                        jpwl_correct;         /*  8236     4 */
	int                        jpwl_exp_comps;       /*  8240     4 */
	int                        jpwl_max_tiles;       /*  8244     4 */
	unsigned int               flags;                /*  8248     4 */

	/* size: 8252, cachelines: 129, members: 17 */
	/* last cacheline: 60 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/opj_decompress.c */
/* <ffd> /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/opj_decompress.c:111 */
struct opj_decompress_params {
	struct opj_dparameters     core;                 /*     0  8252 */
	/* --- cacheline 128 boundary (8192 bytes) was 60 bytes ago --- */
	char                       infile[4096];         /*  8252  4096 */
	/* --- cacheline 192 boundary (12288 bytes) was 60 bytes ago --- */
	char                       outfile[4096];        /* 12348  4096 */
	/* --- cacheline 256 boundary (16384 bytes) was 60 bytes ago --- */
	int                        decod_format;         /* 16444     4 */
	/* --- cacheline 257 boundary (16448 bytes) --- */
	int                        cod_format;           /* 16448     4 */
	char                       indexfilename[4096];  /* 16452  4096 */
	/* --- cacheline 321 boundary (20544 bytes) was 4 bytes ago --- */
	unsigned int               DA_x0;                /* 20548     4 */
	unsigned int               DA_x1;                /* 20552     4 */
	unsigned int               DA_y0;                /* 20556     4 */
	unsigned int               DA_y1;                /* 20560     4 */
	int                        m_verbose;            /* 20564     4 */
	unsigned int               tile_index;           /* 20568     4 */
	unsigned int               nb_tile_to_decode;    /* 20572     4 */
	struct opj_prec            *precision;           /* 20576     8 */
	unsigned int               nb_precision;         /* 20584     4 */
	int                        force_rgb;            /* 20588     4 */
	int                        upsample;             /* 20592     4 */
	int                        split_pnm;            /* 20596     4 */
	int                        num_threads;          /* 20600     4 */
	int                        quiet;                /* 20604     4 */
	/* --- cacheline 322 boundary (20608 bytes) --- */
	unsigned int               numcomps;             /* 20608     4 */

	/* XXX 4 bytes hole, try to pack */

	unsigned int               *comps_indices;       /* 20616     8 */

	/* size: 20624, cachelines: 323, members: 22 */
	/* sum members: 20620, holes: 1, sum holes: 4 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/opj_decompress.c */
/* <145a> /home/liu2598/Product/openjpeg/master/src_raw/src/bin/common/opj_getopt.h:6 */
struct opj_option {
	char                       *name;                /*     0     8 */
	int                        has_arg;              /*     8     4 */

	/* XXX 4 bytes hole, try to pack */

	int                        *flag;                /*    16     8 */
	int                        val;                  /*    24     4 */

	/* size: 32, cachelines: 1, members: 4 */
	/* sum members: 24, holes: 1, sum holes: 4 */
	/* padding: 4 */
	/* last cacheline: 32 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/opj_decompress.c */
/* <1537> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.h:1031 */
struct opj_codestream_index {
	long int                   main_head_start;      /*     0     8 */
	long int                   main_head_end;        /*     8     8 */
	long unsigned int          codestream_size;      /*    16     8 */
	unsigned int               marknum;              /*    24     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_marker_info     *marker;              /*    32     8 */
	unsigned int               maxmarknum;           /*    40     4 */
	unsigned int               nb_of_tiles;          /*    44     4 */
	struct opj_tile_index      *tile_index;          /*    48     8 */

	/* size: 56, cachelines: 1, members: 8 */
	/* sum members: 52, holes: 1, sum holes: 4 */
	/* last cacheline: 56 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/opj_decompress.c */
/* <15fc> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.h:776 */
struct opj_marker_info {
	unsigned short             type;                 /*     0     2 */

	/* XXX 6 bytes hole, try to pack */

	long int                   pos;                  /*     8     8 */
	int                        len;                  /*    16     4 */

	/* size: 24, cachelines: 1, members: 3 */
	/* sum members: 14, holes: 1, sum holes: 6 */
	/* padding: 4 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/opj_decompress.c */
/* <163e> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.h:999 */
struct opj_tile_index {
	unsigned int               tileno;               /*     0     4 */
	unsigned int               nb_tps;               /*     4     4 */
	unsigned int               current_nb_tps;       /*     8     4 */
	unsigned int               current_tpsno;        /*    12     4 */
	struct opj_tp_index        *tp_index;            /*    16     8 */
	unsigned int               marknum;              /*    24     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_marker_info     *marker;              /*    32     8 */
	unsigned int               maxmarknum;           /*    40     4 */
	unsigned int               nb_packet;            /*    44     4 */
	struct opj_packet_info     *packet_index;        /*    48     8 */

	/* size: 56, cachelines: 1, members: 10 */
	/* sum members: 52, holes: 1, sum holes: 4 */
	/* last cacheline: 56 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/opj_decompress.c */
/* <16db> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.h:986 */
struct opj_tp_index {
	long int                   start_pos;            /*     0     8 */
	long int                   end_header;           /*     8     8 */
	long int                   end_pos;              /*    16     8 */

	/* size: 24, cachelines: 1, members: 3 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/opj_decompress.c */
/* <171d> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.h:760 */
struct opj_packet_info {
	long int                   start_pos;            /*     0     8 */
	long int                   end_ph_pos;           /*     8     8 */
	long int                   end_pos;              /*    16     8 */
	double                     disto;                /*    24     8 */

	/* size: 32, cachelines: 1, members: 4 */
	/* last cacheline: 32 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/convert.c */
/* <3b8a> /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/convert.c:2568 */
union memfuzz_anonymous_struct_0 {
	short                      val;                /*     0     2 */
	signed char                vals[2];            /*     0     2 */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/convert.c */
/* <3baa> /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/convert.c:2592 */
union memfuzz_anonymous_struct_1 {
	unsigned short             val;                /*     0     2 */
	unsigned char              vals[2];            /*     0     2 */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/convert.c */
/* <423d> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.h:359 */
struct opj_poc {
	unsigned int               resno0;               /*     0     4 */
	unsigned int               compno0;              /*     4     4 */
	unsigned int               layno1;               /*     8     4 */
	unsigned int               resno1;               /*    12     4 */
	unsigned int               compno1;              /*    16     4 */
	unsigned int               layno0;               /*    20     4 */
	unsigned int               precno0;              /*    24     4 */
	unsigned int               precno1;              /*    28     4 */
	enum PROG_ORDER            prg1;                 /*    32     4 */
	enum PROG_ORDER            prg;                  /*    36     4 */
	char                       progorder[5];         /*    40     5 */

	/* XXX 3 bytes hole, try to pack */

	unsigned int               tile;                 /*    48     4 */
	int                        tx0;                  /*    52     4 */
	int                        tx1;                  /*    56     4 */
	int                        ty0;                  /*    60     4 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	int                        ty1;                  /*    64     4 */
	unsigned int               layS;                 /*    68     4 */
	unsigned int               resS;                 /*    72     4 */
	unsigned int               compS;                /*    76     4 */
	unsigned int               prcS;                 /*    80     4 */
	unsigned int               layE;                 /*    84     4 */
	unsigned int               resE;                 /*    88     4 */
	unsigned int               compE;                /*    92     4 */
	unsigned int               prcE;                 /*    96     4 */
	unsigned int               txS;                  /*   100     4 */
	unsigned int               txE;                  /*   104     4 */
	unsigned int               tyS;                  /*   108     4 */
	unsigned int               tyE;                  /*   112     4 */
	unsigned int               dx;                   /*   116     4 */
	unsigned int               dy;                   /*   120     4 */
	unsigned int               lay_t;                /*   124     4 */
	/* --- cacheline 2 boundary (128 bytes) --- */
	unsigned int               res_t;                /*   128     4 */
	unsigned int               comp_t;               /*   132     4 */
	unsigned int               prc_t;                /*   136     4 */
	unsigned int               tx0_t;                /*   140     4 */
	unsigned int               ty0_t;                /*   144     4 */

	/* size: 148, cachelines: 3, members: 36 */
	/* sum members: 145, holes: 1, sum holes: 3 */
	/* last cacheline: 20 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/convert.c */
/* <3ec3> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.h:387 */
struct opj_cparameters {
	int                        tile_size_on;         /*     0     4 */
	int                        cp_tx0;               /*     4     4 */
	int                        cp_ty0;               /*     8     4 */
	int                        cp_tdx;               /*    12     4 */
	int                        cp_tdy;               /*    16     4 */
	int                        cp_disto_alloc;       /*    20     4 */
	int                        cp_fixed_alloc;       /*    24     4 */
	int                        cp_fixed_quality;     /*    28     4 */
	int                        *cp_matrice;          /*    32     8 */
	char                       *cp_comment;          /*    40     8 */
	int                        csty;                 /*    48     4 */
	enum PROG_ORDER            prog_order;           /*    52     4 */
	struct opj_poc             POC[32];              /*    56  4736 */
	/* --- cacheline 74 boundary (4736 bytes) was 56 bytes ago --- */
	unsigned int               numpocs;              /*  4792     4 */
	int                        tcp_numlayers;        /*  4796     4 */
	/* --- cacheline 75 boundary (4800 bytes) --- */
	float                      tcp_rates[100];       /*  4800   400 */
	/* --- cacheline 81 boundary (5184 bytes) was 16 bytes ago --- */
	float                      tcp_distoratio[100];  /*  5200   400 */
	/* --- cacheline 87 boundary (5568 bytes) was 32 bytes ago --- */
	int                        numresolution;        /*  5600     4 */
	int                        cblockw_init;         /*  5604     4 */
	int                        cblockh_init;         /*  5608     4 */
	int                        mode;                 /*  5612     4 */
	int                        irreversible;         /*  5616     4 */
	int                        roi_compno;           /*  5620     4 */
	int                        roi_shift;            /*  5624     4 */
	int                        res_spec;             /*  5628     4 */
	/* --- cacheline 88 boundary (5632 bytes) --- */
	int                        prcw_init[33];        /*  5632   132 */
	/* --- cacheline 90 boundary (5760 bytes) was 4 bytes ago --- */
	int                        prch_init[33];        /*  5764   132 */
	/* --- cacheline 92 boundary (5888 bytes) was 8 bytes ago --- */
	char                       infile[4096];         /*  5896  4096 */
	/* --- cacheline 156 boundary (9984 bytes) was 8 bytes ago --- */
	char                       outfile[4096];        /*  9992  4096 */
	/* --- cacheline 220 boundary (14080 bytes) was 8 bytes ago --- */
	int                        index_on;             /* 14088     4 */
	char                       index[4096];          /* 14092  4096 */
	/* --- cacheline 284 boundary (18176 bytes) was 12 bytes ago --- */
	int                        image_offset_x0;      /* 18188     4 */
	int                        image_offset_y0;      /* 18192     4 */
	int                        subsampling_dx;       /* 18196     4 */
	int                        subsampling_dy;       /* 18200     4 */
	int                        decod_format;         /* 18204     4 */
	int                        cod_format;           /* 18208     4 */
	int                        jpwl_epc_on;          /* 18212     4 */
	int                        jpwl_hprot_MH;        /* 18216     4 */
	int                        jpwl_hprot_TPH_tileno[16]; /* 18220    64 */
	/* --- cacheline 285 boundary (18240 bytes) was 44 bytes ago --- */
	int                        jpwl_hprot_TPH[16];   /* 18284    64 */
	/* --- cacheline 286 boundary (18304 bytes) was 44 bytes ago --- */
	int                        jpwl_pprot_tileno[16]; /* 18348    64 */
	/* --- cacheline 287 boundary (18368 bytes) was 44 bytes ago --- */
	int                        jpwl_pprot_packno[16]; /* 18412    64 */
	/* --- cacheline 288 boundary (18432 bytes) was 44 bytes ago --- */
	int                        jpwl_pprot[16];       /* 18476    64 */
	/* --- cacheline 289 boundary (18496 bytes) was 44 bytes ago --- */
	int                        jpwl_sens_size;       /* 18540     4 */
	int                        jpwl_sens_addr;       /* 18544     4 */
	int                        jpwl_sens_range;      /* 18548     4 */
	int                        jpwl_sens_MH;         /* 18552     4 */
	int                        jpwl_sens_TPH_tileno[16]; /* 18556    64 */
	/* --- cacheline 290 boundary (18560 bytes) was 60 bytes ago --- */
	int                        jpwl_sens_TPH[16];    /* 18620    64 */
	/* --- cacheline 291 boundary (18624 bytes) was 60 bytes ago --- */
	enum CINEMA_MODE           cp_cinema;            /* 18684     4 */
	/* --- cacheline 292 boundary (18688 bytes) --- */
	int                        max_comp_size;        /* 18688     4 */
	enum RSIZ_CAPABILITIES     cp_rsiz;              /* 18692     4 */
	char                       tp_on;                /* 18696     1 */
	char                       tp_flag;              /* 18697     1 */
	char                       tcp_mct;              /* 18698     1 */

	/* XXX 1 byte hole, try to pack */

	int                        jpip_on;              /* 18700     4 */
	void *                     mct_data;             /* 18704     8 */
	int                        max_cs_size;          /* 18712     4 */
	unsigned short             rsiz;                 /* 18716     2 */

	/* size: 18720, cachelines: 293, members: 60 */
	/* sum members: 18717, holes: 1, sum holes: 1 */
	/* padding: 2 */
	/* last cacheline: 32 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/convert.c */
/* <46bf> /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/convert.c:1492 */
struct pnm_header {
	int                        width;                /*     0     4 */
	int                        height;               /*     4     4 */
	int                        maxval;               /*     8     4 */
	int                        depth;                /*    12     4 */
	int                        format;               /*    16     4 */
	char                       rgb;                  /*    20     1 */
	char                       rgba;                 /*    21     1 */
	char                       gray;                 /*    22     1 */
	char                       graya;                /*    23     1 */
	char                       bw;                   /*    24     1 */
	char                       ok;                   /*    25     1 */

	/* size: 28, cachelines: 1, members: 11 */
	/* padding: 2 */
	/* last cacheline: 28 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/convert.c */
/* <476d> /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/convert.h:52 */
struct raw_cparameters {
	int                        rawWidth;             /*     0     4 */
	int                        rawHeight;            /*     4     4 */
	int                        rawComp;              /*     8     4 */
	int                        rawBitDepth;          /*    12     4 */
	int                        rawSigned;            /*    16     4 */

	/* XXX 4 bytes hole, try to pack */

	struct raw_comp_cparameters *rawComps;           /*    24     8 */

	/* size: 32, cachelines: 1, members: 6 */
	/* sum members: 28, holes: 1, sum holes: 4 */
	/* last cacheline: 32 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/convert.c */
/* <47ce> /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/convert.h:42 */
struct raw_comp_cparameters {
	int                        dx;                   /*     0     4 */
	int                        dy;                   /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/convertbmp.c */
/* <6035> /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/convertbmp.c:48 */
typedef struct memfuzz_anonymous_struct_2 {
	unsigned short             bfType;               /*     0     2 */

	/* XXX 2 bytes hole, try to pack */

	unsigned int               bfSize;               /*     4     4 */
	unsigned short             bfReserved1;          /*     8     2 */
	unsigned short             bfReserved2;          /*    10     2 */
	unsigned int               bfOffBits;            /*    12     4 */

	/* size: 16, cachelines: 1, members: 5 */
	/* sum members: 14, holes: 1, sum holes: 2 */
	/* last cacheline: 16 bytes */
} OPJ_BITMAPFILEHEADER;
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/convertbmp.c */
/* <6081> /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/convertbmp.c:56 */
typedef struct memfuzz_anonymous_struct_3 {
	unsigned int               biSize;               /*     0     4 */
	unsigned int               biWidth;              /*     4     4 */
	unsigned int               biHeight;             /*     8     4 */
	unsigned short             biPlanes;             /*    12     2 */
	unsigned short             biBitCount;           /*    14     2 */
	unsigned int               biCompression;        /*    16     4 */
	unsigned int               biSizeImage;          /*    20     4 */
	unsigned int               biXpelsPerMeter;      /*    24     4 */
	unsigned int               biYpelsPerMeter;      /*    28     4 */
	unsigned int               biClrUsed;            /*    32     4 */
	unsigned int               biClrImportant;       /*    36     4 */
	unsigned int               biRedMask;            /*    40     4 */
	unsigned int               biGreenMask;          /*    44     4 */
	unsigned int               biBlueMask;           /*    48     4 */
	unsigned int               biAlphaMask;          /*    52     4 */
	unsigned int               biColorSpaceType;     /*    56     4 */
	unsigned char              biColorSpaceEP[36];   /*    60    36 */
	/* --- cacheline 1 boundary (64 bytes) was 32 bytes ago --- */
	unsigned int               biRedGamma;           /*    96     4 */
	unsigned int               biGreenGamma;         /*   100     4 */
	unsigned int               biBlueGamma;          /*   104     4 */
	unsigned int               biIntent;             /*   108     4 */
	unsigned int               biIccProfileData;     /*   112     4 */
	unsigned int               biIccProfileSize;     /*   116     4 */
	unsigned int               biReserved;           /*   120     4 */

	/* size: 124, cachelines: 2, members: 24 */
	/* last cacheline: 60 bytes */
} OPJ_BITMAPINFOHEADER;
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/index.c */
/* <66a4> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.h:845 */
struct opj_codestream_info {
	double                     D_max;                /*     0     8 */
	int                        packno;               /*     8     4 */
	int                        index_write;          /*    12     4 */
	int                        image_w;              /*    16     4 */
	int                        image_h;              /*    20     4 */
	enum PROG_ORDER            prog;                 /*    24     4 */
	int                        tile_x;               /*    28     4 */
	int                        tile_y;               /*    32     4 */
	int                        tile_Ox;              /*    36     4 */
	int                        tile_Oy;              /*    40     4 */
	int                        tw;                   /*    44     4 */
	int                        th;                   /*    48     4 */
	int                        numcomps;             /*    52     4 */
	int                        numlayers;            /*    56     4 */

	/* XXX 4 bytes hole, try to pack */

	/* --- cacheline 1 boundary (64 bytes) --- */
	int                        *numdecompos;         /*    64     8 */
	int                        marknum;              /*    72     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_marker_info     *marker;              /*    80     8 */
	int                        maxmarknum;           /*    88     4 */
	int                        main_head_start;      /*    92     4 */
	int                        main_head_end;        /*    96     4 */
	int                        codestream_size;      /*   100     4 */
	struct opj_tile_info       *tile;                /*   104     8 */

	/* size: 112, cachelines: 2, members: 22 */
	/* sum members: 104, holes: 2, sum holes: 8 */
	/* last cacheline: 48 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/index.c */
/* <6866> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.h:805 */
struct opj_tile_info {
	double                     *thresh;              /*     0     8 */
	int                        tileno;               /*     8     4 */
	int                        start_pos;            /*    12     4 */
	int                        end_header;           /*    16     4 */
	int                        end_pos;              /*    20     4 */
	int                        pw[33];               /*    24   132 */
	/* --- cacheline 2 boundary (128 bytes) was 28 bytes ago --- */
	int                        ph[33];               /*   156   132 */
	/* --- cacheline 4 boundary (256 bytes) was 32 bytes ago --- */
	int                        pdx[33];              /*   288   132 */
	/* --- cacheline 6 boundary (384 bytes) was 36 bytes ago --- */
	int                        pdy[33];              /*   420   132 */
	/* --- cacheline 8 boundary (512 bytes) was 40 bytes ago --- */
	struct opj_packet_info     *packet;              /*   552     8 */
	int                        numpix;               /*   560     4 */

	/* XXX 4 bytes hole, try to pack */

	double                     distotile;            /*   568     8 */
	/* --- cacheline 9 boundary (576 bytes) --- */
	int                        marknum;              /*   576     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_marker_info     *marker;              /*   584     8 */
	int                        maxmarknum;           /*   592     4 */
	int                        num_tps;              /*   596     4 */
	struct opj_tp_info         *tp;                  /*   600     8 */

	/* size: 608, cachelines: 10, members: 17 */
	/* sum members: 600, holes: 2, sum holes: 8 */
	/* last cacheline: 32 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/bin/jp2/index.c */
/* <69d0> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.h:789 */
struct opj_tp_info {
	int                        tp_start_pos;         /*     0     4 */
	int                        tp_end_header;        /*     4     4 */
	int                        tp_end_pos;           /*     8     4 */
	int                        tp_start_pack;        /*    12     4 */
	int                        tp_numpacks;          /*    16     4 */

	/* size: 20, cachelines: 1, members: 5 */
	/* last cacheline: 20 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/thread.c */
/* <c3c7> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/thread.c:309 */
struct opj_mutex_t {
	union {
		struct __pthread_mutex_s __data;         /*     0    40 */
		char               __size[40];           /*     0    40 */
		long int           __align;              /*     0     8 */
	} mutex; /*     0    40 */

	/* size: 40, cachelines: 1, members: 1 */
	/* last cacheline: 40 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/thread.c */
/* <c4e5> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/thread.c:344 */
struct opj_cond_t {
	union {
		struct __pthread_cond_s __data;          /*     0    48 */
		char               __size[48];           /*     0    48 */
		long long int      __align;              /*     0     8 */
	} cond; /*     0    48 */

	/* size: 48, cachelines: 1, members: 1 */
	/* last cacheline: 48 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/thread.c */
/* <c62f> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/thread.c:383 */
struct opj_thread_t {
	void **thread_fn;                                                /*     0     8 */
	void *                     user_data;            /*     8     8 */
	long unsigned int          thread;               /*    16     8 */

	/* size: 24, cachelines: 1, members: 3 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/thread.c */
/* <c69a> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/thread.c:498 */
typedef struct memfuzz_anonymous_struct_11 {
	int                        key;                  /*     0     4 */

	/* XXX 4 bytes hole, try to pack */

	void *                     value;                /*     8     8 */
	void **opj_free_func;                                                /*    16     8 */

	/* size: 24, cachelines: 1, members: 3 */
	/* sum members: 20, holes: 1, sum holes: 4 */
	/* last cacheline: 24 bytes */
} opj_tls_key_val_t;
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/thread.c */
/* <c6ed> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/thread.c:605 */
struct opj_thread_pool_t {
	struct {
		struct opj_thread_pool_t *tp;            /*     0     8 */
		struct opj_thread_t *thread;             /*     8     8 */
		int                marked_as_waiting;    /*    16     4 */

		/* XXX 4 bytes hole, try to pack */

		struct opj_mutex_t *mutex;               /*    24     8 */
		struct opj_cond_t  *cond;                /*    32     8 */
	} *worker_threads; /*     0     8 */
	int                        worker_threads_count; /*     8     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_cond_t          *cond;                /*    16     8 */
	struct opj_mutex_t         *mutex;               /*    24     8 */
	enum memfuzz_anonymous_enum_0 state;

	/* XXX 4 bytes hole, try to pack */

	struct opj_job_list_t      *job_queue;           /*    40     8 */
	int                        pending_jobs_count;   /*    48     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_worker_thread_list_t *waiting_worker_thread_list; /*    56     8 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	int                        waiting_worker_thread_count; /*    64     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_tls_t           *tls;                 /*    72     8 */
	int                        signaling_threshold;  /*    80     4 */

	/* size: 88, cachelines: 2, members: 11 */
	/* sum members: 68, holes: 4, sum holes: 16 */
	/* padding: 4 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/thread.c */
/* <c797> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/thread.c:578 */
typedef struct memfuzz_anonymous_struct_12 {
	struct opj_thread_pool_t   *tp;                  /*     0     8 */
	struct opj_thread_t        *thread;              /*     8     8 */
	int                        marked_as_waiting;    /*    16     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_mutex_t         *mutex;               /*    24     8 */
	struct opj_cond_t          *cond;                /*    32     8 */

	/* size: 40, cachelines: 1, members: 5 */
	/* sum members: 36, holes: 1, sum holes: 4 */
	/* last cacheline: 40 bytes */
} opj_worker_thread_t;
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/thread.c */
/* <c800> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/thread.c:593 */
struct opj_job_list_t {
	struct {
		void **job_fn;                                        /*     0     8 */
		void *             user_data;            /*     8     8 */
	} *job; /*     0     8 */
	struct opj_job_list_t      *next;                /*     8     8 */

	/* size: 16, cachelines: 1, members: 2 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/thread.c */
/* <c835> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/thread.c:573 */
typedef struct memfuzz_anonymous_struct_13 {
	void **job_fn;                                                /*     0     8 */
	void *                     user_data;            /*     8     8 */

	/* size: 16, cachelines: 1, members: 2 */
	/* last cacheline: 16 bytes */
} opj_worker_thread_job_t;
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/thread.c */
/* <c881> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/thread.c:504 */
struct opj_tls_t {
	struct {
		int                key;                  /*     0     4 */

		/* XXX 4 bytes hole, try to pack */

		void *             value;                /*     8     8 */
		void **opj_free_func;                                        /*    16     8 */
	} *key_val; /*     0     8 */
	int                        key_val_count;        /*     8     4 */

	/* size: 16, cachelines: 1, members: 2 */
	/* padding: 4 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/thread.c */
/* <c8c0> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/thread.c:599 */
struct opj_worker_thread_list_t {
	struct {
		struct opj_thread_pool_t *tp;            /*     0     8 */
		struct opj_thread_t *thread;             /*     8     8 */
		int                marked_as_waiting;    /*    16     4 */

		/* XXX 4 bytes hole, try to pack */

		struct opj_mutex_t *mutex;               /*    24     8 */
		struct opj_cond_t  *cond;                /*    32     8 */
	} *worker_thread; /*     0     8 */
	struct opj_worker_thread_list_t *next;           /*     8     8 */

	/* size: 16, cachelines: 1, members: 2 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/cio.c */
/* <cff4> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/cio.h:81 */
struct opj_stream_private {
	void *                     m_user_data;          /*     0     8 */
	void **m_free_user_data_fn;                                                /*     8     8 */
	long unsigned int          m_user_data_length;   /*    16     8 */
	void **m_read_fn;                                                /*    24     8 */
	void **m_write_fn;                                                /*    32     8 */
	void **m_skip_fn;                                                /*    40     8 */
	void **m_seek_fn;                                                /*    48     8 */
	unsigned char              *m_stored_data;       /*    56     8 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	unsigned char              *m_current_data;      /*    64     8 */
	void **m_opj_skip;                                                /*    72     8 */
	void **m_opj_seek;                                                /*    80     8 */
	long unsigned int          m_bytes_in_buffer;    /*    88     8 */
	long int                   m_byte_offset;        /*    96     8 */
	long unsigned int          m_buffer_size;        /*   104     8 */
	unsigned int               m_status;             /*   112     4 */

	/* size: 120, cachelines: 2, members: 15 */
	/* padding: 4 */
	/* last cacheline: 56 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/cio.c */
/* <d1da> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/event.h:50 */
struct opj_event_mgr {
	void *                     m_error_data;         /*     0     8 */
	void *                     m_warning_data;       /*     8     8 */
	void *                     m_info_data;          /*    16     8 */
	void **error_handler;                                                /*    24     8 */
	void **warning_handler;                                                /*    32     8 */
	void **info_handler;                                                /*    40     8 */

	/* size: 48, cachelines: 1, members: 6 */
	/* last cacheline: 48 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/event.c */
/* <df4b> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/event.c:123 */
struct __va_list_tag {
	unsigned int               gp_offset;            /*     0     4 */
	unsigned int               fp_offset;            /*     4     4 */
	void *                     overflow_arg_area;    /*     8     8 */
	void *                     reg_save_area;        /*    16     8 */

	/* size: 24, cachelines: 1, members: 4 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/image.c */
/* <e8a5> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.h:231 */
struct opj_ppx_struct {
	unsigned char              *m_data;              /*     0     8 */
	unsigned int               m_data_size;          /*     8     4 */

	/* size: 16, cachelines: 1, members: 2 */
	/* padding: 4 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/image.c */
/* <e8d7> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.h:241 */
struct opj_tcp {
	unsigned int               csty;                 /*     0     4 */
	enum PROG_ORDER            prg;                  /*     4     4 */
	unsigned int               numlayers;            /*     8     4 */
	unsigned int               num_layers_to_decode; /*    12     4 */
	unsigned int               mct;                  /*    16     4 */
	float                      rates[100];           /*    20   400 */
	/* --- cacheline 6 boundary (384 bytes) was 36 bytes ago --- */
	unsigned int               numpocs;              /*   420     4 */
	struct opj_poc             pocs[32];             /*   424  4736 */
	/* --- cacheline 80 boundary (5120 bytes) was 40 bytes ago --- */
	unsigned int               ppt_markers_count;    /*  5160     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_ppx_struct      *ppt_markers;         /*  5168     8 */
	unsigned char              *ppt_data;            /*  5176     8 */
	/* --- cacheline 81 boundary (5184 bytes) --- */
	unsigned char              *ppt_buffer;          /*  5184     8 */
	unsigned int               ppt_data_size;        /*  5192     4 */
	unsigned int               ppt_len;              /*  5196     4 */
	float                      distoratio[100];      /*  5200   400 */
	/* --- cacheline 87 boundary (5568 bytes) was 32 bytes ago --- */
	struct opj_tccp            *tccps;               /*  5600     8 */
	int                        m_current_tile_part_number; /*  5608     4 */
	unsigned int               m_nb_tile_parts;      /*  5612     4 */
	unsigned char              *m_data;              /*  5616     8 */
	unsigned int               m_data_size;          /*  5624     4 */

	/* XXX 4 bytes hole, try to pack */

	/* --- cacheline 88 boundary (5632 bytes) --- */
	double                     *mct_norms;           /*  5632     8 */
	float                      *m_mct_decoding_matrix; /*  5640     8 */
	float                      *m_mct_coding_matrix; /*  5648     8 */
	struct opj_mct_data        *m_mct_records;       /*  5656     8 */
	unsigned int               m_nb_mct_records;     /*  5664     4 */
	unsigned int               m_nb_max_mct_records; /*  5668     4 */
	struct opj_simple_mcc_decorrelation_data *m_mcc_records; /*  5672     8 */
	unsigned int               m_nb_mcc_records;     /*  5680     4 */
	unsigned int               m_nb_max_mcc_records; /*  5684     4 */
	unsigned int               cod:1;                /*  5688: 0  4 */
	unsigned int               ppt:1;                /*  5688: 1  4 */
	unsigned int               POC:1;                /*  5688: 2  4 */

	/* size: 5696, cachelines: 89, members: 32 */
	/* sum members: 5680, holes: 2, sum holes: 8 */
	/* sum bitfield members: 3 bits (0 bytes) */
	/* padding: 4 */
	/* bit_padding: 29 bits */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/image.c */
/* <eda2> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.h:165 */
struct opj_stepsize {
	int                        expn;                 /*     0     4 */
	int                        mant;                 /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/image.c */
/* <ece0> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.h:175 */
struct opj_tccp {
	unsigned int               csty;                 /*     0     4 */
	unsigned int               numresolutions;       /*     4     4 */
	unsigned int               cblkw;                /*     8     4 */
	unsigned int               cblkh;                /*    12     4 */
	unsigned int               cblksty;              /*    16     4 */
	unsigned int               qmfbid;               /*    20     4 */
	unsigned int               qntsty;               /*    24     4 */
	struct opj_stepsize        stepsizes[97];        /*    28   776 */
	/* --- cacheline 12 boundary (768 bytes) was 36 bytes ago --- */
	unsigned int               numgbits;             /*   804     4 */
	int                        roishift;             /*   808     4 */
	unsigned int               prcw[33];             /*   812   132 */
	/* --- cacheline 14 boundary (896 bytes) was 48 bytes ago --- */
	unsigned int               prch[33];             /*   944   132 */
	/* --- cacheline 16 boundary (1024 bytes) was 52 bytes ago --- */
	int                        m_dc_level_shift;     /*  1076     4 */

	/* size: 1080, cachelines: 17, members: 13 */
	/* last cacheline: 56 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/image.c */
/* <edfb> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.h:210 */
struct opj_mct_data {
	enum MCT_ELEMENT_TYPE      m_element_type;       /*     0     4 */
	enum MCT_ARRAY_TYPE        m_array_type;         /*     4     4 */
	unsigned int               m_index;              /*     8     4 */

	/* XXX 4 bytes hole, try to pack */

	unsigned char              *m_data;              /*    16     8 */
	unsigned int               m_data_size;          /*    24     4 */

	/* size: 32, cachelines: 1, members: 5 */
	/* sum members: 24, holes: 1, sum holes: 4 */
	/* padding: 4 */
	/* last cacheline: 32 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/image.c */
/* <ee66> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.h:222 */
struct opj_simple_mcc_decorrelation_data {
	unsigned int               m_index;              /*     0     4 */
	unsigned int               m_nb_comps;           /*     4     4 */
	struct opj_mct_data        *m_decorrelation_array; /*     8     8 */
	struct opj_mct_data        *m_offset_array;      /*    16     8 */
	unsigned int               m_is_irreversible:1;  /*    24: 0  4 */

	/* size: 32, cachelines: 1, members: 5 */
	/* padding: 4 */
	/* bit_padding: 31 bits */
	/* last cacheline: 32 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/image.c */
/* <eec5> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.h:335 */
struct opj_decoding_param {
	unsigned int               m_reduce;             /*     0     4 */
	unsigned int               m_layer;              /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/image.c */
/* <eef5> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.h:315 */
struct opj_encoding_param {
	unsigned int               m_max_comp_size;      /*     0     4 */
	int                        m_tp_pos;             /*     4     4 */
	int                        *m_matrice;           /*     8     8 */
	unsigned char              m_tp_flag;            /*    16     1 */

	/* Bitfield combined with previous fields */

	unsigned int               m_disto_alloc:1;      /*    16: 8  4 */
	unsigned int               m_fixed_alloc:1;      /*    16: 9  4 */
	unsigned int               m_fixed_quality:1;    /*    16:10  4 */
	unsigned int               m_tp_on:1;            /*    16:11  4 */

	/* size: 24, cachelines: 1, members: 8 */
	/* padding: 4 */
	/* bit_padding: 20 bits */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/image.c */
/* <e82d> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.h:395 */
union memfuzz_anonymous_struct_14 {
	struct opj_decoding_param  m_dec;              /*     0     8 */
	struct opj_encoding_param  m_enc;              /*     0    24 */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/image.c */
/* <e713> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.h:347 */
struct opj_cp {
	unsigned short             rsiz;                 /*     0     2 */

	/* XXX 2 bytes hole, try to pack */

	unsigned int               tx0;                  /*     4     4 */
	unsigned int               ty0;                  /*     8     4 */
	unsigned int               tdx;                  /*    12     4 */
	unsigned int               tdy;                  /*    16     4 */

	/* XXX 4 bytes hole, try to pack */

	char                       *comment;             /*    24     8 */
	unsigned int               tw;                   /*    32     4 */
	unsigned int               th;                   /*    36     4 */
	unsigned int               ppm_markers_count;    /*    40     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_ppx_struct      *ppm_markers;         /*    48     8 */
	unsigned char              *ppm_data;            /*    56     8 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	unsigned int               ppm_len;              /*    64     4 */
	unsigned int               ppm_data_read;        /*    68     4 */
	unsigned char              *ppm_data_current;    /*    72     8 */
	unsigned char              *ppm_buffer;          /*    80     8 */
	unsigned char              *ppm_data_first;      /*    88     8 */
	unsigned int               ppm_data_size;        /*    96     4 */
	int                        ppm_store;            /*   100     4 */
	int                        ppm_previous;         /*   104     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_tcp             *tcps;                /*   112     8 */
	union {
		struct opj_decoding_param m_dec;         /*   120     8 */
		struct opj_encoding_param m_enc;         /*   120    24 */
	} m_specific_param;                              /*   120    24 */
	/* --- cacheline 2 boundary (128 bytes) was 16 bytes ago --- */
	unsigned int               ppm:1;                /*   144: 0  4 */
	unsigned int               m_is_decoder:1;       /*   144: 1  4 */
	unsigned int               allow_different_bit_depth_sign:1; /*   144: 2  4 */

	/* size: 152, cachelines: 3, members: 24 */
	/* sum members: 130, holes: 4, sum holes: 14 */
	/* sum bitfield members: 3 bits (0 bytes) */
	/* padding: 4 */
	/* bit_padding: 29 bits */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.c */
/* <f136> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/opj_codec.h:48 */
struct opj_decompression {
	void **opj_read_header;                                                /*     0     8 */
	void **opj_decode;                                                /*     8     8 */
	void **opj_read_tile_header;                                                /*    16     8 */
	void **opj_decode_tile_data;                                                /*    24     8 */
	void **opj_end_decompress;                                                /*    32     8 */
	void **opj_destroy;                                                /*    40     8 */
	void **opj_setup_decoder;                                                /*    48     8 */
	void **opj_set_decode_area;                                                /*    56     8 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	void **opj_get_decoded_tile;                                                /*    64     8 */
	void **opj_set_decoded_resolution_factor;                                                /*    72     8 */
	void **opj_set_decoded_components;                                                /*    80     8 */

	/* size: 88, cachelines: 2, members: 11 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.c */
/* <f8d4> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/opj_codec.h:124 */
struct opj_compression {
	void **opj_start_compress;                                                /*     0     8 */
	void **opj_encode;                                                /*     8     8 */
	void **opj_write_tile;                                                /*    16     8 */
	void **opj_end_compress;                                                /*    24     8 */
	void **opj_destroy;                                                /*    32     8 */
	void **opj_setup_encoder;                                                /*    40     8 */
	void **opj_encoder_set_extra_options;                                                /*    48     8 */

	/* size: 56, cachelines: 1, members: 7 */
	/* last cacheline: 56 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.c */
/* <f0c4> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/opj_codec.h:44 */
union memfuzz_anonymous_struct_15 {
	struct opj_decompression   m_decompression;    /*     0    88 */
	struct opj_compression     m_compression;      /*     0    56 */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.c */
/* <f0b0> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/opj_codec.h:42 */
struct opj_codec_private {
	union {
		struct opj_decompression m_decompression; /*     0    88 */
		struct opj_compression m_compression;    /*     0    56 */
	} m_codec_data;                                  /*     0    88 */
	/* --- cacheline 1 boundary (64 bytes) was 24 bytes ago --- */
	void *                     m_codec;              /*    88     8 */
	struct opj_event_mgr       m_event_mgr;          /*    96    48 */
	/* --- cacheline 2 boundary (128 bytes) was 16 bytes ago --- */
	int                        is_decompressor;      /*   144     4 */

	/* XXX 4 bytes hole, try to pack */

	void **opj_dump_codec;                                                /*   152     8 */
	void **opj_get_codec_info;                                                /*   160     8 */
	void **opj_get_codec_index;                                                /*   168     8 */
	void **opj_set_threads;                                                /*   176     8 */

	/* size: 184, cachelines: 3, members: 8 */
	/* sum members: 180, holes: 1, sum holes: 4 */
	/* last cacheline: 56 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.c */
/* <1021b> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.h:935 */
struct opj_tile_v2_info {
	int                        tileno;               /*     0     4 */
	unsigned int               csty;                 /*     4     4 */
	enum PROG_ORDER            prg;                  /*     8     4 */
	unsigned int               numlayers;            /*    12     4 */
	unsigned int               mct;                  /*    16     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_tccp_info       *tccp_info;           /*    24     8 */

	/* size: 32, cachelines: 1, members: 6 */
	/* sum members: 28, holes: 1, sum holes: 4 */
	/* last cacheline: 32 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.c */
/* <10190> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.h:956 */
struct opj_codestream_info_v2 {
	unsigned int               tx0;                  /*     0     4 */
	unsigned int               ty0;                  /*     4     4 */
	unsigned int               tdx;                  /*     8     4 */
	unsigned int               tdy;                  /*    12     4 */
	unsigned int               tw;                   /*    16     4 */
	unsigned int               th;                   /*    20     4 */
	unsigned int               nbcomps;              /*    24     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_tile_v2_info    m_default_tile_info;  /*    32    32 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	struct opj_tile_v2_info    *tile_info;           /*    64     8 */

	/* size: 72, cachelines: 2, members: 9 */
	/* sum members: 68, holes: 1, sum holes: 4 */
	/* last cacheline: 8 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.c */
/* <10284> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/openjpeg.h:900 */
struct opj_tccp_info {
	unsigned int               compno;               /*     0     4 */
	unsigned int               csty;                 /*     4     4 */
	unsigned int               numresolutions;       /*     8     4 */
	unsigned int               cblkw;                /*    12     4 */
	unsigned int               cblkh;                /*    16     4 */
	unsigned int               cblksty;              /*    20     4 */
	unsigned int               qmfbid;               /*    24     4 */
	unsigned int               qntsty;               /*    28     4 */
	unsigned int               stepsizes_mant[97];   /*    32   388 */
	/* --- cacheline 6 boundary (384 bytes) was 36 bytes ago --- */
	unsigned int               stepsizes_expn[97];   /*   420   388 */
	/* --- cacheline 12 boundary (768 bytes) was 40 bytes ago --- */
	unsigned int               numgbits;             /*   808     4 */
	int                        roishift;             /*   812     4 */
	unsigned int               prcw[33];             /*   816   132 */
	/* --- cacheline 14 boundary (896 bytes) was 52 bytes ago --- */
	unsigned int               prch[33];             /*   948   132 */

	/* size: 1080, cachelines: 17, members: 14 */
	/* last cacheline: 56 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <1173e> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c:1321 */
struct j2k_prog_order {
	enum PROG_ORDER            enum_prog;            /*     0     4 */
	char                       str_prog[5];          /*     4     5 */

	/* size: 12, cachelines: 1, members: 2 */
	/* padding: 3 */
	/* last cacheline: 12 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <118e2> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c:1369 */
struct opj_dec_memory_marker_handler {
	unsigned int               id;                   /*     0     4 */
	unsigned int               states;               /*     4     4 */
	void **handler;                                                /*     8     8 */

	/* size: 16, cachelines: 1, members: 3 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <11a44> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.h:457 */
struct opj_j2k_dec {
	unsigned int               m_state;              /*     0     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_tcp             *m_default_tcp;       /*     8     8 */
	unsigned char              *m_header_data;       /*    16     8 */
	unsigned int               m_header_data_size;   /*    24     4 */
	unsigned int               m_sot_length;         /*    28     4 */
	unsigned int               m_start_tile_x;       /*    32     4 */
	unsigned int               m_start_tile_y;       /*    36     4 */
	unsigned int               m_end_tile_x;         /*    40     4 */
	unsigned int               m_end_tile_y;         /*    44     4 */
	int                        m_tile_ind_to_dec;    /*    48     4 */

	/* XXX 4 bytes hole, try to pack */

	long int                   m_last_sot_read_pos;  /*    56     8 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	int                        m_last_tile_part;     /*    64     4 */
	unsigned int               m_numcomps_to_decode; /*    68     4 */
	unsigned int               *m_comps_indices_to_decode; /*    72     8 */
	unsigned int               m_can_decode:1;       /*    80: 0  4 */
	unsigned int               m_discard_tiles:1;    /*    80: 1  4 */
	unsigned int               m_skip_data:1;        /*    80: 2  4 */
	unsigned int               m_nb_tile_parts_correction_checked:1; /*    80: 3  4 */
	unsigned int               m_nb_tile_parts_correction:1; /*    80: 4  4 */

	/* size: 88, cachelines: 2, members: 19 */
	/* sum members: 72, holes: 2, sum holes: 8 */
	/* sum bitfield members: 5 bits (0 bytes) */
	/* padding: 4 */
	/* bit_padding: 27 bits */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <12225> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.h:499 */
struct opj_j2k_enc {
	unsigned int               m_current_poc_tile_part_number; /*     0     4 */
	unsigned int               m_current_tile_part_number; /*     4     4 */
	int                        m_TLM;                /*     8     4 */
	int                        m_Ttlmi_is_byte;      /*    12     4 */
	long int                   m_tlm_start;          /*    16     8 */
	unsigned char              *m_tlm_sot_offsets_buffer; /*    24     8 */
	unsigned char              *m_tlm_sot_offsets_current; /*    32     8 */
	unsigned int               m_total_tile_parts;   /*    40     4 */

	/* XXX 4 bytes hole, try to pack */

	unsigned char              *m_encoded_tile_data; /*    48     8 */
	unsigned int               m_encoded_tile_size;  /*    56     4 */

	/* XXX 4 bytes hole, try to pack */

	/* --- cacheline 1 boundary (64 bytes) --- */
	unsigned char              *m_header_tile_data;  /*    64     8 */
	unsigned int               m_header_tile_data_size; /*    72     4 */
	int                        m_PLT;                /*    76     4 */
	unsigned int               m_reserved_bytes_for_PLT; /*    80     4 */

	/* size: 88, cachelines: 2, members: 14 */
	/* sum members: 76, holes: 2, sum holes: 8 */
	/* padding: 4 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <11972> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.h:562 */
union memfuzz_anonymous_struct_16 {
	struct opj_j2k_dec         m_decoder;          /*     0    88 */
	struct opj_j2k_enc         m_encoder;          /*     0    88 */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <1194e> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.h:557 */
struct opj_j2k {
	int                        m_is_decoder;         /*     0     4 */

	/* XXX 4 bytes hole, try to pack */

	union {
		struct opj_j2k_dec m_decoder;            /*     8    88 */
		struct opj_j2k_enc m_encoder;            /*     8    88 */
	} m_specific_param;                              /*     8    88 */
	/* --- cacheline 1 boundary (64 bytes) was 32 bytes ago --- */
	struct opj_image           *m_private_image;     /*    96     8 */
	struct opj_image           *m_output_image;      /*   104     8 */
	struct opj_cp              m_cp;                 /*   112   152 */
	/* --- cacheline 4 boundary (256 bytes) was 8 bytes ago --- */
	struct opj_procedure_list  *m_procedure_list;    /*   264     8 */
	struct opj_procedure_list  *m_validation_list;   /*   272     8 */
	struct opj_codestream_index *cstr_index;         /*   280     8 */
	unsigned int               m_current_tile_number; /*   288     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_tcd             *m_tcd;               /*   296     8 */
	struct opj_thread_pool_t   *m_tp;                /*   304     8 */
	unsigned int               ihdr_w;               /*   312     4 */
	unsigned int               ihdr_h;               /*   316     4 */
	/* --- cacheline 5 boundary (320 bytes) --- */
	unsigned int               dump_state;           /*   320     4 */

	/* size: 328, cachelines: 6, members: 14 */
	/* sum members: 316, holes: 2, sum holes: 8 */
	/* padding: 4 */
	/* last cacheline: 8 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <125a8> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.h:395 */
union memfuzz_anonymous_struct_17 {
	struct opj_decoding_param  m_dec;              /*     0     8 */
	struct opj_encoding_param  m_enc;              /*     0    24 */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <126c8> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/function_list.h:57 */
struct opj_procedure_list {
	unsigned int               m_nb_procedures;      /*     0     4 */
	unsigned int               m_nb_max_procedures;  /*     4     4 */
	void ***m_procedures;                                                /*     8     8 */

	/* size: 16, cachelines: 1, members: 3 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <1292b> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tcd.h:251 */
struct opj_tcd {
	int                        tp_pos;               /*     0     4 */
	unsigned int               tp_num;               /*     4     4 */
	unsigned int               cur_tp_num;           /*     8     4 */
	unsigned int               cur_totnum_tp;        /*    12     4 */
	unsigned int               cur_pino;             /*    16     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_tcd_image       *tcd_image;           /*    24     8 */
	struct opj_image           *image;               /*    32     8 */
	struct opj_cp              *cp;                  /*    40     8 */
	struct opj_tcp             *tcp;                 /*    48     8 */
	unsigned int               tcd_tileno;           /*    56     4 */
	unsigned int               m_is_decoder:1;       /*    60: 0  4 */

	/* XXX 31 bits hole, try to pack */

	/* --- cacheline 1 boundary (64 bytes) --- */
	struct opj_thread_pool_t   *thread_pool;         /*    64     8 */
	unsigned int               win_x0;               /*    72     4 */
	unsigned int               win_y0;               /*    76     4 */
	unsigned int               win_x1;               /*    80     4 */
	unsigned int               win_y1;               /*    84     4 */
	int                        whole_tile_decoding;  /*    88     4 */

	/* XXX 4 bytes hole, try to pack */

	int                        *used_component;      /*    96     8 */

	/* size: 104, cachelines: 2, members: 18 */
	/* sum members: 92, holes: 2, sum holes: 8 */
	/* sum bitfield members: 1 bits, bit holes: 1, sum bit holes: 31 bits */
	/* last cacheline: 40 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <12a2f> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tcd.h:242 */
struct opj_tcd_image {
	struct opj_tcd_tile        *tiles;               /*     0     8 */

	/* size: 8, cachelines: 1, members: 1 */
	/* last cacheline: 8 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <12a54> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tcd.h:228 */
struct opj_tcd_tile {
	int                        x0;                   /*     0     4 */
	int                        y0;                   /*     4     4 */
	int                        x1;                   /*     8     4 */
	int                        y1;                   /*    12     4 */
	unsigned int               numcomps;             /*    16     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_tcd_tilecomp    *comps;               /*    24     8 */
	int                        numpix;               /*    32     4 */

	/* XXX 4 bytes hole, try to pack */

	double                     distotile;            /*    40     8 */
	double                     distolayer[100];      /*    48   800 */
	/* --- cacheline 13 boundary (832 bytes) was 16 bytes ago --- */
	unsigned int               packno;               /*   848     4 */

	/* size: 856, cachelines: 14, members: 10 */
	/* sum members: 844, holes: 2, sum holes: 8 */
	/* padding: 4 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <12ae7> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tcd.h:189 */
struct opj_tcd_tilecomp {
	int                        x0;                   /*     0     4 */
	int                        y0;                   /*     4     4 */
	int                        x1;                   /*     8     4 */
	int                        y1;                   /*    12     4 */
	unsigned int               compno;               /*    16     4 */
	unsigned int               numresolutions;       /*    20     4 */
	unsigned int               minimum_num_resolutions; /*    24     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_tcd_resolution  *resolutions;         /*    32     8 */
	unsigned int               resolutions_size;     /*    40     4 */

	/* XXX 4 bytes hole, try to pack */

	int                        *data;                /*    48     8 */
	int                        ownsData;             /*    56     4 */

	/* XXX 4 bytes hole, try to pack */

	/* --- cacheline 1 boundary (64 bytes) --- */
	long unsigned int          data_size_needed;     /*    64     8 */
	long unsigned int          data_size;            /*    72     8 */
	int                        *data_win;            /*    80     8 */
	unsigned int               win_x0;               /*    88     4 */
	unsigned int               win_y0;               /*    92     4 */
	unsigned int               win_x1;               /*    96     4 */
	unsigned int               win_y1;               /*   100     4 */
	int                        numpix;               /*   104     4 */

	/* size: 112, cachelines: 2, members: 19 */
	/* sum members: 96, holes: 3, sum holes: 12 */
	/* padding: 4 */
	/* last cacheline: 48 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <12c94> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tcd.h:157 */
struct opj_tcd_band {
	int                        x0;                   /*     0     4 */
	int                        y0;                   /*     4     4 */
	int                        x1;                   /*     8     4 */
	int                        y1;                   /*    12     4 */
	unsigned int               bandno;               /*    16     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_tcd_precinct    *precincts;           /*    24     8 */
	unsigned int               precincts_data_size;  /*    32     4 */
	int                        numbps;               /*    36     4 */
	float                      stepsize;             /*    40     4 */

	/* size: 48, cachelines: 1, members: 9 */
	/* sum members: 40, holes: 1, sum holes: 4 */
	/* padding: 4 */
	/* last cacheline: 48 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <12be4> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tcd.h:171 */
struct opj_tcd_resolution {
	int                        x0;                   /*     0     4 */
	int                        y0;                   /*     4     4 */
	int                        x1;                   /*     8     4 */
	int                        y1;                   /*    12     4 */
	unsigned int               pw;                   /*    16     4 */
	unsigned int               ph;                   /*    20     4 */
	unsigned int               numbands;             /*    24     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_tcd_band        bands[3];             /*    32   144 */
	/* --- cacheline 2 boundary (128 bytes) was 48 bytes ago --- */
	unsigned int               win_x0;               /*   176     4 */
	unsigned int               win_y0;               /*   180     4 */
	unsigned int               win_x1;               /*   184     4 */
	unsigned int               win_y1;               /*   188     4 */

	/* size: 192, cachelines: 3, members: 12 */
	/* sum members: 188, holes: 1, sum holes: 4 */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <12d75> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tcd.h:146 */
union memfuzz_anonymous_struct_18 {
	struct opj_tcd_cblk_enc    *enc;               /*     0     8 */
	struct opj_tcd_cblk_dec    *dec;               /*     0     8 */
	void *                     blocks;             /*     0     8 */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <12d19> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tcd.h:142 */
struct opj_tcd_precinct {
	int                        x0;                   /*     0     4 */
	int                        y0;                   /*     4     4 */
	int                        x1;                   /*     8     4 */
	int                        y1;                   /*    12     4 */
	unsigned int               cw;                   /*    16     4 */
	unsigned int               ch;                   /*    20     4 */
	union {
		struct opj_tcd_cblk_enc *enc;            /*    24     8 */
		struct opj_tcd_cblk_dec *dec;            /*    24     8 */
		void *             blocks;               /*    24     8 */
	} cblks;                                         /*    24     8 */
	unsigned int               block_size;           /*    32     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_tgt_tree        *incltree;            /*    40     8 */
	struct opj_tgt_tree        *imsbtree;            /*    48     8 */

	/* size: 56, cachelines: 1, members: 10 */
	/* sum members: 52, holes: 1, sum holes: 4 */
	/* last cacheline: 56 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <12dd3> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tcd.h:77 */
struct opj_tcd_cblk_enc {
	unsigned char              *data;                /*     0     8 */
	struct opj_tcd_layer       *layers;              /*     8     8 */
	struct opj_tcd_pass        *passes;              /*    16     8 */
	int                        x0;                   /*    24     4 */
	int                        y0;                   /*    28     4 */
	int                        x1;                   /*    32     4 */
	int                        y1;                   /*    36     4 */
	unsigned int               numbps;               /*    40     4 */
	unsigned int               numlenbits;           /*    44     4 */
	unsigned int               data_size;            /*    48     4 */
	unsigned int               numpasses;            /*    52     4 */
	unsigned int               numpassesinlayers;    /*    56     4 */
	unsigned int               totalpasses;          /*    60     4 */

	/* size: 64, cachelines: 1, members: 13 */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <12e88> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tcd.h:67 */
struct opj_tcd_layer {
	unsigned int               numpasses;            /*     0     4 */
	unsigned int               len;                  /*     4     4 */
	double                     disto;                /*     8     8 */
	unsigned char              *data;                /*    16     8 */

	/* size: 24, cachelines: 1, members: 4 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <12ed1> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tcd.h:57 */
struct opj_tcd_pass {
	unsigned int               rate;                 /*     0     4 */

	/* XXX 4 bytes hole, try to pack */

	double                     distortiondec;        /*     8     8 */
	unsigned int               len;                  /*    16     4 */
	unsigned int               term:1;               /*    20: 0  4 */

	/* size: 24, cachelines: 1, members: 4 */
	/* sum members: 16, holes: 1, sum holes: 4 */
	/* sum bitfield members: 1 bits (0 bytes) */
	/* bit_padding: 31 bits */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <12f1d> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tcd.h:120 */
struct opj_tcd_cblk_dec {
	struct opj_tcd_seg         *segs;                /*     0     8 */
	struct opj_tcd_seg_data_chunk *chunks;           /*     8     8 */
	int                        x0;                   /*    16     4 */
	int                        y0;                   /*    20     4 */
	int                        x1;                   /*    24     4 */
	int                        y1;                   /*    28     4 */
	unsigned int               numbps;               /*    32     4 */
	unsigned int               numlenbits;           /*    36     4 */
	unsigned int               numnewpasses;         /*    40     4 */
	unsigned int               numsegs;              /*    44     4 */
	unsigned int               real_num_segs;        /*    48     4 */
	unsigned int               m_current_max_segs;   /*    52     4 */
	unsigned int               numchunks;            /*    56     4 */
	unsigned int               numchunksalloc;       /*    60     4 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	int                        *decoded_data;        /*    64     8 */

	/* size: 72, cachelines: 2, members: 15 */
	/* last cacheline: 8 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <12fea> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tcd.h:105 */
struct opj_tcd_seg {
	unsigned int               len;                  /*     0     4 */
	unsigned int               numpasses;            /*     4     4 */
	unsigned int               real_num_passes;      /*     8     4 */
	unsigned int               maxpasses;            /*    12     4 */
	unsigned int               numnewpasses;         /*    16     4 */
	unsigned int               newlen;               /*    20     4 */

	/* size: 24, cachelines: 1, members: 6 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <1304b> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tcd.h:94 */
struct opj_tcd_seg_data_chunk {
	unsigned char              *data;                /*     0     8 */
	unsigned int               len;                  /*     8     4 */

	/* size: 16, cachelines: 1, members: 2 */
	/* padding: 4 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <1307c> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tgt.h:67 */
struct opj_tgt_tree {
	unsigned int               numleafsh;            /*     0     4 */
	unsigned int               numleafsv;            /*     4     4 */
	unsigned int               numnodes;             /*     8     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_tgt_node        *nodes;               /*    16     8 */
	unsigned int               nodes_size;           /*    24     4 */

	/* size: 32, cachelines: 1, members: 5 */
	/* sum members: 24, holes: 1, sum holes: 4 */
	/* padding: 4 */
	/* last cacheline: 32 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <130d1> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tgt.h:57 */
struct opj_tgt_node {
	struct opj_tgt_node        *parent;              /*     0     8 */
	int                        value;                /*     8     4 */
	int                        low;                  /*    12     4 */
	unsigned int               known;                /*    16     4 */

	/* size: 24, cachelines: 1, members: 4 */
	/* padding: 4 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.c */
/* <1a600> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tcd.h:291 */
struct opj_tcd_marker_info {
	int                        need_PLT;             /*     0     4 */
	unsigned int               packet_count;         /*     4     4 */
	unsigned int               *p_packet_size;       /*     8     8 */

	/* size: 16, cachelines: 1, members: 3 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/jp2.c */
/* <1a6ee> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/jp2.h:204 */
struct opj_jp2_header_handler {
	unsigned int               id;                   /*     0     4 */

	/* XXX 4 bytes hole, try to pack */

	void **handler;                                                /*     8     8 */

	/* size: 16, cachelines: 1, members: 2 */
	/* sum members: 12, holes: 1, sum holes: 4 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/jp2.c */
/* <1a906> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.h:562 */
union memfuzz_anonymous_struct_19 {
	struct opj_j2k_dec         m_decoder;          /*     0    88 */
	struct opj_j2k_enc         m_encoder;          /*     0    88 */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/jp2.c */
/* <1b5b0> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.h:395 */
union memfuzz_anonymous_struct_20 {
	struct opj_decoding_param  m_dec;              /*     0     8 */
	struct opj_encoding_param  m_enc;              /*     0    24 */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/jp2.c */
/* <1bd7d> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tcd.h:146 */
union memfuzz_anonymous_struct_21 {
	struct opj_tcd_cblk_enc    *enc;               /*     0     8 */
	struct opj_tcd_cblk_dec    *dec;               /*     0     8 */
	void *                     blocks;             /*     0     8 */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/jp2.c */
/* <1c163> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/jp2.h:140 */
struct opj_jp2_comps {
	unsigned int               depth;                /*     0     4 */
	unsigned int               sgnd;                 /*     4     4 */
	unsigned int               bpcc;                 /*     8     4 */

	/* size: 12, cachelines: 1, members: 3 */
	/* last cacheline: 12 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/jp2.c */
/* <1c19b> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/jp2.h:128 */
struct opj_jp2_color {
	unsigned char              *icc_profile_buf;     /*     0     8 */
	unsigned int               icc_profile_len;      /*     8     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_jp2_cdef        *jp2_cdef;            /*    16     8 */
	struct opj_jp2_pclr        *jp2_pclr;            /*    24     8 */
	unsigned char              jp2_has_colr;         /*    32     1 */

	/* size: 40, cachelines: 1, members: 5 */
	/* sum members: 29, holes: 1, sum holes: 4 */
	/* padding: 7 */
	/* last cacheline: 40 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/jp2.c */
/* <1a778> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/jp2.h:149 */
struct opj_jp2 {
	struct opj_j2k             *j2k;                 /*     0     8 */
	struct opj_procedure_list  *m_validation_list;   /*     8     8 */
	struct opj_procedure_list  *m_procedure_list;    /*    16     8 */
	unsigned int               w;                    /*    24     4 */
	unsigned int               h;                    /*    28     4 */
	unsigned int               numcomps;             /*    32     4 */
	unsigned int               bpc;                  /*    36     4 */
	unsigned int               C;                    /*    40     4 */
	unsigned int               UnkC;                 /*    44     4 */
	unsigned int               IPR;                  /*    48     4 */
	unsigned int               meth;                 /*    52     4 */
	unsigned int               approx;               /*    56     4 */
	unsigned int               enumcs;               /*    60     4 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	unsigned int               precedence;           /*    64     4 */
	unsigned int               brand;                /*    68     4 */
	unsigned int               minversion;           /*    72     4 */
	unsigned int               numcl;                /*    76     4 */
	unsigned int               *cl;                  /*    80     8 */
	struct opj_jp2_comps       *comps;               /*    88     8 */
	long int                   j2k_codestream_offset; /*    96     8 */
	long int                   jpip_iptr_offset;     /*   104     8 */
	int                        jpip_on;              /*   112     4 */
	unsigned int               jp2_state;            /*   116     4 */
	unsigned int               jp2_img_state;        /*   120     4 */

	/* XXX 4 bytes hole, try to pack */

	/* --- cacheline 2 boundary (128 bytes) --- */
	struct opj_jp2_color       color;                /*   128    40 */
	int                        ignore_pclr_cmap_cdef; /*   168     4 */
	unsigned char              has_jp2h;             /*   172     1 */
	unsigned char              has_ihdr;             /*   173     1 */

	/* size: 176, cachelines: 3, members: 28 */
	/* sum members: 170, holes: 1, sum holes: 4 */
	/* padding: 2 */
	/* last cacheline: 48 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/jp2.c */
/* <1c1f0> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/jp2.h:100 */
struct opj_jp2_cdef {
	struct opj_jp2_cdef_info   *info;                /*     0     8 */
	unsigned short             n;                    /*     8     2 */

	/* size: 16, cachelines: 1, members: 2 */
	/* padding: 6 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/jp2.c */
/* <1c221> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/jp2.h:93 */
struct opj_jp2_cdef_info {
	unsigned short             cn;                   /*     0     2 */
	unsigned short             typ;                  /*     2     2 */
	unsigned short             asoc;                 /*     4     2 */

	/* size: 6, cachelines: 1, members: 3 */
	/* last cacheline: 6 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/jp2.c */
/* <1c25e> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/jp2.h:116 */
struct opj_jp2_pclr {
	unsigned int               *entries;             /*     0     8 */
	unsigned char              *channel_sign;        /*     8     8 */
	unsigned char              *channel_size;        /*    16     8 */
	struct opj_jp2_cmap_comp   *cmap;                /*    24     8 */
	unsigned short             nr_entries;           /*    32     2 */
	unsigned char              nr_channels;          /*    34     1 */

	/* size: 40, cachelines: 1, members: 6 */
	/* padding: 5 */
	/* last cacheline: 40 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/jp2.c */
/* <1c2bf> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/jp2.h:108 */
struct opj_jp2_cmap_comp {
	unsigned short             cmp;                  /*     0     2 */
	unsigned char              mtyp;                 /*     2     1 */
	unsigned char              pcol;                 /*     3     1 */

	/* size: 4, cachelines: 1, members: 3 */
	/* last cacheline: 4 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/jp2.c */
/* <1e87f> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/jp2.h:198 */
struct opj_jp2_box {
	unsigned int               length;               /*     0     4 */
	unsigned int               type;                 /*     4     4 */
	int                        init_pos;             /*     8     4 */

	/* size: 12, cachelines: 1, members: 3 */
	/* last cacheline: 12 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/jp2.c */
/* <1e8d9> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/jp2.h:216 */
struct opj_jp2_img_header_writer_handler {
	void **handler;                                                /*     0     8 */
	unsigned char              *m_data;              /*     8     8 */
	unsigned int               m_size;               /*    16     4 */

	/* size: 24, cachelines: 1, members: 3 */
	/* padding: 4 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/pi.c */
/* <1f597> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/pi.h:73 */
struct opj_pi_iterator {
	unsigned char              tp_on;                /*     0     1 */

	/* XXX 7 bytes hole, try to pack */

	short                      *include;             /*     8     8 */
	unsigned int               include_size;         /*    16     4 */
	unsigned int               step_l;               /*    20     4 */
	unsigned int               step_r;               /*    24     4 */
	unsigned int               step_c;               /*    28     4 */
	unsigned int               step_p;               /*    32     4 */
	unsigned int               compno;               /*    36     4 */
	unsigned int               resno;                /*    40     4 */
	unsigned int               precno;               /*    44     4 */
	unsigned int               layno;                /*    48     4 */
	int                        first;                /*    52     4 */
	struct opj_poc             poc;                  /*    56   148 */
	/* --- cacheline 3 boundary (192 bytes) was 12 bytes ago --- */
	unsigned int               numcomps;             /*   204     4 */
	struct opj_pi_comp         *comps;               /*   208     8 */
	unsigned int               tx0;                  /*   216     4 */
	unsigned int               ty0;                  /*   220     4 */
	unsigned int               tx1;                  /*   224     4 */
	unsigned int               ty1;                  /*   228     4 */
	unsigned int               x;                    /*   232     4 */
	unsigned int               y;                    /*   236     4 */
	unsigned int               dx;                   /*   240     4 */
	unsigned int               dy;                   /*   244     4 */
	struct opj_event_mgr       *manager;             /*   248     8 */

	/* size: 256, cachelines: 4, members: 24 */
	/* sum members: 249, holes: 1, sum holes: 7 */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/pi.c */
/* <1f8f7> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/pi.h:63 */
struct opj_pi_comp {
	unsigned int               dx;                   /*     0     4 */
	unsigned int               dy;                   /*     4     4 */
	unsigned int               numresolutions;       /*     8     4 */

	/* XXX 4 bytes hole, try to pack */

	struct opj_pi_resolution   *resolutions;         /*    16     8 */

	/* size: 24, cachelines: 1, members: 4 */
	/* sum members: 20, holes: 1, sum holes: 4 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/pi.c */
/* <1f940> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/pi.h:55 */
struct opj_pi_resolution {
	unsigned int               pdx;                  /*     0     4 */
	unsigned int               pdy;                  /*     4     4 */
	unsigned int               pw;                   /*     8     4 */
	unsigned int               ph;                   /*    12     4 */

	/* size: 16, cachelines: 1, members: 4 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/pi.c */
/* <21448> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.h:395 */
union memfuzz_anonymous_struct_22 {
	struct opj_decoding_param  m_dec;              /*     0     8 */
	struct opj_encoding_param  m_enc;              /*     0    24 */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tcd.c */
/* <21f5c> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tcd.h:146 */
union memfuzz_anonymous_struct_23 {
	struct opj_tcd_cblk_enc    *enc;               /*     0     8 */
	struct opj_tcd_cblk_dec    *dec;               /*     0     8 */
	void *                     blocks;             /*     0     8 */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tcd.c */
/* <22625> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.h:395 */
union memfuzz_anonymous_struct_24 {
	struct opj_decoding_param  m_dec;              /*     0     8 */
	struct opj_encoding_param  m_enc;              /*     0    24 */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tcd.c */
/* <2569b> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/t2.h:54 */
struct opj_t2 {
	struct opj_image           *image;               /*     0     8 */
	struct opj_cp              *cp;                  /*     8     8 */

	/* size: 16, cachelines: 1, members: 2 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tgt.c */
/* <25e0d> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/bio.h:56 */
struct opj_bio {
	unsigned char              *start;               /*     0     8 */
	unsigned char              *end;                 /*     8     8 */
	unsigned char              *bp;                  /*    16     8 */
	unsigned int               buf;                  /*    24     4 */
	unsigned int               ct;                   /*    28     4 */

	/* size: 32, cachelines: 1, members: 5 */
	/* last cacheline: 32 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/dwt.c */
/* <2670d> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/dwt.c:83 */
struct dwt_local {
	int                        *mem;                 /*     0     8 */
	int                        dn;                   /*     8     4 */
	int                        sn;                   /*    12     4 */
	int                        cas;                  /*    16     4 */

	/* size: 24, cachelines: 1, members: 4 */
	/* padding: 4 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/dwt.c */
/* <266a1> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/dwt.c:1207 */
typedef struct memfuzz_anonymous_struct_25 {
	struct dwt_local           v;                    /*     0    24 */
	unsigned int               rh;                   /*    24     4 */
	unsigned int               w;                    /*    28     4 */
	int                        *tiledp;              /*    32     8 */
	unsigned int               min_j;                /*    40     4 */
	unsigned int               max_j;                /*    44     4 */
	void **p_encode_and_deinterleave_v;                                                /*    48     8 */

	/* size: 56, cachelines: 1, members: 7 */
	/* last cacheline: 56 bytes */
} opj_dwt_encode_v_job_t;
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/dwt.c */
/* <26798> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/dwt.c:1180 */
typedef struct memfuzz_anonymous_struct_26 {
	struct dwt_local           h;                    /*     0    24 */
	unsigned int               rw;                   /*    24     4 */
	unsigned int               w;                    /*    28     4 */
	int                        *tiledp;              /*    32     8 */
	unsigned int               min_j;                /*    40     4 */
	unsigned int               max_j;                /*    44     4 */
	void **p_function;                                                /*    48     8 */

	/* size: 56, cachelines: 1, members: 7 */
	/* last cacheline: 56 bytes */
} opj_dwt_encode_h_job_t;
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/dwt.c */
/* <268de> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/dwt.c:2007 */
typedef struct memfuzz_anonymous_struct_27 {
	struct dwt_local           h;                    /*     0    24 */
	unsigned int               rw;                   /*    24     4 */
	unsigned int               w;                    /*    28     4 */
	int                        *tiledp;              /*    32     8 */
	unsigned int               min_j;                /*    40     4 */
	unsigned int               max_j;                /*    44     4 */

	/* size: 48, cachelines: 1, members: 6 */
	/* last cacheline: 48 bytes */
} opj_dwt_decode_h_job_t;
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/dwt.c */
/* <26943> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/dwt.c:2031 */
typedef struct memfuzz_anonymous_struct_28 {
	struct dwt_local           v;                    /*     0    24 */
	unsigned int               rh;                   /*    24     4 */
	unsigned int               w;                    /*    28     4 */
	int                        *tiledp;              /*    32     8 */
	unsigned int               min_j;                /*    40     4 */
	unsigned int               max_j;                /*    44     4 */

	/* size: 48, cachelines: 1, members: 6 */
	/* last cacheline: 48 bytes */
} opj_dwt_decode_v_job_t;
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/dwt.c */
/* <26a00> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/dwt.c:92 */
typedef union memfuzz_anonymous_struct_29 {
	float                      f[8];               /*     0    32 */
} opj_v8_t;
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/dwt.c */
/* <26a80> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/dwt.c:96 */
struct v8dwt_local {
	union {
		float              f[8];                 /*     0    32 */
	} *wavelet; /*     0     8 */
	int                        dn;                   /*     8     4 */
	int                        sn;                   /*    12     4 */
	int                        cas;                  /*    16     4 */
	unsigned int               win_l_x0;             /*    20     4 */
	unsigned int               win_l_x1;             /*    24     4 */
	unsigned int               win_h_x0;             /*    28     4 */
	unsigned int               win_h_x1;             /*    32     4 */

	/* size: 40, cachelines: 1, members: 8 */
	/* padding: 4 */
	/* last cacheline: 40 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/dwt.c */
/* <26a2e> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/dwt.c:3199 */
typedef struct memfuzz_anonymous_struct_30 {
	struct v8dwt_local         h;                    /*     0    40 */
	unsigned int               rw;                   /*    40     4 */
	unsigned int               w;                    /*    44     4 */
	float                      *aj;                  /*    48     8 */
	unsigned int               nb_rows;              /*    56     4 */

	/* size: 64, cachelines: 1, members: 5 */
	/* padding: 4 */
} opj_dwt97_decode_h_job_t;
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/dwt.c */
/* <26aff> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/dwt.c:3248 */
typedef struct memfuzz_anonymous_struct_31 {
	struct v8dwt_local         v;                    /*     0    40 */
	unsigned int               rh;                   /*    40     4 */
	unsigned int               w;                    /*    44     4 */
	float                      *aj;                  /*    48     8 */
	unsigned int               nb_columns;           /*    56     4 */

	/* size: 64, cachelines: 1, members: 5 */
	/* padding: 4 */
} opj_dwt97_decode_v_job_t;
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/dwt.c */
/* <29f5d> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tcd.h:146 */
union memfuzz_anonymous_struct_32 {
	struct opj_tcd_cblk_enc    *enc;               /*     0     8 */
	struct opj_tcd_cblk_dec    *dec;               /*     0     8 */
	void *                     blocks;             /*     0     8 */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/dwt.c */
/* <2a5d8> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.h:395 */
union memfuzz_anonymous_struct_33 {
	struct opj_decoding_param  m_dec;              /*     0     8 */
	struct opj_encoding_param  m_enc;              /*     0    24 */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/t1.c */
/* <2b498> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/mqc.h:74 */
struct opj_mqc {
	unsigned int               c;                    /*     0     4 */
	unsigned int               a;                    /*     4     4 */
	unsigned int               ct;                   /*     8     4 */
	unsigned int               end_of_byte_stream_counter; /*    12     4 */
	unsigned char              *bp;                  /*    16     8 */
	unsigned char              *start;               /*    24     8 */
	unsigned char              *end;                 /*    32     8 */
	struct opj_mqc_state       *ctxs[19];            /*    40   152 */
	/* --- cacheline 3 boundary (192 bytes) --- */
	struct opj_mqc_state       **curctx;             /*   192     8 */
	unsigned char              *lut_ctxno_zc_orient; /*   200     8 */
	unsigned char              backup[2];            /*   208     2 */

	/* size: 216, cachelines: 4, members: 11 */
	/* padding: 6 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/t1.c */
/* <2b3fd> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/t1.h:184 */
struct opj_t1 {
	struct opj_mqc             mqc;                  /*     0   216 */
	/* --- cacheline 3 boundary (192 bytes) was 24 bytes ago --- */
	int                        *data;                /*   216     8 */
	unsigned int               *flags;               /*   224     8 */
	unsigned int               w;                    /*   232     4 */
	unsigned int               h;                    /*   236     4 */
	unsigned int               datasize;             /*   240     4 */
	unsigned int               flagssize;            /*   244     4 */
	int                        encoder;              /*   248     4 */
	int                        mustuse_cblkdatabuffer; /*   252     4 */
	/* --- cacheline 4 boundary (256 bytes) --- */
	unsigned char              *cblkdatabuffer;      /*   256     8 */
	unsigned int               cblkdatabuffersize;   /*   264     4 */

	/* size: 272, cachelines: 5, members: 11 */
	/* padding: 4 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/t1.c */
/* <2b56c> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/mqc.h:58 */
struct opj_mqc_state {
	unsigned int               qeval;                /*     0     4 */
	unsigned int               mps;                  /*     4     4 */
	struct opj_mqc_state       *nmps;                /*     8     8 */
	struct opj_mqc_state       *nlps;                /*    16     8 */

	/* size: 24, cachelines: 1, members: 4 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/t1.c */
/* <2b618> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/t1.c:1568 */
typedef struct memfuzz_anonymous_struct_34 {
	int                        whole_tile_decoding;  /*     0     4 */
	unsigned int               resno;                /*     4     4 */
	struct opj_tcd_cblk_dec    *cblk;                /*     8     8 */
	struct opj_tcd_band        *band;                /*    16     8 */
	struct opj_tcd_tilecomp    *tilec;               /*    24     8 */
	struct opj_tccp            *tccp;                /*    32     8 */
	int                        mustuse_cblkdatabuffer; /*    40     4 */

	/* XXX 4 bytes hole, try to pack */

	int                        *pret;                /*    48     8 */
	struct opj_event_mgr       *p_manager;           /*    56     8 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	struct opj_mutex_t         *p_manager_mutex;     /*    64     8 */
	int                        check_pterm;          /*    72     4 */

	/* size: 80, cachelines: 2, members: 11 */
	/* sum members: 72, holes: 1, sum holes: 4 */
	/* padding: 4 */
	/* last cacheline: 16 bytes */
} opj_t1_cblk_decode_processing_job_t;
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/t1.c */
/* <2b8fd> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tcd.h:146 */
union memfuzz_anonymous_struct_35 {
	struct opj_tcd_cblk_enc    *enc;               /*     0     8 */
	struct opj_tcd_cblk_dec    *dec;               /*     0     8 */
	void *                     blocks;             /*     0     8 */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/t1.c */
/* <2bee9> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/t1.c:2108 */
typedef struct memfuzz_anonymous_struct_36 {
	unsigned int               compno;               /*     0     4 */
	unsigned int               resno;                /*     4     4 */
	struct opj_tcd_cblk_enc    *cblk;                /*     8     8 */
	struct opj_tcd_tile        *tile;                /*    16     8 */
	struct opj_tcd_band        *band;                /*    24     8 */
	struct opj_tcd_tilecomp    *tilec;               /*    32     8 */
	struct opj_tccp            *tccp;                /*    40     8 */
	double                     *mct_norms;           /*    48     8 */
	unsigned int               mct_numcomps;         /*    56     4 */

	/* XXX 4 bytes hole, try to pack */

	/* --- cacheline 1 boundary (64 bytes) --- */
	int                        *pret;                /*    64     8 */
	struct opj_mutex_t         *mutex;               /*    72     8 */

	/* size: 80, cachelines: 2, members: 11 */
	/* sum members: 76, holes: 1, sum holes: 4 */
	/* last cacheline: 16 bytes */
} opj_t1_cblk_encode_processing_job_t;
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/t1.c */
/* <322f7> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.h:395 */
union memfuzz_anonymous_struct_37 {
	struct opj_decoding_param  m_dec;              /*     0     8 */
	struct opj_encoding_param  m_enc;              /*     0    24 */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/t2.c */
/* <32dd8> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/j2k.h:395 */
union memfuzz_anonymous_struct_38 {
	struct opj_decoding_param  m_dec;              /*     0     8 */
	struct opj_encoding_param  m_enc;              /*     0    24 */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/t2.c */
/* <349a0> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/tcd.h:146 */
union memfuzz_anonymous_struct_39 {
	struct opj_tcd_cblk_enc    *enc;               /*     0     8 */
	struct opj_tcd_cblk_dec    *dec;               /*     0     8 */
	void *                     blocks;             /*     0     8 */
};
/* Used at: /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/sparse_array.c */
/* <35876> /home/liu2598/Product/openjpeg/master/src_raw/src/lib/openjp2/sparse_array.c:35 */
struct opj_sparse_array_int32 {
	unsigned int               width;                /*     0     4 */
	unsigned int               height;               /*     4     4 */
	unsigned int               block_width;          /*     8     4 */
	unsigned int               block_height;         /*    12     4 */
	unsigned int               block_count_hor;      /*    16     4 */
	unsigned int               block_count_ver;      /*    20     4 */
	int                        **data_blocks;        /*    24     8 */

	/* size: 32, cachelines: 1, members: 7 */
	/* last cacheline: 32 bytes */
};
#endif
