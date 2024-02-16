#include <glad/glad.h>
class Logger {
  public:
	void error(const char* message);

  private:
	GLenum glError(const char* file, int line);
};
