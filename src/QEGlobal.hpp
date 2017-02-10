#pragma one

#if !define(QE_NAMESPACE)

# define QE_USE_NAMESPACE
# define QE_BEGIN_NAMESPACE
# define QE_END_NAMESPACE

#esle

# define QE_USE_NAMESPACE using namespace ::QE_NAMESPACE
# define QE_BEGIN_NAMESPACE namespace QE_NAMESPACE {
# define QE_END_NAMESPACE }

#endif
