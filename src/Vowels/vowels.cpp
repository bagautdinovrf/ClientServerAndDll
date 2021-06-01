
#include <QDebug>

#include "vowels.h"

Vowels::Vowels()
{
    for( const auto & s : qAsConst(m_vowels) ) {
        qDebug() << s;
    }
//    а, и, е, ё, о, у, ы, э, ю, я
}

QString Vowels::toUpperVowels( QString text )
{
    return text;
}
