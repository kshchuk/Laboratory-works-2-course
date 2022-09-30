/*
*
 *  Expression.cpp
 *
 *  Created on: Sep 30, 2022
 *
 *  Author:  Yaroslav Kishchuk
 *  Contact: Kshchuk@gmail.com
 *
 */


#include "Expression.h"

#include <string>

#include "doctest.h"


namespace expr
{
    /// <summary>
    /// Parses expression into RPN (reverse polish notation),
    ///  then fill it in binary tree
    /// </summary>
    /// <param name="expression"> - expression to handle</param>
    Expression::Expression(std::string expression) : BinaryTree()
    {
        std::vector<std::string> rpn;
        try {
            rpn = GenRpn(expression);
        }
        catch (std::runtime_error& e) {
            std::cout << "Runtime error occured:\n " << e.what();
        }

        std::reverse(rpn.begin(), rpn.end());
        std::vector<std::string>::iterator start = rpn.begin();
        GenSubTree(&this->root, start);
    }

    /// <summary>
    /// Delete previous data and create new Expression
    /// </summary>
    /// <param name="expression"></param>
    void Expression::LoadExpression(std::string expression) 
    {
        this->Clear(root);
        delete root;

        new (this) Expression(expression);
    }

    Expression::Expression(Node* expr) {
        this->root = expr;
    }

    std::string Expression::to_string(Node* node) const
    {
        if (root == nullptr)
            return std::string("");
        if (node == nullptr)
            node = root;

        if (isFunction(node->data)) {
            if (isUnaryFunction(node->data))
                return (node->data + '(' + to_string(node->right) + ')');
            else
                return ('(' + to_string(node->left) + ')' + node->data + '(' + to_string(node->right) + ')');
        }
        else
            return node->data;
    }

    void Expression::ProcessOperation(std::string function, 
        std::stack<std::string>& operators, std::vector<std::string>& rpn) const
    {
        int cur_function_priority = this->kFunctionsPriorities.at(function);
        while (!operators.empty())
        {
            int stack_function_priority = this->kFunctionsPriorities.at(operators.top());
            if (stack_function_priority <= cur_function_priority) {
                rpn.push_back(operators.top());
                operators.pop();
            }
            else
                break;
        }
        operators.push(function);
    }

    std::vector<std::string> Expression::GenRpn(std::string expression) const
    {
        std::stack <std::string> operations;
        std::vector<std::string> rpn;

        for (int i = 0; i < expression.size(); i++)
        {
            if (expression.find("log", i) == i) {
                ProcessOperation(std::string("log"), operations, rpn);
                i += 2;
            }
            else if (expression.find("ln", i) == i) {
                ProcessOperation(std::string("ln"), operations, rpn);
                i++;
            }
            else if (expression.find("sin", i) == i) {
                ProcessOperation(std::string("sin"), operations, rpn);
                i += 2;
            }
            else if (expression.find("cos", i) == i) {
                ProcessOperation(std::string("cos"), operations, rpn);
                i += 2;
            }
            else if (expression.find("tg", i) == i) {
                ProcessOperation(std::string("tg"), operations, rpn);
                i++;
            }
            else if (isalnum(expression[i]))
            {
                std::string var;
                while (isalnum(expression[i]) || expression[i] == '.' || expression[i] == ',')
                {
                    var.append(1, expression[i]);
                    i++;
                }
                i--;
                rpn.push_back(var);
            }
            else switch (expression[i])
            {
            case '(':
                operations.push(std::string(1, expression[i]));
                break;
            case ')':
                while (operations.empty() || operations.top() != "(")
                {
                    if (operations.empty())
                        throw std::runtime_error("Input error: Brackets correctness error\n");

                    rpn.push_back(operations.top());
                    operations.pop();
                }
                operations.pop();
                break;

            case '+':
            case '-':
            case '/':
            case '*':
            case '^':
                ProcessOperation(std::string(1, expression[i]), operations, rpn);
                if (i > 1)
                    if (expression[i] == '-' && expression[i - 1] == '(' && expression[i - 2] == '-')
                        rpn.push_back("0");
                break;
            default:
                throw std::runtime_error("Input error: Invalid symbol\n");
            }
        }

        while (!operations.empty())
        {
            if (operations.top() == "(" || operations.top() == ")")
                throw std::runtime_error("Input error: Brackets correctness error\n");

            rpn.push_back(operations.top());
            operations.pop();
        }
        return rpn;
    }

