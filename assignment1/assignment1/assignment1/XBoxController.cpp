//Peter huynh z5160067
//mtrn 2500
//14:00 -> 16:00 tuesday tutorial 

#include <iostream>
#include <Windows.h>
#include <xinput.h>
#include <math.h>
#include "XBoxController.h"
#include "XInputWrapper.h"
// but im not a rapper

 XINPUT_STATE State;
 XINPUT_VIBRATION Vibration;
 DWORD id;
#define left_deadzone 10000
#define right_deadzone 10000


// this is the constructor
GamePad::XBoxController::XBoxController(XInputWrapper * xinput, DWORD id)
{
	// put the inputs through the rapper
	this->xinputs = xinput;
	Controllerid = id;

}

DWORD GamePad::XBoxController::GetControllerId()
{
	//jsut returns a value from 0 to 3 (max four controllers)
	return Controllerid;
}
//from line 32 to 169, if a button is pressed, then the value would
//be returned true else is false wallah cuz
bool GamePad::XBoxController::IsConnected()
{
	//checking the battery state and if the value is not zero
	// it is connected else not connected
	if (XInputGetState(id, &State) == ERROR_DEVICE_NOT_CONNECTED) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedA()
{
	xinputs->XInputGetState(id, &State);
	if (State.Gamepad.wButtons == XINPUT_GAMEPAD_A) {
		return true; 
	}
	return false;
}

bool GamePad::XBoxController::PressedB()
{
	
	xinputs->XInputGetState(id, &State);
	if (State.Gamepad.wButtons == XINPUT_GAMEPAD_B) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedX()
{
	xinputs->XInputGetState(id, &State);
	if (State.Gamepad.wButtons == XINPUT_GAMEPAD_X) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedY()
{
	xinputs->XInputGetState(id, &State);
	if (State.Gamepad.wButtons == XINPUT_GAMEPAD_Y) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedLeftShoulder()
{
	xinputs->XInputGetState(id, &State);
	if (State.Gamepad.wButtons == XINPUT_GAMEPAD_LEFT_SHOULDER) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedRightShoulder()
{
	xinputs->XInputGetState(id, &State);
	if (State.Gamepad.wButtons == XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedLeftDpad()
{
	xinputs->XInputGetState(id, &State);
	if (State.Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_LEFT) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedRightDpad()
{
	xinputs->XInputGetState(id, &State);
	if (State.Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_RIGHT) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedUpDpad()
{
	xinputs->XInputGetState(id, &State);
	if (State.Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_UP) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedDownDpad()
{
	xinputs->XInputGetState(id, &State);
	if (State.Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_DOWN) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedStart()
{
	xinputs->XInputGetState(id, &State);
	if (State.Gamepad.wButtons == XINPUT_GAMEPAD_START) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedBack()
{
	xinputs->XInputGetState(id, &State);
	if (State.Gamepad.wButtons == XINPUT_GAMEPAD_BACK) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedLeftThumb()
{
	xinputs->XInputGetState(id, &State);
	if (State.Gamepad.wButtons == XINPUT_GAMEPAD_LEFT_THUMB) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedRightThumb()
{
	xinputs->XInputGetState(id, &State);
	if (State.Gamepad.wButtons == XINPUT_GAMEPAD_RIGHT_THUMB) {
		return true;
	}
	return false;
}

// for each left/righttriggerlocation, they return a char value
// but later can be converted to decimal by int the output
BYTE GamePad::XBoxController::LeftTriggerLocation()
{
	xinputs->XInputGetState(id, &State);
	
	return 	int(State.Gamepad.bLeftTrigger);
	//tried making an int and it doesn't work for me 
}

BYTE GamePad::XBoxController::RightTriggerLocation()
{
	xinputs->XInputGetState(id, &State);

	return 	State.Gamepad.bRightTrigger;
	// why does it return ASCII???
}

// returns x and y values for for left and right thumb
GamePad::Coordinate GamePad::XBoxController::LeftThumbLocation()
{
	xinputs->XInputGetState(id, &State);
	short LX = State.Gamepad.sThumbLX;
	short LY = State.Gamepad.sThumbLY;


	//determine how far the controller is pushed
	float magnitude = sqrt(LX*LX + LY * LY);

	//determine the direction the controller is pushed
	float normalizedLX = LX / magnitude;
	float normalizedLY = LY / magnitude;

	float normalizedMagnitude = 0;

	//check if the controller is outside a circular dead zone
	if (magnitude > left_deadzone)
	{
		//clip the magnitude at its expected maximum value
		if (magnitude > 32767) magnitude = 32767;

		//adjust magnitude relative to the end of the dead zone
		magnitude -= left_deadzone;

		//optionally normalize the magnitude with respect to its expected range
		//giving a magnitude value of 0.0 to 1.0
		normalizedMagnitude = magnitude / (32767 - left_deadzone);
	}
	else //if the controller is in the deadzone zero out the magnitude
	{
		magnitude = 0.0;
		normalizedMagnitude = 0.0;
	}

	return GamePad::Coordinate(LX,LY);
}

GamePad::Coordinate GamePad::XBoxController::RightThumbLocation()
{
	xinputs->XInputGetState(id, &State);
	short RX = State.Gamepad.sThumbRX;
	short RY = State.Gamepad.sThumbRY;

	//determine how far the controller is pushed
	float magnitude_R = sqrt(RX*RX + RY * RY);

	//determine the direction the controller is pushed
	float normalizedRX = RX / magnitude_R;
	float normalizedRY = RY / magnitude_R;

	float normalizedMagnitude_R = 0;

	//check if the controller is outside a circular dead zone
	if (magnitude_R > right_deadzone)
	{
		//clip the magnitude at its expected maximum value
		if (magnitude_R > 32767) magnitude_R = 32767;

		//adjust magnitude relative to the end of the dead zone
		magnitude_R -= right_deadzone;

		//optionally normalize the magnitude with respect to its expected range
		//giving a magnitude value of 0.0 to 1.0
		normalizedMagnitude_R = magnitude_R / (32767 - right_deadzone);
	}
	else //if the controller is in the deadzone zero out the magnitude
	{
		magnitude_R = 0.0;
		normalizedMagnitude_R = 0.0;
	}

	return GamePad::Coordinate(RX,RY);
}

// intitilise the vibration settings?
void GamePad::XBoxController::Vibrate(WORD left, WORD right)
{
	// note that this doesn't need return a values
	//what is word? i have not idea m8
	
	// get the set state from the header file and now set the values for the motor
	
	Vibration.wLeftMotorSpeed = left;
	Vibration.wRightMotorSpeed = right;
	xinputs->XInputSetState(id, &Vibration);
}

// 'set' values for the deadzone radius
void GamePad::XBoxController::SetDeadzone(unsigned int radius)
{
	deadzone = radius;
	
}
