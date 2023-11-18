#ifndef _MEMFUZZ_STRUCT_H_
#define _MEMFUZZ_STRUCT_H_
/*Add necessary header here to avoid compile problems*/
/*Struct Declaration Begin*/
struct mz_stream_s;
struct memfuzz_anonymous_struct_0;
struct tinfl_decompressor_tag;
struct memfuzz_anonymous_struct_1;
struct memfuzz_anonymous_struct_2;
struct mz_zip_internal_state_tag;
struct memfuzz_anonymous_struct_3;
struct memfuzz_anonymous_struct_4;
struct memfuzz_anonymous_struct_5;
struct memfuzz_anonymous_struct_6;
struct memfuzz_anonymous_struct_7;
struct memfuzz_anonymous_struct_8;
struct memfuzz_anonymous_struct_9;
struct zip_entry_t;
struct zip_t;
struct zip_entry_mark_t;
struct memfuzz_anonymous_struct_10;
/*Enumeration Definition Begin*/
enum zip_modify_t {
		MZ_KEEP   = 0,
		MZ_DELETE = 1,
		MZ_MOVE   = 2,
	};
enum memfuzz_anonymous_enum_0 {
			TDEFL_STATUS_BAD_PARAM      = 4294967294,
			TDEFL_STATUS_PUT_BUF_FAILED = 4294967295,
			TDEFL_STATUS_OKAY           = 0,
			TDEFL_STATUS_DONE           = 1,
		};
enum memfuzz_anonymous_enum_1 {
			TDEFL_NO_FLUSH   = 0,
			TDEFL_SYNC_FLUSH = 2,
			TDEFL_FULL_FLUSH = 3,
			TDEFL_FINISH     = 4,
		};
enum memfuzz_anonymous_enum_2 {
			MZ_ZIP_MODE_INVALID                    = 0,
			MZ_ZIP_MODE_READING                    = 1,
			MZ_ZIP_MODE_WRITING                    = 2,
			MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED = 3,
		};
enum memfuzz_anonymous_enum_3 {
			MZ_ZIP_TYPE_INVALID = 0,
			MZ_ZIP_TYPE_USER    = 1,
			MZ_ZIP_TYPE_MEMORY  = 2,
			MZ_ZIP_TYPE_HEAP    = 3,
			MZ_ZIP_TYPE_FILE    = 4,
			MZ_ZIP_TYPE_CFILE   = 5,
			MZ_ZIP_TOTAL_TYPES  = 6,
		};
enum memfuzz_anonymous_enum_4 {
			MZ_ZIP_NO_ERROR                     = 0,
			MZ_ZIP_UNDEFINED_ERROR              = 1,
			MZ_ZIP_TOO_MANY_FILES               = 2,
			MZ_ZIP_FILE_TOO_LARGE               = 3,
			MZ_ZIP_UNSUPPORTED_METHOD           = 4,
			MZ_ZIP_UNSUPPORTED_ENCRYPTION       = 5,
			MZ_ZIP_UNSUPPORTED_FEATURE          = 6,
			MZ_ZIP_FAILED_FINDING_CENTRAL_DIR   = 7,
			MZ_ZIP_NOT_AN_ARCHIVE               = 8,
			MZ_ZIP_INVALID_HEADER_OR_CORRUPTED  = 9,
			MZ_ZIP_UNSUPPORTED_MULTIDISK        = 10,
			MZ_ZIP_DECOMPRESSION_FAILED         = 11,
			MZ_ZIP_COMPRESSION_FAILED           = 12,
			MZ_ZIP_UNEXPECTED_DECOMPRESSED_SIZE = 13,
			MZ_ZIP_CRC_CHECK_FAILED             = 14,
			MZ_ZIP_UNSUPPORTED_CDIR_SIZE        = 15,
			MZ_ZIP_ALLOC_FAILED                 = 16,
			MZ_ZIP_FILE_OPEN_FAILED             = 17,
			MZ_ZIP_FILE_CREATE_FAILED           = 18,
			MZ_ZIP_FILE_WRITE_FAILED            = 19,
			MZ_ZIP_FILE_READ_FAILED             = 20,
			MZ_ZIP_FILE_CLOSE_FAILED            = 21,
			MZ_ZIP_FILE_SEEK_FAILED             = 22,
			MZ_ZIP_FILE_STAT_FAILED             = 23,
			MZ_ZIP_INVALID_PARAMETER            = 24,
			MZ_ZIP_INVALID_FILENAME             = 25,
			MZ_ZIP_BUF_TOO_SMALL                = 26,
			MZ_ZIP_INTERNAL_ERROR               = 27,
			MZ_ZIP_FILE_NOT_FOUND               = 28,
			MZ_ZIP_ARCHIVE_TOO_LARGE            = 29,
			MZ_ZIP_VALIDATION_FAILED            = 30,
			MZ_ZIP_WRITE_CALLBACK_FAILED        = 31,
			MZ_ZIP_TOTAL_ERRORS                 = 32,
		};
