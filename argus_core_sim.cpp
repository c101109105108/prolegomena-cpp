#include <iostream>
#include <chrono>
#include <cmath>
#include <thread>
#include <fstream>

const int center_pwm = 1365; // and/or 1355 tested center with mirror attached 10-15*x*x
const int pwm_min = 520;
const int pwm_max = 2520;

const float proportional_gain = 0.02f; // Kp -- f = float literal
const float integral_gain = 0.00f;     // Ki -- f = float literal
const float derivative_gain = 0.01f;   // Kd -- f = float literal

struct ControlState {

    float pwm_x = 1365.0f;
    float pwm_y = 1365.0f;
    float prev_error_x = 0.0f;
    float prev_error_y = 0.0f;
    float integral_x = 0.0f;
    float integral_y = 0.0f;

};

void updateControl(ControlState& ctrl, float target_x, float target_y, float laser_x, float laser_y, double dt) {

    float error_x = target_x - laser_x;
    float error_y = target_y - laser_y;

    if (std::abs(error_x) < 3.0f) error_x = 0.0f;
    if (std::abs(error_y) < 3.0f) error_y = 0.0f;

    float p_x = proportional_gain * error_x;

    ctrl.integral_x += (error_x * dt);
    float i_x = integral_gain * ctrl.integral_x;

    float d_x = 0.0f;

    if (dt > 0.0) {
        d_x = derivative_gain * ((error_x - ctrl.prev_error_x) / dt);
    }

    ctrl.pwm_x += (p_x + i_x + d_x);
    ctrl.prev_error_x = error_x;

    float p_y = proportional_gain * error_y;

    ctrl.integral_y += (error_y * dt);
    float i_y = integral_gain * ctrl.integral_y;

    float d_y = 0.0f;
    if (dt > 0.0) {
        d_y = derivative_gain * ((error_y - ctrl.prev_error_y) / dt);
    }

    ctrl.pwm_y += (p_y + i_y + d_y);
    ctrl.prev_error_y = error_y;

    if (ctrl.pwm_x > pwm_max) ctrl.pwm_x = pwm_max;
    if (ctrl.pwm_x < pwm_min) ctrl.pwm_x = pwm_min;
    if (ctrl.pwm_y > pwm_max) ctrl.pwm_y = pwm_max;
    if (ctrl.pwm_y < pwm_min) ctrl.pwm_y = pwm_min;
}

void testControl() {
    ControlState ctrl;

    float target_x = 400.0f;
    float target_y = 300.0f;
    float laser_x = 50.0f;
    float laser_y = 200.0f;

    std::ofstream data_log("argus_core_sim_telemetry.csv");
    data_log << "Elapsed Time(s),Target_X,Target_Y,Laser_X,Laser_Y,Error_X,Error_Y,PWM_X,PWM_Y" << '\n';

    auto start_time = std::chrono::steady_clock::now();
    auto last_time = start_time;

    for (int i = 0; i < 100; i++) {
      
        auto current_time = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = current_time - last_time;
      
        double dt = elapsed.count();
        if (dt == 0.0) dt = 0.001;
      
        std::chrono::duration<double> total_elapsed = current_time - start_time;

        laser_x += (target_x - laser_x) * 0.1f;
        laser_y += (target_y - laser_y) * 0.1f;

        updateControl(ctrl, target_x, target_y, laser_x, laser_y, dt);

        float error_x = target_x - laser_x;
        float error_y = target_y - laser_y;

        data_log << total_elapsed.count() << "," << target_x << "," << target_y << "," << laser_x << "," << laser_y << "," << error_x << "," << error_y << "," << ctrl.pwm_x << "," << ctrl.pwm_y << "\n";

        std::cout << '\n' << "Target_X: " << (int)target_x << " px | Target_Y: " << (int)target_y << " px" << '\n' 
            << "Laser_X: " << (int)laser_x << " px  | Laser_Y: " << (int)laser_y << " px" << '\n' 
            << "Error_X: " << (int)error_x << " px  | Error_Y: " << (int)error_y << " px" << '\n'
            << "Elapsed Time: " << dt << " seconds" << '\n' << "--------";

        if (std::abs(error_x) < 3.0f && std::abs(error_y) < 3.0f) {
            std::cout << " [ LOCKED ] --------";
        }

        last_time = current_time;

        std::this_thread::sleep_for(std::chrono::milliseconds(30)); //delay
    }
  
    data_log.close();
}

int main() {
  
    testControl();
    return 0;
}
