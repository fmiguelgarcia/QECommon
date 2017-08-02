#include "QString.hpp"
#include <QtGlobal>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <string>

using namespace boost;
using namespace std;

template< class Archive >
void boost::serialization::save(
	Archive &ar,
	const QString& s,
	const unsigned int )
{
#ifdef Q_CC_GNU
	// Please compile this package using C++ _GLIBCXX_USE_CXX11_ABI.
	static_assert( _GLIBCXX_USE_CXX11_ABI == 1);
#endif

	const string str = s.toStdString();
	ar << str;
}

template< class Archive>
void boost::serialization::load(
	Archive &ar,
	QString& s,
	const unsigned int )
{
	string stds;
	ar >> stds;
	s = QString::fromStdString( stds);
}

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
