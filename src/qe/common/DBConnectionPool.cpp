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
 */

#include "DBConnectionPool.hpp"
#include "DBConnectionLockGuard.hpp"
#include <QStringBuilder>
#include <QSqlDatabase>
#include <QSqlError>
#include <QThread>

using namespace qe::common;
using namespace std;

Q_LOGGING_CATEGORY( qe::common::lcDBConnectionPool,
	"org.dmious.qe.common.DBConnectionPool");

namespace {
	/// \internal This sequencer guarantees unique names for connections.
	static std::atomic<uint> sequencer;
}

/**
 * \class qe::common::DBConnectionPool
 * \brief It is a pool of database connection names.
 *
 * DBConnectionPool keeps a pool of cloned connections in order to supply them
 * each time a thread wants to use a specific connection.
 * To be sure that connection is locked, you have to use thought
 * a \c DBConnectionLockGuard object.
 *
 * \code
 *	// Clone default connection
 *	{
 * 		DBConnectionLockGuard dbLocked = DBConnectionPool::instance().connection();
 * 		QSqlDatabase db = QSqlDatabase::database( dbLocked.connection());
 * 		...
 *		// dbLocked is returned to pool.
 * 	}
 * \endcode
 */

/// \brief It gets the global instance.
DBConnectionPool& DBConnectionPool::instance()
{
	static unique_ptr<DBConnectionPool> instance;
	static once_flag onceFlag;

	call_once( onceFlag,
			   []{ instance.reset( new DBConnectionPool);});

	return *instance.get();
}

DBConnectionPool::DBConnectionPool()
{
	m_freeConns.reserve(
		max( QThread::idealThreadCount() * 2, 8));
}

/// \brief It locks a cloned connection for @p conn connection.
///
/// If @p conn is empty, the default connection will be used.
/// If there is no free cloned connection, a new one will be created.
/// \param conn Database connection.
DBConnectionLockGuardShd
DBConnectionPool::connection( QString conn) const
{
	if( conn.isEmpty())
		conn = QLatin1Literal( QSqlDatabase::defaultConnection);

	DBConnectionLockGuardShd lockedConn {
		new DBConnectionLockGuard( conn, lock(conn))};

	return lockedConn;
}

/// @brief It gets the name of free lockeable connection cloned from @p conn.
/// If there is no free ones, it will create a new clonned connection
/// from @p conn.
QString DBConnectionPool::lock( const QString& conn) const
{
	QString lockedConn;
	{
		lock_guard<mutex> _(m_freeConnsMtx);
		auto& freeLockedConns = m_freeConns[ conn];
		if( !freeLockedConns.empty())
		{
			lockedConn = freeLockedConns.front();
			freeLockedConns.pop_front();
		}
	}

	if( lockedConn.isEmpty())
		lockedConn = createLockedConnName( conn);

	// qCDebug( lcDBConnectionPool, "Connection '%s' is locked", qUtf8Printable( lockedConn));

	return lockedConn;
}

/// \brief It marks \p lockedConn as free and reusable as a safe connection
/// of \p baseConn.
void DBConnectionPool::release(
	const QString& baseConn,
	const QString& lockedConn) const
{
	lock_guard<mutex> _(m_freeConnsMtx);
	m_freeConns[ baseConn].push_back( lockedConn);

	// qCDebug( lcDBConnectionPool, "Connection '%s' is released", qUtf8Printable( lockedConn));
}

/// @brief It creates a unique cloned connection of @p conn connection name.
/// @return Cloned connection name.
QString DBConnectionPool::createLockedConnName( const QString& conn) const
{
	QString lockedConnName = conn
		% "_"
		% QString::number( ++sequencer);

	QSqlDatabase clonedDb = QSqlDatabase::cloneDatabase(
		QSqlDatabase::database( conn),
		lockedConnName);
	if( !clonedDb.open())
	{
		const QSqlError dbError = clonedDb.lastError();
		qCCritical( lcDBConnectionPool,
			"Connection pool can NOT open the new cloned connection '%s' from '%s': %s",
			qUtf8Printable( lockedConnName),
			qUtf8Printable( conn),
			qUtf8Printable( dbError.text()));
	}

	qCDebug( lcDBConnectionPool,
		"New connection '%s' has been cloned from '%s'",
		qUtf8Printable( lockedConnName),
		qUtf8Printable( conn));

	return lockedConnName;
}
