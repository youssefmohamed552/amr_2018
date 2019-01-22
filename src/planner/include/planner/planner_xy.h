#ifndef PLANNER_XY_H
#define PLANNER_XY_H

#include <iostream>
//#include <ostream>
#include "nav_msgs/Odometry.h"
#include "nav_msgs/Path.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseStamped.h"
#include "ros/ros.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>

typedef geometry_msgs::Pose Pose;


class Vertex{
	private:
		Pose m_pose;
		std::string m_id;
		double m_g;
		double m_h;
		double m_f;
		Vertex* m_prev;

	public:
		Vertex(Pose pose , Pose goal , Vertex* prev)
			:m_pose(pose) , m_prev(prev)
		{ 
			//std::cout << "creating Vertex from (" << pose.position.x << "," << pose.position.y << ") until (" << goal.position.x << "," << goal.position.y << ")" << std::endl;
			std::stringstream ss;
			ss << pose.position.x << " " << pose.position.y;
			m_id = ss.str(); 
			m_h = dist(pose , goal);
			if(prev) m_g = 0.5 + prev->g();
			else m_g = 0.0;
			//std::cout << m_h <<std::endl;
			m_f = m_g + m_h;
		}

		~Vertex(){
			std::cout << "Vertex destroyed" << std::endl;
		}

		void update_g(double new_g , Vertex* new_prev){
			m_prev = new_prev;
			m_g = new_g;
			m_f = m_g + m_h;
		}


		std::string id(){
			return m_id;
		}

		double g() const {
			return m_g;
		}

		double h()const  {
			return m_h;
		}

		double f() const {
			return m_f;
		}

		Pose pose() const {
			return m_pose;
		}

		Vertex* prev() const {
			return m_prev;
		}

		double dist(Pose p1 , Pose p2){
			//std::cout << "dist" << std::endl;
			return pow((pow((p1.position.x - p2.position.x) , 2.0) + pow((p1.position.y - p2.position.y),2.0)) ,0.5);
		}
	
		bool operator==(const Vertex& v){
			return (m_pose.position.x == v.pose().position.x) && (m_pose.position.y == v.pose().position.y);
		}
		
};


bool operator==(const Pose& p1 , const Pose& p2){
	return (p1.position.x == p2.position.x) && (p1.position.y == p2.position.y);
}




class Comp{
	public:
		bool operator()(const Vertex* v1, const Vertex* v2){
			return v1->f() > v2->f();
		}
};



std::ostream& operator<< (std::ostream& out,const Pose& p){
	//std::cout << "printing vertex" << std::endl;
	out << "( " << p.position.x << " , " << p.position.y << " )";
	return out;
}


std::ostream& operator<< (std::ostream& out,const Vertex& v){
	//std::cout << "printing vertex" << std::endl;
	out << "( " << v.pose().position.x << " , " << v.pose().position.y << " )" << " -> f: " << v.f() << " - h: " << v.h() << " - g: " << v.g() << " - prev: ";
	(v.prev()? out << v.prev()->pose(): out << "NULL");
	return out;
}


namespace std{
	template<> struct hash<Pose>{
		std::size_t operator()(const Pose &pose)const noexcept{
			return (std::hash<double>()(pose.position.x)) ^ (std::hash<double>()(pose.position.y));
		}
	};
}

namespace std{
	template<> struct hash<std::pair<Pose,Vertex*>>{
		std::size_t operator()(const std::pair<Pose,Vertex*> &entry)const noexcept{
			Pose pose = entry.first;
			return (std::hash<double>()(pose.position.x)) ^ (std::hash<double>()(pose.position.y));
		}
	};
}


namespace std{
	template<> struct hash<Vertex*>{
		std::size_t operator()(const Vertex* vertex)const noexcept{
			return (std::hash<double>()(vertex->pose().position.x)) ^ (std::hash<double>()(vertex->pose().position.y));
		}
	};
}


std::ostream& operator<< (std::ostream& out , std::vector<Vertex*>& s){
	for(auto it: s)
		out << *it << std::endl;
	return out;
}

std::ostream& operator<< (std::ostream& out , std::unordered_set<Vertex*> s){
	for(auto it: s)
		out << *it << std::endl;
	return out;
}

class PlannerXY{
	private:
	  //std::unordered_map< Pose , Vertex* > closedlist;
		std::unordered_set<Vertex*> closedlist;
		std::vector<Vertex*> openlist;
		//std::priority_queue<  Vertex* , std::vector<Vertex*> , Comp > openlist;
		std::unordered_set< Vertex *> seen_table;
		
	public:
		PlannerXY();
		virtual ~PlannerXY();

		void handle_odom( const nav_msgs::Odometry::ConstPtr& msg );
		void handle_goal( const geometry_msgs::Pose::ConstPtr& msg );

		void search(const geometry_msgs::Pose& pose, const geometry_msgs::Pose& goal);
		void explore_adj_verteces(Vertex* curr_vertex);
		void path_reconstruction(Vertex* );


		ros::Publisher path_publisher;
		ros::Publisher openlistsize_publisher;
		ros::Publisher closedlistsize_publisher;
		nav_msgs::Odometry _odom;
		nav_msgs::Path _path;
		geometry_msgs::Pose _goal;


};
#endif /* PLANNER_XY_H */
