class Solution {
public:

    bool check(string &p,int i){
        bool x=true;
        for(int j=i;j>=0;j--){
            if(p[j]!='*'){
                x=false;
            }
        }
        return x;
    }

    bool solve(int i, int j,string &s, string &p,vector<vector<int>>& dp){
        if(i<0 && j<0)return true;
        if(i<0 && j>=0){
            return check(p,j);
        }
        if(i>=0 && j<0)return false;
        if(dp[i][j]!=-1)return dp[i][j];

        if(s[i]==p[j] || p[j]=='?'){
            return dp[i][j]=solve(i-1,j-1,s,p,dp);
        }
        if(p[j]=='*'){
            return dp[i][j]=solve(i-1,j,s,p,dp)||solve(i,j-1,s,p,dp);
        }
        return dp[i][j]=false;
    }

    bool isMatch(string s, string p) {
        int n=s.size();
        int m=p.size();
        vector<vector<int>>dp(n+1,vector<int>(m+1,-1));
        return solve(n-1,m-1,s,p,dp);
    }
};
