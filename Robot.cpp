#include "Robot.h"

Robot::Robot(int camera_id, cv::String window_name, std::string port_name){
    this->state = RobotState(0, false, 1, _U);
    this->setCameraId(camera_id);
    this->setSquareCount(0);
    this->setWindowName(window_name);

    /* The order is : White - Green - Red - Blue - Orange - Yellow */
    this->minColor = { Scalar(0, 0, 130), Scalar(46, 100, 100), Scalar(120, 100, 100), Scalar(75, 100, 100), Scalar(5, 100, 100), Scalar(20, 100, 100) };
    this->maxColor = { Scalar(255, 110, 255), Scalar(100, 255, 255), Scalar(180, 255, 255), Scalar(130, 255, 255), Scalar(15, 255, 255), Scalar(40, 255, 255) };
}

void Robot::sendRubikMoves(std::vector<std::string> rubikMoves) {
    for (unsigned int i = 0; i < rubikMoves.size(); i++) {
        this->addMove(rubikMoves[i]);
    }
    this->endMove();
}

bool Robot::initRobotMove() {
        if (sendMessageAndRead(robot_init)) {
            return true;
        }
        return false;
}

void Robot::printSentRobotMoves() {
    int size = rmoves.size();
    for (int i = 0; i < size; i++) {
        std::string m = rmoves[i];
        if (m == robot_U0_to_1) {
            std::cout << "U0_to_1 ";
        }
        else if (m == robot_U1_to_0) {
            std::cout << "U1_to_0 ";
        }
        else if (m == robot_U0_to_2) {
            std::cout << "U0_to_2 ";
        }
        else if (m == robot_U2_to_0) {
            std::cout << "U2_to_0 ";
        }
        else if (m == robot_U1_to_2) {
            std::cout << "U1_to_2 ";
        }
        else if (m == robot_U2_to_1) {
            std::cout << "U2_to_1 ";
        }
        else if (m == robot_H0_to_3) {
            std::cout << "H0_to_3 ";
        }
        else if (m == robot_D3_to_0) {
            std::cout << "D3_to_0 ";
        }
        else if (m == robot_H0_to_2) {
            std::cout << "H0_to_2 ";
        }
        else if (m == robot_D2_to_0) {
            std::cout << "D2_to_0 ";
        }
        else if (m == robot_H0_to_1) {
            std::cout << "H0_to_1 ";
        }
        else if (m == robot_D1_to_0) {
            std::cout << "D1_to_0 ";
        }
        else if (m == robot_H1_to_2) {
            std::cout << "H1_to_2 ";
        }
        else if (m == robot_D2_to_1) {
            std::cout << "D2_to_1 ";
        }
        else if (m == robot_H1_to_3) {
            std::cout << "H1_to_3 ";
        }
        else if (m == robot_D3_to_1) {
            std::cout << "D3_to_1 ";
        }
        else if (m == robot_H2_to_3) {
            std::cout << "H2_to_3 ";
        }
        else if (m == robot_D3_to_2) {
            std::cout << "D3_to_2 ";
        }
        else if (m == robot_Bi) {
            std::cout << "Bi ";
        }
        else if (m == robot_B) {
            std::cout << "B ";
        }
    }
    std::cout << std::endl;
}

