#ifndef GLOBAL_H
#define GLOBAL_H

#include <QSqlDatabase>

class Global
{
private:
    Global();

public:
    ~Global();
    static Global *i();

private:
    QSqlDatabase m_db;
    static Global *m_instance;
};

#endif // GLOBAL_H
