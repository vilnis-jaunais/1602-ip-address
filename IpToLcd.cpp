#include <string>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include "GetCommandOutput.h"
#include "LCD1602.h"

using namespace std;

int main(){
    string s = toString("hostname -I");
    char cstr[s.size() + 1];
    s.copy(cstr, 15);
    cstr[14] = '\0';
    lcdSetup(0x27);
    ClrLcd();
    lcdLine(1);
    typeln(cstr);
    exit(1);
}

// bash to compile: g++ LCD1602.cpp GetCommandOutput.cpp IpToLcd.cpp -o printIP -lwiringPi