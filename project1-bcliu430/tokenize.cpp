#include <iostream>
#include <typeinfo>
#include <vector>

#include "tokenize.hpp"

Tokenize::Tokenize(){ }

Tokenize::~Tokenize(){ }

Tokenize::Tokenize(std::istream & express){
    string str;
    char buf[4096];
    while(express.read(buf,sizeof(buf)))
        str.append(buf, sizeof(buf));
    str.append(buf, express.gcount());
    token = setToken(str);
}
vector<string> Tokenize::setToken(string &expression){

    expression = deleteComments(expression);
    vector<string> token;
    string chartoStr, temp, tmp;
    for (unsigned int i = 0; i < expression.length(); i++){
        if(expression[i] =='(')
            temp.append(" ( ");
        else if(expression[i] == ')')
            temp.append( " ) ");
        else
            temp.append(string(1,expression[i]));
    }
    stringstream ss(temp);
    while ( ss >> tmp)
        token.push_back(tmp);
        if(ss.peek() == ' ')
            ss.ignore();

    return token;
}
vector<string> Tokenize::getToken(){ return token; }

string Tokenize::deleteComments(string & str){
  int semicol, newline;

  semicol = str.find(";");
  while(semicol != -1){
      newline = str.find("\n");
      while(newline < semicol){
          newline = str.find("\n", newline+1);
      }
      str.erase(semicol, newline-semicol+1);
      semicol = str.find(";");
  }

  return str;

}

bool Tokenize::AST(){
    if( parePair() == false)
        return false;
    if(token.size() <= 2)
        return false;

    try{
      token.erase(token.begin());
      root = newnode(token.front());
//      cout << "tree root"<<root.getExpression().StringV << '\n' ;

      token.erase(token.begin());
      root = createAST(root);
      if(token.size()>0)
      	return false;
//      cout << "tree root"<<root.getExpression().StringV;
      return true;
    }
    catch (const invalid_argument &err){
      cerr << err.what()<<endl;
      return false;
    }
}

Expression Tokenize::createAST(Expression expression){
//    cout << "token size"<<token.size() << '\n';
    if (token.size() == 0)
      return expression;

    if (token.front() == "("){
      token.erase(token.begin());
      Expression newchild = newnode(token.front());
      token.erase(token.begin());

      newchild = createAST(newchild);
      expression.pushleaf(newchild);

    }
    else if(token.front() == ")"){
      token.erase(token.begin());
//      cout << "tree end"<<expression.getExpression().StringV << '\n';
      return expression;
    }
    else {
        Expression newchild = newnode(token.front());
        token.erase(token.begin());
//        cout << token.front();

        expression.pushleaf(newchild);
        expression = createAST(expression);

        return expression;
    }

    expression = createAST(expression);
    return expression;
}

Expression Tokenize::postordertraversal(Expression root) {

    for (int i = 0; i < root.Leaf().size();i++){
      root.setleaf(postordertraversal(root.getleaf(i)),i);
    //  cout << "root" << root.getExpression().StringV;

    }

    string node = root.getExpression().StringV;
        if (node == "begin") {
            root = env.Begin(root);
        }
        else if (node =="define") {
          root = env.Define(root);
        }
        else if (node == "if"){
          root = env.IF(root);
        }
        else if(node == "and"){
            root = env.And(root);
        }
        else if(node == "or"){
            root = env.Or(root);
        }
        else if(node == "not"){
            root = env.Not(root);
        }
        else if (node == "<" ||node == "<="||node == ">"||node == ">="||node == "="){
          root = env.Comparison(root);
        }
        else if (node == "+" || node == "*"){
          root = env.m_ary(root);
        }
        else if(node == "-"){
            root = env.minus(root);
        }
        else if(node == "/"){
            root = env.division(root);
        }
        else if (node == "pi"){
            root = env.PI();
        }
        else if (node == "@"){
            throw InterpreterSemanticError("No Procedure");
        }
        /*
        else  throw InterpreterSemanticError("No Procedure");
        */
    return root;

}



Expression Tokenize::newnode(string expres){
    atom_type dataType = DataType(expres);
    if(dataType == BoolT){
        if(expres == "True"){
          bool boolean = true;
          Expression newNode( boolean);
          return newNode;

        }
        else{
          bool boolean = false;
          Expression newNode( boolean);
          return newNode;

        }
    }
    else if(dataType == DoubleT){
      Expression newNode(stod(expres));
      return newNode;

    }
    else if(dataType == StringT){
      Expression newNode(expres);
      return newNode;

    }

    Expression newNode = new Expression();
    return newNode;
}

atom_type Tokenize::DataType(string expression){
    if(expression == "True" || expression == "False")
        return BoolT;
    try{
        stod(expression);
        return DoubleT;
    }
    catch(invalid_argument &err){
    for (size_t i =0; i < expression.length(); i++){
        if(isdigit(expression[i])){
            for (int j = i; j < expression.length();j++)
              if(isdigit(expression[i]) == false)
                  return NoneT;
        }
    }
    if(expression.size()>0)
        return StringT;
    else
        return NoneT;
    }
}

bool Tokenize::parePair() {
    int left = 0, right = 0;
    for (unsigned int i = 0; i < token.size(); i++){
      if(token.at(i) == "("){
        left ++;
      }
      else if(token.at(i) == ")"){
        right++;
      }
    }
    if(left == right && left != 0 && right !=0)
      return true;
    else
      return false;
}


Expression Tokenize::getResult(){
  return root;
}
