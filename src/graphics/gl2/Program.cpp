#include "Program.h"
#include "FileSystem.h"
#include "StringRange.h"
#include "StringF.h"
#include "OS.h"
#include "graphics/Shader.h"

namespace Graphics {

namespace GL2 {

static const char *s_glslVersion = "#version 120\n";

struct Shader {
	Shader(GLenum type, const std::string &filename, const std::string &defines) {
		RefCountedPtr<FileSystem::FileData> code = FileSystem::gameDataFiles.ReadFile(filename);

		if (!code)
			OS::Error("Could not load %s", filename.c_str());

		AppendSource(s_glslVersion);
		AppendSource(code->AsStringRange());
		shader = glCreateShader(type);
		Compile(shader);

		// CheckGLSL may use OS::Warning instead of OS::Error so the game may still (attempt to) run
		if (!Graphics::Shader::CheckGLSLErrors(filename.c_str(), shader))
			throw ShaderException();
	};

	~Shader() {
		glDeleteShader(shader);
	}

	GLuint shader;

private:
	void AppendSource(const char *str)
	{
		blocks.push_back(str);
		block_sizes.push_back(std::strlen(str));
	}

	void AppendSource(StringRange str)
	{
		blocks.push_back(str.begin);
		block_sizes.push_back(str.Size());
	}

	void Compile(GLuint shader_id)
	{
		assert(blocks.size() == block_sizes.size());
		glShaderSource(shader_id, blocks.size(), &blocks[0], &block_sizes[0]);
		glCompileShader(shader_id);
	}

	std::vector<const char*> blocks;
	std::vector<GLint> block_sizes;
};

Program::Program(const std::string &name)
: m_name(name)
{
	LoadShaders(name);
	InitUniforms();
}

Program::~Program()
{
	glDeleteProgram(m_program);
}

void Program::Reload()
{
	Unuse();
	glDeleteProgram(m_program);
	LoadShaders(m_name);
	InitUniforms();
}

void Program::Use()
{
	glUseProgram(m_program);
}

void Program::Unuse()
{
	glUseProgram(0);
}

//load, compile and link
void Program::LoadShaders(const std::string &name)
{
	const std::string filename = std::string("shaders/gl2/") + name;

	//load, create and compile shaders
	Shader vs(GL_VERTEX_SHADER, filename + ".vert", "");
	Shader fs(GL_FRAGMENT_SHADER, filename + ".frag", "");

	//create program, attach shaders and link
	m_program = glCreateProgram();
	glAttachShader(m_program, vs.shader);
	glAttachShader(m_program, fs.shader);
	glLinkProgram(m_program);

	Graphics::Shader::CheckGLSLErrors(name.c_str(), m_program);

	//shaders may now be deleted
}

void Program::InitUniforms()
{

}

} // GL2

} // Graphics
