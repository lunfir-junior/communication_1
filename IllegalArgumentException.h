#ifndef ILLEGALARGUMENTEXCEPTION_H
#define ILLEGALARGUMENTEXCEPTION_H

#include <QException>

class IllegalArgumentException : public QException
{
public:
  explicit IllegalArgumentException(std::string mess) : message(mess) {}
  void raise() const { throw *this; }
  IllegalArgumentException *clone() const { return new IllegalArgumentException(*this); }
  const char* what() const throw() { return message.c_str(); }

private:
  std::string message;
};

#endif // ILLEGALARGUMENTEXCEPTION_H
