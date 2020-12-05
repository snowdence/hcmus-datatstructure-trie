#pragma once
#include "ArCommon.h"
class ArTrieNode
{
protected:
	ArTrieNode* _child[ALBT_SIZE];
	bool _end_flag;
public:
	ArTrieNode() {
		_end_flag = false;
		for (int i = 0; i < ALBT_SIZE; i++) {
			_child[i]= nullptr; 
		}
	}
	~ArTrieNode() {
		delete[] _child;
	}
	
	bool isEmpty() {
		for (int i = 0; i < ALBT_SIZE; i++)
			if (_child[i])
				return false;
		return true;
	}
	void setEndFlag(bool flag) {
		this->_end_flag = flag;
	}
	
	bool isEndWord() {
		return this->_end_flag;
	}
	ArTrieNode** getChild() {
		return _child;
	}
	ArTrieNode* getChild(int idx) {
		if (idx <0 || idx > ALBT_SIZE) {
			return nullptr;
		}
		return _child[idx];
	}
	bool setChild(int idx, ArTrieNode *val) {
		if (idx <0 || idx > ALBT_SIZE) {
			return false;
		}
		_child[idx] = val;
		return true;
	}
};

