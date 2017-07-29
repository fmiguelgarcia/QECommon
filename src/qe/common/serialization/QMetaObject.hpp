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
 * * GNU Lesser General Public License Usage
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
#include <QMetaType>
#include <QMetaObject>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/level.hpp>

namespace boost
{
	namespace serialization
	{
		template< class Archive>
		void save(
				Archive &ar,
				const QMetaObject*& mo,
				const unsigned int )
		{
			const QString className;
			if( mo )
				className = mo->className();

			ar & BOOST_SERIALIZATION_NVP( className);
		}

		template< class Archive, class T>
		void load(
				Archive &ar,
				QMetaObject*& mo,
				const unsigned int )
		{
			QString className;
			ar & BOOST_SERIALIZATION_NVP( className);

			const int typeId = QMetaType::type( className.toLocal8Bit().constData());
			mo = QMetaType::metaObjectForType( typeId);
		}

		template< class Archive, class T>
		void serialize(
				Archive &ar,
				QMetaObject& mo,
				const unsigned int version)
		{
			split_free( ar, mo, version);
		}
	}
}

BOOST_CLASS_IMPLEMENTATION( QMetaObject, boost::serialization::object_serializable)