void Robot::printSimplifiedSentRobotMoves() {
    int size = rmoves.size();
    for (int i = 0; i < size; i++) {
        std::string m = rmoves[i];
        if (m == robot_U0_to_1) {
            std::cout << "U ";
        }
        else if (m == robot_U1_to_0) {
            std::cout << "Ui ";
        }
        else if (m == robot_U0_to_2) {
            std::cout << "U ";
        }
        else if (m == robot_U2_to_0) {
            std::cout << "Ui ";
        }
        else if (m == robot_U1_to_2) {
            std::cout << "U ";
        }
        else if (m == robot_U2_to_1) {
            std::cout << "Ui ";
        }
        else if (m == robot_H0_to_3) {
            std::cout << "H3 ";
        }
        else if (m == robot_D3_to_0) {
            std::cout << "D3 ";
        }
        else if (m == robot_H0_to_2) {
            std::cout << "H2 ";
        }
        else if (m == robot_D2_to_0) {
            std::cout << "D2 ";
        }
        else if (m == robot_H0_to_1) {
            std::cout << "H1 ";
        }
        else if (m == robot_D1_to_0) {
            std::cout << "D1 ";
        }
        else if (m == robot_H1_to_2) {
            std::cout << "H1 ";
        }
        else if (m == robot_D2_to_1) {
            std::cout << "D1 ";
        }
        else if (m == robot_H1_to_3) {
            std::cout << "H2 ";
        }
        else if (m == robot_D3_to_1) {
            std::cout << "D2 ";
        }
        else if (m == robot_H2_to_3) {
            std::cout << "H1 ";
        }
        else if (m == robot_D3_to_2) {
            std::cout << "D1 ";
        }
        else if (m == robot_Bi) {
            std::cout << "Bi ";
        }
        else if (m == robot_B) {
            std::cout << "B ";
        }
    }
    std::cout << std::endl;
}

int Robot::getRubikMovesCost(std::vector<std::string> rubikMoves, std::string previousRubikMove) {

    RobotState previousState;
    if (previousRubikMove == "") {
        previousState = this->state;
    }
    else {
        previousState = RobotState::getState(previousRubikMove);
    }
    int cost = 0;
    int size = rubikMoves.size();
    for (int i = 0; i < size; i++) {
        RobotState state = RobotState::getState(rubikMoves[i]);
        //Check referential
        if (state.referential != previousState.referential) {
            if (state.referential == _R) {
                if (previousState.referential == _U) {
                    if (previousState.height != 3) {
                        cost++; //H
                        previousState.height = 3;
                    }
                }
                if (previousState.referential == _F) {
                    cost+= 2; //H B
                }
                cost += 3; //U D B
                previousState.referential = _R;
            }
            else { //going to U or F
                if (previousState.height > 0) {
                    cost++;
                    previousState.height = 0;
                }
                if (previousState.referential == _R) //R --> U  or F
                {
                    cost += 3;//Bi H Ui
                    if (state.referential == _F)
                    {
                        cost++;
                    }
                }
                else { //U --> F || F --> U
                    cost++; //Bi or B
                }
            }
        }
        previousState.referential = state.referential;


        //Check height
        if (previousState.height != state.height) {
            cost++;
            previousState.height = state.height;
        }

        //Check rotation
        if (state.rotator != 0) {
            previousState.rotator += state.rotator;
            cost++;
        }

    }
    return cost;

}

bool Robot::sendMessageAndRead(std::string m) {
    if (this->controller.send(m[0]) || ROBOT_DEBUG){ //Blocks until the robot responds (if ROBOT_DEBUG == 0)
        rmoves.push_back(m);
        return true;
    }

    return false;
}

bool Robot::U0_to_1() {
    if (state.rotator == 0 && sendMessageAndRead(robot_U0_to_1)) {
        state.rotator = 1;
        return true;
    }
    return false;
}

bool Robot::U0_to_2() {
    if (state.rotator == 0 && sendMessageAndRead(robot_U0_to_2)) {
        state.rotator = 2;
        return true;
    }
    return false;
}

bool Robot::U1_to_0() {
    if (state.rotator == 1 && sendMessageAndRead(robot_U1_to_0)) {
        state.rotator = 0;
        return true;
    }
    return false;
}

bool Robot::U1_to_2() {
    if (state.rotator == 1 && sendMessageAndRead(robot_U1_to_2)) {
        state.rotator = 2;
        return true;
    }
    return false;
}

bool Robot::U2_to_0() {
    if (state.rotator == 2 && sendMessageAndRead(robot_U2_to_0)) {
        state.rotator = 0;
        return true;
    }
    return false;
}

