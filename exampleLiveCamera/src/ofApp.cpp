#include "ofApp.h"

void ofApp::setup(){
    
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_NOTICE);
    
	// if you see app crash at runtime, please check,
	// 1. Copy Intel.Realsense.dll and realsense2.dll in to /bin? 
	// 2. Unplug and re-connect Realsense camera and restart app.
    cfg.enable_stream(RS2_STREAM_DEPTH);
    cfg.enable_stream(RS2_STREAM_COLOR);
	pipe.start(cfg);
}

void ofApp::update(){

    // Get depth data from camera
    rs2::frameset frames = pipe.wait_for_frames();
    
    rs2::align align_to_color(RS2_STREAM_COLOR);
    frames = align_to_color.process(frames);
    
    auto depth = frames.get_depth_frame();
    auto color = frames.get_color_frame();
    pc.map_to(color);
    points = pc.calculate(depth);
    textureImg.setFromPixels((const unsigned char*) color.get_data(), color.get_width(), color.get_height(), OF_IMAGE_COLOR);
    

    // Create oF mesh
    mesh.clear();
    mesh.setMode(OF_PRIMITIVE_POINTS);
    int n = points.size();
    if(n!=0){
        const rs2::vertex * vs = points.get_vertices();
        for(int i=0; i<n; i++){
            if(vs[i].z){
                const rs2::vertex v = vs[i];
                glm::vec3 v3(v.x,v.y,v.z);
                mesh.addVertex(v3);
                
                float red   = (float)(textureImg.getPixels()[i * 3]);
                float green = (float)(textureImg.getPixels()[(i * 3) + 1]);
                float blue  = (float)(textureImg.getPixels()[(i * 3) + 2]);
                ofColor c = ofColor({red,green,blue});
                
                mesh.addColor(c);
            }
        }
    }
}

void ofApp::draw(){
    
    ofBackground(200);
    cam.begin();
    float s = 200;
    ofScale(s,-s,-s);
    ofDrawAxis(1);
    
    ofPushMatrix();
    ofTranslate(0, 1, 0);
    ofRotateZDeg(90);
    ofSetColor(0,200);
    ofDrawGridPlane(1, 5, true);
    ofPopMatrix();
    
    mesh.draw();
    
    cam.end();
}

