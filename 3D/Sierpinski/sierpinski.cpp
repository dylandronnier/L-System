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

// Fichier pour la compilation et l'exécution des shaders

// include "shader_utils.h"

#include "shader.hpp"

// Fichier de gestion des L-Systems

#include "lsystem.h"

#define _USE_MATH_DEFINES

const float PI = M_PI ;

int screen_width = 1000 , screen_height = 700 ;

GLuint vertices_buffer , colors_buffer , elements_buffer ;
GLuint program;
GLint mvp_shader ;
GLint attribute_coord3d, attribute_v_color;

float angle = 0.0f ;
string pyramid_curve ;


// Variable globale glm

glm::vec3 rotspeeds ;

// Définition de la courbe représentée par un L-System

int init_ressources () {

  // Sommets de la ligne 

  static const GLfloat pyramid[] = 
    {
        0.0f , 0.0f , 0.0f,
	1.0f , 0.0f  , 0.0f ,
	0.5f , sqrt(3.0f)/ 2.0f , 0.0f,
        0.5f , sqrt(3.0f) / 6.0f , sqrt(6.0f) / 3.0f //top 
   };

  // On entre l'objet dans le buffer des sommets

  glGenBuffers(1, &vertices_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertices_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof pyramid , pyramid , GL_STATIC_DRAW);


  // Couleur des sommets 

  static const GLfloat pyramid_color[] = 
    {	
      1.0f, 0.0f, 0.0f, // red
      0.0f, 1.0f, 0.0f, // green
      0.0f, 0.0f, 1.0f, // blue
      1.0f, 1.0f, 0.0f // yellow 
    }; 
  
  // On remplit le buffer des couleurs 

  glGenBuffers(1, &colors_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, colors_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof pyramid_color , pyramid_color, GL_STATIC_DRAW);


  GLushort pyramid_elements[] = 
    {
      // top
      0, 1, 2,
      0, 2, 3,
      0, 1, 3,
      1, 2, 3
      
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

  program = LoadShaders( "../Shaders/sierpinski.vert", "../Shaders/sierpinski.frag" );
  
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

  attribute_coord3d = glGetAttribLocation(program,"coord3d");

  attribute_v_color = glGetAttribLocation(program,"vertexColor");

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

  // 2nd buffer : les couleurs

  glEnableVertexAttribArray(attribute_v_color);
  glBindBuffer(GL_ARRAY_BUFFER, colors_buffer);
  glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
			);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements_buffer);

  int size;

  stack<glm::mat4> S_model ;


  glm::mat4 anim =
    glm::rotate(glm::mat4(1.0f), angle * rotspeeds.x, glm::vec3(1, 0, 0)) *	// axe des X
    glm::rotate(glm::mat4(1.0f), angle * rotspeeds.y, glm::vec3(0, 1, 0)) *	// axe des Y
    glm::rotate(glm::mat4(1.0f), angle * rotspeeds.z, glm::vec3(0, 0, 1));	// axe des Z


  // Matrice model : Coordonnées objet -> Coordonnées monde

  glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(-0.5f , -sqrt(3.0f) / 6.0f , -sqrt(6.0f) / 12.0f)) ;

  // Matrice view : Coordonnées du monde -> Coordonnées caméra

  glm::mat4 view = glm::lookAt(glm::vec3(0.0, -2.0, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.1, 1.0, 0.0));


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

      model = glm::translate(model,glm::vec3(0.5f,0.0f,0.0f)) ; break ; // Translation

    case 'b' :

      model = glm::translate(model,glm::vec3(-0.5f,0.0f,0.0f)) ; break ; // Translation

    case '+' :

      model = glm::rotate(model,PI/3.0f,glm::vec3(0,0,1)); break ; //Yaw +90

    case '-' :

      model = glm::rotate(model,-PI/3.0f,glm::vec3(0,0,1)); break ; //Yaw +90

    case '{' :

      model = glm::scale(model,glm::vec3(0.5f))  ; break ;
      
    case '}' :
      
      model = glm::scale(model,glm::vec3(2.0f))  ; break ;

    case '^' :
      
      model = glm::rotate(model,PI / 3.0f ,glm::vec3(0.0f,- sqrt(6.0f) / 3.0f,sqrt(3.0f) / 6.0f)); break ;
      
    case '&' :

      model = glm::rotate(model,-PI / 3.0f ,glm::vec3(0.0f,- sqrt(6.0f) / 3.0f,sqrt(3.0f) / 6.0f)); break ;
      
    default : break ;
      
    
    }

  }


  glDisableVertexAttribArray(attribute_coord3d);
  glDisableVertexAttribArray(attribute_v_color);
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
  glDeleteBuffers(1, &colors_buffer);

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
  
  LSystem hilbert("F","+-Ffb^&{}") ; 
  hilbert('F') = "{F}f{F}b+f-{F}+b-^f&{F}^b&" ; 
  hilbert('f') = "f" ; 
  hilbert('+') = "+" ;
  hilbert('-') = "-" ;
  hilbert('b') = "b" ;
  hilbert('{') = "{" ;
  hilbert('}') = "}" ;
  hilbert('&') = "&" ;
  hilbert('^') = "^" ;
  
  

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
