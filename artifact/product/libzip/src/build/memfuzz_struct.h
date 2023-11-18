#ifndef _MEMFUZZ_STRUCT_H_
#define _MEMFUZZ_STRUCT_H_
#include <zlib.h>
/*Add necessary header here to avoid compile problems*/
/*Struct Declaration Begin*/
struct zip_error;
struct zip_stat;
struct dispatch_table_s;
struct progress_userdata_s;
struct zip_file_attributes;
struct zip;
struct zip_source;
struct zip_compression_algorithm;
struct _zip_err_info;
struct zip_dirent;
struct zip_entry;
struct zip_extra_field;
struct zip_string;
union memfuzz_anonymous_struct_0;
union memfuzz_anonymous_struct_1;
struct zip_buffer;
union memfuzz_anonymous_struct_2;
struct zip_filelist;
union memfuzz_anonymous_struct_3;
union memfuzz_anonymous_struct_4;
struct zip_cdir;
union memfuzz_anonymous_struct_5;
union memfuzz_anonymous_struct_6;
union memfuzz_anonymous_struct_7;
union memfuzz_anonymous_struct_8;
union memfuzz_anonymous_struct_9;
union memfuzz_anonymous_struct_10;
union memfuzz_anonymous_struct_11;
union memfuzz_anonymous_struct_12;
union memfuzz_anonymous_struct_13;
union memfuzz_anonymous_struct_14;
union memfuzz_anonymous_struct_15;
union memfuzz_anonymous_struct_16;
union memfuzz_anonymous_struct_17;
union memfuzz_anonymous_struct_18;
union memfuzz_anonymous_struct_19;
union memfuzz_anonymous_struct_20;
union memfuzz_anonymous_struct_21;
union memfuzz_anonymous_struct_22;
union memfuzz_anonymous_struct_23;
struct zip_hash;
struct zip_hash_entry;
union memfuzz_anonymous_struct_24;
union memfuzz_anonymous_struct_25;
union memfuzz_anonymous_struct_26;
struct zip_progress;
union memfuzz_anonymous_struct_27;
struct legacy_ud;
union memfuzz_anonymous_struct_28;
union memfuzz_anonymous_struct_29;
union memfuzz_anonymous_struct_30;
union memfuzz_anonymous_struct_31;
union memfuzz_anonymous_struct_32;
union memfuzz_anonymous_struct_33;
union memfuzz_anonymous_struct_34;
union memfuzz_anonymous_struct_35;
struct zip_buffer_fragment;
union memfuzz_anonymous_struct_36;
struct buffer;
struct read_data;
union memfuzz_anonymous_struct_37;
union memfuzz_anonymous_struct_38;
union memfuzz_anonymous_struct_39;
union memfuzz_anonymous_struct_40;
struct context;
struct implementation;
struct zip_source_args_seek;
union memfuzz_anonymous_struct_41;
struct crc_context;
union memfuzz_anonymous_struct_42;
union memfuzz_anonymous_struct_43;
struct zip_source_file_stat;
struct zip_source_file_context;
struct zip_source_file_operations;
union memfuzz_anonymous_struct_44;
union memfuzz_anonymous_struct_45;
union memfuzz_anonymous_struct_46;
union memfuzz_anonymous_struct_47;
union memfuzz_anonymous_struct_48;
union memfuzz_anonymous_struct_49;
struct _zip_pkware_keys;
struct trad_pkware;
union memfuzz_anonymous_struct_50;
union memfuzz_anonymous_struct_51;
union memfuzz_anonymous_struct_52;
union memfuzz_anonymous_struct_53;
union memfuzz_anonymous_struct_54;
union memfuzz_anonymous_struct_55;
union memfuzz_anonymous_struct_56;
struct __va_list_tag;
union memfuzz_anonymous_struct_57;
union memfuzz_anonymous_struct_58;
union memfuzz_anonymous_struct_59;
union memfuzz_anonymous_struct_60;
struct window;
union memfuzz_anonymous_struct_61;
union memfuzz_anonymous_struct_62;
union memfuzz_anonymous_struct_63;
union memfuzz_anonymous_struct_64;
union memfuzz_anonymous_struct_65;
union memfuzz_anonymous_struct_66;
union memfuzz_anonymous_struct_67;
union memfuzz_anonymous_struct_68;
union memfuzz_anonymous_struct_69;
union memfuzz_anonymous_struct_70;
struct winzip_aes;
union memfuzz_anonymous_struct_71;
union memfuzz_anonymous_struct_72;
struct ctx;
union memfuzz_anonymous_struct_73;
union memfuzz_anonymous_struct_74;
union memfuzz_anonymous_struct_75;
union memfuzz_anonymous_struct_76;
union memfuzz_anonymous_struct_77;
struct _zip_winzip_aes;
/*Enumeration Definition Begin*/
enum zip_source_write_state {
		ZIP_SOURCE_WRITE_CLOSED  = 0,
		ZIP_SOURCE_WRITE_OPEN    = 1,
		ZIP_SOURCE_WRITE_FAILED  = 2,
		ZIP_SOURCE_WRITE_REMOVED = 3,
	};
