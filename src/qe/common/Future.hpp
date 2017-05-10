/*
 * Copyright (C) 2017 Francisco Miguel García Rodríguez
 * Contact: http://www.dmious.com/qe/licensing/
 *
 * This file is part of the QE Common module of the QE Toolkit.
 *
 * $QE_BEGIN_LICENSE$
 * Commercial License Usage
 * Licensees holding valid commercial QE licenses may use this file in
 * accordance with the commercial license agreement provided with the
 * Software or, alternatively, in accordance with the terms contained in
 * a written agreement between you and The Dmious Company. For licensing terms
 * and conditions see http://www.dmious.com/qe/terms-conditions. For further
 * information use the contact form at http://www.dmious.com/contact-us.
 */
#pragma once
#include <qe/common/FutureBase.hpp>
#include <memory>
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

	template< class T>
	class Future
	{
		public:
			using SharedData = FutureData<T>;
			using SharedDataPtr = std::shared_ptr<SharedData>;

			Future() :m_d( std::make_shared<SharedData>())
			{}

			Future( const Future& other) : m_d( other.m_d)
			{}

			Future( Future&& other) : m_d( std::forward<SharedDataPtr>( other.m_d))
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
			Future( const Future& other);
			Future( Future&& other);

			bool isValid() const noexcept;
			void wait() const;
			void value() const;
			void setValue();
			void setException( std::exception_ptr p);
			QObject* sharedQObject() const noexcept;

		private:
			SharedDataPtr m_d;
	};

}}

