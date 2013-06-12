#include "state_gameplay.h"

void GameplayState::setup()
{
    winString = "YOU WIN!!! :D";
    loseString = "NEEEEEJ YOU LOST";
}

bool GameplayState::randomiseFirstTurn()
{
    if ((rand() % 100) < 50)
        return true;
    else
        return false;
}

void GameplayState::takeTurn()
{
    //display: "Your turn. Move a ghost."

    //event loop :O
    inputHandler.processEvents();
    while (inputHandler.pollEvent(event))
    {
        if (event.type == windbreeze::Event::CLOSED)
        {
            nextState = "exit";
        }
        else if (event.type == windbreeze::Event::KEYPRESSED)
        {
            if (event.key.code == windbreeze::Keyboard::Q || event.key.code == windbreeze::Keyboard::ESCAPE)
            {
                nextState = "exit";
            }
            if (event.key.code == windbreeze::Keyboard::M)
            {
                checkIfValidMove();
            }
        }
        else if (event.type == windbreeze::Event::MOUSEBUTTONPRESSED)
        {
            if (event.mouseButton.button == windbreeze::Mouse::LEFT)
            {
                mouseClickLeft(event.mouseButton.x, event.mouseButton.y);
            }
        }
    }

}

void GameplayState::waitForTurn()
{
}

void GameplayState::setTileAsSelected(int x, int y)
{
    selected = true;
    selectedX = x;
    selectedY = y;
    selectedTile = tileGrid[y][x];
    renderer.setSelectedTile(x, y);
}

void GameplayState::deselectTile()
{
    selected = false;
    renderer.setSelectedTile(-1, -1);
}

bool GameplayState::surroundingSelectedTile(int x, int y)
{
    return (((x == selectedX + 1 || x == selectedX - 1) && y == selectedY)
        || ((y == selectedY + 1 || y == selectedY - 1) && x == selectedX));
}

void GameplayState::processTurnInfo(Tile& tile)
{
    if (tile.ghostState == GOOD)
    {
        enemyGoodCaptured++;
        std::cout << "yay you captured a good enemy! good antal: " << enemyGoodCaptured << "\n";
    }
    else if (tile.ghostState == BAD)
    {
        enemyBadCaptured++;
        std::cout << "NEEEEEEEEJ you captured a bad enemy! bad antal: " << enemyBadCaptured << "\n";
    }
    tile = selectedTile;
    tileGrid[selectedY][selectedX].playerState = NEITHER;
    tileGrid[selectedY][selectedX].ghostState = NONE;
}

void GameplayState::checkForGameOver()
{
    if (enemyGoodCaptured == 4)
    {
        renderer.renderText(sfWindow, winString);
    }
    else if (enemyBadCaptured == 4)
    {
        renderer.renderText(sfWindow, loseString);
    }
    else
    {
        renderer.render(sfWindow, tileGrid);
    }
}

bool GameplayState::withinGrid(int x, int y)
{
    return ((x <= 5 && x >= 0) && (y <= 5 && y >= 0));
}

void GameplayState::mouseClickLeft(int xPos, int yPos)
{
    int tileSize = renderer.getTileSize();
    int xTile = xPos/tileSize;
    int yTile = yPos/tileSize;

    if (withinGrid(xTile, yTile))
    {
        Tile& clickedTile = tileGrid[yTile][xTile];
        if (selected)
        {
            if (clickedTile.playerState == ONE)
            {
                setTileAsSelected(xTile, yTile);
            }
            else if (surroundingSelectedTile(xTile, yTile))
            {
                suggestMovement(clickedTile);
                processTurnInfo(clickedTile);
                deselectTile();
            }
        }
        else
        {
            if (clickedTile.playerState == ONE)
            {
                setTileAsSelected(xTile, yTile);
            }
        }
    }
}

std::string GameplayState::run()
{
    windbreeze::Event event;
    std::string nextState;

    if (host)
    {
        turn = randomiseFirstTurn();
        //send.TURNinfo();
    }
    //else
        //waitForFirstTurnSignal();
    
    if (turn)
        takeTurn();
    else
        waitForTurn();

    checkForGameOver();
    return nextState;
}
