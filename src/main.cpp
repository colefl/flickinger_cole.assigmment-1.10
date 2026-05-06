#include "config.h"
#include "triangle_mesh.h"
#include "circle.h"


unsigned int make_shader(const std::string& vertex_filepath, const std::string& fragment_filepath);
unsigned int make_module(const std::string& filepath, unsigned int module_type);
void setOrtho(unsigned int shader, float left, float right, float bottom, float top);
std::vector<Circle*> populateCircles(int num_of_objs);
float calcDist(Circle* obj, Circle* comp_obj);

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

int main(){

    const float WORLD_WIDTH  = 640.0f;
    const float WORLD_HEIGHT = 480.0f;

    // std::ifstream file;

    // std::string line;

    // file.open("../src/shaders/vertex.txt");
    // while(std::getline(file, line)){
    //     std::cout << line << std::endl;
    // }

    srand(time(NULL));

    GLFWwindow* window;

    if(!glfwInit()){
        std::cout << "GLFW didn't start" <<std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My window haha", NULL, NULL); //The monitor(4th parameter) tells us which monitor to show this up on

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        glfwTerminate();
        return -1;
    }

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // int w,h;
    // glfwGetFramebufferSize(window, &w, &h);
    // glViewport(0, 0, w, h);

    //std::cout << "Hello I make it before triangle" << std::endl;

    //TriangleMesh* triangle = new TriangleMesh();
    float lastTime = glfwGetTime();

    int num_of_objs = 10;
    int j;

    std::vector<Circle*> objs = populateCircles(num_of_objs);

    //Circle* circle = new Circle(120.0f, 120.0f, 60.0f, 30);

    //std::cout << "Hello I make it after triangle" << std::endl;
    
    //float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;

    unsigned int shader = make_shader(
        "../src/shaders/vertex.txt",
        "../src/shaders/fragment.txt"
    );

    glUseProgram(shader);
    setOrtho(shader, 0.0f, WORLD_WIDTH, 0.0f, WORLD_HEIGHT);


    float gravity = 50000.0f;
    int obj_idx;

    //int x = 0; //Debug to cancel after one iteration
    while(!glfwWindowShouldClose(window)){
    //while(x != 3){
        float now = glfwGetTime();
        float dt = now - lastTime; //Simple little delta time stuff
        lastTime = now;

        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        // for(j = 0; j < num_of_objs; j++){
        //     objs[j]->update(dt);
        //     // Pass position offset and color as uniforms
        //     int offsetLoc = glGetUniformLocation(shader, "offset");
        //     glUniform2f(offsetLoc, objs[j]->x, objs[j]->y);

        //     int colorLoc = glGetUniformLocation(shader, "color");
        //     glUniform3f(colorLoc, 1.0f, 0.3f, 0.1f); //orange-ish
        // }
        //circle->update(dt);

        std::vector<float> accl_x(num_of_objs, 0.0f);
        std::vector<float> accl_y(num_of_objs, 0.0f);
    
        for(j = 0; j < num_of_objs; j++){
            //int obj_idx;
            for(obj_idx = j + 1; obj_idx < num_of_objs; obj_idx++){
                float dx = objs[obj_idx]->x - objs[j]->x; // direction FROM i TO k
                float dy = objs[obj_idx]->y - objs[j]->y;
                float dist = sqrt(dx*dx + dy*dy) + 25.0f; // softening
                float force  = gravity * (objs[obj_idx]->mass * objs[j]->mass) / (dist * dist);
                //std::cout << force << std::endl;
                // if(dist < objs[j]->radius - objs[obj_idx]->radius + 5.0f){ //5.0 as a buffer, calculating if they're collided
                    //I've never used openGL before and I hate this for some reason it used to be easy and then they decided to make it like 9 times more difficult with this shader and fragment bs. Idk how attributes work still but uunluckily I found the circle thing online sorta kinda but it was on a deprecated version so I had to read through the API for like an hour trying to find the array linking 

                // }
                float fx = force * ((objs[obj_idx]->x - objs[j]->x) / dist); //F = gravity times dx/dist
                float fy = force * ((objs[obj_idx]->y - objs[j]->y) / dist);

                //std::cout << "fx: " << fx << " and fy: " << fy << std::endl;

                //Object 1
                accl_x[obj_idx] -= fx / objs[obj_idx]->mass;
                accl_y[obj_idx] -= fy / objs[obj_idx]->mass;


                //Object 2
                accl_x[j] += fx / objs[j]->mass;
                accl_y[j] += fy / objs[j]->mass;

                if(dist < std::abs(objs[j]->radius - objs[obj_idx]->radius) + 5.0f){
                    //Need to calculate angle based on the change in x and y of both object
                    double theta1 = acos((double)dx / hypot((double)dx, (double)dy)); //We have the hypotenuse of the dx / hypotenuse of the first one
                    //https://stackoverflow.com/questions/345838/ball-to-ball-collision-detection-and-handling
                }

                //std::cout << j << " Accl_x: " << accl_x[j] << " and Accl_y: " << accl_y[j] << " and dt: " << dt << "\n" << std::endl;
            }
        }

        glUseProgram(shader);

        for(j = 0; j < num_of_objs; j++){
            objs[j]->update(dt, accl_x[j], accl_y[j]);
        }


        for(j = 0; j < num_of_objs; j++){
            //objs[j]->update(dt, accl_x[j], accl_y[j]);
            //std::cout << "Accl_x: " << accl_x[j] << " and Accl_y: " << accl_y[j] << " and dt: " << dt << std::endl;

            int offsetLoc = glGetUniformLocation(shader, "offset"); //Let's things be offset
            glUniform2f(offsetLoc, objs[j]->x, objs[j]->y);

            int colorLoc = glGetUniformLocation(shader, "color");
            glUniform3f(colorLoc, (abs((int)(accl_x[j]) * 0.05)), (abs((int)(accl_y[j]) * 0.05)), 0.0f);

            objs[j]->draw(); // draw immediately after setting THIS circle's uniforms
        }



        //circle->draw();
        for(j = 0; j < num_of_objs; j++){
            objs[j]->draw();
        }
        //x++;

        glfwSwapBuffers(window);
    }
	
    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}

