#include<iostream>
#include<vector>
#include<string>

using namespace std;


class Solution{
public:
    vector<int> say;
    string look_and_say(string look,int steps){
        if(steps <= 1){
            return look;
        }
        int len = look.length();
        char tmp = look[0];
        int cnt = 0;
        say.clear();
        for(int i = 0; i < len; i++){
            if(tmp != look[i]){
                say.push_back(cnt);
                say.push_back(tmp - '0');
                cnt = 0;
            }
            tmp = look[i];
            cnt++;
            //cout << look[i];
        }
        say.push_back(cnt);
        say.push_back(tmp - '0');
        look = "";
        for(int i = 0; i < say.size(); i++){
            look+=to_string(say[i]);
        }
        return look_and_say(look,steps-1);
    }
};

int main(){
    Solution s;
    int N = 4;
    cout << s.look_and_say("1",N) << endl;
}
