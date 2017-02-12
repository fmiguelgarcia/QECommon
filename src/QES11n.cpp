#include "QES11n.hpp"

QES11nBase::QES11nBase( QObject* parent)
  : QObject( parent)
{}

const QES11nBase & QES11nBase::operator <<( const QObject *const source) const
{
	save( source);
	return *this;
}

const QES11nBase & QES11nBase::operator >>( QObject *const source) const
{
	load( source);
	return *this;
}
