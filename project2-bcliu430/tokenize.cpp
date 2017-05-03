#include <iostream>
#include <typeinfo>
#include <vector>

#include "tokenize.hpp"

Tokenize::Tokenize(){

}

Tokenize::~Tokenize(){

}
Tokenize::Tokenize(std::istream & expression){
    string str;
    char buf[4096];
    while(expression.read(buf,sizeof(buf)))
        str.append(buf, sizeof(buf));
    str.append(buf, expression.gcount());
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

    if( !parePair() ||token.size() <= 2 ||token.front() != "("){
        return false;
    }

    try{

      token.erase(token.begin());
      root = newnode(token.front());
//      cout << "tree root"<<root.getExpression().StringV << '\n' ;

      token.erase(token.begin());
      root = createAST(root);
      return (token.size() == 0);
      //	return false;
      //}
//      cout << "tree root"<<root.getExpression().StringV;
      //return true;
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

Expression Tokenize::postordertraversal(Expression expression) {
    for (int i = 0; i < expression.Leaf().size();i++){
      expression.setleaf(postordertraversal(expression.getleaf(i)),i);
    //  cout << "root" << root.getExpression().StringV;

    }
    string node = expression.getExpression().StringV;
        if (node == "begin") {
            expression = env.Begin(expression);
        } else if (node =="define") {
          expression = env.Define(expression);
        } else if (node == "if"){
          expression = env.IF(expression);
        } else if(node == "and"){
            expression = env.And(expression);
        } else if(node == "or"){
            expression = env.Or(expression);
        } else if(node == "not"){
            expression = env.Not(expression);
        } else if (node == "<" ||node == "<="||node == ">"||node == ">="||node == "="){
          expression = env.Comparison(expression);
        } else if (node == "+" || node == "*"){
          expression = env.m_ary(expression);
        } else if(node == "-"){
            expression = env.minus(expression);
        } else if(node == "/"){
            expression = env.division(expression);
        } else if (node == "pi"){
            expression = env.PI();
        } else if (node == "sin" || node == "cos"){
            expression = env.Trig(expression);
        } else if (node == "arctan"){
            expression = env.ATan(expression);
        } else if (node == "point"){
            expression =env.Point(expression);
        } else if (node == "line"){
            expression = env.Line(expression);
        } else if (node == "arc"){
            expression = env.Arc(expression);
        } else if(node == "draw"){
            expression = env.Draw(expression);
        } else if (node == "@"){
            throw InterpreterSemanticError("No Procedure");
        }
        /*
        else  throw InterpreterSemanticError("No Procedure");
        */
    return expression;
}



Expression Tokenize::newnode(string expres){
    atom_type dataType = DataType(expres);
    if(dataType == BoolT){
        if(expres == "True"){
          bool boolean = true;
          Expression newNode( boolean);
          return newNode;

        }
        if(expres == "False"){
          bool boolean = false;
          Expression newNode( boolean);
          return newNode;

        }
    }
    if(dataType == DoubleT){
      Expression newNode(stod(expres));
      return newNode;

    }
    if(dataType == StringT){
      Expression newNode(expres);
      return newNode;

    }

//    Expression newNode = new Expression();
//    return newNode;
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
            return NoneT;
        }
    }
    if(expression.size()>0){
        return StringT;
    }
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
    bool ok = (left == right && left != 0 && right !=0);

    return ok;
}


Expression Tokenize::getResult(){
  return root;
}