enum zip_encoding_type {
		ZIP_ENCODING_UNKNOWN      = 0,
		ZIP_ENCODING_ASCII        = 1,
		ZIP_ENCODING_UTF8_KNOWN   = 2,
		ZIP_ENCODING_UTF8_GUESSED = 3,
		ZIP_ENCODING_CP437        = 4,
		ZIP_ENCODING_ERROR        = 5,
	};
/*Struct Definition Begin*/
/* Used at: /home/liu2598/Product/libzip/master/src_format/src/ziptool.c */
/* <547> /home/liu2598/Product/libzip/master/src_format/lib/zip.h:285 */
struct zip_error {
	int                        zip_err;              /*     0     4 */
	int                        sys_err;              /*     4     4 */
	char                       *str;                 /*     8     8 */

	/* size: 16, cachelines: 1, members: 3 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/src/ziptool.c */
/* <57c> /home/liu2598/Product/libzip/master/src_format/lib/zip.h:301 */
struct zip_stat {
	long unsigned int          valid;                /*     0     8 */
	char                       *name;                /*     8     8 */
	long unsigned int          index;                /*    16     8 */
	long unsigned int          size;                 /*    24     8 */
	long unsigned int          comp_size;            /*    32     8 */
	long int                   mtime;                /*    40     8 */
	unsigned int               crc;                  /*    48     4 */
	short unsigned int         comp_method;          /*    52     2 */
	short unsigned int         encryption_method;    /*    54     2 */
	unsigned int               flags;                /*    56     4 */

	/* size: 64, cachelines: 1, members: 10 */
	/* padding: 4 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/src/ziptool.c */
/* <64c> /home/liu2598/Product/libzip/master/src_format/src/ziptool.c:60 */
struct dispatch_table_s {
	char                       *cmdline_name;        /*     0     8 */
	int                        argument_count;       /*     8     4 */

	/* XXX 4 bytes hole, try to pack */

	char                       *arg_names;           /*    16     8 */
	char                       *description;         /*    24     8 */
	void **function;                                                /*    32     8 */

	/* size: 40, cachelines: 1, members: 5 */
	/* sum members: 36, holes: 1, sum holes: 4 */
	/* last cacheline: 40 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/src/ziptool.c */
/* <718> /home/liu2598/Product/libzip/master/src_format/src/ziptool.c:434 */
struct progress_userdata_s {
	double                     percentage;           /*     0     8 */
	double                     limit;                /*     8     8 */

	/* size: 16, cachelines: 1, members: 2 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_add.c */
/* <58dd> /home/liu2598/Product/libzip/master/src_format/lib/zip.h:319 */
struct zip_file_attributes {
	long unsigned int          valid;                /*     0     8 */
	unsigned char              version;              /*     8     1 */
	unsigned char              host_system;          /*     9     1 */
	unsigned char              ascii;                /*    10     1 */
	unsigned char              version_needed;       /*    11     1 */
	unsigned int               external_file_attributes; /*    12     4 */
	short unsigned int         general_purpose_bit_flags; /*    16     2 */
	short unsigned int         general_purpose_bit_mask; /*    18     2 */

	/* size: 24, cachelines: 1, members: 8 */
	/* padding: 4 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_add.c */
/* <595f> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:279 */
struct zip {
	struct zip_source          *src;                 /*     0     8 */
	unsigned int               open_flags;           /*     8     4 */

	/* XXX 4 bytes hole, try to pack */

