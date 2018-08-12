// *********************************************************
//
// File autogenerated for the iirob_filters package
// by the rosparam_handler package.
// Please do not edit.
//
// ********************************************************/

#pragma once

#include <ros/param.h>
#include <ros/node_handle.h>
#include <rosparam_handler/utilities.hpp>
#ifdef DYNAMIC_RECONFIGURE_FOUND
#include <iirob_filters/KalmanFilterConfig.h>
#else
struct KalmanFilterConfig{};
#endif


namespace iirob_filters {

/// \brief Parameter struct generated by rosparam_handler
struct KalmanFilterParameters {

  using Config = KalmanFilterConfig;

  KalmanFilterParameters(const ros::NodeHandle& private_node_handle)
  : globalNamespace{"/"},
    privateNamespace{private_node_handle.getNamespace() + "/"},
    nodeName{rosparam_handler::getNodeName(private_node_handle)} {}

  /// \brief Get values from parameter server
  /// 
  /// Will fail if a value can not be found and no default value is given.
  void fromParamServer(){
    bool success = true;
    success &= rosparam_handler::getParam(privateNamespace + "dt", dt, double{0});
    success &= rosparam_handler::getParam(privateNamespace + "n", n, int{0});
    success &= rosparam_handler::getParam(privateNamespace + "m", m, int{0});
    success &= rosparam_handler::getParam(privateNamespace + "A", A, std::vector<double>{});
    success &= rosparam_handler::getParam(privateNamespace + "At", At, std::vector<double>{});
    success &= rosparam_handler::getParam(privateNamespace + "C", C, std::vector<double>{});
    success &= rosparam_handler::getParam(privateNamespace + "Q", Q, std::vector<double>{});
    success &= rosparam_handler::getParam(privateNamespace + "Q_coeff", Q_coeff, std::vector<double>{});
    success &= rosparam_handler::getParam(privateNamespace + "Q_exponent", Q_exponent, std::vector<double>{});
    success &= rosparam_handler::getParam(privateNamespace + "Q_variance", Q_variance, double{0});
    success &= rosparam_handler::getParam(privateNamespace + "R", R, std::vector<double>{});
    success &= rosparam_handler::getParam(privateNamespace + "P", P, std::vector<double>{});
    success &= rosparam_handler::getParam(privateNamespace + "x0", x0, std::vector<double>{});

    if(!success){
      missingParamsWarning();
      rosparam_handler::exit("RosparamHandler: GetParam could net retrieve parameter.");
    }
    ROS_DEBUG_STREAM(*this);
  }

  /// \brief Set parameters on ROS parameter server.
  void toParamServer(){
  rosparam_handler::setParam(privateNamespace + "dt",dt);
  rosparam_handler::setParam(privateNamespace + "n",n);
  rosparam_handler::setParam(privateNamespace + "m",m);
  rosparam_handler::setParam(privateNamespace + "A",A);
  rosparam_handler::setParam(privateNamespace + "At",At);
  rosparam_handler::setParam(privateNamespace + "C",C);
  rosparam_handler::setParam(privateNamespace + "Q",Q);
  rosparam_handler::setParam(privateNamespace + "Q_coeff",Q_coeff);
  rosparam_handler::setParam(privateNamespace + "Q_exponent",Q_exponent);
  rosparam_handler::setParam(privateNamespace + "Q_variance",Q_variance);
  rosparam_handler::setParam(privateNamespace + "R",R);
  rosparam_handler::setParam(privateNamespace + "P",P);
  rosparam_handler::setParam(privateNamespace + "x0",x0);        
  }

  /// \brief Update configurable parameters.
  ///
  /// \param config  dynamic reconfigure struct
  /// \level ?
  void fromConfig(const Config& config, const uint32_t level = 0){
#ifdef DYNAMIC_RECONFIGURE_FOUND
    dt = config.dt;
    n = config.n;
    m = config.m;
#else
  ROS_FATAL_STREAM("dynamic_reconfigure was not found during compilation. So fromConfig() is not available. Please recompile with dynamic_reconfigure.");
  rosparam_handler::exit("dynamic_reconfigure was not found during compilation. So fromConfig() is not available. Please recompile with dynamic_reconfigure.");
#endif
  }

  /// \brief Stream operator for printing parameter struct
  friend std::ostream& operator<<(std::ostream& os, const KalmanFilterParameters& p)
  {
    os << "[" << p.nodeName << "]\nNode " << p.nodeName << " has the following parameters:\n"
      << "	" << p.privateNamespace << "dt:" << p.dt << "\n"
      << "	" << p.privateNamespace << "n:" << p.n << "\n"
      << "	" << p.privateNamespace << "m:" << p.m << "\n"
      << "	" << p.privateNamespace << "A:" << p.A << "\n"
      << "	" << p.privateNamespace << "At:" << p.At << "\n"
      << "	" << p.privateNamespace << "C:" << p.C << "\n"
      << "	" << p.privateNamespace << "Q:" << p.Q << "\n"
      << "	" << p.privateNamespace << "Q_coeff:" << p.Q_coeff << "\n"
      << "	" << p.privateNamespace << "Q_exponent:" << p.Q_exponent << "\n"
      << "	" << p.privateNamespace << "Q_variance:" << p.Q_variance << "\n"
      << "	" << p.privateNamespace << "R:" << p.R << "\n"
      << "	" << p.privateNamespace << "P:" << p.P << "\n"
      << "	" << p.privateNamespace << "x0:" << p.x0 << "\n"
;
    return os;
  }

    double dt; /*!< time between two updates */
  int n; /*!< number of states */
  int m; /*!< number of measurements */
  std::vector<double> A; /*!< System dynamics matrix(static part): nxn */
  std::vector<double> At; /*!< System dynamics matrix(dynamic part): nxn */
  std::vector<double> C; /*!< Output matrix: mxn */
  std::vector<double> Q; /*!< Process noise covariance: nxn */
  std::vector<double> Q_coeff; /*!< coefficients of the dynamic part of Q */
  std::vector<double> Q_exponent; /*!< exponents of the time differnce */
  double Q_variance; /*!< variance of the process noise */
  std::vector<double> R; /*!< Measurement noise covariance: mxm */
  std::vector<double> P; /*!< Estimate error covariance: nxn */
  std::vector<double> x0; /*!< start state vector */

private:
  /// \brief Issue a warning about missing default parameters.
  void missingParamsWarning(){
    ROS_WARN_STREAM("[" << nodeName << "]\nThe following parameters do not have default values and need to be specified:\n"
    );
  }

  const std::string globalNamespace;
  const std::string privateNamespace;
  const std::string nodeName;
};

} // namespace iirob_filters
