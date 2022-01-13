#include <iostream>
#include <stdexcept>
#include <vector>
#include <stack>
#include <map>

const std::string allOperators = "+-*/";
std::map<std::string, int> priority {
    {"+", 1},
    {"-", 1},
    {"*", 2},
    {"/", 2}
};

int operate (int a, int b, std::string c) {
  switch (c[0]) {
    case '+':
      return a+b;
    case '-':
      return a-b;
    case '*':
      return a*b;
    case '/':
      return a/b;
  }
}

std::vector<std::string> splitting (std::string s){
  std::vector<std::string> v;
  int i = 0;

  while (i < s.length()) {
    if (s[i] == ' ') {
      i++;
      continue;
    }
    if (allOperators.find(s[i]) == std::string::npos) {
      std::string number;
      if (std::isdigit(s[i])) {
        number.push_back(s[i]);
        i++;
        while (i != s.length() && std::isdigit(s[i])) {
          number.push_back(s[i]);
          i++;
        }
        v.push_back(number);
      } else {
        throw std::invalid_argument("Invalid expression input");
      }
    } else {
      v.emplace_back(1, s[i]);
      i++;
    }
  }
  return v;
}

std::vector<std::string> infixToPostfix(const std::vector<std::string> &v) {
  std::stack<std::string> st;
  std::vector<std::string> result;

  for(auto &element : v) {
    if (allOperators.find(element) == std::string::npos) {
      result.push_back(element);
    } else {
      while(!st.empty() && priority[element] <= priority[st.top()]) {
        result.push_back(st.top());
        st.pop();
      }
      st.push(element);
    }
  }
  while(!st.empty()) {
    result.push_back(st.top());
    st.pop();
  }
  return result;
}

int RPN(std::vector<std::string> &v) {
  std::stack<int> st;

  for(auto &element : v) {
    if (allOperators.find(element) == std::string::npos) {
      st.push(stoi(element));
    } else {
      int b = st.top(); st.pop();
      int a = st.top(); st.pop();
      st.push(operate(a, b, element));
    }
  }
  return st.top();
}

void print(const std::vector<std::string> &v) {
  for (auto &element : v) {
    std::cout << element << ' ';
  }
  std::cout << std::endl;
}

int main() {
  std::string input;
  std::vector<std::string> v;
  std::getline(std::cin, input);
  if (std::isdigit(input[input.length() - 1])) {
    v = infixToPostfix(splitting(input));
    print(v);
  } else {
    if (input.find(' ') == std::string::npos) {
      throw std::invalid_argument("Expression must contain spaces");
    } else {
      v = splitting(input);
    }
  }
  std::cout << RPN(v);
  return 0;
}