//----------------------------------------------------------------------------------
// File:        FeedbackParticlesApp/Utils.cpp
// SDK Version: v1.01 
// Email:       gameworks@nvidia.com
// Site:        http://developer.nvidia.com/
//
// Copyright (c) 2014, NVIDIA CORPORATION. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//----------------------------------------------------------------------------------

#include "Utils.h"

//------------------------------------------------------------------------------
//
void NvVertexAttribute::apply(BaseShader* program)
{
    if (NULL == program)
        return;

    NvVertexAttribute* p = this;
    while (NULL != p->name)
    {
        const GLint index = program->getAttribLocation(p->name);

        if (index >= 0)
        {
            glVertexAttribPointer(  index,p->size,p->type,
                p->isNormalized ? GL_TRUE : GL_FALSE,p->stride,(void*)p->offset); 
            glEnableVertexAttribArray(index);
        }

        ++p;
    }
}


//------------------------------------------------------------------------------
//
void NvVertexAttribute::reset(BaseShader* program)
{
    if (NULL == program)
        return;

    NvVertexAttribute* p = this;
    while (NULL != p->name)
    {
        const GLint index = program->getAttribLocation(p->name);
        
        if (index >= 0)
            glDisableVertexAttribArray(index);

        ++p;
    }
}