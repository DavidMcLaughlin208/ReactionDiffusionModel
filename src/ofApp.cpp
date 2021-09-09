#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();
	ofSeedRandom();

	width = ofGetWidth() -guiWidth;
	height = ofGetHeight();

	loadShaders();

	ofBackground(0);
	ofEnableBlendMode(OF_BLENDMODE_ADD);

	cells.resize(width * height);
	for (int i = 0; i < cells.size(); i++) {
		auto& vec2 = cells[i];
		vec2.x = ofRandom(0, 1);
		vec2.y = ofRandom(0, 1);
	}
	cellsBuffer.allocate(cells);

	cellsBuffer.src->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	cellsBuffer.dst->bindBase(GL_SHADER_STORAGE_BUFFER, 1);

	auto modifiedTrailBuffer = cellsBuffer.dst->map<glm::vec2>(GL_READ_WRITE);
	int i = 1;
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetWindowTitle(ofToString(ofGetMouseY()));

	// Swap buffers and rebind to respective locations
	cellsBuffer.swap();
	cellsBuffer.src->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	cellsBuffer.dst->bindBase(GL_SHADER_STORAGE_BUFFER, 1);

	// Compute Shader
	computeShader.begin();
	computeShader.setUniform1i("cellsSize", cells.size());
	computeShader.dispatchCompute(cells.size() / 1024, 1, 1);
	computeShader.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
	//ofSetColor(ofColor::red);
	//ofDrawRectangle(0, 0, width, height);
	shader.begin();
	shader.setUniform1i("screenWidth", width);
	shader.setUniform1i("cellsSize", cells.size());
	shader.setUniform1f("xRatio", float(ofGetWidth() - guiWidth) / float(width));
	shader.setUniform1f("yRatio", float(ofGetHeight()) / float(height));
	ofDrawRectangle(0, 0, ofGetWidth() - guiWidth, ofGetHeight());
	//ofDrawRectangle(0, 0, width, height*2);
	shader.end();
}

void ofApp::loadShaders() {
	shader.load("Shaders/shader");
	computeShader.setupShaderFromFile(GL_COMPUTE_SHADER, "Shaders/shader.compute");
	computeShader.linkProgram();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
