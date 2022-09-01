#define _WINDOWS
#include "Framework.h"
#include "Board.h"
#include "GameOver.h"

#include "string"
#include <filesystem>
#include <numbers>
#include <cmath>
#include <utility>

#include "iostream"


#define PLATFORM_VELOCITY 0.5
#define BALL_VELOCITY 0.5

/* Test Framework realization */
class MyFramework : public Framework {

public:
	int width;
	int height;
	Board* board;
	bool showBoard;

	Sprite* gameOverSprite = NULL;
	Sprite* blueWallSprite = NULL;
	std::vector<Sprite*> platformSprites;
	Sprite* ballSprite = NULL;
	Sprite* cursorSprite = NULL;


	MyFramework(int width, int height) {
		this->width = width;
		this->height = height;
		showBoard = true;
	}

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = this->width;
		height = this->height;
		fullscreen = false;
	}

	virtual bool Init() {
		// load resources
		
		blueWallSprite = createSprite(getResourcePath("01-Breakout-Tiles.png").c_str());
		platformSprites = {
			createSprite(getResourcePath("50-Breakout-Tiles.png").c_str()),
			createSprite(getResourcePath("51-Breakout-Tiles.png").c_str()),
			createSprite(getResourcePath("52-Breakout-Tiles.png").c_str())
		};
		cursorSprite = createSprite(getResourcePath("59-Breakout-Tiles.png").c_str());
		ballSprite = createSprite(getResourcePath("63-Breakout-Tiles.png").c_str());

		board = new Board(width, height, blueWallSprite, platformSprites, cursorSprite, ballSprite);

		gameOverSprite = createSprite(getResourcePath("GameOver.jpg").c_str());

		showCursor(false);
		return true;
	}

	virtual void Close() {

	}

	virtual bool Tick() {

		drawTestBackground();
		if (showBoard)
		{
			board->update();
			board->draw();
			if (board->ball->y + board->ball->height > board->platform->y + board->platform->height)
			{
				showBoard = false;
				delete board->ball;
				delete board->cursor;
				delete board->platform;
				board->units.clear();
			}
		}
		else
		{
			setSpriteSize(gameOverSprite, this->width, this->height);
			drawSprite(gameOverSprite, 0, 0);
		}

		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		//std::cout << x << ":" << y << " -> " << xrelative << ":" << yrelative << std::endl;
		if (showBoard)
			board->cursor->move(x, y);
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		if (showBoard)
			switch (button)
			{
			case FRMouseButton::LEFT:
				if (isReleased) {
					int cursorX = board->cursor->x;
					int cursorY = board->cursor->y;

					int ballX = board->ball->x;
					int ballY = board->ball->y;

					int dx = cursorX - ballX;
					int dy = cursorY - ballY;
					long double len = sqrt(pow(dx, 2) + pow(dy, 2));

					board->ball->setVelosity(BALL_VELOCITY);
					board->ball->setDirection(dx / len, dy / len);
				}
				break;
			case FRMouseButton::RIGHT:
				board->ball->resetVelosity();
				break;
			case FRMouseButton::MIDDLE:
				break;
			case FRMouseButton::COUNT:
				break;
			default:
				break;
			}
	}

	virtual void onKeyPressed(FRKey k) {
		switch (k)
		{
		case FRKey::RIGHT:
			if (showBoard) {
				board->platform->setVelosity(PLATFORM_VELOCITY);
				board->platform->setDirection(1, 0);
			}
			break;
		case FRKey::LEFT:
			if (showBoard) {
				board->platform->setVelosity(PLATFORM_VELOCITY);
				board->platform->setDirection(-1, 0);
			}
			break;
		case FRKey::DOWN:
			if (showBoard == false)
			{
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

	virtual void onKeyReleased(FRKey k) {
		switch (k)
		{
		case FRKey::RIGHT:
			if (showBoard) {
				board->platform->resetVelosity();
			}
			break;
		case FRKey::LEFT:
			if (showBoard) {
				board->platform->resetVelosity();
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


private:
	std::string getResourcePath(std::string resourceName) {
		auto path = std::filesystem::current_path() / "data" / resourceName;
		return path.string();
	}

};

int main(int argc, char* argv[])
{
	// default values
	int width = 800;
	int height = 600;

	// values from command line
	if (argc == 3) {
		// TODO input validation 
		width = std::stoi(argv[1]);
		height = std::stoi(argv[2]);
	}

	return run(new MyFramework(width, height));
}
