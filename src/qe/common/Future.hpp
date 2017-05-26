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
#include <qe/common/FutureData.hpp>

namespace qe { namespace common {

	template< class T>
	class Future
	{
		public:
			using SharedData = FutureData<T>;
			using SharedDataPtr = std::shared_ptr<SharedData>;

			Future() :m_d(
				new SharedData,
				SharedPtrQObjectDeleter())
			{}

			Future( const Future& other) noexcept
				: m_d( other.m_d)
			{}

			Future( Future&& other) noexcept
				: m_d( std::forward<SharedDataPtr>( other.m_d))
			{}

			inline bool isValid() const noexcept
			{ return m_d->future.valid();}

			inline void wait() const
			{ m_d->future.wait(); }

			inline T value() const
			{ return m_d->future.get();}

			inline void setValue( const T& value)
			{ m_d->setValue( value);}

			inline void setValue( T&& value)
			{ m_d->setValue( std::forward<T>(value));}

			inline void setException( std::exception_ptr p)
			{ m_d->setException( p); }

			inline QObject* sharedQObject() const noexcept
			{ return m_d.get(); }

			inline FutureBase* base() const noexcept
			{ return m_d.get(); }	

		private:
			SharedDataPtr m_d;
	};

	/// @brief Void template specialization.
	template<>
	class QECOMMON_EXPORT Future<void>
	{
		public:
			using SharedData = FutureData<void>;
			using SharedDataPtr = std::shared_ptr<SharedData>;

			Future();
			Future( const Future& other) noexcept;
			Future( Future&& other) noexcept;

			bool isValid() const noexcept;
			void wait() const;
			void value() const;
			void setValue();
			void setException( std::exception_ptr p);
			QObject* sharedQObject() const noexcept;
			FutureBase* base() const noexcept;

		private:
			SharedDataPtr m_d;
	};

}}

