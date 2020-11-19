// MetaMorseCodifier.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

#include <Windows.h>

//returns a string rather than a char so I can return an empty string
std::string GetCharFromMorse(std::string morse)
{
	remove_if(morse.begin(), morse.end(), isspace); //remove whitespace

	if(morse == ".-")		return "a" ;
	if(morse == "-...")		return "b" ;
	if(morse == "-.-.")		return "c" ;
	if(morse == "-..")		return "d" ;
	if(morse == ".")		return "e" ;
	if(morse == "..-.")		return "f" ;
	if(morse == "--.")		return "g" ;
	if(morse == "....")		return "h" ;
	if(morse == "..")		return "i" ;
	if(morse == ".---")		return "j" ;
	if(morse == "-.-")		return "k" ;
	if(morse == ".-..")		return "l" ;
	if(morse == "--")		return "m" ;
	if(morse == "-.")		return "n" ;
	if(morse == "---")		return "o" ;
	if(morse == ".--.")		return "p" ;
	if(morse == "--.-")		return "q" ;
	if(morse == ".-.")		return "r" ;
	if(morse == "...")		return "s" ;
	if(morse == "-")		return "t" ;
	if(morse == "..-")		return "u" ;
	if(morse == "...-")		return "v" ;
	if(morse == ".--")		return "w" ;
	if(morse == "-..-")		return "x" ;
	if(morse == "-.--")		return "y" ;
	if(morse == "--..")		return "z" ;

	if (morse == ".--.-")	return "å" ;
	if (morse == ".-.-")	return "ä" ; //Doesn't show up correctly in the console on my machine, may need to look into
	if (morse == "---.")	return "ö" ;


	if(morse == "-.-.--" 
		|| morse == "---.")	return "!" ;
	if(morse == "/")		return " " ;
	if(morse == "--..--")	return "," ;
	if(morse == "..--..")	return "?" ;
	if(morse == ".-.-.-")	return "." ;
	if(morse == "-..-.")	return "/" ;
	if(morse == ".----.")	return "\"";
	if(morse == "-....-")	return "-" ;

	if (morse == "-----")   return "0" ;
	if (morse == ".----")   return "1" ;
	if (morse == "..---")   return "2" ;
	if (morse == "...--")   return "3" ;
	if (morse == "....-")   return "4" ;
	if (morse == ".....")   return "5" ;
	if (morse == "-....")   return "6" ;
	if (morse == "--...")   return "7" ;
	if (morse == "---..")   return "8" ;
	if (morse == "----.")   return "9" ;

	return ""; //if the morse combination doesn't make sense, return nothing
}

std::string GetMorseOfChar(char c)
{
	c = (char)tolower((int)c);

	switch (c)
	{
	case 'a':  return ".-";
	case 'b':  return "-...";
	case 'c':  return "-.-.";
	case 'd':  return "-..";
	case 'e':  return ".";
	case 'f':  return "..-.";
	case 'g':  return "--.";
	case 'h':  return "....";
	case 'i':  return "..";
	case 'j':  return ".---";
	case 'k':  return "-.-";
	case 'l':  return ".-..";
	case 'm':  return "--";
	case 'n':  return "-.";
	case 'o':  return "---";
	case 'p':  return ".--.";
	case 'q':  return "--.-";
	case 'r':  return ".-.";
	case 's':  return "...";
	case 't':  return "-";
	case 'u':  return "..-";
	case 'v':  return "...-";	
	case 'w':  return ".--";
	case 'x':  return "-..-";
	case 'y':  return "-.--";
	case 'z':  return "--..";

	case -122:  return ".--.-"; //å
	case -124:  return ".-.-";	//ä
	case -108:  return "---.";	//ö

	case '0': return "-----";
	case '1': return ".----";
	case '2': return "..---";
	case '3': return "...--";
	case '4': return "....-";
	case '5': return ".....";
	case '6': return "-....";
	case '7': return "--...";
	case '8': return "---..";
	case '9': return "----.";

	case ' ':  return "/";
	case ',':  return "--..--";
	case '?':  return "..--..";
	case '!':  return "-.-.--";
	case '.':  return ".-.-.-";
	case '/':  return "-..-.";
	case '\'': return ".----.";
	case '-': return "-....-";


	default:
		return ""; //if there's have no translation for the character ignore it
		break;
	}
}


std::string ToMorse(std::string message, int times = 0)
{
	std::string morse;

	for (int i = 0; i < message.length(); i++)
	{
		morse += GetMorseOfChar(message[i]);
		if (i != message.length() -1) morse += ' ';
	}
	
	//Recursively converts to morse

	if (times > 0)
		return ToMorse(morse, times - 1);
	else return morse;
}

