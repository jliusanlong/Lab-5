#include "stdafx.h"
#include "CPong.h"
#include "cvui.h"


CPong::CPong(int comport, int rows, int cols)
{
	_control.init_com(comport);
	_canvas = cv::Mat::zeros(rows, cols, CV_8UC3);

	cvui::init("Pong");

	//cv::namedWindow("Pong", cv::WINDOW_AUTOSIZE);
}

CPong::~CPong()
{
}

void CPong::gpio()
{
	_joystick = _control.get_analog(1, 26);

	_button_A = _control.get_button(33);

	
}

void CPong::update()
{ 
	_joystick -= 50;
	_joystick *= -1;

	//Stabalize at origin
	
	if (_joystick > 2 || _joystick < -2)
	{
		_playerPaddleTL.y += _joystick / 5;
		_playerPaddleBR.y += _joystick / 5;
	}
	/*
	if (_playerPaddleTL.y <= 0)
	{
		_playerPaddleTL = { 980,0 };
		_playerPaddleBR = { 1000,110 };
	}

	if(_playerPaddleBR.y >= 750)
	{
		_playerPaddleTL = { 980,640 };
		_playerPaddleBR = { 1000,750 };
	}*/
}

void CPong::draw()
{
	_canvas.setTo(cv::Scalar(0, 0, 0));

	cvui::window(_canvas, 10, 10, 250, 210, "Pong");


	cvui::printf(_canvas, 20, 40, "Ballsize = %.2f", _ballSize);
	cvui::trackbar(_canvas, 20, 55, 220, &_ballSize, (float)5, (float)100);
	
	cvui::printf(_canvas, 20, 110, "Velocity = %.2f", _velocity);
	cvui::trackbar(_canvas, 20, 125, 220, &_velocity, (float)100, (float)400);

	_exit_clicked = cvui::button(_canvas, 20, 180, "EXIT");
	_reset = cvui::button(_canvas, 90, 180, "RESET");
	if (_reset)
	{
		_canvas.setTo(cv::Scalar(0, 0, 0));  // Clear the canvas
	}

	
	cv::circle(_canvas, cv::Point(500, 375), _ballSize, cv::Scalar(255, 255, 255), cv::FILLED);

	cv::rectangle(_canvas, _compPaddleTL, _compPaddleBR, cv::Scalar(255, 255, 255), cv::FILLED);
	cv::rectangle(_canvas, _playerPaddleTL, _playerPaddleBR, cv::Scalar(255, 255, 255), cv::FILLED);

	cv::rectangle(_canvas, _compPaddleTL, _compPaddleBR, cv::Scalar(0, 255, 0), cv::FILLED);

	cvui::update();

	cv::imshow("Pong", _canvas);
}

void CPong::run()
{
	while (true)
	{
		CPong::gpio();
		CPong::update();
		CPong::draw();

		int key = cv::waitKey(1) & 0xFF;
		if (key == 'q' || key == 'Q' || _exit_clicked)
		{
			cv::destroyWindow("Pong");
			break;
		}
	}
}