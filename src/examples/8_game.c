#include "../app.h"
#include "../shapes.h"

typedef struct NavigationKeys { u8 left, right, up, down; } NavigationKeys;
typedef struct Player {
    f32 size, speed;
    vec2 pos;
} Player;
typedef struct Game {
    Player player;
    NavigationKeys keys, move;
} Game;

void drawPlayer() {
    // App already has a few timers:
    // Use the update timer to track the time difference since the last time this function was called (delta_time):
    startFrameTimer(&app->time.timers.update);

    // Get the Game instance from the app:
    Game *game = (Game*)app->user_data;
    f32 amount = game->player.speed * app->time.timers.update.delta_time;

    if (game->move.left)  game->player.pos.x -= amount;
    if (game->move.right) game->player.pos.x += amount;
    if (game->move.up)    game->player.pos.y -= amount;
    if (game->move.down)  game->player.pos.y += amount;

    Rect rect;
    rect.min.x = (i16)(game->player.pos.x - game->player.size);
    rect.max.x = (i16)(game->player.pos.x + game->player.size);
    rect.min.y = (i16)(game->player.pos.y - game->player.size);
    rect.max.y = (i16)(game->player.pos.y + game->player.size);

    fillPixelGrid(&app->window_content, Color(Black));
    fillRect(     &app->window_content, Color(Blue),  &rect);

    endFrameTimer(&app->time.timers.update);
}

void movePlayer(u8 key, bool pressed) {
    // Get the Game instance from the app:
    Game *game = (Game*)app->user_data;

    if (key == game->keys.left)  game->move.left  = pressed;
    if (key == game->keys.right) game->move.right = pressed;
    if (key == game->keys.up)    game->move.up    = pressed;
    if (key == game->keys.down)  game->move.down  = pressed;
}

void initApp(Defaults *defaults) {
    // Tell the app what to do whenever it needs to redraw the window or a keyboard-key was pressed or released:
    app->on.windowRedraw = drawPlayer;
    app->on.keyChanged   = movePlayer;

    // Get a contiguous block of memory from the OS for use as a linear allocator (a.k.: Arena):
    if (!app->initMemory(sizeof(Game)))
        return; // App will terminate if this failed

    // Allocate memory for the Game using the arena allocator and store it's pointer on the app:
    app->user_data = app->allocateMemory(sizeof(Game));
    if (!app->user_data)
        return; // App will terminate if this failed

    // Use the allocated memory as a Game instance:
    Game *game = (Game*)app->user_data;

    // Set custom key-binding for the player navigation:
    game->keys.up    = 'W';
    game->keys.left  = 'A';
    game->keys.down  = 'S';
    game->keys.right = 'D';

    // Initialize Player:
    game->player.speed = 80;
    game->player.size  = 10;
    game->player.pos.x = 20;
    game->player.pos.y = 20;

    // Initialize navigation state:
    game->move.left  = false;
    game->move.right = false;
    game->move.up    = false;
    game->move.down  = false;
}
