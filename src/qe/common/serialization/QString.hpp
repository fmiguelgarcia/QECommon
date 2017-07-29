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
#include <QString>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/level.hpp>
#include <string>

namespace boost
{
	namespace serialization
	{
		template< class Archive >
		void save(
				Archive &ar,
				const QString& s,
				const unsigned int )
		{
			const std::string stds = s.toStdString();
			ar & stds;
			// const QByteArray utf8 = s.toUtf8();
			// ar & BOOST_SERIALIZATION_NVP( utf8);
		}

		template< class Archive>
		void load(
				Archive &ar,
				QString& s,
				const unsigned int )
		{
			std::string stds;
			ar & stds;
			s = QString::fromStdString( stds);

			// QByteArray utf8;
			// ar & BOOST_SERIALIZATION_NVP( utf8);
			// s = QString::fromUtf8( utf8);
		}

		template< class Archive>
		void serialize(
				Archive &ar,
				QString& p,
				const unsigned int version)
		{
			split_free( ar, p, version);
		}
	}
}
BOOST_CLASS_IMPLEMENTATION( QString, boost::serialization::object_serializable)
