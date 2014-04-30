#ifndef __VECTOR_3D_H__
#define __VECTOR_3D_H__
 
#include "math.h"
#include <string.h>
#include <iostream>
#include <sstream>
/*
ABOUT: 3D Vector and rotation functions. Rotations about X, Y, Z, and any arbitruary Vector
AUTHOR: Kenny Cason
WEBSITE: Ken-Soft.com
EMAIL: kenneth.cason@gmail.com
DATE: 11-19-2009
*/
 
#define PI 3.14159265358979323846264338327950288f
 
static float degToRad(float deg) {
    return deg * PI / 180;
}

struct Vector3D {
 
    float x;
    float y;
    float z;
 
    Vector3D() {
        x = 0; y = 0; z = 0;
    }
 
    Vector3D(float _x, float _y, float _z) {
        x = _x; y = _y; z = _z;
    }
 
    /**
     * assignment operator
     */
    void operator=(Vector3D v) {
        x = v.x; y = v.y; z = v.z;
    }
 
    /**
     * equality operator
     */
    bool operator==(Vector3D v) {
        return (x == v.x && y == v.y && z == v.z);
    }
 
    /**
     * equality operator
     */
    bool operator!=(Vector3D v) {
        return (x != v.x || y != v.y || z != v.z);
    }
 
    /**
     * addition operators
     */
	//bool??
    void operator+=(Vector3D v) {
        x += v.x; y += v.y; z += v.z;
    }
 
    Vector3D operator+(Vector3D v) {
        Vector3D vect;
        vect.x = x + v.x; vect.y = y + v.y; vect.z = z + v.z;
        return vect;
    }
 
    Vector3D operator++(int) {
        x++; y++; z++;
    }
 
    Vector3D operator++() {
        ++x; ++y; ++z;
    }
 
    /**
     * subtraction operators
     */
	//bool??
    void operator-=(Vector3D v) {
        x -= v.x; y -= v.y; z -= v.z;
    }
 
    Vector3D operator-(Vector3D v) {
        Vector3D vect;
        vect.x = x - v.x; vect.y = y - v.y; vect.z = z - v.z;
        return vect;
    }
 
    Vector3D operator--(int) {
        x--; y--; z--;
    }
 
    Vector3D operator--() {
        --x; --y; --z;
    }
 
    /**
     * division operators
     */
    bool operator/=(float scalar) {
        x /= scalar; y /= scalar; z /= scalar;
    }
 
    Vector3D operator/(float scalar){
        Vector3D vect;
        vect.x = x / scalar; vect.y = y / scalar; vect.z = z / scalar;
        return vect;
    }
 
    bool operator/=(Vector3D v) {
        x /= v.x; y /= v.y; z /= v.z;
    }
 
    Vector3D operator/(Vector3D v){
        Vector3D vect;
        vect.x = x / v.x; vect.y = y / v.y; vect.z = z / v.z;
        return vect;
    }
 
 
    /**
     * multiplication operators
     */
    bool operator*=(float scalar) {
        x *= scalar; y *= scalar; z *= scalar;
    }
 
    Vector3D operator*(float scalar){
        Vector3D vect;
        vect.x = x * scalar; vect.y = y * scalar; vect.z = z * scalar;
        return vect;
    }
 
    bool operator*=(Vector3D v) {
        x *= v.x; y *= v.y; z *= v.z;
    }
 
    Vector3D operator*(Vector3D v){
        Vector3D vect;
        vect.x = x * v.x; vect.y = y * v.y; vect.z = z * v.z;
        return vect;
    }
 
 
    /**
     * exponent operators
     */
    bool operator^=(float power) {
        x = pow(x, power); y = pow(y, power); z = pow(z, power);
    }
 
    Vector3D operator^(float power){
        Vector3D vect;
        vect.x = pow(x, power); vect.y = pow(y, power); vect.z = pow(z, power);
        return vect;
    }
 
	float len() {
		return sqrt(x * x + y * y +  z * z);
	}
    /**
     * Return Unit Vector
     */
    Vector3D unit() {
        Vector3D vect;
        float d = sqrt(x * x + y * y +  z * z);
        vect = *(this) / d;
        return vect;
    }
 
    /**
     * toString()
     */
    std::string toString() {
        std::stringstream oss;
        oss << "(" << x << "," << y << "," << z << ")";
		std::string str = oss.str();
        return str;
    }

	void rotateXrad(float theta)
	{
		Vector3D newv;
		newv.x = x;
		newv.y = y * cos(theta) + z * -sin(theta);
		newv.z = y * sin(theta) + z * cos(theta);

		(*this) = newv;
	}
	void rotateXdeg(float theta)
	{
		this->rotateXrad(degToRad(theta));
	}
	
