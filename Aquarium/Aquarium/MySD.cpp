// 
// 
// 

#include "MySD.h"

MySDStruct MySD;

void writeFeed()
{
	if (!SD.begin(53)) {
		Serial.println("initialization failed!");
		return;
	}
	Serial.println("initialization done.");

	// open the file. note that only one file can be open at a time,
	// so you have to close this one before opening another.
	MySD.feadfile = SD.open("Feed.txt", FILE_WRITE);

	// if the file opened okay, write to it:
	if (MySD.feadfile) {
		Serial.print("Writing to test.txt...");
		MySD.feadfile.print("Data ");
		MySD.feadfile.print(MyRTC.currentDay);
		MySD.feadfile.print(".");
		MySD.feadfile.print(MyRTC.currentMonth);
		MySD.feadfile.print(".");
		MySD.feadfile.print(MyRTC.currentYear);
		MySD.feadfile.print("  Time ");
		MySD.feadfile.print(MyRTC.currentHour);
		MySD.feadfile.print(":");
		MySD.feadfile.println(MyRTC.currentMinute);
		// close the file:
		MySD.feadfile.close();
		Serial.println("done.");
	}
	else {
		// if the file didn't open, print an error:
		Serial.println("error opening test.txt");
	}

}

void writeTemp()
{
	if (!SD.begin(53)) {
		Serial.println("initialization failed!");
		return;
	}
	Serial.println("initialization done.");

	// open the file. note that only one file can be open at a time,
	// so you have to close this one before opening another.
	MySD.tempfile = SD.open("Temperature.txt", FILE_WRITE);

	// if the file opened okay, write to it:
	if (MySD.tempfile) {
		Serial.print("Writing to test.txt...");
		MySD.tempfile.print("Data ");
		MySD.tempfile.print(MyRTC.currentDay);
		MySD.tempfile.print(".");
		MySD.tempfile.print(MyRTC.currentMonth);
		MySD.tempfile.print(".");
		MySD.tempfile.print(MyRTC.currentYear);
		MySD.tempfile.print("  Time ");
		MySD.tempfile.print(MyRTC.currentHour);
		MySD.tempfile.print(":");
		MySD.tempfile.print(MyRTC.currentMinute);
		MySD.tempfile.print("  Temperature ");
		MySD.tempfile.print(Temperature.realTemp);
		MySD.tempfile.println(" C");
		// close the file:
		MySD.tempfile.close();
		Serial.println("done.");
	}
	else {
		// if the file didn't open, print an error:
		Serial.println("error opening test.txt");
	}
}

