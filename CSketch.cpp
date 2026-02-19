#include "stdafx.h"
#include "CSketch.h"
#include "cvui.h"

CSketch::CSketch(int comport, int rows, int cols)
{
	_control.init_com(comport);
	_canvas = cv::Mat::zeros(rows, cols, CV_8UC3);

	_position = cv::Point(375, 375);        // x = cols/2, y = rows/2
	_previousPosition = cv::Point(375, 375);

	cvui::init("Etch-A-Sketch");
	cv::namedWindow("Etch-A-Sketch", cv::WINDOW_AUTOSIZE);

	for (int i = 0; i <= (_colors.size()-1); i++)
	{
		_control.set_data(0, _LED_colors[i], 0);
	}

	_control.set_data(0, _LED_colors[_colorIndex], 1);	
}
	
CSketch::~CSketch()
{
}

void CSketch::run()
{
	while (true)
	{
		CSketch::gpio();
		CSketch::update();
		CSketch::draw();

		int key = cv::waitKey(1) & 0xFF;
		if (key == 'q' || key == 'Q' || _exit_clicked)
		{
			cv::destroyWindow("Etch-A-Sketch");
			break;
		}
	}
}

void CSketch::gpio()
{
	_joystick.x = _control.get_analog(1, 2);
	_joystick.y = _control.get_analog(1, 26);

	_control.get_data(1, 24, value);
	_accelerometer = value;

	_button_A = _control.get_button(33);
	_button_B = _control.get_button(32);
}

void CSketch::update()
{
	_joystick.x -= 50;
	_joystick.y -= 50;
	_joystick.y *= -1;

	_previousPosition = _position;

	//Stabalize at origin
	if (_joystick.x > 2 || _joystick.x < -2)
	{
		_position.x += _joystick.x / 4;
	}

	if (_joystick.y > 2 || _joystick.y <-2)
	{
		_position.y += _joystick.y / 4;
	}

	//Boundary
	if(_position.x>=750)
	{
		_position.x = 749;
	}
	else if(_position.x<=0)
	{
		_position.x = 0;
	}
	if(_position.y>=750)
	{
		_position.y = 748;
	}
	else if(_position.y<=0)
	{
		_position.y = 1;
	}

	////////////////////////////////////
	if (_button_A== true)
	{
		_canvas.setTo(cv::Scalar(0, 0, 0));  // Clear the canvas
		_position = cv::Point(375, 375);      // Reset position
		_previousPosition = cv::Point(375, 375);
	}

	if (_button_B == true)
	{
		_colorIndex = (_colorIndex + 1) % _colors.size();	
		_previous_colorIndex = (_colorIndex - 1 + _colors.size()) % _colors.size();

		_control.set_data(0, _LED_colors[_colorIndex], 1);
		_control.set_data(0, _LED_colors[_previous_colorIndex], 0);
	}
	////////////////////////////////////
	
	if (_accelerometer - _previous_accelerometer > 1600 || _accelerometer - _previous_accelerometer < -1600 )
	{
		_canvas.setTo(cv::Scalar(0, 0, 0));  // Clear the canvas
		_position = cv::Point(375, 375);      // Reset position
		_previousPosition = cv::Point(375, 375);
	}
	_previous_accelerometer = _accelerometer;
	
}


void CSketch::draw()
{
	cvui::window(_canvas, 10, 10, 175, 75, "Etch-A-Sketch");
	_exit_clicked = cvui::button(_canvas, 20, 40, "EXIT");
	_reset = cvui::button(_canvas, 90, 40, "RESET");
	if (_reset)
	{
		_canvas.setTo(cv::Scalar(0, 0, 0));  // Clear the canvas
		_position = cv::Point(375, 375);      // Reset position
		_previousPosition = cv::Point(375, 375);
	}

	cv::line(_canvas, _previousPosition, _position, _colors[_colorIndex], 2);

	cvui::update();

	cv::imshow("Etch-A-Sketch", _canvas);
}