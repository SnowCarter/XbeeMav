/* SerialDevice.h -- Serial Device class to handle serial communications
                     with XBee --                                            */
/* ------------------------------------------------------------------------- */
/* September 20, 2016 -- @Copyright Aymen Soussia. All rights reserved.      */
/*                                  (aymen.soussia@gmail.com)                */


#pragma once

#include<deque>
#include<iostream>
#include<memory> 

#include<boost/asio.hpp>

#include"MultithreadingDeque.hpp"
#include"XBeeFrame.h"


namespace Mist
{


namespace Xbee
{


typedef MultithreadingDeque<std::shared_ptr<std::string>> Thread_Safe_Deque;


//*****************************************************************************
class SerialDevice
{
public:
	SerialDevice();
	~SerialDevice();

	bool Init(const std::string& device, const std::size_t baud_rate);
	void Send_Frame(const std::string& frame);
	void Run_Service();
	void Stop_Service();
	Thread_Safe_Deque* Get_In_Messages_Pointer();

private:

	enum FRAME_TYPE
	{
		AT_COMMAND = 0,
		AT_COMMAND_QUEUE_REGISTER_VALUE = 1,
		TRANSMIT_REQUEST = 2,
		EXPLICIT_ADDRESSING_COMMAND_FRAME = 3,
		REMOTE_AT_COMMAND = 4,
		AT_COMMAND_RESPONSE = 5,
		MODEM_STATUS = 6,
		TRANSMIT_STATUS = 7,
		ROUTE_INFORMATION_PACKET = 8,
		AGGREGATE_ADDRESSING_UPDATE = 9,
		RECEIVE_PACKET = 10,
		EXPLICIT_RX_INDICATOR = 11,
		IO_DATA_SAMPLE_RX_INDICATOR = 12,
		NODE_IDENTIFICATION_INDICATOR = 13,
		REMOTE_AT_COMMAND_RESPONSE = 14
	};

	void Init_Frame_Type_Keys();
	void Set_Port_Options(const std::size_t baud_rate);
	void Read_Frame_Header();
	void Read_Frame_Body();
	void Write_Frame();

	boost::asio::io_service io_service_;
	boost::asio::serial_port serial_port_;
	std::deque<std::string> out_messages_;
	Thread_Safe_Deque in_messages_;
	Mist::Xbee::Frame current_frame_;
	unsigned int FRAME_TYPE_KEYS[REMOTE_AT_COMMAND_RESPONSE + 1];
};


}


}