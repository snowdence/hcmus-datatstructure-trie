#define ALBT_SIZE 26
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>

using namespace std;

/// <summary>
/// Function to combine the input list for searching 
/// </summary>
class ArHelper
{
public:
    static void reCombination(vector<string>& vctSave, char* result, char* str, int count[], int lv, int size, int length)
    {
        if (lv == size)
        {
            return;
        }

        for (int i = 0; i < length; i++)
        {
            if (count[i] == 0)
            {
                continue;
            }

            count[i]--;

            result[lv] = str[i];

            if (lv >= 2)
            {
                string temp = "";
                for (int i = 0; i <= lv; i++)
                {
                    temp += result[i];
                }
                vctSave.push_back(temp);
            }

            reCombination(vctSave, result, str, count, lv + 1, size, length);
            count[i]++;
        }
    }

    //Preprocess to combine all case of v with lexi-order
    static vector<string> combination(vector<char> v)
    {
        map<char, int> map_letter;
        for (int i = 0; i < v.size(); i++)
        {
            if (map_letter.find(v[i]) != map_letter.end())
            {
                map_letter[v[i]] = map_letter[v[i]] + 1;
            }
            else
            {
                map_letter[v[i]] = 1;
            }
        }

        char* letters = new char[map_letter.size()];

        int* count = new int[map_letter.size()];
        char* result = new char[v.size()];

        map<char, int>::iterator it = map_letter.begin();
        int i = 0;
        for (it; it != map_letter.end(); it++)
        {
            letters[i] = (char)it->first;
            count[i] = (int)it->second;
            i++;
        }

        int length = map_letter.size();
        int size = v.size();
        vector<string> vctResult;
        reCombination(vctResult, result, letters, count,
            0, size, length);
        return vctResult;
    }
};

/// <summary>
/// The structure to represent a node in trie tree
/// </summary>
class ArTrieNode
{
protected:
    ArTrieNode* _child[ALBT_SIZE]; //keep the child with buffer of 26 letter (lowcase English alphabet)
    bool _end_flag; //flag to mark this node is end of a string

public:
    ArTrieNode()
    {
        _end_flag = false;
        for (int i = 0; i < ALBT_SIZE; i++)
        {
            _child[i] = nullptr;
        }
    }
    ~ArTrieNode()
    {
        for (int i = 0; i < ALBT_SIZE; i++)
        {
            delete[] _child[i];
        }
    }

    /// <summary>
    /// check this node don't have any child node
    /// </summary>
    /// <returns></returns>
    bool isEmpty()
    {
        for (int i = 0; i < ALBT_SIZE; i++)
            if (_child[i])
                return false;
        return true;
    }
    /// <summary>
    /// Setter for end flag
    /// </summary>
    /// <param name="flag"></param>
    void setEndFlag(bool flag)
    {
        this->_end_flag = flag;
    }
    /// <summary>
    /// return the end flag whether this node is end of some string
    /// </summary>
    /// <returns></returns>
    bool isEndWord()
    {
        return this->_end_flag;
    }

    ArTrieNode** getChild()
    {
        return _child;
    }

    /// <summary>
    /// Get child by index
    /// </summary>
    /// <param name="idx">index to get the data</param>
    /// <returns></returns>
    ArTrieNode* getChild(int idx)
    {
        if (idx < 0 || idx > ALBT_SIZE)
        {
            return nullptr;
        }
        return _child[idx];
    }
    bool setChild(int idx, ArTrieNode* val)
    {
        if (idx < 0 || idx > ALBT_SIZE)
        {
            return false;
        }
        _child[idx] = val;
        return true;
    }
};

/// <summary>
/// TRee structure provide the insert, remove, search feature for trie structure
/// </summary>
class ArTrieTree
{
private:
    ArTrieNode* _root; //root node
    int _count_dict = 0; //counter cache of this tree

public:
    ArTrieTree()
    {
        _count_dict = 0;
        _root = new ArTrieNode();
        cout << "ArTrieTree " << endl;
    }
    /// <summary>
    /// Receive the size of dict (number words) that 's represented by this tree
    /// </summary>
    /// <returns>int</returns>
    int size()
    {
        return _count_dict;
    }
    /// <summary>
    /// Insert a word to the trie tree
    /// </summary>
    /// <param name="key"></param>
    void insert(string key)
    {

        ArTrieNode* temp = this->getRoot();
        for (int i = 0; i < key.length(); i++)
        {
            int idx = key[i] - 'a';
            if (!temp->getChild(idx))
            {
                temp->setChild(idx, new ArTrieNode());
            }
            temp = temp->getChild(idx);
        }
        if (temp->isEndWord() == true)
        {
            //existed
        }
        else
        {
            _count_dict++;
            temp->setEndFlag(true);
        }
    }