enum memfuzz_anonymous_enum_5 {
		TINFL_STATUS_FAILED_CANNOT_MAKE_PROGRESS = 4294967292,
		TINFL_STATUS_BAD_PARAM                   = 4294967293,
		TINFL_STATUS_ADLER32_MISMATCH            = 4294967294,
		TINFL_STATUS_FAILED                      = 4294967295,
		TINFL_STATUS_DONE                        = 0,
		TINFL_STATUS_NEEDS_MORE_INPUT            = 1,
		TINFL_STATUS_HAS_MORE_OUTPUT             = 2,
	};
/*Struct Definition Begin*/
/* Used at: /home/liu2598/Product/miniz/master/src_format/src/zip.c */
/* <8ee> /home/liu2598/Product/miniz/master/src_format/src/miniz.h:330 */
struct mz_stream_s {
	unsigned char              *next_in;             /*     0     8 */
	unsigned int               avail_in;             /*     8     4 */

	/* XXX 4 bytes hole, try to pack */

	long unsigned int          total_in;             /*    16     8 */
	unsigned char              *next_out;            /*    24     8 */
	unsigned int               avail_out;            /*    32     4 */

	/* XXX 4 bytes hole, try to pack */

	long unsigned int          total_out;            /*    40     8 */
	char                       *msg;                 /*    48     8 */
	struct mz_internal_state   *state;               /*    56     8 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	void **zalloc;                                                /*    64     8 */
	void **zfree;                                                /*    72     8 */
	void *                     opaque;               /*    80     8 */
	int                        data_type;            /*    88     4 */

	/* XXX 4 bytes hole, try to pack */

	long unsigned int          adler;                /*    96     8 */
	long unsigned int          reserved;             /*   104     8 */

