// pass window reference to renderer
// create draw ghosts, dungeon, etc. functions - private
// merge render functions
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "tile.h"

class Renderer
{
    public:
        Renderer(sf::RenderWindow& window);
        void render(const TileGrid& grid, bool host, int mouseX, int mouseY);
        void renderSetup(const TileGrid& grid, bool host, int mouseX, int mouseY);
        void renderText(std::string& string);
        void drawPlaceGhostText();
        int getTileSize();

    private:
        int tileSize;

        sf::RenderWindow& window;
        
        sf::Texture dungeonTexture;
        sf::Sprite dungeonSprite;
        sf::Sprite dungeonSelectedSprite;
        sf::Sprite dungeonReadySprite;
        sf::Sprite dungeonMouseSprite;
        sf::Texture ghostTexture;
        sf::Sprite ghostSpriteUnknown;
        sf::Sprite ghostSpriteGood;
        sf::Sprite ghostSpriteBad;

        sf::Font font;
        sf::Text text;
};
