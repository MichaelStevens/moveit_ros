/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (c) 2012, Willow Garage, Inc.
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the Willow Garage nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

/* Author: Ioan Sucan */

#ifndef MOVEIT_PICK_PLACE_PICK_PLACE_
#define MOVEIT_PICK_PLACE_PICK_PLACE_

#include <moveit/pick_place/grasp_filter.h>
#include <moveit/constraint_sampler_manager_loader/constraint_sampler_manager_loader.h>
#include <moveit/plan_execution/plan_execution.h>
#include <moveit_msgs/PickupAction.h>
#include <moveit_msgs/PlaceAction.h>

namespace pick_place
{

class PickPlace
{
public: 

  struct Plan
  {
    // The full starting state of the robot at the start of the trajectory
    moveit_msgs::RobotState trajectory_start_;

    // The trajectory that moved group produced for execution
    std::vector<moveit_msgs::RobotTrajectory> planned_trajectory_;
    
    // An error code reflecting what went wrong (if anything)
    moveit_msgs::MoveItErrorCodes error_code_;
  };
  
  PickPlace(const plan_execution::PlanExecutionPtr &plan_execution);
  
  const constraint_samplers::ConstraintSamplerManagerPtr& getConstraintsSamplerManager(void) const
  {
    return constraint_sampler_manager_loader_->getConstraintSamplerManager();
  }
  
  const plan_execution::PlanExecutionPtr &getPlanExecution(void) const
  {
    return plan_execution_;
  }
  
  /** \brief Plan the sequence of motions that perform a pickup action */
  bool planPick(const planning_scene::PlanningScenePtr &planning_scene, const moveit_msgs::PickupGoal &goal, Plan &plan, double timeout) const;

  /** \brief Plan the sequence of motions that perform a placement action */
  bool planPlace(const planning_scene::PlanningScenePtr &planning_scene, const moveit_msgs::PlaceGoal &goal, Plan &plan, double timeout) const;

  /** \brief Plan and execute the sequence of motions that perform a placement action */
  bool executePick(const planning_scene::PlanningScenePtr &planning_scene, const moveit_msgs::PickupGoal &goal, double timeout) const;

  /** \brief Plan and execute the sequence of motions that perform a placement action */
  bool executePlace(const planning_scene::PlanningScenePtr &planning_scene, const moveit_msgs::PlaceGoal &goal, double timeout) const;

private:
  
  plan_execution::PlanExecutionPtr plan_execution_;  
  constraint_sampler_manager_loader::ConstraintSamplerManagerLoaderPtr constraint_sampler_manager_loader_;
};

}

#endif
