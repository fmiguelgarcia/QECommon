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
#pragma once
#include <qe/common/serialization/QString.hpp>
#include <QMetaEnum>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/level.hpp>

namespace boost
{
	namespace serialization
	{
		template< class Archive >
		void save(
				Archive &ar,
				const QMetaEnum& a,
				const unsigned int )
		{
			const QString scope = a.scope();
			const QString name = a.name();

			ar & BOOST_SERIALIZATION_NVP( scope);
			ar & BOOST_SERIALIZATION_NVP( name);
		}

		template< class Archive>
		void load(
				Archive &ar,
				QMetaEnum& a,
				const unsigned int )
		{
			QString scope, name; 

			ar & BOOST_SERIALIZATION_NVP( scope);
			ar & BOOST_SERIALIZATION_NVP( name);

			/// @todo
		}

		template< class Archive>
		void serialize(
				Archive &ar,
				QMetaEnum& p,
				const unsigned int version)
		{
			split_free( ar, p, version);
		}
	}
}

BOOST_CLASS_IMPLEMENTATION( QMetaEnum, boost::serialization::object_serializable)
