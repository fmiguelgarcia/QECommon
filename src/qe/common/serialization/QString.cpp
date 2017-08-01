#include "QString.hpp"
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

using namespace boost;

template
void boost::serialization::save<archive::polymorphic_oarchive>(
	archive::polymorphic_oarchive &ar,
	const QString& s,
	const unsigned int);

template
void boost::serialization::load<archive::polymorphic_iarchive>(
	archive::polymorphic_iarchive &ar,
	QString& s,
	const unsigned int );
