#pragma once

struct PerTick {
    const f64 seconds, milliseconds, microseconds, nanoseconds;
    PerTick() = delete;
    explicit PerTick(const f64 tps) :
        seconds(     1          / tps),
        milliseconds(1000       / tps),
        microseconds(1000000    / tps),
        nanoseconds( 1000000000 / tps) {}
};

typedef struct Ticks {
    const PerTick per_tick;
    const u64 per_second;
    Ticks() = delete;
    explicit Ticks(const u64 tps) : per_second(tps), per_tick((f64)tps) {}
} Ticks;

struct Timer {
    f32 delta_time = 0;
    u64 ticks_before = 0,
        ticks_after = 0,
        ticks_diff = 0,
        accumulated_ticks = 0,
        accumulated_frame_count = 0,
        ticks_of_last_report = 0,
        seconds = 0,
        milliseconds = 0,
        microseconds = 0,
        nanoseconds = 0;
    f64 average_frames_per_tick = 0,
        average_ticks_per_frame = 0;
    u16 average_frames_per_second = 0,
        average_milliseconds_per_frame = 0,
        average_microseconds_per_frame = 0,
        average_nanoseconds_per_frame = 0;

    Timer() = delete;
    Ticks *ticks = nullptr;
    explicit Timer(Ticks *tks) : ticks(tks), ticks_before(os::getTicks()), ticks_of_last_report(os::getTicks()) {};
    void accumulate() {
        ticks_diff = ticks_after - ticks_before;
        accumulated_ticks += ticks_diff;
        accumulated_frame_count++;

        seconds      = (u64)(ticks->per_tick.seconds      * (f64)(ticks_diff));
        milliseconds = (u64)(ticks->per_tick.milliseconds * (f64)(ticks_diff));
        microseconds = (u64)(ticks->per_tick.microseconds * (f64)(ticks_diff));
        nanoseconds  = (u64)(ticks->per_tick.nanoseconds  * (f64)(ticks_diff));
    }

    void average() {
        average_frames_per_tick = (f64)accumulated_frame_count / (f64)accumulated_ticks;
        average_ticks_per_frame = (f64)accumulated_ticks / (f64)accumulated_frame_count;
        average_frames_per_second = (u16)(average_frames_per_tick      * (f64)ticks->per_second);
        average_milliseconds_per_frame = (u16)(average_ticks_per_frame * ticks->per_tick.milliseconds);
        average_microseconds_per_frame = (u16)(average_ticks_per_frame * ticks->per_tick.microseconds);
        average_nanoseconds_per_frame = (u16)(average_ticks_per_frame  * ticks->per_tick.nanoseconds);
        accumulated_ticks = accumulated_frame_count = 0;
    }

    INLINE void startFrame() {
        ticks_after = ticks_before;
        ticks_before = os::getTicks();
        ticks_diff = ticks_before - ticks_after;
        delta_time = (f32)((f64)ticks_diff * ticks->per_tick.seconds);
    }

    INLINE void endFrame() {
        ticks_after = os::getTicks();
        accumulate();
        if (accumulated_ticks >= ticks->per_second / 4)
            average();
    }
};

struct Timers {
    Timer update, render, aux;
    Timers() = delete;
    explicit Timers(Ticks *ticks) : update(ticks), render(ticks), aux(ticks) {}
};

struct Time {
    Ticks ticks;
    Timers timers;
    Time() : ticks(os::ticks_per_second), timers(&ticks) {}
};