	void rotateYrad(float theta)
	{
		Vector3D newv;
		newv.x = x * cos(theta) + z * sin(theta);
		newv.y = y;
		newv.z = x * -sin(theta) + z * cos(theta);

		(*this) = newv;
	}
	void rotateYdeg(float theta)
	{
		this->rotateYrad(degToRad(theta));
	}

	void rotateZrad(float theta)
	{
		Vector3D newv;
		newv.x = x * cos(theta) + y * -sin(theta);
		newv.y = x * sin(theta) + y * cos(theta);
		newv.z = z;

		(*this) = newv;
	}
	void rotateZdeg(float theta)
	{
		this->rotateZrad(degToRad(theta));
	}
 
	void rotateAroundVectorRad(struct Vector3D vect2, float theta)
	{
		Vector3D newv;
		Vector3D unit = vect2.unit();
		//theta = Math.toRadians(theta);
		float q0 = cos(theta/2);
		float q1 = sin(theta/2)*unit.x;
		float q2 = sin(theta/2)*unit.y;
		float q3 = sin(theta/2)*unit.z;

		// column vect
		newv.x = (q0*q0 + q1*q1 - q2*q2 - q3*q3)*x +    2*(q2*q1 - q0*q3) * y +                       2*(q3*q1 + q0*q2) * z;
		newv.y = 2*(q1*q2 + q0*q3)*x +             (q0*q0 - q1*q1 + q2*q2 - q3*q3) * y +       2*(q3*q2 - q0*q1) * z;
		newv.z = 2*(q1*q3 - q0*q2)*x +             2*(q2*q3 + q0*q1) * y +                     (q0*q0 - q1*q1 - q2*q2 + q3*q3) * z;

		(*this) = newv;
	}
	void rotateAroundVectorDeg(struct Vector3D vect2, float theta)
	{
		this->rotateAroundVectorRad(vect2, degToRad(theta));
	}

	void rotateGLrad(float i,float j, float k)
	{

		Vector3D vy(0,1.0f,0);
		Vector3D vz(0,0,1.0f);

		this->rotateXrad(i);
		vy.rotateXrad(i);
		vz.rotateXrad(i);

		this->rotateAroundVectorRad(vy,j);
		vz.rotateAroundVectorRad(vy,j);

		this->rotateAroundVectorRad(vz,k);
	}
	void rotateGLdeg(float i,float j, float k)
	{
		/*
			glRotatef(i,1,0,0);
			glRotatef(j,0,1,0);
			glRotatef(k,0,0,1);
		*/
		this->rotateGLrad(degToRad(i),degToRad(j),degToRad(k));
	}
};


static Vector3D rotateX(struct Vector3D Vector, float theta);
static Vector3D rotateY(struct Vector3D vector, float theta);
static Vector3D rotateZ(struct Vector3D vector, float theta);
static Vector3D getUnitVector3D(struct Vector3D vector);
static Vector3D rotateAroundVector3D(struct Vector3D vect1, struct Vector3D vect2, float theta);
static Vector3D rotateGL(struct Vector3D Vector, float i,float j, float k);
static Vector3D rotateXdeg(struct Vector3D Vector, float theta);
static Vector3D rotateYdeg(struct Vector3D vector, float theta);
static Vector3D rotateZdeg(struct Vector3D vector, float theta);
static Vector3D rotateAroundVector3Ddeg(struct Vector3D vect1, struct Vector3D vect2, float theta);
static Vector3D rotateGLdeg(struct Vector3D Vector, float i,float j, float k);

/**
  * [(1      ,0      ,0),
  *  (0      ,cos(a) ,-sin(a)),
  *  (0      ,sin(a) ,cos(a))]
  * @param Vector3D
  * @param theta
  */
Vector3D rotateX(struct Vector3D vector, float theta) {
    Vector3D newv;
    newv.x = vector.x;
    newv.y = vector.y * cos(theta) + vector.z * -sin(theta);
    newv.z = vector.y * sin(theta) + vector.z * cos(theta);
    return newv;
}

/**
  * [(cos(a) ,0      ,sin(a)),
  *  (0      ,1      ,0),
  *  (-sin(a),0      ,cos(a))]
  * @param Vector3D
  * @param theta
  */
Vector3D rotateY(struct Vector3D vector, float theta) {
    Vector3D newv;
    newv.x = vector.x * cos(theta) + vector.z * sin(theta);
    newv.y = vector.y;
    newv.z = vector.x * -sin(theta) + vector.z * cos(theta);
    return newv;
}

/**
  * [(cos(a),-sin(a),0),
  *  (sin(a),cos(a) ,0),
  *  (0     ,0      ,1)]
  * @param Vector3D
  * @param theta
  */
