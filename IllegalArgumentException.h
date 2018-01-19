#ifndef ILLEGALARGUMENTEXCEPTION_H
#define ILLEGALARGUMENTEXCEPTION_H

#include <QException>

class IllegalArgumentException : public QException
{
public:
  void raise() const { throw *this; }
  IllegalArgumentException *clone() const { return new IllegalArgumentException(*this); }
};

#endif // ILLEGALARGUMENTEXCEPTION_H
