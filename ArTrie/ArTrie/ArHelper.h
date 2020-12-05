#pragma once
#include <iostream> 
#include <map>
#include <vector>
#include <string>
using namespace std;

class ArHelper
{
public:
	ArHelper() {

	}

	static void reCombination(vector<string>& vctSave, char* result, char* str, int count[], int lv, int size, int length) {
		if (lv == size) {
			return;
		}
		
		for (int i = 0; i < length; i++)
		{
			if (count[i] == 0) {
				continue;
			}

			count[i]--;

			result[lv] = str[i];

			if (lv >= 2) {
				string temp = "";
				for (int i = 0; i <= lv; i++) {
					temp += result[i];
				}
				vctSave.push_back(temp);
			}

			reCombination(vctSave,result,  str, count, lv + 1, size, length);
			count[i]++; 
		}
	}

	static 	vector<string>  combination(vector<char> v) {
		map<char, int> map_letter;
		for (int i = 0; i < v.size(); i++) {
			if (map_letter.find(v[i]) != map_letter.end()) {
				map_letter[v[i]] = map_letter[v[i]] + 1;
			}
			else {
				map_letter[v[i]] = 1;
			}
		}

		char* letters = new char[map_letter.size()];

		int* count = new int[map_letter.size()];
		char* result = new char[v.size()];

		map<char, int>::iterator it = map_letter.begin();
		int i = 0;
		for (it; it != map_letter.end(); it++) {
			letters[i] = it->first;

			count[i] = it->second;

			i++;
		}

		int length = map_letter.size();
		int size = v.size();
		vector<string> vctResult;
		reCombination(vctResult,result, letters, count,
			0, size, length);
		return vctResult;
		

	}
};

