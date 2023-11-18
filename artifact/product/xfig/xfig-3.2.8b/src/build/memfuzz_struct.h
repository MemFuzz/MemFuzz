#ifndef _MEMFUZZ_STRUCT_H_
#define _MEMFUZZ_STRUCT_H_
/*Add necessary header here to avoid compile problems*/
/*Struct Declaration Begin*/
struct Cmap;
struct memfuzz_anonymous_struct_12;
struct _appres;
struct paper_def;
struct _recent_file_struct;
struct f_pos;
struct _pics;
struct f_point;
struct f_arrow;
struct f_ellipse;
struct memfuzz_anonymous_struct_13;
struct f_arc;
struct f_pic;
struct f_line;
struct f_text;
struct f_spline;
struct f_shape;
struct f_compound;
struct f_linkinfo;
struct counts;
struct memfuzz_anonymous_struct_27;
struct _patrn_strct;
struct memfuzz_anonymous_struct_41;
struct memfuzz_anonymous_struct_55;
struct memfuzz_anonymous_struct_69;
struct memfuzz_anonymous_struct_83;
struct memfuzz_anonymous_struct_97;
struct memfuzz_anonymous_struct_111;
struct memfuzz_anonymous_struct_125;
struct memfuzz_anonymous_struct_145;
struct memfuzz_anonymous_struct_146;
struct xfont;
struct _fstruct;
struct _xfstruct;
struct memfuzz_anonymous_struct_147;
struct main_menu_struct;
struct memfuzz_anonymous_struct_161;
struct _icon_struct;
struct memfuzz_anonymous_struct_175;
struct memfuzz_anonymous_struct_189;
struct memfuzz_anonymous_struct_203;
struct memfuzz_anonymous_struct_217;
struct memfuzz_anonymous_struct_218;
struct memfuzz_anonymous_struct_219;
struct memfuzz_anonymous_struct_220;
struct memfuzz_anonymous_struct_221;
struct memfuzz_anonymous_struct_222;
struct memfuzz_anonymous_struct_273;
struct choice_struct;
struct ind_sw_struct;
struct _RGB;
struct memfuzz_anonymous_struct_287;
struct memfuzz_anonymous_struct_301;
struct memfuzz_anonymous_struct_315;
struct memfuzz_anonymous_struct_329;
struct memfuzz_anonymous_struct_381;
union memfuzz_anonymous_struct_382;
struct memfuzz_anonymous_struct_383;
struct sfactor_def;
struct memfuzz_anonymous_struct_384;
struct memfuzz_anonymous_struct_398;
struct memfuzz_anonymous_struct_412;
struct memfuzz_anonymous_struct_426;
struct memfuzz_anonymous_struct_440;
struct memfuzz_anonymous_struct_454;
struct memfuzz_anonymous_struct_468;
struct memfuzz_anonymous_struct_484;
struct memfuzz_anonymous_struct_485;
struct f_libobj;
struct memfuzz_anonymous_struct_499;
struct memfuzz_anonymous_struct_514;
struct memfuzz_anonymous_struct_528;
struct memfuzz_anonymous_struct_543;
struct memfuzz_anonymous_struct_558;
struct memfuzz_anonymous_struct_559;
struct memfuzz_anonymous_struct_574;
struct xfig_stream;
struct _haeders;
struct memfuzz_anonymous_struct_589;
struct memfuzz_anonymous_struct_604;
struct memfuzz_anonymous_struct_618;
struct memfuzz_anonymous_struct_619;
struct memfuzz_anonymous_struct_620;
struct memfuzz_anonymous_struct_635;
struct memfuzz_anonymous_struct_649;
struct pcxhed;
struct memfuzz_anonymous_struct_663;
struct memfuzz_anonymous_struct_677;
struct memfuzz_anonymous_struct_691;
struct memfuzz_anonymous_struct_705;
struct _pcxhead;
struct memfuzz_anonymous_struct_763;
struct memfuzz_anonymous_struct_765;
struct memfuzz_anonymous_struct_766;
struct geom;
struct memfuzz_anonymous_struct_780;
struct memfuzz_anonymous_struct_794;
struct memfuzz_anonymous_struct_808;
struct memfuzz_anonymous_struct_822;
struct memfuzz_anonymous_struct_823;
struct memfuzz_anonymous_struct_837;
struct memfuzz_anonymous_struct_852;
struct memfuzz_anonymous_struct_870;
struct _fpnt;
struct _arrow_shape;
struct memfuzz_anonymous_struct_885;
struct memfuzz_anonymous_struct_933;
struct memfuzz_anonymous_struct_948;
struct memfuzz_anonymous_struct_962;
struct memfuzz_anonymous_struct_976;
struct angle_table;
struct memfuzz_anonymous_struct_990;
struct memfuzz_anonymous_struct_1004;
struct memfuzz_anonymous_struct_1018;
struct memfuzz_anonymous_struct_1042;
struct memfuzz_anonymous_struct_1057;
struct memfuzz_anonymous_struct_1071;
struct memfuzz_anonymous_struct_1085;
struct memfuzz_anonymous_struct_1099;
struct memfuzz_anonymous_struct_1113;
struct memfuzz_anonymous_struct_1127;
struct memfuzz_anonymous_struct_1179;
struct memfuzz_anonymous_struct_1232;
struct mode_switch_struct;
struct _CompKey;
struct memfuzz_anonymous_struct_1249;
struct memfuzz_anonymous_struct_1300;
struct _global;
union memfuzz_anonymous_struct_1303;
struct memfuzz_anonymous_struct_1357;
struct _HSV;
struct memfuzz_anonymous_struct_1358;
struct memfuzz_anonymous_struct_1458;
struct memfuzz_anonymous_struct_1509;
struct memfuzz_anonymous_struct_1566;
struct memfuzz_anonymous_struct_1568;
struct memfuzz_anonymous_struct_1619;
struct memfuzz_anonymous_struct_1672;
struct memfuzz_anonymous_struct_1738;
struct memfuzz_anonymous_struct_1790;
struct memfuzz_anonymous_struct_1841;
struct memfuzz_anonymous_struct_1893;
struct memfuzz_anonymous_struct_1945;
struct memfuzz_anonymous_struct_1999;
struct _keyboard_history_s;
struct memfuzz_anonymous_struct_2050;
struct __va_list_tag;
struct memfuzz_anonymous_struct_2102;
struct memfuzz_anonymous_struct_2104;
struct lib_rec;
struct _FigListClassRec;
struct _FigListRec;
struct memfuzz_anonymous_struct_2154;
struct memfuzz_anonymous_struct_2155;
struct memfuzz_anonymous_struct_2206;
struct memfuzz_anonymous_struct_2309;
struct memfuzz_anonymous_struct_2360;
struct rotated_text_item_template;
struct style_template;
struct memfuzz_anonymous_struct_2431;
struct tick_info_struct;
struct ruler_skip_struct;
struct ruler_info_struct;
struct memfuzz_anonymous_struct_2493;
struct memfuzz_anonymous_struct_2546;
struct memfuzz_anonymous_struct_2597;
struct Element;
struct Style;
struct Style_family;
struct memfuzz_anonymous_struct_2650;
struct memfuzz_anonymous_struct_2652;
struct memfuzz_anonymous_struct_2666;
struct memfuzz_anonymous_struct_2685;
struct memfuzz_anonymous_struct_2699;
struct memfuzz_anonymous_struct_2723;
struct memfuzz_anonymous_struct_2738;
struct memfuzz_anonymous_struct_2794;
/*Enumeration Definition Begin*/
enum pictypes {
		T_PIC_NONE = 0,
		T_PIC_EPS  = 1,
		T_PIC_PDF  = 2,
		T_PIC_GIF  = 3,
		T_PIC_JPEG = 4,
		T_PIC_PCX  = 5,
		T_PIC_PNG  = 6,
		T_PIC_PPM  = 7,
		T_PIC_TIF  = 8,
		T_PIC_XBM  = 9,
		T_PIC_XPM  = 10,
		LAST_PIC   = 11,
	};
enum Element_type {
		Tint   = 0,
		Tfloat = 1,
		TColor = 2,
	};
enum memfuzz_anonymous_enum_0 {
		XtAddress          = 0,
		XtBaseOffset       = 1,
		XtImmediate        = 2,
		XtResourceString   = 3,
		XtResourceQuark    = 4,
		XtWidgetBaseOffset = 5,
		XtProcedureArg     = 6,
	};
enum memfuzz_anonymous_enum_1 {
			PTYPE_NONE         = 0,
			PTYPE_START_PLINE  = 1,
			PTYPE_START_VERTEX = 2,
			PTYPE_END_VERTEX   = 3,
			PTYPE_END_PLINE    = 4,
			PTYPE_CUT          = 5,
		};
enum memfuzz_anonymous_enum_2 {
		XrmoptionNoArg     = 0,
		XrmoptionIsArg     = 1,
		XrmoptionStickyArg = 2,
		XrmoptionSepArg    = 3,
		XrmoptionResArg    = 4,
		XrmoptionSkipArg   = 5,
		XrmoptionSkipLine  = 6,
		XrmoptionSkipNArgs = 7,
	};