    bool Expression::isNumber(std::string str) const
    {
        for (auto i : str) {
            char end = *(str.end() - 1);
            if (!isdigit(i) && i != '.' && i != ',' && !(i == '-' && end != '-'))
                return false;
        }
        return true;
    }

    void Expression::CheckVar(std::string var)
    {
        if (std::find(vars.begin(), vars.end(), var) == vars.end())
            vars.push_back(var);
    }

    bool Expression::isFunction(std::string str) const
    {
        return kFunctionsPriorities.count(str) != 0;
    }

    bool Expression::isUnaryFunction(std::string str) const
    {
        if (!isFunction(str))
            return false;
        return kFunctionsPriorities.at(str) == 1;
    }

    void Expression::GenSubTree(Node** node, std::vector<std::string>::iterator& cur)
    {
        if (isFunction(*cur))
        {
            *node = new Node(std::string(*cur));
            std::vector<std::string>::iterator funct = cur;
            GenSubTree(&(*node)->right, ++cur);
            if (!isUnaryFunction(*funct))
                GenSubTree(&(*node)->left, ++cur);
        }
        else {
            *node = new Node(std::string(*cur));
            if (!isNumber(*cur))
                CheckVar(*cur);
        }
    }

    bool Expression::Compare(Node* node_1, Node* node_2) const
    {
        if (!node_1 && !node_2)
            return true;
        else if (!node_1 && node_2 || node_1 && !node_2)
            return false;
        else
            if (node_1->data == node_2->data ||
                isNumber(node_1->data) && isNumber(node_2->data) &&
                std::stod(node_1->data) == std::stod(node_2->data))
            {
                if (node_1->data == "+" || node_1->data == "*")
                    return (Compare(node_1->left, node_2->left) && Compare(node_1->right, node_2->right) ||
                        Compare(node_1->left, node_2->right) && Compare(node_1->right, node_2->left));
                else
                    if (isUnaryFunction(node_1->data)) {
                        return Compare(node_1->right, node_2->right);
                    }
                    else
                        return (Compare(node_1->left, node_2->left) && Compare(node_1->right, node_2->right));
            }
            else
                return false;
    }

    void Expression::dCos(std::string var, Node*& cos_node)
    {
        Node* mult = new Node(std::string("*"));

        Node* diff = new Node(std::string("-"));
        Node* dCos = new Node(std::string("sin"));
        dCos->right = Copy(cos_node->right);
        diff->left = new Node(std::string("0"));
        diff->right = dCos;
        mult->left = diff;
        mult->right = Differentiate(var, cos_node->right);
        *cos_node = *mult;
    }

    void Expression::dSin(std::string var, Node*& sin_node)
    {
        Node* mult = new Node(std::string("*"));
        Node* dSin = new Node(std::string("cos"));
        dSin->right = Copy(sin_node->right);
        mult->left = dSin;
        mult->right = Differentiate(var, sin_node->right);

        *sin_node = *mult;
    }

    void Expression::dLog(std::string var, Node*& log_node)
    {
        Node* mult = new Node(std::string("*"));

        Node* div = new Node(std::string("/"));
        Node* multInDenominator = new Node(std::string("*"));
        Node* lnA = new Node(std::string("ln"));
        lnA->right = Copy(log_node->left);
        multInDenominator->left = Copy(log_node->right);
        multInDenominator->right = lnA;
        div->left = new Node(std::string("1"));
        div->right = multInDenominator;

        mult->left = div;
        mult->right = Differentiate(var, log_node->right);

        *log_node = *mult;
    }

    void Expression::dPow(std::string var, Node*& pow_node)
    {
        Node* mult = new Node(std::string("*"));

        Node* dPow = new Node(std::string("*"));
        dPow->left = Copy(pow_node->right);
        Node* newPower = new Node(std::string("-"));
        newPower->left = Copy(pow_node->right);
        newPower->right = new Node(std::string("1"));
        Node* newPow = new Node(std::string("^"));
        newPow->left = Copy(pow_node->left);
        newPow->right = newPower;
        dPow->right = newPow;

        mult->left = dPow;
        mult->right = Differentiate(var, pow_node->left);

        *pow_node = *mult;
    }

    void Expression::dLn(std::string var, Node*& ln_node)
    {
        Node* mult = new Node(std::string("*"));

        Node* divide = new Node(std::string("/"));
        divide->left = new Node(std::string("1"));
        divide->right = Copy(ln_node->right);
        mult->left = divide;
        mult->right = Differentiate(var, ln_node->right);

        *ln_node = *mult;
    }

