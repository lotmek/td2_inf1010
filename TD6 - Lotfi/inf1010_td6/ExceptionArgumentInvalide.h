#ifndef EXCEPTIONARGUMENTINVALIDE_H
#define EXCEPTIONARGUMENTINVALIDE_H

#include <QException>
#include <QString>

class ExceptionArgumentInvalide : public QException {
public:
    ExceptionArgumentInvalide(const char* s);
    virtual const char* what() const noexcept;
private :
    const char* s_;
};



ExceptionArgumentInvalide::ExceptionArgumentInvalide(const char* s) : s_(s){}

const char* ExceptionArgumentInvalide::what() const noexcept { return s_; }

#endif // EXCEPTIONARGUMENTINVALIDE_H