bool Robot::U2_to_1() {
    if (state.rotator == 2 && sendMessageAndRead(robot_U2_to_1)) {
        state.rotator = 1;
        return true;
    }
    return false;
}

bool Robot::U0() {
    switch (state.rotator) {
    case 1:
        return U1_to_0();
    case 2:
        return U2_to_0();
    default:
        return false;
    }
}

bool Robot::U1() {
    switch (state.rotator) {
    case 0:
        return U0_to_1();
    case 2:
        return U2_to_1();
    default:
        return false;
    }
}

bool Robot::U2() {
    switch (state.rotator) {
    case 0:
        return U0_to_2();
    case 1:
        return U1_to_2();
    default:
        return false;
    }
}

bool Robot::U() {
    if (state.rotator == 0) {
        return U1();
    }
    else if (state.rotator == 1) {
        return U2();
    }
    return false;
}
bool Robot::Ui() {
    if (state.rotator == 1) {
        return U0();
    }
    else if (state.rotator == 2) {
        return U1();
    }
    return false;
}

bool Robot::H0_to_1() {
    if (state.height == 0 && sendMessageAndRead(robot_H0_to_1)) {
        state.height = 1;
        return true;
    }

    return false;
}
bool Robot::H0_to_2() {
    if (state.height == 0 && sendMessageAndRead(robot_H0_to_2)) {
        state.height = 2;
        return true;
    }

    return false;
}
bool Robot::H0_to_3() {
    if (state.height == 0 && sendMessageAndRead(robot_H0_to_3)) {
        state.height = 3;
        return true;
    }

    return false;
}
bool Robot::H1_to_2() {
    if (state.height == 1 && sendMessageAndRead(robot_H1_to_2)) {
        state.height = 2;
        return true;
    }

    return false;
}
bool Robot::H1_to_3() {
    if (state.height == 1 && sendMessageAndRead(robot_H1_to_3)) {
        state.height = 3;
        return true;
    }

    return false;
}
bool Robot::H2_to_3() {
    if (state.height == 2 && sendMessageAndRead(robot_H2_to_3)) {
        state.height = 3;
        return true;
    }
    return false;
}

bool Robot::D3_to_0() {
    if (state.height == 3 && sendMessageAndRead(robot_D3_to_0)) {
        state.height = 0;
        return true;
    }
    return false;
}
bool Robot::D2_to_0() {
    if (state.height == 2 && sendMessageAndRead(robot_D2_to_0)) {
        state.height = 0;
        return true;
    }
    return false;
}
bool Robot::D1_to_0() {
    if (state.height == 1 && sendMessageAndRead(robot_D1_to_0)) {
        state.height = 0;
        return true;
    }
    return false;
}
bool Robot::D2_to_1() {
    if (state.height == 2 && sendMessageAndRead(robot_D2_to_1)) {
        state.height = 1;
        return true;
    }
    return false;
}
bool Robot::D3_to_2() {
    if (state.height == 3 && (robot_D3_to_2)) {
        state.height = 2;
        return true;
    }
    return false;
}
bool Robot::D3_to_1() {
    if (state.height == 3 && sendMessageAndRead(robot_D3_to_1)) {
        state.height = 1;
        return true;
    }
    return false;
}

bool Robot::H1() {
    switch (state.height) {
    case 0:
        return H0_to_1();
    case 1:
        return H1_to_2();
    case 2:
        return H2_to_3();
    default:
        return false;
    }
}
bool Robot::H2() {
    switch (state.height) {
    case 0:
        return H0_to_2();
    case 1:
        return H1_to_3();
    default:
        return false;
    }

}
bool Robot::H3() {
    if (state.height == 0) {
        return H0_to_3();
    }
    return false;

}
bool Robot::D1() {
    switch (state.height) {
    case 3:
        return D3_to_2();
    case 2:
        return D2_to_1();
    case 1:
        return D1_to_0();
    default:
        return false;
    }
}
bool Robot::D2() {
    switch (state.height) {
    case 3:
        return D3_to_1();
    case 2:
        return D2_to_0();
    default:
        return false;
    }
}
bool Robot::D3() {
    if (state.height == 3) {
        return D3_to_0();
    }
    return false;
}


