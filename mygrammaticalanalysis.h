#ifndef MYGRAMMATICALANALYSIS_H
#define MYGRAMMATICALANALYSIS_H

#include <QString>
#include <QVector>
#include <QDebug>
#include <iostream>

class binaryData
{
public:
    QString kind,value;
    binaryData(QString _kind,QString _value)
    {
        this->kind = _kind;
        this->value = _value;
    }
};

class myGrammaticalAnalysis
{
public:
    myGrammaticalAnalysis();
    void setBinaryData(QString _kind, QString _value);
    void clearBinaryData();
    QVector<QString> begin();
    void chengXu();
    void shengMIngXuLie();
    void _shengMingXuLie();
    void shengMingYuJu();
    void biaoShiFuBiao();
    void _biaoShiFuBiao();
    void yuJuXuLie();
    void _yuJuXuLie();
    void yuJu();
    void ifYuJu();
    void whileYuJu();
    void forYuJu();
    void fuHeYuJu();
    void fuZhiYuJu();
    void biaoDaShi();
    void buErBiaoDaShi();
    void _buErBiaoDaShi();
    void guanXiYunSuanFu();
    void suanShuBiaoDashi();
    void _suanShuBiaoDaShi();
    void xiang();
    void _xiang();
    void yinZi();
    void biaoShiFu();
    void _biaoShiFu();
    void wuFuHaoZhengShu();
    void _wuFuHaoZhengShu();
    void ziMu();
    void shuZi();
    void error();


private:
    QVector<binaryData> bData;
    QVector<QString> ans;
    int index, len;
};

#endif // MYGRAMMATICALANALYSIS_H