enum memfuzz_anonymous_enum_3 {
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
enum memfuzz_anonymous_enum_4 {
		JDCT_ISLOW = 0,
		JDCT_IFAST = 1,
		JDCT_FLOAT = 2,
	};
enum memfuzz_anonymous_enum_5 {
		JDITHER_NONE    = 0,
		JDITHER_ORDERED = 1,
		JDITHER_FS      = 2,
	};
/*Struct Definition Begin*/
/* Used at: d_arcbox.c */
/* <a11> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/resources.h:127 */
struct Cmap {
	short unsigned int         red;                  /*     0     2 */
	short unsigned int         green;                /*     2     2 */
	short unsigned int         blue;                 /*     4     2 */

	/* XXX 2 bytes hole, try to pack */

	long unsigned int          pixel;                /*     8     8 */

	/* size: 16, cachelines: 1, members: 4 */
	/* sum members: 14, holes: 1, sum holes: 2 */
	/* last cacheline: 16 bytes */
};
/* Used at: d_arcbox.c */
/* <a4e> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/resources.h:132 */
typedef struct memfuzz_anonymous_struct_12 {
	char                       *name;                /*     0     8 */
	char                       *rgb;                 /*     8     8 */

	/* size: 16, cachelines: 1, members: 2 */
	/* last cacheline: 16 bytes */
} fig_colors;
/* Used at: d_arcbox.c */
/* <d72> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/resources.h:190 */
struct _appres {
	char                       write_v40;            /*     0     1 */
	char                       allownegcoords;       /*     1     1 */

	/* XXX 2 bytes hole, try to pack */

	int                        balloon_delay;        /*     4     4 */
	char                       *boldFont;            /*     8     8 */
	char                       *browser;             /*    16     8 */
	int                        but_per_row;          /*    24     4 */

	/* XXX 4 bytes hole, try to pack */

	char                       *buttonFont;          /*    32     8 */
	char                       *canvasbackground;    /*    40     8 */
	char                       *canvasforeground;    /*    48     8 */
	char                       DEBUG;                /*    56     1 */
	char                       dontswitchcmap;       /*    57     1 */
	char                       installowncmap;       /*    58     1 */
	char                       showaxislines;        /*    59     1 */
	char                       smallicons;           /*    60     1 */

	/* XXX 3 bytes hole, try to pack */

	/* --- cacheline 1 boundary (64 bytes) --- */
	char                       *exportLanguage;      /*    64     8 */
	char                       flushleft;            /*    72     1 */

	/* XXX 7 bytes hole, try to pack */

	char                       *geometry;            /*    80     8 */
	char                       *iconGeometry;        /*    88     8 */
	char                       *image_editor;        /*    96     8 */
	char                       INCHES;               /*   104     1 */

	/* XXX 3 bytes hole, try to pack */

	int                        internalborderwidth;  /*   108     4 */
	int                        jpeg_quality;         /*   112     4 */

	/* XXX 4 bytes hole, try to pack */

	char                       *keyFile;             /*   120     8 */
	/* --- cacheline 2 boundary (128 bytes) --- */
	char                       landscape;            /*   128     1 */
	char                       latexfonts;           /*   129     1 */

	/* XXX 6 bytes hole, try to pack */

	char                       *library_dir;         /*   136     8 */
	float                      magnification;        /*   144     4 */
	int                        max_image_colors;     /*   148     4 */
	char                       monochrome;           /*   152     1 */
	char                       multiple;             /*   153     1 */

	/* XXX 6 bytes hole, try to pack */

	char                       *normalFont;          /*   160     8 */
	char                       *pageborder;          /*   168     8 */
	char                       *paper_size;          /*   176     8 */
	int                        papersize;            /*   184     4 */
	char                       RHS_PANEL;            /*   188     1 */

	/* XXX 3 bytes hole, try to pack */

	/* --- cacheline 3 boundary (192 bytes) --- */
	char                       *pdf_viewer;          /*   192     8 */
	int                        rulerthick;           /*   200     4 */
	char                       scalablefonts;        /*   204     1 */
	char                       showallbuttons;       /*   205     1 */
	char                       showballoons;         /*   206     1 */
	char                       showlengths;          /*   207     1 */
	char                       shownums;             /*   208     1 */
	char                       show_pageborder;      /*   209     1 */
	char                       specialtext;          /*   210     1 */

	/* XXX 5 bytes hole, try to pack */

	char                       *spellcheckcommand;   /*   216     8 */
	int                        spinner_delay;        /*   224     4 */
	int                        spinner_rate;         /*   228     4 */
	int                        startfillstyle;       /*   232     4 */
	float                      startfontsize;        /*   236     4 */
	int                        startgridmode;        /*   240     4 */
	int                        startgridtype;        /*   244     4 */
	int                        startarrowtype;       /*   248     4 */
	float                      startarrowthick;      /*   252     4 */
	/* --- cacheline 4 boundary (256 bytes) --- */
	float                      startarrowwidth;      /*   256     4 */
	float                      startarrowlength;     /*   260     4 */
	char                       *startlatexFont;      /*   264     8 */
	int                        startlinewidth;       /*   272     4 */
	int                        startposnmode;        /*   276     4 */
	char                       *startpsFont;         /*   280     8 */
	float                      starttextstep;        /*   288     4 */
	char                       tablet;               /*   292     1 */

	/* XXX 3 bytes hole, try to pack */

	float                      tmp_height;           /*   296     4 */
	float                      tmp_width;            /*   300     4 */
	char                       tracking;             /*   304     1 */

	/* XXX 3 bytes hole, try to pack */

	int                        transparent;          /*   308     4 */
	float                      userscale;            /*   312     4 */

	/* XXX 4 bytes hole, try to pack */

	/* --- cacheline 5 boundary (320 bytes) --- */
	char                       *userunit;            /*   320     8 */
	float                      zoom;                 /*   328     4 */

	/* XXX 4 bytes hole, try to pack */

	char                       *version;             /*   336     8 */
	int                        export_margin;        /*   344     4 */
	char                       flipvisualhints;      /*   348     1 */
	char                       rigidtext;            /*   349     1 */
	char                       hiddentext;           /*   350     1 */
	char                       showdepthmanager;     /*   351     1 */
	char                       *grid_color;          /*   352     8 */
	int                        smooth_factor;        /*   360     4 */
	char                       icon_view;            /*   364     1 */

	/* XXX 3 bytes hole, try to pack */

	int                        library_icon_size;    /*   368     4 */
	char                       splash;               /*   372     1 */

	/* XXX 3 bytes hole, try to pack */

	char                       *axislines;           /*   376     8 */
	/* --- cacheline 6 boundary (384 bytes) --- */
	int                        freehand_resolution;  /*   384     4 */

	/* XXX 4 bytes hole, try to pack */

	char                       *tgrid_unit;          /*   392     8 */
	char                       overlap;              /*   400     1 */

	/* XXX 7 bytes hole, try to pack */

	char                       *ghostscript;         /*   408     8 */
	char                       *gslib;               /*   416     8 */
	char                       correct_font_size;    /*   424     1 */

	/* XXX 3 bytes hole, try to pack */

	int                        encoding;             /*   428     4 */
	char                       save8bit;             /*   432     1 */
	char                       crosshair;            /*   433     1 */
	char                       autorefresh;          /*   434     1 */
	char                       write_bak;            /*   435     1 */
	char                       international;        /*   436     1 */

	/* XXX 3 bytes hole, try to pack */

	char                       *font_menu_language;  /*   440     8 */
	/* --- cacheline 7 boundary (448 bytes) --- */
	char                       euc_encoding;         /*   448     1 */
	char                       locale_encoding;      /*   449     1 */
	char                       latin_keyboard;       /*   450     1 */
	char                       always_use_fontset;   /*   451     1 */

	/* XXX 4 bytes hole, try to pack */

	struct _XOC                *fixed_fontset;       /*   456     8 */
	int                        fontset_size;         /*   464     4 */

	/* XXX 4 bytes hole, try to pack */

	char                       *xim_input_style;     /*   472     8 */
	char                       *fig2dev_localize_option; /*   480     8 */
	char                       *text_preedit;        /*   488     8 */

	/* size: 496, cachelines: 8, members: 102 */
	/* sum members: 408, holes: 22, sum holes: 88 */
	/* last cacheline: 48 bytes */
};
/* Used at: d_arcbox.c */
/* <12b7> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/resources.h:331 */
struct paper_def {
	char                       *sname;               /*     0     8 */
	char                       *fname;               /*     8     8 */
	int                        width;                /*    16     4 */
	int                        height;               /*    20     4 */

	/* size: 24, cachelines: 1, members: 4 */
	/* last cacheline: 24 bytes */
};
/* Used at: d_arcbox.c */
/* <18a6> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/resources.h:432 */
struct _recent_file_struct {
	char                       *name;                /*     0     8 */
	struct _WidgetRec          *menu;                /*     8     8 */

	/* size: 16, cachelines: 1, members: 2 */
	/* last cacheline: 16 bytes */
};
/* Used at: d_arcbox.c */
/* <194b> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:113 */
struct f_pos {
	int                        x;                    /*     0     4 */
	int                        y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: d_arcbox.c */
/* <c59> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:117 */
struct _pics {
	char                       *file;                /*     0     8 */
	long int                   time_stamp;           /*     8     8 */
	unsigned char              *bitmap;              /*    16     8 */
	enum pictypes              subtype;              /*    24     4 */
	int                        size_x;               /*    28     4 */
	int                        size_y;               /*    32     4 */
	struct f_pos               bit_size;             /*    36     8 */

	/* XXX 4 bytes hole, try to pack */

