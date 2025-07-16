class ManhattanDataStructure {
private:
    multiset<long long> setU, setV;
 
public:
    void insertPoint(long long x, long long y) {
        long long u = x + y;
        long long v = x - y;
        setU.insert(u);
        setV.insert(v);
    }
 
    bool deletePoint(long long x, long long y) {
        long long u = x + y;
        long long v = x - y;
 
        auto itU = setU.find(u);
        auto itV = setV.find(v);
 
        if (itU == setU.end() || itV == setV.end()) {
            return false;  // Point not found.
        }
 
        setU.erase(itU);
        setV.erase(itV);
        return true;
    }
 
    long long queryMaxManhattan() {
        if(setU.empty() || setV.empty()) return 0;
        long long maxU = *setU.rbegin();
        long long minU = *setU.begin();
        long long maxV = *setV.rbegin();
        long long minV = *setV.begin();
        return max(maxU - minU, maxV - minV);
    }
};