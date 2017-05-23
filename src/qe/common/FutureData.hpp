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
#include <qe/common/FutureBase.hpp>
#include <future>

namespace qe { namespace common {

	/// @brief This class represents
	template< class T>
	class FutureData
		: public FutureBase
	{
		public:
			explicit FutureData( QObject* parent = nullptr)
				: FutureBase( parent)
			{
				future = promise.get_future();
			}

			inline void setValue( const T& value)
			{
				promise.set_value( value);
				emit finished();
			}

			inline void setValue( T&& value)
			{
				promise.set_value( std::forward<T>(value));
				emit finished();
			}

			inline void setException( std::exception_ptr p)
			{
				promise.set_exception( p);
				emit finished();
			}

			std::promise<T> promise;
			std::future<T> future;
	};

	/// @brief Void template specialization.
	template<>
	class QECOMMON_EXPORT FutureData<void>
		: public FutureBase
	{
		public:
			explicit FutureData<void>( QObject* parent = nullptr);

			void setValue();
			void setException( std::exception_ptr p);

			std::promise<void> promise;
			std::future<void> future;
	};
}}
