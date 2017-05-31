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
#include <QLoggingCategory>
#include <QString>
#include <deque>
#include <memory>
#include <mutex>

namespace qe { namespace common {
	Q_DECLARE_LOGGING_CATEGORY( lcDBConnectionPool);

	class DBConnectionPoolPrivate;
	class DBConnectionLockGuard;
	class QECOMMON_EXPORT DBConnectionPool
	{
		friend class DBConnectionLockGuard;
		public:
			static DBConnectionPool& instance();

			std::shared_ptr<DBConnectionLockGuard>
			connection( QString conn = QString()) const;

		protected:
			QString lock( const QString& conn) const;
			void release( const QString& baseConn, const QString& lockedConn) const;

			DBConnectionPoolPrivate *d_ptr;
		private:
			using QStringDeque = std::deque<QString>;
			using Conn2LockedConnMap = QHash< QString, QStringDeque>;

			DBConnectionPool();
			QString createLockedConnName( const QString& conn) const;

			mutable std::mutex m_freeConnsMtx;
			mutable Conn2LockedConnMap m_freeConns;

			Q_DECLARE_PRIVATE( DBConnectionPool);
	};
}}