	struct Cmap                cmap[256];            /*    48  4096 */
	/* --- cacheline 64 boundary (4096 bytes) was 48 bytes ago --- */
	int                        numcols;              /*  4144     4 */
	int                        transp;               /*  4148     4 */
	int                        refcount;             /*  4152     4 */

	/* XXX 4 bytes hole, try to pack */

	/* --- cacheline 65 boundary (4160 bytes) --- */
	struct _pics               *prev;                /*  4160     8 */
	struct _pics               *next;                /*  4168     8 */

	/* size: 4176, cachelines: 66, members: 13 */
	/* sum members: 4168, holes: 2, sum holes: 8 */
	/* last cacheline: 16 bytes */
};
/* Used at: d_arcbox.c */
/* <1987> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:137 */
struct f_point {
	int                        x;                    /*     0     4 */
	int                        y;                    /*     4     4 */
	struct f_point             *next;                /*     8     8 */

	/* size: 16, cachelines: 1, members: 3 */
	/* last cacheline: 16 bytes */
};
/* Used at: d_arcbox.c */
/* <19c5> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:146 */
struct f_arrow {
	int                        type;                 /*     0     4 */
	int                        style;                /*     4     4 */
	float                      thickness;            /*     8     4 */
	float                      wd;                   /*    12     4 */
	float                      ht;                   /*    16     4 */

	/* size: 20, cachelines: 1, members: 5 */
	/* last cacheline: 20 bytes */
};
/* Used at: d_arcbox.c */
/* <1a0c> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:159 */
struct f_ellipse {
	int                        tagged;               /*     0     4 */
	int                        distrib;              /*     4     4 */
	int                        type;                 /*     8     4 */
	int                        style;                /*    12     4 */
	int                        thickness;            /*    16     4 */
	int                        pen_color;            /*    20     4 */
	int                        fill_color;           /*    24     4 */
	int                        fill_style;           /*    28     4 */
	int                        depth;                /*    32     4 */
	int                        pen_style;            /*    36     4 */
	float                      style_val;            /*    40     4 */
	float                      angle;                /*    44     4 */
	int                        direction;            /*    48     4 */
	struct f_pos               center;               /*    52     8 */
	struct f_pos               radiuses;             /*    60     8 */
	/* --- cacheline 1 boundary (64 bytes) was 4 bytes ago --- */
	struct f_pos               start;                /*    68     8 */
	struct f_pos               end;                  /*    76     8 */

	/* XXX 4 bytes hole, try to pack */

	char                       *comments;            /*    88     8 */
	struct f_ellipse           *next;                /*    96     8 */

	/* size: 104, cachelines: 2, members: 19 */
	/* sum members: 100, holes: 1, sum holes: 4 */
	/* last cacheline: 40 bytes */
};
/* Used at: d_arcbox.c */
/* <1b0e> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_13 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: d_arcbox.c */
/* <1b2b> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:192 */
struct f_arc {
	int                        tagged;               /*     0     4 */
	int                        distrib;              /*     4     4 */
	int                        type;                 /*     8     4 */
	int                        style;                /*    12     4 */
	int                        thickness;            /*    16     4 */
	int                        pen_color;            /*    20     4 */
	int                        fill_color;           /*    24     4 */
	int                        fill_style;           /*    28     4 */
	int                        depth;                /*    32     4 */
	int                        pen_style;            /*    36     4 */
	float                      style_val;            /*    40     4 */

	/* XXX 4 bytes hole, try to pack */

	struct f_arrow             *for_arrow;           /*    48     8 */
	struct f_arrow             *back_arrow;          /*    56     8 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	int                        cap_style;            /*    64     4 */
	float                      angle;                /*    68     4 */
	int                        direction;            /*    72     4 */
	struct {
		float              x;                    /*    76     4 */
		float              y;                    /*    80     4 */
	} center;                                        /*    76     8 */
	struct f_pos               point[3];             /*    84    24 */

	/* XXX 4 bytes hole, try to pack */

	char                       *comments;            /*   112     8 */
	struct f_arc               *next;                /*   120     8 */

	/* size: 128, cachelines: 2, members: 20 */
	/* sum members: 120, holes: 2, sum holes: 8 */
};
/* Used at: d_arcbox.c */
/* <1c4f> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:235 */
struct f_pic {
	struct _pics               *pic_cache;           /*     0     8 */
	char                       new;                  /*     8     1 */

	/* XXX 3 bytes hole, try to pack */

	int                        flipped;              /*    12     4 */
	float                      hw_ratio;             /*    16     4 */

	/* XXX 4 bytes hole, try to pack */

	long unsigned int          mask;                 /*    24     8 */
	int                        color;                /*    32     4 */

	/* XXX 4 bytes hole, try to pack */

	long unsigned int          pixmap;               /*    40     8 */
	int                        pix_rotation;         /*    48     4 */
	int                        pix_width;            /*    52     4 */
	int                        pix_height;           /*    56     4 */
	int                        pix_flipped;          /*    60     4 */

	/* size: 64, cachelines: 1, members: 11 */
	/* sum members: 53, holes: 3, sum holes: 11 */
};
/* Used at: d_arcbox.c */
/* <1cf6> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:258 */
struct f_line {
	int                        tagged;               /*     0     4 */
	int                        distrib;              /*     4     4 */
	int                        type;                 /*     8     4 */
	int                        style;                /*    12     4 */
	int                        thickness;            /*    16     4 */
	int                        pen_color;            /*    20     4 */
	int                        fill_color;           /*    24     4 */
	int                        fill_style;           /*    28     4 */
	int                        depth;                /*    32     4 */
	int                        pen_style;            /*    36     4 */
	float                      style_val;            /*    40     4 */

	/* XXX 4 bytes hole, try to pack */

	struct f_arrow             *for_arrow;           /*    48     8 */
	struct f_arrow             *back_arrow;          /*    56     8 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	int                        cap_style;            /*    64     4 */

	/* XXX 4 bytes hole, try to pack */

	struct f_point             *points;              /*    72     8 */
	int                        join_style;           /*    80     4 */
	int                        radius;               /*    84     4 */
	struct f_pic               *pic;                 /*    88     8 */
	char                       *comments;            /*    96     8 */
	struct f_line              *next;                /*   104     8 */

	/* size: 112, cachelines: 2, members: 20 */
	/* sum members: 104, holes: 2, sum holes: 8 */
	/* last cacheline: 48 bytes */
};
/* Used at: d_arcbox.c */
/* <1e20> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:299 */
struct f_text {
	int                        tagged;               /*     0     4 */
	int                        distrib;              /*     4     4 */
	int                        type;                 /*     8     4 */
	int                        font;                 /*    12     4 */
	struct {
		struct _XExtData   *ext_data;            /*    16     8 */
		long unsigned int  fid;                  /*    24     8 */
		unsigned int       direction;            /*    32     4 */
		unsigned int       min_char_or_byte2;    /*    36     4 */
		unsigned int       max_char_or_byte2;    /*    40     4 */
		unsigned int       min_byte1;            /*    44     4 */
		unsigned int       max_byte1;            /*    48     4 */
		int                all_chars_exist;      /*    52     4 */
		unsigned int       default_char;         /*    56     4 */
		int                n_properties;         /*    60     4 */
		/* --- cacheline 1 boundary (64 bytes) --- */
		struct {
			long unsigned int name;          /*    64     8 */
			long unsigned int card32;        /*    72     8 */
		} *properties; /*    64     8 */
		struct {
			short int  lbearing;             /*    72     2 */
			short int  rbearing;             /*    74     2 */
			short int  width;                /*    76     2 */
			short int  ascent;               /*    78     2 */
			short int  descent;              /*    80     2 */
			short unsigned int attributes;   /*    82     2 */
		} min_bounds; /*    72    12 */
		struct {
			short int  lbearing;             /*    84     2 */
			short int  rbearing;             /*    86     2 */
			short int  width;                /*    88     2 */
			short int  ascent;               /*    90     2 */
			short int  descent;              /*    92     2 */
			short unsigned int attributes;   /*    94     2 */
		} max_bounds; /*    84    12 */
		struct {
			short int  lbearing;             /*    96     2 */
			short int  rbearing;             /*    98     2 */
			short int  width;                /*   100     2 */
			short int  ascent;               /*   102     2 */
			short int  descent;              /*   104     2 */
			short unsigned int attributes;   /*   106     2 */
		} *per_char; /*    96     8 */
		int                ascent;               /*   104     4 */
		int                descent;              /*   108     4 */
	} *fontstruct; /*    16     8 */
	float                      zoom;                 /*    24     4 */
	int                        size;                 /*    28     4 */
	int                        color;                /*    32     4 */
	int                        depth;                /*    36     4 */
	float                      angle;                /*    40     4 */
	int                        flags;                /*    44     4 */
	int                        ascent;               /*    48     4 */
	int                        length;               /*    52     4 */
	int                        descent;              /*    56     4 */
	int                        base_x;               /*    60     4 */
	int                        base_y;               /*    64     4 */
	int                        pen_style;            /*    68     4 */
	char                       *cstring;             /*    72     8 */
	char                       *comments;            /*    80     8 */
	struct f_text              *next;                /*    88     8 */

	/* size: 96, cachelines: 2, members: 20 */
	/* last cacheline: 32 bytes */
};
/* Used at: d_arcbox.c */
/* <1f44> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:367 */
struct f_spline {
	int                        tagged;               /*     0     4 */
	int                        distrib;              /*     4     4 */
	int                        type;                 /*     8     4 */
	int                        style;                /*    12     4 */
	int                        thickness;            /*    16     4 */
	int                        pen_color;            /*    20     4 */
	int                        fill_color;           /*    24     4 */
	int                        fill_style;           /*    28     4 */
	int                        depth;                /*    32     4 */
	int                        pen_style;            /*    36     4 */
	float                      style_val;            /*    40     4 */

