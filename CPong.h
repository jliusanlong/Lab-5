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
	
	int frame = 0;
	float FPS;

	double start_tic, freq, elapsed_time;

	bool _button_A;
	int _paddleHeight = 110;
	cv::Point2f _compPaddleTL={0,320 }, _compPaddleBR={20,430 };
	cv::Point2f _playerPaddleTL={ 980,320 }, _playerPaddleBR={ 1000,430 };

	float _ballSize=25;
	float _velocity = 200;
	float _joystick, _prevJoyPos, _joyPos;

	bool _exit_clicked = false, _reset = false; 
};