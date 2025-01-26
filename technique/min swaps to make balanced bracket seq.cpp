long swapCount(string chars) 
{
    
    // Stores total number of Left and 
    // Right brackets encountered
    int countLeft = 0, countRight = 0; 
    
    // swap stores the number of swaps 
    // required imbalance maintains 
    // the number of imbalance pair
    int swap = 0 , imbalance = 0; 
     
    for(int i = 0; i < chars.length(); i++) 
    {
        if (chars[i] == '[') 
        {
            
            // Increment count of Left bracket
            countLeft++; 
            
            if (imbalance > 0) 
            {
                
                // swaps count is last swap count + total 
                // number imbalanced brackets
                swap += imbalance; 
                
                // imbalance decremented by 1 as it solved
                // only one imbalance of Left and Right
                imbalance--;     
            }
        } 
        else if(chars[i] == ']' ) 
        {
            
            // Increment count of Right bracket
            countRight++; 
            
            // imbalance is reset to current difference 
            // between Left and Right brackets
            imbalance = (countRight - countLeft); 
        }
    }
    return swap;
}