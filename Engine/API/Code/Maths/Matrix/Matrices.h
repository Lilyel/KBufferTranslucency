#pragma once

//#include "MatrixFixe.h"
//#include "MatrixDynamic.h"
#include "Matrix4x4.h"
#include "Matrix3x3.h"

#include <type_traits>
/*
namespace ae
{
	/// \ingroup math
	/// <summary>
	/// Alias for matrices. If the row count and the column count is specified
	/// the matrix will be a MatrixFixe otherwise it will be a MatrixDynamic.
	/// </summary>
	/// <seealso cref="MatrixDynamic"/>
	/// <seealso cref="MatrixFixe"/>
	template<typename T, Uint32 CountRow = 0, Uint32 CountCol = 1>
	using Matrix = typename std::conditional<( CountRow <= 0 ) || ( CountCol <= 0 ),
		MatrixDynamic,
		MatrixFixe<CountRow, CountCol>>::type;

} // ae

*/