	/* XXX 4 bytes hole, try to pack */

	struct f_arrow             *for_arrow;           /*    48     8 */
	struct f_arrow             *back_arrow;          /*    56     8 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	int                        cap_style;            /*    64     4 */

	/* XXX 4 bytes hole, try to pack */

	struct f_point             *points;              /*    72     8 */
	struct f_shape             *sfactors;            /*    80     8 */
	char                       *comments;            /*    88     8 */
	struct f_spline            *next;                /*    96     8 */

	/* size: 104, cachelines: 2, members: 18 */
	/* sum members: 96, holes: 2, sum holes: 8 */
	/* last cacheline: 40 bytes */
};
/* Used at: d_arcbox.c */
/* <203c> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:407 */
struct f_shape {
	double                     s;                    /*     0     8 */
	struct f_shape             *next;                /*     8     8 */

	/* size: 16, cachelines: 1, members: 2 */
	/* last cacheline: 16 bytes */
};
/* Used at: d_arcbox.c */
/* <2081> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:417 */
struct f_compound {
	int                        tagged;               /*     0     4 */
	int                        distrib;              /*     4     4 */
	struct f_pos               nwcorner;             /*     8     8 */
	struct f_pos               secorner;             /*    16     8 */
	struct f_line              *lines;               /*    24     8 */
	struct f_ellipse           *ellipses;            /*    32     8 */
	struct f_spline            *splines;             /*    40     8 */
	struct f_text              *texts;               /*    48     8 */
	struct f_arc               *arcs;                /*    56     8 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	char                       *comments;            /*    64     8 */
	struct f_compound          *parent;              /*    72     8 */
	struct f_compound          *GABPtr;              /*    80     8 */
	char                       draw_parent;          /*    88     1 */

	/* XXX 7 bytes hole, try to pack */

	struct f_compound          *compounds;           /*    96     8 */
	struct f_compound          *next;                /*   104     8 */

	/* size: 112, cachelines: 2, members: 15 */
	/* sum members: 105, holes: 1, sum holes: 7 */
	/* last cacheline: 48 bytes */
};
/* Used at: d_arcbox.c */
/* <2164> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:435 */
struct f_linkinfo {
	struct f_line              *line;                /*     0     8 */
	struct f_point             *endpt;               /*     8     8 */
	struct f_point             *prevpt;              /*    16     8 */
	int                        two_pts;              /*    24     4 */

	/* XXX 4 bytes hole, try to pack */

	struct f_linkinfo          *next;                /*    32     8 */

	/* size: 40, cachelines: 1, members: 5 */
	/* sum members: 36, holes: 1, sum holes: 4 */
	/* last cacheline: 40 bytes */
};
/* Used at: d_arcbox.c */
/* <28a0> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/u_redraw.h:35 */
struct counts {
	unsigned int               num_arcs;             /*     0     4 */
	unsigned int               num_lines;            /*     4     4 */
	unsigned int               num_ellipses;         /*     8     4 */
	unsigned int               num_splines;          /*    12     4 */
	unsigned int               num_texts;            /*    16     4 */
	unsigned int               cnt_arcs;             /*    20     4 */
	unsigned int               cnt_lines;            /*    24     4 */
	unsigned int               cnt_ellipses;         /*    28     4 */
	unsigned int               cnt_splines;          /*    32     4 */
	unsigned int               cnt_texts;            /*    36     4 */

	/* size: 40, cachelines: 1, members: 10 */
	/* last cacheline: 40 bytes */
};
/* Used at: d_arc.c */
/* <49bc> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_27 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: d_arc.c */
/* <5842> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_drawprim.h:102 */
struct _patrn_strct {
	int                        owidth;               /*     0     4 */
	int                        oheight;              /*     4     4 */
	char                       *odata;               /*     8     8 */
	int                        cwidth;               /*    16     4 */
	int                        cheight;              /*    20     4 */
	char                       *cdata;               /*    24     8 */

	/* size: 32, cachelines: 1, members: 6 */
	/* last cacheline: 32 bytes */
};
/* Used at: d_box.c */
/* <85c5> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_41 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: d_ellipse.c */
/* <b4a4> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_55 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: d_line.c */
/* <ea88> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_69 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: d_picobj.c */
/* <11efb> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_83 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: d_regpoly.c */
/* <14da6> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_97 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: d_spline.c */
/* <17794> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_111 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: d_subspline.c */
/* <1a6bc> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_125 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: d_text.c */
/* <1ce7f> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/resources.h:305 */
typedef struct memfuzz_anonymous_struct_145 {
	int                        length;               /*     0     4 */
	int                        ascent;               /*     4     4 */
	int                        descent;              /*     8     4 */

	/* size: 12, cachelines: 1, members: 3 */
	/* last cacheline: 12 bytes */
} pr_size;
/* Used at: d_text.c */
/* <1dd22> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_146 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: d_text.c */
/* <1e52b> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/u_fonts.h:38 */
struct xfont {
	int                        size;                 /*     0     4 */

	/* XXX 4 bytes hole, try to pack */

	long unsigned int          fid;                  /*     8     8 */
	char                       *fname;               /*    16     8 */
	char                       *bname;               /*    24     8 */
	struct {
		struct _XExtData   *ext_data;            /*    32     8 */
		long unsigned int  fid;                  /*    40     8 */
		unsigned int       direction;            /*    48     4 */
		unsigned int       min_char_or_byte2;    /*    52     4 */
		unsigned int       max_char_or_byte2;    /*    56     4 */
		unsigned int       min_byte1;            /*    60     4 */
		/* --- cacheline 1 boundary (64 bytes) --- */
		unsigned int       max_byte1;            /*    64     4 */
		int                all_chars_exist;      /*    68     4 */
		unsigned int       default_char;         /*    72     4 */
		int                n_properties;         /*    76     4 */
		struct {
			long unsigned int name;          /*    80     8 */
			long unsigned int card32;        /*    88     8 */
		} *properties; /*    80     8 */
		struct {
			short int  lbearing;             /*    88     2 */
			short int  rbearing;             /*    90     2 */
			short int  width;                /*    92     2 */
			short int  ascent;               /*    94     2 */
			short int  descent;              /*    96     2 */
			short unsigned int attributes;   /*    98     2 */
		} min_bounds; /*    88    12 */
		struct {
			short int  lbearing;             /*   100     2 */
			short int  rbearing;             /*   102     2 */
			short int  width;                /*   104     2 */
			short int  ascent;               /*   106     2 */
			short int  descent;              /*   108     2 */
			short unsigned int attributes;   /*   110     2 */
		} max_bounds; /*   100    12 */
		struct {
			short int  lbearing;             /*   112     2 */
			short int  rbearing;             /*   114     2 */
			short int  width;                /*   116     2 */
			short int  ascent;               /*   118     2 */
			short int  descent;              /*   120     2 */
			short unsigned int attributes;   /*   122     2 */
		} *per_char; /*   112     8 */
		int                ascent;               /*   120     4 */
		int                descent;              /*   124     4 */
	} *fstruct; /*    32     8 */
	struct _XOC                *fset;                /*    40     8 */
	struct xfont               *next;                /*    48     8 */

	/* size: 56, cachelines: 1, members: 7 */
	/* sum members: 52, holes: 1, sum holes: 4 */
	/* last cacheline: 56 bytes */
};
/* Used at: d_text.c */
/* <1e592> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/u_fonts.h:48 */
struct _fstruct {
	char                       *name;                /*     0     8 */
	int                        xfontnum;             /*     8     4 */

	/* size: 16, cachelines: 1, members: 2 */
	/* padding: 4 */
	/* last cacheline: 16 bytes */
};
/* Used at: d_text.c */
/* <1e5b7> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/u_fonts.h:53 */
struct _xfstruct {
	char                       *template;            /*     0     8 */
	struct xfont               *xfontlist;           /*     8     8 */

	/* size: 16, cachelines: 1, members: 2 */
	/* last cacheline: 16 bytes */
};
/* Used at: d_text.c */
/* <1ea96> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_cmdpanel.h:25 */
typedef struct memfuzz_anonymous_struct_147 {
	char                       *name;                /*     0     8 */
	int                        u_line;               /*     8     4 */

	/* XXX 4 bytes hole, try to pack */

	void **func;                                                /*    16     8 */
	char                       checkmark;            /*    24     1 */

	/* size: 32, cachelines: 1, members: 4 */
	/* sum members: 21, holes: 1, sum holes: 4 */
	/* padding: 7 */
	/* last cacheline: 32 bytes */
} menu_def;
/* Used at: d_text.c */
/* <1eada> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_cmdpanel.h:36 */
struct main_menu_struct {
	char                       label[16];            /*     0    16 */
	char                       menu_name[16];        /*    16    16 */
	char                       hint[16];             /*    32    16 */
	struct {
		char               *name;                /*    48     8 */
		int                u_line;               /*    56     4 */

		/* XXX 4 bytes hole, try to pack */

		/* --- cacheline 1 boundary (64 bytes) --- */
		void **func;                                        /*    64     8 */
		char               checkmark;            /*    72     1 */
	} *menu; /*    48     8 */
	struct _WidgetRec          *widget;              /*    56     8 */
	struct _WidgetRec          *menuwidget;          /*    64     8 */

