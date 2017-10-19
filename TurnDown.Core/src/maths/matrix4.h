#pragma once

#include "maths.h"

namespace turndown {
	namespace maths {

		struct matrix4 
		{
			union
			{
				float elements[4 * 4];
				Vector4 columns[4];
			};

			matrix4();
			matrix4(float diagonal);

			static matrix4 identity();

			matrix4& multiply(const matrix4& other);
			friend matrix4 operator*(matrix4 left, const matrix4& right);
			matrix4& operator*=(const matrix4& other);
			
			Vector3 multiply(const Vector3& other) const;
			friend Vector3 operator*(const matrix4& left, const Vector3& right);

			Vector4 multiply(const Vector4& other) const;
			friend Vector4 operator*(const matrix4& left, const Vector4& right);

			static matrix4 orthographic(float left, float right, float bottom, float top, float near, float far);
			static matrix4 perspective(float fov, float aspectRation, float near, float far);

			static matrix4 translation(const Vector3& translation);
			static matrix4 rotation(float angle, const Vector3& axis);
			static matrix4 scale(const Vector3& scale);
		};

	}
}