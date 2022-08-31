#define _WINDOWS
#include "Framework.h"
#include "Board.h"

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

	Sprite* blueWallSprite = NULL;
	std::vector<Sprite*> platformSprites;
	Sprite* ballSprite = NULL;
	Sprite* coursorSprite = NULL;


	MyFramework(int width, int height) {
		this->width = width;
		this->height = height;
		board = new Board(width, height);
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
		ballSprite = createSprite(getResourcePath("63-Breakout-Tiles.png").c_str());
		coursorSprite = createSprite(getResourcePath("59-Breakout-Tiles.png").c_str());

		board->addUnit(new Unit(blueWallSprite, 0, 200, 150, 50));
		board->addUnit(new Unit(blueWallSprite, 150, 0, 150, 50));
		board->addUnit(new Unit(blueWallSprite, 300, 0, 150, 50));
		board->addUnit(new Unit(blueWallSprite, 450, 0, 150, 50));
		board->addUnit(new Unit(blueWallSprite, 600, 0, 150, 50));
		board->addUnit(new Unit(blueWallSprite, 750, 0, 50, 50));

		board->addPlatform(new PratformUnit(platformSprites, board->width / 2, board->height - 100, 160, 50));
		board->addBall(new DynamicUnit(ballSprite, board->width / 2, board->height - 160, 32, 32));
		board->addCoursor(new Unit(coursorSprite, -50, -50, 16, 16));


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
				showBoard = false;
		}

		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		//std::cout << x << ":" << y << " -> " << xrelative << ":" << yrelative << std::endl;
		board->coursor->move(x, y);
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		switch (button)
		{
		case FRMouseButton::LEFT:
			if (isReleased) {
				int coursorX = board->coursor->x;
				int coursorY = board->coursor->y;

				int ballX = board->ball->x;
				int ballY = board->ball->y;

				int dx = coursorX - ballX;
				int dy = coursorY - ballY;
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
			board->platform->setVelosity(PLATFORM_VELOCITY);
			board->platform->setDirection(1, 0);
			break;
		case FRKey::LEFT:
			board->platform->setVelosity(PLATFORM_VELOCITY);
			board->platform->setDirection(-1, 0);
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

	virtual void onKeyReleased(FRKey k) {
		switch (k)
		{
		case FRKey::RIGHT:
			board->platform->resetVelosity();
			break;
		case FRKey::LEFT:
			board->platform->resetVelosity();
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
