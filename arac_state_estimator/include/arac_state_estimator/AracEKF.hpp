#include <ros/ros.h>

// ROS messages / services
#include <sensor_msgs/Imu.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TransformStamped.h>
#include <std_msgs/Empty.h>
#include <visualization_msgs/Marker.h>

#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <memory>
#include <mutex>

#include "arac_model/AracModel.hpp"

#include "kulman_state_estimator/KulmanStateEstimatorBase.hpp"

namespace estimator {

using Model = kuco::AracModel;

class AracEKF : public KulmanStateEstimatorBase<Model>
{
 public:

  AracEKF(Model& model);

  virtual void initilize(ros::NodeHandle* nh) override;

  virtual void advance(double dt) override;

  virtual void readParameters() override ;

 private:
  virtual void initilizeSubscribers() override ;
  virtual void initilizePublishers() override ;
  // Todo : Bunu disari al bir sekilde
  virtual void publishVisualization();

  virtual void publishEstimatedState() override ;
  void getImuMsg(sensor_msgs::Imu msg ) ;

  // Subscriber
  ros::Subscriber imuSubscriber_;
  // Subscriber names
  std::string imuSubscriberName_;
  // Subscriber queue_size
  int imuSubscriberQueueSize_;
  // Subscriber msgs
  sensor_msgs::Imu imuMsg_;

  // Visualization
  ros::Publisher vis_pub_ ;


  virtual void pStep();
  virtual void mStep();
  virtual void getInput();
  virtual void getSensorData();

  double time_;
  double delT_;

  // state number
  int n_ ;
  // sensor variable number
  int m_ ;
  // input number
  int l_ ;


  Eigen::VectorXd U_;
  Eigen::VectorXd Xp_;
  Eigen::VectorXd Xm_;
  Eigen::MatrixXd Pp_;
  Eigen::MatrixXd Pm_;

  Eigen::VectorXd Y_;
  Eigen::VectorXd Z_;
  Eigen::VectorXd h_;

  Eigen::MatrixXd Q_;
  Eigen::MatrixXd R_;
  Eigen::MatrixXd K_;
  Eigen::MatrixXd S_;
  Eigen::MatrixXd F_;
  Eigen::MatrixXd H_;
  Eigen::MatrixXd Eye_;

  double rWheel_ ;
  double lWheel_ ;

  kuco::Velocity positionWorldToBase_;
  kuco::Quaternion orientationWorldToBase_;
  kuco::Velocity velocityWorldToBaseInWorldFrame_;
  kuco::AngularVelocity angularVelocityWorldToBaseInWorldFrame_;
};
}
