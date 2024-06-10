/*
本实验目的是构建相等理论的DPLL(T)求解器，实现对无量词一阶逻辑--相等理论的求解。
输入格式:
第一行为2个整数n，m，n表示变元的个数，m表示命题子句个数（假设命题为CNF范式）。
接下来m行，每行为一个命题子句，每个子句由若干个元组构成，元组之间用逗号隔开，元组内部用空格隔开。一个元组代表一个原子命题，由三个整数构成，第一个整数表示正负号,1表示正数,-1表示负数，0表示子句结束，后两个整数表示变元的编号。
例如
3 3
1 1 2,-1 1 3,0
1 2 3,0
1 1 3,0
表示有3个变元，3个命题子句，意思是x1==x3并且x1==x2并且（x1==x2或x1!=x3）。
我们使用并查集来维护等价关系，对于CDCL返回的赋值，观察是否满足相等理论，如果不满足则添加约束，重新调用CDCL求解，如果满足则返回SAT。
*/

#include <iostream>
#include <vector>
#include <algorithm> 
#include <map> 
#include <numeric>
#include <tuple>
#include<fstream>
#include<cstring>
using namespace std;
#define N 100

struct dsu {

  vector<size_t> pa, size, sum;

  explicit dsu(size_t size_)
      : pa(size_ * 2), size(size_ * 2, 1), sum(size_ * 2) {
    iota(pa.begin(), pa.begin() + size_, size_);
    iota(pa.begin() + size_, pa.end(), size_);
    iota(sum.begin() + size_, sum.end(), 0);
  }

  void unite(size_t x, size_t y) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (size[x] < size[y]) swap(x, y);
    pa[y] = x;
    size[x] += size[y];
    sum[x] += sum[y];
  }


  size_t find(size_t x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }
};

int main(){
    int n, m;

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> n >> m;
    dsu d(n);
    vector<vector<tuple<int, int, int> > > clauses; // 存储子句, 子句中的元素是一个三元组，第一个元素表示正负号，1表示正，-1表示负，后两个元素表示变元的编号
    int atom[N][N]; // 存储原子命题与布尔变量的对应关系
    int cnt = 0; // atom[i][j]表示第i个变元与第j个变元的等价关系转换为布尔变量的编号，0表示没有，cnt表示当前原子命题的个数
    memset(atom, 0, sizeof(atom));
    for(int i = 0; i < m; i++){
        vector<tuple<int, int, int> > clause;
        while(true){
            int sign, x, y;
            cin >> sign >> x >> y;
            if(atom[x][y] == 0){
                atom[x][y] = atom[y][x] = ++cnt;
            }
            clause.push_back({sign, x, y});
            if(cin.get()!=',')
                break;
        }
        clauses.push_back(clause);
    }
    /*将公式处理为命题骨架，对每个原子，对应一个布尔变量，将命题骨架写入文件,文件格式与MiniSAT的格式一致，例如之前的例子
    1 2被编号为1，1 3被编号为2，2 3被编号为3，1 3被编号为4，那么文件内容为
    p cnf 3 4
    1 -2 0
    3 0
    4 0
    */
   //打开文件
    fstream fp;
    fp.open("skeleton.txt", ios::out);
    fp<<"p cnf "<<cnt<<" "<<clauses.size()<<"\n";

    for(int i = 0;i<clauses.size();i++){
        for(int j = 0;j<clauses[i].size();j++){
            int sign, x, y;
            tie(sign, x, y) = clauses[i][j];
            fp<<sign*atom[x][y]<<" ";
        }
            fp<<"0\n";
    }



    fp.close();


    return 0;

}
