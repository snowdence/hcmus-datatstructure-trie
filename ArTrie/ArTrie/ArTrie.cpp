#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "ArTrieTree.h"
#include <map>
#include <fstream>
#include "ArHelper.h"
using namespace std;


bool read_dict(string file_name, ArTrieTree& tree) {
	std::ifstream in(file_name.c_str());
	if (!in)
	{
		std::cerr << "Cannot open the File : " << file_name << std::endl;
		return false;
	}
	std::string str;
	while (std::getline(in, str))
	{
		if (str.size() > 0) {
			tree.insert(str);
		}
	}
	in.close();
	return true;
}

bool read_file(string fileName, std::vector<char>& vec_str) {
	std::ifstream in(fileName.c_str());
	if (!in)
	{
		std::cerr << "Cannot open the File : " << fileName << std::endl;
		return false;
	}
	std::string str;
	while (std::getline(in, str, ' '))
	{
		if (str.size() > 1) {
			cout << "Error separated by a single space" << endl;
			return false;
		}

		if (str.size() == 1) {
			if (isalpha(str[0])){
				vec_str.push_back(tolower(str[0]));
			}
			else {
				cout << "Error, the character is not valid alphabet char" << endl;
				return false;
			}
		}
	}
	in.close();
	return true;
}

vector<string> filter_dict(ArTrieTree& trie_tree, vector<char>& iv) {
	vector<string>combine_str = ArHelper::combination(iv);
	vector<string>result;
	for (string str : combine_str) {
		if (trie_tree.search(str)) {
			result.push_back(str);
			//cout << str << endl;
		}
	}
	return result;
}
void output_file(string file, vector<string> result) {
	std::ofstream oss(file);

	if (!oss)
	{
		std::cerr << "Cannot open the File : " << file << std::endl;
	}
	oss << result.size() << endl;
	for (string& str : result) {
		oss << str << endl;
	}
	cout << "Success to write output file: " << file << endl;

	oss.close();
}


static void show_usage(std::string name)
{
	std::cerr << "Usage: <file_execute_name>.exe DictPath InputPath OuputPath"
		<< "Options:\n"
		<< "\tfile_execute_name.exe: Exe file\n"
		<< "\tDictPath: Path to the \"Dict.txt\" file\n"
		<< "\tInputPath: Path to the \"input.txt\" file\n"
		<< "\tOutputPath: Path to the \"output.txt\" file\n"
		<< "\t Sample: a.exe Dict.txt input.txt output.txt"
		<< std::endl;
}


int main(int argc, char* argv[]) {
	string input_file_name = "input.txt";
	string output_file_name = "output.txt";
	string dict_file_name = "Dict.txt";


	if (argc < 3) {
		show_usage(argv[0]);
		return 1;
	}
	dict_file_name = argv[1];
	input_file_name = argv[2];
	output_file_name = argv[3]; 

	vector<char> iv;
	ArTrieTree trie_tree;
	cout << endl;
	

	read_dict(dict_file_name, trie_tree);
	cout << "Size of dict: " << trie_tree.size() << endl;
	
	

	read_file(input_file_name, iv);

	sort(iv.begin(), iv.end(), greater<char>());
	cout << "Allow auto sort the input file " << endl;


	vector<string> result = filter_dict(trie_tree, iv);
	output_file(output_file_name, result);
	return 0;
}