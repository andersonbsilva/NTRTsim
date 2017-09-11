/*
 * Copyright © 2012, United States Government, as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All rights reserved.
 * 
 * The NASA Tensegrity Robotics Toolkit (NTRT) v1 platform is licensed
 * under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0.
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
*/

#ifndef LENGTH_CONTROLLER_H
#define LENGTH_CONTROLLER_H

/**
 * @file LengthController.h
 * @brief Contains the definition of class LengthController.
 * @author Brian Cera
 * $Id$
 */

// This library
#include "core/tgObserver.h"
#include "controllers/tgBasicController.h"
#include "core/tgBasicActuator.h"

// The C++ Standard Library
#include <vector>

// Forward declarations
class SUPERballV2Model;

class RestlenPlaybackController : public tgObserver<SUPERballV2Model>
{
public:
    RestlenPlaybackController(const char* cmdFile, int cmdStoreHz);
    
    /**
     * Nothing to delete, destructor must be virtual
     */
    virtual ~RestlenPlaybackController();
    
    std::vector<double> interpolateForTime(double time);
    
    virtual void onSetup(SUPERballV2Model& subject);
    
    /**
     * Apply the length controller. Called by notifyStep(dt) of its
     * subject.
     * @param[in] subject - the RPModel that is being controlled. Must
     * have a list of allMuscles populated
     * @param[in] dt, current timestep must be positive
     */
    virtual void onStep(SUPERballV2Model& subject, double dt);
    
    void setRestLengthWithCmdTensionLength(int actuatorID, double tension_cmd, double length_cmd, double dt);

    std::vector<tgBasicController*> m_controllers; //instantiate vector of controllers
    std::vector<tgBasicActuator*> actuators;
    
private:
    double globalTime;
    std::vector<std::vector<double> > cmdDataStore;
    int cmdStoreFreq;
};

#endif // LENGTH_CONTROLLER_H
