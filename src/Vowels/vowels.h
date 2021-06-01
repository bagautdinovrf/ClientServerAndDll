#ifndef VOWELS_H
#define VOWELS_H

#include <QString>

#include "Vowels_global.h"


class VOWELS_EXPORT Vowels
{
public:
    Vowels();

    QString toUpperVowels( QString text );

private:
    QString m_vowels = "аиеёоуыэюя";

};

#endif // VOWELS_H
