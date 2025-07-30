#include <string>
#include <stdexcept>

#include "shaders.hpp"

using namespace std::string_literals;

static const char* vertexShaderCode = R"(
    #version 150
    uniform vec4 scale;

    in vec2 vert;
    in vec2 vertUV;

    out vec2 fragUV;

    void main() {
        gl_Position = vec4(vert.x*scale.x+scale.z, vert.y*scale.y+scale.w, 0.0, 1.0);
        fragUV = vertUV;
    }
)";

static const char* fragmentShaderCode = R"(
    #version 150
    uniform sampler2D tex;

    in vec2 fragUV;

    out vec4 outputColor;

    void main() {
        outputColor = vec4(texture(tex, fragUV).rgb, 1.0);
    }
)";

static std::string getShaderLog(GLuint shader) {
    if (glIsShader(shader)) {
        std::string message = "";

        int infoLogLength = 0;
        int maxLength = infoLogLength;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        char* infoLog = new char[maxLength];

        glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
        if (infoLogLength > 0) {
            message = infoLog;
        }

        delete[] infoLog;

        return message;
    } else {
        return "Wrong shader handle";
    }
}

static std::string getProgramLog(GLuint shaderProgram) {
    if (glIsProgram(shaderProgram)) {
        std::string message = "";

        int infoLogLength = 0;
        int maxLength = infoLogLength;

        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
        char* infoLog = new char[maxLength];

        glGetProgramInfoLog(shaderProgram, maxLength, &infoLogLength, infoLog);
        if (infoLogLength > 0) {
            message = infoLog;
        }

        delete[] infoLog;
        return message;
    } else {
        return "Wrong shader program handle";
    }
}

static GLuint compileShader(const char* source, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    const GLchar* lines[] = {
        source };
    glShaderSource(shader, 1, lines, NULL);
    glCompileShader(shader);
    GLint isCompiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled != GL_TRUE) {
        std::string msg;
        if (shaderType == GL_VERTEX_SHADER) {
            msg = "Vertex shader compile error: ";
        } else if (shaderType == GL_FRAGMENT_SHADER) {
            msg = "Fragment shader compile error: ";
        } else {
            msg = "Shader compile error: ";
        }
        throw std::runtime_error(msg + getShaderLog(shader));
    }
    return shader;
}

static GLuint compileShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode) {
    GLuint program = glCreateProgram();

    GLuint compiledVertexShader = compileShader(vertexShaderCode, GL_VERTEX_SHADER);
    GLuint compiledFragmentShader = compileShader(fragmentShaderCode, GL_FRAGMENT_SHADER);

    glAttachShader(program, compiledVertexShader);
    glAttachShader(program, compiledFragmentShader);
    glLinkProgram(program);
    GLint result = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result != GL_TRUE) {
        throw std::runtime_error("Shader link error: "s + getProgramLog(program));
    }
    glDeleteShader(compiledVertexShader);
    glDeleteShader(compiledFragmentShader);
    return program;
};

GLuint initShaders(GLint& vertex_pos, GLint& vertex_uv, GLint& texture, GLint& scale) {
    GLuint program = compileShaderProgram(vertexShaderCode, fragmentShaderCode);
    vertex_pos = glGetAttribLocation(program, "vert");
    vertex_uv = glGetAttribLocation(program, "vertUV");
    texture = glGetUniformLocation(program, "tex");
    scale = glGetUniformLocation(program, "scale");
    return program;
}

void shadersScale(GLint param, float x, float y, float xoffset, float yoffset) {
    glUniform4f(param, x, y, xoffset, yoffset);
}
