#include <bits/stdc++.h>
using namespace std;

// 問題文の形式でvec値を出力
void print_vec(vector<int> vec) {
  cout << "[ ";
  for(int i = 0; i < vec.size(); i++) {
    cout << vec.at(i) << " ";
  }
  cout << "]" << endl;
}

// 変数名を読み取りイコールを読み飛ばす
string read_name() {
  string name, eq;
  cin >> name >> eq;
  return name;
}

// std::stoiが使えない為以下を使用
// 与えられる数値はすべて1桁
int mystoi(string s) {
  char tmp = s.at(0);
  return tmp -= 48;
}

// int式の項を1つ読み取る。
// 数字ならその値を返し、そうでないなら変数として解釈し変数の値を返す
// var_int : intの変数を保持するmap
int read_int(map<string, int> &var_int) {
  
  string term;
  cin >> term;

  if(isdigit(term.at(0))) {
    return mystoi(term);
  } else {
    return var_int[term];
  }
}

// int式全体を読み取って計算する
// var_int : intの変数を保持するmap
int calc_int(map<string, int> &var_int) {
  
  string ope = "";
  int result = 0;

  while(ope != ";" ) {
    int term = read_int(var_int);

    if(ope == "") {
      result = term;
    }
    if(ope == "+") {
      result += term;
    }
    if(ope == "-") {
      result -= term;
    }

    cin >> ope;
  }
  
  return result;
}

// vec値を読み取る
// 最初の"["は読み取ってある前提であることに注意
// var_int : intの変数を保持するmap
vector<int> read_vec_val(map<string, int> &var_int) {
  
  vector<int> result;
  string tmp = "";

  while(tmp != "]") {

    int val = read_int(var_int);  // 数値の読み込み
    result.push_back(val);  // 数値を追加

    cin >> tmp;  // ","or"]"が読み込まれる
  }

  return result;
}

// vec式の項を1つ読み取る
// vec値ならその値を返し、そうでないなら変数として解釈し変数の値を返す
// var_int : intの変数を保持するmap
// var_vec : vecの変数を保持するmap
vector<int> read_vec(map<string, int> &var_int, map<string, vector<int> > &var_vec) {
  
  string term;
  cin >> term;

  if(term == "[") {
    // vec値
    return read_vec_val(var_int);
  } else {
    // 変数
    return var_vec[term];
  }
}

// vec式全体を読み取って計算する
// var_int : intの変数を保持するmap
// var_vec : vecの変数を保持するmap
vector<int> calc_vec(map<string, int> &var_int, map<string, vector<int> > &var_vec) {
  
  string ope;
  vector<int> result;

  while(ope != ";") {

    vector<int> vec = read_vec(var_int, var_vec);

    if(ope == "") {
      result = vec;
    }
    if(ope == "+") {
      for(int i=0; i < result.size(); i++) {
        result.at(i) += vec.at(i);
      }
    }
    if(ope == "-") {
      for(int i=0; i < result.size(); i++) {
          result.at(i) -= vec.at(i);
      }
    }

    cin >> ope;
  }
  return result;
}

int main() {

  // 命令の行数を取得
  int N;
  cin >> N;

  map<string, int> var_int; // intの変数を管理するmap
  map<string, vector<int> > var_vec; // vectorの変数を管理するmap

  // 行数分の処理
  for (int i = 0; i < N; i++) {

    // 命令を受け取る
    string s;
    cin >> s;

    // int命令の処理
    if (s == "int") {
      // 変数名を読み取る
      string name = read_name();
      // 右辺の式を計算して変数に代入
      var_int[name] = calc_int(var_int);
    }

    // vec命令の処理
    if (s == "vec") {
      // 変数名を読み取る
      string name = read_name();
      // 右辺の式を計算して変数に代入
      var_vec[name] = calc_vec(var_int, var_vec);
    
    }

    // print_int命令の処理
    if (s == "print_int") {
      // 式を計算して出力
      cout << calc_int(var_int) << endl;
    }

    // print_vec命令の処理
    if (s == "print_vec") {
      // 式を計算して出力
      print_vec(calc_vec(var_int, var_vec));
    }
  }
}