	struct zip_error           error;                /*    16    16 */
	unsigned int               flags;                /*    32     4 */
	unsigned int               ch_flags;             /*    36     4 */
	char                       *default_password;    /*    40     8 */
	struct zip_string          *comment_orig;        /*    48     8 */
	struct zip_string          *comment_changes;     /*    56     8 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	_Bool                      comment_changed;      /*    64     1 */

	/* XXX 7 bytes hole, try to pack */

	long unsigned int          nentry;               /*    72     8 */
	long unsigned int          nentry_alloc;         /*    80     8 */
	struct zip_entry           *entry;               /*    88     8 */
	unsigned int               nopen_source;         /*    96     4 */
	unsigned int               nopen_source_alloc;   /*   100     4 */
	struct zip_source          **open_source;        /*   104     8 */
	struct zip_hash            *names;               /*   112     8 */
	struct zip_progress        *progress;            /*   120     8 */

	/* size: 128, cachelines: 2, members: 17 */
	/* sum members: 117, holes: 2, sum holes: 11 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_add.c */
/* <5a6e> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:383 */
struct zip_source {
	struct zip_source          *src;                 /*     0     8 */
	union {
		void **f;                                        /*     8     8 */
		void **l;                                        /*     8     8 */
	} cb;                                            /*     8     8 */
	void *                     ud;                   /*    16     8 */
	struct zip_error           error;                /*    24    16 */
	long int                   supports;             /*    40     8 */
	unsigned int               open_count;           /*    48     4 */
	enum zip_source_write_state write_state;         /*    52     4 */
	_Bool                      source_closed;        /*    56     1 */

	/* XXX 7 bytes hole, try to pack */

	/* --- cacheline 1 boundary (64 bytes) --- */
	struct zip                 *source_archive;      /*    64     8 */
	unsigned int               refcount;             /*    72     4 */
	_Bool                      eof;                  /*    76     1 */
	_Bool                      had_read_error;       /*    77     1 */

	/* XXX 2 bytes hole, try to pack */

	long unsigned int          bytes_read;           /*    80     8 */

	/* size: 88, cachelines: 2, members: 13 */
	/* sum members: 79, holes: 2, sum holes: 9 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_add.c */
/* <5bb3> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:124 */
struct zip_compression_algorithm {
	void **maximum_compressed_size;                                                /*     0     8 */
	void **allocate;                                                /*     8     8 */
	void **deallocate;                                                /*    16     8 */
	void **general_purpose_bit_flags;                                                /*    24     8 */
	unsigned char              version_needed;       /*    32     1 */

	/* XXX 7 bytes hole, try to pack */

	void **start;                                                /*    40     8 */
	void **end;                                                /*    48     8 */
	void **input;                                                /*    56     8 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	void **end_of_input;                                                /*    64     8 */
	void **process;                                                /*    72     8 */

	/* size: 80, cachelines: 2, members: 10 */
	/* sum members: 73, holes: 1, sum holes: 7 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_add.c */
/* <5dba> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:196 */
struct _zip_err_info {
	int                        type;                 /*     0     4 */

	/* XXX 4 bytes hole, try to pack */

	char                       *description;         /*     8     8 */

	/* size: 16, cachelines: 1, members: 2 */
	/* sum members: 12, holes: 1, sum holes: 4 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_add.c */
/* <5e62> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:326 */
struct zip_dirent {
	unsigned int               changed;              /*     0     4 */
	_Bool                      local_extra_fields_read; /*     4     1 */
	_Bool                      cloned;               /*     5     1 */
	_Bool                      crc_valid;            /*     6     1 */

	/* XXX 1 byte hole, try to pack */

	short unsigned int         version_madeby;       /*     8     2 */
	short unsigned int         version_needed;       /*    10     2 */
	short unsigned int         bitflags;             /*    12     2 */

	/* XXX 2 bytes hole, try to pack */

	int                        comp_method;          /*    16     4 */

	/* XXX 4 bytes hole, try to pack */

	long int                   last_mod;             /*    24     8 */
	unsigned int               crc;                  /*    32     4 */

	/* XXX 4 bytes hole, try to pack */

