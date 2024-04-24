#include "mygrammaticalanalysis.h"

myGrammaticalAnalysis::myGrammaticalAnalysis() : index(0),len(0)
{

}

void myGrammaticalAnalysis::setBinaryData(QString _kind, QString _value)
{
    binaryData _data(_kind,_value);
    this->bData.push_back(_data);
    return;
}
QVector<QString> myGrammaticalAnalysis::begin()
{
    len = this->bData.size();
    chengXu();
    return ans;
}

void myGrammaticalAnalysis::chengXu()
{
    qDebug() << 1;
    if(bData[index].value == "main" && bData[index+1].value == "("
        && bData[index+2].value == ")" && bData[index+3].value == "{")
    {
        ans.push_back("<程序> → <main关键字> () { <声明序列> <语句序列> }");
        index += 4;
        this->shengMIngXuLie();
        this->yuJuXuLie();
        if(bData[index].value == "}") index++;
        else this->error();
    }
    qDebug() << 1;
}
void myGrammaticalAnalysis::error()
{
    ans.push_back("出现错误!");
    qDebug() << this->bData[index].value << ";" << this->bData[index].kind;
    std::system("PAUSE");
    return;
}
void myGrammaticalAnalysis::shengMIngXuLie()
{
    qDebug() << 2;
    if(bData[index].value == "int")
    {
        ans.push_back("<声明序列> → <声明语句> <声明序列'>");
        this->shengMingYuJu();
        this->_shengMingXuLie();
    }else{
        ans.push_back("<声明序列> → <空>");
    }
    qDebug() << 2;
}



void myGrammaticalAnalysis::_shengMingXuLie()
{
    qDebug() << 3;
    if (bData[index].value == "int")
    {
        ans.push_back("<声明序列'> → <声明语句> <声明序列'>");
        this->shengMingYuJu();
        this->_shengMingXuLie();
    }
    else
    {
        ans.push_back("<声明序列'> → <空>");
    }
    qDebug() << 3;
}

void myGrammaticalAnalysis::shengMingYuJu()
{
    qDebug() << 4;
    if (bData[index].value == "int")
    {
        ans.push_back("<声明语句> → <int关键字> <标识符表> ;");
        index++; // 匹配 int
        this->biaoShiFuBiao();
        if (bData[index].value == ";") index++;
        else this->error();
    }
    else
    {
        this->error();
    }
    qDebug() << 4;
}


void myGrammaticalAnalysis::biaoShiFuBiao()
{
    qDebug() << 5;
    if (bData[index].kind == "identifier")
    {
        ans.push_back("<标识符表> → <标识符> <标识符表'>");
        this->biaoShiFu();
        this->_biaoShiFuBiao();
    }
    else
    {
        this->error();
    }
    qDebug() << 5;
}

void myGrammaticalAnalysis::_biaoShiFuBiao()
{
    qDebug() << 6;
    if (bData[index].value == ",")
    {
        ans.push_back("<标识符表'> → , <标识符> <标识符表'>");
        index++;
        this->biaoShiFu();
        this->_biaoShiFuBiao();
    }
    else
    {
        ans.push_back("<标识符表'>→<空>");
    }
    qDebug() << 6;
}

void myGrammaticalAnalysis::yuJuXuLie()
{
    qDebug() << 7;
    if (bData[index].kind == "keyword"  || bData[index].value == "{"
        || bData[index].kind == "identifier")
    {
        ans.push_back("<语句序列> → <语句> <语句序列'>");
        this->yuJu();
        this->_yuJuXuLie();
    }
    else
    {
        ans.push_back("<语句序列> → <空>");
    }
    qDebug() << 7;
}

void myGrammaticalAnalysis::_yuJuXuLie()
{
    qDebug() << 8;
    if (bData[index].kind == "keyword"  || bData[index].value == "{"
        || bData[index].kind == "identifier")
    {
        ans.push_back("<语句序列'> → <语句> <语句序列'>");
        this->yuJu();
        this->_yuJuXuLie();
    }
    else
    {
        ans.push_back("<语句序列'> → <空>");
    }
    qDebug() << 8;
}



