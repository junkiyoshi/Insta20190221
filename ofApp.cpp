#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetBackgroundAuto(false);
	ofSetColor(39);

	this->location = glm::vec2(ofRandom(ofGetWidth() * 0.2, ofGetWidth() * 0.8), ofRandom(ofGetHeight() * 0.2, ofGetHeight() * 0.8));
	this->percent = 0.0;
	this->noise_seed = ofRandom(10000);
	this->noise_scale = ofRandom(3, 8);
	this->color.setHsb(ofRandom(255), 230, 255);
}

//--------------------------------------------------------------
void ofApp::update() {

	if (this->percent < 1.0) {

		this->percent += 0.15;
	}
	else {

		this->location = glm::vec2(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
		this->percent = 0.f;
		this->noise_seed = ofRandom(10000);
		this->noise_scale = ofRandom(3, 8);
		this->color.setHsb(ofRandom(255), ofRandom(100, 255), ofRandom(200, 255));
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	float base_radius = 80;

	ofPushMatrix();
	ofTranslate(this->location);

	vector<glm::vec2> vertices;
	for (int i = 0; i < 3600; i++) {

		float deg = i * 0.1;
		auto noise_point = glm::vec2(cos(deg * DEG_TO_RAD), sin(deg * DEG_TO_RAD));
		auto noise_value = ofNoise(this->noise_seed, noise_point.x * this->noise_scale, noise_point.y * this->noise_scale);
		float grow_radius = base_radius + pow((1 + noise_value), 7) * this->percent;

		auto point = glm::vec2(grow_radius * cos(deg * DEG_TO_RAD), grow_radius * sin(deg * DEG_TO_RAD));
		vertices.push_back(point);
	}

	ofSetColor(this->color);

	ofBeginShape();
	ofVertices(vertices);
	ofEndShape();

	ofPopMatrix();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}