	long unsigned int          comp_size;            /*    40     8 */
	long unsigned int          uncomp_size;          /*    48     8 */
	struct zip_string          *filename;            /*    56     8 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	struct zip_extra_field     *extra_fields;        /*    64     8 */
	struct zip_string          *comment;             /*    72     8 */
	unsigned int               disk_number;          /*    80     4 */
	short unsigned int         int_attrib;           /*    84     2 */

	/* XXX 2 bytes hole, try to pack */

	unsigned int               ext_attrib;           /*    88     4 */

	/* XXX 4 bytes hole, try to pack */

	long unsigned int          offset;               /*    96     8 */
	short unsigned int         compression_level;    /*   104     2 */
	short unsigned int         encryption_method;    /*   106     2 */

	/* XXX 4 bytes hole, try to pack */

	char                       *password;            /*   112     8 */

	/* size: 120, cachelines: 2, members: 22 */
	/* sum members: 99, holes: 7, sum holes: 21 */
	/* last cacheline: 56 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_add.c */
/* <5f9a> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:408 */
struct zip_entry {
	struct zip_dirent          *orig;                /*     0     8 */
	struct zip_dirent          *changes;             /*     8     8 */
	struct zip_source          *source;              /*    16     8 */
	_Bool                      deleted;              /*    24     1 */

	/* size: 32, cachelines: 1, members: 4 */
	/* padding: 7 */
	/* last cacheline: 32 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_add.c */
/* <5fe8> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:367 */
struct zip_extra_field {
	struct zip_extra_field     *next;                /*     0     8 */
	unsigned int               flags;                /*     8     4 */
	short unsigned int         id;                   /*    12     2 */
	short unsigned int         size;                 /*    14     2 */
	unsigned char              *data;                /*    16     8 */

	/* size: 24, cachelines: 1, members: 5 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_add.c */
/* <6042> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:418 */
struct zip_string {
	unsigned char              *raw;                 /*     0     8 */
	short unsigned int         length;               /*     8     2 */

	/* XXX 2 bytes hole, try to pack */

	enum zip_encoding_type     encoding;             /*    12     4 */
	unsigned char              *converted;           /*    16     8 */
	unsigned int               converted_length;     /*    24     4 */

	/* size: 32, cachelines: 1, members: 5 */
	/* sum members: 26, holes: 1, sum holes: 2 */
	/* padding: 4 */
	/* last cacheline: 32 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_add.c */
/* <610e> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_0 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_add_dir.c */
/* <6f8c> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_1 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_close.c */
/* <7dc1> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:446 */
struct zip_buffer {
	_Bool                      ok;                   /*     0     1 */
	_Bool                      free_data;            /*     1     1 */

	/* XXX 6 bytes hole, try to pack */

	unsigned char              *data;                /*     8     8 */
	long unsigned int          size;                 /*    16     8 */
	long unsigned int          offset;               /*    24     8 */

	/* size: 32, cachelines: 1, members: 5 */
	/* sum members: 26, holes: 1, sum holes: 6 */
	/* last cacheline: 32 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_close.c */
/* <7e8c> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_2 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_close.c */
/* <7eb0> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:457 */
struct zip_filelist {
	long unsigned int          idx;                  /*     0     8 */

	/* size: 8, cachelines: 1, members: 1 */
	/* last cacheline: 8 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_delete.c */
/* <a328> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_3 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_dir_add.c */
/* <b250> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_4 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_dirent.c */
/* <c17f> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:356 */
struct zip_cdir {
	struct zip_entry           *entry;               /*     0     8 */
	long unsigned int          nentry;               /*     8     8 */
	long unsigned int          nentry_alloc;         /*    16     8 */
	long unsigned int          size;                 /*    24     8 */
	long unsigned int          offset;               /*    32     8 */
	struct zip_string          *comment;             /*    40     8 */
	_Bool                      is_zip64;             /*    48     1 */

