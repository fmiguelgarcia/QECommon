/*
 * Copyright 2017 Francisco Miguel <francisco.miguel.garcia.rodriguez@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "Future.hpp"
using namespace qe::common;
using namespace std;

// Class FutureData
// ============================================================================

FutureData<void>::FutureData( QObject* parent)
	: FutureBase( parent)
{}

void FutureData<void>::setValue()
{
	promise.set_value();
	emit finished();
}

void FutureData<void>::setException( std::exception_ptr p)
{
	promise.set_exception( p);
	emit finished();
}

// Class Future
// ============================================================================

Future<void>::Future()
	: m_d( make_shared<SharedData>())
{}

Future<void>::Future( const Future<void>& other)
	: m_d( other.m_d)
{}

Future<void>::Future( Future<void>&& other)
	: m_d( std::move( other.m_d))
{}

bool Future<void>::isValid() const noexcept
{ return m_d->future.valid();}

void Future<void>::wait() const
{ return m_d->future.wait();}

void Future<void>::value() const
{ m_d->future.get();}

void Future<void>::setValue()
{ m_d->setValue();}

void Future<void>::setException( std::exception_ptr p)
{ m_d->setException(p);}

QObject* Future<void>::sharedQObject() const noexcept
{ return m_d.get();}