    void Expression::dTg(std::string var, Node*& tg_node)
    {
        Node* mult = new Node(std::string("*"));

        Node* divide = new Node(std::string("/"));
        Node* power = new Node(std::string("^"));
        Node* cos = new Node(std::string("cos"));
        cos->right = Copy(tg_node->right);
        power->left = cos;
        power->right = new Node(std::string("2"));
        divide->left = new Node(std::string("1"));
        divide->right = power;
        mult->left = divide;
        mult->right = Differentiate(var, tg_node->right);

        *tg_node = *mult;
    }

    void Expression::PrintVarList() const
    {
        for (auto var : vars)
            std::cout << var << ", ";
    }

    Expression::Node* Expression::Differentiate(std::string var, Node* node)
    {
        if (node == nullptr)
            node = root;

        if (node->data == var) {
            node->data = std::string("1");
        }
        else if (!isFunction(node->data)) {
            node->data = std::string("0");
        }
        else {
            if (node->data == "sin")
                dSin(var, node);
            else if (node->data == "cos")
                dCos(var, node);
            else if (node->data == "tg")
                dTg(var, node);
            else if (node->data == "ln")
                dLn(var, node);
            else if (node->data == "cos")
                dCos(var, node);
            else if (node->data == "log")
                dLog(var, node);
            else if (node->data == "^")
                dPow(var, node);
            else if (node->data == "*")
                dMult(var, node);
            else if (node->data == "/")
                dDiv(var, node);
            else if (node->data == "+" || node->data == "-") {
                Differentiate(var, node->left);
                Differentiate(var, node->right);
            }
        }
        this->Simplify(node);
        return node;
    }

    void Expression::dDiv(std::string var, Node*& div_node)
    {
        Node* div = new Node(std::string("/"));

        Node* numerator = new Node(std::string("-")), * denominator = new Node(std::string("^"));
        Node* toReduce = new Node(std::string("*")), * subtractor = new Node(std::string("*"));
        toReduce->left = Copy(div_node->left);
        subtractor->right = Copy(div_node->right);
        denominator->left = Copy(div_node->right);
        toReduce->right = Differentiate(var, div_node->right);
        subtractor->left = Differentiate(var, div_node->left);
        numerator->left = toReduce;
        numerator->right = subtractor;
        denominator->right = new Node(std::string("2"));
        div->left = numerator;
        div->right = denominator;

        *div_node = *div;
    }

    void Expression::dMult(std::string var, Node*& mult_node)
    {
        Node* sum = new Node(std::string("+"));

        Node* dod_1 = new Node(std::string("*")),
            * dod_2 = new Node(std::string("*"));

        dod_1->left = Copy(mult_node->left);
        dod_2->right = Copy(mult_node->right);
        dod_1->right = Differentiate(var, mult_node->right);
        dod_2->left = Differentiate(var, mult_node->left);
        sum->left = dod_1;
        sum->right = dod_2;

        *mult_node = *sum;
    }

    double Expression::CalculateFunction(std::string function, double arg_1, double arg_2) const
    {
        if (function == "+")
            return arg_1 + arg_2;
        else if (function == "-")
            return arg_1 - arg_2;
        else if (function == "*")
            return arg_1 * arg_2;
        else if (function == "/") {
            if (arg_2 == 0)
                throw std::overflow_error("Math error: Dividing by Zero");
            return arg_1 / arg_2;
        }
        else if (function == "^")
            return pow(arg_1, arg_2);
        else if (function == "ln") {
            if (arg_1 <= 0)
                throw std::overflow_error("Math error: Wrong function argument 'ln(a)', 'a' is less than or equal to Zorro\n");

            return log(arg_1);
        }
        else if (function == "log") {
            if (arg_1 <= 0 || arg_2 <= 0)
                throw std::overflow_error("Math error: Wrong function argument 'log(a, b)', 'a' or 'b' is less than or equal to Zero\n");
            if (arg_1 == 1)
                throw std::overflow_error("Math error: Wrong function argument 'log(a, b)', 'a' is equal to One\n");

            return (log(arg_2) / log(arg_1));
        }
        else if (function == "sin")
            return sin(arg_1);
        else if (function == "cos")
            return cos(arg_1);
        else if (function == "tg")
            return tan(arg_1);
        else return arg_1;
    }

