#include <stdio.h>
#include "cgmath-min.h"

template <class T> inline bool is_equal(const T& left, const T& right) { return std::abs(left - right) <= precision<T>::value(); }

int points = 0;

void test_tvec2()
{
	vec2	v1;
	vec2	v2;
	ivec2	iv;
	vec2	tv;
	float	scalar;
	const	vec2 cv(70.000000, 8.000000);

	v1 = vec2(97.000000f, 88.000000f);
	v1.operator[](0) += 10.000000f;
	if (v1 != vec2(107.000000f, 88.000000f)) printf("[X] vec2::operator[]\n"); else points++;
	v1.at(1) += 96.000000f;
	if (v1 != vec2(107.000000f, 184.000000f)) printf("[X] vec2::at()\n"); else points++;
	iv = ivec2(51, 65);
	iv.operator[](0) += 27;
	if (iv != ivec2(78, 65)) printf("[X] ivec2::operator[]\n"); else points++;

	v1 = vec2(58.000000f, 99.000000f);
	tv = +v1;	if (tv != vec2(58.000000f, 99.000000f)) printf("[X] vec2::operator+()\n"); else points++;
	tv = -v1;	if (tv != vec2(-58.000000f, -99.000000f)) printf("[X] vec2::operator-()\n"); else points++;
	tv = +cv;	if (tv != vec2(70.000000f, 8.000000f)) printf("[X] vec2::operator+() const\n"); else points++;
	tv = -cv;	if (tv != vec2(-70.000000f, -8.000000f)) printf("[X] vec2::operator-() const\n"); else points++;

	scalar = 7.000000f;
	v1 = vec2(82.000000f, 5.000000f);
	tv = v1 + cv;	if (tv != vec2(152.000000f, 13.000000f)) printf("[X] vec2::operator+(const vec2& v)\n"); else points++;
	tv = v1 - cv;	if (tv != vec2(12.000000f, -3.000000f)) printf("[X] vec2::operator-(const vec2& v)\n"); else points++;
	tv = v1*cv;	if (tv != vec2(5740.000000f, 40.000000f)) printf("[X] vec2::operator*(const vec2& v)\n"); else points++;
	tv = v1 / cv;	if (tv != vec2(1.171429f, 0.625000f)) printf("[X] vec2::operator/(const vec2& v)\n"); else points++;
	tv = cv + v1;	if (tv != vec2(152.000000f, 13.000000f)) printf("[X] vec2::operator+(const vec2& v) const\n"); else points++;
	tv = cv - v1;	if (tv != vec2(-12.000000f, 3.000000f)) printf("[X] vec2::operator-(const vec2& v) const\n"); else points++;
	tv = cv*v1;	if (tv != vec2(5740.000000f, 40.000000f)) printf("[X] vec2::operator*(const vec2& v) const\n"); else points++;
	tv = cv / v1;	if (tv != vec2(0.853659f, 1.600000f)) printf("[X] vec2::operator/(const vec2& v) const\n"); else points++;
	tv = v1 + scalar;	if (tv != vec2(89.000000f, 12.000000f)) printf("[X] vec2::operator+(float a)\n"); else points++;
	tv = v1 - scalar;	if (tv != vec2(75.000000f, -2.000000f)) printf("[X] vec2::operator-(float a)\n"); else points++;
	tv = v1*scalar;	if (tv != vec2(574.000000f, 35.000000f)) printf("[X] vec2::operator*(float a)\n"); else points++;
	tv = v1 / scalar;	if (tv != vec2(11.714286f, 0.714286f)) printf("[X] vec2::operator/(float a)\n"); else points++;

	v1 = vec2(94.000000f, 8.000000f);
	if (!is_equal(v1.length(), 94.339813f)) printf("[X] vec2::length()\n"); else points++;

	v1 = vec2(48.000000f, 76.000000f);
	v2 = vec2(86.000000f, 28.000000f);
	if (!is_equal(v1.dot(v2), 6256.000000f)) printf("[X] vec2::dot()\n"); else points++;
	if (!is_equal(cv.dot(v1), 3968.000000f)) printf("[X] vec2::dot() const\n"); else points++;

	v1 = vec2(85.000000f, 25.000000f);
	if (v1.normalize() != vec2(0.959365f, 0.282166f)) printf("[X] vec2::normalize()\n"); else points += 2;
}

