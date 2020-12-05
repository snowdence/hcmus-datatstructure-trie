#pragma once
#include "ArTrieNode.h"
#include <iostream>
using namespace std;
class ArTrieTree
{
private:
	ArTrieNode* _root;

public:
	ArTrieTree() {
		_root = new ArTrieNode();
		cout << "ARTrieTRee " << endl;
	}
	void insert(string key) {
		ArTrieNode* temp = this->getRoot();
		for (int i = 0; i < key.length(); i++) {
			int idx = key[i] - 'a'; 
			if (!temp->getChild(idx)) {
				temp->setChild(idx , new ArTrieNode());
			}
			temp = temp->getChild(idx);
		}
		temp->setEndFlag(true);
	}

	bool search(string key) {
		ArTrieNode* temp = this->getRoot();
		for (int i = 0; i < key.length(); i++)
		{
			int idx = key[i] - 'a';
			if (!temp->getChild(idx)) {
				return false;
			}
			
			temp = temp->getChild(idx);
		}
		return (temp != NULL && temp->isEndWord());
	}


	ArTrieNode* remove(ArTrieNode * node, string key, int depth = 0) {
		if (!node) return nullptr;
		
		if (depth == key.size()) {
			if (node->isEndWord()) {
				node->setEndFlag(false);
			}
			if (node->isEmpty()) {
				delete node;
				node= nullptr;
			}
			return node;
		}
		


		int idx = key[depth] - 'a';
		node->setChild(idx, this->remove(node->getChild(idx), key, depth + 1));
		
		if (node->isEmpty() && node->isEndWord() ==false) {
			delete node;
			node = nullptr;
		}
		return node;
	}
	ArTrieNode* getRoot() {
		return _root;
	}
	
	

};

