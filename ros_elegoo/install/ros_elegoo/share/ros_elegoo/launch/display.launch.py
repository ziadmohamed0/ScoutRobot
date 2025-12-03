#!/usr/bin/env python3
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    # Get package directory
    pkg_share = get_package_share_directory('ros_elegoo')
    
    # Path to URDF file
    urdf_file = os.path.join(pkg_share, 'urdf', 'ros_elegoo.urdf')
    
    # Read URDF content
    with open(urdf_file, 'r') as f:
        urdf_content = f.read()
    
    # Declare launch arguments
    model_arg = DeclareLaunchArgument(
        'model',
        default_value=urdf_file,
        description='Absolute path to robot URDF file'
    )
    
    rviz_arg = DeclareLaunchArgument(
        'rviz',
        default_value='true',
        description='Launch RViz'
    )
    
    # Robot state publisher node
    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        parameters=[{'robot_description': urdf_content}],
        arguments=[urdf_file]
    )
    
    # Joint state publisher with GUI
    joint_state_publisher = Node(
        package='joint_state_publisher_gui',
        executable='joint_state_publisher_gui',
        output='screen'
    )
    
    # RViz node (conditional)
    rviz = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        output='screen',
        condition=IfCondition(LaunchConfiguration('rviz'))
    )
    
    return LaunchDescription([
        model_arg,
        rviz_arg,
        robot_state_publisher,
        joint_state_publisher,
        rviz
    ])
