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

double stiffness2;

double stiffness;
int n;

namespace gazebo 
{
	class ModelPush2 : public ModelPlugin
	{
		
		public: 
		    // Called by world update start event
			void Load(physics::ModelPtr _parent,sdf::ElementPtr /*_sdf*/);
		
			void OnUpdate();
			
			void SetStiffness2(const double &_stiff2);
			
			// Callback Function
			void OnRosMsg2(const std_msgs::Float32ConstPtr &_msg2);
			
			
		private:
			    //  Pointer to model
				physics::ModelPtr model;
					
				event::ConnectionPtr updateConnection;
				
				// Node used for ROS transport
				std::unique_ptr<ros::NodeHandle> rosNode2;
				
				//A ROS subscriber to a named topic
				ros::Subscriber rosSub2;
				
				// Helps process messages on the topic
				ros::CallbackQueue rosQueue2;
				
				std::thread rosQueueThread2;
				
				
				// Helper Function that processes messages
				void QueueThread2();
		
		};
	
	
	void ModelPush2::Load(physics::ModelPtr _parent,sdf::ElementPtr _sdf)
			{
				this->model= _parent;
				
			    // Callback On Update Function type.
				this->updateConnection =event::Events::ConnectPause(boost::bind(&ModelPush2::OnUpdate,this));
				
				//Initialize ROS
				if (!ros::isInitialized())
				{
					int argc=0;
					char **argv=NULL;
					ros::init(argc,argv,"gazebo_client",ros::init_options::NoSigintHandler);
				}
					
				//Create our ROS node
				this->rosNode2.reset(new ros::NodeHandle("gazebo_client2"));
				
				// Create a topic name
				ros::SubscribeOptions so2= ros::SubscribeOptions::create<std_msgs::Float32>("/" + this->model->GetName()+"/joint2" + "/stiffness_cmd",1,boost::bind(&ModelPush2::OnRosMsg2,this,_1),ros::VoidPtr(),&this->rosQueue2);
				
				
				// Subscribe to this topic and register a callback
				this->rosSub2= this->rosNode2->subscribe(so2);
				
				
				//Spin up queue helper thread
				this->rosQueueThread2=std::thread(std::bind(&ModelPush2::QueueThread2,this));
				
			}
					
	void ModelPush2:: OnUpdate()
			{
			
				physics::JointPtr joint= model->GetJoint("elastic_joint2");
				printf("Enter a stiffness value \n :");
				scanf("%d",&n);
				// 0 refers to revolute or prismatic
				joint->SetStiffness(0,n);
			    stiffness=joint->GetStiffness(0);
			
		    
			    printf("%lf \n",stiffness);
			}
	
	void ModelPush2:: SetStiffness2(const double &_stiff2 )
			{
				// Set the Joints Stiffness 
				physics::JointPtr joint2= model->GetJoint("elastic_joint2");
				
				// 0 refers to revolute or prismatic
				joint2->SetStiffness(0,_stiff2);
				stiffness2=joint2->GetStiffness(0);
					
				    
			    printf("The Stiffness of joint2 is set at %lf \n",stiffness2);
			}
	
	

	//  Callback function to handle incoming messages
	void ModelPush2:: OnRosMsg2(const std_msgs::Float32ConstPtr &_msg2)
			{
				this->SetStiffness2(_msg2->data);
			}
	
	
	
	void ModelPush2:: QueueThread2()
			{
				static const double timeout=0.01;
				while(this->rosNode2->ok())
				{
					this->rosQueue2.callAvailable(ros::WallDuration(timeout));
				}
				
			}
	
	
	
	
	GZ_REGISTER_MODEL_PLUGIN(ModelPush2)
	
}
