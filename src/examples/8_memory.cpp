#include "../SlimApp.h"

struct NavigationKeys { u8 left, right, up, down; };
struct Player { f32 size = 0, speed = 0; vec2 pos;};
struct Game { Player *player; NavigationKeys keys, move; };

void drawPlayer() {
    // App already has a few timers:
    // Use the update timer to track the time difference since the last time this function was called (delta_time):
    Timer &timer = app->time.timers.update;
    timer.startFrame();

    // Get the Game instance and it's player from the app:
    Game &game = *(Game*)app->user_data;
    Player &player = *game.player;
    f32 amount = player.speed * timer.delta_time;

    if (game.move.left)  player.pos.x -= amount;
    if (game.move.right) player.pos.x += amount;
    if (game.move.up)    player.pos.y -= amount;
    if (game.move.down)  player.pos.y += amount;

    Rect rect;
    rect.min.x = (i16)(player.pos.x - player.size);
    rect.max.x = (i16)(player.pos.x + player.size);
    rect.min.y = (i16)(player.pos.y - player.size);
    rect.max.y = (i16)(player.pos.y + player.size);
    PixelGrid &canvas = app->window_content;
    canvas.fill(Color(Black));
    canvas.fillRect(Color(Blue), rect);

    timer.endFrame();
}

void movePlayer(u8 key, bool pressed) {
    // Get the Game instance from the app:
    Game *game = (Game*)app->user_data;

    if (key == game->keys.left)  game->move.left  = pressed;
    if (key == game->keys.right) game->move.right = pressed;
    if (key == game->keys.up)    game->move.up    = pressed;
    if (key == game->keys.down)  game->move.down  = pressed;
}

void App::init(Defaults *defaults) {
    on.windowRedraw = drawPlayer;
    on.keyChanged   = movePlayer;

    // Note: All memory related failures set 'is_running' to
    // 'false' which would exit the application on the next frame.

    // Get a contiguous block of memory from the platform:
    if (!initMemory(sizeof(Game) + sizeof(Player))) return;

    // Allocate memory for the game and store it on the app:
    Game *game = (Game*)allocateMemory(sizeof(Game));
    if (game) user_data = game;
    else return;

    // Allocate memory for the player store it on the game:
    auto player = (Player*)allocateMemory(sizeof(Player));
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