unsigned int make_shader(const std::string& vertex_filepath, const std::string& fragment_filepath) {
	//To store all the shader modules
	std::vector<unsigned int> modules;

	//Add a vertex shader module
	modules.push_back(make_module(vertex_filepath, 
                GL_VERTEX_SHADER));

	//Add a fragment shader module
	modules.push_back(make_module(fragment_filepath, 
                GL_FRAGMENT_SHADER));

	//Attach all the modules then link the program
	unsigned int shader = glCreateProgram();
	for (unsigned int shaderModule : modules) {
		glAttachShader(shader, shaderModule);
	}
	glLinkProgram(shader);

	//Check the linking worked
	int success;
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		char errorLog[1024];
		glGetProgramInfoLog(shader, 1024, 
                NULL, errorLog);
		std::cout << "Shader linking error:\n" << errorLog << '\n';
	}

	//Modules are now unneeded and can be freed
	for (unsigned int shaderModule : modules) {
		glDeleteShader(shaderModule);
	}

	return shader;
}

unsigned int make_module(const std::string& filepath, unsigned int module_type) {
	std::ifstream file;
	std::stringstream bufferedLines;
	std::string line;

	file.open(filepath);
	while (std::getline(file, line)) {
		//std::cout << line << std::endl;
		bufferedLines << line << '\n';
	}
	std::string shaderSource = bufferedLines.str();
	const char* shaderSrc = shaderSource.c_str();
	bufferedLines.str("");
	file.close();

	unsigned int shaderModule = glCreateShader(module_type);
	glShaderSource(shaderModule, 1, &shaderSrc, NULL);
	glCompileShader(shaderModule);

	int success;
	glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
	if (!success) {
		char errorLog[1024];
		glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
		std::cout << "Shader Module compilation error:\n" << errorLog << std::endl;
	}

	return shaderModule;
}


/*
This method creates an orthographic screen for us to draw on*/
void setOrtho(unsigned int shader, float left, float right, float bottom, float top) {
    float tx = -(right + left) / (right - left);
    float ty = -(top + bottom) / (top - bottom);

    float matrix[16] = {
        2.0f/(right-left),  0,                  0,  0,
        0,                  2.0f/(top-bottom),   0,  0,
        0,                  0,                  -1,  0,
        tx,                 ty,                  0,  1
    };
    int loc = glGetUniformLocation(shader, "projection");
    glUniformMatrix4fv(loc, 1, GL_FALSE, matrix);
}

std::vector<Circle*> populateCircles(int num_of_objs){
    int rand_num = rand();
    std::vector<Circle*> tmp;
    //Circle* tmp_crlc;
    int i;
    for(i = 0; i < num_of_objs; i++){
        tmp.push_back(new Circle((float)(rand_num % SCREEN_WIDTH), (float)(rand_num % SCREEN_HEIGHT),(float)(7 * (1 + rand_num % 5)), 30, (float)(1 + rand_num % 5)));
        rand_num = rand();
        //std::cout << "rand_num " << rand_num << std::endl;
    }
    return tmp;
}

//Used to calculate the distance between two objects to be compared to the difference of their radii
float calcDist(Circle* obj, Circle* comp_obj){
    //std::cout << "dx: " << comp_obj->x - obj->x << " and dy: " << comp_obj->y - obj->y << std::endl;
    return (float) sqrt(((comp_obj->x - obj->x)*(comp_obj->x - obj->x) + (comp_obj->y - obj->y)*(comp_obj->y - obj->y)));
}