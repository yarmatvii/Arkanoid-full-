#define _WINDOWS
#include "Framework.h"
#include "Board.h"
#include "UI.h"
#include "Effect.h"

#include <string>
#include <filesystem>
#include <numbers>
#include <cmath>
#include <utility>
#include "wtypes.h"
#include <iostream>

/* Test Framework realization */
class MyFramework : public Framework
{

public:
	int width;
	int height;
	bool fullscreen;
	Board* board;
	UI* ui;
	bool showBoard;

	Sprite* bg = NULL;
	Sprite* gameOverSprite = NULL;
	Sprite* victorySprite = NULL;
	Sprite* blueWallSprite = NULL;
	Sprite* yellowBlockSprite = NULL;
	std::vector<Sprite*> platformSprites;
	Sprite* ballSprite = NULL;
	Sprite* cursorSprite = NULL;
	Sprite* goldBlockSprite = NULL;

	MyFramework(int width, int height, bool fullscreen)
	{
		this->width = width;
		this->height = height;
		this->fullscreen = fullscreen;
		showBoard = true;
	}

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = this->width;
		height = this->height;
		fullscreen = this->fullscreen;
	}

	virtual bool Init()
	{
		// load resources

		bg = createSprite(getResourcePath("bg.jpg").c_str());

		blueWallSprite = createSprite(getResourcePath("01-Breakout-Tiles.png").c_str());
		platformSprites = {
			createSprite(getResourcePath("50-Breakout-Tiles.png").c_str()),
			createSprite(getResourcePath("51-Breakout-Tiles.png").c_str()),
			createSprite(getResourcePath("52-Breakout-Tiles.png").c_str())
		};
		cursorSprite = createSprite(getResourcePath("59-Breakout-Tiles.png").c_str());
		ballSprite = createSprite(getResourcePath("63-Breakout-Tiles.png").c_str());
		yellowBlockSprite = createSprite(getResourcePath("13-Breakout-Tiles.png").c_str());
		goldBlockSprite = createSprite(getResourcePath("25-Breakout-Tiles.png").c_str());

		board = new Board(width, height, blueWallSprite, yellowBlockSprite, goldBlockSprite, platformSprites, cursorSprite, ballSprite);

		ui = new UI(width, height);

		gameOverSprite = createSprite(getResourcePath("GameOver.jpg").c_str());
		victorySprite = createSprite(getResourcePath("Victory.jpg").c_str());

		showCursor(false);
		board->ball->setDirection(0, 1);
		return true;
	}

	virtual void Close()
	{
		destroySprite(ui->zero);
		destroySprite(ui->one);
		destroySprite(ui->two);
		destroySprite(ui->three);
		destroySprite(ui->four);
		destroySprite(ui->five);
		destroySprite(ui->six);
		destroySprite(ui->seven);
		destroySprite(ui->eight);
		destroySprite(ui->nine);

		destroySprite(ui->speedAbility);
		destroySprite(ui->scoreboardStart);
		destroySprite(board->damagedBlock);
		destroySprite(bg);
		destroySprite(gameOverSprite);
		destroySprite(victorySprite);
		destroySprite(goldBlockSprite);
		destroySprite(yellowBlockSprite);
		destroySprite(blueWallSprite);
		destroySprite(ballSprite);
		destroySprite(cursorSprite);
		for (auto sprite : platformSprites)
		{
			destroySprite(sprite);
		}
	}

	virtual bool Tick()
	{
		drawTestBackground();
		showBoard = board->tick(showBoard, gameOverSprite, victorySprite, bg);
		ui->tick(board->score, width, height, showBoard);
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative)
	{
		if (showBoard) board->cursor->move(x, y);
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased)
	{
		if (showBoard)
			switch (button)
			{
			case FRMouseButton::LEFT:
				if (isReleased) {
					board->launchBall();
				}
				break;
			case FRMouseButton::RIGHT:
				if (isReleased) {
					board->addRandomEffect();
				}
				break;
			case FRMouseButton::MIDDLE:
				break;
			case FRMouseButton::COUNT:
				break;
			default:
				break;
			}
	}

	virtual void onKeyPressed(FRKey k)
	{
		switch (k)
		{
		case FRKey::RIGHT:
			if (showBoard)
			{
				board->platform->setDirection(board->platform->getDirectionX() + 1, 0);
			}
			break;
		case FRKey::LEFT:
			if (showBoard)
			{
				board->platform->setDirection(board->platform->getDirectionX() - 1, 0);
			}
			break;
		case FRKey::DOWN:
			if (showBoard == false)
			{
				Close();
				Init();
				showBoard = true;
			}
			break;
		case FRKey::UP:
			break;
		case FRKey::COUNT:
			break;
		default:
			break;
		}
	}

	virtual void onKeyReleased(FRKey k)
	{
		switch (k)
		{
		case FRKey::RIGHT:
			if (showBoard)
			{
				board->platform->setDirection(board->platform->getDirectionX() - 1, 0);
			}
			break;
		case FRKey::LEFT:
			if (showBoard)
			{
				board->platform->setDirection(board->platform->getDirectionX() + 1, 0);
			}
			break;
		case FRKey::DOWN:
			break;
		case FRKey::UP:
			break;
		case FRKey::COUNT:
			break;
		default:
			break;
		}
	}

	virtual const char* GetTitle() override
	{
		return "Arcanoid";
	}

};

int main(int argc, char* argv[])
{
	int width = 800;
	int height = 600;
	int fullscreen = false;

	if (argc == 4 && strcmp(argv[1], "-window") == 0)
	{
		width = std::stoi(argv[2]);
		height = std::stoi(argv[3]);
	}

	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	if (width == desktop.right && height == desktop.bottom) fullscreen = true;

	return run(new MyFramework(width, height, fullscreen));
}
