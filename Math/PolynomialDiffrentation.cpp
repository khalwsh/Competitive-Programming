void handle(string &temp,string &ans) {
    string cof;
    int ind = -1;
    for(int i=0;i<temp.size();i++){
        if(temp[i]=='x'){
            ind = i;break;
        }
        cof += temp[i];
    }
    if(ind==-1)return;
    string deg;
    for(int i = ind+1;i<temp.size();i++){
        deg += temp[i];
    }
    if(deg.empty() && cof.empty()){
        ans += '1';
        return;
    }
    if(deg.empty()){
        ans+=cof;
        return;
    }
    if(cof.empty()){
        ans += deg;
        if(deg=="1")return;
        ans+='x';
        if(deg!="2")ans+= to_string(stoll(deg) - 1);
        return;
    }
    ans += to_string(stoll(cof) * stoll(deg));
    if(deg=="1")return;
    ans+='x';
    if(deg!="2")ans+= to_string(stoll(deg) - 1);
}
string PolynomialDifferentiation(string &s){
    //the format of the Polynomial is axb-cxd+kxl  : where the powers is sorted decreasing and if the cof or power is 1 doesn't be written and if power is 0 the x doesn't exist
    string temp;
    if(count(s.begin(),s.end(),'x')==0){
        return "0";
    }
    string ans;
    for(auto &val:s){
        if(val=='-'||val=='+'){
            handle(temp,ans);
            ans+=val;
            temp.clear();
            continue;
        }
        temp+=val;
    }
    handle(temp,ans);
    while(ans.back() == '+' ||ans.back() == '-')ans.pop_back();
    return ans;
}