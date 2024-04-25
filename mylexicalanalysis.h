#ifndef MYLEXICALANALYSIS_H
#define MYLEXICALANALYSIS_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <QString>
#include <string.h>
#include <QVector>

class myLexicalAnalysis
{
public:
    myLexicalAnalysis();
    int isDigit(char a);
    int isAlpha(char a);
    int isboundary(char a);
    int isoperator(char a);
    QVector<QString> begin(char *s);

};

#endif // MYLEXICALANALYSIS_H
