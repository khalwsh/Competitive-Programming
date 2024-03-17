int SetBit(int n,int index){
    return n|(1ll<<index);
}

bool is_set(unsigned int number, int x) {
    return (number >> x) & 1;
}