/*  COURBE DE HILBERT EN 3D */


// Bibliothèques clasiques
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stack>

// Bibliothèque gérant les extensions d'OpenGL

#include <GL/glew.h>

// Bibliothèque GLUT : gestion de la fenêtre, intéractions avec le système...

#include <GL/freeglut.h>

// Bibliothèque mathématiques d'OpenGL
#define GLM_FORCE_RADIANS
// glm::vec3, glm::vec4, glm::ivec4, glm::mat4
#include <glm/glm.hpp>
// glm::perspective
// glm::translate, glm::rotate, glm::scale
#include <glm/gtc/matrix_transform.hpp>
// glm::value_ptr
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/closest_point.hpp>

// Bibliothèque pour le chargement des textures
#include <SOIL/SOIL.h>


// Fichier pour la compilation et l'exécution des shaders

// include "shader_utils.h"

#include "shader.hpp"

// Fichier de gestion des L-Systems

#include "lsystem.h"

int screen_width = 1000 , screen_height = 700 ;

GLuint vertices_buffer , texture_buffer , elements_buffer ;
GLuint program;
GLuint texture_id ;
GLint mvp_shader , mytexture_shader ;
GLint attribute_coord3d, attribute_texcoord;


float angle = 0.f ;
float Pi_2 = 1.5708f ;
string pyramid_curve ;


// Variable globale glm

glm::vec3 rotspeeds ;
//glm::vec3 position ;




// Définition de la courbe représentée par un L-System



int init_ressources () {

  texture_id = SOIL_load_OGL_texture
    (
     "../Textures/Pyramid.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  if(texture_id == 0)
    cerr << "SOIL loading error: '" << SOIL_last_result() << "' (" << "res_texture.png" << ")" << endl;
  
  // Sommets de la pyramide

  static const GLfloat pyramid[] = 
    {
      // face 1

      0.0f , 0.0f , 1.0f ,
      -1.0f , -1.0f , 0.0f ,
      -1.0f , 1.0f , 0.0f ,

      // face 2

      0.0f , 0.0f , 1.0f ,
      1.0f , 1.0f , 0.0f ,
      1.0f , -1.0f , 0.0f ,

      // face 3

      0.0f , 0.0f , 1.0f ,
      -1.0f , -1.0f , 0.0f ,
      1.0f , -1.0f , 0.0f ,

      // face 4

      0.0f , 0.0f , 1.0f ,
      1.0f , 1.0f , 0.0f ,
      -1.0f , 1.0f , 0.0f    
      
    };


  // On entre l'objet dans le buffer des sommets

  glGenBuffers(1, &vertices_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertices_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof pyramid , pyramid , GL_STATIC_DRAW);


  // Couleur des sommets 


  GLfloat pyramid_texcoords[3*2*4] =
    {
      
      1.0 , 0.5 ,
      0.0 , 0.0 ,
      0.0 , 1.0
     

    };

  for (int i = 1; i < 4; i++)
    memcpy(&pyramid_texcoords[i*3*2], &pyramid_texcoords[0], 2*4*sizeof(GLfloat));

  // On remplit le buffer des couleurs 

  glGenBuffers(1, &texture_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, texture_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof pyramid_texcoords , pyramid_texcoords, GL_STATIC_DRAW);


  static const GLushort pyramid_elements[] = 
    {
      0, 1, 2,
      3, 4, 5,
      6, 7, 8,
      9, 10, 11
      
      // back
      
      //1, 3, 2,
      //1, 3, 4,

    };

  glGenBuffers(1, &elements_buffer );
  glBindBuffer(GL_ARRAY_BUFFER, elements_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof pyramid_elements , pyramid_elements, GL_STATIC_DRAW);

  // Gestion des shaders

  GLint link_ok = GL_FALSE;

  /*GLuint vs, fs;
  if ((vs = create_shader("hilbert.vert", GL_VERTEX_SHADER))   == 0) return 0;
  if ((fs = create_shader("hilbert.frag", GL_FRAGMENT_SHADER)) == 0) return 0;*/

  program = LoadShaders( "../Shaders/pyramid.vert", "../Shaders/pyramid.frag" );
  
  /*program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
  if (!link_ok) {
    fprintf(stderr, "glLinkProgram:");
    print_log(program);
    return 0;
    }*/

  mvp_shader = glGetUniformLocation(program, "MVP");

  mytexture_shader = glGetUniformLocation(program, "MyTexture");

  attribute_coord3d = glGetAttribLocation(program,"coord3d");

  attribute_texcoord = glGetAttribLocation(program,"texcoord");

  srand48(time(NULL));

  rotspeeds = glm::vec3 (drand48() * 5, drand48() * 5, drand48() * 5);
  //position = glm::vec3 ((drand48() - 0.5) * 2, (drand48() - 0.5) * 2, (drand48() - 0.5) * 2);

  return 1;
}



void onIdle() {
  angle = glutGet(GLUT_ELAPSED_TIME) / 1000.0 * glm::radians(5.0);	// base 15° per second
  glutPostRedisplay();
}


void onDisplay() {

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Fond uni noir
  glClearStencil(0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
  
  glUseProgram(program);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glUniform1i(mytexture_shader, /*GL_TEXTURE*/0);

  // 1er buffer attribué : les vertices

  glEnableVertexAttribArray(attribute_coord3d);
  glBindBuffer(GL_ARRAY_BUFFER, vertices_buffer);
  glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

  // 2nd buffer : la texture

  glEnableVertexAttribArray(attribute_texcoord);
  glBindBuffer(GL_ARRAY_BUFFER, texture_buffer);
  glVertexAttribPointer(
			attribute_texcoord, // attribute
			2,                  // number of elements per vertex, here (x,y)
			GL_FLOAT,           // the type of each element
			GL_FALSE,           // take our values as-is
			0,                  // no extra data between each position
			0                   // offset of first element
			);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements_buffer);

  int size;

  stack<glm::mat4> S_model ;


  glm::mat4 anim =
    glm::rotate(glm::mat4(1.0f), angle * rotspeeds.x, glm::vec3(1, 0, 0)) *	// axe des X
    glm::rotate(glm::mat4(1.0f), angle * rotspeeds.y, glm::vec3(0, 1, 0)) *	// axe des Y
    glm::rotate(glm::mat4(1.0f), angle * rotspeeds.z, glm::vec3(0, 0, 1));	// axe des Z


  // Matrice model : Coordonnées objet -> Coordonnées monde

  glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(0.,0.,0.5)) ;

  // Matrice view : Coordonnées du monde -> Coordonnées caméra

  glm::mat4 view = glm::lookAt(glm::vec3(3.0, -4.0, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.1, 1.0, 0.0));


  // Matrice projection : Coordonnées caméra -> Coordonnées "homogènes"

  glm::mat4 projection = glm::perspective(45.0f, 1.0f*screen_width/screen_height, 0.1f, 100.0f);
  
  for (int i = 0 ; i < pyramid_curve.size() ; i++) {

    glm::mat4 mvp = projection * view * anim * model ;
    glUniformMatrix4fv(mvp_shader, 1, GL_FALSE, glm::value_ptr(mvp));
    
    /* Turtle interpretation */

    switch (pyramid_curve[i]) {


    case 'F' : 

      glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
      glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0); break ;


    case 'f' :

      model = glm::translate(model,glm::vec3(2.5,0.0,0.0)) ; break ; // Translation

    case 'b' :

      model = glm::translate(model,glm::vec3(-2.5,0.0,0.0)) ; break ; // Translation

    case '+' :

      model = glm::rotate(model,Pi_2,glm::vec3(0,0,1)); break ; //Yaw +90

    case '{' :

      model = glm::scale(model,glm::vec3(0.5))  ; break ;
      
    case '}' :
      
      model = glm::scale(model,glm::vec3(2.0))  ; break ;

    case '[' :

      S_model.push(model) ; break ;

    case ']' :

      model = S_model.top() ; S_model.pop() ; break ;
      
    default : break ;
      
    
    }
    





  }


  glDisableVertexAttribArray(attribute_coord3d);
  glDisableVertexAttribArray(attribute_texcoord);
  glutSwapBuffers();
  

}


