#pragma once

#define Kilobytes(value) ((value)*1024LL)
#define Megabytes(value) (Kilobytes(value)*1024LL)
#define Gigabytes(value) (Megabytes(value)*1024LL)
#define Terabytes(value) (Gigabytes(value)*1024LL)

#define MEMORY_SIZE Gigabytes(1)
#define MEMORY_BASE Terabytes(2)

struct Memory {
    u8* address;
    u64 capacity, occupied;

    Memory(u8* address, const u64 capacity) : address{address}, capacity{capacity}, occupied{0} {}

    void* allocate(u64 size) {
        if (!address) return nullptr;
        occupied += size;
        if (occupied > capacity) return nullptr;

        void* current_address = address;
        address += size;
        return current_address;
    }
};