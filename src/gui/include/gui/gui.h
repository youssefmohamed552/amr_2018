#ifndef GUI_H
#define GUI_H

#include <iostream>
#include "ros/ros.h"

#include <QtOpenGL/QGLWidget>
#include <QtGui/QKeyEvent>
#include <QtCore/QTimer>

#include "geometry_msgs/Point.h"
#include "nav_msgs/Path.h"
#include "nav_msgs/Odometry.h"
#include "sensor_msgs/LaserScan.h"

class GUI: public QGLWidget {
	Q_OBJECT;
	public:
		GUI(QWidget * parent = NULL);
		virtual ~GUI();

		void handleLaserScan( const sensor_msgs::LaserScan::ConstPtr& msg);
		void handleOdom( const nav_msgs::Odometry::ConstPtr& msg);
		void handleGoal( const geometry_msgs::Pose::ConstPtr& msg);
		void handlePath( const nav_msgs::Path::ConstPtr& msg);
		void handleProjection( const nav_msgs::Path::ConstPtr& msg);
		void handleLookahead( const geometry_msgs::Point::ConstPtr& msg);

	protected slots:
		void timer_callback( void );

	protected:
		virtual void initializeGL();
		virtual void resizeGL(int width, int height);
		virtual void paintGL();
		void drawCoordinateSystem(void );
		void drawGrid();
		void drawLaserScan( const sensor_msgs::LaserScan& laserscan, const double& red = 0.0, const double& green = 0.0 , const double& blue = 0.0 );
		void drawRobot( const geometry_msgs::Pose& pose , const double& red = 0.0 , const double& green = 0.0 , const double& blue = 0.0, const double& radius = 0.1225);
		void drawPath( const nav_msgs::Path& path , const double& red = 0.0 , const double& green = 0.0 , const double& blue = 0.0 , const double& width = 1.0 );
		void drawPoint( const geometry_msgs::Point& point, const double& red = 0.0, const double& green = 0.0 , const double& blue = 0.0 , const double& size = 1.0);
		virtual void keyPressEvent(QKeyEvent* event);

		QTimer _timer;
		
		double _zoom;
		std::pair< double , double > _center;

		sensor_msgs::LaserScan _laserscan;
		nav_msgs::Odometry _odom;
		nav_msgs::Path _path;
		nav_msgs::Path _projection;
		geometry_msgs::Pose _goal;
		geometry_msgs::Point _lookahead;

};
#endif /* GUI_H */

