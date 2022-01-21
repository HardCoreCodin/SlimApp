#pragma once

#define Kilobytes(value) ((value)*1024LL)
#define Megabytes(value) (Kilobytes(value)*1024LL)
#define Gigabytes(value) (Megabytes(value)*1024LL)
#define Terabytes(value) (Gigabytes(value)*1024LL)

#define MEMORY_SIZE Gigabytes(1)
#define MEMORY_BASE Terabytes(2)

struct Memory {
    u8* address = nullptr;
    u64 capacity = 0;
    u64 occupied = 0;

    void init(u8* Address, const u64 Capacity) {
        address = Address;
        capacity = Capacity;
    }
    void* allocate(u64 size) {
        if (!address) return nullptr;
        occupied += size;
        if (occupied > capacity) return nullptr;

        void* current_address = address;
        address += size;
        return current_address;
    }
};