Vector3D rotateZ(struct Vector3D vector, float theta) {
    Vector3D newv;
    newv.x = vector.x * cos(theta) + vector.y * -sin(theta);
    newv.y = vector.x * sin(theta) + vector.y * cos(theta);
    newv.z = vector.z;
    return newv;
}


/**
  * returns a unit vector
  */
Vector3D getUnitVector3D(struct Vector3D vector) {
    Vector3D newv;
    float d = sqrt(vector.x * vector.x + vector.y * vector.y +  vector.z * vector.z);
    newv.x = vector.x / d;
    newv.y = vector.y / d;
    newv.z = vector.z / d;
    return newv;
}


/**
  * using quaternions to rotate around an arbirtuary axis
  * Given angle theta in radians and unit vector u = ai + bj + ck or (a,b,c)
  *
  * q0 = cos(r/2),  q1 = sin(r/2) a,  q2 = sin(r/2) b,  q3 = sin(r/2) c
  *
  * Q =
  * [
  *   (q0^2 + q1^2 - q2^2 - q3^2)        2(q1q2 - q0q3)     2(q1q3 + q0q2)
  *   2(q2q1 + q0q3)           (q0^2 - q1^2 + q2^2 - q3^2)  2(q2q3 - q0q1)
  *   2(q3q1 - q0q2)             2(q3q2 + q0q1)     (q0^2 - q1^2 - q2^2 + q3^2)
  * ]
  *
  * Q u = u
  *
  * @param Vector3D 1
  * @param Vector3D 2
  * @param theta
  * @return Vector
  */
Vector3D rotateAroundVector3D(Vector3D vect1, Vector3D vect2, float theta) {
    Vector3D newv;
    Vector3D unit = getUnitVector3D(vect2);
    //theta = Math.toRadians(theta);
    float q0 = cos(theta/2);
    float q1 = sin(theta/2)*unit.x;
    float q2 = sin(theta/2)*unit.y;
    float q3 = sin(theta/2)*unit.z;

    // column vect
	newv.x = (q0*q0 + q1*q1 - q2*q2 - q3*q3)*vect1.x +    2*(q2*q1 - q0*q3) * vect1.y +                       2*(q3*q1 + q0*q2) * vect1.z;
    newv.y = 2*(q1*q2 + q0*q3)*vect1.x +             (q0*q0 - q1*q1 + q2*q2 - q3*q3) * vect1.y +       2*(q3*q2 - q0*q1) * vect1.z;
    newv.z = 2*(q1*q3 - q0*q2)*vect1.x +             2*(q2*q3 + q0*q1) * vect1.y +                     (q0*q0 - q1*q1 - q2*q2 + q3*q3) * vect1.z;

    //newv.x = (q0*q0 + q1*q1 - q2*q2 - q3*q3)* +    2*(q2*q1 + q0*q3) * vect1.y +                       2*(q3*q1 - q0*q2) * vect1.z;
    //newv.y = 2*(q1*q2 - q0*q3)*vect1.x +             (q0*q0 - q1*q1 + q2*q2 - q3*q3) * vect1.y +       2*(q3*q2 + q0*q1) * vect1.z;
    //newv.z = 2*(q1*q3 + q0*q2)*vect1.x +             2*(q2*q3 - q0*q1) * vect1.y +                     (q0*q0 - q1*q1 - q2*q2 + q3*q3) * vect1.z;
    return newv;
}

Vector3D rotateGL(struct Vector3D Vector, float i,float j, float k)
{
	Vector3D newv;

	Vector3D vy(0,1.0f,0);
	Vector3D vz(0,0,1.0f);

	newv = rotateX(Vector,i);
	vy = rotateX(vy,i);
	vz = rotateX(vz,i);

	newv = rotateAroundVector3D(newv,vy,j);
	vz = rotateAroundVector3D(vz,vy,j);

	newv = rotateAroundVector3D(newv,vz,k);

	return newv;
}


static Vector3D rotateXdeg(struct Vector3D Vector, float theta)
{
	return rotateX(Vector,degToRad(theta));
}
static Vector3D rotateYdeg(struct Vector3D vector, float theta)
{
	return rotateY(vector,degToRad(theta));
}
static Vector3D rotateZdeg(struct Vector3D vector, float theta)
{
	return rotateZ(vector,degToRad(theta));
}
static Vector3D rotateAroundVector3Ddeg(struct Vector3D vect1, struct Vector3D vect2, float theta)
{
	return rotateAroundVector3D(vect1,vect2,degToRad(theta));
}
static Vector3D rotateGLdeg(struct Vector3D Vector, float i,float j, float k)
{
	return rotateGL(Vector,degToRad(i),degToRad(j),degToRad(k));
}
#endif
