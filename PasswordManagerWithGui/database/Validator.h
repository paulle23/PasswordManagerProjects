#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QString>
#include <QRegularExpression>

class Validator{
public:

static bool validEmail(QString email){
    QRegularExpression regex(
    "^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$"
    );
    return regex.match(email).hasMatch();
}

static QString passwordStrength(QString password){
    bool upper = false;
    bool lower = false;
    bool digit = false;
    bool special = false;
    QString chars = "!@#$%^&*()-+";

    for(QChar c: password){
        if(c.isUpper())
            upper=true;
        if(c.isLower())
            lower=true;
        if(c.isDigit())
            digit=true;
        if(chars.contains(c))
            special=true;
    }
    int score =
        upper+
        lower+
        digit+
        special+
        (password.length()>=8);

    if(score==5)
        return "Strong";
    if(score>=3)
        return "Medium";
    return "Weak";
}
};
#endif