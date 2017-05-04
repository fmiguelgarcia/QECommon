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
#include <qe/common/Common.hpp>
#include <QException>
#include <QString>
#include <QByteArray>

namespace qe { namespace common 
{
	/// @brief QE exception base class that supports transfer across threads.
    class QECOMMON_EXPORT Exception : public QException
	{
		public:
			/// @brief Constructor.
			/// @param message Exception message
			/// @see Exception#what()
			explicit Exception( const QString& message);

			/// @brief Constructor using local 8-bit codec.
			/// @param message local 8-bit text.
			explicit Exception( const QByteArray& message) noexcept;

			/// @brief Copy constructor.
			Exception( const Exception& other) noexcept;
		
			/// @brief Move constructor.	
			Exception( Exception&& other) noexcept;

			/// @brief Copy operator
			Exception& operator=( const Exception& other) noexcept;

			/// @brief It clones this exception.
			/// It is useful to move across threads.
			Exception* clone() const override;

			/// @brief It throws this exception.
			void raise() const override;	

			/// @return A c-string that describes the exception.
			/// The return pointer is guaranteed to be valid at least until the 
			/// exception object is destroyed
			const char* what() const noexcept override;

			/// @brief It makes an @c Exception object and throws it.
			template< typename T>
			inline static void makeAndThrow( T&& message)
			{
				Exception exc( std::forward<T>(message));
			  	exc.raise();
			}	

		private:
			/// stored Message. It uses the local 8-bit representation. 
			QByteArray m_message;
	};
}}
	
