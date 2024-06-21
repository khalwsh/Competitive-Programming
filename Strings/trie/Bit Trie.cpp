struct Trie{
	Trie* arr[2];
	int freq;
	Trie(){
		freq = 0;
		for(auto &val:arr){
			val = nullptr;
		}
	}
	~Trie(){
		if(arr[0])delete arr[0];
		if(arr[1])delete arr[1];
	}
	void insert(ll x, int idx = 40) {
		if (idx == -1) {
			freq++;
			return;
		}
		bool temp = ((x & (1LL << idx)));
		if (arr[temp] == nullptr) {
			arr[temp] = new Trie();
		}
    	freq++; // Increment freq only if a node is traversed
    	arr[temp]->insert(x, idx - 1);
	}

	bool erase(ll x, int idx = 40) {
		if (idx == -1) {
			freq--;
			return true;
		}
		bool temp = ((x & (1LL << idx)));
		if (arr[temp] == nullptr) return false;
		if (arr[temp]->erase(x, idx - 1)) {
		    freq--; // Decrement freq only if a node is traversed
		    if (arr[temp]->freq == 0) {
	        	delete arr[temp];
	        	arr[temp] = nullptr;
	        }
		    return true;
		}
		return false;
	}

	ll Get(ll x , int idx = 40){
		if(idx == -1)return 0;
		bool temp = ((x & (1LL<<idx)));
		if(arr[!temp] != nullptr)return arr[!temp]->Get(x , idx - 1) | (1LL<<idx);
		else{
			assert(arr[temp]);
			return arr[temp]->Get(x , idx - 1);
		}
	}
};