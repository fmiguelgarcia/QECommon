#include <qe/common/Common.hpp>
#include <qe/common/Exception.hpp>

using namespace qe::common;

int main(int argc, char** argv)
{
	int status = 0;
	const QString message = QStringLiteral( "Throwing an exception");

	try {
		Exception::makeAndThrow( message);
	}catch( Exception & e){
		if( message != e.what())
			status = 1;	
	}

	return status;
}
