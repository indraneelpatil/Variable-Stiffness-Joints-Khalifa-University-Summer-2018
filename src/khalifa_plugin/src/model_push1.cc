#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/rendering/rendering.hh>
#include <gazebo/sensors/sensors.hh>
#include <gazebo/common/common.hh>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include <boost/bind.hpp>
#include <thread>
#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"
#include "std_msgs/Float32.h"

double stiffness1;

double stiffness;
int n;

namespace gazebo 
{
	class ModelPush1 : public ModelPlugin
	{
		
		public: 
		    // Called by world update start event
			void Load(physics::ModelPtr _parent,sdf::ElementPtr /*_sdf*/);
		
			void OnUpdate();
			
			void SetStiffness1(const double &_stiff1);
			
			// Callback Function
			void OnRosMsg1(const std_msgs::Float32ConstPtr &_msg1);
			
			
		private:
			    //  Pointer to model
				physics::ModelPtr model;
					
				event::ConnectionPtr updateConnection;
				
				// Node used for ROS transport
				std::unique_ptr<ros::NodeHandle> rosNode1;
				
				//A ROS subscriber to a named topic
				ros::Subscriber rosSub1;
				
				// Helps process messages on the topic
				ros::CallbackQueue rosQueue1;
				
				std::thread rosQueueThread1;
				
				
				// Helper Function that processes messages
				void QueueThread1();
		
		};
	
	
	void ModelPush1::Load(physics::ModelPtr _parent,sdf::ElementPtr _sdf)
			{
				this->model= _parent;
				
			    // Callback On Update Function type.
				this->updateConnection =event::Events::ConnectPause(boost::bind(&ModelPush1::OnUpdate,this));
				
				//Initialize ROS
				if (!ros::isInitialized())
				{
					int argc=0;
					char **argv=NULL;
					ros::init(argc,argv,"gazebo_client",ros::init_options::NoSigintHandler);
				}
					
				//Create our ROS node
				this->rosNode1.reset(new ros::NodeHandle("gazebo_client1"));
				
				// Create a topic name
				ros::SubscribeOptions so1= ros::SubscribeOptions::create<std_msgs::Float32>("/" + this->model->GetName()+"/joint1" + "/stiffness_cmd",1,boost::bind(&ModelPush1::OnRosMsg1,this,_1),ros::VoidPtr(),&this->rosQueue1);
				
				
				// Subscribe to this topic and register a callback
				this->rosSub1= this->rosNode1->subscribe(so1);
				
				
				//Spin up queue helper thread
				this->rosQueueThread1=std::thread(std::bind(&ModelPush1::QueueThread1,this));
				
			}
					
	void ModelPush1:: OnUpdate()
			{
			
				physics::JointPtr joint= model->GetJoint("elastic_joint1");
				printf("Enter a stiffness value \n :");
				scanf("%d",&n);
				// 0 refers to revolute or prismatic
				joint->SetStiffness(0,n);
			    stiffness=joint->GetStiffness(0);
			
		    
			    printf("%lf \n",stiffness);
			}
	
	void ModelPush1:: SetStiffness1(const double &_stiff1 )
			{
				// Set the Joints Stiffness 
				physics::JointPtr joint1= model->GetJoint("elastic_joint1");
				
				// 0 refers to revolute or prismatic
				joint1->SetStiffness(0,_stiff1);
				stiffness1=joint1->GetStiffness(0);
					
				    
			    printf("The Stiffness of joint1 is set at %lf \n",stiffness1);
			}
	
	

	//  Callback function to handle incoming messages
	void ModelPush1:: OnRosMsg1(const std_msgs::Float32ConstPtr &_msg1)
			{
				this->SetStiffness1(_msg1->data);
			}
	
	
	
	void ModelPush1:: QueueThread1()
			{
				static const double timeout=0.01;
				while(this->rosNode1->ok())
				{
					this->rosQueue1.callAvailable(ros::WallDuration(timeout));
				}
				
			}
	
	
	
	
	GZ_REGISTER_MODEL_PLUGIN(ModelPush1)
	
}