void test_tvec3()
{
	vec3 v1;
	vec3 v2;
	ivec3 iv;
	vec3 tv;
	float scalar;
	const vec3 cv(41.000000f, 70.000000f, 8.000000f);

	v1 = vec3(44.000000f, 85.000000f, 53.000000f);
	v1.operator[](0) += 78.000000f;
	if (v1 != vec3(122.000000f, 85.000000f, 53.000000f)) printf("[X] vec3::operator[]\n"); else points++;
	v1.at(1) += 65.000000f;
	if (v1 != vec3(122.000000f, 150.000000f, 53.000000f)) printf("[X] vec3::at()\n"); else points++;
	iv = ivec3(100, 94, 46);
	iv.operator[](0) += 99;
	if (iv != ivec3(199, 94, 46)) printf("[X] ivec3::operator[]\n"); else points++;

	v1 = vec3(51.000000f, 58.000000f, 85.000000f);
	tv = +v1;	if (tv != vec3(51.000000f, 58.000000f, 85.000000f)) printf("[X] vec3::operator+()\n"); else points++;
	tv = -v1;	if (tv != vec3(-51.000000f, -58.000000f, -85.000000f)) printf("[X] vec3::operator-()\n"); else points++;
	tv = +cv;	if (tv != vec3(41.000000f, 70.000000f, 8.000000f)) printf("[X] vec3::operator+() const\n"); else points++;
	tv = -cv;	if (tv != vec3(-41.000000f, -70.000000f, -8.000000f)) printf("[X] vec3::operator-() const\n"); else points++;

	scalar = 6.000000f;
	v1 = vec3(81.000000f, 50.000000f, 56.000000f);
	tv = v1 + cv;	if (tv != vec3(122.000000f, 120.000000f, 64.000000f)) printf("[X] vec3::operator+(const vec3& v)\n"); else points++;
	tv = v1 - cv;	if (tv != vec3(40.000000f, -20.000000f, 48.000000f)) printf("[X] vec3::operator-(const vec3& v)\n"); else points++;
	tv = v1*cv;	if (tv != vec3(3321.000000f, 3500.000000f, 448.000000f)) printf("[X] vec3::operator*(const vec3& v)\n"); else points++;
	tv = v1 / cv;	if (tv != vec3(1.975610f, 0.714286f, 7.000000f)) printf("[X] vec3::operator/(const vec3& v)\n"); else points++;
	tv = cv + v1;	if (tv != vec3(122.000000f, 120.000000f, 64.000000f)) printf("[X] vec3::operator+(const vec3& v) const\n"); else points++;
	tv = cv - v1;	if (tv != vec3(-40.000000f, 20.000000f, -48.000000f)) printf("[X] vec3::operator-(const vec3& v) const\n"); else points++;
	tv = cv*v1;	if (tv != vec3(3321.000000f, 3500.000000f, 448.000000f)) printf("[X] vec3::operator*(const vec3& v) const\n"); else points++;
	tv = cv / v1;	if (tv != vec3(0.506173f, 1.400000f, 0.142857f)) printf("[X] vec3::operator/(const vec3& v) const\n"); else points++;
	tv = v1 + scalar;	if (tv != vec3(87.000000f, 56.000000f, 62.000000f)) printf("[X] vec3::operator+(float a)\n"); else points++;
	tv = v1 - scalar;	if (tv != vec3(75.000000f, 44.000000f, 50.000000f)) printf("[X] vec3::operator-(float a)\n"); else points++;
	tv = v1*scalar;	if (tv != vec3(486.000000f, 300.000000f, 336.000000f)) printf("[X] vec3::operator*(float a)\n"); else points++;
	tv = v1 / scalar;	if (tv != vec3(13.500000f, 8.333333f, 9.333333f)) printf("[X] vec3::operator/(float a)\n"); else points++;

	v1 = vec3(76.000000f, 67.000000f, 82.000000f);
	if (!is_equal(v1.length(), 130.341858f)) printf("[X] vec3::length()\n"); else points++;

	v1 = vec3(80.000000f, 92.000000f, 55.000000f);
	v2 = vec3(9.000000f, 17.000000f, 65.000000f);
	if (!is_equal(v1.dot(v2), 5859.000000f)) printf("[X] vec3::dot()\n"); else points++;
	if (!is_equal(cv.dot(v1), 10160.000000f)) printf("[X] vec3::dot() const\n"); else points++;

	v1 = vec3(21.000000f, 80.000000f, 67.000000f);
	if (v1.normalize() != vec3(0.197290f, 0.751580f, 0.629448f)) printf("[X] vec3::normalize()\n"); else points += 2;

	v1 = vec3(9.000000f, 75.000000f, 39.000000f);
	v2 = vec3(37.000000f, 24.000000f, 64.000000f);
	if ((v1^v2) != vec3(3864.000000f, 867.000000f, -2559.000000f)) printf("[X] vec3::operator^()\n"); else points += 2;
	if ((cv^v1) != vec3(2130.000000f, -1527.000000f, 2445.000000f)) printf("[X] vec3::operator^() const\n"); else points += 2;
	if (v2.cross(v1) != vec3(-3864.000000f, -867.000000f, 2559.000000f)) printf("[X] vec3::cross()\n"); else points += 2;
	if (cv.cross(v2) != vec3(4288.000000f, -2328.000000f, -1606.000000f)) printf("[X] vec3::cross() const\n"); else points += 2;

}

