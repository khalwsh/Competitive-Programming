int TurningTurtlesGame (const string &s) {
    // Given a horizontal line of N coins: Head / Tail
    // Moves
    //  - pick any head and flip it to tail
    //  - optionally , flip any coin on left of your chosen coin
    // loser who can't make flips any more
    // observation:
    // if the kth position is a head it is equalivant to pile with size k (one base)
    int xoring = 0;
    for(int i = 1;i <= s.size();i++) {
        if(s[i - 1] == 'H')xoring ^= i - 1;
    }
    return xoring ? 1 : 2;
}