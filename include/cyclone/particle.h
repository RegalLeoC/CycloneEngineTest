/**  A point mass is somewhat imaginary: it is an object that has
mass, but no size. It is an object, therefore, that can’t rotate, but otherwise moves
around normally. It might seem that this fantasy is particularly useless: every real
object does have size, after all. But the physics of many things can be simplified to point masses. 

The term point masses is rarely used in game physics, however. Almost always we call them “particles.”*/

/** 
 * A particle is the simples object that can be simulated in the physics system.

*/

#ifndef CYCLONE_PARTICLE_H
#define CYCLONE_PARTICLE_H

#include "precision.h"
#include "core.h"


namespace cyclone {

    class Particle
    {
        protected:
        /**
         * Holds the linear position of the particle
         * in world space.
         */
        Vector3 position;

        /**
         * Hols the linear velocity of the particle in world space.
         */

        Vector3 velocity;

        /**
         * Holds the acceleration of the particle. This value
         * can be used to set acceleration due to gracity (its primary use)
         * or any other constant acceleration.
         */

        Vector3 acceleration;

        // ADD SPECIAL DRAG FORCES LATER

        /** 
         * Holds the amount of daming applied to linear motion.
         * Damping is required to remove energy added
         * through numerical instability in the integrator.
         */

        real damping;


        /** 
         * Holds the inverse of the mass of the partcile. 
         * It is more useful to hold the inverse mass because 
         * integtation is simper, and because in real-time
         * simultaion it is more useful to have objects with
         * infinite mass (immovable)  than zero mass 
         * (completely unstable in numerical simulation).
         */

        real inverseMass;

        /** 
         * Integrates the particle foward in time by the given amount.
         * This function uses a Newton-Euler integration methos, which is a linear approximation to the correct integral.
         * For this reason it may be inaccurate un some cases.
         */
        void integrate (real duration);

        /**
         * 
         * Clears forces applied to the particle. This will
         * be called automatically after each integration step.
         */

        void clearAccumulator();

    };
    
}

#endif // CYCLONE_BODY_H