    /// <summary>
    /// Search a key whether it 's existed in this tree 
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    bool search(string key)
    {
        ArTrieNode* temp = this->getRoot();
        for (int i = 0; i < key.length(); i++)
        {
            int idx = key[i] - 'a';
            if (!temp->getChild(idx))
            {
                return false;
            }

            temp = temp->getChild(idx);
        }
        return (temp != NULL && temp->isEndWord());
    }

    /// <summary>
    /// Remove a word of the tree
    /// </summary>
    /// <param name="node">the root node</param>
    /// <param name="key">the key word to remove</param>
    /// <param name="depth">init depth = 0 </param>
    /// <returns>The root node of removed tree</returns>
    ArTrieNode* remove(ArTrieNode* node, string key, int depth = 0)
    {
        if (!node)
            return nullptr;

        if (depth == key.size())
        {
            if (node->isEndWord())
            {
                node->setEndFlag(false);
            }
            if (node->isEmpty())
            {
                delete node;
                node = nullptr;
            }
            return node;
        }

        int idx = key[depth] - 'a';
        node->setChild(idx, this->remove(node->getChild(idx), key, depth + 1));

        if (node->isEmpty() && node->isEndWord() == false)
        {
            delete node;
            node = nullptr;
        }
        return node;
    }
    ArTrieNode* getRoot()
    {
        return _root;
    }
};

/// <summary>
/// Function to read the dictionary file and insert to tree
/// </summary>
/// <param name="file_name">file_name</param>
/// <param name="tree">trie_tree instance</param>
/// <returns>true if success/ false if file not existed or exception</returns>
bool read_dict(string file_name, ArTrieTree& tree)
{
    std::ifstream in(file_name.c_str());
    if (!in)
    {
        std::cerr << "Cannot open the File : " << file_name << std::endl;
        return false;
    }
    std::string str;
    while (std::getline(in, str))
    {
        if (str.size() > 0)
        {
            tree.insert(str);
        }
    }
    in.close();
    return true;
}

/// <summary>
/// Read file input and save to vector<char>
/// </summary>
/// <param name="fileName">input file name</param>
/// <param name="vec_str">input list (char)</param>
/// <returns>true if success and false if file or format 're not correct</returns>
bool read_file(string fileName, std::vector<char>& vec_str)
{
    std::ifstream in(fileName.c_str());
    if (!in)
    {
        std::cerr << "Cannot open the File : " << fileName << std::endl;
        return false;
    }
    std::string str;
    while (std::getline(in, str, ' '))
    {
        if (str.size() > 1)
        {
            cout << "Error separated by a single space" << endl;
            return false;
        }

        if (str.size() == 1)
        {
            if (isalpha(str[0]))
            {
                vec_str.push_back(tolower(str[0]));
            }
            else
            {
                cout << "Error, the character is not valid alphabet char" << endl;
                return false;
            }
        }
    }
    in.close();
    return true;
}

/// <summary>
/// Filter to get the result by search trie tree
/// </summary>
/// <param name="trie_tree"></param>
/// <param name="iv"></param>
/// <returns></returns>
vector<string> filter_dict(ArTrieTree& trie_tree, vector<char>& iv)
{
    vector<string> combine_str = ArHelper::combination(iv);
    vector<string> result;
    for (string str : combine_str)
    {
        if (trie_tree.search(str))
        {
            result.push_back(str);
            //cout << str << endl;
        }
    }
    return result;
}

/// <summary>
/// Write output to file
/// </summary>
/// <param name="file"></param>
/// <param name="result"></param>
void output_file(string file, vector<string> result)
{
    std::ofstream oss(file);

    if (!oss)
    {
        std::cerr << "Cannot open the File : " << file << std::endl;
    }
    oss << result.size() << endl;
    for (string& str : result)
    {
        oss << str << endl;
    }
    cout << "Success to write output file: " << file << endl;

    oss.close();
}

/// <summary>
/// Show the usage of this program
/// </summary>
/// <param name="name"></param>
static void show_usage(std::string name)
{
    std::cerr << "Usage: <file_execute_name>.exe DictPath InputPath OuputPath\n"
        << "Options:\n"
        << "\tfile_execute_name.exe: Exe file\n"
        << "\tDictPath: Path to the \"Dict.txt\" file\n"
        << "\tInputPath: Path to the \"input.txt\" file\n"
        << "\tOutputPath: Path to the \"output.txt\" file\n"
        << "\t Sample: a.exe Dict.txt input.txt output.txt"
        << std::endl;
}


/// <summary>
/// Main entry function
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char* argv[])
{
    string input_file_name = "input.txt";
    string output_file_name = "output.txt";
    string dict_file_name = "Dict.txt";

    if (argc < 3)
    {
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