	/* size: 72, cachelines: 2, members: 6 */
	/* last cacheline: 8 bytes */
};
/* Used at: e_addpt.c */
/* <24a67> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_161 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: e_addpt.c */
/* <25b33> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_icons.h:33 */
struct _icon_struct {
	int                        width;                /*     0     4 */
	int                        height;               /*     4     4 */
	char                       *bits;                /*     8     8 */

	/* size: 16, cachelines: 1, members: 3 */
	/* last cacheline: 16 bytes */
};
/* Used at: e_align.c */
/* <28960> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_175 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: e_arrow.c */
/* <2d606> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_189 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: e_break.c */
/* <311a6> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_203 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: e_chop.c */
/* <340f2> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_217 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: e_chop.c */
/* <34a95> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_intersect.h:22 */
typedef struct memfuzz_anonymous_struct_218 {
	int                        seg_idx;              /*     0     4 */
	int                        x;                    /*     4     4 */
	int                        y;                    /*     8     4 */

	/* size: 12, cachelines: 1, members: 3 */
	/* last cacheline: 12 bytes */
} isects_s;
/* Used at: e_chop.c */
/* <34ac9> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_intersect.h:28 */
typedef struct memfuzz_anonymous_struct_219 {
	struct {
		int                seg_idx;              /*     0     4 */
		int                x;                    /*     4     4 */
		int                y;                    /*     8     4 */
	} *isects; /*     0     8 */
	int                        nr_isects;            /*     8     4 */
	int                        max_isects;           /*    12     4 */

	/* size: 16, cachelines: 1, members: 3 */
	/* last cacheline: 16 bytes */
} isect_cb_s;
/* Used at: e_chop.c */
/* <34c15> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/e_chop.c:51 */
typedef struct memfuzz_anonymous_struct_220 {
	void *                     object;               /*     0     8 */
	int                        type;                 /*     8     4 */

	/* size: 16, cachelines: 1, members: 2 */
	/* padding: 4 */
	/* last cacheline: 16 bytes */
} axe_objects_s;
/* Used at: e_chop.c */
/* <34cc3> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/e_chop.c:70 */
typedef struct memfuzz_anonymous_struct_221 {
	int                        x;                    /*     0     4 */
	int                        y;                    /*     4     4 */
	enum memfuzz_anonymous_enum_1 ptype;

	/* XXX 4 bytes hole, try to pack */

	double                     dist;                 /*    16     8 */

	/* size: 24, cachelines: 1, members: 4 */
	/* sum members: 20, holes: 1, sum holes: 4 */
	/* last cacheline: 24 bytes */
} s_point_s;
/* Used at: e_chop.c */
/* <34d03> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/e_chop.c:77 */
typedef struct memfuzz_anonymous_struct_222 {
	struct {
		int                x;                    /*     0     4 */
		int                y;                    /*     4     4 */
	enum memfuzz_anonymous_enum_1 ptype;

		/* XXX 4 bytes hole, try to pack */

		double             dist;                 /*    16     8 */
	} *points; /*     0     8 */
	int                        points_next;          /*     8     4 */
	int                        points_max;           /*    12     4 */

	/* size: 16, cachelines: 1, members: 3 */
	/* last cacheline: 16 bytes */
} l_point_s;
/* Used at: e_compound.c */
/* <3acab> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_273 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: e_compound.c */
/* <3be0b> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_indpanel.h:116 */
struct choice_struct {
	int                        value;                /*     0     4 */

	/* XXX 4 bytes hole, try to pack */

	struct _icon_struct        *icon;                /*     8     8 */
	long unsigned int          pixmap;               /*    16     8 */

	/* size: 24, cachelines: 1, members: 3 */
	/* sum members: 20, holes: 1, sum holes: 4 */
	/* last cacheline: 24 bytes */
};
/* Used at: e_compound.c */
/* <3be9a> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_indpanel.h:129 */
struct ind_sw_struct {
	int                        type;                 /*     0     4 */

	/* XXX 4 bytes hole, try to pack */

	long unsigned int          func;                 /*     8     8 */
	char                       line1[38];            /*    16    38 */
	char                       line2[8];             /*    54     8 */

	/* XXX 2 bytes hole, try to pack */

	/* --- cacheline 1 boundary (64 bytes) --- */
	int                        sw_width;             /*    64     4 */

	/* XXX 4 bytes hole, try to pack */

	int                        *i_varadr;            /*    72     8 */
	float                      *f_varadr;            /*    80     8 */
	void **inc_func;                                                /*    88     8 */
	void **dec_func;                                                /*    96     8 */
	void **show_func;                                                /*   104     8 */
	int                        min;                  /*   112     4 */
	int                        max;                  /*   116     4 */
	float                      inc;                  /*   120     4 */

	/* XXX 4 bytes hole, try to pack */

	/* --- cacheline 2 boundary (128 bytes) --- */
	struct choice_struct       *choices;             /*   128     8 */
	int                        numchoices;           /*   136     4 */
	int                        sw_per_row;           /*   140     4 */
	int                        update;               /*   144     4 */

	/* XXX 4 bytes hole, try to pack */

	struct _WidgetRec          *button;              /*   152     8 */
	struct _WidgetRec          *formw;               /*   160     8 */
	struct _WidgetRec          *updbut;              /*   168     8 */
	long unsigned int          pixmap;               /*   176     8 */
	struct _WidgetRec          *panel;               /*   184     8 */

	/* size: 192, cachelines: 3, members: 22 */
	/* sum members: 174, holes: 5, sum holes: 18 */
};
/* Used at: e_compound.c */
/* <3c04a> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_color.h:73 */
struct _RGB {
	short unsigned int         r;                    /*     0     2 */
	short unsigned int         g;                    /*     2     2 */
	short unsigned int         b;                    /*     4     2 */

	/* size: 6, cachelines: 1, members: 3 */
	/* last cacheline: 6 bytes */
};
/* Used at: e_convert.c */
/* <3e728> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_287 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: e_copy.c */
/* <4257f> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_301 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: e_delete.c */
/* <45c77> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_315 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: e_deletept.c */
/* <48fa4> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_329 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: e_edit.c */
/* <4f22f> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_381 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: e_edit.c */
/* <50c15> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_util.h:168 */
typedef union memfuzz_anonymous_struct_382 {
	void *                     ptr;                /*     0     8 */
	int                        val;                /*     0     4 */
} ptr_int;
/* Used at: e_edit.c */
/* <51745> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/e_edit.c:310 */
struct memfuzz_anonymous_struct_383 {
	struct _icon_struct        *image;               /*     0     8 */
	long unsigned int          image_pm;             /*     8     8 */

	/* size: 16, cachelines: 1, members: 2 */
	/* last cacheline: 16 bytes */
};
/* Used at: e_edit.c */
/* <518ff> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/e_edit.c:428 */
struct sfactor_def {
	char                       label[13];            /*     0    13 */

	/* XXX 3 bytes hole, try to pack */

	double                     value;                /*    16     8 */

	/* size: 24, cachelines: 1, members: 2 */
	/* sum members: 21, holes: 1, sum holes: 3 */
	/* last cacheline: 24 bytes */
};
/* Used at: e_edit.c */
/* <519e7> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/e_edit.c:453 */
struct memfuzz_anonymous_struct_384 {
	int                        thickness;            /*     0     4 */
	int                        pen_color;            /*     4     4 */
	int                        fill_color;           /*     8     4 */
	int                        depth;                /*    12     4 */
	long int                   arc_type;             /*    16     8 */
	int                        cap_style;            /*    24     4 */
	int                        join_style;           /*    28     4 */
	int                        style;                /*    32     4 */
	float                      style_val;            /*    36     4 */
	int                        pen_style;            /*    40     4 */
	int                        fill_style;           /*    44     4 */
	char                       *comments;            /*    48     8 */
	struct f_arrow             for_arrow;            /*    56    20 */
	/* --- cacheline 1 boundary (64 bytes) was 12 bytes ago --- */
	struct f_arrow             back_arrow;           /*    76    20 */

	/* size: 96, cachelines: 2, members: 14 */
	/* last cacheline: 32 bytes */
};
/* Used at: e_flip.c */
/* <605c8> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_398 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: e_glue.c */
/* <6459c> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_412 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: e_joinsplit.c */
/* <687c1> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_426 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: e_measure.c */
/* <6c9e9> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_440 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: e_move.c */
/* <713cb> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_454 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: e_movept.c */
/* <7404a> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_468 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: e_placelib.c */
/* <79867> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_484 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: e_placelib.c */
/* <7a485> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_library.h:21 */
struct memfuzz_anonymous_struct_485 {
	int                        x;                    /*     0     4 */
	int                        y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: e_placelib.c */
/* <7a4a2> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_library.h:20 */
struct f_libobj {
	struct {
		int                x;                    /*     0     4 */
		int                y;                    /*     4     4 */
	} corner;                                        /*     0     8 */
	struct f_compound          *compound;            /*     8     8 */