void myGrammaticalAnalysis::yuJu()
{
    qDebug() << 9;
    if (bData[index].value == "if")
        this->ifYuJu();
    else if (bData[index].value == "while")
        this->whileYuJu();
    else if (bData[index].value == "for")
        this->forYuJu();
    else if (bData[index].value == "{")
        this->fuHeYuJu();
    else if (bData[index].kind == "identifier")
        this->fuZhiYuJu();
    else
        this->error();
    qDebug() << 9;
}

void myGrammaticalAnalysis::ifYuJu()
{
    qDebug() << 10;
    if (bData[index].value == "if" )
    {
        ans.push_back("<if语句> → <if关键字> ( <表达式> ) <复合语句>");
        index++; // 匹配 if 关键字
        if (bData[index].value == "(") index++;
        else this->error();
        this->biaoDaShi();
        if (bData[index].value == ")") index++;
        else this->error();
        this->fuHeYuJu();
    }
    else
    {
        this->error();
    }
    qDebug() << 10;
}

void myGrammaticalAnalysis::whileYuJu()
{
    qDebug() << 11;
    if (bData[index].value == "while")
    {
        ans.push_back("<while语句> → <while关键字> ( <表达式> ) <复合语句>");
        index++; // 匹配 while 关键字
        if (bData[index].value == "(") index++;
        else this->error();
        this->biaoDaShi();
        if (bData[index].value == ")") index++;
        else this->error();
        this->fuHeYuJu();
    }
    else
    {
        this->error();
    }
    qDebug() << 11;
}

void myGrammaticalAnalysis::forYuJu()
{
    qDebug() << 12;
    if (bData[index].value == "for")
    {
        ans.push_back("<for语句> → <for关键字> ( <表达式> ; <表达式> ; <表达式> ) <复合语句>");
        index++; // 匹配 for 关键字
        if (bData[index].value == "(") index++;
        else this->error();
        this->biaoDaShi();
        if (bData[index].value == ";") index++;
        else this->error();
        this->biaoDaShi();
        if (bData[index].value == ";") index++;
        else this->error();
        this->biaoDaShi();
        if (bData[index].value == ")") index++;
        else this->error();
        this->fuHeYuJu();
    }
    else
    {
        this->error();
    }
    qDebug() << 12;
}

void myGrammaticalAnalysis::fuHeYuJu()
{
    qDebug() << 13;
    if (bData[index].value == "{")
    {
        ans.push_back("<复合语句> → { <语句序列> }");
        index++; // 匹配 {
        this->yuJuXuLie();
        if (bData[index].value == "}") index++;
        else this->error();
    }
    else
    {
        this->error();
    }
    qDebug() << 13;
}

void myGrammaticalAnalysis::fuZhiYuJu()
{
    qDebug() << 14;
    if (bData[index].kind == "identifier")
    {
        ans.push_back("<赋值语句> → <表达式> ;");
        this->biaoDaShi();
        if (bData[index].value == ";") index++;
        else this->error();
    }
    else
    {
        this->error();
    }
    qDebug() << 14;
}

void myGrammaticalAnalysis::biaoDaShi()
{
    qDebug() << 15;
    if ( bData[index-1].value == "(" &&  bData[index-2].value == "if")
    {
        ans.push_back("<表达式> → <布尔表达式>");
        this->buErBiaoDaShi();
    }
    else if ( bData[index-1].value == "(" &&  bData[index-2].value == "while")
    {
        ans.push_back("<表达式> → <布尔表达式>");
        this->buErBiaoDaShi();
    }
    else if ( bData[index-1].value == "(" &&  bData[index-2].value == "for")
    {
        ans.push_back("<表达式> → <布尔表达式>");
        this->buErBiaoDaShi();
    }
    else if (((bData[index].value[0] >= 'a' && bData[index].value[0] <= 'z') ||
             (bData[index].value[0] >= 'A' && bData[index].value[0] <= 'Z') ||
                (bData[index].value[0] >= '0' && bData[index].value[0] <= '9'))
               && bData[index+1].value == "=")
    {
        ans.push_back("<表达式> → <标识符> = <算数表达式>");
        this->biaoShiFu();
        if (bData[index].value == "=") index++;
        else this->error();
        this->suanShuBiaoDashi();
    }
    else
    {
        this->error();
    }
    qDebug() << 15;
}



