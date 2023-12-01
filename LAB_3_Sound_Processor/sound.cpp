#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

int sampleRate = 44100;
int bytesPerSample = 2;

class parser {
public:
	void pars(std::ifstream& inputFile, std::ofstream& outputFile) {
		// Чтение заголовка 
		char header[44];
		inputFile.read(header, 44);
		outputFile.write(header, 44);

		// Чтение размера блока info
		int infoSize = 0;
		inputFile.seekg(40, std::ios::beg);
		inputFile.read(reinterpret_cast<char*>(&infoSize), 4);

		// Чтение блока info
		std::vector<char> infoBlock(infoSize);
		inputFile.read(infoBlock.data(), infoSize);
		outputFile.write(infoBlock.data(), infoSize);

		// Чтение символов data
		char dataChars[4];
		inputFile.read(dataChars, 4);
		outputFile.write(dataChars, 4);
	}
};

class Wav {
public:
	virtual void converter() = 0;
	virtual ~Wav() {}
};

class mute : public Wav {
public:
	std::string fileName;
	int finish;
	int start;
	mute(int a, int b, std::string c) {
		start = a;
		finish = b;
		fileName = c;
	}
	void converter() {
		parser obj;

		std::ifstream inputFile;
		std::ofstream outputFile;

		inputFile.open(fileName, std::ios::binary);
		outputFile.open("output.wav", std::ios::binary);
		obj.pars(inputFile, outputFile);

		// Чтение размера блока data
		int dataSize = 0;
		inputFile.read(reinterpret_cast<char*>(&dataSize), 4);
		outputFile.write(reinterpret_cast<const char*>(&dataSize), 4);

		std::vector<char> buffer(dataSize);
		inputFile.read(buffer.data(), dataSize);

		// Замена данных на нули 
		start *= sampleRate * bytesPerSample;
		finish *= sampleRate * bytesPerSample;
		for (int i = start; i <= finish; ++i) {
			buffer[i] = 0;
		}

		// Запись измененных данных в новый файл
		outputFile.write(buffer.data(), dataSize);

		outputFile.close();
		inputFile.close();
	}
};

class mix : public Wav {
public:
	std::string fileName;
	std::string second_file_name;
	int start;
	int finish;

	mix (std::string a, std::string b, int c, int d) {
		second_file_name = a;
		fileName = b;
		start = c;
		finish = d;

	}
	void converter() {

		parser obj;

		std::ifstream inputFile1;
		std::ifstream inputFile2;
		std::ofstream outputFile;

		inputFile1.open(fileName, std::ios::binary);
		inputFile2.open(second_file_name, std::ios::binary);
		outputFile.open("output.wav", std::ios::binary);

		obj.pars(inputFile1, outputFile);

		// Чтение размера блока data
		int dataSize = 0;
		inputFile1.read(reinterpret_cast<char*>(&dataSize), 4);
		outputFile.write(reinterpret_cast<const char*>(&dataSize), 4);

		std::vector<char> buffer1(dataSize);
		inputFile1.read(buffer1.data(), dataSize);

		std::vector<char> buffer2(dataSize);
		inputFile2.read(buffer2.data(), dataSize);

		//миксование
		start *= sampleRate * bytesPerSample;
		finish *= sampleRate * bytesPerSample;

		for (int i = start; i < finish; ++i) {
			buffer1[i] = (buffer1[i]+ buffer2[i])/2;
		}

		// Запись измененных данных в новый файл
		outputFile.write(buffer1.data(), dataSize);

		outputFile.close();
		inputFile1.close();
		inputFile2.close();
	}
};

class reverse : public Wav {
public:
	std::string fileName;
	reverse(std::string b) {
		fileName = b;
	}
	void converter() {
		parser obj;

		std::ifstream inputFile;
		std::ofstream outputFile;

		inputFile.open(fileName, std::ios::binary);
		outputFile.open("output.wav", std::ios::binary);
		obj.pars(inputFile, outputFile);

		// Чтение размера блока data
		int dataSize = 0;
		inputFile.read(reinterpret_cast<char*>(&dataSize), 4);
		outputFile.write(reinterpret_cast<const char*>(&dataSize), 4);

		std::vector<char> buffer(dataSize);
		inputFile.read(buffer.data(), dataSize);

		//Разворот
		std::reverse(buffer.begin(), buffer.end());

		for (int i = 0; i < dataSize; i += 2) {
			unsigned short x = buffer[i] | (buffer[i + 1] << 8); 
			x = (x >> 8) | (x << 8); 
			buffer[i] = x & 0xFF; 
			buffer[i + 1] = (x >> 8) & 0xFF;
		}

		outputFile.write(buffer.data(), dataSize);

		outputFile.close();
		inputFile.close();
	}
};

class Creator {
public:
	virtual Wav* to_convert() = 0;
	virtual ~Creator() {};
};

class mute_Creator : public Creator {
public:
	int start;
	int finish;
	std::string fileName;
	mute_Creator(int a, int b, std::string c) {
		start = a;
		finish = b;
		fileName = c;
	}
	Wav* to_convert() {
		return new mute(start, finish, fileName);
	}
};

class mix_Creator : public Creator {
public:
	std::string second_file_name;
	std::string fileName;
	int start;
	int finish;

	mix_Creator(std::string a, std::string b, int c, int d) {
		second_file_name = a;
		fileName = b;
		start = c;
		finish = d;

	}
	Wav* to_convert() {
		return new mix(second_file_name, fileName, start, finish);
	}

};

class reverse_Creator : public Creator {
public:
	std::string fileName;
	reverse_Creator(std::string a) {
		fileName = a;
	}
	Wav* to_convert() {
		return new reverse(fileName);
	}
};

Creator* getFactoryForUserInput(std::ifstream& commands, int i, std::vector<std::string> files) {

	std::string current_command;
	commands >> current_command;
	if (i > 0) {
		std::ifstream tmp1 ("output.wav", std::ios::binary);
		std::ofstream tmp2 ("tmp2.wav", std::ios::binary);
		tmp2 << tmp1.rdbuf();
		tmp1.close();
		tmp2.close();
	}

	if (current_command == "mute") {
		int start;
		int finish;
		commands >> start >> finish;
		if (i == 0) {
			return new mute_Creator(start, finish, files[i]);
		}
		else {
			return new mute_Creator(start, finish, "tmp2.wav");
		}
	}
	else if (current_command == "reverse") {
		if (i == 0) {
			return new reverse_Creator(files[0]);
		}
		else {
			return new reverse_Creator("tmp2.wav");
		}
	}
	else if (current_command == "mix") {
		int start;
		int finish;
		int second_file_name;
		commands >> second_file_name >> start >> finish;
		if (i == 0) {
			return new mix_Creator(files[second_file_name], files[0], start, finish);
		}
		else {
			return new mix_Creator(files[second_file_name], "tmp2.wav", start, finish);
		}
	}
}
	
int main() {
	std::ifstream files_list;
	files_list.open("files_list.txt");

	std::vector<std::string> files;
	std::string line;

	while (std::getline(files_list, line)) {
		files.push_back(line);
	}

	std::ifstream commands;
	commands.open("commands.txt");

	int lineCount = 0;
	while (std::getline(commands, line)) {
		lineCount++;
	}
	commands.close();

	std::ifstream tmp;
	commands.open("commands.txt");

	for (int i = 0; i < lineCount; i++) {


		Creator* factory = getFactoryForUserInput(commands, i, files);
		Wav* converted = factory->to_convert();
		converted->converter();
	}
}