	/* size: 16, cachelines: 1, members: 2 */
	/* last cacheline: 16 bytes */
};
/* Used at: e_rotate.c */
/* <7d768> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_499 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: e_scale.c */
/* <81f87> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_514 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: e_tangent.c */
/* <8856a> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_528 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: e_update.c */
/* <8b1e7> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_543 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: f_load.c */
/* <90802> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_558 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: f_load.c */
/* <91012> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/f_read.h:41 */
typedef struct memfuzz_anonymous_struct_559 {
	char                       landscape;            /*     0     1 */
	char                       flushleft;            /*     1     1 */
	char                       units;                /*     2     1 */

	/* XXX 1 byte hole, try to pack */

	int                        grid_unit;            /*     4     4 */
	int                        papersize;            /*     8     4 */
	float                      magnification;        /*    12     4 */
	char                       multiple;             /*    16     1 */

	/* XXX 3 bytes hole, try to pack */

	int                        transparent;          /*    20     4 */

	/* size: 24, cachelines: 1, members: 8 */
	/* sum members: 20, holes: 2, sum holes: 4 */
	/* last cacheline: 24 bytes */
} fig_settings;
/* Used at: f_picobj.c */
/* <960a8> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_574 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: f_picobj.c */
/* <96897> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/f_picobj.h:36 */
struct xfig_stream {
	struct _IO_FILE            *fp;                  /*     0     8 */
	char                       *name;                /*     8     8 */
	char                       *name_on_disk;        /*    16     8 */
	char                       *content;             /*    24     8 */
	char                       *uncompress;          /*    32     8 */
	char                       name_buf[128];        /*    40   128 */
	/* --- cacheline 2 boundary (128 bytes) was 40 bytes ago --- */
	char                       name_on_disk_buf[128]; /*   168   128 */
	/* --- cacheline 4 boundary (256 bytes) was 40 bytes ago --- */
	char                       content_buf[128];     /*   296   128 */

	/* size: 424, cachelines: 7, members: 8 */
	/* last cacheline: 40 bytes */
};
/* Used at: f_picobj.c */
/* <9776f> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/f_picobj.c:69 */
struct _haeders {
	char                       *type;                /*     0     8 */
	char                       *bytes;               /*     8     8 */
	void **readfunc;                                                /*    16     8 */

	/* size: 24, cachelines: 1, members: 3 */
	/* last cacheline: 24 bytes */
};
/* Used at: f_read.c */
/* <9a9ce> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_589 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: f_readeps.c */
/* <a2d0c> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_604 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: f_readgif.c */
/* <a6bfa> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_618 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: f_readgif.c */
/* <a74a9> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/f_readgif.c:64 */
struct memfuzz_anonymous_struct_619 {
	unsigned int               Width;                /*     0     4 */
	unsigned int               Height;               /*     4     4 */
	struct Cmap                ColorMap[256];        /*     8  4096 */
	/* --- cacheline 64 boundary (4096 bytes) was 8 bytes ago --- */
	unsigned int               BitPixel;             /*  4104     4 */
	unsigned int               ColorResolution;      /*  4108     4 */
	unsigned int               Background;           /*  4112     4 */
	unsigned int               AspectRatio;          /*  4116     4 */

	/* size: 4120, cachelines: 65, members: 7 */
	/* last cacheline: 24 bytes */
};
/* Used at: f_readgif.c */
/* <a7520> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/f_readgif.c:74 */
struct memfuzz_anonymous_struct_620 {
	int                        transparent;          /*     0     4 */
	int                        delayTime;            /*     4     4 */
	int                        inputFlag;            /*     8     4 */
	int                        disposal;             /*    12     4 */

	/* size: 16, cachelines: 1, members: 4 */
	/* last cacheline: 16 bytes */
};
/* Used at: f_readold.c */
/* <aa509> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_635 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: f_readpcx.c */
/* <ada91> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_649 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: f_readpcx.c */
/* <ae68c> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/f_readpcx.c:55 */
struct pcxhed {
	unsigned char              manuf;                /*     0     1 */
	unsigned char              ver;                  /*     1     1 */
	unsigned char              encod;                /*     2     1 */
	unsigned char              bpp;                  /*     3     1 */
	unsigned char              x1lo;                 /*     4     1 */
	unsigned char              x1hi;                 /*     5     1 */
	unsigned char              y1lo;                 /*     6     1 */
	unsigned char              y1hi;                 /*     7     1 */
	unsigned char              x2lo;                 /*     8     1 */
	unsigned char              x2hi;                 /*     9     1 */
	unsigned char              y2lo;                 /*    10     1 */
	unsigned char              y2hi;                 /*    11     1 */
	unsigned char              unused1[4];           /*    12     4 */
	unsigned char              pal16[48];            /*    16    48 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	unsigned char              reserved;             /*    64     1 */
	unsigned char              nplanes;              /*    65     1 */
	unsigned char              bytelinelo;           /*    66     1 */
	unsigned char              bytelinehi;           /*    67     1 */
	unsigned char              unused2[60];          /*    68    60 */

	/* size: 128, cachelines: 2, members: 19 */
};
/* Used at: f_readppm.c */
/* <b0b9a> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_663 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: f_readxbm.c */
/* <b3d3d> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_677 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: f_save.c */
/* <b6a07> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_691 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: f_util.c */
/* <bc765> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_705 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: f_wrpcx.c */
/* <c1c84> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/f_wrpcx.c:22 */
struct _pcxhead {
	unsigned char              id;                   /*     0     1 */
	unsigned char              vers;                 /*     1     1 */
	unsigned char              format;               /*     2     1 */
	unsigned char              bppl;                 /*     3     1 */
	short unsigned int         xmin;                 /*     4     2 */
	short unsigned int         ymin;                 /*     6     2 */
	short unsigned int         xmax;                 /*     8     2 */
	short unsigned int         ymax;                 /*    10     2 */
	short unsigned int         hdpi;                 /*    12     2 */
	short unsigned int         vdpi;                 /*    14     2 */
	unsigned char              egapal[48];           /*    16    48 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	unsigned char              reserv;               /*    64     1 */
	unsigned char              nplanes;              /*    65     1 */
	short unsigned int         blp;                  /*    66     2 */
	short unsigned int         palinfo;              /*    68     2 */
	short unsigned int         hscrnsiz;             /*    70     2 */
	short unsigned int         vscrnsiz;             /*    72     2 */
	unsigned char              fill[54];             /*    74    54 */

	/* size: 128, cachelines: 2, members: 18 */
};
/* Used at: main.c */
/* <c6d84> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_763 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: main.c */
/* <c8c54> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_library.h:21 */
struct memfuzz_anonymous_struct_765 {
	int                        x;                    /*     0     4 */
	int                        y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: main.c */
/* <c9257> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/main.c:128 */
typedef struct memfuzz_anonymous_struct_766 {
	struct {
		struct _XExtData   *ext_data;            /*     0     8 */
		long unsigned int  visualid;             /*     8     8 */
		int                class;                /*    16     4 */

		/* XXX 4 bytes hole, try to pack */

		long unsigned int  red_mask;             /*    24     8 */
		long unsigned int  green_mask;           /*    32     8 */
		long unsigned int  blue_mask;            /*    40     8 */
		int                bits_per_rgb;         /*    48     4 */
		int                map_entries;          /*    52     4 */
	} *visual; /*     0     8 */
	int                        depth;                /*     8     4 */

	/* size: 16, cachelines: 1, members: 2 */
	/* padding: 4 */
	/* last cacheline: 16 bytes */
} OptionsRec;
/* Used at: main.c */
/* <c9298> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/main.c:135 */
struct geom {
	int                        wid;                  /*     0     4 */
	int                        ht;                   /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: mode.c */
/* <ce54e> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_780 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: object.c */
/* <d1ba5> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_794 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: resources.c */
/* <d401a> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_808 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: u_bound.c */
/* <d700e> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_822 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: u_bound.c */
/* <d7e41> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_drawprim.h:26 */
typedef struct memfuzz_anonymous_struct_823 {
	int                        x;                    /*     0     4 */
	int                        y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
} zXPoint;
/* Used at: u_create.c */
/* <dbcfa> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_837 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: u_drag.c */
/* <e0806> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_852 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: u_draw.c */
/* <e61af> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_870 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: u_draw.c */
/* <e7971> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/u_draw.c:57 */
struct _fpnt {
	double                     x;                    /*     0     8 */
	double                     y;                    /*     8     8 */

	/* size: 16, cachelines: 1, members: 2 */
	/* last cacheline: 16 bytes */
};
/* Used at: u_draw.c */
/* <e7992> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/u_draw.c:61 */
struct _arrow_shape {
	int                        numpts;               /*     0     4 */
	int                        tipno;                /*     4     4 */
	int                        numfillpts;           /*     8     4 */
	char                       simplefill;           /*    12     1 */
	char                       clip;                 /*    13     1 */
	char                       half;                 /*    14     1 */

	/* XXX 1 byte hole, try to pack */

	double                     tipmv;                /*    16     8 */
	struct _fpnt               points[6];            /*    24    96 */
	/* --- cacheline 1 boundary (64 bytes) was 56 bytes ago --- */
	struct _fpnt               fillpoints[6];        /*   120    96 */

	/* size: 216, cachelines: 4, members: 9 */
	/* sum members: 215, holes: 1, sum holes: 1 */
	/* last cacheline: 24 bytes */
};
/* Used at: u_elastic.c */
/* <f11a4> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_885 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: u_error.c */
/* <f817a> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_933 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: u_fonts.c */
/* <fb236> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_948 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: u_free.c */
/* <fd967> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_962 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: u_geom.c */
/* <100bca> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_976 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: u_geom.c */
/* <101625> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/u_geom.c:963 */
struct angle_table {
	int                        x;                    /*     0     4 */
	int                        y;                    /*     4     4 */
	double                     angle;                /*     8     8 */

