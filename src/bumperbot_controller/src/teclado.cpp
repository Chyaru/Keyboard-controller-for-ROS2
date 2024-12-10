#include"bumperbot_controller/teclado.hpp"
#include<iostream>
#include<unistd.h>
#include<termios.h>

using std::placeholders::_1;
using std::placeholders::_2;


char getchar_(){
    char buf=0;
    struct termios old={0};
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1)<0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
} 


ControladorTeclado::ControladorTeclado(const std::string &name) : Node(name){
    leer_teclado_ = create_publisher<geometry_msgs::msg::TwistStamped>("/bumperbot_controller/cmd_vel", 10);
    RCLCPP_INFO_STREAM(get_logger(), "Publisher en ejecusion");
    ControladorTeclado::callb();

}

void ControladorTeclado::callb(){
    double vel = 0.2;
    while(1){
        char x = getchar_();
        int y = -1;
        if(x=='W') {
            y = 0;
        }else if(x=='S'){
            y=1;
        }else if(x=='D'){
            y=2;
        }else if(x=='A'){
            y=3;
        }else if(x=='Q'){
            y=4;
        }else if(x=='E'){
            vel+=0.1;
        }else if(x=='R'){
            vel-=0.1;
        }
        if(y==4) break;
        ControladorTeclado::lectura_teclado(y,vel);
    }
    rclcpp::shutdown();
}

void ControladorTeclado::lectura_teclado(const int &msg, const double &vel){
    geometry_msgs::msg::TwistStamped velocidad;
    if(msg==-1){
        velocidad.twist.linear.x = 0;
        velocidad.twist.angular.z = 0;
    }else if(msg==0){
        velocidad.twist.linear.x = vel;
        velocidad.twist.angular.z = 0;
    }else if(msg==1){
        velocidad.twist.linear.x = -vel;
        velocidad.twist.angular.z = 0;
    }else if(msg==2){
        velocidad.twist.linear.x = 0;
        velocidad.twist.angular.z = vel;
    }else{
        velocidad.twist.linear.x = 0;
        velocidad.twist.angular.z = -vel;
    }
    if(msg!=-1)
        RCLCPP_INFO_STREAM(get_logger(), "sending linear velocity: ["<<velocidad.twist.linear.x << "] angular velocity: ["<<velocidad.twist.angular.z<<"]");
    else 
        RCLCPP_INFO_STREAM(get_logger(), "STOPPING THE ROBOT, current velocity: ["<<vel<<"]");
    leer_teclado_->publish(velocidad);
    return;

}
int main(int argc, char ** argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ControladorTeclado>("teclado_");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}