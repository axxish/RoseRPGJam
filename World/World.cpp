#include "World.h"

World::World(){

}

void World::Init(uint16_t tileSize, uint16_t worldWidth, uint16_t worldHeight) 
{

    p_width = worldWidth;
    p_height = worldHeight;

    p_worldTileSet = TileSet("resources/maptiles.png", tileSize);
    p_worldTileSet.addTileType("air", {1, 7, 1, 1}, false);
    p_worldTileSet.addTileType("floor", {3, 3, 1, 1}, false);
    p_worldTileSet.addTileType("wall", {1, 1, 1, 1}, true);

    p_entSpriteSheet = new SpriteSheet("resources/creatures.png", tileSize);
   
    p_entSpriteSheet->AddSprite("hero", {0, 0, 1, 1});
    p_entSpriteSheet->AddSprite("rat", {1, 1, 1, 1});

    p_currentLevel = Tilemap(worldWidth, worldHeight);
    p_currentLevel.tiles = testWorld;


    Entity player("player", "hero", 100, 1, 1, this);
    Entities.push_back(player);

    Entities.push_back(Entity("Rat", "rat", 100, 2, 3, this));

    
}

TileSet* World::GetTileSet(){
    return &p_worldTileSet;
}

Tilemap* World::GetTilemap(){
    return &p_currentLevel;
}


void World::DrawTilemap(GameWindow &renderer)
{
    std::vector<TileType> types = p_worldTileSet.getTileTypes();
    std::vector<uint16_t> tiles = p_currentLevel.tiles;

    int width = p_currentLevel.getWidth();
    int height = p_currentLevel.getHeight();
    int y = 0;

    for (int i = 0, x = 0; i < tiles.size(); i++, x++)
    {
        // if the iterator is greater than the width we go to next line
        if (x >= width)
        {
            y++;
            x = 0;
        }
        renderer.DrawSprite(p_worldTileSet.getSpriteSheet(), types[tiles[i]].getTextureName(), x, y);
    }
}

void World::DrawEntities(GameWindow &renderer){
    for(Entity i : Entities){
        renderer.DrawSprite(*p_entSpriteSheet, i.SpriteName, i.X, i.Y);
    }
}



void World::OnRender(GameWindow& renderer){
    DrawTilemap(renderer);
    DrawEntities(renderer);

}

void World::OnUpdate(){
    if(IsKeyPressed(KEY_W)){
        Entities[0].Move(0, -1);
        Camera.target = {(float)Entities[0].X * 16, (float)Entities[0].Y * 16};
        
    }
    if(IsKeyPressed(KEY_S)){
        Entities[0].Move(0, 1);
        Camera.target = {(float)Entities[0].X * 16, (float)Entities[0].Y * 16};
    }

    if(IsKeyPressed(KEY_A)){
        Entities[0].Move(-1, 0);
        Camera.target = {(float)Entities[0].X * 16, (float)Entities[0].Y * 16};
    }
    if(IsKeyPressed(KEY_D)){
        Entities[0].Move(1, 0);
        Camera.target = {(float)Entities[0].X * 16, (float)Entities[0].Y * 16};
    }
}
