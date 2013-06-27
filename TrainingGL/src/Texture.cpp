#include "Texture.h"

namespace SolarGL
{        
    Texture::Texture():
    _width(0),
    _height(0),
    _channelCount(0),
    _textureId(-1)
    {
            
    }
        
    void Texture::loadFromFile(const char* filename)
    {
        int width, height, channels;
        unsigned char *ht_map = SOIL_load_image(filename,
                                                &width,
                                                &height,
                                                &channels,
                                                SOIL_LOAD_AUTO
                                                );
        
        //Check for an error during the load process
        if(!ht_map)
        {
            printf( "Image loading error from SOIL: '%s'\n", SOIL_last_result() );
            assert(false);
        }
                
        _height = height;
        _width = width;
        _channelCount = channels;
        
        if (!_buffer.empty())
            _buffer.clear();

        int numBytes = _height*_width*_channelCount;
        _buffer.assign(ht_map, ht_map+numBytes);
        
        float htmapVal = *(ht_map+432);
        float buffVal = _buffer[432];
        assert(htmapVal==buffVal);

        //Deallocate the memory taken up by SOIL
        SOIL_free_image_data( ht_map ); 
    }
            
    void Texture::prepare()
    {
        glGenTextures(1, &_textureId);
        glBindTexture(GL_TEXTURE_2D, _textureId);           
        Util::GLErrorAssert();
                
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_REPEAT);
        
        GLenum format;
        
        if(_channelCount==4)
        {       
            format = GL_RGBA;
        }       
        else if(_channelCount==3)
        {       
            format = GL_RGB;
        }       
        else
        {       
            ASSERT(false,"Image format not supported\n");
        }
        
        glTexImage2D(GL_TEXTURE_2D,         //target
                     0,                     //level of detail
                     _channelCount,         //internal format 
                     _width, _height, 0,    //width, height, border
                     format,                //external format               
                     GL_UNSIGNED_BYTE,      //type
                     &(_buffer[0])          //pixel buffer
                     );        
        
        Util::GLErrorAssert();        
        glBindTexture(GL_TEXTURE_2D, 0);                                
    }
}