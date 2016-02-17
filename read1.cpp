/*!
 \file      Example1.cpp

 \brief     Example code source for class serialib.
            This example open the device on ttyACM0.
            (USB to RS232 converter under linux).
            If the opening is successful, it sends the AT command
            and waits for a string being received from the device.
            After 5 seconds, if no valid data are received from the
            device, reception is giving up.

 \author    Philippe Lucidarme (University of Angers) <serialib@googlegroups.com>
 \version   1.2
 \date      05/01/2011
 */

#include <stdio.h>
#include "serialib.h"
#include <sstream>
#include <bitset>
#include <string>
#include <iomanip>


#if defined (_WIN32) || defined( _WIN64)
#define         DEVICE_PORT             "COM9"                               // COM1 for windows
#endif

#ifdef __linux__
#define         DEVICE_PORT             "/dev/ttyO1"                         // ttyS0 for linux
#endif

using namespace std;

const char* hex_char_to_bin(char c)
{
    // TODO handle default / error
    switch(toupper(c))
    {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
    }
}

std::string hex_str_to_bin_str(const std::string& hex)
{
    // TODO use a loop from <algorithm> or smth
    std::string bin;
    for(unsigned i = 0; i != hex.length(); ++i)
       bin += hex_char_to_bin(hex[i]);
    return bin;
}


int main()
{
    serialib LS;                                                            // Object of the serialib class
    int Ret,dick=0;                                                                // Used for return values
    char Buffer[128];




    // Open serial port

    Ret=LS.Open(DEVICE_PORT,115200);                                        // Open serial link at 115200 bauds
    cout<<"Ret Value write:"<<Ret<<endl;
    if (Ret!=1) {                                                           // If an error occured...
        printf ("Error while opening port. Permission problem ?\n");        // ... display a message ...
        return Ret;                                                         // ... quit the application
    }
    printf ("Serial port opened successfully !\n");



	while(dick =0)
	{
    // Write the AT command on the serial port
    LS.WriteChar(128);
    LS.WriteChar(132);
    
    LS.WriteChar(148);
    LS.WriteChar(1);
    LS.WriteChar(7);
   
    /*cout<<"Ret Value:"<<Ret<<endl;
    if (Ret!=1) {                                                           // If the writting operation failed ...
        printf ("Error while writing data\n");                              // ... display a message ...
        return Ret;                                                         // ... quit the application.
    }
    printf ("Write operation is successful \n");
    */



    //Read a string from the serial device
    Ret=LS.Read(Buffer,5,1000);                                // Read a maximum of 128 characters with a timeout of 5 seconds
   // Ret=LS.ReadString(Buffer,'\n',10000,10000);                                                                        // The final character of the string must be a line feed ('\n')
    cout<<"Ret Value read:"<<Ret<<endl;
    if (Ret>0)                                                              // If a string has been read from, print the string
    {
       int i = 0 ;
       char temp[6];
       //i = atoi(Buffer);
       
       
       cout<<"hex: "<<endl;
        for (const char* p = Buffer; *p; ++p)
        {
            printf("%02X\n", *p);
            cout << (int)*p << endl;
            temp[i] = *p;
            cout <<"P value: " << (int)temp[i] <<"end" <<endl;
            i++;
        }
        printf("\n");
        
        //auto WTF= Buffer;
        
        //hex_str_to_bin_str(WTF);
        
        /*cout<<"store value: " <<temp <<"end" <<endl;
        printf("%02x\n", temp);*/
        

        
       /*cout <<"str: " <<Buffer << endl;
       cout <<"val: "  << i << endl;
       
       std::cout <<"hex: " <<std::hex << Buffer<< '\n';
       
       cout << "a is " << hex << (int) Buffer<< endl;
       printf (" -> %x\n",Buffer);*/
    }
    else
        printf ("TimeOut reached. No data received !\n");                   // If not, print a message.

	}

    // Close the connection with the device

    LS.Close();

    return 0;
}


