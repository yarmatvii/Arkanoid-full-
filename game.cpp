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

	Sprite* blueWallSprite = NULL;
	std::vector<Sprite*> platformSprites;
	Sprite* ballSprite = NULL;
	Sprite* coursorSprite = NULL;


	MyFramework(int width, int height) {
		this->width = width;
		this->height = height;
		board = new Board(width, height);
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

		/*board->addUnit(new Unit(blueWallSprite, 0, 0, 150, 50));
		board->addUnit(new Unit(blueWallSprite, 150, 0, 150, 50));
		board->addUnit(new Unit(blueWallSprite, 300, 0, 150, 50));
		board->addUnit(new Unit(blueWallSprite, 450, 0, 150, 50));
		board->addUnit(new Unit(blueWallSprite, 600, 0, 150, 50));
		board->addUnit(new Unit(blueWallSprite, 750, 0, 50, 50));*/

		board->addPlatform(new PratformUnit(platformSprites, board->width/2, board->height - 100, 160, 50));
		board->addBall(new DynamicUnit(ballSprite, board->width / 2, board->height - 160, 32, 32));
		board->addCoursor(new Unit(coursorSprite, -50, -50, 16, 16));

		showCursor(false);
		return true;
	}

	virtual void Close() {

	}

	virtual bool Tick() {
		drawTestBackground();
		board->update();
		board->draw();
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		//std::cout << x << ":" << y << " -> " << xrelative << ":" << yrelative << std::endl;
		board->coursor->move(x, y);
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		if (button == FRMouseButton::LEFT) {
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
		}
		else if (button == FRMouseButton::RIGHT) {
			board->ball->resetVelosity();
		}
		else if (button == FRMouseButton::MIDDLE) {

		}
		else if (button == FRMouseButton::COUNT) {

		}
	}

	virtual void onKeyPressed(FRKey k) {
		if (k == FRKey::LEFT) {
			board->platform->setVelosity(PLATFORM_VELOCITY);
			board->platform->setDirection(-1, 0);
		}
		else if (k == FRKey::RIGHT) {
			board->platform->setVelosity(PLATFORM_VELOCITY);
			board->platform->setDirection(1, 0);
		}
		else if (k == FRKey::UP) {

		}
		else if (k == FRKey::DOWN) {

		}
	}

	virtual void onKeyReleased(FRKey k) {
		if (k == FRKey::LEFT) {
			board->platform->resetVelosity();
		}
		else if (k == FRKey::RIGHT) {
			board->platform->resetVelosity();
		}
		else if (k == FRKey::UP) {

		}
		else if (k == FRKey::DOWN) {

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
