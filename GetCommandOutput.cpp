#include <string>
#include <iostream>
#include <stdio.h>

using namespace std;

string toString(const char* command)
{
	FILE* pipe = popen(command, "r");		
	if (!pipe){
		return "ERROR";
	}
	char buffer[128];
	string result = "";
	while(!feof(pipe))						
	{
		if(fgets(buffer, 128, pipe) != NULL){
			result += buffer;
		}
	}
	pclose(pipe);
	return(result);
}