void test_tvec4()
{
	vec4 v1;
	vec4 v2;
	ivec4 iv;
	vec4 tv;
	float scalar;
	const vec4 cv(28.000000f, 3.000000f, 99.000000f, 50.000000f);

	v1 = vec4(76.000000f, 5.000000f, 75.000000f, 35.000000f);
	v1.operator[](0) += 1;
	if (v1 != vec4(77.000000f, 5.000000f, 75.000000f, 35.000000f)) printf("[X] vec4::operator[]\n"); else points++;
	v1.at(1) += 1;
	if (v1 != vec4(77.000000f, 6.000000f, 75.000000f, 35.000000f)) printf("[X] vec4::at()\n"); else points++;
	iv = ivec4(87, 69, 48, 45);
	iv.operator[](0) += 28;
	if (iv != ivec4(115, 69, 48, 45)) printf("[X] ivec4::operator[]\n"); else points++;

	v1 = vec4(57.000000f, 69.000000f, 67.000000f, 11.000000f);
	tv = +v1;	if (tv != vec4(57.000000f, 69.000000f, 67.000000f, 11.000000f)) printf("[X] vec4::operator+()\n"); else points++;
	tv = -v1;	if (tv != vec4(-57.000000f, -69.000000f, -67.000000f, -11.000000f)) printf("[X] vec4::operator-()\n"); else points++;
	tv = +cv;	if (tv != vec4(28.000000f, 3.000000f, 99.000000f, 50.000000f)) printf("[X] vec4::operator+() const\n"); else points++;
	tv = -cv;	if (tv != vec4(-28.000000f, -3.000000f, -99.000000f, -50.000000f)) printf("[X] vec4::operator-() const\n"); else points++;

	scalar = 66.000000f;
	v1 = vec4(40.000000f, 45.000000f, 34.000000f, 45.000000f);
	tv = v1 + cv;	if (tv != vec4(68.000000f, 48.000000f, 133.000000f, 95.000000f)) printf("[X] vec4::operator+(const vec4& v)\n"); else points++;
	tv = v1 - cv;	if (tv != vec4(12.000000f, 42.000000f, -65.000000f, -5.000000f)) printf("[X] vec4::operator-(const vec4& v)\n"); else points++;
	tv = v1*cv;	if (tv != vec4(1120.000000f, 135.000000f, 3366.000000f, 2250.000000f)) printf("[X] vec4::operator*(const vec4& v)\n"); else points++;
	tv = v1 / cv;	if (tv != vec4(1.428571f, 15.000000f, 0.343434f, 0.900000f)) printf("[X] vec4::operator/(const vec4& v)\n"); else points++;
	tv = cv + v1;	if (tv != vec4(68.000000f, 48.000000f, 133.000000f, 95.000000f)) printf("[X] vec4::operator+(const vec4& v) const\n"); else points++;
	tv = cv - v1;	if (tv != vec4(-12.000000f, -42.000000f, 65.000000f, 5.000000f)) printf("[X] vec4::operator-(const vec4& v) const\n"); else points++;
	tv = cv*v1;	if (tv != vec4(1120.000000f, 135.000000f, 3366.000000f, 2250.000000f)) printf("[X] vec4::operator*(const vec4& v) const\n"); else points++;
	tv = cv / v1;	if (tv != vec4(0.700000f, 0.066667f, 2.911765f, 1.111111f)) printf("[X] vec4::operator/(const vec4& v) const\n"); else points++;
	tv = v1 + scalar;	if (tv != vec4(106.000000f, 111.000000f, 100.000000f, 111.000000f)) printf("[X] vec4::operator+(float a)\n"); else points++;
	tv = v1 - scalar;	if (tv != vec4(-26.000000f, -21.000000f, -32.000000f, -21.000000f)) printf("[X] vec4::operator-(float a)\n"); else points++;
	tv = v1*scalar;	if (tv != vec4(2640.000000f, 2970.000000f, 2244.000000f, 2970.000000f)) printf("[X] vec4::operator*(float a)\n"); else points++;
	tv = v1 / scalar;	if (tv != vec4(0.606061f, 0.681818f, 0.515152f, 0.681818f)) printf("[X] vec4::operator/(float a)\n"); else points++;

	v1 = vec4(33.000000f, 24.000000f, 53.000000f, 25.000000f);
	if (!is_equal(v1.length(), 71.407280f)) printf("[X] vec4::length()\n"); else points++;

	v1 = vec4(79.000000f, 20.000000f, 11.000000f, 13.000000f);
	v2 = vec4(62.000000f, 42.000000f, 10.000000f, 65.000000f);
	if (!is_equal(v1.dot(v2), 6693.000000f)) printf("[X] vec4::dot()\n"); else points++;
	if (!is_equal(cv.dot(v1), 4011.000000f)) printf("[X] vec4::dot() const\n"); else points++;

	v1 = vec4(77.000000f, 89.000000f, 16.000000f, 89.000000f);
	if (v1.normalize() != vec4(0.518816f, 0.599670f, 0.107806f, 0.599670f)) printf("[X] vec4::normalize()\n"); else points += 2;
}

