//Peter huynh z5160067
//mtrn 2500
//14:00 -> 16:00 tuesday tutorial 


#include <iostream>
#include <Windows.h>
#include <math.h>
#include "XInputWrapper.h"
#include "XBoxController.h"

#define max_radius 32767

bool quit = false;


int main() {


	while (!quit) {
		XINPUT_VIBRATION Vibrate;
		XInputWrapper xinput;
		int hey = 0;

		//GamePad::XBoxController SetDeadzone(unsigned int radius);

		GamePad::XBoxController controller(&xinput, 0);
		// now we can take out the x and y values from each thumb
		GamePad::Coordinate leftthumb = controller.LeftThumbLocation();
		GamePad::Coordinate righthumb = controller.RightThumbLocation();

		// show that the controller is connected and ready to be used
		if (controller.IsConnected()) {
			std::cout << "controller is not connected" << std::endl;
			
		}
		else {

		std::cout << controller.GetControllerId() << "   ";

		if (controller.PressedA()) {
			std::cout << "A";

		}

		else if (controller.PressedRightThumb()) {
			std::cout << "R Thumb";
		//	controller.RightTriggerLocation() == 0x0000;

		}
		else if (controller.PressedLeftThumb()) {
			std::cout << "L Thumb";
			controller.RightTriggerLocation() == 0000;
		
			Vibrate.wLeftMotorSpeed = 0;
			Vibrate.wRightMotorSpeed = 0;
			XInputSetState(0, &Vibrate);
			

		}
		else if (controller.PressedBack()) {
			std::cout << "Back";
			break;

		}
		else if (controller.PressedStart()) {
			std::cout << "Start";
			Vibrate.wLeftMotorSpeed = 65000;
			Vibrate.wRightMotorSpeed = 65535;
			XInputSetState(0, &Vibrate);
		}
		else if (controller.PressedLeftShoulder()) {
			std::cout << "L Shoulder";

		}
		else if (controller.PressedRightShoulder()) {
			std::cout << "R Shoulder";

		}
		else if (controller.LeftTriggerLocation() > 0x00f0) {
			Vibrate.wLeftMotorSpeed = 30000;
			Vibrate.wLeftMotorSpeed = 30000;
			XInputSetState(0, &Vibrate);
		}
		else if (controller.RightTriggerLocation() >0) {
			Vibrate.wLeftMotorSpeed = (int(controller.RightTriggerLocation())/25)*6500;
			Vibrate.wRightMotorSpeed = 0;
			XInputSetState(0, &Vibrate);
		}
		else {
			std::cout << "off";
			Vibrate.wRightMotorSpeed = 0;
			Vibrate.wLeftMotorSpeed = 0;
			XInputSetState(0, &Vibrate);
		}




		

		if (controller.PressedLeftThumb()) {
			int hey = 0;
			
		}
		else {
			hey = int(controller.RightTriggerLocation()) / 25;
		}


		std::cout << "   " << int(controller.LeftTriggerLocation()) / 25 << "   " << hey << std::endl;
		
		
	
		//std::cout << "   " << leftthumb.GetX() << "   " << leftthumb.GetY();
		//std::cout << "   " << righthumb.GetX() << "   " << righthumb.GetY();
		//std::cout << "   " << normalizedMagnitude * leftthumb.GetX() << "   " << normalizedMagnitude * leftthumb.GetY() << "   "; 
		//std::cout << "   " << normalizedMagnitude_R * righthumb.GetX() << "   " << normalizedMagnitude_R * righthumb.GetY() << std::endl;

		//dead to me
		// the normalize is the ratio for moving one unit after deadzone 
		// such that it wouldh increase sensitivity ???
		// but i still don't understand how to set the deadzone.
	
		Sleep(500);
		}
	} 
	
	return 0;
}