	/* size: 16, cachelines: 1, members: 3 */
	/* last cacheline: 16 bytes */
};
/* Used at: u_ghostscript.c */
/* <10720e> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_990 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: u_list.c */
/* <10aefe> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1004 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: u_markers.c */
/* <111740> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1018 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: u_print.c */
/* <11783d> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1042 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: u_redraw.c */
/* <11f2b6> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1057 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: u_scale.c */
/* <124ba1> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1071 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: u_search.c */
/* <127ab8> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1085 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: u_smartsearch.c */
/* <12d319> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1099 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: u_translate.c */
/* <131c36> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1113 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: u_undo.c */
/* <135048> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1127 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_browse.c */
/* <13d00c> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1179 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_canvas.c */
/* <143da3> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1232 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_canvas.c */
/* <1455c1> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_modepanel.h:34 */
struct mode_switch_struct {
	struct _icon_struct        *icon;                /*     0     8 */
	int                        mode;                 /*     8     4 */

	/* XXX 4 bytes hole, try to pack */

	void **setmode_func;                                                /*    16     8 */
	int                        objmask;              /*    24     4 */

	/* XXX 4 bytes hole, try to pack */

	long unsigned int          indmask;              /*    32     8 */
	char                       modemsg[80];          /*    40    80 */
	/* --- cacheline 1 boundary (64 bytes) was 56 bytes ago --- */
	char                       popup;                /*   120     1 */

	/* XXX 7 bytes hole, try to pack */

	/* --- cacheline 2 boundary (128 bytes) --- */
	struct _WidgetRec          *widget;              /*   128     8 */
	long unsigned int          pixmap;               /*   136     8 */
	long unsigned int          reversePM;            /*   144     8 */

	/* size: 152, cachelines: 3, members: 10 */
	/* sum members: 137, holes: 3, sum holes: 15 */
	/* last cacheline: 24 bytes */
};
/* Used at: w_canvas.c */
/* <145eb1> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_canvas.c:99 */
struct _CompKey {
	unsigned char              key;                  /*     0     1 */
	unsigned char              first;                /*     1     1 */
	unsigned char              second;               /*     2     1 */

	/* XXX 5 bytes hole, try to pack */

	struct _CompKey            *next;                /*     8     8 */

	/* size: 16, cachelines: 1, members: 4 */
	/* sum members: 11, holes: 1, sum holes: 5 */
	/* last cacheline: 16 bytes */
};
/* Used at: w_capture.c */
/* <14a70d> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1249 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_cmdpanel.c */
/* <151928> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1300 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_cmdpanel.c */
/* <153a2d> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_cmdpanel.c:933 */
struct _global {
	char                       tracking;             /*     0     1 */
	char                       autorefresh;          /*     1     1 */
	char                       show_pageborder;      /*     2     1 */
	char                       showdepthmanager;     /*     3     1 */
	char                       showballoons;         /*     4     1 */
	char                       showlengths;          /*     5     1 */
	char                       shownums;             /*     6     1 */
	char                       allownegcoords;       /*     7     1 */
	char                       showaxislines;        /*     8     1 */

	/* size: 9, cachelines: 1, members: 9 */
	/* last cacheline: 9 bytes */
};
/* Used at: w_cmdpanel.c */
/* <153ed3> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_cmdpanel.c:1619 */
union memfuzz_anonymous_struct_1303 {
	void *                     ptr;                /*     0     8 */
	unsigned char              val;                /*     0     1 */
};
/* Used at: w_color.c */
/* <15c652> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1357 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_color.c */
/* <15d971> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_color.h:77 */
struct _HSV {
	float                      h;                    /*     0     4 */
	float                      s;                    /*     4     4 */
	float                      v;                    /*     8     4 */

	/* size: 12, cachelines: 1, members: 3 */
	/* last cacheline: 12 bytes */
};
/* Used at: w_color.c */
/* <15e1c0> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_color.c:2416 */
typedef struct memfuzz_anonymous_struct_1358 {
	struct _XtAppStruct        *app;                 /*     0     8 */
	struct _XDisplay           *dpy;                 /*     8     8 */
	struct _XGC                *gc;                  /*    16     8 */
	long unsigned int          root;                 /*    24     8 */
	char                       drawn;                /*    32     1 */

	/* XXX 3 bytes hole, try to pack */

	int                        x;                    /*    36     4 */
	int                        y;                    /*    40     4 */
	int                        ox;                   /*    44     4 */
	int                        oy;                   /*    48     4 */
	int                        width;                /*    52     4 */
	int                        height;               /*    56     4 */

	/* XXX 4 bytes hole, try to pack */

	/* --- cacheline 1 boundary (64 bytes) --- */
	long unsigned int          id;                   /*    64     8 */

	/* size: 72, cachelines: 2, members: 12 */
	/* sum members: 65, holes: 2, sum holes: 7 */
	/* last cacheline: 8 bytes */
} GrabInfo;
/* Used at: w_digitize.c */
/* <16c107> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1458 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_dir.c */
/* <17443d> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1509 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_drawprim.c */
/* <17be08> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1566 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_drawprim.c */
/* <17d7a3> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_drawprim.c:76 */
struct memfuzz_anonymous_struct_1568 {
	char                       *fn;                  /*     0     8 */
	int                        s;                    /*     8     4 */

	/* size: 16, cachelines: 1, members: 2 */
	/* padding: 4 */
	/* last cacheline: 16 bytes */
};
/* Used at: w_export.c */
/* <185797> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1619 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_file.c */
/* <190805> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1672 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_fontpanel.c */
/* <19bcb8> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/resources.h:313 */
typedef struct memfuzz_anonymous_struct_1738 {
	int                        type;                 /*     0     4 */

	/* XXX 4 bytes hole, try to pack */

	char                       *label;               /*     8     8 */
	char                       *info;                /*    16     8 */

	/* size: 24, cachelines: 1, members: 3 */
	/* sum members: 20, holes: 1, sum holes: 4 */
	/* last cacheline: 24 bytes */
} MenuItemRec;
/* Used at: w_grid.c */
/* <1a268e> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1790 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_help.c */
/* <1a8459> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1841 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_indpanel.c */
/* <1b1a77> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1893 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_intersect.c */
/* <1c1dad> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1945 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_keyboard.c */
/* <1ca965> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_1999 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_keyboard.c */
/* <1cc530> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_keyboard.c:43 */
struct _keyboard_history_s {
	char                       *str;                 /*     0     8 */
	struct _keyboard_history_s *next;                /*     8     8 */
	struct _keyboard_history_s *prior;               /*    16     8 */

	/* size: 24, cachelines: 1, members: 3 */
	/* last cacheline: 24 bytes */
};
/* Used at: w_layers.c */
/* <1d1426> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_2050 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_library.c */
/* <1d5313> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/<built-in>:0 */
struct __va_list_tag {
	unsigned int               gp_offset;            /*     0     4 */
	unsigned int               fp_offset;            /*     4     4 */
	void *                     overflow_arg_area;    /*     8     8 */
	void *                     reg_save_area;        /*    16     8 */

	/* size: 24, cachelines: 1, members: 4 */
	/* last cacheline: 24 bytes */
};
/* Used at: w_library.c */
/* <1d940a> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_2102 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_library.c */
/* <1db014> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_library.h:21 */
struct memfuzz_anonymous_struct_2104 {
	int                        x;                    /*     0     4 */
	int                        y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_library.c */
/* <1db85a> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_library.c:134 */
struct lib_rec {
	char                       *name;                /*     0     8 */
	char                       *longname;            /*     8     8 */
	char                       *path;                /*    16     8 */
	char                       figs_at_top;          /*    24     1 */

	/* XXX 3 bytes hole, try to pack */

	int                        nsubs;                /*    28     4 */
	struct lib_rec             *subdirs[101];        /*    32   808 */

	/* size: 840, cachelines: 14, members: 6 */
	/* sum members: 837, holes: 1, sum holes: 3 */
	/* last cacheline: 8 bytes */
};

struct _CoreClassPart
{
	char tmp[224];
};

/* Used at: w_listwidget.c */
/* <1e2693> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_listwidgetP.h:47 */
struct _FigListClassRec {
	struct _CoreClassPart      core_class;           /*     0   224 */
	/* --- cacheline 3 boundary (192 bytes) was 32 bytes ago --- */
	struct {
		void **change_sensitive;                                        /*   224     8 */
	} simple_class; /*   224     8 */
	struct {
		int                foo;                  /*   232     4 */
	} list_class; /*   232     4 */
	struct {
		int                make_compiler_happy;  /*   236     4 */
	} figList_class; /*   236     4 */

	/* size: 240, cachelines: 4, members: 4 */
	/* last cacheline: 48 bytes */
};
struct _CorePart{
	char tmp[208];
};
/* Used at: w_listwidget.c */
/* <1e26e1> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_listwidgetP.h:73 */
struct _FigListRec {
	struct _CorePart           core;                 /*     0   208 */
	/* --- cacheline 3 boundary (192 bytes) was 16 bytes ago --- */
	struct {
		long unsigned int  cursor;               /*   208     8 */
		long unsigned int  insensitive_border;   /*   216     8 */
		char               *cursor_name;         /*   224     8 */
		long unsigned int  pointer_fg;           /*   232     8 */
		long unsigned int  pointer_bg;           /*   240     8 */
		char               international;        /*   248     1 */
	} simple; /*   208    48 */
	/* --- cacheline 4 boundary (256 bytes) --- */
	struct {
		long unsigned int  foreground;           /*   256     8 */
		short unsigned int internal_width;       /*   264     2 */
		short unsigned int internal_height;      /*   266     2 */
		short unsigned int column_space;         /*   268     2 */
		short unsigned int row_space;            /*   270     2 */
		int                default_cols;         /*   272     4 */
		char               force_cols;           /*   276     1 */
		char               paste;                /*   277     1 */
		char               vertical_cols;        /*   278     1 */

