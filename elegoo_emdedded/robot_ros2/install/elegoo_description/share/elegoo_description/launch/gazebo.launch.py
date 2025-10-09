import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess, IncludeLaunchDescription
from launch.substitutions import LaunchConfiguration, Command
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    # Get package directories
    pkg_elegoo_description = get_package_share_directory('elegoo_description')
    pkg_gazebo_ros = get_package_share_directory('gazebo_ros')
    
    # Path to URDF file
    urdf_file = os.path.join(pkg_elegoo_description, 'urdf', 'Elegoo.urdf')
    
    # Read URDF file
    with open(urdf_file, 'r') as infp:
        robot_desc = infp.read()
    
    # Declare launch arguments
    use_sim_time = LaunchConfiguration('use_sim_time', default='true')
    x_pose = LaunchConfiguration('x_pose', default='0.0')
    y_pose = LaunchConfiguration('y_pose', default='0.0')
    z_pose = LaunchConfiguration('z_pose', default='0.1')
    
    declare_use_sim_time = DeclareLaunchArgument(
        'use_sim_time',
        default_value='true',
        description='Use simulation (Gazebo) clock if true'
    )
    
    declare_x_position = DeclareLaunchArgument(
        'x_pose',
        default_value='0.0',
        description='X position of robot spawn'
    )
    
    declare_y_position = DeclareLaunchArgument(
        'y_pose',
        default_value='0.0',
        description='Y position of robot spawn'
    )
    
    declare_z_position = DeclareLaunchArgument(
        'z_pose',
        default_value='0.1',
        description='Z position of robot spawn'
    )
    
    # Gazebo server launch
    gzserver_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_gazebo_ros, 'launch', 'gzserver.launch.py')
        ),
        launch_arguments={'world': 'worlds/empty.world'}.items()
    )
    
    # Gazebo client launch
    gzclient_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_gazebo_ros, 'launch', 'gzclient.launch.py')
        )
    )
    
    # Robot State Publisher
    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[{
            'use_sim_time': use_sim_time,
            'robot_description': robot_desc
        }]
    )
    
    # Spawn robot in Gazebo
    spawn_entity = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=[
            '-topic', 'robot_description',
            '-entity', 'elegoo_robot',
            '-x', x_pose,
            '-y', y_pose,
            '-z', z_pose
        ],
        output='screen'
    )
    
    # Joint State Publisher (optional - for manual control if needed)
    joint_state_publisher = Node(
        package='joint_state_publisher',
        executable='joint_state_publisher',
        name='joint_state_publisher',
        parameters=[{'use_sim_time': use_sim_time}]
    )
    
    return LaunchDescription([
        declare_use_sim_time,
        declare_x_position,
        declare_y_position,
        declare_z_position,
        gzserver_cmd,
        gzclient_cmd,
        robot_state_publisher,
        spawn_entity,
        joint_state_publisher
    ])
