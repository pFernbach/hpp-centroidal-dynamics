#ifndef _ROBUST_EQUILIBRIUM_LIB_UTIL_HH
#define _ROBUST_EQUILIBRIUM_LIB_UTIL_HH

#include <Eigen/Dense>
#include <Eigen/src/Core/util/Macros.h>

#include "cdd/cddmp.h"
#include "cdd/setoper.h"
#include "cdd/cddtypes.h"
#include "cdd/cdd.h"

namespace robust_equilibrium
{

//#define USE_FLOAT 1;
#ifdef USE_FLOAT
typedef float value_type;
#else
typedef double value_type;
#endif

typedef Eigen::Matrix <value_type, 2, 1>                                            Vector2;
typedef Eigen::Matrix <value_type, 1, 2>                                            RVector2;
typedef Eigen::Matrix <value_type, 3, 1>                                            Vector3;
typedef Eigen::Matrix <value_type, 1, 3>                                            RVector3;
typedef Eigen::Matrix <value_type, 6, 1>                                            Vector6;
typedef Eigen::Matrix <value_type, Eigen::Dynamic, 1>                               VectorX;
typedef Eigen::Matrix <value_type, 1, Eigen::Dynamic>                               RVectorX;
typedef Eigen::Matrix <value_type, 3, 3, Eigen::RowMajor>                           Rotation;
typedef Eigen::Matrix <value_type, Eigen::Dynamic, 2, Eigen::RowMajor>              MatrixX2;
typedef Eigen::Matrix <value_type, 3, 3, Eigen::RowMajor>                           Matrix3;
typedef Eigen::Matrix <value_type, Eigen::Dynamic, 3, Eigen::RowMajor>              MatrixX3;
typedef Eigen::Matrix <value_type, 3, Eigen::Dynamic, Eigen::RowMajor>              Matrix3X;
typedef Eigen::Matrix <value_type, 4, 3, Eigen::RowMajor>                           Matrix43;
typedef Eigen::Matrix <value_type, 6, Eigen::Dynamic, Eigen::RowMajor>              Matrix6X;
typedef Eigen::Matrix <value_type, 6, 2, Eigen::RowMajor>                           Matrix62;
typedef Eigen::Matrix <value_type, 6, 3, Eigen::RowMajor>                           Matrix63;
typedef Eigen::Matrix <value_type, Eigen::Dynamic, 6, Eigen::RowMajor>              MatrixX6;
typedef Eigen::Matrix <value_type, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> MatrixXX;

//define Eigen ref if available
#if EIGEN_VERSION_AT_LEAST(3,2,2)
typedef Eigen::Ref<Vector2>     Ref_vector2;
typedef Eigen::Ref<Vector3>     Ref_vector3;
typedef Eigen::Ref<VectorX>     Ref_vectorX;
typedef Eigen::Ref<Rotation>    Ref_rotation;
typedef Eigen::Ref<MatrixX3>    Ref_matrixX3;
typedef Eigen::Ref<Matrix43>    Ref_matrix43;
typedef Eigen::Ref<Matrix6X>    Ref_matrix6X;
typedef Eigen::Ref<MatrixXX>    Ref_matrixXX;

typedef const Eigen::Ref<const Vector2>     & Cref_vector2;
typedef const Eigen::Ref<const Vector3>     & Cref_vector3;
typedef const Eigen::Ref<const VectorX>     & Cref_vectorX;
typedef const Eigen::Ref<const Rotation>    & Cref_rotation;
typedef const Eigen::Ref<const MatrixX3>    & Cref_matrixX3;
typedef const Eigen::Ref<const Matrix43>    & Cref_matrix43;
typedef const Eigen::Ref<const Matrix6X>    & Cref_matrix6X;
typedef const Eigen::Ref<const MatrixXX>    & Cref_matrixXX;
#else
typedef Vector2     & Ref_vector2;
typedef Vector3     & Ref_vector3;
typedef VectorX     & Ref_vectorX;
typedef Rotation    & Ref_rotation;
typedef MatrixX3    & Ref_matrixX3;
typedef Matrix43    & Ref_matrix43;
typedef Matrix6X    & Ref_matrix6X;
typedef MatrixXX    & Ref_matrixXX;

typedef const Vector2     & Cref_vector2;
typedef const Vector3     & Cref_vector3;
typedef const VectorX     & Cref_vectorX;
typedef const Rotation    & Cref_rotation;
typedef const MatrixX3    & Cref_matrixX3;
typedef const Matrix43    & Cref_matrix43;
typedef const Matrix6X    & Cref_matrix6X;
typedef const MatrixXX    & Cref_matrixXX;
#endif

/**
 * Convert the specified list of rays from Eigen to cdd format.
 * @param input The mXn input Eigen matrix contains m rays of dimension n.
 * @return The mX(n+1) output cdd matrix, which contains an additional column,
 * the first one, with all zeros.
 */
dd_MatrixPtr cone_span_eigen_to_cdd(Cref_matrixXX input);

/**
 * Compute the cross-product skew-symmetric matrix associated to the specified vector.
 */
Rotation crossMatrix(Cref_vector3 x);


void init_cdd_library();

void release_cdd_library();

void uniform(Cref_matrixXX lower_bounds, Cref_matrixXX upper_bounds, Ref_matrixXX out);

void euler_matrix(double roll, double pitch, double yaw, Ref_rotation R);

bool generate_rectangle_contacts(double lx, double ly, Cref_vector3 pos, Cref_vector3 rpy,
                                 Ref_matrix43 p, Ref_matrix43 N);

} //namespace robust_equilibrium

#endif //_ROBUST_EQUILIBRIUM_LIB_UTIL_HH
