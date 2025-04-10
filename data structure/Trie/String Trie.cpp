struct Trie {
	Trie* arr[26] = {nullptr};
	int lst = 0;
	int st = 0;

	Trie() {
		for (int i = 0; i < 26; ++i) {
			arr[i] = nullptr;
		}
		lst = 0;
		st = 0;
	}

	~Trie() {
		for (int i = 0; i < 26; ++i) {
			if (arr[i] != nullptr) {
				delete arr[i];
				arr[i] = nullptr;
			}
		}
	}

	void insert(const string &word, int idx = 0) {
		if (idx == word.size()) {
			lst++;
			st++;
			return;
		}
		int ch = word[idx] - 'a';
		if (arr[ch] == nullptr) {
			arr[ch] = new Trie();
		}
		if(idx!=0)st++;
		arr[ch]->insert(word, idx + 1);
	}

	int count_equal(const string &word, int idx = 0) const {
		if (idx == word.size()) {
			return lst;
		}
		int ch = word[idx] - 'a';
		if (arr[ch] == nullptr) {
			return 0;
		}
		return arr[ch]->count_equal(word, idx + 1);
	}

	int count_prefix(const string &word, int idx = 0) const {
		if (idx == word.size()) {
			return st;
		}
		int ch = word[idx] - 'a';
		if (arr[ch] == nullptr) {
			return 0;
		}
		return arr[ch]->count_prefix(word, idx + 1);
	}

	bool erase(const string &word, int idx = 0) {
		if (idx == word.size()) {
			lst--;
			st--;
			return true;
		}
		int ch = word[idx] - 'a';
		if (arr[ch] == nullptr) {
			return false;
		}
		if (!arr[ch]->erase(word, idx + 1)) {
			return false;
		}
		if(idx!=0) st--;
		if (arr[ch]->st == 0) {
			delete arr[ch];
			arr[ch] = nullptr;
		}
		return true;
	}
	bool GetProperPrefixTo(const string &s , string &temp , vector<string>&ans , int idx = 0){
		if(s.size() > idx){
			int ch = s[idx] - 'a';
			if(arr[ch] == nullptr)return false;
			temp += s[idx];
			return arr[ch]->GetProperPrefixTo(s , temp,ans, idx + 1);
		}else{
			for(int i = 0;idx != s.size() && i<lst;i++){
				ans.emplace_back(temp);
				break;
			}
			for(int i = 0;i<26;i++){
				if(arr[i]){
					temp += (char)(i + 'a');
					bool x = arr[i]->GetProperPrefixTo(s , temp ,ans, idx + 1);
					temp.pop_back();
				}
			}
			return true;
		}
	}
};