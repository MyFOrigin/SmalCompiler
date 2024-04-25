#include "mylexicalanalysis.h"

myLexicalAnalysis::myLexicalAnalysis()
{

}
int myLexicalAnalysis::isDigit(char a)
{
    if(a-'0'>=0&&a-'0'<=9)
        return 1;
    else
        return 0;
}

int myLexicalAnalysis::isAlpha(char a)
{
    if((a>='a'&&a<='z')||(a>='A'&&a<='Z'))
        return 1;
    else
        return 0;
}

int myLexicalAnalysis::isboundary(char a)
{
    if(a=='{'||a=='}'||a=='('||a==')'||a==','||a==';')
        return 1;
    else
        return 0;
}

int myLexicalAnalysis::isoperator(char a)
{
    if(a=='='||a=='+'||a=='-'||a=='*'||a=='/'||a=='<'||a=='>'||a=='!')
        return 1;
    else
        return 0;
}

QVector<QString> myLexicalAnalysis::begin(char *s)
{
    QVector<QString> ans;
    int j;
    int len = strlen(s);
    int k = 0;
    while(k<len)
    {
        if(s[k]==' '||s[k]=='\n')
        {
            k++;
            continue;
        }
        else if(isDigit(s[k]))
        {
            char temp[123];
            j = 0;
            temp[j++] = s[k];
            k++;
            while(k<len&&isDigit(s[k]))
            {
                temp[j++] = s[k];
                k++;
            }
            temp[j] = '\0';
            ans.push_back("( integer , "+QString::fromUtf8(temp)+" )");
        }
        else if(isAlpha(s[k])||s[k]=='_')
        {
            char temp[123];
            j = 0;
            temp[j++] = s[k];
            k++;
            while(k<len&&(isAlpha(s[k])||isDigit(s[k])||s[k]=='_'))
            {
                temp[j++] = s[k];
                k++;
            }
            temp[j] = '\0';
            if(strcmp(temp, "if")==0||strcmp(temp, "main")==0||strcmp(temp, "else")==0||strcmp(temp, "for")==0||strcmp(temp, "while")==0||strcmp(temp, "int")==0)
            {
                ans.push_back("( keyword , "+QString::fromUtf8(temp)+" )");
            }
            else
            {
                ans.push_back("( identifier , "+QString::fromUtf8(temp)+" )");
            }
        }
        else if(isboundary(s[k]))
        {
            ans.push_back(QString("( boundary , %1 )").arg(s[k]));
            k++;
        }
        else if(isoperator(s[k]))
        {
            if(k<len-1)
            {
                k++;
                if(s[k]=='='&&(s[k-1]=='='||s[k-1]=='>'||s[k-1]=='<'||s[k-1]=='!'))
                {
                    ans.push_back(QString("( operator , %1%2 )").arg(s[k-1]).arg(s[k]));
                    k++;
                }
                else
                {
                    ans.push_back(QString("( operator , %1 )").arg(s[k-1]));
                }
            }
            else
            {
                ans.push_back(QString("( operator , %1 )").arg(s[k]));
                k++;
            }
        }
    }
    return ans;
}
