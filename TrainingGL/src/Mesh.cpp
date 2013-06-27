#include "Mesh.h"

namespace SolarGL
{
    Mesh::Mesh()
    {

    }

    Mesh::~Mesh()
    {

    }

    void Mesh::load(const char* filename)
    {
        //load the mesh dumped from blender as json
        //first read all the json data into a single string from file
        std::ifstream meshfile(filename, std::ios::in | std::ios::binary);
        std::string contents;
        if (meshfile)
        {	
	        meshfile.seekg(0, std::ios::end);
	        contents.resize(meshfile.tellg());
	        meshfile.seekg(0, std::ios::beg);
	        meshfile.read(&contents[0], contents.size());
	        meshfile.close();
        }
        else
        {
	        printf("error: cannot find mesh file!");
	        exit(1);
        }

        //we can now use picojson to parse this string containing the mesh data
        picojson::value v;  
        // read json value from stream
        std::stringstream jsonstream(contents);
        jsonstream >> v;
        if (std::cin.fail())
        {
	        std::cerr << picojson::get_last_error() << std::endl;
	        exit(1);
        }

        // check if the type of the value is "object"
        // root node, in our case must be an object
        if (! v.is<picojson::object>()) {
	        std::cerr << "json is not an object" << std::endl;
	        exit(1);
        }

        const picojson::value::object& root = v.get<picojson::object>();
        for (picojson::value::object::const_iterator i = root.begin(); i != root.end(); ++i)
        {
	        std::string childname = i->first;
	        picojson::value child = i->second;
	        if(childname.compare("vertices")==0)
	        {
		        picojson::array vertslist = child.get<picojson::array>();
		        for (picojson::value::array::const_iterator vertex = vertslist.begin(); vertex != vertslist.end(); ++vertex)
		        {
			        picojson::array coords = vertex->get<picojson::array>();
			        float x = coords[0].get<double>();
			        float y = coords[1].get<double>();
                    float z = coords[2].get<double>();
			        _vertices.push_back(x);
			        _vertices.push_back(y);
                    _vertices.push_back(z);
		        }
	        }
	        else if(childname.compare("faces")==0)
	        {
		        picojson::array facelist = child.get<picojson::array>();
		        for (picojson::value::array::const_iterator face = facelist.begin(); face != facelist.end(); ++face)
		        {
			        picojson::array vertindices = face->get<picojson::array>();
			        unsigned int v1 = (unsigned short)vertindices[0].get<double>();
			        unsigned int v2 = (unsigned short)vertindices[1].get<double>();
			        unsigned int v3 = (unsigned short)vertindices[2].get<double>();
			        _faceIndices.push_back(v1);
			        _faceIndices.push_back(v2);
			        _faceIndices.push_back(v3);
		        }
	        }
	        else if((childname.compare("texture_coords")==0))
	        {
		        picojson::array texcoordslist = child.get<picojson::array>();
		        for (picojson::value::array::const_iterator vertex = texcoordslist.begin(); vertex != texcoordslist.end(); ++vertex)
		        {
			        picojson::array coords = vertex->get<picojson::array>();
			        float x = coords[0].get<double>();
			        float y = coords[1].get<double>();
			        _texCoords.push_back(x);
			        _texCoords.push_back(y);
		        }
	        }
        }

  //      float planeWidth = 10;
  //      float planeHeight = 10;
  //      float planeVertices[] =
		//{
		//	-planeWidth/2, -planeHeight/2, 0.f,
		//	planeWidth/2, -planeHeight/2, 0.f,
		//	planeWidth/2,  planeHeight/2, 0.f,
		//	-planeWidth/2,  planeHeight/2, 0.f 
		//};
		//_vertices.assign(planeVertices, planeVertices+12);

  //      GLuint planeIndices[] =
  //      {
  //          0, 3, 1,
  //          3, 2, 1
  //      };
  //      _faceIndices.assign(planeIndices, planeIndices+6);

  //      float planeTexCoords[] = 
  //      {
  //          0.f, 1.f,
  //          1.f, 1.f,
  //          1.f, 0.f,
  //          0.f, 0.f
  //      };
  //      _texCoords.assign(planeTexCoords, planeTexCoords+8);
    }

    void Mesh::prepare()
    {
        //First bind the vertex coordinates
        glGenBuffers(1, &_vertexBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
        glBufferData(GL_ARRAY_BUFFER, _vertices.size()*sizeof(GLfloat), &(_vertices[0]), GL_STATIC_DRAW);
        Util::GLErrorAssert();

        //Next bind the texture coordinates
        glGenBuffers(1, &_texCoordsBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, _texCoordsBufferId);
        glBufferData(GL_ARRAY_BUFFER, _texCoords.size()*sizeof(GLfloat), &(_texCoords[0]), GL_STATIC_DRAW);
        Util::GLErrorAssert();

        //Finally bind the indices
        glGenBuffers(1,&_elementBufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _faceIndices.size()*sizeof(GLuint), &(_faceIndices[0]), GL_STATIC_DRAW);
        Util::GLErrorAssert();

        // bind with 0 so that no buffers are left active/selected until necessary
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