	/* size: 112, cachelines: 2, members: 14 */
	/* sum members: 100, holes: 3, sum holes: 12 */
	/* last cacheline: 48 bytes */
};
/* Used at: /home/liu2598/Product/miniz/master/src_format/src/zip.c */
/* <e90> /home/liu2598/Product/miniz/master/src_format/src/miniz.h:840 */
typedef struct memfuzz_anonymous_struct_0 {
	void **m_pPut_buf_func;                                                /*     0     8 */
	void *                     m_pPut_buf_user;      /*     8     8 */
	unsigned int               m_flags;              /*    16     4 */
	unsigned int               m_max_probes[2];      /*    20     8 */
	int                        m_greedy_parsing;     /*    28     4 */
	unsigned int               m_adler32;            /*    32     4 */
	unsigned int               m_lookahead_pos;      /*    36     4 */
	unsigned int               m_lookahead_size;     /*    40     4 */
	unsigned int               m_dict_size;          /*    44     4 */
	unsigned char              *m_pLZ_code_buf;      /*    48     8 */
	unsigned char              *m_pLZ_flags;         /*    56     8 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	unsigned char              *m_pOutput_buf;       /*    64     8 */
	unsigned char              *m_pOutput_buf_end;   /*    72     8 */
	unsigned int               m_num_flags_left;     /*    80     4 */
	unsigned int               m_total_lz_bytes;     /*    84     4 */
	unsigned int               m_lz_code_buf_dict_pos; /*    88     4 */
	unsigned int               m_bits_in;            /*    92     4 */
	unsigned int               m_bit_buffer;         /*    96     4 */
	unsigned int               m_saved_match_dist;   /*   100     4 */
	unsigned int               m_saved_match_len;    /*   104     4 */
	unsigned int               m_saved_lit;          /*   108     4 */
	unsigned int               m_output_flush_ofs;   /*   112     4 */
	unsigned int               m_output_flush_remaining; /*   116     4 */
	unsigned int               m_finished;           /*   120     4 */
	unsigned int               m_block_index;        /*   124     4 */
	/* --- cacheline 2 boundary (128 bytes) --- */
	unsigned int               m_wants_to_finish;    /*   128     4 */
	enum memfuzz_anonymous_enum_0 m_prev_return_status;
	void*                      *m_pIn_buf;           /*   136     8 */
	void *                     m_pOut_buf;           /*   144     8 */
	long unsigned int          *m_pIn_buf_size;      /*   152     8 */
	long unsigned int          *m_pOut_buf_size;     /*   160     8 */
	enum memfuzz_anonymous_enum_1 m_flush;

	/* XXX 4 bytes hole, try to pack */

	unsigned char              *m_pSrc;              /*   176     8 */
	long unsigned int          m_src_buf_left;       /*   184     8 */
	/* --- cacheline 3 boundary (192 bytes) --- */
	long unsigned int          m_out_buf_ofs;        /*   192     8 */
	unsigned char              m_dict[33025];        /*   200 33025 */

	/* XXX 1 byte hole, try to pack */

	/* --- cacheline 519 boundary (33216 bytes) was 10 bytes ago --- */
	short unsigned int         m_huff_count[3][288]; /* 33226  1728 */
	/* --- cacheline 546 boundary (34944 bytes) was 10 bytes ago --- */
	short unsigned int         m_huff_codes[3][288]; /* 34954  1728 */
	/* --- cacheline 573 boundary (36672 bytes) was 10 bytes ago --- */
	unsigned char              m_huff_code_sizes[3][288]; /* 36682   864 */
	/* --- cacheline 586 boundary (37504 bytes) was 42 bytes ago --- */
	unsigned char              m_lz_code_buf[65536]; /* 37546 65536 */
	/* --- cacheline 1610 boundary (103040 bytes) was 42 bytes ago --- */
	short unsigned int         m_next[32768];        /* 103082 65536 */
	/* --- cacheline 2634 boundary (168576 bytes) was 42 bytes ago --- */
	short unsigned int         m_hash[32768];        /* 168618 65536 */
	/* --- cacheline 3658 boundary (234112 bytes) was 42 bytes ago --- */
	unsigned char              m_output_buf[85196];  /* 234154 85196 */

	/* size: 319352, cachelines: 4990, members: 43 */
	/* sum members: 319345, holes: 2, sum holes: 5 */
	/* padding: 2 */
	/* last cacheline: 56 bytes */
} tdefl_compressor;
/* Used at: /home/liu2598/Product/miniz/master/src_format/src/zip.c */
/* <11e3> /home/liu2598/Product/miniz/master/src_format/src/miniz.h:1108 */
struct tinfl_decompressor_tag {
	unsigned int               m_state;              /*     0     4 */
	unsigned int               m_num_bits;           /*     4     4 */
	unsigned int               m_zhdr0;              /*     8     4 */
	unsigned int               m_zhdr1;              /*    12     4 */
	unsigned int               m_z_adler32;          /*    16     4 */
	unsigned int               m_final;              /*    20     4 */
	unsigned int               m_type;               /*    24     4 */
	unsigned int               m_check_adler32;      /*    28     4 */
	unsigned int               m_dist;               /*    32     4 */
	unsigned int               m_counter;            /*    36     4 */
	unsigned int               m_num_extra;          /*    40     4 */
	unsigned int               m_table_sizes[3];     /*    44    12 */
	long unsigned int          m_bit_buf;            /*    56     8 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	long unsigned int          m_dist_from_out_buf_start; /*    64     8 */
	struct {
		unsigned char      m_code_size[288];     /*    72   288 */
		/* --- cacheline 5 boundary (320 bytes) was 40 bytes ago --- */
		short int          m_look_up[1024];      /*   360  2048 */
		/* --- cacheline 37 boundary (2368 bytes) was 40 bytes ago --- */
		short int          m_tree[576];          /*  2408  1152 */
	} m_tables[3]; /*    72 10464 */
	/* --- cacheline 164 boundary (10496 bytes) was 40 bytes ago --- */
	unsigned char              m_raw_header[4];      /* 10536     4 */
	unsigned char              m_len_codes[457];     /* 10540   457 */

