#define _WINDOWS

#include <iostream>
#include <string>
#include <filesystem>
#include <numbers>
#include <cmath>
#include <utility>
#include <wtypes.h>

#include "Framework.h"
#include "Board.h"
#include "Effect.h"


/* Test Framework realization */
class MyFramework : public Framework {

public:
	int width;
	int height;
	bool fullscreen;
	Board* board;
	bool showHUD;

	MyFramework(int width, int height, bool fullscreen) {
		this->width = width;
		this->height = height;
		this->fullscreen = fullscreen;
		this->showHUD = false;
	}

	virtual void PreInit(int& width, int& height, bool& fullscreen) {
		width = this->width;
		height = this->height;
		fullscreen = this->fullscreen;
	}

	virtual bool Init() {
		this->board = new Board(width, height);
		showCursor(false);
		return true;
	}

	virtual void Close() {
		delete this->board;

	}

	virtual bool Tick() {
		this->showHUD = board->tick();
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		if (this->showHUD == false) {
			board->cursor->move(x, y);
		};
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		if (this->showHUD == false) {
			switch (button) {
			case FRMouseButton::LEFT:
				if (isReleased) {
					if (board->ball->velocity() == 0) {
						board->launchBall();
					}
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

	}

	virtual void onKeyPressed(FRKey k) {
		switch (k) {
		case FRKey::RIGHT:
			if (this->showHUD == false) {
				board->platform->direction(board->platform->directionX() + 1, 0);
			}
			break;
		case FRKey::LEFT:
			if (this->showHUD == false) {
				board->platform->direction(board->platform->directionX() - 1, 0);
			}
			break;
		case FRKey::DOWN:
			break;
		case FRKey::UP:
			if (this->showHUD == true) {
				this->board->reset();
				this->showHUD = false;
			}
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
			if (this->showHUD == false) {
				board->platform->direction(board->platform->directionX() - 1, 0);
			}
			break;
		case FRKey::LEFT:
			if (this->showHUD == false) {
				board->platform->direction(board->platform->directionX() + 1, 0);
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

	virtual const char* GetTitle() override {
		return "Arcanoid";
	}
};

int main(int argc, char* argv[]) {
	int width = 1280;
	int height = 720;
	int fullscreen = false;

	if (argc == 4 && strcmp(argv[1], "-window") == 0) {
		width = std::stoi(argv[2]);
		height = std::stoi(argv[3]);
	}

	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	if (width == desktop.right && height == desktop.bottom) {
		fullscreen = true;
	}

	return run(new MyFramework(width, height, fullscreen));
}
