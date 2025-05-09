//     https://leetcode.com/problems/implement-trie-prefix-tree/description/
// this is the besic implementation of trie ,,,,,,   ok Punit now you are boss in trie ...... don't leave any question of trie without solving it

class TrieNode {
public:
    TrieNode* child[26];
    bool isWord;
    int wordCount;
    int prefixCount;

    TrieNode() {
        isWord = false;
        wordCount = 0;
        prefixCount = 0;
        for (int i = 0; i < 26; ++i) {
            child[i] = nullptr;
        }
    }
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!node->child[idx]) {
                node->child[idx] = new TrieNode();
            }
            node = node->child[idx];
            node->prefixCount++;
        }
        node->isWord = true;
        node->wordCount++;
    }

    bool search(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!node->child[idx]) {
                return false;
            }
            node = node->child[idx];
        }
        return node->isWord;
    }

    bool startsWith(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (!node->child[idx]) {
                return false;
            }
            node = node->child[idx];
        }
        return true;
    }

    int countWordsEqualTo(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!node->child[idx]) {
                return 0;
            }
            node = node->child[idx];
        }
        return node->wordCount;
    }

    int countWordsStartingWith(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (!node->child[idx]) {
                return 0;
            }
            node = node->child[idx];
        }
        return node->prefixCount;
    }

    void erase(const string& word) {
        if (!search(word)) {
            return;
        }
        TrieNode* node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            node = node->child[idx];
            node->prefixCount--;
        }
        node->wordCount--;
        if (node->wordCount == 0) {
            node->isWord = false;
        }
    }
};
