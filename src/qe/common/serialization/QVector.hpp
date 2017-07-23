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
#include <QVector>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/vector.hpp>
#include <vector>

namespace boost
{
	namespace serialization
	{
	 	// Class QVector
		// ==============================================================
		template< class Archive, class T>
		void save(
				Archive &ar,
				const QVector<T>& v,
				const unsigned int )
		{
			const auto stdVector = v.toStdVector();
			ar & stdVector;
		}

		template< class Archive, class T>
		void load(
				Archive &ar,
				QVector<T>& v,
				const unsigned int )
		{
			std::vector<T> stdVector;
			ar & stdVector;
			v = QVector<T>::fromStdVector( stdVector);
		}

		template< class Archive, class T>
		void serialize(
				Archive &ar,
				QVector<T>& v,
				const unsigned int version)
		{
			split_free( ar, v, version);
		}
	}
}
