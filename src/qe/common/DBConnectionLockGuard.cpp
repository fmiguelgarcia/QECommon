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
 * $QE_END_LICENSE$
 */

#include "DBConnectionLockGuard.hpp"
#include "DBConnectionPool.hpp"

using namespace qe::common;

/**
 * @class qe::common::DBConnectionLockGuard
 * @brief It locks and releases connections from @c qe::common::DBConnectionPool.
 *
 * DBConnectionLockGuard is used to ensure that specific connection is
 * used just by one thread. Once this object is deleted, the connection is
 * returned to the pool.
 *
 * @since 1.0.0
 * @inmodule QECommon
 */

/// @brief It creates a connection lock guard.
/// @param baseConn Base connection name.
/// @param lockedConn Unique connection name. It has been cloned from @p baseConn
DBConnectionLockGuard::DBConnectionLockGuard(
	const QString& baseConn,
	const QString& lockedConn)
	: m_baseConn( baseConn),
	m_lockedConn( lockedConn)
{ }

DBConnectionLockGuard::~DBConnectionLockGuard()
{
	DBConnectionPool::instance().release( m_baseConn, m_lockedConn);
}

/// @brief It returns the connection name that should be used to execute SQL
/// queries in a safe way.
QString DBConnectionLockGuard::connection() const noexcept
{ return m_lockedConn;}

QSqlDatabase DBConnectionLockGuard::database() const
{
	return QSqlDatabase::database( m_lockedConn);
}