bool Robot::B() {
    if (state.balancer && sendMessageAndRead(robot_B)) {
        state.balancer = false;
        return true;
    }
    return false;
}

bool Robot::Bi() {
    if (!state.balancer && sendMessageAndRead(robot_Bi)) {
        state.balancer = true;
        return true;
    }
    return false;
}

void Robot::resetHeight() {
    if (state.height == 3) {
        D3();
    }
    else if (state.height == 2) {
        D2();
    }
    else if (state.height == 1) {
        D1();
    }
}

void Robot::goDown(int height) {
    switch (height) {
    case 3:
        D3();
        break;
    case 2:
        D2();
        break;
    case 1:
        D1();
        break;
    default:
        break;
    }
}

void Robot::goUp(int height) {
    switch (height) {
    case 3:
        H3();
        break;
    case 2:
        H2();
        break;
    case 1:
        H1();
        break;
    default:
        break;
    }
}

void Robot::rotate(int rotation) {
    if (rotation > 0) {
        while (rotation > 0) {
            U();
            rotation--;
        }
    }
    else {
        while (rotation < 0) {
            Ui();
            rotation++;
        }
    }
}

void Robot::addHeight(int height) {
    int result = height - this->state.height;
    if (result < 0) {
        goDown(-result);
    }
    else if (result > 0) {
        goUp(result);
    }
}

void Robot::addMove(std::string rubikMove) {

    //V�rification du r�f�rentiel
    //Si le mouvement est L, Li, B, Bi, D ou Di, le r�f�rentiel a chang�.
    if (this->previousRubikMove == _L || previousRubikMove == _B || previousRubikMove == _D) {
        goUp(3 - this->state.height); //Go to top
        Ui(); //Go back to previous referential
    }
    else if (previousRubikMove == _Li || previousRubikMove == _Bi || previousRubikMove == _Di) {
        goUp(3 - this->state.height); //Go to top
        U(); //Go back to previous referential
    }

    this->previousRubikMove = rubikMove;

    RobotState state = RobotState::getState(rubikMove);

    //V�rification du r�f�rentiel (Le balancier est donc g�r�)
        //Si changement : hauteur = 0
    if (state.referential != this->state.referential) {
        if (this->state.referential == _U) {
            if (state.referential == _F) {
                resetHeight();
                Bi();
            }
            else if (state.referential == _R) {
                if (this->state.rotator == 2) {
                    resetHeight();
                    Ui();
                }
                goUp(3 - this->state.height);
                U(); D3(); Bi();
            }
        }
        else if (this->state.referential == _F) {
            resetHeight();
            if (state.referential == _U) {
                B();
            }
            else if (state.referential == _R) {
                if (this->state.rotator == 2) {
                    Ui();
                }
                B(); H3(); U(); D3(); Bi();
            }
        }
        else if (this->state.referential == _R) {
            resetHeight();
            if (this->state.rotator == 0) {
                U();
            }
            B(); H3(); Ui();
            if (state.referential == _U) {
                //Done
            }
            else if (state.referential == _F) {
                Bi();
            }
        }
        this->state.referential = state.referential;
    }

    //V�rification mouvement
    if (state.rotator == 1) {
        if (this->state.rotator == 2) {
            resetHeight();
            Ui();
        }
        //else : OK
    }
    else if (state.rotator == -1) {
        if (this->state.rotator == 0) {
            resetHeight();
            U();
        }
        //else : OK
    }
    else if (state.rotator == 2) {
        if (this->state.rotator == 2) {
            state.rotator = -2; //We can rotate backwards to perform U2
        }
        else if (this->state.rotator == 1) {
            resetHeight();
            Ui();
        }
    }

    //Changement de la hauteur
    addHeight(state.height);

    //Mouvement
    rotate(state.rotator);
}

