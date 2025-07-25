int computeGrundy(int x){
    if(x == 0) return 0;
    int msb = 31 - __builtin_clz(x);
    vector<int>moves;
    for(int i = 1;i < (1 << msb);i++){
        // moves array will have grundy of next possible positions
        moves.emplace_back(computeGrundy(x - i));
    }
    sort(moves.begin() , moves.end());
    moves.erase(unique(moves.begin() , moves.end()) , moves.end());

    int mex = 0;
    for(auto &m : moves){
        if(m == mex){
            mex++;
        }else if(m > mex){
            break;
        }
    }
    return ret = mex;
}