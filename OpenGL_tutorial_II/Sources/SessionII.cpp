// Just using the same header to make it easier
#include <SessionII.hpp>


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


std::string preamble =
	"Session II Code\n";

int main(int argc, char **argv)
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
	#endif


	// Print Preamble
	std:printf(preamble.c_str());


	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Session II", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	//  Uncomment below to actually test for depth. 
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader program
	// ------------------------------------
	Shader ourShader(PROJECT_SOURCE_DIR "/OpenGL_tutorial_II/Shaders/shader.vert", PROJECT_SOURCE_DIR "/OpenGL_tutorial_II/Shaders/shader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	// load and create a texture 
	// -------------------------
	unsigned int texture1, texture2;
	// texture 1
	// ---------
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char *data = stbi_load(PROJECT_SOURCE_DIR "/OpenGL_tutorial_II/Media/textures/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// texture 2
	// ---------
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	data = stbi_load(PROJECT_SOURCE_DIR "/OpenGL_tutorial_II/Media/textures/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	ourShader.use();
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);

	// Only print the first loop
	bool virgin = true;
	std::cout << "Example of defining a matrix" << std::endl <<
		glm::to_string(glm::mat3(1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f)) << std::endl << std::endl;

	// Example Translation, multiply, and subtract: 
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans(1.0f);
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	std::cout << "Before translation: " << glm::to_string(vec) << std::endl;
	vec = trans * vec;
	std::cout << "After translation: " << glm::to_string(vec) << std::endl;
	vec -= glm::vec4(1.0f, 1.0f, 0.0, 0.0f);
	std::cout << "After subtraction: " << glm::to_string(vec) << std::endl << std::endl;

	// Example of mulitpling matrices
	std::cout << "Matrix: " << glm::to_string(trans) << std::endl;
	trans = trans*trans;
	std::cout << "Matrix squared: " << glm::to_string(trans) << std::endl << std::endl;
	

	// render loop
	// -----------
	// Axis rotation rates and angles
	float xRotationRate = 1.0f;
	float xRotationAngle = glm::radians(90.0f);
	float yRotationRate = 1.0f;
	float yRotationAngle = glm::radians(90.0f);
	float zRotationRate = 1.0f;
	float zRotationAngle = glm::radians(90.0f);
	// Axis scaling
	float xScale = 1.25f;
	float yScale = 1.25f;
	float zScale = 1.25f;
	// Axis Positions
	float xPosition = 0.0f;
	float yPosition = 0.0f;
	float zPosition = -1.0f;
	const float rotationRateStep = 5.0f;
	float lastFrameTime = (float)glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		float currentFrameTime = (float)glfwGetTime();
		float deltaTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		// create transformations
		glm::mat4 model(1.0f);
		glm::mat4 view(1.0f);
		glm::mat4 projection(1.0f);
		bool scaleable = false;
		bool translation = false;

		// input
		// -----
		processInput(window);
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		{
			scaleable = true;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
		{
			translation = true;
		}
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)	//U
		{
			if (scaleable)
			{
				xScale += 0.5f * deltaTime;
				std::cout << "Scaleable = true" << std::endl;
			}
			else if (translation)
			{
				xPosition += 0.5f * deltaTime;
				std::cout << "Translation = true" << std::endl;
			}
			else
			{
				xRotationRate += rotationRateStep * deltaTime;
				std::cout << "Increase Rotation Rate in X axis " << std::endl;
			}
			
		}
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)	//J
		{
			if (scaleable)
			{
				xScale = std::max(0.0f, xScale - 0.5f * deltaTime);
				std::cout << "Scaleable = true" << std::endl;
			}
			else if (translation)
			{
				xPosition -= 0.5f * deltaTime;
				std::cout << "Translation = true" << std::endl;
			}
			else
			{
			xRotationRate = std::max(0.0f, xRotationRate - rotationRateStep * deltaTime);
			std::cout << "Decrease Rotation Rate in X axis" << std::endl;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)	//I
		{
			if (scaleable)
			{
				yScale += 0.5f * deltaTime;
				std::cout << "Scaleable = true" << std::endl;
			}
			else if (translation)
			{
				std::cout << "Translation = true" << std::endl;
			}
			else
			{
			yRotationRate += rotationRateStep * deltaTime;
			std::cout << "Increase Rotation Rate in Y axis" << std::endl;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)	//K
		{
			if (scaleable)
			{
				yScale = std::max(0.0f, yScale - 0.5f * deltaTime);
				std::cout << "Scaleable = true" << std::endl;
			}
			else if (translation)
			{
				std::cout << "Translation = true" << std::endl;
			}
			else
			{
			yRotationRate = std::max(0.0f, yRotationRate - rotationRateStep * deltaTime);
			std::cout << "Decrease Rotation Rate in Y axis" << std::endl;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)	//O
		{
			if (scaleable)
			{
				zScale += 0.5f * deltaTime;
				std::cout << "Scaleable = true" << std::endl;
			}
			else if (translation)
			{
				std::cout << "Translation = true" << std::endl;
			}
			else
			{
			zRotationRate += rotationRateStep * deltaTime;
			std::cout << "Increase Rotation Rate in Z axis" << std::endl;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)	//L
		{
			if (scaleable)
			{
				zScale = std::max(0.0f, zScale - 0.5f * deltaTime);
				std::cout << "Scaleable = true" << std::endl;
			}
			else if (translation)
			{
				std::cout << "Translation = true" << std::endl;
			}
			else
			{
			zRotationRate = std::max(0.0f, zRotationRate - rotationRateStep * deltaTime);
			std::cout << "Decrease Rotation Rate in Z axis" << std::endl;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)	//R
		{
			// Reset all rotation rates to 1.0f
			xRotationRate = 1.0f;
			yRotationRate = 1.0f;
			zRotationRate = 1.0f;
			// Reset all scaling to 1.25f
			xScale = 1.25f;
			yScale = 1.25f;
			zScale = 1.25f;
			// Reset all positions to originals
			xPosition = 0.0f;
			yPosition = 0.0f;
			zPosition = -1.0f;
			std::cout << "Reset Rotation Rate in all axis" << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)	//P
		{
			std::cout << "Uniform Scaling" << std::endl;
		}

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

															// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// activate shader
		ourShader.use();

		if (virgin)
		{
			std::cout << "model matrix initialization" << std::endl <<
				glm::to_string(model) << std::endl << std::endl;
		}
		
		// Applying transformation BACKWARDs.  We want this box to rotate in position so first we apply a translation (the last applied to the box)
		model = glm::translate(model, glm::vec3(xPosition, yPosition, zPosition));

		xRotationAngle += xRotationRate * deltaTime;
		yRotationAngle += yRotationRate * deltaTime;
		zRotationAngle += zRotationRate * deltaTime;
		glm::vec3 angle(xRotationAngle, yRotationAngle, zRotationAngle);
		if (virgin)
		{
			std::cout << "model matrix after translation of -1 in z dimension" << std::endl <<
				glm::to_string(model) << std::endl << std::endl;
		}

		// Then we rotate the object based on how much time has passed (so continually rotating it) 
		//  Splitting up each dimension to make it easier to weight rotation in each dimension
		model = glm::rotate(model, angle.x, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, angle.y, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, angle.z, glm::vec3(0.0f, 0.0f, 1.0f));

		if (virgin)
		{
			std::cout << "model matrix now after rotation in all dimensions" << std::endl <<
				glm::to_string(model) << std::endl <<  "Angle: " << glm::to_string(glm::degrees(angle)) <<std::endl << std::endl;
		}

		// Finally, we scale the object by the specified scale factors in each dimension
		model = glm::scale(model, glm::vec3(xScale, yScale, zScale));  		// M scaled by the vector 

		if (virgin)
		{
			std::cout << "model matrix now after scale of 1.25 in all dimensions" << std::endl <<
				glm::to_string(model) << std::endl << std::endl << std::endl;
		}


		//  Look at is just pointing at origin so would be an identity matrix so excluded from this example
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		// retrieve the matrix uniform locations
		unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
		unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
		// pass them to the shaders (3 different ways)
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		ourShader.setMat4("projection", projection);

		// render box
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();

		// Set it to stop printing after the first loop
		virgin = false;
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
