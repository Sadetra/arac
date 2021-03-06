#include <ros/ros.h>

// ROS messages / services
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TransformStamped.h>
#include <std_msgs/Empty.h>

#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <memory>
#include <mutex>

#include "arac_model/AracModel.hpp"

#include "kulman_state_estimator/KulmanStateEstimatorBase.hpp"

namespace estimator {

using Model = kuco::AracModel;

class AracPerfectEstimator : public KulmanStateEstimatorBase<Model>
{
 public:

  AracPerfectEstimator(Model& model);

  virtual void initilize(ros::NodeHandle* nh) override;

  virtual void advance(double dt) override;

 private:
  kuco::Velocity positionWorldToBase_;
  kuco::Quaternion orientationWorldToBase_;
  kuco::Velocity velocityWorldToBaseInWorldFrame_;
  kuco::AngularVelocity angularVelocityWorldToBaseInWorldFrame_;
};

}
