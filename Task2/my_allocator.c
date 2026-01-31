#include "my_allocator.h"

#define POOL_16_SIZE  100  // 100 блоков по 16 байт
#define POOL_180_SIZE 50   // 50 блоков по 180 байт

typedef union Block16
{
    char data[16];
    union Block16* next;
} Block16;

typedef union Block180
{
    char data[180];
    union Block180* next;
} Block180;


// Массивы памяти
static Block16 pool16[POOL_16_SIZE];
static Block180 pool180[POOL_180_SIZE];

// Головы списков свободных блоков
static Block16* free_head16 = NULL;
static Block180* free_head180 = NULL;

// Состояние аллокатора
static int is_initialized = 0;

/**
 * Инициализация пулов: связываем блоки в цепочку (список).
 * Каждый блок хранит адрес следующего, пока он не занят.
 */
static void init_pools()
{
    // Подготовка маленького пула (16 байт)
    for (int i = 0; i < POOL_16_SIZE - 1; i++)
    {
        pool16[i].next = &pool16[i + 1];
    }
    pool16[POOL_16_SIZE - 1].next = NULL;
    free_head16 = &pool16[0];

    // Подготовка большого пула (180 байт)
    for (int i = 0; i < POOL_180_SIZE - 1; i++)
    {
        pool180[i].next = &pool180[i + 1];
    }
    pool180[POOL_180_SIZE - 1].next = NULL;
    free_head180 = &pool180[0];

    is_initialized = 1;
}

void my_free(void* ptr)
{
    if (ptr == NULL) return;

    // Определяем принадлежность указателя к пулу по его адресу в памяти
    if (ptr >= (void*)&pool16[0] && ptr <= (void*)&pool16[POOL_16_SIZE - 1])
    {
        Block16* block = (Block16*)ptr;
        // Возвращаем блок в начало списка свободных (принцип LIFO - стек)
        block->next = free_head16;
        free_head16 = block;
    }
    else if (ptr >= (void*)&pool180[0] && ptr <= (void*)&pool180[POOL_180_SIZE - 1])
    {
        Block180* block = (Block180*)ptr;
        block->next = free_head180;
        free_head180 = block;
    }
}

void* my_malloc(size_t size)
{

    if (!is_initialized)
    {
        init_pools();
    }

    // Логика выбора пула в зависимости от запрошенного размера
    if (size > 0 && size <= 15)
    {
        if (free_head16 == NULL) return NULL;

        // Забираем первый свободный блок из головы списка
        Block16* block_to_give = free_head16;
        free_head16 = free_head16->next;
        return (void*)block_to_give;
    }
    else if (size > 15 && size <= 180)
    {
        if (free_head180 == NULL) return NULL;

        Block180* block_to_give = free_head180;
        free_head180 = free_head180->next;
        return (void*)block_to_give;
    }
    // Размер не поддерживается
    return NULL;
}
