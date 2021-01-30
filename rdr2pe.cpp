#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

string promptConversionType() {
	string response;
	while (response != "file" && response != "folder") {
		cout << "Do you want to extract from a single file or all files in a folder? [file/folder]: ";
		cin >> response;
		transform(response.begin(), response.end(), response.begin(), ::tolower);
		cout << endl;
	}
	return response;
}

void convertFile(string filePath) {
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
	unsigned char bytesToFind[] = {0xFF, 0xD9};
	ofstream outputFile;
	outputFile.open(filePath.append(".jpg"), ios::binary);

	for (int i = 0; i < len2; i++) {
		outputFile << buffer2[i];

		unsigned int byteRead = (unsigned int)buffer2[i];
		if (byteRead > 255) byteRead = byteRead - 0xffffff00;

		if (byte1Found) {
			if (byteRead == (unsigned int)bytesToFind[1]) {
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
}

int main()
{
	string conversionType = promptConversionType();

	cin.clear();
	cin.sync();

	if (conversionType == "file") {
		string filePath;
		cout << "Enter path to file (include file name): ";
		getline(cin, filePath);

		while (!fs::exists(filePath) || fs::is_directory(filePath)) {
			cout << "File does not exist or is a folder. If you want to convert all files in a folder, choose the folder option." << endl << endl;
			cout << "Enter path to file (include file name): ";
			getline(cin, filePath);
		}

		convertFile(filePath);

	} else if (conversionType == "folder") {
		cout << "Enter path to folder: ";
		string folderPath;
		getline(cin, folderPath);

		while (!fs::exists(folderPath) || fs::is_regular_file(folderPath)) {
			cout << "Error: Folder does not exist or is a file. If you want to convert a file, choose the file option." << endl << endl;
			cout << "Enter path to folder: ";
			getline(cin, folderPath);
		}

		for (const auto & entry : fs::directory_iterator(folderPath)) {
			string pathString = entry.path().generic_string();
			string fileName = pathString.substr(pathString.find_last_of('/') + 1);
			bool isPRDRFile = !fileName.compare(0, 4, "PRDR") && fileName.find_last_of('.') == string::npos;
			if (isPRDRFile) {
				cout << "Extracting photo from " << pathString << endl;
				convertFile(pathString);
			}
		}
	}

	//------------------------------------------------------------

	cout << endl << "Photo extraction completed. Press any key to exit" << flush;
	_getch();
} 