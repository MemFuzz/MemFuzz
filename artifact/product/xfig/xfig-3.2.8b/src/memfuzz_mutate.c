#include "memfuzz_mutate.h"
#include "memfuzz_struct.h"
#include "memfuzz_util.h"
#include "memfuzz_hook.h"
#include "memfuzz_pool.h"
#include "memfuzz_config.h"
void mutate__XExtData(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_0(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_3(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_4(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_5(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_6(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_7(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_8(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_9(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_10(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_11(void* ptr1, int level){return ;}
void mutate_Cmap(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_Cmap  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct Cmap* ptr = ptr1;
    mutate_int16_t(&(ptr->red), level+1);
    mutate_int16_t(&(ptr->green), level+1);
    mutate_int16_t(&(ptr->blue), level+1);
    mutate_int64_t(&(ptr->pixel), level+1);
    pool_insert("Cmap", ptr1);
    #ifdef DEBUG
    printf("leave mutate_Cmap  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_12(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_12  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_12* ptr = ptr1;
    mutate_c_str(ptr->name);
    mutate_c_str(ptr->rgb);
    pool_insert("memfuzz_anonymous_struct_12", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_12  \n"); fflush(stdout);
    #endif
}
void mutate__pics(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate__pics  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct _pics* ptr = ptr1;
    mutate_c_str(ptr->file);
    mutate_int64_t(&(ptr->time_stamp), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->bitmap);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->bitmap, level + 1, len); }
    #else
    //ptr->bitmap = ...(unsigned char  *bitmap)
    #endif
    mutate_enum(&(ptr->subtype), 12);
    mutate_int32_t(&(ptr->size_x), level+1);
    mutate_int32_t(&(ptr->size_y), level+1);
    mutate_f_pos(&(ptr->bit_size), level+1);
    for(int i = 0; i < SAMPLE_TIMES; i++)
    {
        mutate_Cmap(&(ptr->cmap)[random()%256], level+1);
    }
    mutate_int32_t(&(ptr->numcols), level+1);
    mutate_int32_t(&(ptr->transp), level+1);
    mutate_int32_t(&(ptr->refcount), level+1);
    {
        if(ptr->prev) { mutate__pics(ptr->prev, level+1); }
        len = 0;
        arr = pool_get_values("_pics", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->prev;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->prev = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->prev = ptr_save;
        free(arr);
    }
    {
        if(ptr->next) { mutate__pics(ptr->next, level+1); }
        len = 0;
        arr = pool_get_values("_pics", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->next;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->next = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->next = ptr_save;
        free(arr);
    }
    pool_insert("_pics", ptr1);
    #ifdef DEBUG
    printf("leave mutate__pics  \n"); fflush(stdout);
    #endif
}
void mutate__appres(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate__appres  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct _appres* ptr = ptr1;
    mutate_int8_t(&(ptr->write_v40), level+1);
    mutate_int8_t(&(ptr->allownegcoords), level+1);
    mutate_int32_t(&(ptr->balloon_delay), level+1);
    mutate_c_str(ptr->boldFont);
    mutate_c_str(ptr->browser);
    mutate_int32_t(&(ptr->but_per_row), level+1);
    mutate_c_str(ptr->buttonFont);
    mutate_c_str(ptr->canvasbackground);
    mutate_c_str(ptr->canvasforeground);
    mutate_int8_t(&(ptr->DEBUG), level+1);
    mutate_int8_t(&(ptr->dontswitchcmap), level+1);
    mutate_int8_t(&(ptr->installowncmap), level+1);
    mutate_int8_t(&(ptr->showaxislines), level+1);
    mutate_int8_t(&(ptr->smallicons), level+1);
    mutate_c_str(ptr->exportLanguage);
    mutate_int8_t(&(ptr->flushleft), level+1);
    mutate_c_str(ptr->geometry);
    mutate_c_str(ptr->iconGeometry);
    mutate_c_str(ptr->image_editor);
    mutate_int8_t(&(ptr->INCHES), level+1);
    mutate_int32_t(&(ptr->internalborderwidth), level+1);
    mutate_int32_t(&(ptr->jpeg_quality), level+1);
    mutate_c_str(ptr->keyFile);
    mutate_int8_t(&(ptr->landscape), level+1);
    mutate_int8_t(&(ptr->latexfonts), level+1);
    mutate_c_str(ptr->library_dir);
    mutate_float(&(ptr->magnification), level+1);
    mutate_int32_t(&(ptr->max_image_colors), level+1);
    mutate_int8_t(&(ptr->monochrome), level+1);
    mutate_int8_t(&(ptr->multiple), level+1);
    mutate_c_str(ptr->normalFont);
    mutate_c_str(ptr->pageborder);
    mutate_c_str(ptr->paper_size);
    mutate_int32_t(&(ptr->papersize), level+1);
    mutate_int8_t(&(ptr->RHS_PANEL), level+1);
    mutate_c_str(ptr->pdf_viewer);
    mutate_int32_t(&(ptr->rulerthick), level+1);
    mutate_int8_t(&(ptr->scalablefonts), level+1);
    mutate_int8_t(&(ptr->showallbuttons), level+1);
    mutate_int8_t(&(ptr->showballoons), level+1);
    mutate_int8_t(&(ptr->showlengths), level+1);
    mutate_int8_t(&(ptr->shownums), level+1);
    mutate_int8_t(&(ptr->show_pageborder), level+1);
    mutate_int8_t(&(ptr->specialtext), level+1);
    mutate_c_str(ptr->spellcheckcommand);
    mutate_int32_t(&(ptr->spinner_delay), level+1);
    mutate_int32_t(&(ptr->spinner_rate), level+1);
    mutate_int32_t(&(ptr->startfillstyle), level+1);
    mutate_float(&(ptr->startfontsize), level+1);
    mutate_int32_t(&(ptr->startgridmode), level+1);
    mutate_int32_t(&(ptr->startgridtype), level+1);
    mutate_int32_t(&(ptr->startarrowtype), level+1);
    mutate_float(&(ptr->startarrowthick), level+1);
    mutate_float(&(ptr->startarrowwidth), level+1);
    mutate_float(&(ptr->startarrowlength), level+1);
    mutate_c_str(ptr->startlatexFont);
    mutate_int32_t(&(ptr->startlinewidth), level+1);
    mutate_int32_t(&(ptr->startposnmode), level+1);
    mutate_c_str(ptr->startpsFont);
    mutate_float(&(ptr->starttextstep), level+1);
    mutate_int8_t(&(ptr->tablet), level+1);
    mutate_float(&(ptr->tmp_height), level+1);
    mutate_float(&(ptr->tmp_width), level+1);
    mutate_int8_t(&(ptr->tracking), level+1);
    mutate_int32_t(&(ptr->transparent), level+1);
    mutate_float(&(ptr->userscale), level+1);
    mutate_c_str(ptr->userunit);
    mutate_float(&(ptr->zoom), level+1);
    mutate_c_str(ptr->version);
    mutate_int32_t(&(ptr->export_margin), level+1);
    mutate_int8_t(&(ptr->flipvisualhints), level+1);
    mutate_int8_t(&(ptr->rigidtext), level+1);
    mutate_int8_t(&(ptr->hiddentext), level+1);
    mutate_int8_t(&(ptr->showdepthmanager), level+1);
    mutate_c_str(ptr->grid_color);
    mutate_int32_t(&(ptr->smooth_factor), level+1);
    mutate_int8_t(&(ptr->icon_view), level+1);
    mutate_int32_t(&(ptr->library_icon_size), level+1);
    mutate_int8_t(&(ptr->splash), level+1);
    mutate_c_str(ptr->axislines);
    mutate_int32_t(&(ptr->freehand_resolution), level+1);
    mutate_c_str(ptr->tgrid_unit);
    mutate_int8_t(&(ptr->overlap), level+1);
    mutate_c_str(ptr->ghostscript);
    mutate_c_str(ptr->gslib);
    mutate_int8_t(&(ptr->correct_font_size), level+1);
    mutate_int32_t(&(ptr->encoding), level+1);
    mutate_int8_t(&(ptr->save8bit), level+1);
    mutate_int8_t(&(ptr->crosshair), level+1);
    mutate_int8_t(&(ptr->autorefresh), level+1);
    mutate_int8_t(&(ptr->write_bak), level+1);
    mutate_int8_t(&(ptr->international), level+1);
    mutate_c_str(ptr->font_menu_language);
    mutate_int8_t(&(ptr->euc_encoding), level+1);
    mutate_int8_t(&(ptr->locale_encoding), level+1);
    mutate_int8_t(&(ptr->latin_keyboard), level+1);
    mutate_int8_t(&(ptr->always_use_fontset), level+1);
    {
        if(ptr->fixed_fontset) { mutate__XOC(ptr->fixed_fontset, level+1); }
        len = 0;
        arr = pool_get_values("_XOC", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->fixed_fontset;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->fixed_fontset = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->fixed_fontset = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->fontset_size), level+1);
    mutate_c_str(ptr->xim_input_style);
    mutate_c_str(ptr->fig2dev_localize_option);
    mutate_c_str(ptr->text_preedit);
    pool_insert("_appres", ptr1);
    #ifdef DEBUG
    printf("leave mutate__appres  \n"); fflush(stdout);
    #endif
}
void mutate_paper_def(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_paper_def  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct paper_def* ptr = ptr1;
    mutate_c_str(ptr->sname);
    mutate_c_str(ptr->fname);
    mutate_int32_t(&(ptr->width), level+1);
    mutate_int32_t(&(ptr->height), level+1);
    pool_insert("paper_def", ptr1);
    #ifdef DEBUG
    printf("leave mutate_paper_def  \n"); fflush(stdout);
    #endif
}
void mutate__recent_file_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate__recent_file_struct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct _recent_file_struct* ptr = ptr1;
    mutate_c_str(ptr->name);
    {
        if(ptr->menu) { mutate__WidgetRec(ptr->menu, level+1); }
        len = 0;
        arr = pool_get_values("_WidgetRec", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->menu;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->menu = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->menu = ptr_save;
        free(arr);
    }
    pool_insert("_recent_file_struct", ptr1);
    #ifdef DEBUG
    printf("leave mutate__recent_file_struct  \n"); fflush(stdout);
    #endif
}
void mutate_f_pos(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_f_pos  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct f_pos* ptr = ptr1;
    mutate_int32_t(&(ptr->x), level+1);
    mutate_int32_t(&(ptr->y), level+1);
    pool_insert("f_pos", ptr1);
    #ifdef DEBUG
    printf("leave mutate_f_pos  \n"); fflush(stdout);
    #endif
}
void mutate_f_point(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_f_point  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct f_point* ptr = ptr1;
    mutate_int32_t(&(ptr->x), level+1);
    mutate_int32_t(&(ptr->y), level+1);
    {
        if(ptr->next) { mutate_f_point(ptr->next, level+1); }
        len = 0;
        arr = pool_get_values("f_point", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->next;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->next = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->next = ptr_save;
        free(arr);
    }
    pool_insert("f_point", ptr1);
    #ifdef DEBUG
    printf("leave mutate_f_point  \n"); fflush(stdout);
    #endif
}
void mutate_f_arrow(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_f_arrow  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct f_arrow* ptr = ptr1;
    mutate_int32_t(&(ptr->type), level+1);
    mutate_int32_t(&(ptr->style), level+1);
    mutate_float(&(ptr->thickness), level+1);
    mutate_float(&(ptr->wd), level+1);
    mutate_float(&(ptr->ht), level+1);
    pool_insert("f_arrow", ptr1);
    #ifdef DEBUG
    printf("leave mutate_f_arrow  \n"); fflush(stdout);
    #endif
}
void mutate_f_ellipse(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_f_ellipse  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct f_ellipse* ptr = ptr1;
    mutate_int32_t(&(ptr->tagged), level+1);
    mutate_int32_t(&(ptr->distrib), level+1);
    mutate_int32_t(&(ptr->type), level+1);
    mutate_int32_t(&(ptr->style), level+1);
    mutate_int32_t(&(ptr->thickness), level+1);
    mutate_int32_t(&(ptr->pen_color), level+1);
    mutate_int32_t(&(ptr->fill_color), level+1);
    mutate_int32_t(&(ptr->fill_style), level+1);
    mutate_int32_t(&(ptr->depth), level+1);
    mutate_int32_t(&(ptr->pen_style), level+1);
    mutate_float(&(ptr->style_val), level+1);
    mutate_float(&(ptr->angle), level+1);
    mutate_int32_t(&(ptr->direction), level+1);
    mutate_f_pos(&(ptr->center), level+1);
    mutate_f_pos(&(ptr->radiuses), level+1);
    mutate_f_pos(&(ptr->start), level+1);
    mutate_f_pos(&(ptr->end), level+1);
    mutate_c_str(ptr->comments);
    {
        if(ptr->next) { mutate_f_ellipse(ptr->next, level+1); }
        len = 0;
        arr = pool_get_values("f_ellipse", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->next;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->next = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->next = ptr_save;
        free(arr);
    }
    pool_insert("f_ellipse", ptr1);
    #ifdef DEBUG
    printf("leave mutate_f_ellipse  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_13(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_13  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_13* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_13", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_13  \n"); fflush(stdout);
    #endif
}
void mutate_f_arc(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_f_arc  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct f_arc* ptr = ptr1;
    mutate_int32_t(&(ptr->tagged), level+1);
    mutate_int32_t(&(ptr->distrib), level+1);
    mutate_int32_t(&(ptr->type), level+1);
    mutate_int32_t(&(ptr->style), level+1);
    mutate_int32_t(&(ptr->thickness), level+1);
    mutate_int32_t(&(ptr->pen_color), level+1);
    mutate_int32_t(&(ptr->fill_color), level+1);
    mutate_int32_t(&(ptr->fill_style), level+1);
    mutate_int32_t(&(ptr->depth), level+1);
    mutate_int32_t(&(ptr->pen_style), level+1);
    mutate_float(&(ptr->style_val), level+1);
    {
        if(ptr->for_arrow) { mutate_f_arrow(ptr->for_arrow, level+1); }
        len = 0;
        arr = pool_get_values("f_arrow", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->for_arrow;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->for_arrow = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->for_arrow = ptr_save;
        free(arr);
    }
    {
        if(ptr->back_arrow) { mutate_f_arrow(ptr->back_arrow, level+1); }
        len = 0;
        arr = pool_get_values("f_arrow", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->back_arrow;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->back_arrow = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->back_arrow = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->cap_style), level+1);
    mutate_float(&(ptr->angle), level+1);
    mutate_int32_t(&(ptr->direction), level+1);
    //ptr->center = ...(struct anonymous {float  x; float  y; } center)
    for(int i = 0; i < 3; i++)
    {
        mutate_f_pos(&(ptr->point)[i], level+1);
    }
    mutate_c_str(ptr->comments);
    {
        if(ptr->next) { mutate_f_arc(ptr->next, level+1); }
        len = 0;
        arr = pool_get_values("f_arc", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->next;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->next = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->next = ptr_save;
        free(arr);
    }
    pool_insert("f_arc", ptr1);
    #ifdef DEBUG
    printf("leave mutate_f_arc  \n"); fflush(stdout);
    #endif
}
void mutate_f_pic(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_f_pic  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct f_pic* ptr = ptr1;
    {
        if(ptr->pic_cache) { mutate__pics(ptr->pic_cache, level+1); }
        len = 0;
        arr = pool_get_values("_pics", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->pic_cache;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->pic_cache = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->pic_cache = ptr_save;
        free(arr);
    }
    mutate_int8_t(&(ptr->new), level+1);
    mutate_int32_t(&(ptr->flipped), level+1);
    mutate_float(&(ptr->hw_ratio), level+1);
    mutate_int64_t(&(ptr->mask), level+1);
    mutate_int32_t(&(ptr->color), level+1);
    mutate_int64_t(&(ptr->pixmap), level+1);
    mutate_int32_t(&(ptr->pix_rotation), level+1);
    mutate_int32_t(&(ptr->pix_width), level+1);
    mutate_int32_t(&(ptr->pix_height), level+1);
    mutate_int32_t(&(ptr->pix_flipped), level+1);
    pool_insert("f_pic", ptr1);
    #ifdef DEBUG
    printf("leave mutate_f_pic  \n"); fflush(stdout);
    #endif
}
void mutate_f_line(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_f_line  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct f_line* ptr = ptr1;
    mutate_int32_t(&(ptr->tagged), level+1);
    mutate_int32_t(&(ptr->distrib), level+1);
    mutate_int32_t(&(ptr->type), level+1);
    mutate_int32_t(&(ptr->style), level+1);
    mutate_int32_t(&(ptr->thickness), level+1);
    mutate_int32_t(&(ptr->pen_color), level+1);
    mutate_int32_t(&(ptr->fill_color), level+1);
    mutate_int32_t(&(ptr->fill_style), level+1);
    mutate_int32_t(&(ptr->depth), level+1);
    mutate_int32_t(&(ptr->pen_style), level+1);
    mutate_float(&(ptr->style_val), level+1);
    {
        if(ptr->for_arrow) { mutate_f_arrow(ptr->for_arrow, level+1); }
        len = 0;
        arr = pool_get_values("f_arrow", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->for_arrow;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->for_arrow = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->for_arrow = ptr_save;
        free(arr);
    }
    {
        if(ptr->back_arrow) { mutate_f_arrow(ptr->back_arrow, level+1); }
        len = 0;
        arr = pool_get_values("f_arrow", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->back_arrow;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->back_arrow = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->back_arrow = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->cap_style), level+1);
    {
        if(ptr->points) { mutate_f_point(ptr->points, level+1); }
        len = 0;
        arr = pool_get_values("f_point", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->points;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->points = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->points = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->join_style), level+1);
    mutate_int32_t(&(ptr->radius), level+1);
    {
        if(ptr->pic) { mutate_f_pic(ptr->pic, level+1); }
        len = 0;
        arr = pool_get_values("f_pic", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->pic;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->pic = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->pic = ptr_save;
        free(arr);
    }
    mutate_c_str(ptr->comments);
    {
        if(ptr->next) { mutate_f_line(ptr->next, level+1); }
        len = 0;
        arr = pool_get_values("f_line", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->next;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->next = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->next = ptr_save;
        free(arr);
    }
    pool_insert("f_line", ptr1);
    #ifdef DEBUG
    printf("leave mutate_f_line  \n"); fflush(stdout);
    #endif
}
void mutate_f_text(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_f_text  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct f_text* ptr = ptr1;
    mutate_int32_t(&(ptr->tagged), level+1);
    mutate_int32_t(&(ptr->distrib), level+1);
    mutate_int32_t(&(ptr->type), level+1);
    mutate_int32_t(&(ptr->font), level+1);
    //ptr->fontstruct = ...(struct anonymous *{struct _XExtData *ext_data; long unsigned int  fid; unsigned int  direction; unsigned int  min_char_or_byte2; unsigned int  max_char_or_byte2; unsigned int  min_byte1; unsigned int  max_byte1; int  all_chars_exist; unsigned int  default_char; int  n_properties; struct anonymous *{long unsigned int  name; long unsigned int  card32; } properties; struct anonymous {short int  lbearing; short int  rbearing; short int  width; short int  ascent; short int  descent; short unsigned int  attributes; } min_bounds; struct anonymous {short int  lbearing; short int  rbearing; short int  width; short int  ascent; short int  descent; short unsigned int  attributes; } max_bounds; struct anonymous *{short int  lbearing; short int  rbearing; short int  width; short int  ascent; short int  descent; short unsigned int  attributes; } per_char; int  ascent; int  descent; } fontstruct)
    mutate_float(&(ptr->zoom), level+1);
    mutate_int32_t(&(ptr->size), level+1);
    mutate_int32_t(&(ptr->color), level+1);
    mutate_int32_t(&(ptr->depth), level+1);
    mutate_float(&(ptr->angle), level+1);
    mutate_int32_t(&(ptr->flags), level+1);
    mutate_int32_t(&(ptr->ascent), level+1);
    mutate_int32_t(&(ptr->length), level+1);
    mutate_int32_t(&(ptr->descent), level+1);
    mutate_int32_t(&(ptr->base_x), level+1);
    mutate_int32_t(&(ptr->base_y), level+1);
    mutate_int32_t(&(ptr->pen_style), level+1);
    mutate_c_str(ptr->cstring);
    mutate_c_str(ptr->comments);
    {
        if(ptr->next) { mutate_f_text(ptr->next, level+1); }
        len = 0;
        arr = pool_get_values("f_text", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->next;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->next = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->next = ptr_save;
        free(arr);
    }
    pool_insert("f_text", ptr1);
    #ifdef DEBUG
    printf("leave mutate_f_text  \n"); fflush(stdout);
    #endif
}
void mutate_f_spline(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_f_spline  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct f_spline* ptr = ptr1;
    mutate_int32_t(&(ptr->tagged), level+1);
    mutate_int32_t(&(ptr->distrib), level+1);
    mutate_int32_t(&(ptr->type), level+1);
    mutate_int32_t(&(ptr->style), level+1);
    mutate_int32_t(&(ptr->thickness), level+1);
    mutate_int32_t(&(ptr->pen_color), level+1);
    mutate_int32_t(&(ptr->fill_color), level+1);
    mutate_int32_t(&(ptr->fill_style), level+1);
    mutate_int32_t(&(ptr->depth), level+1);
    mutate_int32_t(&(ptr->pen_style), level+1);
    mutate_float(&(ptr->style_val), level+1);
    {
        if(ptr->for_arrow) { mutate_f_arrow(ptr->for_arrow, level+1); }
        len = 0;
        arr = pool_get_values("f_arrow", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->for_arrow;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->for_arrow = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->for_arrow = ptr_save;
        free(arr);
    }
    {
        if(ptr->back_arrow) { mutate_f_arrow(ptr->back_arrow, level+1); }
        len = 0;
        arr = pool_get_values("f_arrow", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->back_arrow;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->back_arrow = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->back_arrow = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->cap_style), level+1);
    {
        if(ptr->points) { mutate_f_point(ptr->points, level+1); }
        len = 0;
        arr = pool_get_values("f_point", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->points;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->points = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->points = ptr_save;
        free(arr);
    }
    {
        if(ptr->sfactors) { mutate_f_shape(ptr->sfactors, level+1); }
        len = 0;
        arr = pool_get_values("f_shape", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->sfactors;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->sfactors = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->sfactors = ptr_save;
        free(arr);
    }
    mutate_c_str(ptr->comments);
    {
        if(ptr->next) { mutate_f_spline(ptr->next, level+1); }
        len = 0;
        arr = pool_get_values("f_spline", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->next;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->next = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->next = ptr_save;
        free(arr);
    }
    pool_insert("f_spline", ptr1);
    #ifdef DEBUG
    printf("leave mutate_f_spline  \n"); fflush(stdout);
    #endif
}
void mutate_f_shape(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_f_shape  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct f_shape* ptr = ptr1;
    mutate_double(&(ptr->s), level+1);
    {
        if(ptr->next) { mutate_f_shape(ptr->next, level+1); }
        len = 0;
        arr = pool_get_values("f_shape", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->next;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->next = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->next = ptr_save;
        free(arr);
    }
    pool_insert("f_shape", ptr1);
    #ifdef DEBUG
    printf("leave mutate_f_shape  \n"); fflush(stdout);
    #endif
}
void mutate_f_compound(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_f_compound  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct f_compound* ptr = ptr1;
    mutate_int32_t(&(ptr->tagged), level+1);
    mutate_int32_t(&(ptr->distrib), level+1);
    mutate_f_pos(&(ptr->nwcorner), level+1);
    mutate_f_pos(&(ptr->secorner), level+1);
    {
        if(ptr->lines) { mutate_f_line(ptr->lines, level+1); }
        len = 0;
        arr = pool_get_values("f_line", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->lines;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->lines = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->lines = ptr_save;
        free(arr);
    }
    {
        if(ptr->ellipses) { mutate_f_ellipse(ptr->ellipses, level+1); }
        len = 0;
        arr = pool_get_values("f_ellipse", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->ellipses;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->ellipses = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->ellipses = ptr_save;
        free(arr);
    }
    {
        if(ptr->splines) { mutate_f_spline(ptr->splines, level+1); }
        len = 0;
        arr = pool_get_values("f_spline", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->splines;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->splines = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->splines = ptr_save;
        free(arr);
    }
    {
        if(ptr->texts) { mutate_f_text(ptr->texts, level+1); }
        len = 0;
        arr = pool_get_values("f_text", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->texts;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->texts = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->texts = ptr_save;
        free(arr);
    }
    {
        if(ptr->arcs) { mutate_f_arc(ptr->arcs, level+1); }
        len = 0;
        arr = pool_get_values("f_arc", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->arcs;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->arcs = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->arcs = ptr_save;
        free(arr);
    }
    mutate_c_str(ptr->comments);
    {
        if(ptr->parent) { mutate_f_compound(ptr->parent, level+1); }
        len = 0;
        arr = pool_get_values("f_compound", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->parent;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->parent = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->parent = ptr_save;
        free(arr);
    }
    {
        if(ptr->GABPtr) { mutate_f_compound(ptr->GABPtr, level+1); }
        len = 0;
        arr = pool_get_values("f_compound", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->GABPtr;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->GABPtr = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->GABPtr = ptr_save;
        free(arr);
    }
    mutate_int8_t(&(ptr->draw_parent), level+1);
    {
        if(ptr->compounds) { mutate_f_compound(ptr->compounds, level+1); }
        len = 0;
        arr = pool_get_values("f_compound", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->compounds;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->compounds = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->compounds = ptr_save;
        free(arr);
    }
    {
        if(ptr->next) { mutate_f_compound(ptr->next, level+1); }
        len = 0;
        arr = pool_get_values("f_compound", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->next;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->next = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->next = ptr_save;
        free(arr);
    }
    pool_insert("f_compound", ptr1);
    #ifdef DEBUG
    printf("leave mutate_f_compound  \n"); fflush(stdout);
    #endif
}
void mutate_f_linkinfo(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_f_linkinfo  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct f_linkinfo* ptr = ptr1;
    {
        if(ptr->line) { mutate_f_line(ptr->line, level+1); }
        len = 0;
        arr = pool_get_values("f_line", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->line;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->line = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->line = ptr_save;
        free(arr);
    }
    {
        if(ptr->endpt) { mutate_f_point(ptr->endpt, level+1); }
        len = 0;
        arr = pool_get_values("f_point", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->endpt;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->endpt = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->endpt = ptr_save;
        free(arr);
    }
    {
        if(ptr->prevpt) { mutate_f_point(ptr->prevpt, level+1); }
        len = 0;
        arr = pool_get_values("f_point", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->prevpt;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->prevpt = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->prevpt = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->two_pts), level+1);
    {
        if(ptr->next) { mutate_f_linkinfo(ptr->next, level+1); }
        len = 0;
        arr = pool_get_values("f_linkinfo", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->next;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->next = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->next = ptr_save;
        free(arr);
    }
    pool_insert("f_linkinfo", ptr1);
    #ifdef DEBUG
    printf("leave mutate_f_linkinfo  \n"); fflush(stdout);
    #endif
}
void mutate_counts(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_counts  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct counts* ptr = ptr1;
    mutate_int32_t(&(ptr->num_arcs), level+1);
    mutate_int32_t(&(ptr->num_lines), level+1);
    mutate_int32_t(&(ptr->num_ellipses), level+1);
    mutate_int32_t(&(ptr->num_splines), level+1);
    mutate_int32_t(&(ptr->num_texts), level+1);
    mutate_int32_t(&(ptr->cnt_arcs), level+1);
    mutate_int32_t(&(ptr->cnt_lines), level+1);
    mutate_int32_t(&(ptr->cnt_ellipses), level+1);
    mutate_int32_t(&(ptr->cnt_splines), level+1);
    mutate_int32_t(&(ptr->cnt_texts), level+1);
    pool_insert("counts", ptr1);
    #ifdef DEBUG
    printf("leave mutate_counts  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_14(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_15(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_16(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_17(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_18(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_19(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_20(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_21(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_22(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_23(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_24(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_25(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_26(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_27(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_27  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_27* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_27", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_27  \n"); fflush(stdout);
    #endif
}
void mutate__patrn_strct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate__patrn_strct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct _patrn_strct* ptr = ptr1;
    mutate_int32_t(&(ptr->owidth), level+1);
    mutate_int32_t(&(ptr->oheight), level+1);
    mutate_c_str(ptr->odata);
    mutate_int32_t(&(ptr->cwidth), level+1);
    mutate_int32_t(&(ptr->cheight), level+1);
    mutate_c_str(ptr->cdata);
    pool_insert("_patrn_strct", ptr1);
    #ifdef DEBUG
    printf("leave mutate__patrn_strct  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_28(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_29(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_30(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_31(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_32(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_33(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_34(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_35(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_36(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_37(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_38(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_39(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_40(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_41(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_41  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_41* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_41", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_41  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_42(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_43(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_44(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_45(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_46(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_47(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_48(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_49(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_50(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_51(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_52(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_53(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_54(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_55(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_55  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_55* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_55", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_55  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_56(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_57(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_58(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_59(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_60(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_61(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_62(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_63(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_64(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_65(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_66(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_67(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_68(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_69(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_69  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_69* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_69", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_69  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_70(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_71(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_72(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_73(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_74(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_75(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_76(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_77(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_78(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_79(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_80(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_81(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_82(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_83(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_83  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_83* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_83", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_83  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_84(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_85(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_86(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_87(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_88(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_89(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_90(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_91(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_92(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_93(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_94(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_95(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_96(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_97(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_97  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_97* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_97", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_97  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_98(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_99(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_100(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_101(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_102(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_103(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_104(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_105(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_106(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_107(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_108(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_109(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_110(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_111(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_111  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_111* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_111", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_111  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_112(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_113(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_114(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_115(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_116(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_117(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_118(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_119(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_120(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_121(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_122(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_123(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_124(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_125(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_125  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_125* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_125", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_125  \n"); fflush(stdout);
    #endif
}
void mutate__IO_FILE(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_126(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_127(void* ptr1, int level){return ;}
void mutate__IO_marker(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_128(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_129(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_130(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_131(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_132(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_133(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_134(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_135(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_136(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_137(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_138(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_139(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_140(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_141(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_142(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_143(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_144(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_145(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_145  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_145* ptr = ptr1;
    mutate_int32_t(&(ptr->length), level+1);
    mutate_int32_t(&(ptr->ascent), level+1);
    mutate_int32_t(&(ptr->descent), level+1);
    pool_insert("memfuzz_anonymous_struct_145", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_145  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_146(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_146  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_146* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_146", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_146  \n"); fflush(stdout);
    #endif
}
void mutate_xfont(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_xfont  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct xfont* ptr = ptr1;
    mutate_int32_t(&(ptr->size), level+1);
    mutate_int64_t(&(ptr->fid), level+1);
    mutate_c_str(ptr->fname);
    mutate_c_str(ptr->bname);
    //ptr->fstruct = ...(struct anonymous *{struct _XExtData *ext_data; long unsigned int  fid; unsigned int  direction; unsigned int  min_char_or_byte2; unsigned int  max_char_or_byte2; unsigned int  min_byte1; unsigned int  max_byte1; int  all_chars_exist; unsigned int  default_char; int  n_properties; struct anonymous *{long unsigned int  name; long unsigned int  card32; } properties; struct anonymous {short int  lbearing; short int  rbearing; short int  width; short int  ascent; short int  descent; short unsigned int  attributes; } min_bounds; struct anonymous {short int  lbearing; short int  rbearing; short int  width; short int  ascent; short int  descent; short unsigned int  attributes; } max_bounds; struct anonymous *{short int  lbearing; short int  rbearing; short int  width; short int  ascent; short int  descent; short unsigned int  attributes; } per_char; int  ascent; int  descent; } fstruct)
    {
        if(ptr->fset) { mutate__XOC(ptr->fset, level+1); }
        len = 0;
        arr = pool_get_values("_XOC", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->fset;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->fset = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->fset = ptr_save;
        free(arr);
    }
    {
        if(ptr->next) { mutate_xfont(ptr->next, level+1); }
        len = 0;
        arr = pool_get_values("xfont", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->next;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->next = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->next = ptr_save;
        free(arr);
    }
    pool_insert("xfont", ptr1);
    #ifdef DEBUG
    printf("leave mutate_xfont  \n"); fflush(stdout);
    #endif
}
void mutate__fstruct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate__fstruct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct _fstruct* ptr = ptr1;
    mutate_c_str(ptr->name);
    mutate_int32_t(&(ptr->xfontnum), level+1);
    pool_insert("_fstruct", ptr1);
    #ifdef DEBUG
    printf("leave mutate__fstruct  \n"); fflush(stdout);
    #endif
}
void mutate__xfstruct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate__xfstruct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct _xfstruct* ptr = ptr1;
    mutate_c_str(ptr->template);
    {
        if(ptr->xfontlist) { mutate_xfont(ptr->xfontlist, level+1); }
        len = 0;
        arr = pool_get_values("xfont", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->xfontlist;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->xfontlist = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->xfontlist = ptr_save;
        free(arr);
    }
    pool_insert("_xfstruct", ptr1);
    #ifdef DEBUG
    printf("leave mutate__xfstruct  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_147(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_147  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_147* ptr = ptr1;
    mutate_c_str(ptr->name);
    mutate_int32_t(&(ptr->u_line), level+1);
    //ptr->func = ...(function func)
    mutate_int8_t(&(ptr->checkmark), level+1);
    pool_insert("memfuzz_anonymous_struct_147", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_147  \n"); fflush(stdout);
    #endif
}
void mutate_main_menu_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_main_menu_struct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct main_menu_struct* ptr = ptr1;
    assign_int8_t_array(&(ptr->label), level + 1, 16);
    assign_int8_t_array(&(ptr->menu_name), level + 1, 16);
    assign_int8_t_array(&(ptr->hint), level + 1, 16);
    //ptr->menu = ...(struct anonymous *{char  *name; int  u_line; function func; char  checkmark; } menu)
    {
        if(ptr->widget) { mutate__WidgetRec(ptr->widget, level+1); }
        len = 0;
        arr = pool_get_values("_WidgetRec", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->widget;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->widget = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->widget = ptr_save;
        free(arr);
    }
    {
        if(ptr->menuwidget) { mutate__WidgetRec(ptr->menuwidget, level+1); }
        len = 0;
        arr = pool_get_values("_WidgetRec", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->menuwidget;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->menuwidget = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->menuwidget = ptr_save;
        free(arr);
    }
    pool_insert("main_menu_struct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_main_menu_struct  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_148(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_149(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_150(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_151(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_152(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_153(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_154(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_155(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_156(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_157(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_158(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_159(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_160(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_161(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_161  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_161* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_161", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_161  \n"); fflush(stdout);
    #endif
}
void mutate__icon_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate__icon_struct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct _icon_struct* ptr = ptr1;
    mutate_int32_t(&(ptr->width), level+1);
    mutate_int32_t(&(ptr->height), level+1);
    mutate_c_str(ptr->bits);
    pool_insert("_icon_struct", ptr1);
    #ifdef DEBUG
    printf("leave mutate__icon_struct  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_162(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_163(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_164(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_165(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_166(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_167(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_168(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_169(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_170(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_171(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_172(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_173(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_174(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_175(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_175  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_175* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_175", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_175  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_176(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_177(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_178(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_179(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_180(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_181(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_182(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_183(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_184(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_185(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_186(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_187(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_188(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_189(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_189  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_189* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_189", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_189  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_190(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_191(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_192(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_193(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_194(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_195(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_196(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_197(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_198(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_199(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_200(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_201(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_202(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_203(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_203  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_203* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_203", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_203  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_204(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_205(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_206(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_207(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_208(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_209(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_210(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_211(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_212(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_213(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_214(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_215(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_216(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_217(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_217  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_217* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_217", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_217  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_218(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_218  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_218* ptr = ptr1;
    mutate_int32_t(&(ptr->seg_idx), level+1);
    mutate_int32_t(&(ptr->x), level+1);
    mutate_int32_t(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_218", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_218  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_219(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_219  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_219* ptr = ptr1;
    //ptr->isects = ...(struct anonymous *{int  seg_idx; int  x; int  y; } isects)
    mutate_int32_t(&(ptr->nr_isects), level+1);
    mutate_int32_t(&(ptr->max_isects), level+1);
    pool_insert("memfuzz_anonymous_struct_219", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_219  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_220(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_220  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_220* ptr = ptr1;
        mutate_int32_t(&(ptr->type), level+1);
    pool_insert("memfuzz_anonymous_struct_220", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_220  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_221(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_221  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_221* ptr = ptr1;
    mutate_int32_t(&(ptr->x), level+1);
    mutate_int32_t(&(ptr->y), level+1);
    mutate_enum(&(ptr->ptype), 6);
    mutate_double(&(ptr->dist), level+1);
    pool_insert("memfuzz_anonymous_struct_221", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_221  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_222(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_222  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_222* ptr = ptr1;
    //ptr->points = ...(struct anonymous *{int  x; int  y; enum ptype; double  dist; } points)
    mutate_int32_t(&(ptr->points_next), level+1);
    mutate_int32_t(&(ptr->points_max), level+1);
    pool_insert("memfuzz_anonymous_struct_222", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_222  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_223(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_224(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_225(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_226(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_227(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_228(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_229(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_230(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_231(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_232(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_233(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_234(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_235(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_236(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_237(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_238(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_239(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_240(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_241(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_242(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_243(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_244(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_245(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_246(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_247(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_248(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_249(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_250(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_251(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_252(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_253(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_254(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_255(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_256(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_257(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_258(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_259(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_260(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_261(void* ptr1, int level){return ;}
void mutate__XEvent(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_262(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_263(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_264(void* ptr1, int level){return ;}
void mutate__WidgetRec(void* ptr1, int level){return ;}
void mutate__WidgetClassRec(void* ptr1, int level){return ;}
void mutate__XtActionsRec(void* ptr1, int level){return ;}
void mutate__CompositeClassRec(void* ptr1, int level){return ;}
void mutate__ConstraintClassRec(void* ptr1, int level){return ;}
void mutate__ObjectClassRec(void* ptr1, int level){return ;}
void mutate__RectObjClassRec(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_265(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_266(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_267(void* ptr1, int level){return ;}
void mutate__XtCallbackRec(void* ptr1, int level){return ;}
void mutate__XtResource(void* ptr1, int level){return ;}
void mutate__XtTMRec(void* ptr1, int level){return ;}
void mutate__CorePart(void* ptr1, int level){return ;}
void mutate__CoreClassPart(void* ptr1, int level){return ;}
void mutate__CompositeClassPart(void* ptr1, int level){return ;}
void mutate__ConstraintClassPart(void* ptr1, int level){return ;}
void mutate__ObjectClassPart(void* ptr1, int level){return ;}
void mutate__RectObjClassPart(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_268(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_269(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_270(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_271(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_272(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_273(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_273  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_273* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_273", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_273  \n"); fflush(stdout);
    #endif
}
void mutate_choice_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_choice_struct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct choice_struct* ptr = ptr1;
    mutate_int32_t(&(ptr->value), level+1);
    {
        if(ptr->icon) { mutate__icon_struct(ptr->icon, level+1); }
        len = 0;
        arr = pool_get_values("_icon_struct", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->icon;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->icon = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->icon = ptr_save;
        free(arr);
    }
    mutate_int64_t(&(ptr->pixmap), level+1);
    pool_insert("choice_struct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_choice_struct  \n"); fflush(stdout);
    #endif
}
void mutate_ind_sw_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_ind_sw_struct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct ind_sw_struct* ptr = ptr1;
    mutate_int32_t(&(ptr->type), level+1);
    mutate_int64_t(&(ptr->func), level+1);
    assign_int8_t_array(&(ptr->line1), level + 1, 38);
    assign_int8_t_array(&(ptr->line2), level + 1, 8);
    mutate_int32_t(&(ptr->sw_width), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->i_varadr);
    len /= sizeof(int32_t);
    if(len != 0){ mutate_int32_t_array(ptr->i_varadr, level + 1, len); }
    #else
    //ptr->i_varadr = ...(int  *i_varadr)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->f_varadr);
    len /= sizeof(float);
    if(len != 0){ mutate_float_array(ptr->f_varadr, level + 1, len); }
    #else
    //ptr->f_varadr = ...(float  *f_varadr)
    #endif
    //ptr->inc_func = ...(function inc_func)
    //ptr->dec_func = ...(function dec_func)
    //ptr->show_func = ...(function show_func)
    mutate_int32_t(&(ptr->min), level+1);
    mutate_int32_t(&(ptr->max), level+1);
    mutate_float(&(ptr->inc), level+1);
    {
        if(ptr->choices) { mutate_choice_struct(ptr->choices, level+1); }
        len = 0;
        arr = pool_get_values("choice_struct", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->choices;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->choices = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->choices = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->numchoices), level+1);
    mutate_int32_t(&(ptr->sw_per_row), level+1);
    mutate_int32_t(&(ptr->update), level+1);
    {
        if(ptr->button) { mutate__WidgetRec(ptr->button, level+1); }
        len = 0;
        arr = pool_get_values("_WidgetRec", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->button;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->button = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->button = ptr_save;
        free(arr);
    }
    {
        if(ptr->formw) { mutate__WidgetRec(ptr->formw, level+1); }
        len = 0;
        arr = pool_get_values("_WidgetRec", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->formw;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->formw = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->formw = ptr_save;
        free(arr);
    }
    {
        if(ptr->updbut) { mutate__WidgetRec(ptr->updbut, level+1); }
        len = 0;
        arr = pool_get_values("_WidgetRec", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->updbut;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->updbut = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->updbut = ptr_save;
        free(arr);
    }
    mutate_int64_t(&(ptr->pixmap), level+1);
    {
        if(ptr->panel) { mutate__WidgetRec(ptr->panel, level+1); }
        len = 0;
        arr = pool_get_values("_WidgetRec", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->panel;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->panel = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->panel = ptr_save;
        free(arr);
    }
    pool_insert("ind_sw_struct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_ind_sw_struct  \n"); fflush(stdout);
    #endif
}
void mutate__RGB(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate__RGB  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct _RGB* ptr = ptr1;
    mutate_int16_t(&(ptr->r), level+1);
    mutate_int16_t(&(ptr->g), level+1);
    mutate_int16_t(&(ptr->b), level+1);
    pool_insert("_RGB", ptr1);
    #ifdef DEBUG
    printf("leave mutate__RGB  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_274(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_275(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_276(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_277(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_278(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_279(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_280(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_281(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_282(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_283(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_284(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_285(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_286(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_287(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_287  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_287* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_287", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_287  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_288(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_289(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_290(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_291(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_292(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_293(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_294(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_295(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_296(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_297(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_298(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_299(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_300(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_301(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_301  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_301* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_301", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_301  \n"); fflush(stdout);
    #endif
}
void mutate_timespec(void* ptr1, int level){return ;}
void mutate_stat(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_302(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_303(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_304(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_305(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_306(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_307(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_308(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_309(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_310(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_311(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_312(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_313(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_314(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_315(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_315  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_315* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_315", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_315  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_316(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_317(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_318(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_319(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_320(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_321(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_322(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_323(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_324(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_325(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_326(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_327(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_328(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_329(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_329  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_329* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_329", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_329  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_330(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_331(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_332(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_333(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_334(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_335(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_336(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_337(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_338(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_339(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_340(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_341(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_342(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_343(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_344(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_345(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_346(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_347(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_348(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_349(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_350(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_351(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_352(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_353(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_354(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_355(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_356(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_357(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_358(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_359(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_360(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_361(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_362(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_363(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_364(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_365(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_366(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_367(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_368(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_369(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_370(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_371(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_372(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_373(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_374(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_375(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_376(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_377(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_378(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_379(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_380(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_381(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_381  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_381* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_381", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_381  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_382(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_382  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_382* ptr = ptr1;
        mutate_int32_t(&(ptr->val), level+1);
    pool_insert("memfuzz_anonymous_struct_382", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_382  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_383(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_383  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_383* ptr = ptr1;
    {
        if(ptr->image) { mutate__icon_struct(ptr->image, level+1); }
        len = 0;
        arr = pool_get_values("_icon_struct", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->image;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->image = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->image = ptr_save;
        free(arr);
    }
    mutate_int64_t(&(ptr->image_pm), level+1);
    pool_insert("memfuzz_anonymous_struct_383", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_383  \n"); fflush(stdout);
    #endif
}
void mutate_sfactor_def(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_sfactor_def  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct sfactor_def* ptr = ptr1;
    assign_int8_t_array(&(ptr->label), level + 1, 13);
    mutate_double(&(ptr->value), level+1);
    pool_insert("sfactor_def", ptr1);
    #ifdef DEBUG
    printf("leave mutate_sfactor_def  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_384(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_384  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_384* ptr = ptr1;
    mutate_int32_t(&(ptr->thickness), level+1);
    mutate_int32_t(&(ptr->pen_color), level+1);
    mutate_int32_t(&(ptr->fill_color), level+1);
    mutate_int32_t(&(ptr->depth), level+1);
    mutate_int64_t(&(ptr->arc_type), level+1);
    mutate_int32_t(&(ptr->cap_style), level+1);
    mutate_int32_t(&(ptr->join_style), level+1);
    mutate_int32_t(&(ptr->style), level+1);
    mutate_float(&(ptr->style_val), level+1);
    mutate_int32_t(&(ptr->pen_style), level+1);
    mutate_int32_t(&(ptr->fill_style), level+1);
    mutate_c_str(ptr->comments);
    mutate_f_arrow(&(ptr->for_arrow), level+1);
    mutate_f_arrow(&(ptr->back_arrow), level+1);
    pool_insert("memfuzz_anonymous_struct_384", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_384  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_385(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_386(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_387(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_388(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_389(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_390(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_391(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_392(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_393(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_394(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_395(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_396(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_397(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_398(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_398  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_398* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_398", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_398  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_399(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_400(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_401(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_402(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_403(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_404(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_405(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_406(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_407(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_408(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_409(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_410(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_411(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_412(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_412  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_412* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_412", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_412  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_413(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_414(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_415(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_416(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_417(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_418(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_419(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_420(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_421(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_422(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_423(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_424(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_425(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_426(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_426  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_426* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_426", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_426  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_427(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_428(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_429(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_430(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_431(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_432(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_433(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_434(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_435(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_436(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_437(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_438(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_439(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_440(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_440  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_440* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_440", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_440  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_441(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_442(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_443(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_444(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_445(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_446(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_447(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_448(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_449(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_450(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_451(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_452(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_453(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_454(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_454  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_454* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_454", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_454  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_455(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_456(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_457(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_458(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_459(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_460(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_461(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_462(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_463(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_464(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_465(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_466(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_467(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_468(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_468  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_468* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_468", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_468  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_469(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_470(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_471(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_472(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_473(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_474(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_475(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_476(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_477(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_478(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_479(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_480(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_481(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_482(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_483(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_484(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_484  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_484* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_484", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_484  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_485(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_485  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_485* ptr = ptr1;
    mutate_int32_t(&(ptr->x), level+1);
    mutate_int32_t(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_485", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_485  \n"); fflush(stdout);
    #endif
}
void mutate_f_libobj(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_f_libobj  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct f_libobj* ptr = ptr1;
    //ptr->corner = ...(struct anonymous {int  x; int  y; } corner)
    {
        if(ptr->compound) { mutate_f_compound(ptr->compound, level+1); }
        len = 0;
        arr = pool_get_values("f_compound", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->compound;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->compound = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->compound = ptr_save;
        free(arr);
    }
    pool_insert("f_libobj", ptr1);
    #ifdef DEBUG
    printf("leave mutate_f_libobj  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_486(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_487(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_488(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_489(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_490(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_491(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_492(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_493(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_494(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_495(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_496(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_497(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_498(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_499(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_499  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_499* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_499", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_499  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_500(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_501(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_502(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_503(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_504(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_505(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_506(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_507(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_508(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_509(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_510(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_511(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_512(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_513(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_514(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_514  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_514* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_514", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_514  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_515(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_516(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_517(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_518(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_519(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_520(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_521(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_522(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_523(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_524(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_525(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_526(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_527(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_528(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_528  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_528* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_528", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_528  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_529(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_530(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_531(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_532(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_533(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_534(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_535(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_536(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_537(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_538(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_539(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_540(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_541(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_542(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_543(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_543  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_543* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_543", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_543  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_544(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_545(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_546(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_547(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_548(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_549(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_550(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_551(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_552(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_553(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_554(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_555(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_556(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_557(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_558(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_558  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_558* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_558", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_558  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_559(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_559  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_559* ptr = ptr1;
    mutate_int8_t(&(ptr->landscape), level+1);
    mutate_int8_t(&(ptr->flushleft), level+1);
    mutate_int8_t(&(ptr->units), level+1);
    mutate_int32_t(&(ptr->grid_unit), level+1);
    mutate_int32_t(&(ptr->papersize), level+1);
    mutate_float(&(ptr->magnification), level+1);
    mutate_int8_t(&(ptr->multiple), level+1);
    mutate_int32_t(&(ptr->transparent), level+1);
    pool_insert("memfuzz_anonymous_struct_559", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_559  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_560(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_561(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_562(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_563(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_564(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_565(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_566(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_567(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_568(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_569(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_570(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_571(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_572(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_573(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_574(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_574  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_574* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_574", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_574  \n"); fflush(stdout);
    #endif
}
void mutate_xfig_stream(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_xfig_stream  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct xfig_stream* ptr = ptr1;
    {
        if(ptr->fp) { mutate__IO_FILE(ptr->fp, level+1); }
        len = 0;
        arr = pool_get_values("_IO_FILE", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->fp;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->fp = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->fp = ptr_save;
        free(arr);
    }
    mutate_c_str(ptr->name);
    mutate_c_str(ptr->name_on_disk);
    mutate_c_str(ptr->content);
    //ptr->uncompress = ...(const *uncompress)
    assign_int8_t_array(&(ptr->name_buf), level + 1, 128);
    assign_int8_t_array(&(ptr->name_on_disk_buf), level + 1, 128);
    assign_int8_t_array(&(ptr->content_buf), level + 1, 128);
    pool_insert("xfig_stream", ptr1);
    #ifdef DEBUG
    printf("leave mutate_xfig_stream  \n"); fflush(stdout);
    #endif
}
void mutate__haeders(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate__haeders  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct _haeders* ptr = ptr1;
    mutate_c_str(ptr->type);
    mutate_c_str(ptr->bytes);
    //ptr->readfunc = ...(function readfunc)
    pool_insert("_haeders", ptr1);
    #ifdef DEBUG
    printf("leave mutate__haeders  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_575(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_576(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_577(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_578(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_579(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_580(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_581(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_582(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_583(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_584(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_585(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_586(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_587(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_588(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_589(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_589  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_589* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_589", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_589  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_590(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_591(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_592(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_593(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_594(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_595(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_596(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_597(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_598(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_599(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_600(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_601(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_602(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_603(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_604(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_604  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_604* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_604", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_604  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_605(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_606(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_607(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_608(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_609(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_610(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_611(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_612(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_613(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_614(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_615(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_616(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_617(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_618(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_618  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_618* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_618", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_618  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_619(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_619  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_619* ptr = ptr1;
    mutate_int32_t(&(ptr->Width), level+1);
    mutate_int32_t(&(ptr->Height), level+1);
    for(int i = 0; i < SAMPLE_TIMES; i++)
    {
        mutate_Cmap(&(ptr->ColorMap)[random()%256], level+1);
    }
    mutate_int32_t(&(ptr->BitPixel), level+1);
    mutate_int32_t(&(ptr->ColorResolution), level+1);
    mutate_int32_t(&(ptr->Background), level+1);
    mutate_int32_t(&(ptr->AspectRatio), level+1);
    pool_insert("memfuzz_anonymous_struct_619", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_619  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_620(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_620  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_620* ptr = ptr1;
    mutate_int32_t(&(ptr->transparent), level+1);
    mutate_int32_t(&(ptr->delayTime), level+1);
    mutate_int32_t(&(ptr->inputFlag), level+1);
    mutate_int32_t(&(ptr->disposal), level+1);
    pool_insert("memfuzz_anonymous_struct_620", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_620  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_621(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_622(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_623(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_624(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_625(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_626(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_627(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_628(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_629(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_630(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_631(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_632(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_633(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_634(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_635(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_635  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_635* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_635", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_635  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_636(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_637(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_638(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_639(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_640(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_641(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_642(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_643(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_644(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_645(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_646(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_647(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_648(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_649(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_649  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_649* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_649", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_649  \n"); fflush(stdout);
    #endif
}
void mutate_pcxhed(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_pcxhed  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct pcxhed* ptr = ptr1;
    mutate_int8_t(&(ptr->manuf), level+1);
    mutate_int8_t(&(ptr->ver), level+1);
    mutate_int8_t(&(ptr->encod), level+1);
    mutate_int8_t(&(ptr->bpp), level+1);
    mutate_int8_t(&(ptr->x1lo), level+1);
    mutate_int8_t(&(ptr->x1hi), level+1);
    mutate_int8_t(&(ptr->y1lo), level+1);
    mutate_int8_t(&(ptr->y1hi), level+1);
    mutate_int8_t(&(ptr->x2lo), level+1);
    mutate_int8_t(&(ptr->x2hi), level+1);
    mutate_int8_t(&(ptr->y2lo), level+1);
    mutate_int8_t(&(ptr->y2hi), level+1);
    assign_int8_t_array(&(ptr->unused1), level + 1, 4);
    assign_int8_t_array(&(ptr->pal16), level + 1, 48);
    mutate_int8_t(&(ptr->reserved), level+1);
    mutate_int8_t(&(ptr->nplanes), level+1);
    mutate_int8_t(&(ptr->bytelinelo), level+1);
    mutate_int8_t(&(ptr->bytelinehi), level+1);
    assign_int8_t_array(&(ptr->unused2), level + 1, 60);
    pool_insert("pcxhed", ptr1);
    #ifdef DEBUG
    printf("leave mutate_pcxhed  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_650(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_651(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_652(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_653(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_654(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_655(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_656(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_657(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_658(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_659(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_660(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_661(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_662(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_663(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_663  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_663* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_663", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_663  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_664(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_665(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_666(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_667(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_668(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_669(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_670(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_671(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_672(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_673(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_674(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_675(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_676(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_677(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_677  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_677* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_677", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_677  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_678(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_679(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_680(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_681(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_682(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_683(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_684(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_685(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_686(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_687(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_688(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_689(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_690(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_691(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_691  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_691* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_691", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_691  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_692(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_693(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_694(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_695(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_696(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_697(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_698(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_699(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_700(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_701(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_702(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_703(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_704(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_705(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_705  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_705* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_705", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_705  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_706(void* ptr1, int level){return ;}
void mutate__pcxhead(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate__pcxhead  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct _pcxhead* ptr = ptr1;
    mutate_int8_t(&(ptr->id), level+1);
    mutate_int8_t(&(ptr->vers), level+1);
    mutate_int8_t(&(ptr->format), level+1);
    mutate_int8_t(&(ptr->bppl), level+1);
    mutate_int16_t(&(ptr->xmin), level+1);
    mutate_int16_t(&(ptr->ymin), level+1);
    mutate_int16_t(&(ptr->xmax), level+1);
    mutate_int16_t(&(ptr->ymax), level+1);
    mutate_int16_t(&(ptr->hdpi), level+1);
    mutate_int16_t(&(ptr->vdpi), level+1);
    assign_int8_t_array(&(ptr->egapal), level + 1, 48);
    mutate_int8_t(&(ptr->reserv), level+1);
    mutate_int8_t(&(ptr->nplanes), level+1);
    mutate_int16_t(&(ptr->blp), level+1);
    mutate_int16_t(&(ptr->palinfo), level+1);
    mutate_int16_t(&(ptr->hscrnsiz), level+1);
    mutate_int16_t(&(ptr->vscrnsiz), level+1);
    assign_int8_t_array(&(ptr->fill), level + 1, 54);
    pool_insert("_pcxhead", ptr1);
    #ifdef DEBUG
    printf("leave mutate__pcxhead  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_707(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_708(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_709(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_710(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_711(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_712(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_713(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_714(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_715(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_716(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_717(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_718(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_719(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_720(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_721(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_722(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_723(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_724(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_725(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_726(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_727(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_728(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_729(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_730(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_731(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_732(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_733(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_734(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_735(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_736(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_737(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_738(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_739(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_740(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_741(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_742(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_743(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_744(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_745(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_746(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_747(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_748(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_749(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_750(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_751(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_752(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_753(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_754(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_755(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_756(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_757(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_758(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_759(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_760(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_761(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_762(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_763(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_763  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_763* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_763", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_763  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_764(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_765(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_765  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_765* ptr = ptr1;
    mutate_int32_t(&(ptr->x), level+1);
    mutate_int32_t(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_765", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_765  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_766(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_766  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_766* ptr = ptr1;
    //ptr->visual = ...(struct anonymous *{struct _XExtData *ext_data; long unsigned int  visualid; int  class; long unsigned int  red_mask; long unsigned int  green_mask; long unsigned int  blue_mask; int  bits_per_rgb; int  map_entries; } visual)
    mutate_int32_t(&(ptr->depth), level+1);
    pool_insert("memfuzz_anonymous_struct_766", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_766  \n"); fflush(stdout);
    #endif
}
void mutate_geom(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_geom  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct geom* ptr = ptr1;
    mutate_int32_t(&(ptr->wid), level+1);
    mutate_int32_t(&(ptr->ht), level+1);
    pool_insert("geom", ptr1);
    #ifdef DEBUG
    printf("leave mutate_geom  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_767(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_768(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_769(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_770(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_771(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_772(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_773(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_774(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_775(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_776(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_777(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_778(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_779(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_780(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_780  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_780* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_780", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_780  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_781(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_782(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_783(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_784(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_785(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_786(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_787(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_788(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_789(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_790(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_791(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_792(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_793(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_794(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_794  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_794* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_794", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_794  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_795(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_796(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_797(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_798(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_799(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_800(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_801(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_802(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_803(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_804(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_805(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_806(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_807(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_808(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_808  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_808* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_808", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_808  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_809(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_810(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_811(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_812(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_813(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_814(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_815(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_816(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_817(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_818(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_819(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_820(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_821(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_822(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_822  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_822* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_822", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_822  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_823(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_823  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_823* ptr = ptr1;
    mutate_int32_t(&(ptr->x), level+1);
    mutate_int32_t(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_823", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_823  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_824(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_825(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_826(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_827(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_828(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_829(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_830(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_831(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_832(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_833(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_834(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_835(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_836(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_837(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_837  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_837* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_837", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_837  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_838(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_839(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_840(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_841(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_842(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_843(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_844(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_845(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_846(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_847(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_848(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_849(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_850(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_851(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_852(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_852  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_852* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_852", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_852  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_853(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_854(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_855(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_856(void* ptr1, int level){return ;}
void mutate_funcs(void* ptr1, int level){return ;}
void mutate__XImage(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_857(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_858(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_859(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_860(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_861(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_862(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_863(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_864(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_865(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_866(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_867(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_868(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_869(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_870(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_870  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_870* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_870", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_870  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_871(void* ptr1, int level){return ;}
void mutate__fpnt(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate__fpnt  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct _fpnt* ptr = ptr1;
    mutate_double(&(ptr->x), level+1);
    mutate_double(&(ptr->y), level+1);
    pool_insert("_fpnt", ptr1);
    #ifdef DEBUG
    printf("leave mutate__fpnt  \n"); fflush(stdout);
    #endif
}
void mutate__arrow_shape(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate__arrow_shape  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct _arrow_shape* ptr = ptr1;
    mutate_int32_t(&(ptr->numpts), level+1);
    mutate_int32_t(&(ptr->tipno), level+1);
    mutate_int32_t(&(ptr->numfillpts), level+1);
    mutate_int8_t(&(ptr->simplefill), level+1);
    mutate_int8_t(&(ptr->clip), level+1);
    mutate_int8_t(&(ptr->half), level+1);
    mutate_double(&(ptr->tipmv), level+1);
    for(int i = 0; i < 6; i++)
    {
        mutate__fpnt(&(ptr->points)[i], level+1);
    }
    for(int i = 0; i < 6; i++)
    {
        mutate__fpnt(&(ptr->fillpoints)[i], level+1);
    }
    pool_insert("_arrow_shape", ptr1);
    #ifdef DEBUG
    printf("leave mutate__arrow_shape  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_872(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_873(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_874(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_875(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_876(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_877(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_878(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_879(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_880(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_881(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_882(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_883(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_884(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_885(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_885  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_885* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_885", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_885  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_886(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_887(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_888(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_889(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_890(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_891(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_892(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_893(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_894(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_895(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_896(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_897(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_898(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_899(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_900(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_901(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_902(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_903(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_904(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_905(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_906(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_907(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_908(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_909(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_910(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_911(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_912(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_913(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_914(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_915(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_916(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_917(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_918(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_919(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_920(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_921(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_922(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_923(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_924(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_925(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_926(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_927(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_928(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_929(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_930(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_931(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_932(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_933(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_933  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_933* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_933", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_933  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_934(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_935(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_936(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_937(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_938(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_939(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_940(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_941(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_942(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_943(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_944(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_945(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_946(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_947(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_948(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_948  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_948* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_948", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_948  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_949(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_950(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_951(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_952(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_953(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_954(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_955(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_956(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_957(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_958(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_959(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_960(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_961(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_962(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_962  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_962* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_962", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_962  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_963(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_964(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_965(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_966(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_967(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_968(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_969(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_970(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_971(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_972(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_973(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_974(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_975(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_976(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_976  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_976* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_976", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_976  \n"); fflush(stdout);
    #endif
}
void mutate_angle_table(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_angle_table  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct angle_table* ptr = ptr1;
    mutate_int32_t(&(ptr->x), level+1);
    mutate_int32_t(&(ptr->y), level+1);
    mutate_double(&(ptr->angle), level+1);
    pool_insert("angle_table", ptr1);
    #ifdef DEBUG
    printf("leave mutate_angle_table  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_977(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_978(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_979(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_980(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_981(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_982(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_983(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_984(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_985(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_986(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_987(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_988(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_989(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_990(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_990  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_990* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_990", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_990  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_991(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_992(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_993(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_994(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_995(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_996(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_997(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_998(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_999(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1000(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1001(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1002(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1003(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1004(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1004  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1004* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1004", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1004  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1005(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1006(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1007(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1008(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1009(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1010(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1011(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1012(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1013(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1014(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1015(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1016(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1017(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1018(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1018  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1018* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1018", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1018  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1019(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1020(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1021(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1022(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1023(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1024(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1025(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1026(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1027(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1028(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1029(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1030(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1031(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1032(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1033(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1034(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1035(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1036(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1037(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1038(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1039(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1040(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1041(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1042(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1042  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1042* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1042", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1042  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1043(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1044(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1045(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1046(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1047(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1048(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1049(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1050(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1051(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1052(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1053(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1054(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1055(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1056(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1057(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1057  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1057* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1057", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1057  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1058(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1059(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1060(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1061(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1062(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1063(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1064(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1065(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1066(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1067(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1068(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1069(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1070(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1071(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1071  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1071* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1071", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1071  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1072(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1073(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1074(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1075(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1076(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1077(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1078(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1079(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1080(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1081(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1082(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1083(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1084(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1085(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1085  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1085* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1085", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1085  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1086(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1087(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1088(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1089(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1090(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1091(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1092(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1093(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1094(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1095(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1096(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1097(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1098(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1099(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1099  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1099* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1099", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1099  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1100(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1101(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1102(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1103(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1104(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1105(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1106(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1107(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1108(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1109(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1110(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1111(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1112(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1113(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1113  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1113* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1113", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1113  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1114(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1115(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1116(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1117(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1118(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1119(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1120(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1121(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1122(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1123(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1124(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1125(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1126(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1127(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1127  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1127* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1127", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1127  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1128(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1129(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1130(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1131(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1132(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1133(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1134(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1135(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1136(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1137(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1138(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1139(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1140(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1141(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1142(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1143(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1144(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1145(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1146(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1147(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1148(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1149(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1150(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1151(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1152(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1153(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1154(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1155(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1156(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1157(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1158(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1159(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1160(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1161(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1162(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1163(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1164(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1165(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1166(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1167(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1168(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1169(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1170(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1171(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1172(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1173(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1174(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1175(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1176(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1177(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1178(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1179(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1179  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1179* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1179", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1179  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1180(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1181(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1182(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1183(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1184(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1185(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1186(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1187(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1188(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1189(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1190(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1191(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1192(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1193(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1194(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1195(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1196(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1197(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1198(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1199(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1200(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1201(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1202(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1203(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1204(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1205(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1206(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1207(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1208(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1209(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1210(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1211(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1212(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1213(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1214(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1215(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1216(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1217(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1218(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1219(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1220(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1221(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1222(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1223(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1224(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1225(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1226(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1227(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1228(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1229(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1230(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1231(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1232(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1232  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1232* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1232", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1232  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1233(void* ptr1, int level){return ;}
void mutate_mode_switch_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_mode_switch_struct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct mode_switch_struct* ptr = ptr1;
    {
        if(ptr->icon) { mutate__icon_struct(ptr->icon, level+1); }
        len = 0;
        arr = pool_get_values("_icon_struct", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->icon;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->icon = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->icon = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->mode), level+1);
    //ptr->setmode_func = ...(function setmode_func)
    mutate_int32_t(&(ptr->objmask), level+1);
    mutate_int64_t(&(ptr->indmask), level+1);
    assign_int8_t_array(&(ptr->modemsg), level + 1, 80);
    mutate_int8_t(&(ptr->popup), level+1);
    {
        if(ptr->widget) { mutate__WidgetRec(ptr->widget, level+1); }
        len = 0;
        arr = pool_get_values("_WidgetRec", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->widget;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->widget = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->widget = ptr_save;
        free(arr);
    }
    mutate_int64_t(&(ptr->pixmap), level+1);
    mutate_int64_t(&(ptr->reversePM), level+1);
    pool_insert("mode_switch_struct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_mode_switch_struct  \n"); fflush(stdout);
    #endif
}
void mutate__CompKey(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate__CompKey  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct _CompKey* ptr = ptr1;
    mutate_int8_t(&(ptr->key), level+1);
    mutate_int8_t(&(ptr->first), level+1);
    mutate_int8_t(&(ptr->second), level+1);
    {
        if(ptr->next) { mutate__CompKey(ptr->next, level+1); }
        len = 0;
        arr = pool_get_values("_CompKey", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->next;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->next = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->next = ptr_save;
        free(arr);
    }
    pool_insert("_CompKey", ptr1);
    #ifdef DEBUG
    printf("leave mutate__CompKey  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1234(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1235(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1236(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1237(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1238(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1239(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1240(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1241(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1242(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1243(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1244(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1245(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1246(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1247(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1248(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1249(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1249  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1249* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1249", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1249  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1250(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1251(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1252(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1253(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1254(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1255(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1256(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1257(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1258(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1259(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1260(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1261(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1262(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1263(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1264(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1265(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1266(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1267(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1268(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1269(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1270(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1271(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1272(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1273(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1274(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1275(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1276(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1277(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1278(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1279(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1280(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1281(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1282(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1283(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1284(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1285(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1286(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1287(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1288(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1289(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1290(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1291(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1292(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1293(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1294(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1295(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1296(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1297(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1298(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1299(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1300(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1300  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1300* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1300", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1300  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1301(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1302(void* ptr1, int level){return ;}
void mutate__global(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate__global  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct _global* ptr = ptr1;
    mutate_int8_t(&(ptr->tracking), level+1);
    mutate_int8_t(&(ptr->autorefresh), level+1);
    mutate_int8_t(&(ptr->show_pageborder), level+1);
    mutate_int8_t(&(ptr->showdepthmanager), level+1);
    mutate_int8_t(&(ptr->showballoons), level+1);
    mutate_int8_t(&(ptr->showlengths), level+1);
    mutate_int8_t(&(ptr->shownums), level+1);
    mutate_int8_t(&(ptr->allownegcoords), level+1);
    mutate_int8_t(&(ptr->showaxislines), level+1);
    pool_insert("_global", ptr1);
    #ifdef DEBUG
    printf("leave mutate__global  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1303(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1303  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_1303* ptr = ptr1;
        mutate_int8_t(&(ptr->val), level+1);
    pool_insert("memfuzz_anonymous_struct_1303", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1303  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1304(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1305(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1306(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1307(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1308(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1309(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1310(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1311(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1312(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1313(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1314(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1315(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1316(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1317(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1318(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1319(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1320(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1321(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1322(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1323(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1324(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1325(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1326(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1327(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1328(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1329(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1330(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1331(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1332(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1333(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1334(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1335(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1336(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1337(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1338(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1339(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1340(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1341(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1342(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1343(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1344(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1345(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1346(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1347(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1348(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1349(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1350(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1351(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1352(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1353(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1354(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1355(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1356(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1357(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1357  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1357* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1357", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1357  \n"); fflush(stdout);
    #endif
}
void mutate__HSV(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate__HSV  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct _HSV* ptr = ptr1;
    mutate_float(&(ptr->h), level+1);
    mutate_float(&(ptr->s), level+1);
    mutate_float(&(ptr->v), level+1);
    pool_insert("_HSV", ptr1);
    #ifdef DEBUG
    printf("leave mutate__HSV  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1358(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1358  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1358* ptr = ptr1;
    {
        if(ptr->app) { mutate__XtAppStruct(ptr->app, level+1); }
        len = 0;
        arr = pool_get_values("_XtAppStruct", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->app;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->app = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->app = ptr_save;
        free(arr);
    }
    {
        if(ptr->dpy) { mutate__XDisplay(ptr->dpy, level+1); }
        len = 0;
        arr = pool_get_values("_XDisplay", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->dpy;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->dpy = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->dpy = ptr_save;
        free(arr);
    }
    {
        if(ptr->gc) { mutate__XGC(ptr->gc, level+1); }
        len = 0;
        arr = pool_get_values("_XGC", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->gc;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->gc = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->gc = ptr_save;
        free(arr);
    }
    mutate_int64_t(&(ptr->root), level+1);
    mutate_int8_t(&(ptr->drawn), level+1);
    mutate_int32_t(&(ptr->x), level+1);
    mutate_int32_t(&(ptr->y), level+1);
    mutate_int32_t(&(ptr->ox), level+1);
    mutate_int32_t(&(ptr->oy), level+1);
    mutate_int32_t(&(ptr->width), level+1);
    mutate_int32_t(&(ptr->height), level+1);
    mutate_int64_t(&(ptr->id), level+1);
    pool_insert("memfuzz_anonymous_struct_1358", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1358  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1359(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1360(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1361(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1362(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1363(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1364(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1365(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1366(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1367(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1368(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1369(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1370(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1371(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1372(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1373(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1374(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1375(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1376(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1377(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1378(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1379(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1380(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1381(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1382(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1383(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1384(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1385(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1386(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1387(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1388(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1389(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1390(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1391(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1392(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1393(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1394(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1395(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1396(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1397(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1398(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1399(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1400(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1401(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1402(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1403(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1404(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1405(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1406(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1407(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1408(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1409(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1410(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1411(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1412(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1413(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1414(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1415(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1416(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1417(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1418(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1419(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1420(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1421(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1422(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1423(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1424(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1425(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1426(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1427(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1428(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1429(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1430(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1431(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1432(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1433(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1434(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1435(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1436(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1437(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1438(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1439(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1440(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1441(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1442(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1443(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1444(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1445(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1446(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1447(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1448(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1449(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1450(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1451(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1452(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1453(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1454(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1455(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1456(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1457(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1458(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1458  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1458* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1458", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1458  \n"); fflush(stdout);
    #endif
}
void mutate_passwd(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1459(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1460(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1461(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1462(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1463(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1464(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1465(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1466(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1467(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1468(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1469(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1470(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1471(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1472(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1473(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1474(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1475(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1476(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1477(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1478(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1479(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1480(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1481(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1482(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1483(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1484(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1485(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1486(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1487(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1488(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1489(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1490(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1491(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1492(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1493(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1494(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1495(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1496(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1497(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1498(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1499(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1500(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1501(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1502(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1503(void* ptr1, int level){return ;}
void mutate__XawListReturnStruct(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1504(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1505(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1506(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1507(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1508(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1509(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1509  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1509* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1509", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1509  \n"); fflush(stdout);
    #endif
}
void mutate_dirent(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1510(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1511(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1512(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1513(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1514(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1515(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1516(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1517(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1518(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1519(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1520(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1521(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1522(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1523(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1524(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1525(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1526(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1527(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1528(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1529(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1530(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1531(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1532(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1533(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1534(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1535(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1536(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1537(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1538(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1539(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1540(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1541(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1542(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1543(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1544(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1545(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1546(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1547(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1548(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1549(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1550(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1551(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1552(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1553(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1554(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1555(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1556(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1557(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1558(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1559(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1560(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1561(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1562(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1563(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1564(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1565(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1566(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1566  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1566* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1566", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1566  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1567(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1568(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1568  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1568* ptr = ptr1;
    mutate_c_str(ptr->fn);
    mutate_int32_t(&(ptr->s), level+1);
    pool_insert("memfuzz_anonymous_struct_1568", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1568  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1569(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1570(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1571(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1572(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1573(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1574(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1575(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1576(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1577(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1578(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1579(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1580(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1581(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1582(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1583(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1584(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1585(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1586(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1587(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1588(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1589(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1590(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1591(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1592(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1593(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1594(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1595(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1596(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1597(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1598(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1599(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1600(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1601(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1602(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1603(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1604(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1605(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1606(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1607(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1608(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1609(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1610(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1611(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1612(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1613(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1614(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1615(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1616(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1617(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1618(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1619(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1619  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1619* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1619", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1619  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1620(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1621(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1622(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1623(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1624(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1625(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1626(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1627(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1628(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1629(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1630(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1631(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1632(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1633(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1634(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1635(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1636(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1637(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1638(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1639(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1640(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1641(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1642(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1643(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1644(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1645(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1646(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1647(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1648(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1649(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1650(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1651(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1652(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1653(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1654(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1655(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1656(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1657(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1658(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1659(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1660(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1661(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1662(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1663(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1664(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1665(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1666(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1667(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1668(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1669(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1670(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1671(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1672(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1672  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1672* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1672", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1672  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1673(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1674(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1675(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1676(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1677(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1678(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1679(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1680(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1681(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1682(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1683(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1684(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1685(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1686(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1687(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1688(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1689(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1690(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1691(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1692(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1693(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1694(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1695(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1696(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1697(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1698(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1699(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1700(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1701(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1702(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1703(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1704(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1705(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1706(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1707(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1708(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1709(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1710(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1711(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1712(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1713(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1714(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1715(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1716(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1717(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1718(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1719(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1720(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1721(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1722(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1723(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1724(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1725(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1726(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1727(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1728(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1729(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1730(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1731(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1732(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1733(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1734(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1735(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1736(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1737(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1738(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1738  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1738* ptr = ptr1;
    mutate_int32_t(&(ptr->type), level+1);
    mutate_c_str(ptr->label);
    mutate_c_str(ptr->info);
    pool_insert("memfuzz_anonymous_struct_1738", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1738  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1739(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1740(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1741(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1742(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1743(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1744(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1745(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1746(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1747(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1748(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1749(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1750(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1751(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1752(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1753(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1754(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1755(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1756(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1757(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1758(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1759(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1760(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1761(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1762(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1763(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1764(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1765(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1766(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1767(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1768(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1769(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1770(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1771(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1772(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1773(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1774(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1775(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1776(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1777(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1778(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1779(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1780(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1781(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1782(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1783(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1784(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1785(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1786(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1787(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1788(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1789(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1790(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1790  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1790* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1790", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1790  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1791(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1792(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1793(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1794(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1795(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1796(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1797(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1798(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1799(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1800(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1801(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1802(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1803(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1804(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1805(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1806(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1807(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1808(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1809(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1810(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1811(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1812(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1813(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1814(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1815(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1816(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1817(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1818(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1819(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1820(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1821(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1822(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1823(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1824(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1825(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1826(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1827(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1828(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1829(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1830(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1831(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1832(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1833(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1834(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1835(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1836(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1837(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1838(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1839(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1840(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1841(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1841  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1841* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1841", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1841  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1842(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1843(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1844(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1845(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1846(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1847(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1848(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1849(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1850(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1851(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1852(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1853(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1854(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1855(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1856(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1857(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1858(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1859(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1860(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1861(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1862(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1863(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1864(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1865(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1866(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1867(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1868(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1869(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1870(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1871(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1872(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1873(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1874(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1875(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1876(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1877(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1878(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1879(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1880(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1881(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1882(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1883(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1884(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1885(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1886(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1887(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1888(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1889(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1890(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1891(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1892(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1893(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1893  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1893* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1893", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1893  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1894(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1895(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1896(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1897(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1898(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1899(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1900(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1901(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1902(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1903(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1904(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1905(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1906(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1907(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1908(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1909(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1910(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1911(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1912(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1913(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1914(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1915(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1916(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1917(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1918(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1919(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1920(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1921(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1922(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1923(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1924(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1925(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1926(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1927(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1928(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1929(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1930(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1931(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1932(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1933(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1934(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1935(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1936(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1937(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1938(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1939(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1940(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1941(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1942(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1943(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1944(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1945(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1945  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1945* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1945", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1945  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1946(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1947(void* ptr1, int level){return ;}
void mutate_re_pattern_buffer(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1948(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1949(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1950(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1951(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1952(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1953(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1954(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1955(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1956(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1957(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1958(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1959(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1960(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1961(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1962(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1963(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1964(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1965(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1966(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1967(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1968(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1969(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1970(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1971(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1972(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1973(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1974(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1975(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1976(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1977(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1978(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1979(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1980(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1981(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1982(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1983(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1984(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1985(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1986(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1987(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1988(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1989(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1990(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1991(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1992(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1993(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1994(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1995(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1996(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1997(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1998(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1999(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1999  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1999* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_1999", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1999  \n"); fflush(stdout);
    #endif
}
void mutate__keyboard_history_s(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate__keyboard_history_s  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct _keyboard_history_s* ptr = ptr1;
    mutate_c_str(ptr->str);
    {
        if(ptr->next) { mutate__keyboard_history_s(ptr->next, level+1); }
        len = 0;
        arr = pool_get_values("_keyboard_history_s", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->next;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->next = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->next = ptr_save;
        free(arr);
    }
    {
        if(ptr->prior) { mutate__keyboard_history_s(ptr->prior, level+1); }
        len = 0;
        arr = pool_get_values("_keyboard_history_s", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->prior;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->prior = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->prior = ptr_save;
        free(arr);
    }
    pool_insert("_keyboard_history_s", ptr1);
    #ifdef DEBUG
    printf("leave mutate__keyboard_history_s  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2000(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2001(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2002(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2003(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2004(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2005(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2006(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2007(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2008(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2009(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2010(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2011(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2012(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2013(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2014(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2015(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2016(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2017(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2018(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2019(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2020(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2021(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2022(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2023(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2024(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2025(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2026(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2027(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2028(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2029(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2030(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2031(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2032(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2033(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2034(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2035(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2036(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2037(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2038(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2039(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2040(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2041(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2042(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2043(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2044(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2045(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2046(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2047(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2048(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2049(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2050(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_2050  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_2050* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_2050", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2050  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2051(void* ptr1, int level){return ;}
void mutate___va_list_tag(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate___va_list_tag  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct __va_list_tag* ptr = ptr1;
    mutate_int32_t(&(ptr->gp_offset), level+1);
    mutate_int32_t(&(ptr->fp_offset), level+1);
            pool_insert("__va_list_tag", ptr1);
    #ifdef DEBUG
    printf("leave mutate___va_list_tag  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2052(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2053(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2054(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2055(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2056(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2057(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2058(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2059(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2060(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2061(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2062(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2063(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2064(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2065(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2066(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2067(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2068(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2069(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2070(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2071(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2072(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2073(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2074(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2075(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2076(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2077(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2078(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2079(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2080(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2081(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2082(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2083(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2084(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2085(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2086(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2087(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2088(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2089(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2090(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2091(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2092(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2093(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2094(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2095(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2096(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2097(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2098(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2099(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2100(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2101(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2102(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_2102  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_2102* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_2102", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2102  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2103(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2104(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_2104  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_2104* ptr = ptr1;
    mutate_int32_t(&(ptr->x), level+1);
    mutate_int32_t(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_2104", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2104  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2105(void* ptr1, int level){return ;}
void mutate_lib_rec(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_lib_rec  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct lib_rec* ptr = ptr1;
    mutate_c_str(ptr->name);
    mutate_c_str(ptr->longname);
    mutate_c_str(ptr->path);
    mutate_int8_t(&(ptr->figs_at_top), level+1);
    mutate_int32_t(&(ptr->nsubs), level+1);
    //ptr->subdirs = ...(*subdirs[101])
    pool_insert("lib_rec", ptr1);
    #ifdef DEBUG
    printf("leave mutate_lib_rec  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2106(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2107(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2108(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2109(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2110(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2111(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2112(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2113(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2114(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2115(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2116(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2117(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2118(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2119(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2120(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2121(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2122(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2123(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2124(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2125(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2126(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2127(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2128(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2129(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2130(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2131(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2132(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2133(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2134(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2135(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2136(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2137(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2138(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2139(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2140(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2141(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2142(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2143(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2144(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2145(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2146(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2147(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2148(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2149(void* ptr1, int level){return ;}
void mutate__SimpleClassRec(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2150(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2151(void* ptr1, int level){return ;}
void mutate__ListClassRec(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2152(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2153(void* ptr1, int level){return ;}
void mutate__FigListClassRec(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate__FigListClassRec  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct _FigListClassRec* ptr = ptr1;
    mutate__CoreClassPart(&(ptr->core_class), level+1);
    //ptr->simple_class = ...(struct anonymous {function change_sensitive; } simple_class)
    //ptr->list_class = ...(struct anonymous {int  foo; } list_class)
    //ptr->figList_class = ...(struct anonymous {int  make_compiler_happy; } figList_class)
    pool_insert("_FigListClassRec", ptr1);
    #ifdef DEBUG
    printf("leave mutate__FigListClassRec  \n"); fflush(stdout);
    #endif
}
void mutate__FigListRec(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate__FigListRec  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct _FigListRec* ptr = ptr1;
    mutate__CorePart(&(ptr->core), level+1);
    //ptr->simple = ...(struct anonymous {long unsigned int  cursor; long unsigned int  insensitive_border; char  *cursor_name; long unsigned int  pointer_fg; long unsigned int  pointer_bg; char  international; } simple)
    //ptr->list = ...(struct anonymous {long unsigned int  foreground; short unsigned int  internal_width; short unsigned int  internal_height; short unsigned int  column_space; short unsigned int  row_space; int  default_cols; char  force_cols; char  paste; char  vertical_cols; int  longest; int  nitems; struct anonymous *{struct _XExtData *ext_data; long unsigned int  fid; unsigned int  direction; unsigned int  min_char_or_byte2; unsigned int  max_char_or_byte2; unsigned int  min_byte1; unsigned int  max_byte1; int  all_chars_exist; unsigned int  default_char; int  n_properties; struct anonymous *{long unsigned int  name; long unsigned int  card32; } properties; struct anonymous {short int  lbearing; short int  rbearing; short int  width; short int  ascent; short int  descent; short unsigned int  attributes; } min_bounds; struct anonymous {short int  lbearing; short int  rbearing; short int  width; short int  ascent; short int  descent; short unsigned int  attributes; } max_bounds; struct anonymous *{short int  lbearing; short int  rbearing; short int  width; short int  ascent; short int  descent; short unsigned int  attributes; } per_char; int  ascent; int  descent; } font; struct _XOC *fontset; char  **list; struct _XtCallbackRec *callback; int  is_highlighted; int  highlight; int  col_width; int  row_height; int  nrows; int  ncols; struct _XGC *normgc; struct _XGC *revgc; struct _XGC *graygc; int  freedoms; } list)
    //ptr->figlist = ...(struct anonymous {int  make_compiler_happy; } figlist)
    pool_insert("_FigListRec", ptr1);
    #ifdef DEBUG
    printf("leave mutate__FigListRec  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2154(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_2154  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_2154* ptr = ptr1;
    mutate_int32_t(&(ptr->make_compiler_happy), level+1);
    pool_insert("memfuzz_anonymous_struct_2154", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2154  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2155(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_2155  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_2155* ptr = ptr1;
    mutate_int32_t(&(ptr->make_compiler_happy), level+1);
    pool_insert("memfuzz_anonymous_struct_2155", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2155  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2156(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2157(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2158(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2159(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2160(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2161(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2162(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2163(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2164(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2165(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2166(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2167(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2168(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2169(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2170(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2171(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2172(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2173(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2174(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2175(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2176(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2177(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2178(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2179(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2180(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2181(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2182(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2183(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2184(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2185(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2186(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2187(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2188(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2189(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2190(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2191(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2192(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2193(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2194(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2195(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2196(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2197(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2198(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2199(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2200(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2201(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2202(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2203(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2204(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2205(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2206(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_2206  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_2206* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_2206", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2206  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2207(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2208(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2209(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2210(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2211(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2212(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2213(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2214(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2215(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2216(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2217(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2218(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2219(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2220(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2221(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2222(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2223(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2224(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2225(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2226(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2227(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2228(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2229(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2230(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2231(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2232(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2233(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2234(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2235(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2236(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2237(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2238(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2239(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2240(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2241(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2242(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2243(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2244(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2245(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2246(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2247(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2248(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2249(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2250(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2251(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2252(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2253(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2254(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2255(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2256(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2257(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2258(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2259(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2260(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2261(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2262(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2263(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2264(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2265(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2266(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2267(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2268(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2269(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2270(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2271(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2272(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2273(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2274(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2275(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2276(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2277(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2278(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2279(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2280(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2281(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2282(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2283(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2284(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2285(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2286(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2287(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2288(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2289(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2290(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2291(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2292(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2293(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2294(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2295(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2296(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2297(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2298(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2299(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2300(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2301(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2302(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2303(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2304(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2305(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2306(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2307(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2308(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2309(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_2309  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_2309* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_2309", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2309  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2310(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2311(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2312(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2313(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2314(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2315(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2316(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2317(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2318(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2319(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2320(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2321(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2322(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2323(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2324(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2325(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2326(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2327(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2328(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2329(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2330(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2331(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2332(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2333(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2334(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2335(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2336(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2337(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2338(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2339(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2340(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2341(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2342(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2343(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2344(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2345(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2346(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2347(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2348(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2349(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2350(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2351(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2352(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2353(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2354(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2355(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2356(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2357(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2358(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2359(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2360(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_2360  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_2360* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_2360", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2360  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2361(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2362(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2363(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2364(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2365(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2366(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2367(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2368(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2369(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2370(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2371(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2372(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2373(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2374(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2375(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2376(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2377(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2378(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2379(void* ptr1, int level){return ;}
void mutate_rotated_text_item_template(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_rotated_text_item_template  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct rotated_text_item_template* ptr = ptr1;
    mutate_int64_t(&(ptr->bitmap), level+1);
    {
        if(ptr->ximage) { mutate__XImage(ptr->ximage, level+1); }
        len = 0;
        arr = pool_get_values("_XImage", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->ximage;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->ximage = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->ximage = ptr_save;
        free(arr);
    }
    mutate_c_str(ptr->text);
    mutate_c_str(ptr->font_name);
    mutate_int64_t(&(ptr->fid), level+1);
    mutate_float(&(ptr->angle), level+1);
    mutate_int32_t(&(ptr->align), level+1);
    mutate_float(&(ptr->magnify), level+1);
    mutate_int32_t(&(ptr->cols_in), level+1);
    mutate_int32_t(&(ptr->rows_in), level+1);
    mutate_int32_t(&(ptr->cols_out), level+1);
    mutate_int32_t(&(ptr->rows_out), level+1);
    mutate_int32_t(&(ptr->nl), level+1);
    mutate_int32_t(&(ptr->max_width), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->corners_x);
    len /= sizeof(float);
    if(len != 0){ mutate_float_array(ptr->corners_x, level + 1, len); }
    #else
    //ptr->corners_x = ...(float  *corners_x)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->corners_y);
    len /= sizeof(float);
    if(len != 0){ mutate_float_array(ptr->corners_y, level + 1, len); }
    #else
    //ptr->corners_y = ...(float  *corners_y)
    #endif
    mutate_int64_t(&(ptr->size), level+1);
    mutate_int32_t(&(ptr->cached), level+1);
    {
        if(ptr->next) { mutate_rotated_text_item_template(ptr->next, level+1); }
        len = 0;
        arr = pool_get_values("rotated_text_item_template", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->next;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->next = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->next = ptr_save;
        free(arr);
    }
    pool_insert("rotated_text_item_template", ptr1);
    #ifdef DEBUG
    printf("leave mutate_rotated_text_item_template  \n"); fflush(stdout);
    #endif
}
void mutate_style_template(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_style_template  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct style_template* ptr = ptr1;
    mutate_float(&(ptr->magnify), level+1);
    mutate_int32_t(&(ptr->bbx_pad), level+1);
    pool_insert("style_template", ptr1);
    #ifdef DEBUG
    printf("leave mutate_style_template  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2380(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2381(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2382(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2383(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2384(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2385(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2386(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2387(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2388(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2389(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2390(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2391(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2392(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2393(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2394(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2395(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2396(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2397(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2398(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2399(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2400(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2401(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2402(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2403(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2404(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2405(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2406(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2407(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2408(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2409(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2410(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2411(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2412(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2413(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2414(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2415(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2416(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2417(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2418(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2419(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2420(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2421(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2422(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2423(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2424(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2425(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2426(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2427(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2428(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2429(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2430(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2431(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_2431  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_2431* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_2431", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2431  \n"); fflush(stdout);
    #endif
}
void mutate_tick_info_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_tick_info_struct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct tick_info_struct* ptr = ptr1;
    mutate_float(&(ptr->min_zoom), level+1);
    mutate_int32_t(&(ptr->skip), level+1);
    mutate_int32_t(&(ptr->length), level+1);
    pool_insert("tick_info_struct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_tick_info_struct  \n"); fflush(stdout);
    #endif
}
void mutate_ruler_skip_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_ruler_skip_struct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct ruler_skip_struct* ptr = ptr1;
    mutate_float(&(ptr->max_zoom), level+1);
    mutate_int32_t(&(ptr->skipt), level+1);
    mutate_int32_t(&(ptr->skipx), level+1);
    mutate_int32_t(&(ptr->prec), level+1);
    pool_insert("ruler_skip_struct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_ruler_skip_struct  \n"); fflush(stdout);
    #endif
}
void mutate_ruler_info_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_ruler_info_struct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct ruler_info_struct* ptr = ptr1;
    mutate_int32_t(&(ptr->ruler_unit), level+1);
    {
        if(ptr->skips) { mutate_ruler_skip_struct(ptr->skips, level+1); }
        len = 0;
        arr = pool_get_values("ruler_skip_struct", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->skips;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->skips = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->skips = ptr_save;
        free(arr);
    }
    {
        if(ptr->ticks) { mutate_tick_info_struct(ptr->ticks, level+1); }
        len = 0;
        arr = pool_get_values("tick_info_struct", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->ticks;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->ticks = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->ticks = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->nticks), level+1);
    pool_insert("ruler_info_struct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_ruler_info_struct  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2432(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2433(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2434(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2435(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2436(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2437(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2438(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2439(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2440(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2441(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2442(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2443(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2444(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2445(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2446(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2447(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2448(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2449(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2450(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2451(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2452(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2453(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2454(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2455(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2456(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2457(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2458(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2459(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2460(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2461(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2462(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2463(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2464(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2465(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2466(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2467(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2468(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2469(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2470(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2471(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2472(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2473(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2474(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2475(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2476(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2477(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2478(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2479(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2480(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2481(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2482(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2483(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2484(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2485(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2486(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2487(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2488(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2489(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2490(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2491(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2492(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2493(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_2493  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_2493* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_2493", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2493  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2494(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2495(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2496(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2497(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2498(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2499(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2500(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2501(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2502(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2503(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2504(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2505(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2506(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2507(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2508(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2509(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2510(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2511(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2512(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2513(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2514(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2515(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2516(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2517(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2518(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2519(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2520(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2521(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2522(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2523(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2524(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2525(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2526(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2527(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2528(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2529(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2530(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2531(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2532(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2533(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2534(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2535(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2536(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2537(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2538(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2539(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2540(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2541(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2542(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2543(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2544(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2545(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2546(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_2546  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_2546* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_2546", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2546  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2547(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2548(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2549(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2550(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2551(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2552(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2553(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2554(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2555(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2556(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2557(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2558(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2559(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2560(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2561(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2562(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2563(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2564(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2565(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2566(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2567(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2568(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2569(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2570(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2571(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2572(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2573(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2574(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2575(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2576(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2577(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2578(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2579(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2580(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2581(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2582(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2583(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2584(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2585(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2586(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2587(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2588(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2589(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2590(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2591(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2592(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2593(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2594(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2595(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2596(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2597(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_2597  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_2597* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_2597", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2597  \n"); fflush(stdout);
    #endif
}
void mutate_Element(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_Element  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct Element* ptr = ptr1;
    mutate_c_str(ptr->name);
    mutate_enum(&(ptr->type), 3);
            mutate_int64_t(&(ptr->flag), level+1);
    pool_insert("Element", ptr1);
    #ifdef DEBUG
    printf("leave mutate_Element  \n"); fflush(stdout);
    #endif
}
void mutate_Style(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_Style  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct Style* ptr = ptr1;
    mutate_c_str(ptr->name);
    for(int i = 0; i < SAMPLE_TIMES; i++)
    {
        mutate_Element(&(ptr->element)[random()%30], level+1);
    }
    pool_insert("Style", ptr1);
    #ifdef DEBUG
    printf("leave mutate_Style  \n"); fflush(stdout);
    #endif
}
void mutate_Style_family(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_Style_family  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct Style_family* ptr = ptr1;
    mutate_c_str(ptr->name);
    for(int i = 0; i < SAMPLE_TIMES; i++)
    {
        mutate_Style(&(ptr->style)[random()%16], level+1);
    }
    pool_insert("Style_family", ptr1);
    #ifdef DEBUG
    printf("leave mutate_Style_family  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2598(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2599(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2600(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2601(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2602(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2603(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2604(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2605(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2606(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2607(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2608(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2609(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2610(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2611(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2612(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2613(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2614(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2615(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2616(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2617(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2618(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2619(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2620(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2621(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2622(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2623(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2624(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2625(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2626(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2627(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2628(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2629(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2630(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2631(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2632(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2633(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2634(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2635(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2636(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2637(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2638(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2639(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2640(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2641(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2642(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2643(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2644(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2645(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2646(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2647(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2648(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2649(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2650(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_2650  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_2650* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_2650", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2650  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2651(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2652(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_2652  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_2652* ptr = ptr1;
    {
        if(ptr->widget) { mutate__WidgetRec(ptr->widget, level+1); }
        len = 0;
        arr = pool_get_values("_WidgetRec", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->widget;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->widget = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->widget = ptr_save;
        free(arr);
    }
    mutate_float(&(ptr->min), level+1);
    mutate_float(&(ptr->max), level+1);
    mutate_float(&(ptr->inc), level+1);
    pool_insert("memfuzz_anonymous_struct_2652", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2652  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2653(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2654(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2655(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2656(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2657(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2658(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2659(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2660(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2661(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2662(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2663(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2664(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2665(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2666(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_2666  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_2666* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_2666", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2666  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2667(void* ptr1, int level){return ;}
void mutate___jmp_buf_tag(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2668(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2669(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2670(void* ptr1, int level){return ;}
void mutate_jpeg_marker_struct(void* ptr1, int level){return ;}
void mutate_jpeg_common_struct(void* ptr1, int level){return ;}
void mutate_jpeg_error_mgr(void* ptr1, int level){return ;}
void mutate_jpeg_memory_mgr(void* ptr1, int level){return ;}
void mutate_jpeg_progress_mgr(void* ptr1, int level){return ;}
void mutate_jpeg_decompress_struct(void* ptr1, int level){return ;}
void mutate_jpeg_source_mgr(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2671(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2672(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2673(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2674(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2675(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2676(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2677(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2678(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2679(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2680(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2681(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2682(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2683(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2684(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2685(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_2685  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_2685* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_2685", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2685  \n"); fflush(stdout);
    #endif
}
void mutate_png_color_struct(void* ptr1, int level){return ;}
void mutate_png_color_16_struct(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2686(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2687(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2688(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2689(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2690(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2691(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2692(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2693(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2694(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2695(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2696(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2697(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2698(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2699(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_2699  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_2699* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_2699", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2699  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2700(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2701(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2702(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2703(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2704(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2705(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2706(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2707(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2708(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2709(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2710(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2711(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2712(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2713(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2714(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2715(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2716(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2717(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2718(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2719(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2720(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2721(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2722(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2723(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_2723  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_2723* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_2723", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2723  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2724(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2725(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2726(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2727(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2728(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2729(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2730(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2731(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2732(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2733(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2734(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2735(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2736(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2737(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2738(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_2738  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_2738* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_2738", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2738  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2739(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2740(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2741(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2742(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2743(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2744(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2745(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2746(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2747(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2748(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2749(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2750(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2751(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2752(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2753(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2754(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2755(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2756(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2757(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2758(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2759(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2760(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2761(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2762(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2763(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2764(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2765(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2766(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2767(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2768(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2769(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2770(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2771(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2772(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2773(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2774(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2775(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2776(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2777(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2778(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2779(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2780(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2781(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2782(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2783(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2784(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2785(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2786(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2787(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2788(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2789(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2790(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2791(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2792(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2793(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2794(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_2794  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_2794* ptr = ptr1;
    mutate_float(&(ptr->x), level+1);
    mutate_float(&(ptr->y), level+1);
    pool_insert("memfuzz_anonymous_struct_2794", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2794  \n"); fflush(stdout);
    #endif
}
void mutate__XDisplay(void* ptr1, int level){return ;}
void mutate__XGC(void* ptr1, int level){return ;}
void mutate__XOC(void* ptr1, int level){return ;}
void mutate__TranslationData(void* ptr1, int level){return ;}
void mutate__XtStateRec(void* ptr1, int level){return ;}
void mutate__XtEventRec(void* ptr1, int level){return ;}
void mutate__XPrivate(void* ptr1, int level){return ;}
void mutate__XrmHashBucketRec(void* ptr1, int level){return ;}
void mutate__XtAppStruct(void* ptr1, int level){return ;}
void mutate_jpeg_decomp_master(void* ptr1, int level){return ;}
void mutate_jpeg_d_main_controller(void* ptr1, int level){return ;}
void mutate_jpeg_d_coef_controller(void* ptr1, int level){return ;}
void mutate_jpeg_d_post_controller(void* ptr1, int level){return ;}
void mutate_jpeg_input_controller(void* ptr1, int level){return ;}
void mutate_jpeg_marker_reader(void* ptr1, int level){return ;}
void mutate_jpeg_entropy_decoder(void* ptr1, int level){return ;}
void mutate_jpeg_inverse_dct(void* ptr1, int level){return ;}
void mutate_jpeg_upsampler(void* ptr1, int level){return ;}
void mutate_jpeg_color_deconverter(void* ptr1, int level){return ;}
void mutate_jpeg_color_quantizer(void* ptr1, int level){return ;}
