#define AngleToShort(X) ((DWORD)((X) * 65536 / 360) & 65535)

struct vector2
{
	float x, y;

	vector2()
	{
		x = 0.0f, y = 0.0f;
	}

	vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	vector2 operator-(vector2 vec)
	{
		return vector2(this->x - vec.x, this->y - vec.y);
	}

	vector2 operator+(vector2 vec)
	{
		return vector2(this->x + vec.x, this->y + vec.y);
	}

	vector2 operator*(vector2 vec)
	{
		return vector2(this->x * vec.x, this->y * vec.y);
	}

	vector2 operator*(float vec)
	{
		return vector2(this->x * vec, this->y * vec);
	}
};

struct vector3
{
	float x, y, z;

	vector3()
	{
		x = 0.0f, y = 0.0f, z = 0.0f;
	}

	vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float dotProduct(vector3 &Vector)
	{
		return (this->x * Vector.x) + (this->y * Vector.y) + (this->z * Vector.z);
	}

	vector3 operator-(vector3 vec)
	{
		return vector3(this->x - vec.x, this->y - vec.y, this->z - vec.z);
	}

	bool operator==(vector3 &vec)
	{
		return (this->x == vec.x && this->y == vec.y && this->z == vec.z);
	}

	vector3 operator+=(vector3 vec)
	{
		return vector3(this->x += vec.x, this->y += vec.y, this->z += vec.z);
	}

	vector3 operator+(vector3 vec)
	{
		return vector3(this->x + vec.x, this->y + vec.y, this->z + vec.z);;
	}

	vector3 operator*=(vector3 vec)
	{
		return vector3(this->x *= vec.x, this->y *= vec.y, this->z *= vec.z);
	}

	vector3 operator*(float value)
	{
		return vector3(this->x *= value, this->y *= value, this->z *= value);
	}

	float distanceEx(vector3 &Vector)
	{
		float _x = this->x - Vector.x, _y = this->y - Vector.y, _z = this->z - Vector.z;
		return ((_x * _x) + (_y * _y) + (_z * _z));
	}

	float distance(vector3 vector)
	{
		return sqrtf(distanceEx(vector));
	}
#define CHECK_VALID( _v ) 0
	__forceinline float LengthSqr(void) const
	{
		CHECK_VALID(*this);
		return (this->x * this->x + this->y * this->y + this->z * this->z);
	}

	void Zero()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
};

struct vector4
{
	float x, y, z, w;

	vector4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}
};

static vector3 VectorToAngles(vector3 Delta)
{
	float Forward, Yaw, Pitch;

	if (Delta.x == 0 && Delta.y == 0)
	{
		Yaw = 0;
		if (Delta.z > 0)
			Pitch = 90.0f;
		else
			Pitch = 270.0f;
	}
	else
	{
		if (Delta.x)
			Yaw = (atan2(Delta.y, Delta.x) * 57.2957804f);
		else if (Delta.y > 0)
			Yaw = 90.0f;
		else
			Yaw = 270.0f;

		if (Yaw < 0)
			Yaw += 360.0f;

		Forward = sqrt((Delta.x * Delta.x) + (Delta.y * Delta.y));
		Pitch = (atan2(Delta.z, Forward) * 57.2957804f);

		if (Pitch < 0)
			Pitch += 360;
	}
	return vector3(-Pitch, Yaw, 0);
}

#define XM_2PI              6.283185307f
#define XM_PI 3.14159265359f

static void AngleVectors(vector3 angles, vector3 *forward, vector3 *right, vector3 *up) {

	float angle;
	float sr, sp, sy, cr, cp, cy;

	angle = angles.y * 0.0174532f;
	sy = sin(angle);
	cy = cos(angle);
	angle = angles.x * 0.0174532f;
	sp = sin(angle);
	cp = cos(angle);
	angle = angles.z * 0.0174532f;
	sr = sin(angle);
	cr = cos(angle);


	if (forward) {
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}
	if (right) {
		right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
		right->y = (-1 * sr*sp*sy + -1 * cr*cy);
		right->z = -1 * sr*cp;
	}

	if (up) {
		up->x = (cr*sp*cy + -sr * -sy);
		up->y = (cr*sp*sy + -sr * cy);
		up->z = cr * cp;
	}
}

static float VectorSize(vector3 a)
{
	return a.x + a.y + a.z;
}

static void AnglesToAxis(vector3 Angles, vector3 &Axis)
{
	vector3 Right;
	AngleVectors(Angles, &Axis, &Right, &Axis);
}

static vector3 VectorSubtract(vector3 a, vector3 b)
{
	vector3 c = vector3();
	if (VectorSize(a) > VectorSize(b)) {
		c.x = a.x - b.x;
		c.y = a.y - b.y;
		c.z = a.z - b.z;
	}
	else {
		c.x = b.x - a.x;
		c.y = b.y - a.y;
		c.z = b.z - a.z;
	}
	return c;
}

static void AnglesToAxis(vector3 Angles, vector3 Axis[3])
{
	vector3 Right;

	AngleVectors(Angles, &Axis[0], &Right, &Axis[2]);
	VectorSubtract(Right, Axis[1]);
}