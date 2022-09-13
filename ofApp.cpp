#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	//this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();

	float phi_deg_step = 3;
	float theta_deg_step = 2;
	float R = 250;
	float r = 50;
	float threshold = 0.52;
	float phi_seed = ofRandom(1000);
	float theta_seed = ofRandom(2000, 3000);

	for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

		for (float theta_deg = 0; theta_deg < 90; theta_deg += theta_deg_step) {

			auto vertex = this->make_point(R, r, theta_deg, phi_deg);
			auto phi_param = ofMap(ofNoise(glm::vec4(vertex * 0.003, phi_seed + ofGetFrameNum() * 0.004)), 0, 1, -180, 180);
			auto theta_param = ofMap(ofNoise(glm::vec4(vertex * 0.03,  theta_seed + ofGetFrameNum() * 0.004)), 0, 1, -360, 360);

			this->mesh.addVertex(this->make_point(R, r, theta_deg + theta_param, phi_deg + phi_param));
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateZ(ofGetFrameNum() * 0.1);

	this->mesh.drawVertices();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}