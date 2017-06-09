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
#include "CACertificatesRepository.hpp"
#include <QSslConfiguration>
#include <memory>
#include <mutex>

using namespace qe::common;
using namespace std;

CACertificatesRepository& CACertificatesRepository::instance()
{
	static unique_ptr<CACertificatesRepository> instance;
	static once_flag onceFlag;

	call_once( onceFlag,
		[]{ instance.reset( new CACertificatesRepository);});
	return *instance.get();
}

CACertificatesRepository::CACertificatesRepository()
{
	QSslConfiguration sslConf;
	m_caList = sslConf.caCertificates();
	m_caList.append( QSslCertificate::fromPath(":/qe/webmvc/ssl/server.crt"));
	m_caList.append( QSslCertificate::fromPath(":/qe/webmvc/ssl/migroslinx.no-ip.org.crt"));
}

CACertificatesRepository::~CACertificatesRepository()
{}

QList<QSslCertificate> CACertificatesRepository::caCertificates() const
{ return m_caList; }