void Robot::endMove() {
    resetHeight();
    /*if (this->state.balancier) {
        Bi();
    }*/
    if (this->state.rotator == 2) {
        Ui();
    }
    if (this->state.rotator == 0) {
        U();
    }
    this->previousRubikMove = "";
}

RobotController& Robot::getController(){
    return this->controller;
}

void Robot::setCameraId(int camera_id){
    this->camera_id = camera_id;
}

int Robot::getCameraId(){
    return this->camera_id;
}

void Robot::setSquareCount(int square_count){
    this->square_count = square_count;
}

int Robot::getSquareCount(){
    return this->square_count;
}

void Robot::setWindowName(String window_name){
    this->window_name = window_name;
}

String Robot::getWindowName(){
    return this->window_name;
}

bool Robot::filterRect(Rect rec){
    /* Delimited a zone on the frame to analyze */
    if (rec.x < 200 || rec.x > 450){
        return false;
    }
    else if (rec.y < 80 || rec.y > 350){
        return false;
    }

    /* Keep only shape with a width and height between 60 and 75*/
    if (rec.width >= 55 && rec.width <= 85){
        if (rec.height >= 55 && rec.height <= 85){
            return true;
        }
    }

    return false;
}

String Robot::defineColorText(int color_id){
    switch (color_id){
        case 0:
            return "W";
        case 1:
            return "G";
        case 2:
            return "R";
        case 3:
            return "B";
        case 4:
            return "O";
        case 5:
            return "Y";
        default:
            return "";
    }
}

bool Robot::isRectCollision(std::vector<SquareRubik> points){
    /* Detect if a cv::Rect intersect an another cv::Rect */
    for (int i = 0; i < points.size(); i++){
        for (int j = i + 1; j < points.size(); j++){
            Rect rec = points.at(i).rect & points.at(j).rect;

            if (rec.x != 0 || rec.y != 0){
                return true;
            }
        }
    }

    return false;
}

int Robot::getNbRectInOtherRect(std::vector<SquareRubik> points){
    int result = 0;
    /* Detect if a cv::Rect is in an another cv::Rect */
    for (int i = 0; i < points.size(); i++){
        for (int j = i + 1; j < points.size(); j++){
            if (((points.at(j).rect.x >= points.at(i).rect.x) && ((points.at(j).rect.x + points.at(j).rect.width) <= (points.at(i).rect.x + points.at(i).rect.width)))
                && ((points.at(j).rect.y >= points.at(i).rect.y) && ((points.at(j).rect.y + points.at(j).rect.height) <= (points.at(i).rect.y + points.at(i).rect.height)))){
                result++;
            }

            if (((points.at(i).rect.x >= points.at(j).rect.x) && ((points.at(i).rect.x + points.at(i).rect.width) <= (points.at(j).rect.x + points.at(j).rect.width)))
                && ((points.at(i).rect.y >= points.at(j).rect.y) && ((points.at(i).rect.y + points.at(i).rect.height) <= (points.at(j).rect.y + points.at(j).rect.height)))){
                result++;
            }
        }
    }
    return result;
}

std::vector<SquareRubik> Robot::isRectInOtherRect(std::vector<SquareRubik> points){
    /* Detect if a cv::Rect is in an another cv::Rect */
    for (int i = 0; i < points.size(); i++){
        for (int j = i + 1; j < points.size(); j++){
            if (((points.at(j).rect.x >= points.at(i).rect.x) && ((points.at(j).rect.x + points.at(j).rect.width) <= (points.at(i).rect.x + points.at(i).rect.width)))
                && ((points.at(j).rect.y >= points.at(i).rect.y) && ((points.at(j).rect.y + points.at(j).rect.height) <= (points.at(i).rect.y + points.at(i).rect.height)))){
                points.erase(points.begin()+j);
            }

            if (((points.at(i).rect.x >= points.at(j).rect.x) && ((points.at(i).rect.x + points.at(i).rect.width) <= (points.at(j).rect.x + points.at(j).rect.width)))
                && ((points.at(i).rect.y >= points.at(j).rect.y) && ((points.at(i).rect.y + points.at(i).rect.height) <= (points.at(j).rect.y + points.at(j).rect.height)))){
                points.erase(points.begin() + i);
            }
        }
    }
    return points;
}

