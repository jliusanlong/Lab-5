#include "stdafx.h"
#include "CControl.h"
#include <chrono>
#include <cstdint>
#include <windows.h>    
#include <opencv2/core.hpp> 

CControl::CControl()
{
}

CControl::~CControl()
{
}

//Chat
int last_number_from_line(const std::string& s)
{
    std::stringstream ss(s);
    std::string token, last;

    while (ss >> token) {
        last = token;              // ends up as the last whitespace-separated piece
    }

    if (last.empty()) {
        throw std::runtime_error("No tokens in string");
    }

    return std::stoi(last);        // convert last token to int
}

//Chat generated millis function
std::uint64_t millis()
{
    using clock = std::chrono::steady_clock;
    static const auto start = clock::now();          // captured once at first call
    const auto now = clock::now();

    return (std::uint64_t)std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
}

void CControl::init_com(int comport)
{
	std::string port_name = "COM" + std::to_string(comport);
	_com.open(port_name, 115200);

}

bool CControl::get_data(int type, int channel, int& result)
{ 
	std::string tx_str = "G " + std::to_string(type) + " " + std::to_string(channel) + "\n";
	std::string rx_str;
    char buff[2];

	    _com.clear_rx();

        // Send TX string
        _com.write(tx_str.c_str(), tx_str.length());

        std::this_thread::sleep_for(std::chrono::microseconds(1));
        //Sleep(1); // wait for ADC conversion, etc. May not be needed?

        rx_str = "";
        // start timeout count
        int64_t start_time = cv::getTickCount();

        buff[0] = 0;
        // Read 1 byte and if an End Of Line then exit loop
        // Timeout after 1 second, if debugging step by step this will cause you to exit the loop
        while ((buff[0] != '\n') && (cv::getTickCount() - start_time) / cv::getTickFrequency() < 1.0)
        {
            if (_com.read(buff, 1) > 0)
            {
                rx_str = rx_str + buff[0];
            }
        }
      
		result = last_number_from_line(rx_str);
        
        return true;
}

bool CControl::set_data(int type, int channel, int val)
{
	std::string tx_str1 = "S " + std::to_string(type) + " " + std::to_string(channel) + " " + std::to_string(val) + "\n";;
    // Send TX string
    _com.write(tx_str1.c_str(), tx_str1.length());
    return true;
}

bool CControl::get_button (int channel)
{
        std::uint64_t current_time = millis();

        static std::uint64_t previous_time = 0;
        const std::uint64_t debounce_time = 200; // 200 milliseconds debounce time
        int value;
        static int button_count = 0;

        if (current_time - previous_time > debounce_time)
        {
            get_data(0, channel, value);

            if (value == 0)
            {
	
                previous_time = current_time;
                return true;
            }
        }
        
        return false;
   
}

float CControl::get_analog(int type, int channel)
{
    float percent;
    int value;
    
    CControl::get_data(type, channel, value);
	
    percent = (value / 4096.0f) * 100.0f;
    
    return percent;

}

