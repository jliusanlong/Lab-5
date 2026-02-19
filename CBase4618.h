#pragma once

#include "CControl.h"

/**
* @brief Base class for BCIT 4618 lab projects
*
* This class provides common functionality for projects .
*
* @author Johnny Liu
*/
class CBase4618
{
public:
	/**
	* @brief Default constructor for CBase4618
	*/
	CBase4618();

	/**
	* @brief Destructor for CBase4618
	*/
	~CBase4618();

protected:
	cv::Mat _canvas; ///< OpenCV matrix for drawing canvas
	CControl _control; ///< Microcontroller control interface

};