	/* size: 11000, cachelines: 172, members: 17 */
	/* padding: 3 */
	/* last cacheline: 56 bytes */
};
/* Used at: /home/liu2598/Product/miniz/master/src_format/src/zip.c */
/* <134b> /home/liu2598/Product/miniz/master/src_format/src/miniz.h:1088 */
typedef struct memfuzz_anonymous_struct_1 {
	unsigned char              m_code_size[288];     /*     0   288 */
	/* --- cacheline 4 boundary (256 bytes) was 32 bytes ago --- */
	short int                  m_look_up[1024];      /*   288  2048 */
	/* --- cacheline 36 boundary (2304 bytes) was 32 bytes ago --- */
	short int                  m_tree[576];          /*  2336  1152 */

	/* size: 3488, cachelines: 55, members: 3 */
	/* last cacheline: 32 bytes */
} tinfl_huff_table;
/* Used at: /home/liu2598/Product/miniz/master/src_format/src/zip.c */
/* <142f> /home/liu2598/Product/miniz/master/src_format/src/miniz.h:1141 */
typedef struct memfuzz_anonymous_struct_2 {
	unsigned int               m_file_index;         /*     0     4 */

	/* XXX 4 bytes hole, try to pack */

	long unsigned int          m_central_dir_ofs;    /*     8     8 */
	short unsigned int         m_version_made_by;    /*    16     2 */
	short unsigned int         m_version_needed;     /*    18     2 */
	short unsigned int         m_bit_flag;           /*    20     2 */
	short unsigned int         m_method;             /*    22     2 */
	long int                   m_time;               /*    24     8 */
	unsigned int               m_crc32;              /*    32     4 */

	/* XXX 4 bytes hole, try to pack */

	long unsigned int          m_comp_size;          /*    40     8 */
	long unsigned int          m_uncomp_size;        /*    48     8 */
	short unsigned int         m_internal_attr;      /*    56     2 */

	/* XXX 2 bytes hole, try to pack */

	unsigned int               m_external_attr;      /*    60     4 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	long unsigned int          m_local_header_ofs;   /*    64     8 */
	unsigned int               m_comment_size;       /*    72     4 */
	int                        m_is_directory;       /*    76     4 */
	int                        m_is_encrypted;       /*    80     4 */
	int                        m_is_supported;       /*    84     4 */
	char                       m_filename[512];      /*    88   512 */
	/* --- cacheline 9 boundary (576 bytes) was 24 bytes ago --- */
	char                       m_comment[512];       /*   600   512 */

	/* size: 1112, cachelines: 18, members: 19 */
	/* sum members: 1102, holes: 3, sum holes: 10 */
	/* last cacheline: 24 bytes */
} mz_zip_archive_file_stat;
/* Used at: /home/liu2598/Product/miniz/master/src_format/src/zip.c */
/* <15e1> /home/liu2598/Product/miniz/master/src_format/src/miniz.h:5121 */
struct mz_zip_internal_state_tag {
	struct {
		void *             m_p;                  /*     0     8 */
		long unsigned int  m_size;               /*     8     8 */
		long unsigned int  m_capacity;           /*    16     8 */
		unsigned int       m_element_size;       /*    24     4 */
	} m_central_dir; /*     0    32 */
	struct {
		void *             m_p;                  /*    32     8 */
		long unsigned int  m_size;               /*    40     8 */
		long unsigned int  m_capacity;           /*    48     8 */
		unsigned int       m_element_size;       /*    56     4 */
	} m_central_dir_offsets; /*    32    32 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	struct {
		void *             m_p;                  /*    64     8 */
		long unsigned int  m_size;               /*    72     8 */
		long unsigned int  m_capacity;           /*    80     8 */
		unsigned int       m_element_size;       /*    88     4 */
	} m_sorted_central_dir_offsets; /*    64    32 */
	unsigned int               m_init_flags;         /*    96     4 */
	int                        m_zip64;              /*   100     4 */
	int                        m_zip64_has_extended_info_fields; /*   104     4 */

	/* XXX 4 bytes hole, try to pack */

	struct _IO_FILE            *m_pFile;             /*   112     8 */
	long unsigned int          m_file_archive_start_ofs; /*   120     8 */
	/* --- cacheline 2 boundary (128 bytes) --- */
	void *                     m_pMem;               /*   128     8 */
	long unsigned int          m_mem_size;           /*   136     8 */
	long unsigned int          m_mem_capacity;       /*   144     8 */

	/* size: 152, cachelines: 3, members: 11 */
	/* sum members: 148, holes: 1, sum holes: 4 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/miniz/master/src_format/src/zip.c */
