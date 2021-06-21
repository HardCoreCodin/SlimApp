#include "../app.h"
#include "../shapes.h"
// Or using the single-header file:
//#include "../SlimApp.h"

typedef struct NavigationKeys { u8 left, right, up, down; } NavigationKeys;
typedef struct Player { f32 size, speed; vec2 pos;} Player;
typedef struct Game { Player *player; NavigationKeys keys, move; } Game;

void drawPlayer() {
    // App already has a few timers:
    // Use the update timer to track the time difference since the last time this function was called (delta_time):
    startFrameTimer(&app->time.timers.update);

    // Get the Game instance and it's player from the app:
    Game *game = (Game*)app->user_data;
    Player *player = game->player;
    f32 amount = player->speed * app->time.timers.update.delta_time;

    if (game->move.left)  player->pos.x -= amount;
    if (game->move.right) player->pos.x += amount;
    if (game->move.up)    player->pos.y -= amount;
    if (game->move.down)  player->pos.y += amount;

    Rect rect;
    rect.min.x = (i16)(player->pos.x - player->size);
    rect.max.x = (i16)(player->pos.x + player->size);
    rect.min.y = (i16)(player->pos.y - player->size);
    rect.max.y = (i16)(player->pos.y + player->size);

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
    app->on.windowRedraw = drawPlayer;
    app->on.keyChanged   = movePlayer;

    // Note: All memory related failures set 'app->is_running' to
    // 'false' which would exit the application on the next frame.

    // Get a contiguous block of memory from the platform:
    if (!initAppMemory(sizeof(Game) + sizeof(Player))) return;

    // Allocate memory for the game and store it on the app:
    Game *game = allocateAppMemory(sizeof(Game));
    if (game) app->user_data = game;
    else return;

    // Allocate memory for the player store it on the game:
    Player *player = allocateAppMemory(sizeof(Player));
    if (player) game->player = player;
    else return;

    // Initialize Player:
    player->speed = 80;
    player->size  = 10;
    player->pos.x = 20;
    player->pos.y = 20;

    // Set custom key-binding for the player navigation:
    game->keys.up    = 'W';
    game->keys.left  = 'A';
    game->keys.down  = 'S';
    game->keys.right = 'D';

    // Initialize navigation state:
    game->move.left  = false;
    game->move.right = false;
    game->move.up    = false;
    game->move.down  = false;
}
