#include<rclcpp/rclcpp.hpp>
#include<geometry_msgs/msg/twist_stamped.hpp>

class ControladorTeclado  : public rclcpp::Node {
public:
    ControladorTeclado(const std::string &name);
    void callb();

private:
    void lectura_teclado(const int &msg, const double &vel);

    rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr leer_teclado_;
};