/* <1830> /home/liu2598/Product/miniz/master/src_format/src/miniz.h:1288 */
typedef struct memfuzz_anonymous_struct_3 {
	long unsigned int          m_archive_size;       /*     0     8 */
	long unsigned int          m_central_directory_file_ofs; /*     8     8 */
	unsigned int               m_total_files;        /*    16     4 */
	enum memfuzz_anonymous_enum_2 m_zip_mode;
	enum memfuzz_anonymous_enum_3 m_zip_type;
	enum memfuzz_anonymous_enum_4 m_last_error;
	long unsigned int          m_file_offset_alignment; /*    32     8 */
	void **m_pAlloc;                                                /*    40     8 */
	void **m_pFree;                                                /*    48     8 */
	void **m_pRealloc;                                                /*    56     8 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	void *                     m_pAlloc_opaque;      /*    64     8 */
	void **m_pRead;                                                /*    72     8 */
	void **m_pWrite;                                                /*    80     8 */
	void **m_pNeeds_keepalive;                                                /*    88     8 */
	void *                     m_pIO_opaque;         /*    96     8 */
	struct mz_zip_internal_state_tag *m_pState;      /*   104     8 */

	/* size: 112, cachelines: 2, members: 16 */
	/* last cacheline: 48 bytes */
} mz_zip_archive;
/* Used at: /home/liu2598/Product/miniz/master/src_format/src/zip.c */
/* <191c> /home/liu2598/Product/miniz/master/src_format/src/miniz.h:1314 */
typedef struct memfuzz_anonymous_struct_4 {
	struct {
		long unsigned int  m_archive_size;       /*     0     8 */
		long unsigned int  m_central_directory_file_ofs; /*     8     8 */
		unsigned int       m_total_files;        /*    16     4 */
	enum memfuzz_anonymous_enum_2 m_zip_mode;
	enum memfuzz_anonymous_enum_3 m_zip_type;
	enum memfuzz_anonymous_enum_4 m_last_error;
		long unsigned int  m_file_offset_alignment; /*    32     8 */
		void **m_pAlloc;                                        /*    40     8 */
		void **m_pFree;                                        /*    48     8 */
		void **m_pRealloc;                                        /*    56     8 */
		/* --- cacheline 1 boundary (64 bytes) --- */
		void *             m_pAlloc_opaque;      /*    64     8 */
		void **m_pRead;                                        /*    72     8 */
		void **m_pWrite;                                        /*    80     8 */
		void **m_pNeeds_keepalive;                                        /*    88     8 */
		void *             m_pIO_opaque;         /*    96     8 */
		struct mz_zip_internal_state_tag *m_pState; /*   104     8 */
	} *pZip; /*     0     8 */
	unsigned int               flags;                /*     8     4 */
	int                        status;               /*    12     4 */
	unsigned int               file_crc32;           /*    16     4 */

	/* XXX 4 bytes hole, try to pack */

	long unsigned int          read_buf_size;        /*    24     8 */
	long unsigned int          read_buf_ofs;         /*    32     8 */
	long unsigned int          read_buf_avail;       /*    40     8 */
	long unsigned int          comp_remaining;       /*    48     8 */
	long unsigned int          out_buf_ofs;          /*    56     8 */
	long unsigned int          cur_file_ofs;         /*    64     8 */
	struct {
		unsigned int       m_file_index;         /*    72     4 */

		/* XXX 4 bytes hole, try to pack */

		long unsigned int  m_central_dir_ofs;    /*    80     8 */
		short unsigned int m_version_made_by;    /*    88     2 */
		short unsigned int m_version_needed;     /*    90     2 */
		short unsigned int m_bit_flag;           /*    92     2 */
		short unsigned int m_method;             /*    94     2 */
		long int           m_time;               /*    96     8 */
		unsigned int       m_crc32;              /*   104     4 */

		/* XXX 4 bytes hole, try to pack */

		long unsigned int  m_comp_size;          /*   112     8 */
		long unsigned int  m_uncomp_size;        /*   120     8 */
		/* --- cacheline 2 boundary (128 bytes) --- */
		short unsigned int m_internal_attr;      /*   128     2 */

		/* XXX 2 bytes hole, try to pack */

		unsigned int       m_external_attr;      /*   132     4 */
		long unsigned int  m_local_header_ofs;   /*   136     8 */
		unsigned int       m_comment_size;       /*   144     4 */
		int                m_is_directory;       /*   148     4 */
		int                m_is_encrypted;       /*   152     4 */
		int                m_is_supported;       /*   156     4 */
		char               m_filename[512];      /*   160   512 */
		/* --- cacheline 10 boundary (640 bytes) was 32 bytes ago --- */
		char               m_comment[512];       /*   672   512 */
	} file_stat; /*    72  1112 */
	/* --- cacheline 18 boundary (1152 bytes) was 32 bytes ago --- */
	void *                     pRead_buf;            /*  1184     8 */
	void *                     pWrite_buf;           /*  1192     8 */
	long unsigned int          out_blk_remain;       /*  1200     8 */
	struct tinfl_decompressor_tag inflator;          /*  1208 11000 */

	/* size: 12208, cachelines: 191, members: 15 */
	/* sum members: 12204, holes: 1, sum holes: 4 */
	/* last cacheline: 48 bytes */
} mz_zip_reader_extract_iter_state;
/* Used at: /home/liu2598/Product/miniz/master/src_format/src/zip.c */
/* <1a00> /home/liu2598/Product/miniz/master/src_format/src/miniz.h:2111 */
typedef struct memfuzz_anonymous_struct_5 {
	struct tinfl_decompressor_tag m_decomp;          /*     0 11000 */
	/* --- cacheline 171 boundary (10944 bytes) was 56 bytes ago --- */
	unsigned int               m_dict_ofs;           /* 11000     4 */
	unsigned int               m_dict_avail;         /* 11004     4 */
	/* --- cacheline 172 boundary (11008 bytes) --- */
	unsigned int               m_first_call;         /* 11008     4 */
	unsigned int               m_has_flushed;        /* 11012     4 */
	int                        m_window_bits;        /* 11016     4 */
	unsigned char              m_dict[32768];        /* 11020 32768 */
	/* --- cacheline 684 boundary (43776 bytes) was 12 bytes ago --- */
	enum memfuzz_anonymous_enum_5 m_last_status;

	/* size: 43792, cachelines: 685, members: 8 */
	/* last cacheline: 16 bytes */
} inflate_state;
/* Used at: /home/liu2598/Product/miniz/master/src_format/src/zip.c */
/* <1b70> /home/liu2598/Product/miniz/master/src_format/src/miniz.h:2545 */
typedef struct memfuzz_anonymous_struct_6 {
	short unsigned int         m_key;                /*     0     2 */
	short unsigned int         m_sym_index;          /*     2     2 */

	/* size: 4, cachelines: 1, members: 2 */
	/* last cacheline: 4 bytes */
} tdefl_sym_freq;
/* Used at: /home/liu2598/Product/miniz/master/src_format/src/zip.c */
/* <1c06> /home/liu2598/Product/miniz/master/src_format/src/miniz.h:3823 */
typedef struct memfuzz_anonymous_struct_7 {
	long unsigned int          m_size;               /*     0     8 */
	long unsigned int          m_capacity;           /*     8     8 */
	unsigned char              *m_pBuf;              /*    16     8 */
	int                        m_expandable;         /*    24     4 */

	/* size: 32, cachelines: 1, members: 4 */
	/* padding: 4 */
	/* last cacheline: 32 bytes */
} tdefl_output_buffer;
/* Used at: /home/liu2598/Product/miniz/master/src_format/src/zip.c */
/* <1e73> /home/liu2598/Product/miniz/master/src_format/src/miniz.h:5115 */
typedef struct memfuzz_anonymous_struct_8 {
	void *                     m_p;                  /*     0     8 */
	long unsigned int          m_size;               /*     8     8 */
	long unsigned int          m_capacity;           /*    16     8 */
	unsigned int               m_element_size;       /*    24     4 */

	/* size: 32, cachelines: 1, members: 4 */
	/* padding: 4 */
	/* last cacheline: 32 bytes */
} mz_zip_array;
/* Used at: /home/liu2598/Product/miniz/master/src_format/src/zip.c */
/* <1ecd> /home/liu2598/Product/miniz/master/src_format/src/miniz.h:8170 */
typedef struct memfuzz_anonymous_struct_9 {
	struct {
		long unsigned int  m_archive_size;       /*     0     8 */
		long unsigned int  m_central_directory_file_ofs; /*     8     8 */
		unsigned int       m_total_files;        /*    16     4 */
	enum memfuzz_anonymous_enum_2 m_zip_mode;
	enum memfuzz_anonymous_enum_3 m_zip_type;
	enum memfuzz_anonymous_enum_4 m_last_error;
		long unsigned int  m_file_offset_alignment; /*    32     8 */
		void **m_pAlloc;                                        /*    40     8 */
		void **m_pFree;                                        /*    48     8 */
		void **m_pRealloc;                                        /*    56     8 */
		/* --- cacheline 1 boundary (64 bytes) --- */
		void *             m_pAlloc_opaque;      /*    64     8 */
		void **m_pRead;                                        /*    72     8 */
		void **m_pWrite;                                        /*    80     8 */
		void **m_pNeeds_keepalive;                                        /*    88     8 */
		void *             m_pIO_opaque;         /*    96     8 */
		struct mz_zip_internal_state_tag *m_pState; /*   104     8 */
	} *m_pZip; /*     0     8 */
	long unsigned int          m_cur_archive_file_ofs; /*     8     8 */
	long unsigned int          m_comp_size;          /*    16     8 */

	/* size: 24, cachelines: 1, members: 3 */
	/* last cacheline: 24 bytes */
} mz_zip_writer_add_state;
/* Used at: /home/liu2598/Product/miniz/master/src_format/src/zip.c */
/* <1f0a> /home/liu2598/Product/miniz/master/src_format/src/zip.c:84 */
struct zip_entry_t {
	long int                   index;                /*     0     8 */
	char                       *name;                /*     8     8 */
	long unsigned int          uncomp_size;          /*    16     8 */
	long unsigned int          comp_size;            /*    24     8 */
	unsigned int               uncomp_crc32;         /*    32     4 */