		/* XXX 1 byte hole, try to pack */

		int                longest;              /*   280     4 */
		int                nitems;               /*   284     4 */
		struct {
			struct _XExtData *ext_data;      /*   288     8 */
			long unsigned int fid;           /*   296     8 */
			unsigned int direction;          /*   304     4 */
			unsigned int min_char_or_byte2;  /*   308     4 */
			unsigned int max_char_or_byte2;  /*   312     4 */
			unsigned int min_byte1;          /*   316     4 */
			/* --- cacheline 5 boundary (320 bytes) --- */
			unsigned int max_byte1;          /*   320     4 */
			int        all_chars_exist;      /*   324     4 */
			unsigned int default_char;       /*   328     4 */
			int        n_properties;         /*   332     4 */
			struct {
				long unsigned int name;  /*   336     8 */
				long unsigned int card32; /*   344     8 */
			} *properties; /*   336     8 */
			struct {
				short int lbearing;      /*   344     2 */
				short int rbearing;      /*   346     2 */
				short int width;         /*   348     2 */
				short int ascent;        /*   350     2 */
				short int descent;       /*   352     2 */
				short unsigned int attributes; /*   354     2 */
			} min_bounds; /*   344    12 */
			struct {
				short int lbearing;      /*   356     2 */
				short int rbearing;      /*   358     2 */
				short int width;         /*   360     2 */
				short int ascent;        /*   362     2 */
				short int descent;       /*   364     2 */
				short unsigned int attributes; /*   366     2 */
			} max_bounds; /*   356    12 */
			struct {
				short int lbearing;      /*   368     2 */
				short int rbearing;      /*   370     2 */
				short int width;         /*   372     2 */
				short int ascent;        /*   374     2 */
				short int descent;       /*   376     2 */
				short unsigned int attributes; /*   378     2 */
			} *per_char; /*   368     8 */
			int        ascent;               /*   376     4 */
			int        descent;              /*   380     4 */
		} *font; /*   288     8 */
		struct _XOC        *fontset;             /*   296     8 */
		char               **list;               /*   304     8 */
		struct _XtCallbackRec *callback;         /*   312     8 */
		int                is_highlighted;       /*   320     4 */
		int                highlight;            /*   324     4 */
		int                col_width;            /*   328     4 */
		int                row_height;           /*   332     4 */
		int                nrows;                /*   336     4 */
		int                ncols;                /*   340     4 */
		struct _XGC        *normgc;              /*   344     8 */
		struct _XGC        *revgc;               /*   352     8 */
		struct _XGC        *graygc;              /*   360     8 */
		int                freedoms;             /*   368     4 */
	} list; /*   256   120 */
	struct {
		int                make_compiler_happy;  /*   376     4 */
	} figlist; /*   376     4 */

	/* size: 384, cachelines: 6, members: 4 */
	/* padding: 4 */
};
/* Used at: w_listwidget.c */
/* <1e2721> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_listwidgetP.h:41 */
typedef struct memfuzz_anonymous_struct_2154 {
	int                        make_compiler_happy;  /*     0     4 */

	/* size: 4, cachelines: 1, members: 1 */
	/* last cacheline: 4 bytes */
} FigListClassPart;
/* Used at: w_listwidget.c */
/* <1e2757> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_listwidgetP.h:58 */
typedef struct memfuzz_anonymous_struct_2155 {
	int                        make_compiler_happy;  /*     0     4 */

	/* size: 4, cachelines: 1, members: 1 */
	/* last cacheline: 4 bytes */
} FigListPart;
/* Used at: w_modepanel.c */
/* <1e7bfd> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_2206 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_msgpanel.c */
/* <1f4313> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_2309 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_print.c */
/* <1fcb36> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_2360 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_rottext.c */
/* <20458c> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_rottext.c:79 */
struct rotated_text_item_template {
	long unsigned int          bitmap;               /*     0     8 */
	struct _XImage             *ximage;              /*     8     8 */
	char                       *text;                /*    16     8 */
	char                       *font_name;           /*    24     8 */
	long unsigned int          fid;                  /*    32     8 */
	float                      angle;                /*    40     4 */
	int                        align;                /*    44     4 */
	float                      magnify;              /*    48     4 */
	int                        cols_in;              /*    52     4 */
	int                        rows_in;              /*    56     4 */
	int                        cols_out;             /*    60     4 */
	/* --- cacheline 1 boundary (64 bytes) --- */
	int                        rows_out;             /*    64     4 */
	int                        nl;                   /*    68     4 */
	int                        max_width;            /*    72     4 */

	/* XXX 4 bytes hole, try to pack */

	float                      *corners_x;           /*    80     8 */
	float                      *corners_y;           /*    88     8 */
	long int                   size;                 /*    96     8 */
	int                        cached;               /*   104     4 */

	/* XXX 4 bytes hole, try to pack */

	struct rotated_text_item_template *next;         /*   112     8 */

	/* size: 120, cachelines: 2, members: 19 */
	/* sum members: 112, holes: 2, sum holes: 8 */
	/* last cacheline: 56 bytes */
};
/* Used at: w_rottext.c */
/* <2046ae> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_rottext.c:114 */
struct style_template {
	float                      magnify;              /*     0     4 */
	int                        bbx_pad;              /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_rulers.c */
/* <20c8dc> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_2431 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_rulers.c */
/* <20d654> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_rulers.c:150 */
struct tick_info_struct {
	float                      min_zoom;             /*     0     4 */
	int                        skip;                 /*     4     4 */
	int                        length;               /*     8     4 */

	/* size: 12, cachelines: 1, members: 3 */
	/* last cacheline: 12 bytes */
};
/* Used at: w_rulers.c */
/* <20d6ff> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_rulers.c:182 */
struct ruler_skip_struct {
	float                      max_zoom;             /*     0     4 */
	int                        skipt;                /*     4     4 */
	int                        skipx;                /*     8     4 */
	int                        prec;                 /*    12     4 */

	/* size: 16, cachelines: 1, members: 4 */
	/* last cacheline: 16 bytes */
};
/* Used at: w_rulers.c */
/* <20d7b6> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_rulers.c:236 */
struct ruler_info_struct {
	int                        ruler_unit;           /*     0     4 */

	/* XXX 4 bytes hole, try to pack */

	struct ruler_skip_struct   *skips;               /*     8     8 */
	struct tick_info_struct    *ticks;               /*    16     8 */
	int                        nticks;               /*    24     4 */

	/* size: 32, cachelines: 1, members: 4 */
	/* sum members: 24, holes: 1, sum holes: 4 */
	/* padding: 4 */
	/* last cacheline: 32 bytes */
};
/* Used at: w_snap.c */
/* <216f1b> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_2493 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_srchrepl.c */
/* <21f747> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_2546 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_style.c */
/* <2280d0> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_2597 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_style.c */
/* <229dde> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_style.h:37 */
struct Element {
	char                       *name;                /*     0     8 */
	enum Element_type          type;                 /*     8     4 */

	/* XXX 4 bytes hole, try to pack */

	void *                     value;                /*    16     8 */
	void *                     toset;                /*    24     8 */
	long unsigned int          flag;                 /*    32     8 */

	/* size: 40, cachelines: 1, members: 5 */
	/* sum members: 36, holes: 1, sum holes: 4 */
	/* last cacheline: 40 bytes */
};
/* Used at: w_style.c */
/* <229e32> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_style.h:44 */
struct Style {
	char                       *name;                /*     0     8 */
	struct Element             element[30];          /*     8  1200 */

	/* size: 1208, cachelines: 19, members: 2 */
	/* last cacheline: 56 bytes */
};
/* Used at: w_style.c */
/* <229e73> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_style.h:49 */
struct Style_family {
	char                       *name;                /*     0     8 */
	struct Style               style[16];            /*     8 19328 */

	/* size: 19336, cachelines: 303, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_util.c */
/* <23158f> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_2650 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_util.c */
/* <232eff> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/w_util.h:161 */
typedef struct memfuzz_anonymous_struct_2652 {
	struct _WidgetRec          *widget;              /*     0     8 */
	float                      min;                  /*     8     4 */
	float                      max;                  /*    12     4 */
	float                      inc;                  /*    16     4 */

	/* size: 24, cachelines: 1, members: 4 */
	/* padding: 4 */
	/* last cacheline: 24 bytes */
} spin_struct;
/* Used at: w_zoom.c */
/* <23acc8> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_2666 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: f_readjpg.c */
/* <23f608> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_2685 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: f_readpng.c */
/* <242345> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_2699 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: f_readtif.c */
/* <247057> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_2723 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: f_readxpm.c */
/* <249a94> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_2738 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
/* Used at: w_i18n.c */
/* <24fd26> /home/liu2598/MemFuzz/generator/fig/src/xfig-3.2.8b/src/object.h:220 */
struct memfuzz_anonymous_struct_2794 {
	float                      x;                    /*     0     4 */
	float                      y;                    /*     4     4 */

	/* size: 8, cachelines: 1, members: 2 */
	/* last cacheline: 8 bytes */
};
#endif
