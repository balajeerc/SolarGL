#pragma once

#include "Util.h"

namespace SolarGL
{
    /// \brief Class that handles image loading
    /// \detail Stores it as RGB data which can be sampled in shader
    class Texture
    {
    public: 
        /// \brief Constructor     
        Texture();
        
        /// \brief gets texture width
        inline int& getWidth(){ return _width; }

        /// \brief gets texture height
        inline int& getHeight(){ return _height; }

        /// \brief gets number of channels
        inline int& getNumChannels(){ return _channelCount; }
        
        /// \brief returns the character buffer
        std::vector<unsigned char>& getBuffer(){ return _buffer; }
        
        /// \brief  loads a texture from a given file
        void load(const char* filename);
                
        /// \brief Prepare a texture for texture mapping
        void prepare();
        
        /// \brief  Returns the texture handle
        inline const GLuint& getTextureId(){ return _textureId; }

    protected:

        /// \brief  Texture buffer
        std::vector<unsigned char> _buffer; 
        
        /// \brief  Texture height
        int _height;
        
        /// \brief  Texture width
        int _width;
        
        /// \brief  Texture channel count  
        int _channelCount;
        
        /// \brief  Texture id            
        GLuint _textureId;                                                                                                                                               
    };
}