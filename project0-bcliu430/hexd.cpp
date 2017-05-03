////////////////////////////////////////////////////////////////////////////////
// Filename:      hexd.cpp
// Name:          Beichen Liu 刘北辰
// Description:   This cpp program is written to convert a binary file into hex
// Last Modified: ver.01-17-2017 File Created
//                ver.01-19-2017 Converted the input binary into a hex and print
//                               Printed out index, printed out some char
//                ver.01-20-2017 Fixed print unknown characters.
//                ver.01-23-2017 Fixed all buges and run the grade script.
//
// TODO: All done
//

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <math.h>

using namespace std;

void hexdump (string infile);

int main(int argc, char ** argv){

    if(argc != 2) {
        // check if there is only one input file
        cerr <<"Usage: " << argv[0] << " <input.bin> " << endl;
        exit(EXIT_FAILURE);
    }
    else {
        // if number of argument is correct
        ifstream infile(argv[1], ios::binary);
        if ( !infile.is_open() ) {
            // check if i can open input file;
            cerr << "cannot open input file, exit! " << endl;
            exit(EXIT_FAILURE);
        }

	    else {
	        hexdump(argv[1]);
	        // run hexdump function
        }
    }

    return EXIT_SUCCESS;
}

void hexdump(string infile){
    uint16_t k = 0;  // index for space between 4 bytes
    uint16_t LineLength = 16; // length of each line
    unsigned char * buf;   // a buffer to store all values;

    ifstream inf(infile, ios::binary);
    if(inf) {
        inf.seekg(0,ios::end);
        uint32_t fileLength = (uint32_t) inf.tellg();
        // find the length of the file
        inf.seekg(0,ios::beg);
        buf = new unsigned char [fileLength];
        inf.read((char*) buf, fileLength);

        uint32_t LastLine = ceil(fileLength/LineLength); // the last line number
        uint32_t lastPos  = fileLength%LineLength;    // last char position

        for (uint32_t i =0; i<fileLength; i+= LineLength){
            if (LastLine == i/LineLength) {
                if (lastPos !=0)
                    LineLength = lastPos;
            }

           unsigned char charbuf[LineLength];

            // print index and hex numbers
            cout<< hex <<setw(7)<<setfill('0')<< i << ": ";
            for (uint32_t j = 0; j < LineLength; j++) {
                cout << hex << setw(2) << (uint32_t) buf[j+i];
                if (isprint(buf[j+i]) == 0) charbuf[j] = '.';
                else charbuf[j] = (char)buf[j+i];
                k++;
                if (k == 2){
                    cout << " ";
                    k=0;
                }
            }

            // last line
            uint32_t left = 15 - lastPos;
            if (LastLine == ceil(i/16) ){
                k = lastPos % 2;
                for (uint32_t a = 0; a <= left; a++) {
                    k++;
                    if (k == 2){
                        cout << " ";
                        k=0;
                    }
                    cout << "  ";
                }
            }
            cout << " ";

            // print char or '.'
            for (uint32_t count = 0; count < LineLength; count++)
                cout << charbuf[count];
            cout<<endl;
//            cout << " " << charbuf  << endl
        }

    }
    return ;
}
