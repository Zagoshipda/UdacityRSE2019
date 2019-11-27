#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot [DONE]
    ROS_INFO_STREAM("Driving the robot...!");

    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    // Call the DriveToTarget service and pass the velocities [DONE]
    if (!client.call(srv))
        ROS_ERROR("Failed to call service DriveToTarget");

}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;

    // TODO: Loop through each pixel in the image and check if there's a bright white one [DONE]
    // Then, identify if this pixel falls in the left, mid, or right side of the image [DONE]
    // Depending on the white ball position, call the drive_bot function and pass velocities to it [DONE]
    // Request a stop when there's no white ball seen by the camera [DONE]

    int cntLeft = 0;
    int cntRight = 0;
    int cntForward = 0;

    // height : # of rows, width : # of columns
    for(int i=0; i<img.height; i++){
        for(int j=0; j<img.width; j++){
            if ((img.data[i*img.width*3 + j*3 + 0] == white_pixel)
                && (img.data[i*img.width*3 + j*3 + 1] == white_pixel)
                && (img.data[i*img.width*3 + j*3 + 2] == white_pixel)){
                    
                if (j < img.width/3){
                    cntLeft++;
                } 
                else if (j < 2*img.width/3){
                    cntForward++;
                } 
                else{
                    cntRight++;
                } 
            }
        }
    }

    // for (int i = 0; i < img.step/3; i++) {
    //     for (int j=0; j<img.height; j++){
    //         if (img.data[j*img.step + i] == white_pixel) {
    //             cntLeft++;
    //         }
    //     }
    // }
    // for (int i = img.step/3; i < 2*img.step/3; i++) {
    //     for (int j=0; j<img.height; j++){
    //         if (img.data[j*img.step + i] == white_pixel) {
    //             cntForward++;
    //         }
    //     }
    // }
    // for (int i = 2*img.step/3; i < img.step; i++) {
    //     for (int j=0; j<img.height; j++){
    //         if (img.data[j*img.step + i] == white_pixel) {
    //             cntRight++;
    //         }
    //     }
    // }

    std::string out;

    if(cntLeft == 0 && cntForward == 0 && cntRight == 0){
        out = "stop";
    }
    else if(cntLeft >= cntForward && cntLeft >= cntRight){
        out = "left";
    }
    else if(cntForward >= cntLeft && cntForward >= cntRight){
        out = "forward";
    }
    else if(cntRight >= cntForward && cntRight >= cntLeft){
        out = "right";
    }

    if(out == "stop"){
        drive_robot(0.0, 0.0);
    }
    else if(out == "left"){
        drive_robot(0.0, 0.5);
    }
    else if(out == "forward"){
        drive_robot(0.5, 0.0);
    }
    else if(out == "right"){
        drive_robot(0.0, -0.5);
    }



}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}