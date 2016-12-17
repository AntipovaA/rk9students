#pragma once
#include <math.h>
#include <cmath>

namespace rk9 {

	class UnitCell {

	public:
		virtual double Eval(double x, double y, double z) = 0;
	};

	class SchwarzPrimitive : public UnitCell {

	private: const int type = 0;
		     double A, K;
	public:		
			SchwarzPrimitive() :
				 A(1.0),
				 K(1.0) {};

			 SchwarzPrimitive(double a) :
				 A(a),
				 K(1.0) {};

			 SchwarzPrimitive(double a, double k) :
				 A(a),
				 K(k) {};
				
		double Eval(double x, double y, double z) {
			return (cos(A*x) + cos(A*y) + cos(A*z) - K);
		}
	};


	class SchwarzPrimitivePinched : public UnitCell {

	private: const int type = 1;
	         double A, K;

	public:	
			SchwarzPrimitivePinched() :
				A(1.0),
				K(0.0) {};

			SchwarzPrimitivePinched(double a) :
				A(a),
				K(0.0) {};

			SchwarzPrimitivePinched(double a, double k) :
				A(a),
				K(k) {};

		double Eval(double x, double y, double z) {
			return (-(2.25*(cos(A*x) + cos(A*y) + cos(A*z)) + 1.25*(cos(A*x)*cos(A*y) + cos(A*y)*cos(A*z) + cos(A*z)*cos(A*x))) - K);
		}
	};


	class SchoenGyroid : public UnitCell {

	private: const int type = 2;
	         double A, K;

	public:
			SchoenGyroid() :
				A(1.0),
				K(0.0) {};

			SchoenGyroid(double a) :
				A(a),
				K(0.0) {};

			SchoenGyroid(double a, double k) :
				A(a),
				K(k) {};

		double Eval(double x, double y, double z) {
			return (10 * (cos(A*x)*sin(A*y) + cos(A*y)*sin(A*z) + cos(A*z)*sin(A*x))
				- 0.5*(cos(A * 2 * x)*cos(A * 2 * y) + cos(A * 2 * y)*cos(A * 2 * z) + cos(A * 2 * z)*cos(A * 2 * x)) - K);
		}
	};


	class SchwarzW : public UnitCell {

	private: const int type = 3;
			 double A, K;

	public:
			SchwarzW() :
				A(1.0),
				K(14.0) {};

			SchwarzW(double a) :
				A(a),
				K(14.0) {};

			SchwarzW(double a, double k) :
				A(a),
				K(k) {};

		double Eval(double x, double y, double z) {
			return (10 * (cos(A*x)*cos(A*y) + cos(A*y)*cos(A*z) + cos(A*z)*cos(A*x))
				- 5 * (cos(A * 2 * x) + cos(A * 2 * y) + cos(A * 2 * z)) - K);
		}
	};

	class NeoviusSurface : public UnitCell {

	private: const int type = 4;
			 double A, K;

	public:
			NeoviusSurface() :
				A(1.0),
				K(0.0) {};

			NeoviusSurface(double a) :
				A(a),
				K(0.0) {};

			NeoviusSurface(double a, double k) :
				A(a),
				K(k) {};

		double Eval(double x, double y, double z) {
			return (-(-sin(A*x)*sin(A*y)*sin(A*z) + sin(A * 2 * x)*sin(A*y) + sin(A * 2 * y)*sin(A*z) + sin(A*x)*sin(A * 2 * z)
				- cos(A*x)*cos(A*y)*cos(A*z) + sin(A * 2 * x)*cos(A*z) + cos(A*x)*sin(A * 2 * y) + cos(A*y)*sin(A * 2 * z)) - K);
		}
	};
}