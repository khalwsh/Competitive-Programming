struct Trie {
    Trie *link[2]{};

    Trie(Trie *left = nullptr, Trie *right = nullptr) {
        link[0] = left, link[1] = right;
    }
};

Trie *getL(Trie *ver) {
    return (ver ? ver->link[0] : nullptr);
}

Trie *getR(Trie *ver) {
    return (ver ? ver->link[1] : nullptr);
}

const int N = 3e5 + 10;
Trie *roots[N]{};

Trie *insert(Trie *version, int x, int Bit = 29) {
    if (Bit == -1) {
        return version ? version : new Trie();
    }
    int bit = x >> Bit & 1;
    if (bit == 0) {
        Trie *right = getR(version);
        return new Trie(insert(getL(version), x, Bit - 1), right);
    } else {
        Trie *left = getL(version);
        return new Trie(left, insert(getR(version), x, Bit - 1));
    }
}

int MaxXor(Trie *version, int a, int Bit = 29) {
    if (Bit == -1) {
        return 0;
    }
    int bit = a >> Bit & 1;
    if (version->link[!bit]) return MaxXor(version->link[!bit], a, Bit - 1) | (1 << Bit);
    return MaxXor(version->link[bit], a, Bit - 1);
}

int MinXor(Trie *version, int a, int Bit = 29) {
    if (Bit == -1) return 0;
    int bit = a >> Bit & 1;
    if (version->link[bit])
        return MinXor(version->link[bit], a, Bit - 1);
    return MinXor(version->link[!bit], a, Bit - 1) | (1 << Bit);
}