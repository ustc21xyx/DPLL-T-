/*
实现SMT的CDCL部分，输入格式与MiniSAT相同，输出格式为
若无解，输出UNSAT
若有解，输出SAT，然后输出解，解为若干个1或-1，1表示对应的布尔变量为真，-1表示对应的布尔变量为假
伪代码:
function CDCL

2. while (true) do

3. while (BCP() = “conﬂict”) do

4. backtrack-level := Analyze-Conflict();

5. if backtrack-level < 0 then return “Unsatisﬁable”;

6. BackTrack(backtrack-level);

7. if ¬Decide() then return “Satisﬁable”;


启发式：
MiniSAT为每一个变量维护一个活动分值，用来衡量每个变量在推断新子句时的参与程度。如果一个子句c是由子句$c_1,...,c_n$推断出来的，
那么子句$c_1,...,c_n$中的每一个v的实例a，都会使得v增加一个inc。inc的大小在每一次冲突后都会乘以1.05，因此最近冲突的变量得分最高。

*/

#include <iostream>
#include <vector>

#define N 100

using namespace std;

int main(){
    freopen("skeleton.txt", "r", stdin);
    freopen("assignments.txt", "w", stdout);
    int n, m;
    cin >> n >> m;
    int assignments[N];
    vector<vector<int> > clauses;
    for(int i = 0; i < m; i++){
        vector<int> clause;
        while(true){
            int x;
            cin >> x;
            if(x == 0) break;
            clause.push_back(x);
        }
        clauses.push_back(clause);
    }

    return 0;
}