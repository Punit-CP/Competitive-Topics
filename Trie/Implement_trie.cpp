//     https://leetcode.com/problems/implement-trie-prefix-tree/description/
// this is the besic implementation of trie ,,,,,,   ok Punit now you are boss in trie ...... don't leave any question of trie without solving it

class Trie {
public:
    struct TrieNode{
        bool isEndOfWord;
        TrieNode*children[26];
    };
    TrieNode* getNode(){
        TrieNode* newNode=new TrieNode();
        newNode->isEndOfWord=false;
        for(int i=0;i<26; i++){
            newNode->children[i]=NULL;
        }
        return newNode;
    }
    TrieNode* root;
    Trie() {
        root=getNode();
    }
    
    void insert(string word) {
        TrieNode*crawler=root;
        for(int i=0; i<word.size(); i++){
            char ch=word[i];
            int idx=ch-'a';
            if(crawler->children[idx]==NULL){
                crawler->children[idx]=getNode();
            }
            crawler=crawler->children[idx];
        }
        crawler->isEndOfWord=true;
    }
    
    bool search(string word) {
        TrieNode*crawler=root;
        for(int i=0; i<word.size(); i++){
            char ch=word[i];
            int idx=ch-'a';
            if(crawler->children[idx]==NULL){
                return false;
            }
            crawler=crawler->children[idx];
        }
        return (crawler->isEndOfWord==true);
    }
    
    bool startsWith(string prefix) {
        TrieNode*crawler=root;
        int i=0;
        for(i=0; i<prefix.size(); i++){
            char ch=prefix[i];
            int idx=ch-'a';
            if(crawler->children[idx]==NULL){
                return false;
            }
            crawler=crawler->children[idx];
        }
        return (i==prefix.size());
    }
};
