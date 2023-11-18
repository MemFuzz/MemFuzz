#include "memfuzz_pool.h"

// Store struct and its pointers. map(char* -> map(void*-> void*))
static GHashTable *pool;

// Store which address is visited. map(void* -> void*)
static GHashTable *dup;

int dup_init()
{
    dup = g_hash_table_new(g_direct_hash, g_direct_equal);
    if(dup == NULL)
    {
        printf("dup init failed\n");
        return 1;
    }
    return 0;
}

void dup_insert(void* addr)
{
    if(dup == NULL)
        dup_init();
    g_hash_table_insert(dup, addr, addr);
}

int dup_is_in(void* addr)
{
    if(dup == NULL)
        dup_init();
    return g_hash_table_lookup(dup, addr) ? 1 : 0;
}

void dup_destroy()
{
    g_hash_table_destroy(dup);
    dup = NULL;
}

void dup_print_info()
{
    printf("Address in duplication table:\n");
    if(dup == NULL)
        return ;
    g_hash_table_foreach(dup, helper_print_pointer , NULL);
    printf("\n");
}

int pool_init_with_names(char** names, int len)
{
    pool = g_hash_table_new(g_str_hash, g_str_equal);
    if(pool == NULL)
    {
        printf("obj pool init failed\n");
        return 1;
    }
    for(int i = 0; i < len; i++)
    {
        GHashTable *set = g_hash_table_new(g_direct_hash, g_direct_equal);
        if(set == NULL)
        {
            printf("obj pool init failed\n");
            return 2;
        }
        g_hash_table_insert(pool, strdup(names[i]), set);
    }
    return 0;
}

int pool_init()
{
    pool = g_hash_table_new(g_str_hash, g_str_equal);
    if(pool == NULL)
    {
        printf("obj pool init failed\n");
        return 1;
    }
    return 0;
}

void pool_insert(char *name, void* val)
{
    if(pool == NULL)
        pool_init();
    GHashTable *set = g_hash_table_lookup(pool, name);
    if(set == NULL)
    {
        set = g_hash_table_new(g_direct_hash, g_direct_equal);
        g_hash_table_insert(pool, strdup(name), set);
    }
    g_hash_table_insert(set, val, val);
}

static void helper_print_pointer(gpointer key, gpointer value, gpointer user_data) {
    printf("%p ", key);
}

static void helper_print_name(gpointer key, gpointer value, gpointer user_data) {
    char* name = (char*)key;
    GHashTable *set = (GHashTable*) value;
    printf("name: %s\nvalues:", name);
    g_hash_table_foreach(set, helper_print_pointer, NULL);
    printf("\n");
}

void pool_print_info()
{
    if(pool)
        g_hash_table_foreach(pool, helper_print_name, NULL);
}

int pool_get_size(char* name)
{
    if(pool == NULL)
        return 0;
    GHashTable* set = g_hash_table_lookup(pool, name);
    if(set == NULL)
        return 0;
    guint size = g_hash_table_size(set);
    return size;
}

struct fetch_tmp{
    void** arr;
    int num;
};

static void helper_fetch_value(gpointer key, gpointer value, gpointer user_data)
{
    struct fetch_tmp *tmp = (struct fetch_tmp*)user_data;
    tmp->arr[tmp->num] = key;
    tmp->num += 1;
}

// The caller takes the ownership of the return value
void** pool_get_values(char* name, int *len)
{
    if(pool == NULL)
        return NULL;
    *len = pool_get_size(name);
    if(*len == 0)
        return NULL;
    GHashTable* set = g_hash_table_lookup(pool, name);
    struct fetch_tmp tmp;
    void** ret = malloc(sizeof(void*) * (*len));
    tmp.arr = ret;
    tmp.num = 0;
    g_hash_table_foreach(set, helper_fetch_value, &tmp);
    return ret;
}

static void helper_destroy(gpointer key, gpointer value, gpointer user_data)
{
    GHashTable* set = (GHashTable*)value;
    char* name = (char*)key;
    g_hash_table_destroy(set);
    free(name);
}

void pool_destroy()
{
    if(pool)
    {
        g_hash_table_foreach(pool, helper_destroy, NULL);
        g_hash_table_destroy(pool);
        pool = NULL;
    }
}

// int main()
// {
//     char *names[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
//     pool_init();
//     for(int i = 0; i < 10; i++)
//     {
//         pool_insert(names[i], (void*)(i*8));
//     }
//     pool_insert("1", 0);
//     pool_print_info();
//     int len = 0;
//     void** arr = pool_get_values("1", &len);
//     for(int i = 0; i < len; i++)
//     {
//         printf("%p\n", arr[i]);
//     }
//     pool_destroy();
//     dup_init();
//     dup_insert(120);
//     dup_insert(100);
//     dup_print_info();
//     return 0;
// }