	/* size: 56, cachelines: 1, members: 7 */
	/* padding: 7 */
	/* last cacheline: 56 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_dirent.c */
/* <c4ff> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_5 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_discard.c */
/* <104b5> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_6 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_entry.c */
/* <11412> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_7 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_error.c */
/* <122b1> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_8 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_extra_field.c */
/* <1425d> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_9 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_extra_field_api.c */
/* <1638d> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_10 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_fdopen.c */
/* <17cc2> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_11 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_file_add.c */
/* <18e01> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_12 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_file_get_offset.c */
/* <19ccc> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_13 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_file_replace.c */
/* <1ae73> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_14 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_file_set_comment.c */
/* <1bfc4> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_15 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_file_set_encryption.c */
/* <1cffb> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_16 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_file_set_external_attributes.c */
/* <1e156> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_17 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_file_set_mtime.c */
/* <1f0a5> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_18 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_get_archive_comment.c */
/* <2017c> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_19 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_get_encryption_implementation.c */
/* <21075> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_20 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_get_file_comment.c */
/* <21f23> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_21 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_get_name.c */
/* <22df1> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_22 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_get_num_entries.c */
/* <23ddf> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_23 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_hash.c */
/* <24662> /home/liu2598/Product/libzip/master/src_format/lib/zip_hash.c:59 */
struct zip_hash {
	unsigned int               table_size;           /*     0     4 */

	/* XXX 4 bytes hole, try to pack */

	long unsigned int          nentries;             /*     8     8 */
	struct zip_hash_entry      **table;              /*    16     8 */

	/* size: 24, cachelines: 1, members: 3 */
	/* sum members: 20, holes: 1, sum holes: 4 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_hash.c */
/* <24699> /home/liu2598/Product/libzip/master/src_format/lib/zip_hash.c:50 */
struct zip_hash_entry {
	unsigned char              *name;                /*     0     8 */
	long int                   orig_index;           /*     8     8 */
	long int                   current_index;        /*    16     8 */
	struct zip_hash_entry      *next;                /*    24     8 */
	unsigned int               hash_value;           /*    32     4 */

	/* size: 40, cachelines: 1, members: 5 */
	/* padding: 4 */
	/* last cacheline: 40 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_io_util.c */
/* <26252> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_24 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_name_locate.c */
/* <281e4> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_25 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_open.c */
/* <2945d> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_26 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_progress.c */
/* <2c76e> /home/liu2598/Product/libzip/master/src_format/lib/zip_progress.c:41 */
struct zip_progress {
	struct zip                 *za;                  /*     0     8 */
	void **callback_progress;                                                /*     8     8 */
	void **ud_progress_free;                                                /*    16     8 */
	void *                     ud_progress;          /*    24     8 */
	void **callback_cancel;                                                /*    32     8 */
	void **ud_cancel_free;                                                /*    40     8 */
	void *                     ud_cancel;            /*    48     8 */
	double                     precision;            /*    56     8 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	double                     last_update;          /*    64     8 */
	double                     start;                /*    72     8 */
	double                     end;                  /*    80     8 */

	/* size: 88, cachelines: 2, members: 11 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_progress.c */
/* <2c859> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_27 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_progress.c */
/* <2c87d> /home/liu2598/Product/libzip/master/src_format/lib/zip_progress.c:264 */
struct legacy_ud {
	void **callback;                                                /*     0     8 */

	/* size: 8, cachelines: 1, members: 1 */
	/* last cacheline: 8 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_rename.c */
/* <2e15d> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_28 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_set_archive_comment.c */
/* <2efdb> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_29 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_set_default_password.c */
/* <2ff79> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_30 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_set_file_compression.c */
/* <30e1a> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_31 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_set_name.c */
/* <31d7f> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_32 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_accept_empty.c */
/* <32f2e> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_33 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_begin_write.c */
/* <33dbc> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_34 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_begin_write_cloning.c */
/* <34c46> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_35 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_buffer.c */
/* <352c0> /home/liu2598/Product/libzip/master/src_format/lib/zip.h:314 */
struct zip_buffer_fragment {
	unsigned char              *data;                /*     0     8 */
	long unsigned int          length;               /*     8     8 */

	/* size: 16, cachelines: 1, members: 2 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_buffer.c */
/* <35b30> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_36 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_buffer.c */
/* <35b54> /home/liu2598/Product/libzip/master/src_format/lib/zip_source_buffer.c:43 */
struct buffer {
	struct zip_buffer_fragment *fragments;           /*     0     8 */
	long unsigned int          *fragment_offsets;    /*     8     8 */
	long unsigned int          nfragments;           /*    16     8 */
	long unsigned int          fragments_capacity;   /*    24     8 */
	long unsigned int          first_owned_fragment; /*    32     8 */
	long unsigned int          shared_fragments;     /*    40     8 */
	struct buffer              *shared_buffer;       /*    48     8 */
	long unsigned int          size;                 /*    56     8 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	long unsigned int          offset;               /*    64     8 */
	long unsigned int          current_fragment;     /*    72     8 */

