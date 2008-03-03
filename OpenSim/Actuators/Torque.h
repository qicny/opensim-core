#ifndef _Torque_h_
#define _Torque_h_
// Torque.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
* Copyright (c)  2005, Stanford University. All rights reserved. 
* Use of the OpenSim software in source form is permitted provided that the following
* conditions are met:
* 	1. The software is used only for non-commercial research and education. It may not
*     be used in relation to any commercial activity.
* 	2. The software is not distributed or redistributed.  Software distribution is allowed 
*     only through https://simtk.org/home/opensim.
* 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
*      presentations, or documents describing work in which OpenSim or derivatives are used.
* 	4. Credits to developers may not be removed from executables
*     created from modifications of the source.
* 	5. Modifications of source code must retain the above copyright notice, this list of
*     conditions and the following disclaimer. 
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
*  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
*  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
*  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
*  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
*  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* Note: This code was originally developed by Realistic Dynamics Inc. 
 * Author: Frank C. Anderson 
 */

#include <string>
#include "osimActuatorsDLL.h"
#include <OpenSim/Common/PropertyStr.h>
#include <OpenSim/Common/PropertyInt.h>
#include <OpenSim/Common/PropertyDblArray.h>
#include <OpenSim/Common/Function.h>
#include <OpenSim/Common/VectorFunction.h>
#include <OpenSim/Simulation/Model/AbstractActuator.h>

#ifdef SWIG
	#ifdef OSIMACTUATORS_API
		#undef OSIMACTUATORS_API
		#define OSIMACTUATORS_API
	#endif
#endif

//=============================================================================
//=============================================================================
/**
 * A class that supports the application of a torque between two bodies, BodyA
 * and BodyB.  This actuator has no states; the control is simply the
 * excitation of the actuator.  The torque is the optimal force multiplied
 * by the excitation.  So the excitation is a simply normalized torque
 * (i.e., torque / optimal force).  The direction of the torque is
 * expressed in the body-local frame of BodyA.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
namespace OpenSim { 

class AbstractBody;

class OSIMACTUATORS_API Torque : public AbstractActuator
{

//=============================================================================
// DATA
//=============================================================================
protected:
	// PROPERTIES
	/** name of BodyA. */
	PropertyStr _propBodyAName;
	/** Unit vector expressed in the local frame of BodyA that
	specifies the direction a positive torque is applied to BodyA.
	(serialized) */
	PropertyDblVec3 _propUnitVectorA;
	/** name of BodyB. */
	PropertyStr _propBodyBName;
	/** Optimal force. */
	PropertyDbl _propOptimalForce;

	// REFERENCES
	std::string& _bodyAName;
	SimTK::Vec3 &_uA;
	std::string& _bodyBName;
	double &_optimalForce;

	AbstractBody *_bA;
	AbstractBody *_bB;

	/** Unit vector expressed in the local frame of BodyB that
	specifies the direction a positive actuator force is applied to BodyB. */
	SimTK::Vec3 _uB;

	/** Excitation (control 0). */
	double _excitation;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	Torque(const std::string &aBodyAName="",const std::string &aBodyBName="");
	Torque(const Torque &aTorque);
	virtual ~Torque();
	virtual Object* copy() const;
private:
	void setNull();
	void setupProperties();
	

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
#ifndef SWIG
	Torque& operator=(const Torque &aTorque);
#endif

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	// BODY A
	void setBodyA(AbstractBody* aBody);
	AbstractBody* getBodyA() const;
	// DIRECTION A
	void setDirectionA(const SimTK::Vec3& aDirection);
	void getDirectionA(SimTK::Vec3& rDirection) const;
	// BODY B
	void setBodyB(AbstractBody* aBody);
	AbstractBody* getBodyB() const;
	// DIRECTION B
	void getDirectionB(SimTK::Vec3& rDirection) const;
	// OPTIMAL FORCE
	void setOptimalForce(double aOptimalForce);
	double getOptimalForce() const;
	// STRESS
	double getStress() const;

	//--------------------------------------------------------------------------
	// APPLICATION
	//--------------------------------------------------------------------------
	virtual void apply();

	//--------------------------------------------------------------------------
	// COMPUTATIONS
	//--------------------------------------------------------------------------
	virtual void computeActuation();
	void computeDirectionForBodyB();
	void computeSpeed();

	//--------------------------------------------------------------------------
	// CHECK
	//--------------------------------------------------------------------------
	virtual bool check() const;
	// Setup method to initialize Body references
	void setup(Model* aModel);

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------

	OPENSIM_DECLARE_DERIVED(Torque, AbstractActuator);

//=============================================================================
};	// END of class Torque

}; //namespace
//=============================================================================
//=============================================================================

#endif // __Torque_h__