std::vector<std::vector<int>> Robot::formatToAlgorithm(std::vector<std::vector<SquareRubik>> sides) {
    std::vector<std::vector<int>> result;

    for (int i = 0; i < sides.size(); i++){
        std::vector<int> side;
        for (int j = 0; j < sides.at(i).size(); j++){
            side.push_back(sides.at(i).at(j).color);
        }
        result.push_back(side);
    }

    return result;
}

std::vector<SquareRubik> Robot::swap(std::vector<SquareRubik> side, std::vector<int> newIndexes) {
    std::vector<SquareRubik> temp = side;
    int size = newIndexes.size();
    for (int i = 0; i < size; i++) {
        side[i] = temp.at(newIndexes.at(i));
    }

    return side;
}

std::vector<std::vector<SquareRubik>> Robot::formatSides(std::vector<std::vector<SquareRubik>> sides){
    // Convention in order to have the a ordered list which match with the algorithm part as explained in the report
    sides[0] = swap(sides[0], std::vector <int>{ 6, 3, 0, 7, 4, 1, 8, 5, 2 });
    std::reverse(sides[3].begin(), sides[3].end());
    sides[2] = swap(sides[2], std::vector <int>{ 2, 5, 8, 1, 4, 7, 0, 3, 6 });

    std::swap(sides[0], sides[1]);
    std::swap(sides[0], sides[5]);
    std::swap(sides[0], sides[2]);
    std::swap(sides[0], sides[3]);

    return sides;
}

