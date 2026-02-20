#pragma once

#include "CBase4618.h"	

class CPong : public CBase4618
{
public:
	CPong(int comport, int rows, int cols);
	~CPong();


	void run();
	void gpio();
	void update();
	void draw();

private:
	bool _button_A;

	cv::Point2i _compPaddleTL={0,430 }, _compPaddleBR={20,320 };
	cv::Point2i _playerPaddleTL={ 980,430 }, _playerPaddleBR={ 1000,320 };

	float _ballSize=25;
	float _velocity = 200;
	float _joystick, _prevJoyPos, _joyPos;

	bool _exit_clicked = false, _reset = false; 
};