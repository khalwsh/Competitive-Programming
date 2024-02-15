void SubMasksForMask(int mask){
    //vis sub masks of the mask in descending order
    for (int s=mask; s; s=(s-1)&mask){
        //do your work on s
    }
    // handle the empty set here
}
void MasksAndSubMasks(int n){
    for(int i=0;i<(1<<n);i++){
        SubMasksForMask(i);
    }
}