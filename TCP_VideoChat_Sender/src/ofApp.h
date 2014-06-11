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
        ofPixels pixels;
        ofImage vidFrame;
        ofTexture vidTexture;
        ofxTCPServer tcpServer;
    
        int camWidth;
        int camHeight;
        int frameSize;
        
        unsigned char *ptrArrPixels;
        
        unsigned char *checkconstpixels;
    
    ofxUDPManager udpConnection;
    
    
    
    
    
		
};