	/* size: 80, cachelines: 2, members: 10 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_buffer.c */
/* <35bf5> /home/liu2598/Product/libzip/master/src_format/lib/zip_source_buffer.c:61 */
struct read_data {
	struct zip_error           error;                /*     0    16 */
	long int                   mtime;                /*    16     8 */
	struct zip_file_attributes attributes;           /*    24    24 */
	struct buffer              *in;                  /*    48     8 */
	struct buffer              *out;                 /*    56     8 */

	/* size: 64, cachelines: 1, members: 5 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_call.c */
/* <3a9c9> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_37 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_close.c */
/* <3b909> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_38 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_commit_write.c */
/* <3c858> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_39 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_compress.c */
/* <3d72e> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_40 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_compress.c */
/* <3d752> /home/liu2598/Product/libzip/master/src_format/lib/zip_source_compress.c:39 */
struct context {
	struct zip_error           error;                /*     0    16 */
	_Bool                      end_of_input;         /*    16     1 */
	_Bool                      end_of_stream;        /*    17     1 */
	_Bool                      can_store;            /*    18     1 */
	_Bool                      is_stored;            /*    19     1 */
	_Bool                      compress;             /*    20     1 */

	/* XXX 3 bytes hole, try to pack */

	int                        method;               /*    24     4 */

	/* XXX 4 bytes hole, try to pack */

	long unsigned int          size;                 /*    32     8 */
	long int                   first_read;           /*    40     8 */
	unsigned char              buffer[8192];         /*    48  8192 */
	/* --- cacheline 128 boundary (8192 bytes) was 48 bytes ago --- */
	struct zip_compression_algorithm *algorithm;     /*  8240     8 */
	void *                     ud;                   /*  8248     8 */

	/* size: 8256, cachelines: 129, members: 12 */
	/* sum members: 8249, holes: 2, sum holes: 7 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_compress.c */
/* <3d808> /home/liu2598/Product/libzip/master/src_format/lib/zip_source_compress.c:58 */
struct implementation {
	short unsigned int         method;               /*     0     2 */

	/* XXX 6 bytes hole, try to pack */

	struct zip_compression_algorithm *compress;      /*     8     8 */
	struct zip_compression_algorithm *decompress;    /*    16     8 */

	/* size: 24, cachelines: 1, members: 3 */
	/* sum members: 18, holes: 1, sum holes: 6 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_crc.c */
/* <3ea06> /home/liu2598/Product/libzip/master/src_format/lib/zip.h:274 */
struct zip_source_args_seek {
	long int                   offset;               /*     0     8 */
	int                        whence;               /*     8     4 */

	/* size: 16, cachelines: 1, members: 2 */
	/* padding: 4 */
	/* last cacheline: 16 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_crc.c */
/* <3f336> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_41 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_crc.c */
/* <3f35a> /home/liu2598/Product/libzip/master/src_format/lib/zip_source_crc.c:41 */
struct crc_context {
	int                        validate;             /*     0     4 */
	int                        crc_complete;         /*     4     4 */
	struct zip_error           error;                /*     8    16 */
	long unsigned int          size;                 /*    24     8 */
	long unsigned int          position;             /*    32     8 */
	long unsigned int          crc_position;         /*    40     8 */
	unsigned int               crc;                  /*    48     4 */

	/* size: 56, cachelines: 1, members: 7 */
	/* padding: 4 */
	/* last cacheline: 56 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_error.c */
/* <40666> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_42 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_file_stdio.c */
/* <4156f> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_43 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_file_stdio.c */
/* <41593> /home/liu2598/Product/libzip/master/src_format/lib/zip_source_file.h:34 */
struct zip_source_file_stat {
	long unsigned int          size;                 /*     0     8 */
	long int                   mtime;                /*     8     8 */
	_Bool                      exists;               /*    16     1 */
	_Bool                      regular_file;         /*    17     1 */