void myGrammaticalAnalysis::suanShuBiaoDashi()
{
    qDebug() << 16;
    if (bData[index].kind == "identifier" || bData[index].kind == "integer" || bData[index].value == "(")
    {
        ans.push_back("<算数表达式> → <项> <算数表达式'>");
        this->xiang();
        this->_suanShuBiaoDaShi();
    }
    else
    {
        this->error();
    }
    qDebug() << 16;
}

void myGrammaticalAnalysis::_suanShuBiaoDaShi()
{
    qDebug() << 17;
    if (bData[index].value == "+")
    {
        ans.push_back("<算数表达式'> → + <项> <算数表达式'>");
        index++;
        this->xiang();
        this->_suanShuBiaoDaShi();
    }
    else if ( bData[index].value == "-") {
        ans.push_back("<算数表达式'> → - <项> <算数表达式'>");
        index++;
        this->xiang();
        this->_suanShuBiaoDaShi();
    }
    else
    {
        ans.push_back("<算数表达式'> → <空>");
    }
    qDebug() << 17;
}

void myGrammaticalAnalysis::xiang()
{
    qDebug() << 18;
    if (bData[index].kind == "identifier" || bData[index].kind == "integer" || bData[index].value == "(")
    {
        ans.push_back("<项> → <因子> <项'>");
        this->yinZi();
        this->_xiang();
    }
    else
    {
        this->error();
    }
    qDebug() << 18;
}

void myGrammaticalAnalysis::_xiang()
{
    qDebug() << 19;
    if (bData[index].value == "*" )
    {
        ans.push_back("<项'> → * <因子> <项'>");
        index++;
        this->yinZi();
        this->_xiang();
    }
    else if (bData[index].value == "/")
    {
        ans.push_back("<项'> → / <因子> <项'>");
        index++;
        this->yinZi();
        this->_xiang();
    }
    else
    {
        ans.push_back("<项'> → <空>");
    }
    qDebug() << 19;
}

void myGrammaticalAnalysis::buErBiaoDaShi()
{
    qDebug() << 20;
    if (bData[index].kind == "identifier" || bData[index].kind == "integer")
    {
        ans.push_back("<布尔表达式> → <算数表达式> <布尔表达式'>");
        this->suanShuBiaoDashi();
        this->_buErBiaoDaShi();
    }
    else
    {
        this->error();
    }
    qDebug() << 20;
}

void myGrammaticalAnalysis::_buErBiaoDaShi()
{
    qDebug() << 21;
    if (bData[index].value == ">" || bData[index].value == "<"
        || bData[index].value == ">=" || bData[index].value == "<="
        || bData[index].value == "==" || bData[index].value == "!=")
    {
        ans.push_back("<布尔表达式'> → <关系运算符> <算数表达式>");
        this->guanXiYunSuanFu();
        this->suanShuBiaoDashi();
    }
    else
    {
        ans.push_back("<布尔表达式'> → 空");
    }
    qDebug() << 21;
}