std::vector<std::vector<int>> Robot::launchCapture(){
    VideoCapture cap(this->camera_id);

    //cap.set(CV_CAP_PROP_SETTINGS, 1); // Show the properties window

    // Handle error when opening the camera
    if (!cap.isOpened())
    {
        std::cout << "Cannot open the video file" << std::endl;
        return {};
    }

    namedWindow(this->getWindowName(), CV_WINDOW_AUTOSIZE);

    std::vector<std::vector<SquareRubik>> results;

    // Empty vector in case of skipping side by the user
    std::vector<SquareRubik> empty;
    for (int i = 0; i < 9; i++){
        empty.push_back(SquareRubik(Rect(), cv::Point2f(0, 0), RubikColor(-1)));
    }

    int nb_capture = 0;

    // Detect frame while we have the all sides of the Rubik's Cube
    while (nb_capture < NB_CAPTURE)
    {
        std::vector<SquareRubik> points;
        // Variables's initialization
        std::vector<std::vector<cv::Point> > contours;
        std::vector<Vec4i> hierarchy;

        std::vector<std::vector<std::vector<cv::Point>>> finalContours;

        Mat frame_RGB;
        Mat filter;
        Mat frame_HSV;
        Mat frame_threshed;
        Mat imgray;
        Mat result;

        this->setSquareCount(0); // Initialization : 0 squares found on the actual side
        cap.read(frame_RGB);
        bilateralFilter(frame_RGB, filter, 9, 75, 75);
        cvtColor(filter, frame_HSV, cv::COLOR_BGR2HSV); // Change from RGB to HSV

        // For each color, detect if there is the color in the frame
        for (int i = 0; i < this->minColor.size(); i++){
            inRange(frame_HSV, this->minColor[i], this->maxColor[i], frame_threshed);
            imgray = frame_threshed;
            threshold(frame_threshed, result, 127, 255, 0);

            findContours(result, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
            finalContours.push_back(contours);
        }

        // For each shape found, we filter it and add it if it match
        for (unsigned int j = 0; j < finalContours.size(); j++){
            String text = defineColorText(j); // Letter to display on the camera Window

            for (unsigned int i = 0; i < finalContours[j].size(); i++){
                Rect rec = cv::boundingRect(finalContours[j][i]);

                if (filterRect(rec)){
                    this->setSquareCount(this->getSquareCount() + 1);
                    rectangle(frame_RGB, rec, Scalar(0, 255, 0), 2);
                    putText(frame_RGB, text, cv::Point2f(rec.x + rec.width / 2, rec.y + rec.height / 2), cv::FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0, 0));
                    points.push_back(SquareRubik(rec, cv::Point2f(rec.x, rec.y), RubikColor(j)));
                }
            }
        }

        imshow(this->getWindowName(), frame_RGB); // Display the RGB frame with the found squares


        // If the camera doesn't detect the 9 squares, the user can press 's' to move to the next step
        if (cv::waitKey(20) == 's'){
            results.push_back(empty);
            nb_capture++;
            // Change the position of the Rubik's cube to get the next side
            if (!this->setRobotPosition(nb_capture)){
                throw RobotPositionException("Failed when changing position of the Rubik's cube");
            }
            else {
                cap.read(frame_RGB);
            }

            /*// Debug Mode
            cv::waitKey(2000);
            cap.read(frame_RGB);*/
        }
        else if (this->getSquareCount() - this->getNbRectInOtherRect(points) == 9) { // Found all cube of a side!
            points = isRectInOtherRect(points);
            this->setSquareCount(points.size());

            if (this->getSquareCount() == 9){
                points = sortResult(points);

                results.push_back(points);

                nb_capture++;
                // Change the position of the Rubik's cube to get the next side
                if (!this->setRobotPosition(nb_capture)){
                    throw RobotPositionException("Failed when changing position of the Rubik's cube");
                }
                else {
                    cap.read(frame_RGB);
                }

                // Debug Mode
                //cv::waitKey(2000);
                //cap.read(frame_RGB);
            }
        }

        contours.clear();
        finalContours.clear();
        hierarchy.clear();
        if (cv::waitKey(20) == 'q'){
            return {};
        }
    }

    cv::destroyWindow(this->window_name);

    results = this->formatSides(results);

    return formatToAlgorithm(results);
}

bool Robot::setRobotPosition(int id){
    /* List of robot moves to do in order to have the correct side in front of the camera */
    switch (id){
        case 1:
            if(!this->H3()) return false;
            if(!this->U()) return false;
            if(!this->D3()) return false;
            return true;
        case 2:
            if(!this->Ui()) return false;
            if(!this->H3()) return false;
            if(!this->U()) return false;
            if(!this->D3()) return false;
            return true;
        case 3:
            if (!this->Ui()) return false;
            if (!this->H3()) return false;
            if (!this->U()) return false;
            if (!this->D3()) return false;
            return true;
        case 4:
            if (!this->Bi()) return false;
            if (!this->H3()) return false;
            if (!this->B()) return false;
            if (!this->D3()) return false;
            return true;
        case 5:
            if (!this->H3()) return false;
            if (!this->Ui()) return false;
            if (!this->Ui()) return false;
            if (!this->D3()) return false;
            return true;
        case 6:
            return true;
        default:
            return false;
    }
}

std::vector<SquareRubik> Robot::sortResult(std::vector<SquareRubik> points){
    /*We sort the list with the Y axis to have the 3 lines not ordered yet. Then we sort each line to have the final result :
            ADECFBIGH --> BCA - FED - GIH --> ABC - DEF - GHI with (xa < xb < xc and xd < xd < xe and ...)
                                                ABC			012
                                                DEF  ==>	345
                                                GHI			678
    */
    std::sort(points.begin(), points.end(), Robot::sortYAxis);
    std::sort(points.begin(), points.begin() + 3, Robot::sortXAxis);
    std::sort(points.begin() + 3, points.begin() + 6, Robot::sortXAxis);
    std::sort(points.begin() + 6, points.end(), Robot::sortXAxis);

    return points;
}
