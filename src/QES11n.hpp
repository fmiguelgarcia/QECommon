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
#include <QEGlobal.hpp>
#include <QObject>

QE_BEGIN_NAMESPACE

/// @brief Base class for serialisation.
class QES11nBase : public QObject
{
	public:
		/// @brief Default constructor.
		QES11nBase( QObject* parent = nullptr);

		/// @brief Save @p source.
		/// @param source Source object.
		virtual void save( const QObject* const source) const = 0;

		/// @brief Load into @p target. 
		virtual void load( QObject* const target) const = 0;

		/// @brief It returns the MIME type.
		virtual QString mimeType() const = 0;
		
		const QES11nBase & operator<<( const QObject *const source) const;
		const QES11nBase & operator>>( QObject *const source) const;
	private:
		Q_DISABLE_COPY( QES11nBase)
};

QE_END_NAMESPACE
