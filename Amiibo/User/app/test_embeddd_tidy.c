#include <stdint.h>
#include <stdlib.h>

// 1. 触发 cppcoreguidelines-no-malloc: 嵌入式禁忌 malloc
void test_malloc(void) {
    uint8_t *ptr = (uint8_t *)malloc(10); // 应该警告：禁用动态内存分配
    (void)ptr;
}

// 2. 触发 bugprone-narrowing-conversions: 寄存器读取截断
void test_narrowing(uint16_t reg_val) {
    uint8_t status = reg_val; // 应该警告：隐式类型截断 (16bit -> 8bit)
    (void)status;
}

// 3. 触发 bugprone-easily-swappable-parameters: 相邻同类型参数
void write_register(uint8_t reg_addr, uint8_t reg_val) { // 应该警告：参数容易传反
    (void)reg_addr;
    (void)reg_val;
}

// 4. 触发 clang-analyzer-core.NullDereference: 空指针解引用/野指针
void test_null_ptr(void) {
    uint32_t *gpio_dr = 0;
    *gpio_dr = 0x01; // 应该警告：解引用空指针
}
