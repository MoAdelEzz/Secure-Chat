#pragma once
#include <iostream>
#include <fstream>
#include<string>
#include <stdlib.h>
#include <stdio.h>
#include <unordered_map>

using namespace std;

class FileParser
{
protected:
	unordered_map < string, string> indexer;
	static FileParser* instance;

	FileParser()
	{
		indexer.clear();
	}

	static string tillDelim(string phrase, char delim, int& offset)
	{
		string word = "";
		while (offset < phrase.size() && phrase[offset] != delim)
		{
			word += phrase[offset++];
		}
		return word;
	}

public:
	static FileParser* getParser()
	{
		if (instance == nullptr) instance = new FileParser();
		return instance;
	}

	void parseFile(string filepath)
	{
		string line = "";
		ifstream file(filepath);

		while (getline(file, line))
		{
			if (line.empty()) continue;
			int offset = 0;
			while (offset < line.size())
			{
				string key = tillDelim(line, ',', offset);
				string value = tillDelim(line, '\n', ++offset);
				indexer[key] = value;
			}
		}

		file.close();
	}

	vector<string> splitByDelim(string phrase, char delim)
	{
		vector<string> splitted;
		int offset = 0;
		while (offset < phrase.size())
		{
			splitted.push_back(tillDelim(phrase, delim, offset));
			offset++;
		}
		return splitted;
	}

	string getValueOf(string key)
	{
		if (indexer.find(key) != indexer.end()) return indexer[key];
		return "";
	}
};