    void Expression::Simplify(Node* node, Node* parent)
    {
        if (node == nullptr)
            node = root;

        try {
            if (isFunction(node->data))
            {
                if (isUnaryFunction(node->data)) {
                    SimplifyUnaryFunction(node, parent);
                }
                else {
                    SimplifyBinaryFunction(node, parent);
                }
            }
        }
        catch (std::overflow_error& e) {
            std::cout << "Overflow error occurred\n" << e.what();
        }
    }

    void Expression::SimplifyBinaryFunction(Node* node, Node* parent)
    {
        if (!isNumber(node->right->data)) {
            Simplify(node->right, node);
        }
        if (!isNumber(node->left->data)) {
            Simplify(node->left, node);
        }
        if (isNumber(node->right->data) && isNumber(node->left->data))
        {
            node->data = std::to_string(CalculateFunction(node->data,
                std::stod(node->left->data), std::stod(node->right->data)));
            Clear(node);
        }
        else {
            // Check all possible combinations to simplify expression

            if (isNumber(node->left->data) && std::stod(node->left->data) == 0)
            {
                if (node->data == "+") {
                    delete node->left;
                    DeleteNode(parent, node, node->right);
                }
                else if (node->data == "*" || node->data == "/" || node->data == "^") {
                    Clear(node);
                    node->data = std::string("0");
                }
            }
            else if (isNumber(node->right->data) && std::stod(node->right->data) == 0)
            {
                if (node->data == "+" || node->data == "-") {
                    delete node->right;
                    DeleteNode(parent, node, node->left);
                }
                else if (node->data == "*") {
                    Clear(node);
                    node->data = std::string("0");
                }
                else if (node->data == "^") {
                    Clear(node);
                    node->data = std::string("1");
                }
            }
            else if (isNumber(node->left->data) && std::stod(node->left->data) == 1)
            {
                if (node->data == "*") {
                    delete node->left;
                    DeleteNode(parent, node, node->right);
                }
                else if (node->data == "^") {
                    Clear(node);
                    node->data = std::string("1");
                }
            }
            else if (isNumber(node->right->data) && std::stod(node->right->data) == 1)
            {
                if (node->data == "*" || node->data == "/" || node->data == "^") {
                    delete node->right;
                    DeleteNode(parent, node, node->left);
                }
                else if (node->data == "log") {
                    Clear(node);
                    node->data = std::string("0");
                }
            }
            else
                if (!isNumber(node->left->data) && !isNumber(node->right->data) && node->data == "-") {
                    if (Compare(node->left, node->right)) {
                        Clear(node);
                        node->data = std::string("0");
                    }
                }
        }
    }
    
    void Expression::SimplifyUnaryFunction(Node* node, Node* parent)
    {
        if (!isNumber(node->right->data)) {
            Simplify(node->right, node);
        }
        if (isNumber(node->right->data)) {
            node->data = std::to_string(CalculateFunction(node->data, std::stod(node->right->data)));
            Clear(node);
        }
    }

    void Expression::ConvertVarsToNumbers(std::map<std::string, double> values, Node* node)
    {
        if (!node)
            return;

        if (!isNumber(node->data) && !isFunction(node->data)) // is variable
            node->data = std::to_string(values.at(node->data));

        ConvertVarsToNumbers(values, node->left);
        ConvertVarsToNumbers(values, node->right);
    }

    double Expression::CalculateExpression(std::map<std::string, double> variables_values) const
    {
        Expression* temp = new Expression(Copy(this->root));
        temp->ConvertVarsToNumbers(variables_values, temp->root);
        temp->Simplify();
        double res = std::stod(temp->root->data);
        temp->Clear(temp->root);
        delete temp;
        return res;
    }

#ifdef _DEBUG

    TEST_CASE("Conversation to string")
    {
        Expression e("10*a+b");
        CHECK(e.to_string() == "((10)*(a))+(b)");

        e.LoadExpression("x+10^y");
        CHECK(e.to_string() == "(x)+((10)^(y))");
    }

    TEST_CASE("Simplifie expression") {
        Expression e("(x-x)+2");
        e.Simplify();
        CHECK(stod(e.to_string()) == 2);

        e.LoadExpression("(11*2*x)^0");
        e.Simplify();
        CHECK(stod(e.to_string()) == 1);

        e.LoadExpression("1*(sin(x)+10*0)/1");
        e.Simplify();
        CHECK(e.to_string() == "sin(x)");
    }

