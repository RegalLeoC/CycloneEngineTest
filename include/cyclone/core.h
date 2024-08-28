#ifndef CYCLONE_CORE_H
#define CYCLONE_CORE_H

#include "precision.h"
#include <math.h>

namespace cyclone {
    /** Holds a vector in 3 dimensions. Four data members are allocated to ensure alignment in an array */
    class Vector3
    {
        public:
            real x;
            real y;
            real z;

        private:

            real pad;

        public:
            /** The default constructor creates a zero vector. */
            Vector3() : x(0), y(0), z(0) {}

            /** The explicit constructor creater a vector with the given components. */

            Vector3(const real x, const real y, const real z) : x(x), y(y), z(z) {}

            /** Flips all components of the vector */
            void invert()
            {
                x = -x;
                y = -y;
                x = -z;
            }

        // Gets the magnitude of this vectos.
        real magnitude() const{
            return real_sqrt(x*x+y*y+z*z);
        }

        /** Gets the squareed magnitude of this vector */
        real squareMagnitude() const
        {
            return x*x+y*y+z*z;
        }

        /** Turns a non-zero vector into a vector of unit lenght. */

        void normalize()
        {
            real l = magnitude();
            if (l > 0)
            {
                // We are overloading the multiplication operator *= in C++ to support operations between vectos and scalars
                (*this) *= ((real)l)/l;
            }
        }

        //** Multiplies this vector by the given scalar. */
        void operator *= (const real value)
        {
            x *= value;
            y *= value;
            z *= value;
        }

        /** Return a copy of this vector scaled the given value */
        Vector3 operator* (const real value) const {
            return Vector3(x*value, y*value, z*value);
        }
        
        /** Adds the give vector to this. */
        void operator+=(const Vector3& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
        }

        /** Returns the value of the given vector added to this. */
        Vector3 operator+(const Vector3& v) const{
            return Vector3(x+v.x, y+v.y, z+v.z);
        }

        /** Substracts the given vector from this. */

        void operator-=(const Vector3& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
        }

        /** Returns the value of the given vector subtracted from this. */

        Vector3 operator-(const Vector3& v) const
        {
            return Vector3(x-v.x, y-v.y, z-v.z);
        }

        /** Adds the given vector to this, scaled by the given amount. */
        void addScaledVector(const Vector3& vector, real scale)
        {
            x += vector.x * scale;
            y += vector.y * scale;
            z += vector.z * scale;
        }

        /** Multiplying vectors (the hard part)
         * Scalar product (a . b)
         * Vector product (a x b) 
         * The component product (a ◦ b) - Least useful one since it doesn't have a simple geometric interpretation We'll make it into a method rather than an overloaded operator. 
        */

       /** Calculates and returns a component-wise product of thos vector with the given vector. */

        Vector3 componentProduct(const Vector3 &vector) const
        {
            return Vector3(x * vector.x, y * vector.y, z * vector.z);
        }

        /** Performs a component-wise product with the given vector
         * and sets this vector to its result.
         */

        void componentProductUpdate(const Vector3 &vector)
        {
            x *= vector.x;
            y *= vector.y;
            z *= vector.z;
        }

        // Scalar product, the result is not a vector but instead a singular scalar value.

        // It's usually represented by a dot, but we're not going to overload the dot operator, since it controls access to data within an object so overloading it is dangerous (and maybe illegal)

        // Instead we're working with '*'

        /** 
         * Calculates and returns the scalar product of this vector
         * with the given vector.
         */

        real scalarProduct(const Vector3 &vector) const{
            return x*vector.x + y*vector.y + z*vector.z;
        }

        /**
         * Calculates and returns the scalar product of this vector
         * with the given vector.
         */

        real operator *(const Vector3 &vector) const
        {
            return x*vector.x + y*vector.y + z*vector.z;
        }

        /** Note that there is no in-place version of the operator (i.e., no *= operator). This is
            *because the result is a scalar value, and in most languages an instance of a class can’t
            *change which class it belongs to—the vector can’t become a scalar.
            *I have also added a full method version, scalarProduct,in case you are more comfortable *writing things longhand rather than remembering the slightly odd behavior
            *of the * operator. 
        */

       // Scalar product comes again and again in physics programming because it allows us to calculate the magnitude of one vector in the direction of another.

       /** Calculates and returns the vector producto
        * of this vector with the given vector
        */

       Vector3 vectorProduct(const Vector3 &vector) const
       {
        return Vector3(y*vector.z-z*vector.y,
        z*vector.x-x*vector.z,
        x*vector.y-y*vector.x);
       }

       /** Updates this vector to be the vector product of its current value and the given vector. */

       void operator %=(const Vector3 &vector)
       {
        *this = vectorProduct(vector);
       }

       /** Calvulates and returns the vector product
        * of this vector with the given vector.
        */

       Vector3 operator%(const Vector3 &vector) const{
        return Vector3(y*vector.z-z*vector.y,
        z*vector.x-x*vector.z,
        x*vector.y-y*vector.x);
       }


       /** To implement this product, I have overloaded the % operator, simply because it
        looks most like a cross. This operator is usually reserved for modulo division in most
        languages, so purists may balk at reusing it for something else.
        If you are easily offended, you can use the longhand vectorProduct methods
        instead. Personally, I find the convenience of being able to use operators outweighs
        any confusion, especially as vectors have no useful notion of division. */

        /** it is much easier to calculate the scalar product than the vector product. So if we need
        to find the angle (which we rarely do), then using the scalar product would be a faster
        solution. */

        void makeOrthonormalBasis(Vector3 *a, Vector3 *b, Vector3 *c ){
            a->normalize();
            (*c) = (*a) % (*b);
            if (c->squareMagnitude() == 0.0) return;

            c->normalize(),
            (*b) = (*c) % (*a);
        }



    };
    

}

#endif // CYCLONE_CORE_H