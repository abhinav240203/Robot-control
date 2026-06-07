import rclpy
from rclpy.node import Node
from rcl_interfaces.msg import SetParametersResult
from rclpy.parameter import Parameter   

class SimpleParameters(Node):
    def __init__(self):
        super().__init__('simple_parameters')
        self.declare_parameter('simple_int_param', 42)
        self.declare_parameter('simple_str_param', 'Hello, ROS 2!')
        self.add_on_set_parameters_callback(self.parameter_callback)    
        
    def parameter_callback(self, params):
        result = SetParametersResult()
        for param in params:
            if param.name == 'simple_int_param':
                if param.type_ == rclpy.Parameter.Type.INTEGER:
                    self.get_logger().info(f"Received new integer parameter: {param.value}")
                    result.successful = True
                else:
                    self.get_logger().error("simple_int_param must be an integer.")
                    result.successful = False
                    result.reason = "simple_int_param must be an integer."
            elif param.name == 'simple_str_param':
                if param.type_ == rclpy.Parameter.Type.STRING:
                    self.get_logger().info(f"Received new string parameter: {param.value}")
                    result.successful = True
                else:
                    self.get_logger().error("simple_str_param must be a string.")
                    result.successful = False
                    result.reason = "simple_str_param must be a string."
        return result
    
def main():
    rclpy.init()
    node = SimpleParameters()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
if __name__ == '__main__':
    main()