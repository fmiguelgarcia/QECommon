/*
 * Copyright (C) 2017 francisco miguel garcia rodriguez
 * Contact: http://www.dmious.com/qe/licensing/
 *
 * This file is part of the QE Common module of the QE Toolkit.
 *
 * $QE_BEGIN_LICENSE:LGPL21$
 * Commercial License Usage
 * Licensees holding valid commercial QE licenses may use this file in
 * accordance with the commercial license agreement provided with the
 * Software or, alternatively, in accordance with the terms contained in
 * a written agreement between you and The Dmious Company. For licensing terms
 * and conditions see http://www.dmious.com/qe/terms-conditions. For further
 * information use the contact form at http://www.dmious.com/contact-us.
 *
 * GNU Lesser General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU Lesser
 * General Public License version 3 as published by the Free
 * Software Foundation and appearing in the file LICENSE.LGPLv3
 * included in the packaging of this file. Please review the
 * following information to ensure the GNU Lesser General Public License
 * requirements will be met: https://www.gnu.org/licenses/lgpl.html and
 * http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 *
 * $QE_END_LICENSE$
 */
#include "QByteArray.hpp"
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/nvp.hpp>

using namespace boost;

template< class Archive >
void boost::serialization::save(
	Archive &ar,
	const QByteArray& a,
	const unsigned int )
{	
	const int size = a.size() * sizeof(char);
	const char * data = a.constData();

	ar & BOOST_SERIALIZATION_NVP( size);
	ar & make_nvp( "data", 
			boost::serialization::make_binary_object( 
				const_cast<void*>(static_cast<const void*>( data)), 
				size * sizeof(char)));
}
	
template
void boost::serialization::save<archive::polymorphic_oarchive>(
	archive::polymorphic_oarchive &ar,
	const QByteArray& a,
	const unsigned int )
;

template< class Archive>
void boost::serialization::load(
		Archive &ar,
		QByteArray& a,
		const unsigned int )
{
	const static int sDataSize = 1024;
	char sData[ sDataSize];
	char *data = sData;
	int size;	

	ar & BOOST_SERIALIZATION_NVP( size);
	if( size > sDataSize )
		data = new char[ size];

	ar & make_nvp( "data", 
			boost::serialization::make_binary_object( 
				static_cast<void*>( data), 
				size * sizeof(char)));
	a = QByteArray( data, size);

	if( data != sData)
		delete [] data;			
}

template
void boost::serialization::load<archive::polymorphic_iarchive>(
		archive::polymorphic_iarchive &ar,
		QByteArray& a,
		const unsigned int );
