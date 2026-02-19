#pragma once
	
#include <array>
#include "CBase4618.h"

/**
* @brief Implements an Etch-A-Sketch drawing application
*
* This class creates an interactive drawing application using joystick input,
* buttons for controls, accelerometer for shake-to-clear, and LED indicators.
*
* @author Johnny Liu
*/
class CSketch : public CBase4618
{
public:
	/**
	* @brief Constructor for CSketch
	* 
	* @param comport The COM port number for microcontroller communication
	* @param rows The number of rows for the canvas
	* @param cols The number of columns for the canvas
	*/
	CSketch(int comport, int rows, int cols);

	/**
	* @brief Destructor for CSketch
	*/
	~CSketch();

	/**
	* @brief Main application loop
	* 
	* Runs the continuous loop for the Etch-A-Sketch application,
	* handling input, updates, and rendering
	* @return void
	*/
	void run();

	/**
	* @brief Reads GPIO inputs from the microcontroller
	* 
	* Retrieves joystick positions, button states, and accelerometer data
	* @return void
	*/
	void gpio();

	/**
	* @brief Updates application state
	* 
	* Processes input data, updates cursor position, handles button presses,
	* color changes, and accelerometer-based canvas clearing
	* @return void
	*/
	void update();

	/**
	* @brief Renders the canvas and UI elements
	* 
	* Draws lines on the canvas, displays GUI buttons, and shows the window
	* @return void
	*/
	void draw();

private:
	cv::Point2f _joystick; ///< Current joystick position (x, y)
	cv::Point _position; ///< Current cursor position on canvas
	cv::Point _previousPosition; ///< Previous cursor position for line drawing

	int _accelerometer; ///< Current accelerometer Y-axis value
	int _previous_accelerometer; ///< Previous accelerometer Y-axis value for delta calculation

	int value; ///< Temporary variable for GPIO data retrieval
	int _button_A; ///< State of button A (clear/reset)
	int _button_B; ///< State of button B (color change)

	const std::array<int, 3> _LED_colors = { 39, 38, 37 }; ///< GPIO pins for RGB LED control

	const std::array<cv::Scalar, 3> _colors = ///< Predefined colors for drawing and LED indicators
	{
		cv::Scalar(0,   0,   255), ///< Red color (B,G,R format)
		cv::Scalar(0,   255, 0),   ///< Green color
		cv::Scalar(255, 0,   0),   ///< Blue color
	};

	std::size_t _colorIndex = 0; ///< Current active color index
	std::size_t _previous_colorIndex; ///< Previous color index for LED control

	bool _reset = false; ///< Reset flag
	bool _exit_clicked = false; ///< Exit button state flag
};