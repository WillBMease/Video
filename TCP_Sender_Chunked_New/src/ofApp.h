#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    private:
        ofVideoGrabber vidGrabber;
        ofxTCPServer tcpServer;
        ofImage vidFrame;
    
        int camWidth;
        int camHeight;
        int camFrameSize;
        int packetSize;
    int flag;
    
        unsigned char *ptrVidFrame;
        char vidFramePixels[307200];
        char tcpFramePacket[100]; //Each packet will have size 100 bytes
    
        //Counters
        int i,j,fpIndex;
    
    
    
		
};
