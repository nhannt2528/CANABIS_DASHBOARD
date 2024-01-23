#ifndef TESTCASE_H
#define TESTCASE_H

#include <QObject>

class testCase : public QObject
{
    Q_OBJECT
public:
    explicit testCase(QObject *parent = nullptr);

signals:
};

#endif // TESTCASE_H
