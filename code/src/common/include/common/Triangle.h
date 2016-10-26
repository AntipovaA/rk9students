#pragma once

#include "common/common_api.h"

namespace rk9
{
	struct COMMON_API Triangle {
		unsigned V[3];

		//Вычислить нормаль к треугольнику
		double* GetNormal(); 
	};
}
