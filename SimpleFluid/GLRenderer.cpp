//
//  GLRenderer.cpp
//  GyroSquares
//
//  Created by James Milton on 28/05/2014.
//  Copyright (c) 2014 James Milton. All rights reserved.
//

#include "GLRenderer.h"
#include "BillboardShader.h"

// Helper constant buffer for drawing screen-aligned quads
static const float SKY_QUAD_COORDS[] = { -1.0f, -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, -1.0f, 1.0f,
    -1.0f,  1.0f, -1.0f, 1.0f,
    1.0f,  1.0f, -1.0f, 1.0f
};

void GLRenderer::initOpenGL() {
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    mViewWidth = 1200;
    mViewHeight = 800;
    reshape(1200, 800);
    
    initBillboardShader();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
    render(0.0);
}

void GLRenderer::initBillboardShader() {
    mBillboardShader = new BillboardShader;
}

void GLRenderer::render(float dt) {
    const float FPS_CLAMP = 1.0f / 15.0f;
    if (dt > FPS_CLAMP)
        dt = FPS_CLAMP;
    
    freeGLBindings();
    
    glm::mat4 mvp = mProjectionMatrix * mViewMatrix;
    glm::vec4 right = mViewMatrix[0];
    glm::vec4 up = mViewMatrix[1];
}

void GLRenderer::reshape(int width, int height) {
    glViewport(0, 0, width, height);
    mViewWidth = width;
    mViewHeight = height;
    mProjectionMatrix = glm::perspective(45.0f, (float)width/(float)height, 0.1f, 100.0f);
    mViewMatrix = glm::lookAt(glm::vec3(0,0,10), glm::vec3(0,0,0), glm::vec3(0,1,0));
    
    glm::vec4 fwidth;
    fwidth = mProjectionMatrix * mViewMatrix * glm::vec4(mViewWidth, mViewHeight, 0, 1);
    mMouseWidth = fwidth.x /= fwidth.w;
    mMouseHeight = fwidth.y /= fwidth.w;
    createFrameBuffers();
}

void GLRenderer::drawScreenAlignedQuad(const unsigned int attrHandle) const
{
    glVertexAttribPointer(attrHandle, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          SKY_QUAD_COORDS);
    glEnableVertexAttribArray(attrHandle);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glDisableVertexAttribArray(attrHandle);
}

void GLRenderer::freeGLBindings(void) const
{
    glBindFramebuffer(GL_FRAMEBUFFER,     0);
    glBindRenderbuffer(GL_RENDERBUFFER,   0);
    glBindBuffer(GL_ARRAY_BUFFER,         0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D,          0);
    glBindTexture(GL_TEXTURE_CUBE_MAP,    0);
}

void GLRenderer::getMousePosition(float x, float y, float z) {
    if (z == INT32_MAX){
        mMousePosition = glm::vec3(-1.0,-1.0,0);
    } else {
        float w = ((x - (mViewWidth/2)) /mMouseWidth) * 2.0;
        float h = ((y - (mViewHeight/2)) /mMouseHeight) * 2.0;
        mMousePosition = glm::vec3(w,h,z);
    }
}

void GLRenderer::getMouseAcceleration(float x, float y, float z) {
    mMouseAcceleration = glm::vec3(x,y,z);
}

void GLRenderer::resetFramebuffers() {
}

void GLRenderer::createFrameBuffers() {
    resetFramebuffers();
}

void GLRenderer::destroy() {
}