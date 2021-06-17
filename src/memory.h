#pragma once

#define Kilobytes(value) ((value)*1024LL)
#define Megabytes(value) (Kilobytes(value)*1024LL)
#define Gigabytes(value) (Megabytes(value)*1024LL)
#define Terabytes(value) (Gigabytes(value)*1024LL)

#define MEMORY_SIZE Gigabytes(1)
#define MEMORY_BASE Terabytes(2)

typedef struct ArenaAllocator {
    u8* address;
    u64 occupied;
} ArenaAllocator;

void initArenaAllocator(ArenaAllocator *arena_allocator, u8* memory) {
    arena_allocator->address = (u8*)memory;
    arena_allocator->occupied = 0;
}

void* allocateMemory(ArenaAllocator *memory, u64 size) {
    if (!memory->address) return null;

    memory->occupied += size;

    void* address = memory->address;
    memory->address += size;
    return address;
}