#pragma once
#include <QEGlobal.hpp>
#include <QObject>

QE_BEGIN_NAMESPACE

class QES11nBase : public QObject
{
	public:
		QES11nBase( QObject* parent = nullptr);

		virtual void save( const QObject* const source) const = 0;
		virtual void load( QObject* const target) const = 0;
		virtual QString mimeType() const = 0;
		
		const QES11nBase & operator<<( const QObject *const source) const;
		const QES11nBase & operator>>( QObject *const source) const;
	private:
		Q_DISABLE_COPY( QES11nBase)
};

QE_END_NAMESPACE