	/* XXX 4 bytes hole, try to pack */

	long unsigned int          offset;               /*    40     8 */
	unsigned char              header[30];           /*    48    30 */

	/* XXX 2 bytes hole, try to pack */

	/* --- cacheline 1 boundary (64 bytes) was 16 bytes ago --- */
	long unsigned int          header_offset;        /*    80     8 */
	short unsigned int         method;               /*    88     2 */

	/* XXX 6 bytes hole, try to pack */

	struct {
		struct {
			long unsigned int m_archive_size; /*    96     8 */
			long unsigned int m_central_directory_file_ofs; /*   104     8 */
			unsigned int m_total_files;      /*   112     4 */
	enum memfuzz_anonymous_enum_2 m_zip_mode;
	enum memfuzz_anonymous_enum_3 m_zip_type;
	enum memfuzz_anonymous_enum_4 m_last_error;
			/* --- cacheline 2 boundary (128 bytes) --- */
			long unsigned int m_file_offset_alignment; /*   128     8 */
			void **m_pAlloc;                                /*   136     8 */
			void **m_pFree;                                /*   144     8 */
			void **m_pRealloc;                                /*   152     8 */
			void *     m_pAlloc_opaque;      /*   160     8 */
			void **m_pRead;                                /*   168     8 */
			void **m_pWrite;                                /*   176     8 */
			void **m_pNeeds_keepalive;                                /*   184     8 */
			/* --- cacheline 3 boundary (192 bytes) --- */
			void *     m_pIO_opaque;         /*   192     8 */
			struct mz_zip_internal_state_tag *m_pState; /*   200     8 */
		} *m_pZip; /*    96     8 */
		long unsigned int  m_cur_archive_file_ofs; /*   104     8 */
		long unsigned int  m_comp_size;          /*   112     8 */
	} state; /*    96    24 */
	struct {
		void **m_pPut_buf_func;                                        /*   120     8 */
		void *             m_pPut_buf_user;      /*   128     8 */
		unsigned int       m_flags;              /*   136     4 */
		unsigned int       m_max_probes[2];      /*   140     8 */
		int                m_greedy_parsing;     /*   148     4 */
		unsigned int       m_adler32;            /*   152     4 */
		unsigned int       m_lookahead_pos;      /*   156     4 */
		unsigned int       m_lookahead_size;     /*   160     4 */
		unsigned int       m_dict_size;          /*   164     4 */
		unsigned char      *m_pLZ_code_buf;      /*   168     8 */
		unsigned char      *m_pLZ_flags;         /*   176     8 */
		unsigned char      *m_pOutput_buf;       /*   184     8 */
		unsigned char      *m_pOutput_buf_end;   /*   192     8 */
		unsigned int       m_num_flags_left;     /*   200     4 */
		unsigned int       m_total_lz_bytes;     /*   204     4 */
		unsigned int       m_lz_code_buf_dict_pos; /*   208     4 */
		unsigned int       m_bits_in;            /*   212     4 */
		unsigned int       m_bit_buffer;         /*   216     4 */
		unsigned int       m_saved_match_dist;   /*   220     4 */
		unsigned int       m_saved_match_len;    /*   224     4 */
		unsigned int       m_saved_lit;          /*   228     4 */
		unsigned int       m_output_flush_ofs;   /*   232     4 */
		unsigned int       m_output_flush_remaining; /*   236     4 */
		unsigned int       m_finished;           /*   240     4 */
		unsigned int       m_block_index;        /*   244     4 */
		unsigned int       m_wants_to_finish;    /*   248     4 */
	enum memfuzz_anonymous_enum_0 m_prev_return_status;
		/* --- cacheline 4 boundary (256 bytes) --- */
		void*              *m_pIn_buf;           /*   256     8 */
		void *             m_pOut_buf;           /*   264     8 */
		long unsigned int  *m_pIn_buf_size;      /*   272     8 */
		long unsigned int  *m_pOut_buf_size;     /*   280     8 */
	enum memfuzz_anonymous_enum_1 m_flush;

