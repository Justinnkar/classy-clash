#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

int main()
{
    const int windowWidth = {384};
    const int windowHeight = {384};
    InitWindow(windowWidth, windowHeight, "Classy Clash");

    // Map textures
    Texture2D map = LoadTexture("textures/nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos = {0.0, 0.0};
    const float mapScale = 4.0f;

    // Character
    Character knight{windowWidth, windowHeight};

    Prop props[2]{
        Prop{Vector2{600.0f, 300.0f}, LoadTexture("textures/nature_tileset/Rock.png")},
        Prop{Vector2{400.0f, 500.0f}, LoadTexture("textures/nature_tileset/Log.png")}
    };

    Enemy goblin{
        Vector2{},
        LoadTexture("textures/characters/goblin_idle_spritesheet.png"),
        LoadTexture("textures/characters/goblin_run_spritesheet.png")
        };
    goblin.setTarget(&knight);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getworldPos(), -1.0f);

        // draw the map
        DrawTextureEx(map, mapPos, 0, mapScale, WHITE);

        // draw the props
        for (auto prop : props)
        {
            prop.Render(knight.getworldPos());
        }

        knight.tick(GetFrameTime());

        // check map bounds
        if (knight.getworldPos().x < 0.0f
            || knight.getworldPos().y < 0.0f
            || knight.getworldPos().x + windowWidth > map.width * mapScale
            || knight.getworldPos().y + windowHeight > map.height * mapScale)
            {
                knight.undoMovement();
            }
        
        // check prop collision
        for (auto prop : props)
        {
            if (CheckCollisionRecs(knight.getCollisionRec(), prop.getCollisionRec(knight.getworldPos())))
            {
                knight.undoMovement();
            }
        }

        goblin.tick(GetFrameTime());

        EndDrawing();
    }
    UnloadTexture(map);

    CloseWindow();
}