void myGrammaticalAnalysis::guanXiYunSuanFu()
{
    qDebug() << 22;
    if (bData[index].value == ">")
    {
        ans.push_back("<关系运算符> → >");
        index++;
    }
    if (bData[index].value == "<")
    {
        ans.push_back("<关系运算符> → <");
        index++;
    }
    if (bData[index].value == ">=" )
    {
        ans.push_back("<关系运算符> → >=");
        index++;
    }
    if (bData[index].value == "<=")
    {
        ans.push_back("<关系运算符> → <=");
        index++;
    }
    if (bData[index].value == "==")
    {
        ans.push_back("<关系运算符> → ==");
        index++;
    }
    if ( bData[index].value == "!=")
    {
        ans.push_back("<关系运算符> → !=");
        index++;
    }

    else
    {
        //ans.push_back("<关系运算符> → 空");
    }
    /*
    else
    {
        this->error();
    }
*/
    qDebug() << 22;
}

void myGrammaticalAnalysis::ziMu()
{
    qDebug() << 23;
    if (bData[index].kind == "identifier")
    {
        ans.push_back(QString("<字母> → %1 ").arg(bData[index].value));
        index++;
    }
    else
    {
        this->error();
    }
    qDebug() << 23;
}

void myGrammaticalAnalysis::shuZi()
{
    qDebug() << 24;
    if (bData[index].kind == "integer")
    {
        ans.push_back(QString("<数字> → %1 ").arg(bData[index].value));
        index++;
    }
    else
    {
        this->error();
    }
    qDebug() << 24;
}

void myGrammaticalAnalysis::wuFuHaoZhengShu()
{
    qDebug() << 25;
    if (bData[index].kind == "integer")
    {
        ans.push_back("<无符号整数> → <数字> <无符号整数'>");
        this->shuZi();  // 匹配数字
        this->_wuFuHaoZhengShu();
    }
    else
    {
        this->error();
    }
    qDebug() << 25;
}

void myGrammaticalAnalysis::_wuFuHaoZhengShu()
{
    qDebug() << 26;
    if (bData[index].kind == "integer")
    {
        ans.push_back("<无符号整数'> → <数字> <无符号整数'>");
        this->shuZi();  // 匹配数字
        this->_wuFuHaoZhengShu();
    }
    else
    {
        ans.push_back("<无符号整数'> → <空>");
    }
    qDebug() << 26;
}
void myGrammaticalAnalysis::yinZi()
{
    qDebug() << 27;
    if (bData[index].kind == "identifier")
    {
        ans.push_back("<因子> → <标识符>");
        this->biaoShiFu();
    }
    else if (bData[index].kind == "integer")
    {
        ans.push_back("<因子> → <无符号整数>");
        this->wuFuHaoZhengShu();
    }
    else if (bData[index].value == "(")
    {
        ans.push_back("<因子> → ( <算数表达式> )");
        index++; // Match "("
        this->suanShuBiaoDashi();
        if (bData[index].value == ")") index++; // Match ")"
        else this->error();
    }
    else
    {
        this->error();
    }
    qDebug() << 27;
}


void myGrammaticalAnalysis::biaoShiFu()
{
    qDebug() << 28;
    if (bData[index].kind == "identifier")
    {
        ans.push_back("<标识符> → <字母> <标识符'>");
        this->ziMu();
        this->_biaoShiFu();
    }
    else
    {
        this->error();
    }
    qDebug() << 28;
}

void myGrammaticalAnalysis::_biaoShiFu()
{
    qDebug() << 29;
    if ((bData[index].value[0] >= '0' && bData[index].value[0] <= '9'))
    {
        ans.push_back("<标识符'> → <数字> <标识符'>");
        this->shuZi();
        this->_biaoShiFu();
    }
    else if ((bData[index].value[0] >= 'a' && bData[index].value[0] <= 'z') ||
             (bData[index].value[0] >= 'A' && bData[index].value[0] <= 'Z'))
    {
        ans.push_back("<标识符'> → <字母> <标识符'>");
        this->ziMu();
        this->_biaoShiFu();
    }
    else
    {
        ans.push_back("<标识符'> → <空>");
    }
    qDebug() << 29;
}

void myGrammaticalAnalysis::clearBinaryData()
{
    this->bData.clear();
    this->index = 0;
    this->ans.clear();
}



