#pragma once

#define Kilobytes(value) ((value)*1024LL)
#define Megabytes(value) (Kilobytes(value)*1024LL)
#define Gigabytes(value) (Megabytes(value)*1024LL)
#define Terabytes(value) (Gigabytes(value)*1024LL)

#define MEMORY_SIZE Gigabytes(1)
#define MEMORY_BASE Terabytes(2)

typedef struct Memory {
    u8* address;
    u64 occupied;
} Memory;

void initMemory(Memory *memory, u8* address) {
    memory->address = (u8*)address;
    memory->occupied = 0;
}

void* allocateMemory(Memory *memory, u64 size) {
    if (!memory->address) return null;

    memory->occupied += size;

    void* address = memory->address;
    memory->address += size;
    return address;
}