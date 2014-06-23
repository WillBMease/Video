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
        ofxTCPClient tcpClient;
        ofTexture frameTex;
    
        int frameWidth;
        int frameHeight;
        int frameSize;
    
        string serverIP;
        int serverPort;
    
        int packetSize;
        int bytesReceived;
        int totalBytesReceived;
        int packetArrFlag;
    
        char packet[256];
        char recvdFrame[19200];
        unsigned char *usc_frame;
    
        //Counters for loops
        int i,j,pIndex;
    
};