void test_mat4()
{
	vec4 v1;
	mat4 m1;
	mat4 m2;
	float scalar;
	mat4 tmp_mat;
	const mat4 cm(26.000000f, 27.000000f, 46.000000f, 37.000000f, 15.000000f, 12.000000f, 67.000000f, 50.000000f, 49.000000f, 58.000000f, 17.000000f, 85.000000f, 77.000000f, 32.000000f, 91.000000f, 83.000000f);

	m1 = mat4(21.000000f, 61.000000f, 94.000000f, 46.000000f, 91.000000f, 30.000000f, 84.000000f, 45.000000f, 70.000000f, 39.000000f, 67.000000f, 90.000000f, 97.000000f, 91.000000f, 46.000000f, 86.000000f);
	if (!is_equal(m1.operator[](0), 21.000000f) || !is_equal(m1.operator[](1), 61.000000f) ||
		!is_equal(m1.operator[](2), 94.000000f) || !is_equal(m1.operator[](3), 46.000000f) ||
		!is_equal(m1.operator[](4), 91.000000f) || !is_equal(m1.operator[](5), 30.000000f) ||
		!is_equal(m1.operator[](6), 84.000000f) || !is_equal(m1.operator[](7), 45.000000f) ||
		!is_equal(m1.operator[](8), 70.000000f) || !is_equal(m1.operator[](9), 39.000000f) ||
		!is_equal(m1.operator[](10), 67.000000f) || !is_equal(m1.operator[](11), 90.000000f) ||
		!is_equal(m1.operator[](12), 97.000000f) || !is_equal(m1.operator[](13), 91.000000f) ||
		!is_equal(m1.operator[](14), 46.000000f) || !is_equal(m1.operator[](15), 86.000000f)
		) {
		printf("[X] mat4::operator[]\n");
	}
	else {
		points++;
	}

	scalar = 77.000000f;
	m1.operator[](0) += scalar;
	if (!is_equal(m1.operator[](0), 98.000000f)) printf("[X] return of mat4::operator[]\n"); else points++;
	m1.setIdentity();
	tmp_mat = mat4(1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 1.000000f);
	if (m1 != tmp_mat) printf("[X] mat4::setIdentity[]\n"); else points++;

	m1 = mat4(24.000000f, 94.000000f, 23.000000f, 76.000000f, 56.000000f, 69.000000f, 39.000000f, 91.000000f, 7.000000f, 36.000000f, 72.000000f, 24.000000f, 83.000000f, 69.000000f, 93.000000f, 89.000000f);
	tmp_mat = mat4(24.000000f, 56.000000f, 7.000000f, 83.000000f, 94.000000f, 69.000000f, 36.000000f, 69.000000f, 23.000000f, 39.000000f, 72.000000f, 93.000000f, 76.000000f, 91.000000f, 24.000000f, 89.000000f);
	if (m1.transpose() != tmp_mat) printf("[X] mat4::transpose[]\n"); else points++;

	m1 = mat4(12.000000f, 64.000000f, 75.000000f, 30.000000f, 58.000000f, 97.000000f, 30.000000f, 76.000000f, 47.000000f, 31.000000f, 86.000000f, 43.000000f, 7.000000f, 76.000000f, 93.000000f, 75.000000f);
	v1 = vec4(82.000000f, 49.000000f, 74.000000f, 97.000000f);
	if (m1 * v1 != vec4(12580.000000f, 19101.000000f, 15908.000000f, 18455.000000f)) printf("[X] mat4::operator*(const vec4& v)\n"); else points += 3;

	m1 = mat4(70.000000f, 86.000000f, 9.000000f, 98.000000f, 82.000000f, 37.000000f, 33.000000f, 32.000000f, 19.000000f, 89.000000f, 4.000000f, 4.000000f, 27.000000f, 16.000000f, 50.000000f, 35.000000f);
	m2 = mat4(35.000000f, 96.000000f, 89.000000f, 9.000000f, 19.000000f, 69.000000f, 39.000000f, 8.000000f, 9.000000f, 84.000000f, 28.000000f, 96.000000f, 95.000000f, 27.000000f, 4.000000f, 91.000000f);
	tmp_mat = mat4(13475.000000f, 16056.000000f, 10228.000000f, 11100.000000f, 6910.000000f, 14061.000000f, 9793.000000f, 7114.000000f, 2772.000000f, 8409.000000f, 5290.000000f, 1631.000000f, 5024.000000f, 8841.000000f, 4567.000000f, 8356.000000f);
	if (m1 * m2 != tmp_mat) printf("[X] mat4::operator*(const mat4& m)\n"); else points += 3;

	m1 = mat4(74.000000f, 72.000000f, 89.000000f, 72.000000f, 16.000000f, 59.000000f, 77.000000f, 75.000000f, 69.000000f, 55.000000f, 41.000000f, 37.000000f, 74.000000f, 8.000000f, 27.000000f, 54.000000f);
	if (!is_equal(m1.determinant(), -4775562.000000f)) printf("[X] mat4::determinant()\n"); else points += 5;

	m1 = mat4(85.000000f, 15.000000f, 23.000000f, 48.000000f, 74.000000f, 8.000000f, 48.000000f, 25.000000f, 72.000000f, 82.000000f, 10.000000f, 93.000000f, 61.000000f, 1.000000f, 23.000000f, 75.000000f);
	tmp_mat = m1.inverse();
	if (!is_equal(tmp_mat[0], 0.031490f) || !is_equal(tmp_mat[1], -0.008658f) ||
		!is_equal(tmp_mat[2], -0.004777f) || !is_equal(tmp_mat[3], -0.011343f) ||
		!is_equal(tmp_mat[4], -0.007847f) || !is_equal(tmp_mat[5], 0.007606f) ||
		!is_equal(tmp_mat[6], 0.013056f) || !is_equal(tmp_mat[7], -0.013702f) ||
		!is_equal(tmp_mat[8], -0.040408f) || !is_equal(tmp_mat[9], 0.034868f) ||
		!is_equal(tmp_mat[10], 0.003875f) || !is_equal(tmp_mat[11], 0.009433f) ||
		!is_equal(tmp_mat[12], -0.013115f) || !is_equal(tmp_mat[13], -0.003752f) ||
		!is_equal(tmp_mat[14], 0.002523f) || !is_equal(tmp_mat[15], 0.019849f)
		) {
		printf("[X] mat4::inverse()\n");
	}
	else {
		points += 5;
	}
}


void main(void)
{
	test_tvec2();
	test_tvec3();
	test_tvec4();
	test_mat4();

	printf("**************************\n");
	printf("Result : %d / 100 points\n", points);
	printf("**************************\n");
}
