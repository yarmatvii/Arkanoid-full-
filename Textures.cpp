#include "Textures.h"
#include "lib.h"

Textures::Textures() {
	this->_blueBlock = NULL;
	this->_violetBlock = NULL;
	this->_lightBlueBlock = NULL;
	this->_ball = NULL;
	this->_cursor = NULL;
	this->_platform = {};
	this->_restart = NULL;
	this->_background = NULL;
	this->_savingwall = NULL;
	this->_accelerationArea = NULL;
	this->_decelerationArea = NULL;
	this->_zero = NULL;
	this->_one = NULL;
	this->_two = NULL;
	this->_three = NULL;
	this->_four = NULL;
	this->_five = NULL;
	this->_six = NULL;
	this->_seven = NULL;
	this->_eight = NULL;
	this->_nine = NULL;
	this->_heart = NULL;
}


Sprite* Textures::blueBlock(){
	if (this->_blueBlock == NULL) {
		this->_blueBlock = createSprite(getResourcePath("blueblock.png").c_str());
	}
	return this->_blueBlock;
};

Sprite* Textures::violetBlock() {
	if (this->_violetBlock == NULL) {
		this->_violetBlock = createSprite(getResourcePath("violetblock.png").c_str());
	}
	return this->_violetBlock;
};

Sprite* Textures::lightBlueBlock() {
	if (this->_lightBlueBlock == NULL) {
		this->_lightBlueBlock = createSprite(getResourcePath("lightblueblock.png").c_str());
	}
	return this->_lightBlueBlock;
};

Sprite* Textures::ball() {
	if (this->_ball == NULL) {
		this->_ball = createSprite(getResourcePath("ball.png").c_str());
	}
	return this->_ball;
};

Sprite* Textures::cursor() {
	if (this->_cursor == NULL) {
		this->_cursor = createSprite(getResourcePath("cursor.png").c_str());
	}
	return this->_cursor;
};

std::vector<Sprite*> Textures::platform() {
	if (this->_platform.size() == 0) {
		this->_platform.push_back(createSprite(getResourcePath("platform1.png").c_str()));
		this->_platform.push_back(createSprite(getResourcePath("platform2.png").c_str()));
		this->_platform.push_back(createSprite(getResourcePath("platform3.png").c_str()));
	}
	return this->_platform;
};

Sprite* Textures::restart() {
	if (this->_restart == NULL) {
		this->_restart = createSprite(getResourcePath("restart.png").c_str());
	}
	return this->_restart;
};

Sprite* Textures::background() {
	if (this->_background == NULL) {
		this->_background = createSprite(getResourcePath("background.jpg").c_str());
	}
	return this->_background;
};

Sprite* Textures::savingwall() {
	if (this->_savingwall == NULL) {
		this->_savingwall = createSprite(getResourcePath("savingwall.png").c_str());
	}
	return this->_savingwall;
}

Sprite* Textures::accelerationArea() {
	if (this->_accelerationArea == NULL) {
		this->_accelerationArea = createSprite(getResourcePath("acc.png").c_str());
	}
	return this->_accelerationArea;
};

Sprite* Textures::decelerationArea() {
	if (this->_decelerationArea == NULL) {
		this->_decelerationArea = createSprite(getResourcePath("dec.png").c_str());
	}
	return this->_decelerationArea;
};

Sprite* Textures::zero() {
	if (this->_zero == NULL) {
		this->_zero = createSprite(getResourcePath("0.png").c_str());
	}
	return this->_zero;
};

Sprite* Textures::one() {
	if (this->_one == NULL) {
		this->_one = createSprite(getResourcePath("1.png").c_str());
	}
	return this->_one;
};

Sprite* Textures::two() {
	if (this->_two == NULL) {
		this->_two = createSprite(getResourcePath("2.png").c_str());
	}
	return this->_two;
};

Sprite* Textures::three() {
	if (this->_three == NULL) {
		this->_three = createSprite(getResourcePath("3.png").c_str());
	}
	return this->_three;
};

Sprite* Textures::four() {
	if (this->_four == NULL) {
		this->_four = createSprite(getResourcePath("4.png").c_str());
	}
	return this->_four;
};

Sprite* Textures::five() {
	if (this->_five == NULL) {
		this->_five = createSprite(getResourcePath("5.png").c_str());
	}
	return this->_five;
};

Sprite* Textures::six() {
	if (this->_six == NULL) {
		this->_six = createSprite(getResourcePath("6.png").c_str());
	}
	return this->_six;
};

Sprite* Textures::seven() {
	if (this->_seven == NULL) {
		this->_seven = createSprite(getResourcePath("7.png").c_str());
	}
	return this->_seven;
};

Sprite* Textures::eight() {
	if (this->_eight == NULL) {
		this->_eight = createSprite(getResourcePath("8.png").c_str());
	}
	return this->_eight;
};

Sprite* Textures::nine() {
	if (this->_nine == NULL) {
		this->_nine = createSprite(getResourcePath("9.png").c_str());
	}
	return this->_nine;
};

Sprite* Textures::heart() {
	if (this->_heart == NULL) {
		this->_heart = createSprite(getResourcePath("heart.png").c_str());
	}
	return this->_heart;
};