	/* size: 24, cachelines: 1, members: 4 */
	/* padding: 6 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_file_stdio.c */
/* <415db> /home/liu2598/Product/libzip/master/src_format/lib/zip_source_file.h:45 */
struct zip_source_file_context {
	struct zip_error           error;                /*     0    16 */
	long int                   supports;             /*    16     8 */
	char                       *fname;               /*    24     8 */
	void *                     f;                    /*    32     8 */
	struct zip_stat            st;                   /*    40    64 */
	/* --- cacheline 1 boundary (64 bytes) was 40 bytes ago --- */
	struct zip_file_attributes attributes;           /*   104    24 */
	/* --- cacheline 2 boundary (128 bytes) --- */
	struct zip_error           stat_error;           /*   128    16 */
	long unsigned int          start;                /*   144     8 */
	long unsigned int          len;                  /*   152     8 */
	long unsigned int          offset;               /*   160     8 */
	char                       *tmpname;             /*   168     8 */
	void *                     fout;                 /*   176     8 */
	struct zip_source_file_operations *ops;          /*   184     8 */
	/* --- cacheline 3 boundary (192 bytes) --- */
	void *                     ops_userdata;         /*   192     8 */

	/* size: 200, cachelines: 4, members: 14 */
	/* last cacheline: 8 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_file_stdio.c */
/* <41698> /home/liu2598/Product/libzip/master/src_format/lib/zip_source_file.h:74 */
struct zip_source_file_operations {
	void **close;                                                /*     0     8 */
	void **commit_write;                                                /*     8     8 */
	void **create_temp_output;                                                /*    16     8 */
	void **create_temp_output_cloning;                                                /*    24     8 */
	void **open;                                                /*    32     8 */
	void **read;                                                /*    40     8 */
	void **remove;                                                /*    48     8 */
	void **rollback_write;                                                /*    56     8 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	void **seek;                                                /*    64     8 */
	void **stat;                                                /*    72     8 */
	void **string_duplicate;                                                /*    80     8 */
	void **tell;                                                /*    88     8 */
	void **write;                                                /*    96     8 */

	/* size: 104, cachelines: 2, members: 13 */
	/* last cacheline: 40 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_free.c */
/* <42ed7> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_44 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_function.c */
/* <43de6> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_45 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_get_file_attributes.c */
/* <44ffa> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_46 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_layered.c */
/* <4600b> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_47 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_open.c */
/* <4704a> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_48 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_pkware_decode.c */
/* <48059> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_49 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_pkware_decode.c */
/* <4807d> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:467 */
struct _zip_pkware_keys {
	unsigned int               key[3];               /*     0    12 */

	/* size: 12, cachelines: 1, members: 1 */
	/* last cacheline: 12 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_pkware_decode.c */
/* <480b4> /home/liu2598/Product/libzip/master/src_format/lib/zip_source_pkware_decode.c:40 */
struct trad_pkware {
	char                       *password;            /*     0     8 */
	struct _zip_pkware_keys    keys;                 /*     8    12 */

	/* XXX 4 bytes hole, try to pack */

	struct zip_error           error;                /*    24    16 */

	/* size: 40, cachelines: 1, members: 3 */
	/* sum members: 36, holes: 1, sum holes: 4 */
	/* last cacheline: 40 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_pkware_encode.c */
/* <4964c> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_50 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_read.c */
/* <4ad11> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_51 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_remove.c */
/* <4bc1c> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_52 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_rollback_write.c */
/* <4cab5> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_53 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_seek.c */
/* <4d941> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_54 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_seek_write.c */
/* <4e8f6> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_55 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_stat.c */
/* <4f7cb> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_56 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_supports.c */
/* <4fa65> /home/liu2598/Product/libzip/master/src_format/lib/<built-in>:0 */
struct __va_list_tag {
	unsigned int               gp_offset;            /*     0     4 */
	unsigned int               fp_offset;            /*     4     4 */
	void *                     overflow_arg_area;    /*     8     8 */
	void *                     reg_save_area;        /*    16     8 */

	/* size: 24, cachelines: 1, members: 4 */
	/* last cacheline: 24 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_supports.c */
/* <50850> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_57 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_tell.c */
/* <51736> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_58 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_tell_write.c */
/* <525e3> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_59 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_window.c */
/* <534b6> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_60 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_window.c */
/* <534da> /home/liu2598/Product/libzip/master/src_format/lib/zip_source_window.c:40 */
struct window {
	long unsigned int          start;                /*     0     8 */
	long unsigned int          end;                  /*     8     8 */
	_Bool                      end_valid;            /*    16     1 */