/**
Checks if a message contains anything but morse characters. If it contains anything else that means the message has been decrypted
*/
bool GetResolved(std::string morse)
{
	for (int i = 0; i < morse.size(); i++)
	{
		char c = morse[i];
		if (!(c == '.' || c == '-' || c == ' ' || c == '/' || c == '\n')) return true;
	}
	return false;
}



struct TranslationMessage
{
	int iteratios;
	std::string message;
};

/**
Translates morsecode into normal characters. If the result is morse code it translates it again.
*/
TranslationMessage FromMorse(std::string morse, int iterations = 0)
{
	//remove_if(morse.begin(), morse.end(), isspace);
	if (GetResolved(morse) || morse == " " || morse == "")
	{
		//morse += "\n\nThis message was remorsed " + std::to_string(iterations - 1) + " times\n";
		auto msg = TranslationMessage{ iterations, morse };
		return msg;
	}

	std::vector<std::string> morseChars;
	std::string segment;
	std::stringstream stream = (std::stringstream)morse;

	while (std::getline(stream, segment, ' '))
	{
		morseChars.push_back(segment);
	}

	std::string translated;
	for (auto s : morseChars)
	{
		translated += GetCharFromMorse(s);
	}
	return FromMorse(translated, iterations + 1);
}

/**
Copies a string to the clipboard
Source: http://www.cplusplus.com/forum/general/48837/
Thanks random guy from 2011
*/
void ToClipboard(HWND hwnd, const std::string& s) 
{
	OpenClipboard(hwnd);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
	if (!hg) 
	{
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}


int main()
{
	bool repeat = false;
	while (1)
	{
		std::cout << "Would you like to encrypt or decrypt a"<< (repeat ? "nother" : "") << " message?\n\nEnter:\n\n1. For encryption\n2. For decryption\n\n";

		int option;
		std::string number = "";
		std::cin >> number;
		try 
		{
			option = std::stoi(number);
		}
		catch (std::invalid_argument e)
		{
			system("CLS");
			std::cout << "You need to input a number." << std::endl;
			continue;
		}

		system("CLS");
		std::string m;
		std::getline(std::cin, m);

		if (option == 1)
		{
			std::cout << "What's your message?\n\n";
			std::string message;
			std::getline(std::cin, message);
			std::cout << "\nHow many layers of morse?\n" << std::endl;
			int times;
			std::string number = "";
			std::cin >> number;
			try 
			{
				times = std::stoi(number);
			}
			catch (std::invalid_argument e)
			{
				system("CLS");
				std::cout << "You need to input a number" << std::endl;
				continue;
			}

			system("CLS");
			std::string result = ToMorse(message, times);
			std::cout << result << "\n\n";

			std::cout << "To copy the message to the clipboard, enter Y\nEnter anything else to skip\n\n";
			char response;
			std::cin >> response;

			if (std::tolower(response) == 'y')
			{
				ToClipboard(NULL, result);
				std::cout << "\nCopied!\n\n";
			}
		}
		else if (option == 2)
		{
			std::cout << "Enter the message you would like decrypted:\n\n";
			std::string message;
			std::getline(std::cin, message);
			
			if (message.length() >= 4090)
			{
				message = "";

				std::ofstream file;
				file.open("ReallyLongMessage.txt", std::ofstream::trunc); //clearing file
				file.close();

				std::cout << "\nIt looks like your message is too long to fit in the console. Ambitious! \nPaste the message into the notepad that just popped up, save it and close." << std::endl;
				system("notepad.exe ReallyLongMessage.txt");

				std::ifstream f;

				f.open("ReallyLongMessage.txt");
				std::string line;
				while (std::getline(f, line))
				{
					message += line;
				}

				f.close();

				file.open("ReallyLongMessage.txt", std::ofstream::trunc); //clearing file
				file.close();
			}
			TranslationMessage result = FromMorse(message);
			std::cout << "\nLength: " << message.length() <<"\n";
			std::cout << "\nTranslation:\n\n";
			std::cout << result.message << "\n\n";
			std::cout << "This means that the encryption was ~" << message.length() / max(result.message.length(), 1) << " times longer than the actual message." << ((message.length() / max(result.message.length(), 1) > 1000000) ? " lol" : "") << "\n\n";
		}
		else
		{
			std::cout << "Please enter either 1 or 2\n";
		}
		repeat = true;
	}
}
