#include "../SlimApp.h"

struct GameApp : public SlimApp {
    struct NavigationKeys { u8 left, right, up, down; };
    struct Player {
        f32 size = 10;
        f32 speed = 80;
        vec2 pos{20, 20};
    };
    struct Game {
        NavigationKeys keys{'A','D', 'W', 'S'};
        NavigationKeys move{false, false, false, false};
        Player *player = nullptr;
        explicit Game(Player *_player) : player(_player) {}
    };

    bool OnReady() override {
        // Get a contiguous block of memory for the game and player:
        if (!initMemory(sizeof(Game) + sizeof(Player))) return false;

        // Allocate memory for the game and player from that memory block:
        void *game_memory = nullptr, *player_memory = nullptr;
        if (!(game_memory = allocateMemory(sizeof(Game)))) return false;
        if (!(player_memory = allocateMemory(sizeof(Player)))) return false;

        // Create the game (and player) using the memory and store it on tha app,
        user_data = new(game_memory)Game{new(player_memory)Player{}};

        return true;
    }

    void OnKeyChanged(u8 key, bool is_pressed) override {
        // Get the Game instance from the app:
        auto &game = *(Game*)user_data;
        auto &keys = game.keys;
        auto &move = game.move;
        if (key == keys.left)  move.left  = is_pressed;
        if (key == keys.right) move.right = is_pressed;
        if (key == keys.up)    move.up    = is_pressed;
        if (key == keys.down)  move.down  = is_pressed;
    }

    void OnWindowRedraw() override {
        // App already has a few timers: Use the update timer to track the
        // time difference since the last time this function was called (delta_time):
        Timer &timer= time.timers.update;
        timer.startFrame();

        // Get the Game and the Player from the app:
        auto &game = *(Game*)user_data;
        auto &player = *game.player;
        auto &move = game.move;
        f32 amount = player.speed * timer.delta_time;

        if (move.left)  player.pos.x -= amount;
        if (move.right) player.pos.x += amount;
        if (move.up)    player.pos.y -= amount;
        if (move.down)  player.pos.y += amount;

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
};

SlimApp* createApp() { return new GameApp(); }