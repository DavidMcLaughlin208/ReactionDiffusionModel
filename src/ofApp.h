#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include <vector>

class ofApp : public ofBaseApp{

	struct pingPongBuffer {
	public:
		void allocate(vector<glm::vec2> data) {
			// Allocate
			for (int i = 0; i < 2; i++) {
				bufferObjects[i].allocate(data, GL_DYNAMIC_DRAW);
			}

			//Assign
			src = &bufferObjects[0];
			dst = &bufferObjects[1];
		}

		void update(vector<glm::vec2> data) {
			for (int i = 0; i < 2; i++) {
				bufferObjects[i].updateData(data);
			}
		}

		void swap() {
			std::swap(src, dst);
		}

		ofBufferObject& operator[](int n) { return bufferObjects[n]; }
		ofBufferObject* src;       // Source       ->  Ping
		ofBufferObject* dst;       // Destination  ->  Pong

	private:
		ofBufferObject   bufferObjects[2];    // Real addresses of ping/pong ofBufferObjects
	};

	public:
		void setup();
		void update();
		void draw();
		void loadShaders();
		void setupGui();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofShader shader;
		ofShader computeShader;
		vector<glm::vec2> cells;

		pingPongBuffer cellsBuffer;


		int width; 
		int height;
		int guiWidth = 200;

		ofColor aColor;
		ofColor bColor;


		ofxPanel gui;
		ofxFloatSlider diffusionRateASlider;
		ofxFloatSlider diffusionRateBSlider;
		ofxFloatSlider feedRateASlider;
		ofxFloatSlider killRateBSlider;
		
};
