#include <stdio.h>
#include "my_allocator.h"

int main()
{
    printf("--- Allocator Test ---\n");

    // Тест маленьких блоков
    void* p1 = my_malloc(15);
    void* p2 = my_malloc(15);

    printf("Allocated 15 bytes at: %p\n", p1);
    printf("Allocated 15 bytes at: %p\n", p2);

    if (p1 != NULL && p1 != p2)
    {
        printf("Success: Got two different small blocks.\n");
    }

    // Тест большого блока
    void* p3 = my_malloc(180);
    printf("Allocated 180 bytes at: %p\n", p3);

    // Тест освобождения и повторного выделения
    my_free(p1);
    void* p4 = my_malloc(15);
    printf("After free p1, new allocation at: %p\n", p4);

    if (p1 == p4)
    {
        printf("Success: p1 was reused.\n");
    }

    // Тест неверного размера
    void* p5 = my_malloc(500);
    if (p5 == NULL)
    {
        printf("Success: Correctly rejected 500 bytes.\n");
    }

    return 0;
}