void onReshape (int width, int height) {
	screen_width = width;
	screen_height = height;
	glViewport(0, 0, screen_width, screen_height);
}


// On libère les ressources : on vide les buffers

void free_ressources() {
  glDeleteProgram(program);
  glDeleteBuffers(1, &vertices_buffer);
  glDeleteBuffers(1, &texture_buffer);
  glDeleteBuffers(1, &elements_buffer);
  glDeleteTextures(1, &texture_id);

}

// Sortir du mode plein écran

void keyboard( unsigned char key, int x, int y ) {
  switch ( key )
  case 27:
    exit(0) ;
}


int main(int argc, char* argv[]) {

  glewExperimental = true;

  int n;

  cout << "Step ?" << endl ;

  cin >> n ;
  
  LSystem hilbert("F{b+f++[X]}f+{[X]}f+{[X]}f+{X}","+{}[]FXfb") ; 
  hilbert('f') = "f" ; 
  hilbert('F') = "F" ; 
  hilbert('+') = "+" ;
  hilbert('{') = "{" ;
  hilbert('}') = "}" ;
  hilbert('b') = "b" ;
  hilbert('[') = "[" ;
  hilbert(']') = "]" ;
  hilbert('X') = "F{b+f++[X]}f+{[X]}f+{X}";
  
  

  hilbert.SkipStep (n) ;
  pyramid_curve = hilbert.Print();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH|GLUT_STENCIL);
  glutInitWindowSize(screen_width, screen_height);
  glutCreateWindow("Pyramide");
  glutFullScreen();
  glutKeyboardFunc(keyboard);


  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    return -1;
  }

  if (init_ressources()) {
    glutDisplayFunc(onDisplay);
    glutReshapeFunc(onReshape);
    glutIdleFunc(onIdle);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutMainLoop();
  }


  free_ressources() ;
  return 0 ;

}