	/* XXX 7 bytes hole, try to pack */

	struct zip                 *source_archive;      /*    24     8 */
	long unsigned int          source_index;         /*    32     8 */
	long unsigned int          offset;               /*    40     8 */
	struct zip_stat            stat;                 /*    48    64 */
	/* --- cacheline 1 boundary (64 bytes) was 48 bytes ago --- */
	struct zip_file_attributes attributes;           /*   112    24 */
	/* --- cacheline 2 boundary (128 bytes) was 8 bytes ago --- */
	struct zip_error           error;                /*   136    16 */
	long int                   supports;             /*   152     8 */
	_Bool                      needs_seek;           /*   160     1 */

	/* size: 168, cachelines: 3, members: 11 */
	/* sum members: 154, holes: 1, sum holes: 7 */
	/* padding: 7 */
	/* last cacheline: 40 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_write.c */
/* <54f6d> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_61 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_zip.c */
/* <55e24> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_62 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_zip_new.c */
/* <56ee0> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_63 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_stat_index.c */
/* <5828b> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_64 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_strerror.c */
/* <59a43> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_65 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_string.c */
/* <5a8fe> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_66 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_unchange.c */
/* <5bbf1> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_67 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_unchange_data.c */
/* <5ceba> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_68 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_file_stdio_named.c */
/* <5f0b5> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_69 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_winzip_aes_decode.c */
/* <62a85> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_70 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_winzip_aes_decode.c */
/* <62aba> /home/liu2598/Product/libzip/master/src_format/lib/zip_source_winzip_aes_decode.c:40 */
struct winzip_aes {
	char                       *password;            /*     0     8 */
	short unsigned int         encryption_method;    /*     8     2 */

	/* XXX 6 bytes hole, try to pack */

	long unsigned int          data_length;          /*    16     8 */
	long unsigned int          current_position;     /*    24     8 */
	struct _zip_winzip_aes     *aes_ctx;             /*    32     8 */
	struct zip_error           error;                /*    40    16 */

	/* size: 56, cachelines: 1, members: 6 */
	/* sum members: 50, holes: 1, sum holes: 6 */
	/* last cacheline: 56 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_winzip_aes_encode.c */
/* <6432e> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_71 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_add_entry.c */
/* <65a97> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_72 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_algorithm_deflate.c */
/* <6651b> /home/liu2598/Product/libzip/master/src_format/lib/zip_algorithm_deflate.c:40 */
struct ctx {
	struct zip_error           *error;               /*     0     8 */
	_Bool                      compress;             /*     8     1 */

	/* XXX 3 bytes hole, try to pack */

	int                        compression_flags;    /*    12     4 */
	_Bool                      end_of_input;         /*    16     1 */

	/* XXX 7 bytes hole, try to pack */

	struct z_stream_s          zstr;                 /*    24   112 */

	/* size: 136, cachelines: 3, members: 5 */
	/* sum members: 126, holes: 2, sum holes: 10 */
	/* last cacheline: 8 bytes */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_buffer.c */
/* <67ad4> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_73 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_file_get_comment.c */
/* <69694> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_74 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_file_rename.c */
/* <6a5a0> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_75 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_new.c */
/* <6b52f> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_76 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_source_file_common.c */
/* <6d095> /home/liu2598/Product/libzip/master/src_format/lib/zipint.h:385 */
union memfuzz_anonymous_struct_77 {
	void **f;                                              /*     0     8 */
	void **l;                                              /*     0     8 */
};
/* Used at: /home/liu2598/Product/libzip/master/src_format/lib/zip_winzip_aes.c */
/* <6e3cf> /home/liu2598/Product/libzip/master/src_format/lib/zip_winzip_aes.c:45 */
struct _zip_winzip_aes {
	struct evp_cipher_ctx_st   *aes;                 /*     0     8 */
	struct hmac_ctx_st         *hmac;                /*     8     8 */
	unsigned char              counter[16];          /*    16    16 */
	unsigned char              pad[16];              /*    32    16 */
	int                        pad_offset;           /*    48     4 */

	/* size: 56, cachelines: 1, members: 5 */
	/* padding: 4 */
	/* last cacheline: 56 bytes */
};
#endif