    TEST_CASE("Differentiate expression")
    {
        Expression e("(x-x)+2");
        e.Differentiate(std::string("x"));
        CHECK(stod(e.to_string()) == 0);

        e.LoadExpression("x^2");
        e.Differentiate(std::string("x"));
        CHECK(e.to_string() == "(2)*(x)");

        e.LoadExpression("sin(x)");
        e.Differentiate(std::string("x"));
        CHECK(e.to_string() == "cos(x)");

        e.LoadExpression("x^ln(x)");
        e.Differentiate(std::string("x"));
        CHECK(e.to_string() == "(ln(x))*((x)^((ln(x))-(1)))");
    }

    TEST_CASE("Calculating expression")
    {
        Expression e("100*4+2");;
        CHECK(doctest::Approx(e.CalculateExpression()) == 402);

        e.LoadExpression("10^ln(4)");
        CHECK(doctest::Approx(e.CalculateExpression()) == 24.33853);

        e.LoadExpression("sin(x)");
        std::map<std::string, double> vals{ { std::string("x"), 11.0 } };
        CHECK(doctest::Approx(e.CalculateExpression(vals)) == -0.999992);

        e.LoadExpression("5^ln(124.73)+12/4-1/1");
        CHECK(doctest::Approx(e.CalculateExpression(vals)) == 2364.301);
    }

    TEST_CASE("Generate polish notation")
    {
        Expression e;
        std::vector<std::string> v;
        std::string s;

        v = e.GenRpn("x+y*10");
        s = "";
        for (auto elem : v)
            s += elem + " ";
        CHECK(s == std::string("x y 10 * + "));

        v = e.GenRpn(std::string("6*4/2^16+5/sin(10*1.2)^x"));
        s = "";
        for (auto elem : v)
            s += elem + " ";
        CHECK(s == std::string("6 4 * 2 16 ^ / 5 10 1.2 * sin x ^ / + "));

        CHECK_THROWS_AS(e.GenRpn("(x+y*10"), const std::runtime_error&);
    }

    TEST_CASE("Binary function simplification")
    {
        Expression e;

        BinaryTree<std::string>::Node* node1 = new BinaryTree<std::string>::Node("+");
        node1->left = new BinaryTree<std::string>::Node("10"),
        node1->right = new BinaryTree<std::string>::Node("-12");

            
        e.SimplifyBinaryFunction(node1);
        CHECK(stod(node1->data) == -2);
        
        node1->data = "^"; node1->left->data = "0"; node1->right->data = "999";
        e.SimplifyBinaryFunction(node1);
        CHECK(stod(node1->data) == 0);

        node1->data = "-"; node1->left->data = "x"; node1->right->data = "0";
        e.SimplifyBinaryFunction(node1);
        CHECK(e.root->data == "x");

        node1 = new BinaryTree<std::string>::Node(); node1->left = new BinaryTree<std::string>::Node();
        node1->right = new BinaryTree<std::string>::Node();
        node1->data = "log"; node1->left->data = "1"; node1->right->data = "10";
        CHECK_THROWS_AS(e.SimplifyBinaryFunction(node1), const std::overflow_error&);
    }

    TEST_CASE("Unary function simplification")
    {
        Expression e;

        BinaryTree<std::string>::Node* node1 = new BinaryTree<std::string>::Node("sin");
        node1->right = new BinaryTree<std::string>::Node("0");

        e.SimplifyUnaryFunction(node1);
        CHECK(stod(node1->data) == 0);

        node1->data = "cos"; node1->right->data = "0";
        e.SimplifyUnaryFunction(node1);
        CHECK(stod(node1->data) == 1);


        node1->data = "ln"; node1->right->data = "-5";
        CHECK_THROWS_AS(e.SimplifyUnaryFunction(node1), const std::overflow_error&);
    }

    TEST_CASE("Functions calculating")
    {
        Expression e;

        CHECK(e.CalculateFunction("^", 2, 10) == 1024);
        CHECK(e.CalculateFunction("sin", 0) == 0);
        CHECK(e.CalculateFunction("log", 3131, 1) == 0);
        CHECK_THROWS_AS(e.CalculateFunction("/", 0), const std::overflow_error&);
        CHECK_THROWS_AS(e.CalculateFunction("ln", -5), const std::overflow_error&);
    }

#endif // _DEBUG
}