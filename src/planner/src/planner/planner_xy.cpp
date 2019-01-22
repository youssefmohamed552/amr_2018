#include <planner/planner_xy.h>

PlannerXY::
PlannerXY(){

}

PlannerXY::
~PlannerXY(){

}

void
PlannerXY::
search( const geometry_msgs::Pose& pose , const geometry_msgs::Pose& goal ){
	//std::cout << "the search" << std::endl;


//	goal.position.x = 0;
	//add the first node to the open list
	Vertex* start_vertex = new Vertex( pose , goal , nullptr );
	_goal = goal;


	//std::cout << "about to print" <<std::endl;
	//std::cout << *start_vertex << std::endl;
	//Vertex goal_vertex( goal , goal , nullptr );
  openlist.push_back(start_vertex);
	//std::push_heap(openlist.begin(),openlist.end(),Comp);
	//seen_table.insert(start_vertex);
	
	// std::cout << "--------------------" << std::endl;
	// std::cout << "////Open list : " << std::endl << openlist;
	// std::cout << "--------------------" << std::endl;
	Vertex* curr_vertex;

	int i = 0;
	//loop
	while(true){
		// std::cout << "***********************************************" << std::endl;
		// std::cout << "************* ROUND " << i <<  " *************************" << std::endl;
		// std::cout << "***********************************************" << std::endl;
		//pop the node from the open list and assign it to current while adding it to the closed list
		
		curr_vertex = openlist.front();
		//std::cout << curr_vertex << std::endl;
		//std::pair<geometry_msgs::Pose , Vertex> entry(curr_vertex.pose(), curr_vertex);
		//std::pair<Pose, Vertex*> entry(curr_vertex->pose(),curr_vertex);
		closedlist.insert( curr_vertex );
		std::pop_heap(openlist.begin(), openlist.end() , Comp());
		openlist.pop_back();
		// std::cout << "--------------------" << std::endl;
		// std::cout << "////Open list : " << std::endl <<  openlist;
		// std::cout << "--------------------" << std::endl;

		// std::cout << "--------------------" << std::endl;
		// std::cout << "////Closed list : " <<  std::endl << closedlist;
		// std::cout << "--------------------" << std::endl;


		//if current is goal then return
		if(curr_vertex->pose() == _goal)break; 

		//explore all adjacent nodes and add them to the open list
		explore_adj_verteces(curr_vertex);
		//print_open_list();

		i++;
	}
	//fill the path from the nodes aquired
	//std::cout << "open list size : " << openlist.size() << std::endl;
	
	// std::cout << "--------------------" << std::endl;
	// std::cout << "seen : " << std::endl <<  seen_table;
	// std::cout << "--------------------" << std::endl;
	std::cout << "--------------------" << std::endl;
	//std::cout << "last closed list : " << std::endl <<  closedlist;
	std::cout << "--------------------" << std::endl;

	path_reconstruction(curr_vertex);

	path_publisher.publish(_path);


	delete start_vertex;

}
void
PlannerXY::
explore_adj_verteces(Vertex* curr_vertex){
	double m = 0.5;
	double dx[] = {m , m , 0 , -m , -m , -m , 0 , m};
	double dy[] = {0 , -m , -m , -m , 0 , m , m , m};
	
	//loop through all possible adj verteces
	for(unsigned int i = 0; i < 8; i++){
		//check all the possible nodes
		geometry_msgs::Pose possible_pose;
		possible_pose.position.x = curr_vertex->pose().position.x + dx[i];
		possible_pose.position.y = curr_vertex->pose().position.y + dy[i];
		//Vertex possible_vertex(possible_pose , _goal , curr_vertex);

		Vertex* poss = new Vertex(possible_pose, _goal, curr_vertex);
		auto existing_pos = seen_table.find(poss);
		if( existing_pos != seen_table.end()) {
			//if found then assign a better path.
			if( (*existing_pos)->g() > poss->g() ){
				(*existing_pos)->update_g(poss->g() , curr_vertex);
				std::make_heap(openlist.begin(), openlist.end(), Comp());
			}
			continue;
		}
		openlist.push_back(poss);
		std::push_heap(openlist.begin(), openlist.end(), Comp());
		seen_table.insert(poss);
		// std::cout << "--------------------" << std::endl;
		// std::cout << "////Open list : " << std::endl <<  openlist;
		// std::cout << "--------------------" << std::endl;
		//std::cout << "top : " << *openlist.top() << std::endl;

		//if(closedlist[possible_pose]) continue;
		//if(openlist.contains(possible_pose)){
		//	if(openlist[possible_pose].g() < possible_vertex.g()) continue;
		//	else openlist.erase(
		
	}
}


void
PlannerXY::
path_reconstruction(Vertex* g_vertex){
	//store the poses out of the closed list in a stack;
	std::stack<Pose> s;
	Vertex* v = g_vertex;
	while(v){
		s.push(v->pose());
		v = v->prev();
	}


	// push the poses out of the stack into the path
	while(!s.empty()){
		geometry_msgs::PoseStamped pose_stamped;
		pose_stamped.pose = s.top();
		_path.poses.push_back(pose_stamped);
		s.pop();
	}

	//std::cout << *(g_vertex) << std::endl;
	//std::cout << *(g_vertex->prev()) << std::endl;
	for(auto it: _path.poses){
		std::cout << it.pose << std::endl;
	}

}

void
PlannerXY::
handle_odom( const nav_msgs::Odometry::ConstPtr& msg ){
	_odom = *msg;
	return;
}

void
PlannerXY::
handle_goal( const geometry_msgs::Pose::ConstPtr& msg ){
	search( _odom.pose.pose , *msg );
	return;
}

