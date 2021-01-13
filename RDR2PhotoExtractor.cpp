#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

int main()
{
    string filePath;
    cout << "Enter path to file (include file name): ";
    cin >> filePath;
    ifstream fl(filePath);  
    fl.seekg( 0, ios::end );  
    size_t len = fl.tellg();  
    char *buffer = new char[len];  
    fl.seekg(0, ios::beg);   
    fl.read(buffer, len);  
    fl.close();  
    
    const int startBytes = 300;

    size_t len2 = len - startBytes;
    char *buffer2 = buffer + startBytes;

    bool byte1Found = false;
    bool byte2Found = false;
    unsigned char bytesToFind[] = {0xFF, 0xD9};
    ofstream outputFile;
    outputFile.open("output.jpg", ios::binary);

    for (int i = 0; i < len2; i++) {
        if (byte1Found && byte2Found) break;

        outputFile << buffer2[i];

        unsigned int byteRead = (unsigned int)buffer2[i];
        if (byteRead > 255) byteRead = byteRead - 0xffffff00;

        if (byte1Found) {
            if (byteRead == (unsigned int)bytesToFind[1]) {
                byte2Found = true;
                break;
            } else {
                byte1Found = false;
            }
        }

        if (byteRead == (unsigned int)bytesToFind[0]) {
            byte1Found = true;
        }

        if ((i + 1) == len2) {
            cout << "Error: jpg terminator not found. " << filePath << " was copied to output file." << endl;
        }
    }
    cout << "Photo extraction completed. Press any key to exit" << flush;
    _getch();
} 