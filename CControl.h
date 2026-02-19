#pragma once

#include "Serial.h"

/**
* @brief Controls the microcontroller via serial communication
*
* This class contains functions to initialize, send and receive data from the microcontroller.
*
* @author Johnny Liu
*
*/
class CControl
{

private:

	Serial _com; ///< Serial communication object

public:

	/**
	* @brief Default constructor for CControl
	*/
	CControl();

	/**
	* @brief Destructor for CControl
	*/
	~CControl();

	/**
	* @brief Initializes the serial communication with the microcontroller
	* 
	* @param comport The COM port number to use for communication
	* @return void
	*/
	void init_com(int comport);

	/**
	* @brief Retrieves data from the microcontroller
	* 
	* @param type The type of data to retrieve (0 = digital, 1 = analog)
	* @param channel The channel number to retrieve data from
	* @param result Reference to store the retrieved data
	* @return bool True if data was successfully retrieved, false otherwise
	*/
	bool get_data(int type, int channel, int& result);

	/**
	* @brief Sends data to the microcontroller
	* 
	* @param type The type of data to send (0 = digital, 1 = analog)
	* @param channel The channel number to send data to
	* @param val The value to send
	* @return bool True if data was successfully sent, false otherwise
	*/
	bool set_data(int type, int channel, int val);

	/**
	* @brief Retrieves analog data as a percentage
	* 
	* @param type The type of analog data (typically 1)
	* @param channel The channel number to read from
	* @return float The analog value as a percentage (0.0 to 100.0)
	*/
	float get_analog(int type, int channel);

	/**
	* @brief Reads button state with debouncing
	* 
	* @param channel The GPIO channel number of the button
	* @return bool True if button is pressed (with debounce), false otherwise
	*/
	bool get_button(int channel);

};