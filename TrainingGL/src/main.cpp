#include "AppManager.h"

int main(int argc, char* argv[])
{
    SolarGL::AppManager manager;
    manager.initApplication(argc, argv);
    return 0;
}


//#include <stdio.h>
//#include <string.h>
//#include <assert.h>
//#include <GL/glew.h>
//#include <GL/GLUT.h>
//#include <cml/cml.h> 
//
//#define DWASSERT(condition,printstatement)  if(!condition){ printf(printstatement); assert(condition); }
//
////We use some ugly globals for the time being
//
////Window Dimensions
//int currentWindowWidth = 500;
//int currentWindowHeight = 500;
//
//cml::matrix44f *g_pModelViewProjMatrix;
//
////Function to assert any OpenGL errors
//void DWGLErrorAssert()
//{
//	GLint err = glGetError();
//	if (err == GL_NO_ERROR)
//		return;
//	
//	printf("DW_ERROR: OpenGL error encountered!"
//		   "Error Code: %d\n",err);	
//	DWASSERT(false,"");
//}
//
///////////////////////////////////////////////////////////////////
////	Shaders: Source, Compling and Linking
///////////////////////////////////////////////////////////////////
//const char vertexShaderSrc[] = 
//"uniform mat4 ProjectionModelviewMatrix;\n"
//"attribute vec4 InVertex;\n"
//"void main()\n"
//"{\n"
//"	gl_Position = ProjectionModelviewMatrix * InVertex;\n"
//"}\n"
//;
//
//const char fragmentShaderSrc[] =
//"void main()\n"
//"{\n"
//"	gl_FragColor = vec4(1.0,0.0,0.0,1.0);\n"
//"}\n"
//;
//
//struct Shader
//{
//	GLuint vertexShaderId;
//	GLuint fragmentShaderId;
//	GLuint shaderProgramId;
//};
//
////Global shader pointer
//Shader* g_pShader;
//
//void GetErrorLog(int shaderId)
//{
//	GLint log_length;
//    char *log;
//	
//	//glGetShaderiv returns a parameter from a shader object
//	//We use it to get information regarding the log string
//    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &log_length);
//    
//	//Allocate memory for the log error string
//	log = new char[log_length+1];
//	
//	//Now we get the shader log string itself
//    glGetShaderInfoLog(shaderId, log_length, NULL, log);
//	
//	//Dump the error to console
//    printf("%s\n", log);
//    delete [] log;
//}
//
//void LoadAndCompileShader(const char* shaderSource, GLuint* shaderId, GLenum shaderType)
//{
//	//Obtain length of source
//	int shaderSourceLen = strlen(shaderSource);
//	
//	//Create shader
//	*shaderId = glCreateShader(shaderType);	
//	DWASSERT(shaderId!=0,"Unable to create shader\n");
//	
//	//Specify the shader source
//    glShaderSource(*shaderId,					//Shader Id
//				   1,							//Number of shaders required			
//				   &shaderSource,				//Shader source
//				   &shaderSourceLen);			//Character length of the source
//	DWGLErrorAssert();
//	
//	//Compile the shader
//    glCompileShader(*shaderId);	
//	
//	//We now check compilation status
//	GLint shader_ok;
//	glGetShaderiv(*shaderId, GL_COMPILE_STATUS, &shader_ok);
//    if (!shader_ok)
//	{
//		//Compilation failed
//        printf("ERROR: Shader failed to compile. Error log follows:\n");
//		GetErrorLog(*shaderId);
//        glDeleteShader(*shaderId);
//        DWASSERT(false,"");
//    }
//	DWGLErrorAssert();
//}
//
//void AttachAndLinkShaders(GLuint vertShaderId, GLuint fragShaderId, GLuint *shaderProgramId)
//{
//	//Create a new program ID
//	*shaderProgramId = glCreateProgram();
//	
//	glAttachShader(*shaderProgramId, vertShaderId);
//	glAttachShader(*shaderProgramId, fragShaderId);
//	DWGLErrorAssert();
//	
//	//We can bind attribute variables here in case we are specifying 
//	//the indices to bind to. Since we don't do that, and let GL implementation
//	//assign the indices for attribute variables, we can bind buffers *after* linking the shader.
//	//We query the ids bound during rendering via glGetAttribLocation
//	glLinkProgram(*shaderProgramId);
//	
//	GLint program_ok;
//	glGetProgramiv(*shaderProgramId, GL_LINK_STATUS, &program_ok);
//	if (!program_ok)
//	{
//		printf("Failed to link program with vertex and fragment shaders\n");
//		GLint log_length;
//		char *log;
//		
//		glGetProgramiv(*shaderProgramId, GL_INFO_LOG_LENGTH, &log_length);
//		log = new char[log_length+1];
//		
//		glGetProgramInfoLog(*shaderProgramId, log_length, NULL, log);
//		
//		//Dump the error to console
//		printf("%s\n", log);
//		
//		delete [] log;
//		
//		glDeleteProgram(*shaderProgramId);
//		DWASSERT(false,"");
//	}
//}
//
///////////////////////////////////////////////////////////////////
////	Plane: Geometry to be rendered on Scene using VBO
///////////////////////////////////////////////////////////////////
//float planeHeight = 10;
//float planeWidth = 10;
//
//float planeVertices[] =
//{
//	-planeWidth/2, -planeHeight/2, 0.f,
//	planeWidth/2, -planeHeight/2, 0.f,
//	planeWidth/2,  planeHeight/2, 0.f,
//	-planeWidth/2,  planeHeight/2, 0.f 
//};
//
////Draw the rectanglular plane as two triangles
//unsigned int planeIndices[] = 
//{
//	0, 3, 1,
//	3, 2, 1
//};
//
//struct Plane
//{
//	GLuint vertexBufferId;
//	GLuint elementBufferId;
//};
//
////Global Plane pointer
//Plane* g_pPlane;
//
//void GenerateBuffers(Plane* pPlane)
//{
//	//First bind the vertex coordinates
//	glGenBuffers(1, &(pPlane->vertexBufferId));
//	glBindBuffer(GL_ARRAY_BUFFER, pPlane->vertexBufferId);
//	glBufferData(GL_ARRAY_BUFFER, 12*sizeof(float), planeVertices, GL_STATIC_DRAW);
//	DWGLErrorAssert();
//	
//	//Now bind the indices
//	glGenBuffers(1,&(pPlane->elementBufferId));
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pPlane->elementBufferId);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(unsigned int), planeIndices, GL_STATIC_DRAW);	
//	DWGLErrorAssert();
//	
//	// bind with 0 so that no buffers are left active/selected until necessary
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//}
//
//void DrawPlane(Plane* pPlane,Shader* pShader,cml::matrix44f *modelViewProjMatrix)
//{	
//	int shaderId = pShader->shaderProgramId;
//	glUseProgram(shaderId);
//	DWGLErrorAssert();
//	
//	int loc;
//	loc = glGetUniformLocation(shaderId, "ProjectionModelviewMatrix");
//	glUniformMatrix4fv(loc, 1, GL_FALSE, modelViewProjMatrix->data());
//	
//	int vertexLoc = glGetAttribLocation(shaderId, "InVertex");
//	
//	//Specify the vertex coordinates
//	glBindBuffer(GL_ARRAY_BUFFER, pPlane->vertexBufferId);
//	glVertexAttribPointer(
//						  vertexLoc,			//attribute
//						  3,                    //size 
//						  GL_FLOAT,             //type
//						  GL_FALSE,             //not normalized 
//						  sizeof(GLfloat)*3,    //stride
//						  (void*)0              //array buffer offset
//						  );
//	glEnableVertexAttribArray(vertexLoc);
//	
//	//Bind the index buffer before initiating draw
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pPlane->elementBufferId);
//	DWGLErrorAssert();
//	
//	// Draw 2 triangles using just bound(activated) index array
//	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
//	DWGLErrorAssert();
//	
//	//Deactivate array buffers
//	glDisableVertexAttribArray(vertexLoc);		
//	
//	// bind with 0, so, switch back to normal pointer operation
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//	DWGLErrorAssert();
//}
//
////////////////////////////////////////////////////////////////////////////
////	GLUT specific code and callback functions
////////////////////////////////////////////////////////////////////////////
//void display(void)
//{
//	DWGLErrorAssert();
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	
//	//Render Scene Code
//	DrawPlane(g_pPlane, g_pShader,g_pModelViewProjMatrix);
//	
//	glutSwapBuffers();
//}
//
//void reshape(int width, int height)
//{
//    glViewport(0, 0, (GLsizei)width,(GLsizei)height);
//	currentWindowWidth  = width;
//	currentWindowHeight = height; 
//}
//
//void idle(void)
//{
//    glutPostRedisplay();
//}
//
////////////////////////////////////////////////////////////////////////////
////	Application/Scene Setup and Initialisation
////////////////////////////////////////////////////////////////////////////
//void InitApplication(Plane* pPlane,Shader* pShader)
//{	
//	glFrontFace(GL_CW);
//	glDisable(GL_CULL_FACE);	
//	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
//	glColor3f(1.f, 1.f, 1.f);
//	glClearColor(0.f, 0.f, 1.f, 1.f);
//		
//	//Generate buffers for plane
//	GenerateBuffers(pPlane);
//	
//	//Compile shader source
//	LoadAndCompileShader(vertexShaderSrc, &(pShader->vertexShaderId), GL_VERTEX_SHADER);
//	LoadAndCompileShader(fragmentShaderSrc, &(pShader->fragmentShaderId), GL_FRAGMENT_SHADER);
//	
//	//Link and attach shaders
//	AttachAndLinkShaders(pShader->vertexShaderId, pShader->fragmentShaderId, &(pShader->shaderProgramId));
//	
//	
//	//Setup camera projection matrix
//	cml::matrix44f projection;	//projection matrix (row major type)
//	cml::matrix_perspective(projection,			//Projection matrix to set
//							-1.0f,				//Left
//							1.0f,				//Right
//							-1.0f,				//Bottom
//							1.0f,				//Top	
//							1.0f,				//Near
//							100.0f,				//Far
//							cml::right_handed,	//Handedness
//							cml::z_clip_neg_one //enum specifying near clipping range of the
//							);					//canonical view volume for projection matrices	
//	
//	//Setup the camera view matrix
//	//Setup view matrix
//	cml::matrix44f view;		//view matrix (row major type)	
//	cml::vector3f eye, target, up;
//	eye.set(0.f,0.f,10.f);		// Set 'eye' to (0.f,0.f,10.f)
//	target.set(0.f,0.f,0.f);    // Set 'target' to (0.f,0.f,0.f)
//	up.set(0.f,1.f,0.f);		// Set 'up' to (0,1,0), the cardinal Y axis
//	cml::matrix_look_at_RH(view, eye, target, up);	
//		
//	//Set the global pointers
//	g_pPlane = pPlane;
//	g_pShader = pShader;
//	g_pModelViewProjMatrix = new cml::matrix44f();
//	*g_pModelViewProjMatrix = projection*view;
//	
//	for (int i=0; i<4; i++)
//	{
//		for(int j=0;j<4;j++)
//			printf("%f ", (*g_pModelViewProjMatrix)(i,j));
//		
//		printf("\n");
//	}
//	
//}
//
//
//int main(int argc, char** argv)
//{	
//	//Initialising GLUT
//    glutInit(&argc, argv);    
//    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
//    glutInitWindowSize(currentWindowWidth,currentWindowHeight);    
//    glutCreateWindow("Trial GL");
//    glutDisplayFunc(display);
//    glutReshapeFunc(reshape);
//    glutIdleFunc(idle);
//	DWGLErrorAssert();
//	
//	//Create a valid OpenGL rendering context and call glewInit()
//	//to initialize the extension entry points. If glewInit() returns GLEW_OK,
//	//the initialization succeeded and we can use the available extensions as
//	//well as core OpenGL functionality.
//	GLenum err = glewInit();
//	if (GLEW_OK != err)
//	{
//		//Problem: glewInit failed, something is seriously wrong.
//		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
//	}
//	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
//	
//	//Send message to console
//    printf("Starting Application...\n");
//	
//	//Create plane
//	struct Plane newPlane;
// 	
//	//Create shader
//	struct Shader newShader;
//	
//	InitApplication(&newPlane,&newShader);
//	
//	//Start main loop
//	glutMainLoop();
//	
//    return 0;
//}