		/* XXX 4 bytes hole, try to pack */

		unsigned char      *m_pSrc;              /*   296     8 */
		long unsigned int  m_src_buf_left;       /*   304     8 */
		long unsigned int  m_out_buf_ofs;        /*   312     8 */
		/* --- cacheline 5 boundary (320 bytes) --- */
		unsigned char      m_dict[33025];        /*   320 33025 */

		/* XXX 1 byte hole, try to pack */

		/* --- cacheline 521 boundary (33344 bytes) was 2 bytes ago --- */
		short unsigned int m_huff_count[3][288]; /* 33346  1728 */
		/* --- cacheline 548 boundary (35072 bytes) was 2 bytes ago --- */
		short unsigned int m_huff_codes[3][288]; /* 35074  1728 */
		/* --- cacheline 575 boundary (36800 bytes) was 2 bytes ago --- */
		unsigned char      m_huff_code_sizes[3][288]; /* 36802   864 */
		/* --- cacheline 588 boundary (37632 bytes) was 34 bytes ago --- */
		unsigned char      m_lz_code_buf[65536]; /* 37666 65536 */
		/* --- cacheline 1612 boundary (103168 bytes) was 34 bytes ago --- */
		short unsigned int m_next[32768];        /* 103202 65536 */
		/* --- cacheline 2636 boundary (168704 bytes) was 34 bytes ago --- */
		short unsigned int m_hash[32768];        /* 168738 65536 */
		/* --- cacheline 3660 boundary (234240 bytes) was 34 bytes ago --- */
		unsigned char      m_output_buf[85196];  /* 234274 85196 */
	} comp; /*   120 319352 */
	/* --- cacheline 4991 boundary (319424 bytes) was 48 bytes ago --- */
	unsigned int               external_attr;        /* 319472     4 */

