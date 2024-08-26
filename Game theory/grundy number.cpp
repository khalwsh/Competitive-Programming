int computeGrundy(int x) {
    if (x == 0) return 0;
    vector<int> possibleMoves; // fill this array with all possible moves
    for (auto &i : possibleMoves) {
        possibleMoves.emplace_back(computeGrundy(i)); // Consider replacing x with new x
    }

    sort(possibleMoves.begin(), possibleMoves.end());
    possibleMoves.erase(unique(possibleMoves.begin(), possibleMoves.end()), possibleMoves.end());

    int mex = 0;
    for (int move : possibleMoves) {
        if (move == mex) {
            mex++;
        } else if (move > mex) {
            break;
        }
    }

    return mex;
}