#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

#include <rcl_interfaces/msg/set_parameters_result.hpp>

#include <string>
#include <vector>
#include <memory>


using std::placeholders::_1;

using namespace std::chrono_literals;


class SimpleParameterNode : public rclcpp::Node
{
public:
    SimpleParameterNode() : Node("simple_parameter_node")
    {
        declare_parameter<int>("simple_int_param", 42);
        declare_parameter<std::string>("simple_string_param", "Hello, ROS2!");

        parameter_callback_handle_ = add_on_set_parameters_callback(std::bind(&SimpleParameterNode::parametercallback, this, _1));

    }

private:
    OnSetParametersCallbackHandle::SharedPtr parameter_callback_handle_;

    rcl_interfaces::msg::SetParametersResult parametercallback(const std::vector<rclcpp::Parameter> &parameters)
    {
        rcl_interfaces::msg::SetParametersResult result;
        result.successful = true;
        result.reason = "Parameters set successfully.";

        for (const auto &param : parameters)
        {
            if (param.get_name() == "simple_int_param" && param.get_type() == rclcpp::ParameterType::PARAMETER_INTEGER)
            {
                RCLCPP_INFO_STREAM(get_logger(), "Received new value for simple_int_param: " << param.as_int());
            }
            else if (param.get_name() == "simple_string_param" && param.get_type() == rclcpp::ParameterType::PARAMETER_STRING)
            {
                RCLCPP_INFO_STREAM(get_logger(), "Received new value for simple_string_param: " << param.as_string());
            }
        } 

        return result;
    }

};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SimpleParameterNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