	/* XXX 4 bytes hole, try to pack */

	long int                   m_time;               /* 319480     8 */

	/* size: 319488, cachelines: 4992, members: 13 */
	/* sum members: 319472, holes: 4, sum holes: 16 */
};
/* Used at: /home/liu2598/Product/miniz/master/src_format/src/zip.c */
/* <1fcc> /home/liu2598/Product/miniz/master/src_format/src/zip.c:100 */
struct zip_t {
	struct {
		long unsigned int  m_archive_size;       /*     0     8 */
		long unsigned int  m_central_directory_file_ofs; /*     8     8 */
		unsigned int       m_total_files;        /*    16     4 */
	enum memfuzz_anonymous_enum_2 m_zip_mode;
	enum memfuzz_anonymous_enum_3 m_zip_type;
	enum memfuzz_anonymous_enum_4 m_last_error;
		long unsigned int  m_file_offset_alignment; /*    32     8 */
		void **m_pAlloc;                                        /*    40     8 */
		void **m_pFree;                                        /*    48     8 */
		void **m_pRealloc;                                        /*    56     8 */
		/* --- cacheline 1 boundary (64 bytes) --- */
		void *             m_pAlloc_opaque;      /*    64     8 */
		void **m_pRead;                                        /*    72     8 */
		void **m_pWrite;                                        /*    80     8 */
		void **m_pNeeds_keepalive;                                        /*    88     8 */
		void *             m_pIO_opaque;         /*    96     8 */
		struct mz_zip_internal_state_tag *m_pState; /*   104     8 */
	} archive; /*     0   112 */
	unsigned int               level;                /*   112     4 */

	/* XXX 4 bytes hole, try to pack */

	struct zip_entry_t         entry;                /*   120 319488 */

	/* size: 319608, cachelines: 4994, members: 3 */
	/* sum members: 319604, holes: 1, sum holes: 4 */
	/* last cacheline: 56 bytes */
};
/* Used at: /home/liu2598/Product/miniz/master/src_format/src/zip.c */
/* <2024> /home/liu2598/Product/miniz/master/src_format/src/zip.c:112 */
struct zip_entry_mark_t {
	long int                   file_index;           /*     0     8 */
	enum zip_modify_t          type;                 /*     8     4 */

	/* XXX 4 bytes hole, try to pack */

	long unsigned int          m_local_header_ofs;   /*    16     8 */
	long unsigned int          lf_length;            /*    24     8 */

	/* size: 32, cachelines: 1, members: 4 */
	/* sum members: 28, holes: 1, sum holes: 4 */
	/* last cacheline: 32 bytes */
};
/* Used at: /home/liu2598/Product/miniz/master/src_format/src/zip.c */
/* <157b2> /home/liu2598/Product/miniz/master/src_format/src/miniz.h:2354 */
struct memfuzz_anonymous_struct_10 {
	int                        m_err;                /*     0     4 */

	/* XXX 4 bytes hole, try to pack */

	char                       *m_pDesc;             /*     8     8 */

	/* size: 16, cachelines: 1, members: 2 */
	/* sum members: 12, holes: 1, sum holes: 4 */
	/* last cacheline: 16 bytes */
};
#endif
