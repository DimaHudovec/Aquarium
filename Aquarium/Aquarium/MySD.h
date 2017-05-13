// MySD.h

#ifndef _MYSD_h
#define _MYSD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SPI.h>
#include <SD.h>
#include "Temperature.h"
#include "Feed.h"
#include "MyRTC.h"

struct MySDStruct
{
	File feadfile;
	File tempfile;
};

extern MySDStruct MySD;

void writeFeed();
void writeTemp();

#endif

